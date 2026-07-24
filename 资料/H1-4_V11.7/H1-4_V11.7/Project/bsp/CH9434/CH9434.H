/********************************** (C) COPYRIGHT *******************************
 * File Name          : CH9434.h
 * Author             : tech18
 * Version            : V1.0
 * Date               : 2020/05/08
 * Description        : SPI转串口芯片CH9434操作接口头文件定义
 *******************************************************************************/

/******************************************************************************/
#ifndef __CH9434_H__
#define __CH9434_H__

#include "project.h"

/* -----------------------------------------------------------------------------
 *                       调用外部接口函数--用户层定义
 * -----------------------------------------------------------------------------
 */

/* -----------------------------------------------------------------------------
 *                                   宏定义
 * -----------------------------------------------------------------------------
 */
/* enable/disable bit */
#define CH9434_ENABLE (1)
#define CH9434_DISABLE (0)

/* cs pin enable/disable */
#define CH9434_CS_EN (0)
#define CH9434_CS_DIS (1)

/* 串口号 */
#define CH9434_UART_IDX_0 (0)
#define CH9434_UART_IDX_1 (1)
#define CH9434_UART_IDX_2 (2)
#define CH9434_UART_IDX_3 (3)

/* 寄存器操作 */
#define CH9434_REG_OP_WRITE (0x80)
#define CH9434_REG_OP_READ (0x00)

/* 寄存器 */
#define CH9434_UART0_REG_OFFSET_ADD (0x00)
#define CH9434_UART1_REG_OFFSET_ADD (0x10)
#define CH9434_UART2_REG_OFFSET_ADD (0x20)
#define CH9434_UART3_REG_OFFSET_ADD (0x30)
#define CH9434_UARTx_RBR_ADD (0)
#define CH9434_UARTx_THR_ADD (0)
#define CH9434_UARTx_IER_ADD (1)
#define CH9434_UARTx_IIR_ADD (2)
#define CH9434_UARTx_FCR_ADD (2)
#define CH9434_UARTx_LCR_ADD (3)
#define CH9434_UARTx_BIT_DLAB (1 << 7)
#define CH9434_UARTx_MCR_ADD (4)
#define CH9434_UARTx_LSR_ADD (5)
#define CH9434_UARTx_MSR_ADD (6)
#define CH9434_UARTx_SCR_ADD (7)
#define CH9434_UARTx_DLL_ADD (0)
#define CH9434_UARTx_DLM_ADD (1)

// TNOW UART相关
#define CH9434_TNOW_CTRL_CFG_ADD (0x41)
#define CH9434_BIT_TNOW_OUT_POLAR (0xF0)
#define CH9434_BIT_TNOW_OUT_EN (0x0F)
#define CH9434_FIFO_CTRL_ADD (0x42)
#define CH9434_FIFO_CTRL_TR (1 << 4)
#define CH9434_FIFO_UART_IDX (0x0F)
#define CH9434_FIFO_CTRL_L_ADD (0x43)
#define CH9434_FIFO_CTRL_H_ADD (0x44)

// 电源时钟设置
#define CH9434_CLK_CTRL_CFG_ADD (0x48)
#define CH9434_CLK_CTRL_MOD (3 << 6)
#define CH9434_XT_POWER_EN (1 << 5)
#define CH9434_CLK_DIV_MASK (0x1F)
#define CH9434_SLEEP_MOD_CFG_ADD (0x4A)

/* 串口参数定义 */
/* FIFO Size */
#define CH9434_UART_FIFO_MODE_256 (0)  // 256
#define CH9434_UART_FIFO_MODE_512 (1)  // 512
#define CH9434_UART_FIFO_MODE_1024 (2) // 1024
#define CH9434_UART_FIFO_MODE_1280 (3) // 1280
/* Character Size */
#define CH9434_UART_5_BITS_PER_CHAR (5)
#define CH9434_UART_6_BITS_PER_CHAR (6)
#define CH9434_UART_7_BITS_PER_CHAR (7)
#define CH9434_UART_8_BITS_PER_CHAR (8)
/* Stop Bits */
#define CH9434_UART_ONE_STOP_BIT (1)
#define CH9434_UART_TWO_STOP_BITS (2)
/* Parity settings */
#define CH9434_UART_NO_PARITY (0x00)    // 无校验
#define CH9434_UART_ODD_PARITY (0x01)   // 奇校验
#define CH9434_UART_EVEN_PARITY (0x02)  // 偶校验
#define CH9434_UART_MARK_PARITY (0x03)  // 置1 mark
#define CH9434_UART_SPACE_PARITY (0x04) // 空白0 SPACE

/* TNOW序号 */
#define CH9434_TNOW_POLAR_NORMAL (0) // 正常输出
#define CH9434_TNOW_POLAR_OPPO (1)   // 反向输出

#define CH9434_TNOW_0 (0)
#define CH9434_TNOW_1 (1)
#define CH9434_TNOW_2 (2)
#define CH9434_TNOW_3 (3)

/* 低功耗模式 */
#define CH9434_LOWPOWER_INVALID (0)
#define CH9434_LOWPOWER_SLEEP (1)

#define CH9434_CHN_NUM (4)

/* -----------------------------------------------------------------------------
 *                                  接口函数
 * -----------------------------------------------------------------------------
 */
/*******************************************************************************
 * Function Name  : CH9434OscXtFreqSet
 * Description    : 外部晶振频率记录
 * Input          : x_freq：当前芯片连接的晶振频率
 * Output         : None
 * Return         : None
 *******************************************************************************/
void CH9434OscXtFreqSet(unsigned int x_freq);
/*******************************************************************************
* Function Name  : CH9434InitClkMode
* Description    : CH9434芯片时钟模式设置
* Input          : xt_en：外部晶振使能
                   freq_mul_en：倍频功能使能
                   div_num：分频系数
* Output         : None
* Return         : None
*******************************************************************************/
void CH9434InitClkMode(unsigned char xt_en, unsigned char freq_mul_en, unsigned char div_num);
/*******************************************************************************
* Function Name  : CH9434UARTxParaSet
* Description    : 串口参数设置
* Input          : uart_idx：串口号
                   bps：串口的波特率
                   data_bits：数据位
                   stop_bits：停止位
                   veri_bits：校验位
* Output         : None
* Return         : None
*******************************************************************************/
void CH9434UARTxParaSet(unsigned char uart_idx, unsigned int bps, unsigned char data_bits, unsigned char stop_bits, unsigned char veri_bits);
/*******************************************************************************
* Function Name  : CH9434UARTxFIFOSet
* Description    : 串口FIFO设置
* Input          : uart_idx：串口号
                   fifo_en：FIFO功能使能
                   fifo_level：FIFO触发等级
* Output         : None
* Return         : None
*******************************************************************************/
void CH9434UARTxFIFOSet(unsigned char uart_idx, unsigned char fifo_en, unsigned char fifo_level);
/*******************************************************************************
* Function Name  : CH9434UARTxIrqSet
* Description    : 串口中断设置
* Input          : uart_idx：串口号
                   modem：modem信号中断
                   line：线路状态中断
                   tx：发送中断
                   rx：接收中断
* Output         : None
* Return         : None
*******************************************************************************/
void CH9434UARTxIrqSet(unsigned char uart_idx, unsigned char modem, unsigned char line, unsigned char tx, unsigned char rx);
/*******************************************************************************
* Function Name  : CH9434UARTxFlowSet
* Description    : 流控设置
* Input          : uart_idx：串口号
                   flow_en：流控使能
* Output         : None
* Return         : None
*******************************************************************************/
void CH9434UARTxFlowSet(unsigned char uart_idx, unsigned char flow_en);
/*******************************************************************************
 * Function Name  : CH9434UARTxIrqOpen
 * Description    : 开启中断串口请求
 * Input          : uart_idx：串口号
 * Output         : None
 * Return         : None
 *******************************************************************************/
void CH9434UARTxIrqOpen(unsigned char uart_idx);
/*******************************************************************************
* Function Name  : CH9434UARTxRtsDtrPin
* Description    : 设置串口RTS、DTR引脚
* Input          : uart_idx：串口号
                   rts_val：RTS引脚电平状态
                   dtr_val：DTR引脚电平状态
* Output         : None
* Return         : None
*******************************************************************************/
void CH9434UARTxRtsDtrPin(unsigned char uart_idx, unsigned char rts_val, unsigned char dtr_val);
/*******************************************************************************
* Function Name  : CH9434UARTxWriteSRC
* Description    : SRC寄存器写操作
* Input          : uart_idx：串口号
                   src_val：SRC寄存器值
* Output         : None
* Return         : None
*******************************************************************************/
void CH9434UARTxWriteSRC(unsigned char uart_idx, unsigned char src_val);
/*******************************************************************************
 * Function Name  : CH9434UARTxReadSRC
 * Description    : SRC寄存器读操作
 * Input          : uart_idx：串口号
 * Output         : None
 * Return         : SRC寄存器值
 *******************************************************************************/
unsigned char CH9434UARTxReadSRC(unsigned char uart_idx);
/*******************************************************************************
 * Function Name  : CH9434UARTxReadIIR
 * Description    : 串口中断码查询
 * Input          : uart_idx：串口号
 * Output         : None
 * Return         : IIR寄存器值
 *******************************************************************************/
unsigned char CH9434UARTxReadIIR(unsigned char uart_idx);
/*******************************************************************************
 * Function Name  : CH9434UARTxReadLSR
 * Description    : 串口LSR寄存器读取
 * Input          : uart_idx：串口号
 * Output         : None
 * Return         : LSR寄存器值
 *******************************************************************************/
unsigned char CH9434UARTxReadLSR(unsigned char uart_idx);
/*******************************************************************************
 * Function Name  : CH9434UARTxReadMSR
 * Description    : 串口MSR寄存器读取
 * Input          : uart_idx：串口号
 * Output         : None
 * Return         : MSR寄存器值
 *******************************************************************************/
unsigned char CH9434UARTxReadMSR(unsigned char uart_idx);
/*******************************************************************************
 * Function Name  : CH9434UARTxGetRxFIFOLen
 * Description    : 获取串口接收数据长度
 * Input          : uart_idx：串口号
 * Output         : None
 * Return         : 串口接收FIFO的大小
 *******************************************************************************/
unsigned short int CH9434UARTxGetRxFIFOLen(unsigned char uart_idx);
/*******************************************************************************
* Function Name  : CH9434UARTxGetRxFIFOData
* Description    : 读取串口接收数据
* Input          : uart_idx：串口号
                   p_data：数据存储指针
                   read_len：读取的数据长度
* Output         : None
* Return         : 空
*******************************************************************************/
unsigned char CH9434UARTxGetRxFIFOData(unsigned char uart_idx, unsigned char *p_data, unsigned short int read_len);
/*******************************************************************************
 * Function Name  : CH9434UARTxGetTxFIFOLen
 * Description    : 获取串口发送FIFO长度
 * Input          : uart_idx：串口号
 * Output         : None
 * Return         : 当前串口的接收数据长度
 *******************************************************************************/
unsigned short int CH9434UARTxGetTxFIFOLen(unsigned char uart_idx);
/*******************************************************************************
* Function Name  : CH9434UARTxGetRxFIFOData
* Description    : 串口填入发送数据
* Input          : uart_idx：串口号
                   p_data：发送数据指针
                   send_len：发送的数据长度
* Output         : None
* Return         : 空
*******************************************************************************/
unsigned char CH9434UARTxSetTxFIFOData(unsigned char uart_idx, unsigned char *p_data, unsigned short int send_len);
/*******************************************************************************
* Function Name  : CH9434UARTxTnowSet
* Description    : 串口485切换引脚设置
* Input          : uart_idx：串口号
                   tnow_en：串口tnow使能状态
                   polar：极性反向设置
* Output         : None
* Return         : None
*******************************************************************************/
void CH9434UARTxTnowSet(unsigned char uart_idx, unsigned char tnow_en, unsigned char polar);
/*******************************************************************************
 * Function Name  : CH9434LowerPowerModeSet
 * Description    : CH9434芯片低功耗设置
 * Input          : mode：低功耗模式
 * Output         : None
 * Return         : None
 *******************************************************************************/
void CH9434LowerPowerModeSet(unsigned char mode);
/*******************************************************************************
 * Function Name  : CH9434WakeUp
 * Description    : CH9434唤醒操作，从低功耗模式中唤醒
 * Input          : None
 * Output         : None
 * Return         : None
 *******************************************************************************/
void vCH9434WakeUp(void);

/*******************************************************************************/
void multi_usart_data_transmit(unsigned char uart_idx, unsigned char p_data);
unsigned char multi_usart_data_receive(unsigned char uart_idx);
void CH9434_Init(void);
void CH9434Polling(void);

/******************************************************************************/

#endif
