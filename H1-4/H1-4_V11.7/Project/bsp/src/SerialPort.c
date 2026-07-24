

#include "SerialPort.h"

//***************************************************************************/
rxStructure urStruct[9], *tPort = 0; //*pUART=&urStruct1;
rxStructure *pUART = &urStruct[0], *pDUT = &urStruct[1], *pUSB = &urStruct[2], *pDUT2 = &urStruct[3];
rxStructure *pMultPort1 = &urStruct[4], *pMultPort2 = &urStruct[5], *pMultPort3 = &urStruct[6], *pMultPort4 = &urStruct[7], *pCAN1 = &urStruct[8];

/***************************************************************************
;** 函数名称: 	usart_configuration
;** 功能描述:  	usart configuration
;** 输入参数:
;** 返 回 值:
;** 全局变量:
;** 调用模块:
;** 作　  者:   M-L-A
;** 日　  期:  2022-5-25
;** 修改原因:
;** 说    明:
;***************************************************************************/
void usart1_config(uint32_t baud_rate)
{
  gpio_init_type gpio_init_struct;

  /* enable the usart1 and gpio clock */
  crm_periph_clock_enable(CRM_USART1_PERIPH_CLOCK, TRUE);
  crm_periph_clock_enable(CRM_GPIOA_PERIPH_CLOCK, TRUE);

  gpio_default_para_init(&gpio_init_struct);

  /* configure the usart1 tx pin */
  gpio_init_struct.gpio_drive_strength = GPIO_DRIVE_STRENGTH_STRONGER;
  gpio_init_struct.gpio_out_type = GPIO_OUTPUT_PUSH_PULL;
  gpio_init_struct.gpio_mode = GPIO_MODE_MUX;
  gpio_init_struct.gpio_pins = GPIO_PINS_9;
  gpio_init_struct.gpio_pull = GPIO_PULL_UP; // GPIO_PULL_NONE;
  gpio_init(GPIOA, &gpio_init_struct);

  /* configure the usart1 rx pin */
  gpio_init_struct.gpio_drive_strength = GPIO_DRIVE_STRENGTH_STRONGER;
  gpio_init_struct.gpio_out_type = GPIO_OUTPUT_PUSH_PULL;
  gpio_init_struct.gpio_mode = GPIO_MODE_INPUT;
  gpio_init_struct.gpio_pins = GPIO_PINS_10;
  gpio_init_struct.gpio_pull = GPIO_PULL_UP;
  gpio_init(GPIOA, &gpio_init_struct);

  /* config usart nvic interrupt */
  nvic_priority_group_config(NVIC_PRIORITY_GROUP_4);
  nvic_irq_enable(USART1_IRQn, 0, 0);

  /* configure usart1 param */
  usart_init(USART1, baud_rate, USART_DATA_8BITS, USART_STOP_1_BIT);
  usart_transmitter_enable(USART1, TRUE);
  usart_receiver_enable(USART1, TRUE);

  /* enable usart1 interrupt */
  usart_interrupt_enable(USART1, USART_RDBF_INT, TRUE);
  //  usart_interrupt_enable(USART1, USART_TDBE_INT, TRUE);
  usart_enable(USART1, TRUE);

  //  while(usart_flag_get(USART1, USART_TDBE_FLAG) == RESET);
  usart_data_transmit(USART1, 0x0d);
}

/***************************************************************************
;** 函数名称: 	usart_configuration
;** 功能描述:  	usart configuration
;** 输入参数:
;** 返 回 值:
;** 全局变量:
;** 调用模块:
;** 作　  者:   M-L-A
;** 日　  期:  2022-9-20
;** 修改原因：
;** 说    明:
;***************************************************************************/
void usart2_config(uint32_t baud_rate)
{
  gpio_init_type gpio_init_struct;

  /* enable the usart and gpio clock */
  crm_periph_clock_enable(CRM_USART2_PERIPH_CLOCK, TRUE);
  crm_periph_clock_enable(CRM_GPIOA_PERIPH_CLOCK, TRUE);

  gpio_default_para_init(&gpio_init_struct);

  /* configure the usart tx pin */
  gpio_init_struct.gpio_drive_strength = GPIO_DRIVE_STRENGTH_STRONGER;
  gpio_init_struct.gpio_out_type = GPIO_OUTPUT_PUSH_PULL;
  gpio_init_struct.gpio_mode = GPIO_MODE_MUX;
  gpio_init_struct.gpio_pins = GPIO_PINS_2;
  gpio_init_struct.gpio_pull = GPIO_PULL_UP; // GPIO_PULL_NONE;
  gpio_init(GPIOA, &gpio_init_struct);

  /* configure the usart rx pin */
  gpio_init_struct.gpio_drive_strength = GPIO_DRIVE_STRENGTH_STRONGER;
  gpio_init_struct.gpio_out_type = GPIO_OUTPUT_PUSH_PULL;
  gpio_init_struct.gpio_mode = GPIO_MODE_INPUT;
  gpio_init_struct.gpio_pins = GPIO_PINS_3;
  gpio_init_struct.gpio_pull = GPIO_PULL_UP;
  gpio_init(GPIOA, &gpio_init_struct);

  /* config usart nvic interrupt */
  nvic_priority_group_config(NVIC_PRIORITY_GROUP_4);
  nvic_irq_enable(USART2_IRQn, 0, 0);

  /* configure usart param */
  usart_init(USART2, baud_rate, USART_DATA_8BITS, USART_STOP_1_BIT);
  usart_transmitter_enable(USART2, TRUE);
  usart_receiver_enable(USART2, TRUE);

  /* enable usart interrupt */
  usart_interrupt_enable(USART2, USART_RDBF_INT, TRUE);
  //  usart_interrupt_enable(USART1, USART_TDBE_INT, TRUE);
  usart_enable(USART2, TRUE);

  //  usart_data_transmit(USART2, 0x0d);
}

/***************************************************************************
;** 函数名称: 	usart_configuration
;** 功能描述:  	usart configuration
;** 输入参数:
;** 返 回 值:
;** 全局变量:
;** 调用模块:
;** 作　  者:   M-L-A
;** 日　  期:  2022-9-20
;** 修改原因：
;** 说    明:
;***************************************************************************/
void usart3_config(uint32_t baud_rate)
{
  gpio_init_type gpio_init_struct;

  /* enable the usart and gpio clock */
  crm_periph_clock_enable(CRM_USART3_PERIPH_CLOCK, TRUE);
  crm_periph_clock_enable(CRM_GPIOB_PERIPH_CLOCK, TRUE);

  gpio_default_para_init(&gpio_init_struct);

  /* configure the usart tx pin */
  gpio_init_struct.gpio_drive_strength = GPIO_DRIVE_STRENGTH_STRONGER;
  gpio_init_struct.gpio_out_type = GPIO_OUTPUT_PUSH_PULL;
  gpio_init_struct.gpio_mode = GPIO_MODE_MUX;
  gpio_init_struct.gpio_pins = GPIO_PINS_10;
  gpio_init_struct.gpio_pull = GPIO_PULL_UP; // GPIO_PULL_NONE;
  gpio_init(GPIOB, &gpio_init_struct);

  /* configure the usart rx pin */
  gpio_init_struct.gpio_drive_strength = GPIO_DRIVE_STRENGTH_STRONGER;
  gpio_init_struct.gpio_out_type = GPIO_OUTPUT_PUSH_PULL;
  gpio_init_struct.gpio_mode = GPIO_MODE_INPUT;
  gpio_init_struct.gpio_pins = GPIO_PINS_11;
  gpio_init_struct.gpio_pull = GPIO_PULL_UP;
  gpio_init(GPIOB, &gpio_init_struct);

  /* config usart nvic interrupt */
  nvic_priority_group_config(NVIC_PRIORITY_GROUP_4);
  nvic_irq_enable(USART3_IRQn, 0, 0);

  /* configure usart param */
  usart_init(USART3, baud_rate, USART_DATA_8BITS, USART_STOP_1_BIT);
  usart_transmitter_enable(USART3, TRUE);
  usart_receiver_enable(USART3, TRUE);

  /* enable usart interrupt */
  usart_interrupt_enable(USART3, USART_RDBF_INT, TRUE);
  //  usart_interrupt_enable(USART1, USART_TDBE_INT, TRUE);
  usart_enable(USART3, TRUE);

  //  usart_data_transmit(USART3, 0x0d);
}
/***************************************************************************
;** 函数名称: 	usart_configuration
;** 功能描述:  	usart configuration
;** 输入参数:
;** 返 回 值:
;** 全局变量:
;** 调用模块:
;** 作　  者:   M-L-A
;** 日　  期:  2022-9-20
;** 修改原因：
;** 说    明:
;***************************************************************************/
void uart4_config(uint32_t baud_rate)
{
  gpio_init_type gpio_init_struct;

  /* enable the usart and gpio clock */
  crm_periph_clock_enable(CRM_UART4_PERIPH_CLOCK, TRUE);
  crm_periph_clock_enable(CRM_GPIOC_PERIPH_CLOCK, TRUE);

  gpio_default_para_init(&gpio_init_struct);

  /* configure the usart tx pin */
  gpio_init_struct.gpio_drive_strength = GPIO_DRIVE_STRENGTH_STRONGER;
  gpio_init_struct.gpio_out_type = GPIO_OUTPUT_PUSH_PULL;
  gpio_init_struct.gpio_mode = GPIO_MODE_MUX;
  gpio_init_struct.gpio_pins = GPIO_PINS_10;
  gpio_init_struct.gpio_pull = GPIO_PULL_UP; // GPIO_PULL_NONE;
  gpio_init(GPIOC, &gpio_init_struct);

  /* configure the usart rx pin */
  gpio_init_struct.gpio_drive_strength = GPIO_DRIVE_STRENGTH_STRONGER;
  gpio_init_struct.gpio_out_type = GPIO_OUTPUT_PUSH_PULL;
  gpio_init_struct.gpio_mode = GPIO_MODE_INPUT;
  gpio_init_struct.gpio_pins = GPIO_PINS_11;
  gpio_init_struct.gpio_pull = GPIO_PULL_UP;
  gpio_init(GPIOC, &gpio_init_struct);

  /* config usart nvic interrupt */
  nvic_priority_group_config(NVIC_PRIORITY_GROUP_4);
  nvic_irq_enable(UART4_IRQn, 0, 0);

  /* configure usart param */
  usart_init(UART4, baud_rate, USART_DATA_8BITS, USART_STOP_1_BIT);
  usart_transmitter_enable(UART4, TRUE);
  usart_receiver_enable(UART4, TRUE);

  /* enable usart interrupt */
  usart_interrupt_enable(UART4, USART_RDBF_INT, TRUE);
  //  usart_interrupt_enable(USART1, USART_TDBE_INT, TRUE);
  usart_enable(UART4, TRUE);
}

/*重定向c库函数printf到USART1*/
int fputc(int ch, FILE *f)
{
  /* 发送一个字节数据到USART1 */
  /* 等待发送完毕 */
  while (usart_flag_get(USART1, USART_TDBE_FLAG) == RESET)
    ;
  usart_data_transmit(USART1, ch);

  return (ch);
}

///*重定向c库函数scanf到USART1*/
// int fgetc(FILE *f)
//{
//   /* 等待串口1输入数据 */
//	while(usart_flag_get(USART1, USART_RDBF_FLAG) == RESET);
//	return (int)USART1->dt;
// }

/***************************************************************************
;** 函数名称:
;** 功能描述:  USARTx 传送数据
;** 输入参数:
;** 返 回 值:
;** 全局变量:
;** 调用模块:
;** 作　  者:   M-L-A
;** 日　  期:  2012-6-29
;** 修改原因：
;** 说    明:
;***************************************************************************/
void printx(uint16_t d)
{
  //--------------UART-----------------------------------------------------
  if (pUART->send)
  {
    while (usart_flag_get(USART1, USART_TDBE_FLAG) == RESET)
    {
      delay_us(3);
    }
    usart_data_transmit(USART1, d);
  }
  //--------------USB------------------------------------------------------
  if (pUSB->send)
  {
    while (usart_flag_get(USART3, USART_TDBE_FLAG) == RESET)
    {
      delay_us(3);
    }
    usart_data_transmit(USART3, d);
  }
  //--------------ethernet------------------------------------------------------
  if (pEther->send)
  {
    send(socku, (uint8_t *)&d, 1);
  }
  //--------------DUT------------------------------------------------------
  if (pDUT->send == 1)
  {
    while (usart_flag_get(USART2, USART_TDBE_FLAG) == RESET)
    {
      delay_us(3);
    }
    usart_data_transmit(USART2, d);
  }
  //--------------DUT2------------------------------------------------------
  if (pDUT2->send == 1)
  {
    while (usart_flag_get(UART4, USART_TDBE_FLAG) == RESET)
    {
      delay_us(3);
    }
    usart_data_transmit(UART4, d);
  }
  //--------------CH9434----------------------------------------------------
  if (pMultPort1->send == 1)
  {
    multi_usart_data_transmit(1, d);
  }

  if (pMultPort2->send == 1)
  {
    multi_usart_data_transmit(2, d);
  }

  if (pMultPort3->send == 1)
  {
    multi_usart_data_transmit(3, d);
  }

  if (pMultPort4->send == 1)
  {
    multi_usart_data_transmit(4, d);
  }
}
/***************************************************************************
;** 函数名称:
;** 功能描述:  USARTx 传送一帧数据
;** 输入参数:
;** 返 回 值:
;** 全局变量:
;** 调用模块:
;** 作　  者:   M-L-A
;** 日　  期:  2012-6-29
;** 修改原因：
;** 说    明:
;***************************************************************************/
void printfx(char *st)
{
  char *p;
  //--------------UART-----------------------------------------------------
  if (pUART->send)
  {
    p = st;
    while (*p != '\0')
    {
      while (usart_flag_get(USART1, USART_TDBE_FLAG) == RESET)
      {
        delay_us(3);
      }
      usart_data_transmit(USART1, *p);
      p++;
    }
  }
  //--------------USB------------------------------------------------------
  if (pUSB->send)
  {
    p = st;
    while (*p != '\0')
    {
      while (usart_flag_get(USART3, USART_TDBE_FLAG) == RESET)
      {
        delay_us(3);
      }
      usart_data_transmit(USART3, *p);
      p++;
    }
  }
  //--------------ethernet-------------------------------------------------
  if (pEther->send)
  {
    p = st;
    send(socku, (uint8_t *)p, strlen(p)); // delay_ms(100);
  }
  //--------------DUT------------------------------------------------------
  if (pDUT->send == 1)
  {
    p = st;
    while (*p != '\0')
    {
      while (usart_flag_get(USART2, USART_TDBE_FLAG) == RESET)
      {
        delay_us(3);
      }
      usart_data_transmit(USART2, *p);
      p++;
    }
  }
  //--------------DUT2------------------------------------------------------
  if (pDUT2->send == 1)
  {
    p = st;
    while (*p != '\0')
    {
      while (usart_flag_get(UART4, USART_TDBE_FLAG) == RESET)
      {
        delay_us(3);
      }
      usart_data_transmit(UART4, *p);
      p++;
    }
  }

  //--------------CH9434----------------------------------------------------
  if (pMultPort1->send == 1)
  {
    CH9434UARTxSetTxFIFOData(1, (uint8_t *)st, strlen(st));
  }

  if (pMultPort2->send == 1)
  {
    CH9434UARTxSetTxFIFOData(2, (uint8_t *)st, strlen(st));
  }

  if (pMultPort3->send == 1)
  {
    CH9434UARTxSetTxFIFOData(3, (uint8_t *)st, strlen(st));
  }

  if (pMultPort4->send == 1)
  {
    CH9434UARTxSetTxFIFOData(4, (uint8_t *)st, strlen(st));
  }
}
/***************************************************************************
;** 函数名称:
;** 功能描述:  USARTx printf
;** 输入参数:
;** 返 回 值:
;** 全局变量:
;** 调用模块:
;** 作　  者:   M-L-A
;** 日　  期:  2012-6-29
;** 修改原因：
;** 说    明:
;***************************************************************************/
void sprintfx(char *s, ...)
{
  char buffer[128] = {NULL}; // 分配512字节的字符串缓存
  uint8_t len, i;

  va_list ap;
  va_start(ap, s);
  vsprintf(buffer, (const char *)s, ap); // 将格式字符串与后面的参数绑定为一个字符串，拷贝到输出缓存
  va_end(ap);

  // 这里写自己的打印输出函数，比如这里用puts
  //    puts(buffer);
  len = strlen(buffer);

  for (i = 0; i < len; i++)
  {
    if (pUART->send)
    {
      while (usart_flag_get(USART1, USART_TDBE_FLAG) == RESET)
      {
        delay_us(3);
      }
      usart_data_transmit(USART1, buffer[i]);
    }
    if (pUSB->send)
    {
      while (usart_flag_get(USART3, USART_TDBE_FLAG) == RESET)
      {
        delay_us(3);
      }
      usart_data_transmit(USART3, buffer[i]);
    }
    if (pDUT->send == 1)
    {
      while (usart_flag_get(USART2, USART_TDBE_FLAG) == RESET)
      {
        delay_us(3);
      }
      usart_data_transmit(USART2, buffer[i]);
    }
    if (pDUT2->send == 1)
    {
      while (usart_flag_get(UART4, USART_TDBE_FLAG) == RESET)
      {
        delay_us(3);
      }
      usart_data_transmit(UART4, buffer[i]);
    }
  }
  if (pEther->send)
  {
    send(socku, (uint8_t *)buffer, len);
  }

  //--------------CH9434----------------------------------------------------
  if (pMultPort1->send == 1)
  {
    CH9434UARTxSetTxFIFOData(1, (uint8_t *)buffer, len);
  }

  if (pMultPort2->send == 1)
  {
    CH9434UARTxSetTxFIFOData(2, (uint8_t *)buffer, len);
  }

  if (pMultPort3->send == 1)
  {
    CH9434UARTxSetTxFIFOData(3, (uint8_t *)buffer, len);
  }

  if (pMultPort4->send == 1)
  {
    CH9434UARTxSetTxFIFOData(4, (uint8_t *)buffer, len);
  }
}

/***************************************************************************
;** 函数名称:
;** 功能描述:  USARTx 传送一帧数据
;** 输入参数:
;** 返 回 值:
;** 全局变量:
;** 调用模块:
;** 作　  者:   M-L-A
;** 日　  期:  2024-7-22
;** 修改原因：
;** 说    明:
;***************************************************************************/
void printfn(uint8_t *st, uint16_t num)
{
  uint16_t i;

  for (i = 0; i < num; i++)
  {
    if (pUART->send)
    {
      while (usart_flag_get(USART1, USART_TDBE_FLAG) == RESET)
        ;
      usart_data_transmit(USART1, st[i]);
    }
    if (pUSB->send)
    {
      while (usart_flag_get(USART3, USART_TDBE_FLAG) == RESET)
        ;
      usart_data_transmit(USART3, st[i]);
    }
    if (pDUT->send == 1)
    {
      while (usart_flag_get(USART2, USART_TDBE_FLAG) == RESET)
        ;
      usart_data_transmit(USART2, st[i]);
    }
    if (pDUT2->send == 1)
    {
      while (usart_flag_get(UART4, USART_TDBE_FLAG) == RESET)
        ;
      usart_data_transmit(UART4, st[i]);
    }
  }
  if (pEther->send)
  {
    send(SOCK_TCPS, (uint8_t *)st, num);
  }
  //--------------CH9434----------------------------------------------------
  if (pMultPort1->send == 1)
  {
    CH9434UARTxSetTxFIFOData(1, (uint8_t *)st, num);
  }

  if (pMultPort2->send == 1)
  {
    CH9434UARTxSetTxFIFOData(2, (uint8_t *)st, num);
  }

  if (pMultPort3->send == 1)
  {
    CH9434UARTxSetTxFIFOData(3, (uint8_t *)st, num);
  }

  if (pMultPort4->send == 1)
  {
    CH9434UARTxSetTxFIFOData(4, (uint8_t *)st, num);
  }
}
