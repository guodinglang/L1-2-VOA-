#include "project.h"
#include "CH9434.h"
#include "uart_process.h"

extern rxStructure urStruct[8];

void CH9434_Init(void)
{
    uint32_t uartBaudVal = 115200;
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

void vCH9434Process(void)
{
    static uint8_t uart_idx = 0;
    uint8_t uart_lsr, uart_iir;
    uint8_t temp, b;
    rxStructure *portPtr;

    portPtr = &urStruct[3 + uart_idx];
    uart_iir = CH9434UARTxReadIIR(uart_idx);
    switch (uart_iir & 0x0F)
    {
    case 0x01:
    {
        break;
    }
    case 0x06:
    { // 接收线路状态 读 LSR
        uart_lsr = CH9434UARTxReadLSR(uart_idx);
        while ((uart_lsr & 0x01) == 0x01)
        {
            CH9434UARTxGetRxFIFOData(uart_idx, &temp, 1);
            portPtr->rxFIFO[portPtr->len] = temp;
            portPtr->len = (portPtr->len + 1) % RX_MAX_FIFO;
            if (temp == '\r')
            {
                portPtr->rxn++;
            }
            uart_lsr = CH9434UARTxReadLSR(uart_idx);
            portPtr->TimeOut = 10;
        }
        break;
    }
    case 0x04:
    { // 接收数据可用 读 RBR
        uart_lsr = CH9434UARTxReadLSR(uart_idx);

        while ((uart_lsr & 0x01) == 0x01)
        {
            CH9434UARTxGetRxFIFOData(uart_idx, &temp, 1);
            portPtr->rxFIFO[portPtr->len] = temp;
            portPtr->len = (portPtr->len + 1) % RX_MAX_FIFO;
            if (temp == '\r')
            {
                portPtr->rxn++;
            }
            uart_lsr = CH9434UARTxReadLSR(uart_idx);
            portPtr->TimeOut = 10;
        }

        break;
    }
    case 0x0C:
    { // 接收数据超时； 超过 4 个数据的时间未收到下一数据； 读 RBR

        uint8_t str[64] = {0};

        //            uart_lsr = CH9434UARTxReadLSR(uart_idx);

        b = CH9434UARTxGetRxFIFOLen(uart_idx);
        if (b > 0)
        {
            memset(portPtr->rxFIFO, 0, sizeof(portPtr->rxFIFO));
            memset(str, 0, sizeof(str));
            CH9434UARTxGetRxFIFOData(uart_idx, str, b);
            memcpy(portPtr->rxFIFO, &str[0], b);
        }
        pUART->send = 1;
        {
            printfx((char *)str);
        }

        b = 0; // CH9434UARTxGetRxFIFOLen(uart_idx);

        //            while((uart_lsr & 0x01) == 0x01)
        //            {
        //                CH9434UARTxGetRxFIFOData(uart_idx,&temp,1);
        //                portPtr->rxFIFO[portPtr->len] = temp;
        //                portPtr->len = (portPtr->len + 1) % RX_MAX_FIFO;
        //                if(temp == '\r')
        //                {
        //                    portPtr->rxn ++;
        //                }
        //                uart_lsr = CH9434UARTxReadLSR(uart_idx);
        //                portPtr->TimeOut = 10;
        //            }
        break;
    }
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
    uart_idx = (uart_idx + 1) % CH9434_CHN_NUM;
}

// void EXINT9_5_IRQHandler()
//{
//     if(exint_flag_get(EXINT_LINE_7) != RESET)
//     {
//         vCH9434Process();
//         exint_flag_clear(EXINT_LINE_7);
//     }
// }
