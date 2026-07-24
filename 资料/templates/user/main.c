#include "includes.h"

/**
 * @brief  main function.
 * @param  none
 * @retval none
 */
int main(void)
{
  if (AppPort_Wdt_IsTrig() == true)
  {
    /* reset from wdt */
  }

  AppInfo_Init();

  if (AppInfo.ucSpeak)
  {
    BspBuzzer_Start(100, 0, 1);
  }

  { // 调整串口波特率
    BspUart_ClrTxFifo(BspUartCom_RS232);
    BspUart_ClrRxFifo(BspUartCom_RS232);
    BspUart_ClrTxFifo(BspUartCom_USB);
    BspUart_ClrRxFifo(BspUartCom_USB);
    BspUart_ClrTxFifo(BspUartCom_DUT);
    BspUart_ClrRxFifo(BspUartCom_DUT);
    BspUart_ClrTxFifo(BspUartCom_DUT2);
    BspUart_ClrRxFifo(BspUartCom_DUT2);
    BspUart_SetBaudRate(BspUartCom_RS232, AppInfo.ulBaudRate_UART);
    BspUart_SetBaudRate(BspUartCom_USB, AppInfo.ulBaudRate_USB);
    BspUart_SetBaudRate(BspUartCom_DUT, AppInfo.ulBaudRate_DUT);
    BspUart_SetBaudRate(BspUartCom_DUT2, AppInfo.ulBaudRate_DUT2);
  }

  AppThread_Base_Creat();
  AppThread_Creat();
}
