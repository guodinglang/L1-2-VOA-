
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
  DAC1_Config(); // TFT_BL_Curr 设置背光电流DAC1
  swIIC_config(); // EEPROM IIC 1K字节
  epramInitialize(); // EEPROM初始化 AT24C08C
  lcd_init(); // TFT液晶初始化
  usart1_config(setups.brUART);
  usart2_config(setups.brDUT); // DUT
  usart3_config(setups.brUSB);
  uart4_config(115200); // DUT2 setups.brDUT
  SPI2_Config(); // SPI2 转网口
  SPI3_Config(); // SPI3 扩展串口4个
  can_config(); // CAN 配置
  CH9434_Init(); // CH9434 初始化
  BuzzerIOconfig(); //蜂鸣器IO配置
  set_w5500_netinfo(); //设置W5500以太网模块
  bsp_Init();
  //	configWDT(2500);	//1.6ms*x

  //	txCAN1("123456789",9);

  {
    time_wheel_init(&tw); // 初始化时间轮
    add_timer(&tw, 25, 25, Task_25ms, NULL); // 添加25ms定时器
  }

  while (1)
  {
    CH9434Polling(); // CH9434 轮询
    InputIOScan(); // 按键、开关、旋钮轮询
    KeyCallback(); // 按键回调函数
    ethernet_tcp_server(); // TCP服务器
    rxCommandDispose(pUART); // UART1
    rxCommandDispose(pUSB); // UART3
    rxCommandDispose(pEther); // ETH UART4
    DisplayUARTHMI(); // ParameterSetup(); 通过UART-HMI显示参数设置
    SwitchMessage(); // 切换消息
    BuzPoll(); // 蜂鸣器轮询
    WorkStateLED(); // 工作状态LED
    //		wdt_counter_reload();

    time_wheel_execute(&tw); // 执行时间轮任务
  }
}
