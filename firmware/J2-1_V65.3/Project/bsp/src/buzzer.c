/*
*********************************************************************************************************
*
*	模块名称 : 蜂鸣器驱动模块
*	文件名称 : bsp_beep.c
*	版    本 : V1.0
*	说    明 : 驱动蜂鸣器. STM8S 的 PD4 引脚具有BEEP功能。 调用BEEP_Start()函数可以按指定鸣叫时长和
*		   鸣叫次数进行鸣叫，不占用主程序执行时间，无等待。后台自动控制蜂鸣器的启动和停止。
*
*	修改记录 :
*		
*
*	Copyright (C), 
*
*********************************************************************************************************
*/

#include "buzzer.h"


BuzStruct buzz,*pBuz=&buzz;


/***************************************************************************
;** 函数名称:  BeepInitHard
;** 功能描述:  
;** 输入参数:            
;** 返 回 值: 
;** 全局变量: 
;** 调用模块: 
;** 作　  者:   M-L-A
;** 日　  期:   2018-10-1
;** 修改原因：
;** 说    明:  
;***************************************************************************/
void BuzzerIOconfig(void)
{	
	gpio_init_type gpio_init_struct;
	
	crm_periph_clock_enable(CRM_GPIOC_PERIPH_CLOCK, TRUE);
		
	gpio_init_struct.gpio_pins = GPIO_PINS_9;//
	gpio_init_struct.gpio_mode = GPIO_MODE_OUTPUT;
	gpio_init_struct.gpio_pull = GPIO_PULL_UP;
	gpio_init_struct.gpio_out_type = GPIO_OUTPUT_PUSH_PULL;
	gpio_init_struct.gpio_drive_strength = GPIO_DRIVE_STRENGTH_STRONGER;
	gpio_init(GPIOC, &gpio_init_struct);
	
	BUZ_DISABLE();

}

/***************************************************************************
;** 函数名称:  BuzStart
;** 功能描述:  
;** 输入参数: BeepTime : 蜂鸣时间，单位10ms; 0 表示不鸣叫
              StopTime : 停止时间，单位10ms; 0 表示持续鸣叫
              cycle : 鸣叫次数， -1 表示持续鸣叫 

;** 返 回 值: 
;** 全局变量: 
;** 调用模块: 
;** 作　  者:   M-L-A
;** 日　  期:   2018-10-1
;** 修改原因：
;** 说    明:  
;***************************************************************************/
void BuzStart(uint16_t BeepTime, uint16_t StopTime, int8_t cycle)
{
	if(BeepTime>0)
	{
		buzz.enable=true;
		buzz.state=false;
		buzz.start = BeepTime;
		buzz.stop = StopTime;
		buzz.cycle = cycle;
		buzz.time = BeepTime;		
		BUZ_ENABLE();			/* 开始发声 */	
	}
}

/***************************************************************************
;** 函数名称:  BuzStop
;** 功能描述:  停止蜂鸣音。
;** 输入参数: 
;** 返 回 值: 
;** 全局变量: 
;** 调用模块: 
;** 作　  者:   M-L-A
;** 日　  期:   2018-10-1
;** 修改原因：
;** 说    明:  
;***************************************************************************/
void BuzStop(void)
{
	buzz.state = false;
	buzz.enable = false;
	buzz.start = 0;
	buzz.stop = 0;
	buzz.cycle = 0;
	buzz.time = 0;
	BUZ_DISABLE();	/* 必须在清控制标志后再停止发声，避免停止后在中断中又开启 */
	
}

/***************************************************************************
;** 函数名称:  	
;** 功能描述:  	每隔10ms调用1次该函数，用于控制蜂鸣器发声。
;** 输入参数: 	
;** 返 回 值: 	无
;** 优 先 级：  
;** 全局变量: 
;** 调用模块: 
;** 作　  者:   M-L-A
;** 日　  期:   2013-3-18
;** 修改原因：
;** 说    明:    修改于2013-5-3
;***************************************************************************/
void BuzPoll(void)
{
	if(buzz.enable==true)
	{
		if(buzz.time<=0)
		{
			if(buzz.state!=true)
			{
				if(buzz.cycle>0)
				{
					buzz.cycle--;
					if(buzz.cycle<=0)
					{BuzStop();}
					else if(buzz.stop>0)
					{
						buzz.state=true;
						buzz.time=buzz.stop;
						BUZ_DISABLE();		/* 停止发声 */						
					}	
				}
				else if(buzz.cycle==-1)	// 表示持续鸣叫 
				{
					if(buzz.stop>0)
					{
						buzz.state=true;
						buzz.time=buzz.stop;
						BUZ_DISABLE();		/* 停止发声 */						
					}
				}
			}
			else
			{
				buzz.state=false;
				if(buzz.start>0)
				{
					buzz.time=buzz.start;
					BUZ_ENABLE();			/* 开始发声 */
				}
				else
				{BuzStop();}
			}							
		}	
	}
}



/***************************** (END OF FILE) *********************************/




