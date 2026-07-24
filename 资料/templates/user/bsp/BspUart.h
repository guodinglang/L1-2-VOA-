/**
 **************************************************************************
 * @file     BspUart.c
 * @brief    UART驱动 FIFO
 */

/* define to prevent recursive inclusion -------------------------------------*/
#ifndef __BSP_UART_H__
#define __BSP_UART_H__

/* includes ------------------------------------------------------------------*/
#include "BspBoard.h"

/** @addtogroup UART驱动
 * @{
 */

#define config_BSPUART_NUM 4

#define config_BSPUART_USE_UART1 1

#define config_BSPUART_USE_UART2 1

#define config_BSPUART_USE_UART3 1

#define config_BSPUART_USE_UART4 1

#define config_BSPUART_USE_UART5 0

#define config_BSPUART_USE_UART6 0

#define config_BSPUART_USE_UART7 0

#define config_BSPUART_USE_UART8 0

#if (config_BSPUART_USE_UART1 == 1)
#define BSPUART1_TXBUFF_SIZE 256
#define BSPUART1_RXBUFF_SIZE 256
#endif /*config_BSPUART_USE_UART1*/

#if (config_BSPUART_USE_UART2 == 1)
#define BSPUART2_TXBUFF_SIZE 256
#define BSPUART2_RXBUFF_SIZE 256
#endif /*config_BSPUART_USE_UART2*/

#if (config_BSPUART_USE_UART3 == 1)
#define BSPUART3_TXBUFF_SIZE 256
#define BSPUART3_RXBUFF_SIZE 256
#endif /*config_BSPUART_USE_UART3*/

#if (config_BSPUART_USE_UART4 == 1)
#define BSPUART4_TXBUFF_SIZE 256
#define BSPUART4_RXBUFF_SIZE 256
#endif /*config_BSPUART_USE_UART4*/

#if (config_BSPUART_USE_UART5 == 1)
#define BSPUART5_TXBUFF_SIZE 256
#define BSPUART5_RXBUFF_SIZE 256
#endif /*config_BSPUART_USE_UART5*/

#if (config_BSPUART_USE_UART6 == 1)
#define BSPUART6_TXBUFF_SIZE 4096
#define BSPUART6_RXBUFF_SIZE 4096
#endif /*config_BSPUART_USE_UART6*/

#if (config_BSPUART_USE_UART7 == 1)
#define BSPUART7_TXBUFF_SIZE 256
#define BSPUART7_RXBUFF_SIZE 256
#endif /*config_BSPUART_USE_UART7*/

#if (config_BSPUART_USE_UART8 == 1)
#define BSPUART8_TXBUFF_SIZE 512
#define BSPUART8_RXBUFF_SIZE 64
#endif /*config_BSPUART_USE_UART8*/

/**
 * @brief  UART代号列表
 */
typedef enum
{
  BspUartCom_RS232 = 0,
  BspUartCom_USB,
  BspUartCom_DUT,
  BspUartCom_DUT2,
} BspUartCom_E;

/**
 * @brief  UART参数结构体
 */
typedef struct
{
  IRQn_Type irqn;

  uint16_t MaxIdleTime; /* 最大超时时间 */

  uint8_t *p_ucaTxBuff;
  uint8_t *p_ucaRxBuff;

  uint32_t ulTxBuffSize;
  uint32_t ulRxBuffSize;

  dma_channel_type *p_DmaTxChannel;
  dma_channel_type *p_DmaRxChannel;

  dma_init_type *p_DmaTxInitStruct;
  dma_init_type *p_DmaRxInitStruct;

  dma_priority_level_type DmaTxPriority;
  dma_priority_level_type DmaRxPriority;

  void (*p_SendBefore)(void); /* 开始发送之前的回调函数指针(主要用于RS485切换到发送模式) */
  void (*p_SendOver)(void);   /* 发送完毕的回调函数指针(主要用于RS485将发送模式切换为接收模式) */
  void (*p_RecvDone)(void);   /* 串口收完数据的回调函数指针 */
  void (*p_Idle)(void);       /* 空闲回调(一般用于带系统发送时避免多线程同时访问)*/
} BspUart_Param_S;

/**
 * @brief  UART硬件基本参数结构体
 */
typedef struct
{
  uint32_t baud_rate;
  usart_data_bit_num_type data_bit;
  usart_stop_bit_num_type stop_bit;
  usart_parity_selection_type parity;
} BspUart_Setting_S;

typedef union
{
  uint8_t ucValue;
  struct
  {
    uint8_t bTxByDma : 1;
    uint8_t bRxByDma : 1;
    uint8_t bRxStart : 1; /* 开始接收数据标志 */
    uint8_t bRxDone : 1;  /* 接收完成数据标志 */
  };
} BspUart_Flag_U;

/**
 * @brief  UART结构体
 */
typedef struct
{
  usart_type *p_huart;
  BspUart_Setting_S *p_Setting;
  BspUart_Flag_U Flag;
  uint8_t ucMutexIdx;

  IRQn_Type irqn;

  uint16_t MaxIdleTime;  /* 最大超时时间 */
  uint16_t IdleTimerCnt; /* 超时计数器 */

  chry_ringbuffer_t TxFifo;
  chry_ringbuffer_t RxFifo;

  dma_channel_type *p_DmaTxChannel;
  dma_channel_type *p_DmaRxChannel;

  dma_init_type *p_DmaTxInitStruct;
  dma_init_type *p_DmaRxInitStruct;

  dma_priority_level_type DmaTxPriority;
  dma_priority_level_type DmaRxPriority;

  uint32_t ulDmaTxCnt;
  uint32_t ulDmaRxPtr_Curr;
  uint32_t ulDmaRxPtr_Last;

  void (*p_SendBefore)(void); /* 开始发送之前的回调函数指针(主要用于RS485切换到发送模式) */
  void (*p_SendOver)(void);   /* 发送完毕的回调函数指针(主要用于RS485将发送模式切换为接收模式) */
  void (*p_RecvDone)(void);   /* 串口收完数据的回调函数指针 */
  void (*p_Idle)(void);       /* 空闲回调(一般用于带系统发送时避免多线程同时访问)*/

  uint32_t ulTickRxStart;
  uint32_t ulTickTxOver;
} BspUart_S;

typedef void (*pBspUart_SendBefor_TypeDef)(void);
typedef void (*pBspUart_SendOver_TypeDef)(void);
typedef void (*pBspUart_RecvDone_TypeDef)(void);
typedef void (*pBspUart_Idle_TypeDef)(void);

typedef struct
{
  BspUart_S *p_Uart;
  BspUartCom_E Com;
} BspUartLib_S;

#if (config_BSPUART_USE_UART1 == 1)
extern BspUart_S gUart1;
extern BspUart_Setting_S gUart1_Setting;
#endif /*config_BSPUART_USE_UART1*/

#if (config_BSPUART_USE_UART2 == 1)
extern BspUart_S gUart2;
extern BspUart_Setting_S gUart2_Setting;
#endif /*config_BSPUART_USE_UART2*/

#if (config_BSPUART_USE_UART3 == 1)
extern BspUart_S gUart3;
extern BspUart_Setting_S gUart3_Setting;
#endif /*config_BSPUART_USE_UART3*/

#if (config_BSPUART_USE_UART4 == 1)
extern BspUart_S gUart4;
extern BspUart_Setting_S gUart4_Setting;
#endif /*config_BSPUART_USE_UART4*/

#if (config_BSPUART_USE_UART5 == 1)
extern BspUart_S gUart5;
extern BspUart_Setting_S gUart5_Setting;
#endif /*config_BSPUART_USE_UART5*/

#if (config_BSPUART_USE_UART6 == 1)
extern BspUart_S gUart6;
extern BspUart_Setting_S gUart6_Setting;
#endif /*config_BSPUART_USE_UART6*/

#if (config_BSPUART_USE_UART7 == 1)
extern BspUart_S gUart7;
extern BspUart_Setting_S gUart7_Setting;
#endif /*config_BSPUART_USE_UART7*/

#if (config_BSPUART_USE_UART8 == 1)
extern BspUart_S gUart8;
extern BspUart_Setting_S gUart8_Setting;
#endif /*config_BSPUART_USE_UART8*/

void BspUart_Init(void);
void BspUart_CallBack_Set(BspUartCom_E Com,
                          pBspUart_SendBefor_TypeDef p_SendBefore,
                          pBspUart_SendOver_TypeDef p_SendOver,
                          pBspUart_RecvDone_TypeDef p_RecvDone);

// FIFO状态
void BspUart_ClrTxFifo(BspUartCom_E Com);
void BspUart_ClrRxFifo(BspUartCom_E Com);
bool BspUart_ChkHalfFull(BspUartCom_E Com, bool *p_bHalfFull);
bool BspUart_GetRxState(BspUartCom_E Com);
bool BspUart_GetRxingState(BspUartCom_E Com);
void BspUart_ClrRxState(BspUartCom_E Com);
uint16_t BspUart_GetRxCount(BspUartCom_E Com);
uint16_t BspUart_GetTxCount(BspUartCom_E Com);

void BspUart_SetBaudRate(BspUartCom_E Com, uint32_t BaudRate); // 波特率
void BspUart_SetParity(BspUartCom_E Com, uint8_t ucParity);    // 校验位

// 中断回调
void BspUartRxCallBack(BspUart_S *p_Uart);        // 中断接收方式的回调
void BspUartTxCallBack(BspUart_S *p_Uart);        // 中断发送方式的回调
void BspUartErrorCallBack(BspUart_S *p_Uart);     // 错误回调(只是清除可能发生的错误标志,避免串口卡住)
void BspUartDmaTxFullCallBack(BspUart_S *p_Uart); // DMA发送的传输完成回调

// FIFO接口发送,触发完即返回(不要在中断中使用)
bool BspUart_SendBuff(BspUartCom_E Com, uint8_t *p_Buff, uint16_t Len);
void BspUart_SendChar(BspUartCom_E Com, uint8_t Ch);
bool BspUart_SendString(BspUartCom_E Com, char *p_caString);
bool BspUart_Printf(BspUartCom_E Com, char *p_caBuff, uint16_t usBuffSize, char *p_caString, ...);

// FIFO接口接收(不要在中断中使用)
bool BspUart_GetChar(BspUartCom_E Com, uint8_t *p_Byte);
uint16_t BspUart_GetBuff(BspUartCom_E Com, uint8_t *p_Buff, uint16_t Len);
void BspUart_FlushBuff(BspUartCom_E Com);

// 阻塞方式发送,不依赖中断,DMA,适用于特殊场合(不要在中断中使用)
void BspUart_SendChar_Block(BspUartCom_E Com, uint8_t Ch);
void BspUart_SendBuff_Block(BspUartCom_E Com, uint8_t *p_ucaBuff, uint16_t usLen);
void BspUart_SendString_Block(BspUartCom_E Com, char *p_caString);
bool BspUart_Printf_Block(BspUartCom_E Com, char *p_caBuff, uint16_t usBuffSize, char *p_caString, ...);

// 时基中断回调
void BspUart_IrqProc(void);

// 定时任务回调(<=2ms)
void BspUart_Proc(void);

/**
 * @}
 */

#endif /*BspUart.h*/
