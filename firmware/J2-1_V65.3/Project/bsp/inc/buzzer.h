/*
*********************************************************************************************************
*
*	模块名称 : 蜂鸣器模块
*	文件名称 : bsp_beep.h
*	版    本 : V1.0
*	说    明 : 头文件
*	修改记录 :
*		版本号  日期        作者    说明
*		v1.0    2012-10-12 armfly     首版
*
*********************************************************************************************************
*/

#ifndef __BUZZER_H__
#define __BUZZER_H__

#include "project.h" 

//--------------------------------------------------------------------------
//#define BUZZER(n)  n>0? (GPIOC->scr = GPIO_PINS_9):(GPIOC->clr = GPIO_PINS_9) 

#define BUZ_ENABLE()	(GPIOC->scr = GPIO_PINS_9)		/* 使能蜂鸣器鸣叫 */
#define BUZ_DISABLE()	(GPIOC->clr = GPIO_PINS_9) 	   /* 禁止蜂鸣器鸣叫 */

//===========================================================================
//typedef union 
//{
//	uint8_t regis;
//	struct 
//	{
//		unsigned char b0:1;
//		unsigned char b1:1;
//		unsigned char b2:1;
//		unsigned char b3:1;
//		unsigned char b4:1;
//		unsigned char b5:1;
//		unsigned char b6:1;
//		unsigned char b7:1;	
//	}bit;
//}BitPosition;

//--------------------------------------------------------------------------
typedef struct{
	bool         state;
	bool      	 enable;
	uint16_t  	 start;
	uint16_t  	 stop;
	int8_t       cycle;
	uint16_t     time;	
}BuzStruct;

extern BuzStruct *pBuz; /* 定义蜂鸣器全局结构体变量 */
//===========================================================================
/* 供外部调用的函数声明 */
void BuzzerIOconfig(void);
void BuzStart(uint16_t BeepTime, uint16_t StopTime, int8_t cycle);
void BuzStop(void);
void BuzPoll(void);



#endif



