/**
 **************************************************************************
 * @file     BspUart.c
 * @brief    UART驱动 FIFO
 */

/* includes ------------------------------------------------------------------*/
#include "BspConfig.h"

/** @addtogroup UART驱动
 * @{
 */

#if (config_BSPUART_USE_UART1 == 1)
BspUart_S gUart1;
uint8_t sUart1TxBuff[BSPUART1_TXBUFF_SIZE];
uint8_t sUart1RxBuff[BSPUART1_RXBUFF_SIZE];
BspUart_Setting_S gUart1_Setting = {115200, USART_DATA_8BITS, USART_STOP_1_BIT, USART_PARITY_NONE};
#endif /*config_BSPUART_USE_UART1*/

#if (config_BSPUART_USE_UART2 == 1)
BspUart_S gUart2;
uint8_t sUart2TxBuff[BSPUART2_TXBUFF_SIZE];
uint8_t sUart2RxBuff[BSPUART2_RXBUFF_SIZE];
BspUart_Setting_S gUart2_Setting = {115200, USART_DATA_8BITS, USART_STOP_1_BIT, USART_PARITY_NONE};
#endif /*config_BSPUART_USE_UART2*/

#if (config_BSPUART_USE_UART3 == 1)
BspUart_S gUart3;
uint8_t sUart3TxBuff[BSPUART3_TXBUFF_SIZE];
uint8_t sUart3RxBuff[BSPUART3_RXBUFF_SIZE];
BspUart_Setting_S gUart3_Setting = {115200, USART_DATA_8BITS, USART_STOP_1_BIT, USART_PARITY_NONE};
#endif /*config_BSPUART_USE_UART3*/

#if (config_BSPUART_USE_UART4 == 1)
BspUart_S gUart4;
uint8_t sUart4TxBuff[BSPUART4_TXBUFF_SIZE];
uint8_t sUart4RxBuff[BSPUART4_RXBUFF_SIZE];
BspUart_Setting_S gUart4_Setting = {115200, USART_DATA_8BITS, USART_STOP_1_BIT, USART_PARITY_NONE};
#endif /*config_BSPUART_USE_UART4*/

#if (config_BSPUART_USE_UART5 == 1)
BspUart_S gUart5;
uint8_t sUart5TxBuff[BSPUART5_TXBUFF_SIZE];
uint8_t sUart5RxBuff[BSPUART5_RXBUFF_SIZE];
BspUart_Setting_S gUart5_Setting = {115200, USART_DATA_8BITS, USART_STOP_1_BIT, USART_PARITY_NONE};
#endif /*config_BSPUART_USE_UART5*/

#if (config_BSPUART_USE_UART6 == 1)
BspUart_S gUart6;
uint8_t sUart6TxBuff[BSPUART6_TXBUFF_SIZE];
uint8_t sUart6RxBuff[BSPUART6_RXBUFF_SIZE];
BspUart_Setting_S gUart6_Setting = {115200, USART_DATA_8BITS, USART_STOP_1_BIT, USART_PARITY_NONE};
#endif /*config_BSPUART_USE_UART6*/

#if (config_BSPUART_USE_UART7 == 1)
BspUart_S gUart7;
uint8_t sUart7TxBuff[BSPUART7_TXBUFF_SIZE];
uint8_t sUart7RxBuff[BSPUART7_RXBUFF_SIZE];
BspUart_Setting_S gUart7_Setting = {115200, USART_DATA_8BITS, USART_STOP_1_BIT, USART_PARITY_NONE};
#endif /*config_BSPUART_USE_UART7*/

#if (config_BSPUART_USE_UART8 == 1)
BspUart_S gUart8;
uint8_t sUart8TxBuff[BSPUART8_TXBUFF_SIZE];
uint8_t sUart8RxBuff[BSPUART8_RXBUFF_SIZE];
BspUart_Setting_S gUart8_Setting = {115200, USART_DATA_8BITS, USART_STOP_1_BIT, USART_PARITY_NONE};
#endif /*config_BSPUART_USE_UART8*/

extern rt_base_t rt_hw_interrupt_disable(void);
extern void rt_hw_interrupt_enable(rt_base_t level);
extern rt_int32_t rt_vsnprintf(char *buf, rt_size_t size, const char *fmt, va_list args);

static BspUart_S *BspUart_Com2Uart(BspUartCom_E Com);
BspUartCom_E BspUart_Uart2Com(BspUart_S *p_Uart);

void BspUart_ParamLoad(BspUartCom_E Com, usart_type *p_huart, BspUart_Setting_S *p_Setting, BspUart_Param_S *p_Para);

static const BspUartLib_S BspUartLib[config_BSPUART_NUM] =
    {
        {&gUart1, BspUartCom_RS232},
        {&gUart3, BspUartCom_USB},
        {&gUart2, BspUartCom_DUT},
        {&gUart4, BspUartCom_DUT2},
};

/**
 * @brief  初始化UART FIFO 参数
 * @param  none
 * @retval none
 */
void BspUart_Init(void)
{ // 波特率大于115200时建议使用DMA接收 DMA发送和接收可以被单独地启用或关闭,默认是中断收发
  BspUart_Param_S Param;
  BspUart_S *p_Uart;

  { // BspUartCom_RS232
    memset(&Param, 0, sizeof(BspUart_Param_S));

    Param.irqn = USART1_IRQn;
    Param.MaxIdleTime = 50;
    Param.p_ucaTxBuff = sUart1TxBuff;
    Param.p_ucaRxBuff = sUart1RxBuff;
    Param.ulTxBuffSize = sizeof(sUart1TxBuff);
    Param.ulRxBuffSize = sizeof(sUart1RxBuff);

    Param.p_SendBefore = default_process;
    Param.p_SendOver = default_process;
    Param.p_RecvDone = default_process;
    Param.p_Idle = default_process;

    BspUart_ParamLoad(BspUartCom_RS232, USART1, &gUart1_Setting, &Param);

    p_Uart = BspUart_Com2Uart(BspUartCom_RS232);
    p_Uart->ucMutexIdx = BspConfig_MutexCreat("Com_RS232");
  }

  { // BspUartCom_USB
    memset(&Param, 0, sizeof(BspUart_Param_S));

    Param.irqn = USART3_IRQn;
    Param.MaxIdleTime = 50;
    Param.p_ucaTxBuff = sUart3TxBuff;
    Param.p_ucaRxBuff = sUart3RxBuff;
    Param.ulTxBuffSize = sizeof(sUart3TxBuff);
    Param.ulRxBuffSize = sizeof(sUart3RxBuff);

    Param.p_SendBefore = default_process;
    Param.p_SendOver = default_process;
    Param.p_RecvDone = default_process;
    Param.p_Idle = default_process;

    BspUart_ParamLoad(BspUartCom_USB, USART3, &gUart3_Setting, &Param);

    p_Uart = BspUart_Com2Uart(BspUartCom_USB);
    p_Uart->ucMutexIdx = BspConfig_MutexCreat("Com_USB");
  }

  { // BspUartCom_DUT
    memset(&Param, 0, sizeof(BspUart_Param_S));

    Param.irqn = USART2_IRQn;
    Param.MaxIdleTime = 50;
    Param.p_ucaTxBuff = sUart2TxBuff;
    Param.p_ucaRxBuff = sUart2RxBuff;
    Param.ulTxBuffSize = sizeof(sUart2TxBuff);
    Param.ulRxBuffSize = sizeof(sUart2RxBuff);

    Param.p_SendBefore = default_process;
    Param.p_SendOver = default_process;
    Param.p_RecvDone = default_process;
    Param.p_Idle = default_process;

    BspUart_ParamLoad(BspUartCom_DUT, USART2, &gUart2_Setting, &Param);

    p_Uart = BspUart_Com2Uart(BspUartCom_DUT);
    p_Uart->ucMutexIdx = BspConfig_MutexCreat("Com_DUT");
  }

  { // BspUartCom_DUT2
    memset(&Param, 0, sizeof(BspUart_Param_S));

    Param.irqn = UART4_IRQn;
    Param.MaxIdleTime = 50;
    Param.p_ucaTxBuff = sUart4TxBuff;
    Param.p_ucaRxBuff = sUart4RxBuff;
    Param.ulTxBuffSize = sizeof(sUart4TxBuff);
    Param.ulRxBuffSize = sizeof(sUart4RxBuff);

    Param.p_SendBefore = default_process;
    Param.p_SendOver = default_process;
    Param.p_RecvDone = default_process;
    Param.p_Idle = default_process;

    BspUart_ParamLoad(BspUartCom_DUT2, UART4, &gUart4_Setting, &Param);

    p_Uart = BspUart_Com2Uart(BspUartCom_DUT2);
    p_Uart->ucMutexIdx = BspConfig_MutexCreat("Com_DUT2");
  }
}

/**
 * @brief  设置UART回调函数
 * @param  Com:UART代号
 * @param  p_SendBefore:UART发送前调用
 * @param  p_SendOver:UART发送后调用
 * @param  p_ReceiveFinish:UART接受完成时调用
 * @retval none
 */
void BspUart_CallBack_Set(BspUartCom_E Com,
                          pBspUart_SendBefor_TypeDef p_SendBefore,
                          pBspUart_SendOver_TypeDef p_SendOver,
                          pBspUart_RecvDone_TypeDef p_RecvDone)
{
  BspUart_S *p_Uart;

  p_Uart = BspUart_Com2Uart(Com);

  if (p_SendBefore)
  {
    p_Uart->p_SendBefore = p_SendBefore; /* 发送数据前的回调函数 */
  }

  if (p_SendOver)
  {
    p_Uart->p_SendOver = p_SendOver; /* 发送完毕后的回调函数 */
  }

  if (p_RecvDone)
  {
    p_Uart->p_RecvDone = p_RecvDone; /* 串口收完数据的回调函数指针 */
  }
}

/**
 * @brief  COM转换到UART
 * @param  Com:UART代号
 * @retval none
 */
static BspUart_S *BspUart_Com2Uart(BspUartCom_E Com)
{
  if (Com >= config_BSPUART_NUM)
    return BspUartLib[0].p_Uart;

  return BspUartLib[Com].p_Uart;
}

/**
 * @brief  UART转换到COM
 * @param  p_Uart:UART结构体指针
 * @retval none
 */
BspUartCom_E BspUart_Uart2Com(BspUart_S *p_Uart)
{
  uint8_t i;

  for (i = 0; i < config_BSPUART_NUM; i++)
  {
    if (BspUartLib[i].p_Uart == p_Uart)
    {
      return BspUartLib[i].Com;
    }
  }

  return (BspUartCom_E)0;
}

/**
 * @brief  UART加载参数
 * @param  Com:UART代号
 * @param  p_huart:UART硬件结构体指针
 * @param  p_Setting:UART硬件基本参数结构体指针
 * @param  p_Param:UART FIFO参数结构体指针
 * @retval none
 */
void BspUart_ParamLoad(BspUartCom_E Com, usart_type *p_huart, BspUart_Setting_S *p_Setting, BspUart_Param_S *p_Param)
{
  BspUart_S *p_Uart;

  p_Uart = BspUart_Com2Uart(Com);

  memset(p_Uart, 0, sizeof(BspUart_S));

  { // 设置基本参数
    p_Uart->p_huart = p_huart;
    p_Uart->p_Setting = p_Setting;
    p_Uart->Flag.ucValue = 0;
    p_Uart->irqn = p_Param->irqn;
  }

  {                                             // 用户自定义部分
    p_Uart->MaxIdleTime = p_Param->MaxIdleTime; /* 最大超时时间 */

    p_Uart->p_DmaTxChannel = p_Param->p_DmaTxChannel;
    p_Uart->p_DmaRxChannel = p_Param->p_DmaRxChannel;
    p_Uart->p_DmaTxInitStruct = p_Param->p_DmaTxInitStruct;
    p_Uart->p_DmaRxInitStruct = p_Param->p_DmaRxInitStruct;
    p_Uart->DmaTxPriority = p_Param->DmaTxPriority;
    p_Uart->DmaRxPriority = p_Param->DmaRxPriority;

    p_Uart->p_SendBefore = p_Param->p_SendBefore;
    p_Uart->p_SendOver = p_Param->p_SendOver;
    p_Uart->p_RecvDone = p_Param->p_RecvDone;
    p_Uart->p_Idle = p_Param->p_Idle;
  }

  { // 环形缓冲
    chry_ringbuffer_init(&p_Uart->TxFifo, p_Param->p_ucaTxBuff, p_Param->ulTxBuffSize);
    chry_ringbuffer_init(&p_Uart->RxFifo, p_Param->p_ucaRxBuff, p_Param->ulRxBuffSize);
  }

  {
    usart_interrupt_enable(p_Uart->p_huart, USART_RDBF_INT, FALSE);
    usart_interrupt_enable(p_Uart->p_huart, USART_TDBE_INT, FALSE);

    if ((p_Uart->p_DmaTxChannel) && (p_Uart->p_DmaTxInitStruct))
    {
      p_Uart->Flag.bTxByDma = true;

      dma_reset(p_Uart->p_DmaTxChannel);

      dma_default_para_init(p_Uart->p_DmaTxInitStruct);
      p_Uart->p_DmaTxInitStruct->buffer_size = 0;
      p_Uart->p_DmaTxInitStruct->direction = DMA_DIR_MEMORY_TO_PERIPHERAL;
      p_Uart->p_DmaTxInitStruct->memory_base_addr = (uint32_t)0;
      p_Uart->p_DmaTxInitStruct->memory_data_width = DMA_MEMORY_DATA_WIDTH_BYTE;
      p_Uart->p_DmaTxInitStruct->memory_inc_enable = TRUE;
      p_Uart->p_DmaTxInitStruct->peripheral_base_addr = (uint32_t)&(p_Uart->p_huart->dt);
      p_Uart->p_DmaTxInitStruct->peripheral_data_width = DMA_PERIPHERAL_DATA_WIDTH_BYTE;
      p_Uart->p_DmaTxInitStruct->peripheral_inc_enable = FALSE;
      p_Uart->p_DmaTxInitStruct->priority = p_Uart->DmaTxPriority;
      p_Uart->p_DmaTxInitStruct->loop_mode_enable = FALSE;
      dma_init(p_Uart->p_DmaTxChannel, p_Uart->p_DmaTxInitStruct);

      dma_interrupt_enable(p_Uart->p_DmaTxChannel, DMA_FDT_INT, TRUE);
    }
    else
    {
      p_Uart->Flag.bTxByDma = false;
    }

    if ((p_Uart->p_DmaRxChannel) && (p_Uart->p_DmaRxInitStruct))
    {
      p_Uart->Flag.bRxByDma = true;

      dma_reset(p_Uart->p_DmaRxChannel);

      dma_default_para_init(p_Uart->p_DmaRxInitStruct);
      p_Uart->p_DmaRxInitStruct->buffer_size = p_Param->ulRxBuffSize;
      p_Uart->p_DmaRxInitStruct->direction = DMA_DIR_PERIPHERAL_TO_MEMORY;
      p_Uart->p_DmaRxInitStruct->memory_base_addr = (uint32_t)p_Param->p_ucaRxBuff;
      p_Uart->p_DmaRxInitStruct->memory_data_width = DMA_MEMORY_DATA_WIDTH_BYTE;
      p_Uart->p_DmaRxInitStruct->memory_inc_enable = TRUE;
      p_Uart->p_DmaRxInitStruct->peripheral_base_addr = (uint32_t)&(p_Uart->p_huart->dt);
      p_Uart->p_DmaRxInitStruct->peripheral_data_width = DMA_PERIPHERAL_DATA_WIDTH_BYTE;
      p_Uart->p_DmaRxInitStruct->peripheral_inc_enable = FALSE;
      p_Uart->p_DmaRxInitStruct->priority = p_Uart->DmaRxPriority;
      p_Uart->p_DmaRxInitStruct->loop_mode_enable = TRUE;
      dma_init(p_Uart->p_DmaRxChannel, p_Uart->p_DmaRxInitStruct);

      dma_channel_enable(p_Uart->p_DmaRxChannel, TRUE);
    }
    else
    {
      p_Uart->Flag.bRxByDma = false;

      usart_interrupt_enable(p_Uart->p_huart, USART_RDBF_INT, TRUE);
    }
  }
}

/**
 * @brief  UART 清除发送FIFO
 * @param  Com:UART代号
 * @retval none
 */
void BspUart_ClrTxFifo(BspUartCom_E Com)
{
  BspUart_S *p_Uart;
  register rt_base_t level;

  p_Uart = BspUart_Com2Uart(Com);

  level = rt_hw_interrupt_disable();
  chry_ringbuffer_reset(&p_Uart->TxFifo);
  rt_hw_interrupt_enable(level);
}

/**
 * @brief  UART 清除接收FIFO
 * @param  Com:UART代号
 * @retval none
 */
void BspUart_ClrRxFifo(BspUartCom_E Com)
{
  BspUart_S *p_Uart;
  register rt_base_t level;

  p_Uart = BspUart_Com2Uart(Com);

  level = rt_hw_interrupt_disable();
  chry_ringbuffer_reset(&p_Uart->RxFifo);

  if (p_Uart->Flag.bRxByDma == true)
  {
    dma_channel_enable(p_Uart->p_DmaRxChannel, FALSE);

    dma_reset(p_Uart->p_DmaRxChannel);

    dma_default_para_init(p_Uart->p_DmaRxInitStruct);
    p_Uart->p_DmaRxInitStruct->buffer_size = chry_ringbuffer_get_size(&p_Uart->RxFifo);
    p_Uart->p_DmaRxInitStruct->direction = DMA_DIR_PERIPHERAL_TO_MEMORY;
    p_Uart->p_DmaRxInitStruct->memory_base_addr = (uint32_t)p_Uart->RxFifo.pool;
    p_Uart->p_DmaRxInitStruct->memory_data_width = DMA_MEMORY_DATA_WIDTH_BYTE;
    p_Uart->p_DmaRxInitStruct->memory_inc_enable = TRUE;
    p_Uart->p_DmaRxInitStruct->peripheral_base_addr = (uint32_t)&(p_Uart->p_huart->dt);
    p_Uart->p_DmaRxInitStruct->peripheral_data_width = DMA_PERIPHERAL_DATA_WIDTH_BYTE;
    p_Uart->p_DmaRxInitStruct->peripheral_inc_enable = FALSE;
    p_Uart->p_DmaRxInitStruct->priority = p_Uart->DmaRxPriority;
    p_Uart->p_DmaRxInitStruct->loop_mode_enable = TRUE;
    dma_init(p_Uart->p_DmaRxChannel, p_Uart->p_DmaRxInitStruct);

    dma_channel_enable(p_Uart->p_DmaRxChannel, TRUE);
  }

  rt_hw_interrupt_enable(level);
}

/**
 * @brief  UART 检查接收FIFO是否半满
 * @param  Com:UART代号
 * @param  p_bHalfFull:接收FIFO半满标志
 * @retval 接收FIFO半满标志 半满为true
 */
bool BspUart_ChkHalfFull(BspUartCom_E Com, bool *p_bHalfFull)
{
  BspUart_S *p_Uart;
  bool bHalfFull = false;

  p_Uart = BspUart_Com2Uart(Com);

  if (chry_ringbuffer_get_used(&p_Uart->RxFifo) >= (chry_ringbuffer_get_size(&p_Uart->RxFifo) / 2))
  {
    bHalfFull = true;
  }
  else
  {
    bHalfFull = false;
  }

  if (p_bHalfFull)
  {
    *p_bHalfFull = bHalfFull;
  }

  return bHalfFull;
}

/**
 * @brief  UART 检查接收是否完成
 * @param  Com:UART代号
 * @retval 接收完成标志 接收完成为true
 */
bool BspUart_GetRxState(BspUartCom_E Com)
{
  BspUart_S *p_Uart;

  p_Uart = BspUart_Com2Uart(Com);

  return p_Uart->Flag.bRxDone;
}

/**
 * @brief  UART 检查接收是否在进行中
 * @param  Com:UART代号
 * @retval 接收中标志 接收中为true
 */
bool BspUart_GetRxingState(BspUartCom_E Com)
{
  BspUart_S *p_Uart;

  p_Uart = BspUart_Com2Uart(Com);

  return p_Uart->Flag.bRxStart;
}

/**
 * @brief  UART 清除接收完成标志
 * @param  Com:UART代号
 * @retval none
 */
void BspUart_ClrRxState(BspUartCom_E Com)
{
  BspUart_S *p_Uart;
  register rt_base_t level;

  p_Uart = BspUart_Com2Uart(Com);

  level = rt_hw_interrupt_disable();
  p_Uart->Flag.bRxStart = false;
  p_Uart->Flag.bRxDone = false;
  rt_hw_interrupt_enable(level);
}

/**
 * @brief  UART 获取接收FIFO中的有效数据个数
 * @param  Com:UART代号
 * @retval 有效数据个数
 */
uint16_t BspUart_GetRxCount(BspUartCom_E Com)
{
  BspUart_S *p_Uart;

  p_Uart = BspUart_Com2Uart(Com);

  return chry_ringbuffer_get_used(&p_Uart->RxFifo);
}

/**
 * @brief  UART 获取发送FIFO中的有效数据个数
 * @param  Com:UART代号
 * @retval 有效数据个数
 */
uint16_t BspUart_GetTxCount(BspUartCom_E Com)
{
  BspUart_S *p_Uart;

  p_Uart = BspUart_Com2Uart(Com);

  return chry_ringbuffer_get_used(&p_Uart->TxFifo);
}

/**
 * @brief  UART 设置波特率
 * @param  Com:UART代号
 * @param  BaudRate:波特率
 * @retval none
 */
void BspUart_SetBaudRate(BspUartCom_E Com, uint32_t BaudRate)
{
  BspUart_S *p_Uart;
  p_Uart = BspUart_Com2Uart(Com);

  {
    p_Uart->p_Setting->baud_rate = BaudRate;
  }

  usart_enable(p_Uart->p_huart, FALSE);
  usart_init(p_Uart->p_huart,
             p_Uart->p_Setting->baud_rate,
             p_Uart->p_Setting->data_bit,
             p_Uart->p_Setting->stop_bit);
  usart_enable(p_Uart->p_huart, TRUE);
}

/**
 * @brief  UART 设置校验位
 * @param  Com:UART代号
 * @param  ucParity:校验位
 * @retval none
 */
void BspUart_SetParity(BspUartCom_E Com, uint8_t ucParity)
{
  BspUart_S *p_Uart;
  p_Uart = BspUart_Com2Uart(Com);

  if (p_Uart->p_Setting->parity == (usart_parity_selection_type)ucParity)
    return;

  p_Uart->p_Setting->parity = (usart_parity_selection_type)ucParity;

  usart_enable(p_Uart->p_huart, FALSE);

  if (p_Uart->p_Setting->parity == USART_PARITY_NONE)
  {
    p_Uart->p_Setting->data_bit = USART_DATA_8BITS;

    p_Uart->p_huart->ctrl1_bit.dbn = 0;
  }
  else
  {
    p_Uart->p_Setting->data_bit = USART_DATA_9BITS;

    p_Uart->p_huart->ctrl1_bit.dbn = 1;
  }

  usart_parity_selection_config(p_Uart->p_huart, (usart_parity_selection_type)ucParity);

  usart_enable(p_Uart->p_huart, TRUE);
}

void BspUartRxCallBack(BspUart_S *p_Uart)
{
  chry_ringbuffer_write_byte(&p_Uart->RxFifo, (uint8_t)usart_data_receive(p_Uart->p_huart));

  // if (p_Uart->Flag.bRxStart == false)
  // {
  //   p_Uart->ulTickRxStart = rt_tick_get();
  // }

  p_Uart->Flag.bRxStart = true;
  p_Uart->Flag.bRxDone = false;
  p_Uart->IdleTimerCnt = 0;
}

void BspUartTxCallBack(BspUart_S *p_Uart)
{
  uint8_t ucByte;

  if (chry_ringbuffer_read_byte(&p_Uart->TxFifo, &ucByte) == true)
  {
    usart_data_transmit(p_Uart->p_huart, ucByte);
  }
  else
  {
    /* Disable the UART Transmit Data Register Empty Interrupt */
    usart_interrupt_enable(p_Uart->p_huart, USART_TDBE_INT, FALSE);

    // p_Uart->ulTickTxOver = rt_tick_get();
  }
}

static inline int32_t BspUartDmaTxTrig(BspUart_S *p_Uart)
{
  if (chry_ringbuffer_check_empty(&p_Uart->TxFifo) == true)
    return 0;
  if (p_Uart->p_DmaTxChannel->ctrl_bit.chen == TRUE)
    return -1;

  p_Uart->p_DmaTxChannel->ctrl_bit.chen = FALSE;

  p_Uart->p_DmaTxChannel->maddr = (uint32_t)chry_ringbuffer_linear_read_setup(&p_Uart->TxFifo, (uint32_t *)&p_Uart->ulDmaTxCnt);
  p_Uart->p_DmaTxChannel->dtcnt = p_Uart->ulDmaTxCnt;

  if (!p_Uart->ulDmaTxCnt)
    return -2;

  p_Uart->p_DmaTxChannel->ctrl_bit.chen = TRUE;

  return p_Uart->ulDmaTxCnt;
}

void BspUartErrorCallBack(BspUart_S *p_Uart)
{
  volatile uint32_t ulReadOut;

  // 通过先读STS再读DT的方式清除可能发生的错误
  ulReadOut = p_Uart->p_huart->sts;
  ulReadOut = p_Uart->p_huart->dt;
}

void BspUartDmaTxFullCallBack(BspUart_S *p_Uart)
{
  p_Uart->p_DmaTxChannel->ctrl_bit.chen = FALSE;

  chry_ringbuffer_linear_read_done(&p_Uart->TxFifo, p_Uart->ulDmaTxCnt);

  if (BspUartDmaTxTrig(p_Uart) == 0)
  {
  }
}

bool BspUart_SendBuff(BspUartCom_E Com, uint8_t *p_Buff, uint16_t Len)
{
  uint16_t i = 0;
  BspUart_S *p_Uart;

  if (!p_Buff)
    return false;
  if (!Len)
    return false;

  p_Uart = BspUart_Com2Uart(Com);

  BspConfig_MutexTake(p_Uart->ucMutexIdx);

  if (p_Uart->p_SendBefore)
  {
    p_Uart->p_SendBefore();
  }

  while (1)
  {
    if (chry_ringbuffer_check_full(&p_Uart->TxFifo) == false)
    {
      chry_ringbuffer_write_byte(&p_Uart->TxFifo, p_Buff[i++]);
    }
    else
    {
      if (p_Uart->Flag.bTxByDma == true)
      {
        BspUartDmaTxTrig(p_Uart);
      }
      else
      {
        usart_interrupt_enable(p_Uart->p_huart, USART_TDBE_INT, TRUE);
      }
    }

    if (i >= Len)
      break;
  }

  if (p_Uart->Flag.bTxByDma == true)
  {
    BspUartDmaTxTrig(p_Uart);
  }
  else
  {
    usart_interrupt_enable(p_Uart->p_huart, USART_TDBE_INT, TRUE);
  }

  BspConfig_MutexRelease(p_Uart->ucMutexIdx);

  return true;
}

void BspUart_SendChar(BspUartCom_E Com, uint8_t Ch)
{
  BspUart_SendBuff(Com, &Ch, 1);
}

bool BspUart_SendString(BspUartCom_E Com, char *p_caString)
{
  return BspUart_SendBuff(Com, (uint8_t *)p_caString, strlen((const char *)p_caString));
}

bool BspUart_Printf(BspUartCom_E Com, char *p_caBuff, uint16_t usBuffSize, char *p_caString, ...)
{
  va_list args;

  if (!p_caBuff)
    return false;
  if (!p_caString)
    return false;

  memset(p_caBuff, 0, usBuffSize);

  va_start(args, p_caString);
  rt_vsnprintf(p_caBuff, usBuffSize, (const char *)p_caString, args);
  va_end(args);

  return BspUart_SendBuff(Com, (uint8_t *)p_caBuff, strlen((const char *)p_caBuff));
}

bool BspUart_GetChar(BspUartCom_E Com, uint8_t *p_Byte)
{
  BspUart_S *p_Uart;

  if (!p_Byte)
    return false;

  p_Uart = BspUart_Com2Uart(Com);

  if (chry_ringbuffer_read_byte(&p_Uart->RxFifo, p_Byte) == false)
  {
    p_Uart->Flag.bRxDone = false;

    return false;
  }

  return true;
}

uint16_t BspUart_GetBuff(BspUartCom_E Com, uint8_t *p_Buff, uint16_t Len)
{
  BspUart_S *p_Uart;
  uint16_t i = 0;

  if (!p_Buff)
    return 0;
  if (!Len)
    return 0;

  p_Uart = BspUart_Com2Uart(Com);

  while (1)
  {
    if (chry_ringbuffer_read_byte(&p_Uart->RxFifo, &p_Buff[i]) == false)
    {
      p_Uart->Flag.bRxDone = false;

      break;
    }

    if (++i >= Len)
      break;
  }

  return i;
}

void BspUart_FlushBuff(BspUartCom_E Com)
{
  BspUart_S *p_Uart;

  p_Uart = BspUart_Com2Uart(Com);

  while (1)
  {
    if (chry_ringbuffer_drop_byte(&p_Uart->RxFifo) == false)
    {
      p_Uart->Flag.bRxDone = false;

      break;
    }
  }
}

void BspUart_SendChar_Block(BspUartCom_E Com, uint8_t Ch)
{
  BspUart_S *p_Uart;

  p_Uart = BspUart_Com2Uart(Com);

  BspConfig_MutexTake(p_Uart->ucMutexIdx);

  while (usart_flag_get(p_Uart->p_huart, USART_TDBE_FLAG) == RESET)
    ;

  usart_data_transmit(p_Uart->p_huart, Ch);

  BspConfig_MutexRelease(p_Uart->ucMutexIdx);
}

void BspUart_SendBuff_Block(BspUartCom_E Com, uint8_t *p_ucaBuff, uint16_t usLen)
{
  uint16_t i;
  BspUart_S *p_Uart;

  if (!p_ucaBuff)
    return;
  if (!usLen)
    return;

  p_Uart = BspUart_Com2Uart(Com);

  BspConfig_MutexTake(p_Uart->ucMutexIdx);

  for (i = 0; i < usLen; i++)
  {
    while (usart_flag_get(p_Uart->p_huart, USART_TDBE_FLAG) == RESET)
      ;

    usart_data_transmit(p_Uart->p_huart, p_ucaBuff[i]);
  }

  BspConfig_MutexRelease(p_Uart->ucMutexIdx);
}

void BspUart_SendString_Block(BspUartCom_E Com, char *p_caString)
{
  BspUart_SendBuff_Block(Com, (uint8_t *)p_caString, strlen((const char *)p_caString));
}

bool BspUart_Printf_Block(BspUartCom_E Com, char *p_caBuff, uint16_t usBuffSize, char *p_caString, ...)
{
  uint16_t usStrLen = 0;
  va_list args;

  if (!p_caBuff)
    return false;
  if (!p_caString)
    return false;
  memset(p_caBuff, 0, usBuffSize);

  va_start(args, p_caString);
  usStrLen = rt_vsnprintf(p_caBuff, usBuffSize, (const char *)p_caString, args);
  va_end(args);

  BspUart_SendBuff_Block(Com, (uint8_t *)p_caBuff, usStrLen);

  return true;
}

void BspUart_IrqProc(void) // 中断中调用
{
  uint8_t i;
  BspUart_S *p_Uart;

  for (i = 0; i < config_BSPUART_NUM; i++)
  {
    p_Uart = BspUart_Com2Uart((BspUartCom_E)i);

    if (p_Uart->Flag.bRxStart)
    {
      if (p_Uart->IdleTimerCnt < p_Uart->MaxIdleTime)
      {
        p_Uart->IdleTimerCnt++;
      }
      else
      {
        p_Uart->Flag.bRxDone = true;
        p_Uart->Flag.bRxStart = false;

        p_Uart->IdleTimerCnt = 0;
      }
    }
  }
}

void BspUart_Proc(void)
{
  uint8_t i;
  BspUart_S *p_Uart;
  uint32_t ulValidCnt;

  for (i = 0; i < config_BSPUART_NUM; i++)
  {
    p_Uart = BspUart_Com2Uart((BspUartCom_E)i);

    if (p_Uart->p_RecvDone && (p_Uart->p_RecvDone != default_process))
    {
      if (p_Uart->Flag.bRxDone == true)
      {
        p_Uart->Flag.bRxDone = false;

        p_Uart->p_RecvDone();
      }
    }

    if (p_Uart->Flag.bRxByDma == true)
    {
      // DMA读写指针变化,换算到UART接收数量,并更新接收缓存
      p_Uart->ulDmaRxPtr_Curr = p_Uart->p_DmaRxChannel->dtcnt;
      if (p_Uart->ulDmaRxPtr_Last != p_Uart->ulDmaRxPtr_Curr)
      {
        if (p_Uart->ulDmaRxPtr_Last > p_Uart->ulDmaRxPtr_Curr)
        {
          ulValidCnt = p_Uart->ulDmaRxPtr_Last - p_Uart->ulDmaRxPtr_Curr;
        }
        else
        {
          ulValidCnt = chry_ringbuffer_get_size(&p_Uart->RxFifo) - p_Uart->ulDmaRxPtr_Curr;
          ulValidCnt += p_Uart->ulDmaRxPtr_Last;
        }

        p_Uart->ulDmaRxPtr_Last = p_Uart->ulDmaRxPtr_Curr;

        chry_ringbuffer_linear_write_done(&p_Uart->RxFifo, ulValidCnt);

        p_Uart->Flag.bRxStart = true;
        p_Uart->Flag.bRxDone = false;
        p_Uart->IdleTimerCnt = 0;
      }
    }
  }
}

/**
 * @}
 */
