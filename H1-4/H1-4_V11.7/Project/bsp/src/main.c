
/**********************************************************************************************************
 *
 *	模块名称 : 	程序 BSP(Board Support Package)
 *	文件名称 :
 *	版    本 :  V1.0
 *	说    明 :  硬件底层驱动程序集合
 *	修改记录 :
 *   版 本 号 :
 *   日    期 :
 *   作    者 :   M-L-A
 *	说    明 :
 *
 **********************************************************************************************************/

// #include "at32f415_clock.h"
#include "project.h"
#include "main.h"
#include "includes.h"

void Task_25ms(void *arg)
{
  UpdateUARTHMI();
}

/***************************************************************************
;** 函数名称:
;** 功能描述:
;** 输入参数:
;** 返 回 值:
;** 全局变量:
;** 调用模块:
;** 作　  者:   M-L-A
;** 日　  期:   2022-5-25
;** 修改原因：
;** 说    明:

;***************************************************************************/
int main(void)
{
  system_clock_config();
  SysTickConfigure();
  ioConfig();
  DAC1_Config();
  swIIC_config();
  epramInitialize();
  lcd_init();
  usart1_config(setups.brUART);
  usart2_config(setups.brDUT); // DUT
  usart3_config(setups.brUSB);
  uart4_config(115200); // DUT2 setups.brDUT
  SPI2_Config();
  SPI3_Config();
  can_config();
  CH9434_Init();
  BuzzerIOconfig();
  set_w5500_netinfo();
  bsp_Init();
  //	configWDT(2500);	//1.6ms*x

  //	txCAN1("123456789",9);

  {
    time_wheel_init(&tw);
    add_timer(&tw, 25, 25, Task_25ms, NULL);
  }

  while (1)
  {
    CH9434Polling();
    InputIOScan();
    KeyCallback();
    ethernet_tcp_server();
    rxCommandDispose(pUART);
    rxCommandDispose(pUSB);
    rxCommandDispose(pEther);
    DisplayUARTHMI(); // ParameterSetup();
    SwitchMessage();
    BuzPoll();
    WorkStateLED();
    //		wdt_counter_reload();

    time_wheel_execute(&tw);
  }
}
