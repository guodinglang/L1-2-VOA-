
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


//#include "at32f415_clock.h"
#include "project.h"
#include "main.h"
#include "spiFlash.h"


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
//	swIIC_config();
	Time3_Init();          // PWM for MOTOR  M_STEP
	W25Q128_SPI2Config();         // 配置SPI2 连接W25Q128
	W25Q128_ParametInit();        // 从W25Q128读取参数到RAM
//	SPI1_Config();	
//	epramInitialize();
	usart1_config(IndexToBaudrate(params.baud));
	InterADconfig();
	bsp_Init();	
//	configWDT(2500);	//1.6ms*x
	/* 初始化TMC2209 */
    tmc2209_init();               // 初始化TMC2209步进电机驱动器
    tmc2209_stallguard_config();  // 配置TMC2209 stall guard

	while(1)
	{ 	
		rxCommand();
		AcquisitMCP9700A();
		WorkStateLED();
//		wdt_counter_reload();；
	}
}



