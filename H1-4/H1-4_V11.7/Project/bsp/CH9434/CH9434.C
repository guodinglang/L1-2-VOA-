/********************************** (C) COPYRIGHT *******************************
 * File Name          : CH9434.c
 * Author             : tech18
 * Version            : V1.0
 * Date               : 2020/05/08
 * Description        : SPI转串口芯片CH9434操作接口
 *******************************************************************************/

#include "CH9434.h"

/*
一、芯片时钟配置相关说明：
1.外部晶振：32M
2.内部时钟频率：32M
3.开启倍频系数：15（固定）
4.芯片设置最高时钟频率不超过40M
5.串口基准时钟为：不开启倍频：32MHz  开启倍频：32MHz*15/分频系数

二、推荐常见波特率的计算方式
1.32M -> 串口基准时钟计算波特率：32M/8/波特率
2.32*15/13=36.923M -> 串口基准时钟计算波特率：36.923M/8/波特率 （如波特率：921600）

三、变量存储定义
1.osc_xt_frequency：记录外部晶振频率，当使用外部晶振时记录，调用CH9434OscXtFreqSet修改
2.sys_frequency：根据配置的时钟模式，得出的CH9434串口基准时钟，用于后面计算波特率
3.lower_power_reg：记录CH9434低功耗状态
4.ch9434_gpio_x_val：CH9434通用GPIO的输出电平值，按位定义，控制引脚电平函数：CH9434GPIOPinOut
*/

// 定义外部晶振频率
uint32_t osc_xt_frequency = 32000000;

// 定义当前串口基准时钟频率
uint32_t sys_frequency = 32000000; // 芯片默认为内部32M

// 睡眠模式
uint8_t lower_power_reg = 0;

// GPIO的输出电平值 共24个GPIO
// uint32_t ch9434_gpio_x_val = 0;

// extern __IO uint32_t u32FacUs;
extern rxStructure urStruct[];

/* SPI接口SCS引脚控制，0：低电平  1：高电平 */
void CH9434_SPI_SCS_OP(uint8_t sel)
{
    if (sel == 0)
    {
        GPIOB->clr = GPIO_PINS_6;
    }
    else
    {
        GPIOB->scr = GPIO_PINS_6;
    }
}

static void CH9434_US_DELAY(void)
{
    unsigned char d, us = 1;

    while (us--)
    {
        d = 45;
        while (d--)
            ;
    }
}

/* SPI交换一个字节接口 */
unsigned char CH9434_SPI_WRITE_BYTE(unsigned char dat)
{
    uint8_t ret = 0;
    while (spi_i2s_flag_get(SPI3, SPI_I2S_TDBE_FLAG) == RESET)
        ;
    spi_i2s_data_transmit(SPI3, dat);
    while (spi_i2s_flag_get(SPI3, SPI_I2S_RDBF_FLAG) == RESET)
        ;
    ret = (uint8_t)spi_i2s_data_receive(SPI3);
    return ret;
}

/*******************************************************************************
 * Function Name  : CH9434OscXtFreqSet
 * Description    : 外部晶振频率记录
 * Input          : x_freq：当前芯片连接的晶振频率
 * Output         : None
 * Return         : None
 *******************************************************************************/
void CH9434OscXtFreqSet(uint32_t x_freq)
{
    osc_xt_frequency = x_freq;
}

/*******************************************************************************
* Function Name  : CH9434InitClkMode
* Description    : CH9434芯片时钟模式设置
* Input          : xt_en：外部晶振使能
                   freq_mul_en：倍频功能使能
                   div_num：分频系数
* Output         : None
* Return         : None
*******************************************************************************/
void CH9434InitClkMode(uint8_t xt_en, uint8_t freq_mul_en, uint8_t div_num)
{
    uint8_t clk_ctrl_reg;

    clk_ctrl_reg = 0;
    if (freq_mul_en)
        clk_ctrl_reg |= (1 << 7);
    if (xt_en)
        clk_ctrl_reg |= (1 << 6);
    clk_ctrl_reg |= (div_num & 0x1f);

    /* 计算当前的串口基准时钟 */
    switch (clk_ctrl_reg & 0xC0)
    {
    case 0x00:
    { // 内部32M提供时钟
        sys_frequency = 32000000;
        break;
    }
    case 0x40:
    {                                                                       // 外部晶振提供时钟
        if ((osc_xt_frequency > 36000000) || (osc_xt_frequency < 24000000)) // 时钟错误
        {
            return;
        }
        sys_frequency = osc_xt_frequency;
        break;
    }
    case 0x80:
    { // 使用内部32M，并开启倍频
        sys_frequency = 480000000 / (div_num & 0x1f);
        if (sys_frequency > 40000000) // 时钟错误
        {
            sys_frequency = 32000000;
            return;
        }
        break;
    }
    case 0xc0:
    {                                                                       // 使用外部晶振，并开启倍频
        if ((osc_xt_frequency > 36000000) || (osc_xt_frequency < 24000000)) // 时钟错误
        {
            return;
        }
        sys_frequency = (osc_xt_frequency * 15) / (div_num & 0x1f);
        if (sys_frequency > 40000000) // 时钟错误
        {
            sys_frequency = 32000000;
            return;
        }
        break;
    }
    }

    CH9434_SPI_SCS_OP(CH9434_CS_EN);
    CH9434_SPI_WRITE_BYTE(CH9434_REG_OP_WRITE | CH9434_CLK_CTRL_CFG_ADD);
    CH9434_US_DELAY();
    CH9434_SPI_WRITE_BYTE(clk_ctrl_reg);
    CH9434_US_DELAY();
    CH9434_US_DELAY();
    CH9434_US_DELAY();
    CH9434_SPI_SCS_OP(CH9434_CS_DIS);
    delay_ms(100); // 切换时钟需要延时
}

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
void CH9434UARTxParaSet(uint8_t uart_idx, uint32_t bps, uint8_t data_bits, uint8_t stop_bits, uint8_t veri_bits)
{
    uint8_t uart_reg_dll;
    uint8_t uart_reg_dlm;
    uint32_t x;
    uint8_t uart_reg_lcr;

    x = 10 * sys_frequency / 8 / bps;
    x = (x + 5) / 10;

    uart_reg_dll = x & 0xff;
    uart_reg_dlm = (x >> 8) & 0xff;

    // DLAB置位 设置LCR寄存器
    CH9434_SPI_SCS_OP(CH9434_CS_EN);
    CH9434_SPI_WRITE_BYTE(CH9434_REG_OP_READ | CH9434_UARTx_LCR_ADD + 0x10 * uart_idx);
    CH9434_US_DELAY();
    CH9434_US_DELAY();
    CH9434_US_DELAY();
    uart_reg_lcr = CH9434_SPI_WRITE_BYTE(0xff);
    CH9434_US_DELAY();
    CH9434_SPI_SCS_OP(CH9434_CS_DIS);

    uart_reg_lcr |= CH9434_UARTx_BIT_DLAB;
    // 数据位
    uart_reg_lcr &= ~0x03;
    switch (data_bits)
    {
    case CH9434_UART_5_BITS_PER_CHAR:
        break;
    case CH9434_UART_6_BITS_PER_CHAR:
        uart_reg_lcr |= 0x01;
        break;
    case CH9434_UART_7_BITS_PER_CHAR:
        uart_reg_lcr |= 0x02;
        break;
    case CH9434_UART_8_BITS_PER_CHAR:
        uart_reg_lcr |= 0x03;
        break;
    default:
        uart_reg_lcr |= 0x03;
        break;
    }
    // 停止位
    uart_reg_lcr &= ~(1 << 2);
    if (stop_bits == CH9434_UART_TWO_STOP_BITS)
    {
        uart_reg_lcr |= (1 << 2);
    }
    // 校验位
    uart_reg_lcr &= ~(1 << 3);
    uart_reg_lcr &= ~(3 << 4);
    switch (veri_bits)
    {
    case CH9434_UART_NO_PARITY:
        break;
    case CH9434_UART_ODD_PARITY:
        uart_reg_lcr |= (1 << 3);
        break;
    case CH9434_UART_EVEN_PARITY:
        uart_reg_lcr |= (1 << 3);
        uart_reg_lcr |= (1 << 4);
        break;
    case CH9434_UART_MARK_PARITY:
        uart_reg_lcr |= (1 << 3);
        uart_reg_lcr |= (2 << 4);
        break;
    case CH9434_UART_SPACE_PARITY:
        uart_reg_lcr |= (1 << 3);
        uart_reg_lcr |= (3 << 4);
        break;
    default:
        break;
    }

    CH9434_SPI_SCS_OP(CH9434_CS_EN);
    CH9434_SPI_WRITE_BYTE(CH9434_REG_OP_WRITE | CH9434_UARTx_LCR_ADD + 0x10 * uart_idx);
    CH9434_US_DELAY();
    CH9434_SPI_WRITE_BYTE(uart_reg_lcr);
    CH9434_US_DELAY();
    CH9434_US_DELAY();
    CH9434_US_DELAY();
    CH9434_SPI_SCS_OP(CH9434_CS_DIS);

    // 设置DLL DLM
    CH9434_SPI_SCS_OP(CH9434_CS_EN);
    CH9434_SPI_WRITE_BYTE(CH9434_REG_OP_WRITE | CH9434_UARTx_DLL_ADD + 0x10 * uart_idx);
    CH9434_US_DELAY();
    CH9434_SPI_WRITE_BYTE(uart_reg_dll);
    CH9434_US_DELAY();
    CH9434_US_DELAY();
    CH9434_US_DELAY();
    CH9434_SPI_SCS_OP(CH9434_CS_DIS);

    CH9434_SPI_SCS_OP(CH9434_CS_EN);
    CH9434_SPI_WRITE_BYTE(CH9434_REG_OP_WRITE | CH9434_UARTx_DLM_ADD + 0x10 * uart_idx);
    CH9434_US_DELAY();
    CH9434_SPI_WRITE_BYTE(uart_reg_dlm);
    CH9434_US_DELAY();
    CH9434_US_DELAY();
    CH9434_US_DELAY();
    CH9434_SPI_SCS_OP(CH9434_CS_DIS);

    // DLAB清0
    uart_reg_lcr &= ~CH9434_UARTx_BIT_DLAB;

    CH9434_SPI_SCS_OP(CH9434_CS_EN);
    CH9434_SPI_WRITE_BYTE(CH9434_REG_OP_WRITE | CH9434_UARTx_LCR_ADD + 0x10 * uart_idx);
    CH9434_US_DELAY();
    CH9434_SPI_WRITE_BYTE(uart_reg_lcr);
    CH9434_US_DELAY();
    CH9434_US_DELAY();
    CH9434_US_DELAY();
    CH9434_SPI_SCS_OP(CH9434_CS_DIS);
}

/*******************************************************************************
* Function Name  : CH9434UARTxFIFOSet
* Description    : 串口FIFO设置
* Input          : uart_idx：串口号
                   fifo_en：FIFO功能使能
                   fifo_level：FIFO触发等级
* Output         : None
* Return         : None
*******************************************************************************/
void CH9434UARTxFIFOSet(uint8_t uart_idx, uint8_t fifo_en, uint8_t fifo_level)
{
    uint8_t uart_reg_fcr;

    uart_reg_fcr = 0;
    if (fifo_en)
    {
        uart_reg_fcr |= 0x01;
        uart_reg_fcr |= fifo_level << 6;
    }

    CH9434_SPI_SCS_OP(CH9434_CS_EN);
    CH9434_SPI_WRITE_BYTE(CH9434_REG_OP_WRITE | CH9434_UARTx_FCR_ADD + 0x10 * uart_idx);
    CH9434_US_DELAY();
    CH9434_SPI_WRITE_BYTE(uart_reg_fcr);
    CH9434_US_DELAY();
    CH9434_US_DELAY();
    CH9434_US_DELAY();
    CH9434_SPI_SCS_OP(CH9434_CS_DIS);
}

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
void CH9434UARTxIrqSet(uint8_t uart_idx, uint8_t modem, uint8_t line, uint8_t tx, uint8_t rx)
{
    uint8_t uart_reg_ier;

    uart_reg_ier = 0;
    if (modem)
        uart_reg_ier |= (1 << 3);
    if (line)
        uart_reg_ier |= (1 << 2);
    if (tx)
        uart_reg_ier |= (1 << 1);
    if (rx)
        uart_reg_ier |= (1 << 0);

    CH9434_SPI_SCS_OP(CH9434_CS_EN);
    CH9434_SPI_WRITE_BYTE(CH9434_REG_OP_WRITE | CH9434_UARTx_IER_ADD + 0x10 * uart_idx);
    CH9434_US_DELAY();
    CH9434_SPI_WRITE_BYTE(uart_reg_ier);
    CH9434_US_DELAY();
    CH9434_US_DELAY();
    CH9434_US_DELAY();
    CH9434_SPI_SCS_OP(CH9434_CS_DIS);
}

/* 流控功能和引脚设置 */
/*******************************************************************************
* Function Name  : CH9434UARTxFlowSet
* Description    : 流控设置
* Input          : uart_idx：串口号
                   flow_en：流控使能
* Output         : None
* Return         : None
*******************************************************************************/
void CH9434UARTxFlowSet(uint8_t uart_idx, uint8_t flow_en)
{
    uint8_t uart_reg_mcr;

    CH9434_SPI_SCS_OP(CH9434_CS_EN);
    CH9434_SPI_WRITE_BYTE(CH9434_REG_OP_READ | CH9434_UARTx_MCR_ADD + 0x10 * uart_idx);
    CH9434_US_DELAY();
    CH9434_US_DELAY();
    CH9434_US_DELAY();
    uart_reg_mcr = CH9434_SPI_WRITE_BYTE(0xff);
    CH9434_US_DELAY();
    CH9434_SPI_SCS_OP(CH9434_CS_DIS);

    uart_reg_mcr &= ~(1 << 5);
    if (flow_en)
        uart_reg_mcr |= (1 << 5);

    CH9434_SPI_SCS_OP(CH9434_CS_EN);
    CH9434_SPI_WRITE_BYTE(CH9434_REG_OP_WRITE | CH9434_UARTx_MCR_ADD + 0x10 * uart_idx);
    CH9434_US_DELAY();
    CH9434_SPI_WRITE_BYTE(uart_reg_mcr);
    CH9434_US_DELAY();
    CH9434_US_DELAY();
    CH9434_US_DELAY();
    CH9434_SPI_SCS_OP(CH9434_CS_DIS);
}

/*******************************************************************************
 * Function Name  : CH9434UARTxIrqOpen
 * Description    : 开启中断串口请求
 * Input          : uart_idx：串口号
 * Output         : None
 * Return         : None
 *******************************************************************************/
void CH9434UARTxIrqOpen(uint8_t uart_idx)
{
    uint8_t uart_reg_mcr;

    CH9434_SPI_SCS_OP(CH9434_CS_EN);
    CH9434_SPI_WRITE_BYTE(CH9434_REG_OP_READ | CH9434_UARTx_MCR_ADD + 0x10 * uart_idx);
    CH9434_US_DELAY();
    CH9434_US_DELAY();
    CH9434_US_DELAY();
    uart_reg_mcr = CH9434_SPI_WRITE_BYTE(0xff);
    CH9434_US_DELAY();
    CH9434_SPI_SCS_OP(CH9434_CS_DIS);

    uart_reg_mcr |= (1 << 3);

    CH9434_SPI_SCS_OP(CH9434_CS_EN);
    CH9434_SPI_WRITE_BYTE(CH9434_REG_OP_WRITE | CH9434_UARTx_MCR_ADD + 0x10 * uart_idx);
    CH9434_US_DELAY();
    CH9434_SPI_WRITE_BYTE(uart_reg_mcr);
    CH9434_US_DELAY();
    CH9434_US_DELAY();
    CH9434_US_DELAY();
    CH9434_SPI_SCS_OP(CH9434_CS_DIS);
}

/*******************************************************************************
* Function Name  : CH9434UARTxRtsDtrPin
* Description    : 设置串口RTS、DTR引脚
* Input          : uart_idx：串口号
                   rts_val：RTS引脚电平状态
                   dtr_val：DTR引脚电平状态
* Output         : None
* Return         : None
*******************************************************************************/
void CH9434UARTxRtsDtrPin(uint8_t uart_idx, uint8_t rts_val, uint8_t dtr_val)
{
    uint8_t uart_reg_mcr;

    CH9434_SPI_SCS_OP(CH9434_CS_EN);
    CH9434_SPI_WRITE_BYTE(CH9434_REG_OP_READ | CH9434_UARTx_MCR_ADD + 0x10 * uart_idx);
    CH9434_US_DELAY();
    CH9434_US_DELAY();
    CH9434_US_DELAY();
    uart_reg_mcr = CH9434_SPI_WRITE_BYTE(0xff);
    CH9434_US_DELAY();
    CH9434_SPI_SCS_OP(CH9434_CS_DIS);

    if (rts_val)
        uart_reg_mcr |= (1 << 1);
    else
        uart_reg_mcr &= ~(1 << 1);
    if (dtr_val)
        uart_reg_mcr |= (1 << 0);
    else
        uart_reg_mcr &= ~(1 << 0);

    CH9434_SPI_SCS_OP(CH9434_CS_EN);
    CH9434_SPI_WRITE_BYTE(CH9434_REG_OP_WRITE | CH9434_UARTx_MCR_ADD + 0x10 * uart_idx);
    CH9434_US_DELAY();
    CH9434_SPI_WRITE_BYTE(uart_reg_mcr);
    CH9434_US_DELAY();
    CH9434_US_DELAY();
    CH9434_US_DELAY();
    CH9434_SPI_SCS_OP(CH9434_CS_DIS);
}

/*******************************************************************************
* Function Name  : CH9434UARTxWriteSRC
* Description    : SRC寄存器写操作
* Input          : uart_idx：串口号
                   src_val：SRC寄存器值
* Output         : None
* Return         : None
*******************************************************************************/
void CH9434UARTxWriteSRC(uint8_t uart_idx, uint8_t src_val)
{
    CH9434_SPI_SCS_OP(CH9434_CS_EN);
    CH9434_SPI_WRITE_BYTE(CH9434_REG_OP_WRITE | CH9434_UARTx_SCR_ADD + 0x10 * uart_idx);
    CH9434_US_DELAY();
    CH9434_SPI_WRITE_BYTE(src_val);
    CH9434_US_DELAY();
    CH9434_US_DELAY();
    CH9434_US_DELAY();
    CH9434_SPI_SCS_OP(CH9434_CS_DIS);
}

/*******************************************************************************
 * Function Name  : CH9434UARTxReadSRC
 * Description    : SRC寄存器读操作
 * Input          : uart_idx：串口号
 * Output         : None
 * Return         : SRC寄存器值
 *******************************************************************************/
uint8_t CH9434UARTxReadSRC(uint8_t uart_idx)
{
    uint8_t uart_reg_src = 0;

    CH9434_SPI_SCS_OP(CH9434_CS_EN);
    CH9434_SPI_WRITE_BYTE(CH9434_REG_OP_READ | CH9434_UARTx_SCR_ADD + 0x10 * uart_idx);
    CH9434_US_DELAY();
    CH9434_US_DELAY();
    CH9434_US_DELAY();
    uart_reg_src = CH9434_SPI_WRITE_BYTE(0xff);
    CH9434_SPI_SCS_OP(CH9434_CS_DIS);

    return uart_reg_src;
}

/*******************************************************************************
 * Function Name  : CH9434UARTxReadIIR
 * Description    : 串口中断码查询
 * Input          : uart_idx：串口号
 * Output         : None
 * Return         : IIR寄存器值
 *******************************************************************************/
uint8_t CH9434UARTxReadIIR(uint8_t uart_idx)
{
    uint8_t uart_reg_iir = 0;

    CH9434_SPI_SCS_OP(CH9434_CS_EN);
    CH9434_SPI_WRITE_BYTE(CH9434_REG_OP_READ | CH9434_UARTx_IIR_ADD + 0x10 * uart_idx);
    CH9434_US_DELAY();
    CH9434_US_DELAY();
    CH9434_US_DELAY();
    CH9434_US_DELAY();
    uart_reg_iir = CH9434_SPI_WRITE_BYTE(0xff);
    CH9434_US_DELAY();
    CH9434_SPI_SCS_OP(CH9434_CS_DIS);

    return uart_reg_iir;
}

/*******************************************************************************
 * Function Name  : CH9434UARTxReadLSR
 * Description    : 串口LSR寄存器读取
 * Input          : uart_idx：串口号
 * Output         : None
 * Return         : LSR寄存器值
 *******************************************************************************/
uint8_t CH9434UARTxReadLSR(uint8_t uart_idx)
{
    uint8_t uart_reg_lsr = 0;

    CH9434_SPI_SCS_OP(CH9434_CS_EN);
    CH9434_SPI_WRITE_BYTE(CH9434_REG_OP_READ | CH9434_UARTx_LSR_ADD + 0x10 * uart_idx);
    CH9434_US_DELAY();
    CH9434_US_DELAY();
    CH9434_US_DELAY();
    CH9434_US_DELAY();
    uart_reg_lsr = CH9434_SPI_WRITE_BYTE(0xff);
    CH9434_US_DELAY();
    CH9434_SPI_SCS_OP(CH9434_CS_DIS);

    return uart_reg_lsr;
}

/*******************************************************************************
 * Function Name  : CH9434UARTxReadMSR
 * Description    : 串口MSR寄存器读取
 * Input          : uart_idx：串口号
 * Output         : None
 * Return         : MSR寄存器值
 *******************************************************************************/
uint8_t CH9434UARTxReadMSR(uint8_t uart_idx)
{
    uint8_t uart_reg_msr = 0;

    CH9434_SPI_SCS_OP(CH9434_CS_EN);
    CH9434_SPI_WRITE_BYTE(CH9434_REG_OP_READ | CH9434_UARTx_MSR_ADD + 0x10 * uart_idx);
    CH9434_US_DELAY();
    CH9434_US_DELAY();
    CH9434_US_DELAY();
    CH9434_US_DELAY();
    uart_reg_msr = CH9434_SPI_WRITE_BYTE(0xff);
    CH9434_US_DELAY();
    CH9434_SPI_SCS_OP(CH9434_CS_DIS);

    return uart_reg_msr;
}

/* 串口收发数据 */
/*******************************************************************************
 * Function Name  : CH9434UARTxGetRxFIFOLen
 * Description    : 获取串口接收数据长度
 * Input          : uart_idx：串口号
 * Output         : None
 * Return         : 串口接收FIFO的大小
 *******************************************************************************/
uint16_t CH9434UARTxGetRxFIFOLen(uint8_t uart_idx)
{
    uint8_t uart_fifo_ctrl = 0;
    uint8_t uart_fifo_cnt_l;
    uint8_t uart_fifo_cnt_h;
    uint16_t uart_fifo_cnt = 0;

    uart_fifo_ctrl |= uart_idx;

    CH9434_SPI_SCS_OP(CH9434_CS_EN);
    CH9434_SPI_WRITE_BYTE(CH9434_REG_OP_WRITE | CH9434_FIFO_CTRL_ADD);
    CH9434_US_DELAY();
    CH9434_SPI_WRITE_BYTE(uart_fifo_ctrl);
    CH9434_US_DELAY();
    CH9434_US_DELAY();
    CH9434_US_DELAY();
    CH9434_SPI_SCS_OP(CH9434_CS_DIS);

    CH9434_SPI_SCS_OP(CH9434_CS_EN);
    CH9434_SPI_WRITE_BYTE(CH9434_REG_OP_READ | CH9434_FIFO_CTRL_L_ADD);
    CH9434_US_DELAY();
    CH9434_US_DELAY();
    CH9434_US_DELAY();
    CH9434_US_DELAY();
    uart_fifo_cnt_l = CH9434_SPI_WRITE_BYTE(0xff);
    CH9434_SPI_SCS_OP(CH9434_CS_DIS);

    CH9434_SPI_SCS_OP(CH9434_CS_EN);
    CH9434_SPI_WRITE_BYTE(CH9434_REG_OP_READ | CH9434_FIFO_CTRL_H_ADD);
    CH9434_US_DELAY();
    CH9434_US_DELAY();
    CH9434_US_DELAY();
    CH9434_US_DELAY();
    uart_fifo_cnt_h = CH9434_SPI_WRITE_BYTE(0xff);
    CH9434_SPI_SCS_OP(CH9434_CS_DIS);

    uart_fifo_cnt = uart_fifo_cnt_h;
    uart_fifo_cnt = (uart_fifo_cnt << 8) | uart_fifo_cnt_l;

    return uart_fifo_cnt;
}

/*******************************************************************************
* Function Name  : CH9434UARTxGetRxFIFOData
* Description    : 读取串口接收数据
* Input          : uart_idx：串口号
                   p_data：数据存储指针
                   read_len：读取的数据长度
* Output         : None
* Return         : 空
*******************************************************************************/
uint8_t CH9434UARTxGetRxFIFOData(uint8_t uart_idx, uint8_t *p_data, uint16_t read_len)
{
    uint16_t i;
    uint8_t *p_sv_data;
    uint8_t uart_reg_add;

    uart_reg_add = CH9434_REG_OP_READ | CH9434_UARTx_RBR_ADD + 0x10 * uart_idx;
    p_sv_data = p_data;
    for (i = 0; i < read_len; i++)
    {
        CH9434_SPI_SCS_OP(CH9434_CS_EN);
        CH9434_SPI_WRITE_BYTE(uart_reg_add);
        CH9434_US_DELAY();
        CH9434_US_DELAY();
        CH9434_US_DELAY();
        *p_sv_data++ = CH9434_SPI_WRITE_BYTE(0xff);
        CH9434_US_DELAY();
        CH9434_SPI_SCS_OP(CH9434_CS_DIS);
    }

    return 0;
}

uint8_t multi_usart_data_receive(uint8_t uart_idx)
{
    uint8_t retVal;
    uint8_t uart_reg_add;

    uart_reg_add = CH9434_REG_OP_READ | CH9434_UARTx_RBR_ADD + 0x10 * uart_idx;

    CH9434_SPI_SCS_OP(CH9434_CS_EN);
    CH9434_SPI_WRITE_BYTE(uart_reg_add);
    CH9434_US_DELAY();
    CH9434_US_DELAY();
    CH9434_US_DELAY();
    retVal = CH9434_SPI_WRITE_BYTE(0xff);
    CH9434_US_DELAY();
    CH9434_SPI_SCS_OP(CH9434_CS_DIS);
    return retVal;
}

/*******************************************************************************
 * Function Name  : CH9434UARTxGetTxFIFOLen
 * Description    : 获取串口发送FIFO长度
 * Input          : uart_idx：串口号
 * Output         : None
 * Return         : 当前串口的接收数据长度
 *******************************************************************************/
uint16_t CH9434UARTxGetTxFIFOLen(uint8_t uart_idx)
{
    uint8_t uart_fifo_ctrl = 0;
    uint8_t uart_fifo_cnt_l;
    uint8_t uart_fifo_cnt_h;
    uint16_t uart_fifo_cnt = 0;

    uart_fifo_ctrl |= CH9434_FIFO_CTRL_TR;
    uart_fifo_ctrl |= uart_idx;

    CH9434_SPI_SCS_OP(CH9434_CS_EN);
    CH9434_SPI_WRITE_BYTE(CH9434_REG_OP_WRITE | CH9434_FIFO_CTRL_ADD);
    CH9434_US_DELAY();
    CH9434_SPI_WRITE_BYTE(uart_fifo_ctrl);
    CH9434_US_DELAY();
    CH9434_US_DELAY();
    CH9434_SPI_SCS_OP(CH9434_CS_DIS);

    CH9434_SPI_SCS_OP(CH9434_CS_EN);
    CH9434_SPI_WRITE_BYTE(CH9434_REG_OP_READ | CH9434_FIFO_CTRL_L_ADD);
    CH9434_US_DELAY();
    CH9434_US_DELAY();
    CH9434_US_DELAY();
    uart_fifo_cnt_l = CH9434_SPI_WRITE_BYTE(0xff);
    CH9434_SPI_SCS_OP(CH9434_CS_DIS);

    CH9434_SPI_SCS_OP(CH9434_CS_EN);
    CH9434_SPI_WRITE_BYTE(CH9434_REG_OP_READ | CH9434_FIFO_CTRL_H_ADD);
    CH9434_US_DELAY();
    CH9434_US_DELAY();
    CH9434_US_DELAY();
    uart_fifo_cnt_h = CH9434_SPI_WRITE_BYTE(0xff);
    CH9434_SPI_SCS_OP(CH9434_CS_DIS);

    uart_fifo_cnt = uart_fifo_cnt_h;
    uart_fifo_cnt = (uart_fifo_cnt << 8) | uart_fifo_cnt_l;

    return uart_fifo_cnt;
}

/*******************************************************************************
* Function Name  : CH9434UARTxSetTxFIFOData
* Description    : 串口填入发送数据
* Input          : uart_idx：串口号
                   p_data：发送数据指针
                   send_len：发送的数据长度
* Output         : None
* Return         : 空
*******************************************************************************/
uint8_t CH9434UARTxSetTxFIFOData(uint8_t uart_idx, uint8_t *p_data, uint16_t send_len)
{
    uint16_t i;
    uint8_t *p_sv_data;
    uint8_t uart_reg_add;

    if (uart_idx > 0)
    {
        uart_idx--;
    }
    uart_reg_add = CH9434_REG_OP_WRITE | CH9434_UARTx_RBR_ADD + 0x10 * uart_idx;
    p_sv_data = p_data;
    for (i = 0; i < send_len; i++)
    {
        CH9434_SPI_SCS_OP(CH9434_CS_EN);
        CH9434_SPI_WRITE_BYTE(uart_reg_add);
        CH9434_US_DELAY();
        CH9434_SPI_WRITE_BYTE(*p_sv_data++);
        CH9434_US_DELAY();
        CH9434_US_DELAY();
        CH9434_US_DELAY();
        CH9434_SPI_SCS_OP(CH9434_CS_DIS);
    }

    return 0;
}

void multi_usart_data_transmit(uint8_t uart_idx, uint8_t p_data)
{
    uint8_t uart_reg_add;

    if (uart_idx > 0)
    {
        uart_idx--;
    }
    uart_reg_add = CH9434_REG_OP_WRITE | CH9434_UARTx_RBR_ADD + 0x10 * uart_idx;

    CH9434_SPI_SCS_OP(CH9434_CS_EN);
    CH9434_SPI_WRITE_BYTE(uart_reg_add);
    CH9434_US_DELAY();
    CH9434_SPI_WRITE_BYTE(p_data);
    CH9434_US_DELAY();
    CH9434_US_DELAY();
    CH9434_US_DELAY();
    CH9434_SPI_SCS_OP(CH9434_CS_DIS);
}

/*******************************************************************************
* Function Name  : CH9434UARTxTnowSet
* Description    : 串口485切换引脚设置
* Input          : uart_idx：串口号
                   tnow_en：串口tnow使能状态
                   polar：极性反向设置
* Output         : None
* Return         : None
*******************************************************************************/
void CH9434UARTxTnowSet(uint8_t uart_idx, uint8_t tnow_en, uint8_t polar)
{
    uint8_t tnow_ctrl_reg;

    CH9434_SPI_SCS_OP(CH9434_CS_EN);
    CH9434_SPI_WRITE_BYTE(CH9434_REG_OP_READ | CH9434_TNOW_CTRL_CFG_ADD);
    CH9434_US_DELAY();
    CH9434_US_DELAY();
    CH9434_US_DELAY();
    tnow_ctrl_reg = CH9434_SPI_WRITE_BYTE(0xff);
    CH9434_US_DELAY();
    CH9434_SPI_SCS_OP(CH9434_CS_DIS);

    if (tnow_en)
        tnow_ctrl_reg |= (1 << uart_idx);
    else
        tnow_ctrl_reg &= ~(1 << uart_idx);

    if (polar)
        tnow_ctrl_reg |= (1 << (uart_idx + 4));
    else
        tnow_ctrl_reg &= ~(1 << (uart_idx + 4));

    CH9434_SPI_SCS_OP(CH9434_CS_EN);
    CH9434_SPI_WRITE_BYTE(CH9434_REG_OP_WRITE | CH9434_TNOW_CTRL_CFG_ADD);
    CH9434_US_DELAY();
    CH9434_SPI_WRITE_BYTE(tnow_ctrl_reg);
    CH9434_US_DELAY();
    CH9434_US_DELAY();
    CH9434_US_DELAY();
    CH9434_SPI_SCS_OP(CH9434_CS_DIS);
}

/*******************************************************************************
 * Function Name  : CH9434LowerPowerModeSet
 * Description    : CH9434芯片低功耗设置
 * Input          : mode：低功耗模式
 * Output         : None
 * Return         : None
 *******************************************************************************/
void CH9434LowerPowerModeSet(uint8_t mode)
{
    lower_power_reg = mode;
    CH9434_SPI_SCS_OP(CH9434_CS_EN);
    CH9434_SPI_WRITE_BYTE(CH9434_REG_OP_WRITE | CH9434_SLEEP_MOD_CFG_ADD);
    CH9434_US_DELAY();
    CH9434_SPI_WRITE_BYTE(lower_power_reg);
    CH9434_US_DELAY();
    CH9434_US_DELAY();
    CH9434_US_DELAY();
    CH9434_SPI_SCS_OP(CH9434_CS_DIS);
}

/*******************************************************************************
 * Function Name  : CH9434WakeUp
 * Description    : CH9434唤醒操作，从低功耗模式中唤醒，也可操作SPI进行唤醒
 * Input          : None
 * Output         : None
 * Return         : None
 *******************************************************************************/
void vCH9434WakeUp(void)
{
    CH9434_SPI_SCS_OP(CH9434_CS_EN);

    delay_ms(10);
    CH9434_SPI_SCS_OP(CH9434_CS_DIS);
}

/*******************************************************************************
 * Function Name  : CH9434WakeUp
 * Description    : CH9434唤醒操作，从低功耗模式中唤醒，也可操作SPI进行唤醒
 * Input          : None
 * Output         : None
 * Return         : None
 *******************************************************************************/
void CH9434_Init(void)
{
    uint32_t uartBaudVal = 921600; // 115200;
    delay_ms(20);
    vCH9434WakeUp();
    delay_ms(100);
    CH9434InitClkMode(CH9434_ENABLE, CH9434_ENABLE, 13);
    /* port 0 init */
    // config UART para
    CH9434UARTxParaSet(CH9434_UART_IDX_0,           // port select
                       uartBaudVal,                 // set baud
                       CH9434_UART_8_BITS_PER_CHAR, // data length
                       CH9434_UART_ONE_STOP_BIT,    // stop bit length
                       CH9434_UART_NO_PARITY);      // even_odd check
    // config FIFO
    CH9434UARTxFIFOSet(CH9434_UART_IDX_0,           // port select
                       CH9434_ENABLE,               // FIFO enable
                       CH9434_UART_FIFO_MODE_1024); // FIFO trig level
    // config flow control
    CH9434UARTxFlowSet(CH9434_UART_IDX_0, CH9434_DISABLE); // port flow disable
    // config UART interrupt
    CH9434UARTxIrqSet(CH9434_UART_IDX_0, // uart select
                      CH9434_DISABLE,    // MODEM signal interrupt disable
                      CH9434_DISABLE,    // line status interrupt
                      CH9434_DISABLE,    // tx interrupt disable
                      CH9434_DISABLE);   // rx interrupt enable
    // enable port 0 interrupt
    CH9434UARTxIrqOpen(CH9434_UART_IDX_0);
    CH9434UARTxRtsDtrPin(CH9434_UART_IDX_0, CH9434_DISABLE, CH9434_DISABLE);

    /* port 1init */
    CH9434UARTxParaSet(CH9434_UART_IDX_1,
                       uartBaudVal,
                       CH9434_UART_8_BITS_PER_CHAR,
                       CH9434_UART_ONE_STOP_BIT,
                       CH9434_UART_NO_PARITY);
    CH9434UARTxFIFOSet(CH9434_UART_IDX_1,
                       CH9434_ENABLE,
                       CH9434_UART_FIFO_MODE_1024);
    CH9434UARTxFlowSet(CH9434_UART_IDX_1, CH9434_DISABLE);
    CH9434UARTxIrqSet(CH9434_UART_IDX_1,
                      CH9434_DISABLE,
                      CH9434_DISABLE,
                      CH9434_DISABLE,
                      CH9434_DISABLE);
    // enable port 1 interrupt
    CH9434UARTxIrqOpen(CH9434_UART_IDX_1);
    CH9434UARTxRtsDtrPin(CH9434_UART_IDX_1, CH9434_DISABLE, CH9434_DISABLE);

    /* port 2init */
    CH9434UARTxParaSet(CH9434_UART_IDX_2,
                       uartBaudVal,
                       CH9434_UART_8_BITS_PER_CHAR,
                       CH9434_UART_ONE_STOP_BIT,
                       CH9434_UART_NO_PARITY);

    CH9434UARTxFIFOSet(CH9434_UART_IDX_2,
                       CH9434_ENABLE,
                       CH9434_UART_FIFO_MODE_1024);
    CH9434UARTxFlowSet(CH9434_UART_IDX_2, CH9434_DISABLE);
    CH9434UARTxIrqSet(CH9434_UART_IDX_2,
                      CH9434_DISABLE,
                      CH9434_DISABLE,
                      CH9434_DISABLE,
                      CH9434_DISABLE);
    // enable port 2 interrupt
    CH9434UARTxIrqOpen(CH9434_UART_IDX_2);
    CH9434UARTxRtsDtrPin(CH9434_UART_IDX_2, CH9434_DISABLE, CH9434_DISABLE);

    /* port 3 init */
    CH9434UARTxParaSet(CH9434_UART_IDX_3,
                       uartBaudVal,
                       CH9434_UART_8_BITS_PER_CHAR,
                       CH9434_UART_ONE_STOP_BIT,
                       CH9434_UART_NO_PARITY);

    CH9434UARTxFIFOSet(CH9434_UART_IDX_3,
                       CH9434_ENABLE,
                       CH9434_UART_FIFO_MODE_1024);
    CH9434UARTxFlowSet(CH9434_UART_IDX_3, CH9434_DISABLE);
    CH9434UARTxIrqSet(CH9434_UART_IDX_3,
                      CH9434_DISABLE,
                      CH9434_DISABLE,
                      CH9434_DISABLE,
                      CH9434_DISABLE);
    // enable port 3 interrupt
    CH9434UARTxIrqOpen(CH9434_UART_IDX_3);
    CH9434UARTxRtsDtrPin(CH9434_UART_IDX_3, CH9434_DISABLE, CH9434_DISABLE);
}

/*******************************************************************************
 * Function Name  : CH9434Polling
 * Description    : 轮询查询
 * Input          : None
 * Output         : None
 * Return         : None
 *******************************************************************************/
void CH9434Polling(void)
{
    static uint8_t uart_idx = 0;
    uint8_t v;
    rxStructure *pt;

    pt = &urStruct[4 + uart_idx];
    switch (0x0F & CH9434UARTxReadIIR(uart_idx))
    {
    case 0x01:
        break;

    case 0x06:
    { // 接收线路状态 读 LSR
        if (pt->len >= RX_MAX_FIFO)
        {
            pt->len = 0;
        }
        CH9434UARTxGetRxFIFOLen(uart_idx);
        while (0x01 & CH9434UARTxReadLSR(uart_idx))
        {
            CH9434UARTxGetRxFIFOData(uart_idx, &v, 1);
            pt->rxFIFO[pt->len++] = v;
            if (pt->len >= RX_MAX_FIFO)
            {
                break;
            }
        }
        pt->TimeOut = 500;
    }
    break;

    case 0x04:
    { // 接收数据可用 读 RBR
        if (pt->len >= RX_MAX_FIFO)
        {
            pt->len = 0;
        }
        CH9434UARTxGetRxFIFOLen(uart_idx);
        while (0x01 & CH9434UARTxReadLSR(uart_idx))
        {
            CH9434UARTxGetRxFIFOData(uart_idx, &v, 1);
            pt->rxFIFO[pt->len++] = v;
            if (pt->len >= RX_MAX_FIFO)
            {
                break;
            }
        }
        pt->TimeOut = 500;
    }
    break;

    case 0x0C:
    { // 接收数据超时； 超过 4 个数据的时间未收到下一数据； 读 RBR

        if (pt->len >= RX_MAX_FIFO)
        {
            pt->len = 0;
        }
        CH9434UARTxGetRxFIFOLen(uart_idx);
        while (0x01 & CH9434UARTxReadLSR(uart_idx))
        {
            CH9434UARTxGetRxFIFOData(uart_idx, &v, 1);
            pt->rxFIFO[pt->len++] = v;
            if (pt->len >= RX_MAX_FIFO)
            {
                break;
            }
        }
        pt->TimeOut = 500;
    }
    break;

    case 0x02:
    { // THR 寄存器空 读 IIR或写 THR
        break;
    }
    case 0x00:
    { // MODEM 输入变化 读 MSR
        CH9434UARTxReadMSR(uart_idx);
        break;
    }
    }

    uart_idx++;
    if (uart_idx >= CH9434_CHN_NUM)
    {
        uart_idx = 0;
    }
}
