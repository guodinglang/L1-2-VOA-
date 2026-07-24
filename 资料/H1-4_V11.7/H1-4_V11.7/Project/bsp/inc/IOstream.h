/*
 *********************************************************************************************************
 *
 *	模块名称 :
 *	文件名称 :
 *	版    本 : V1.0
 *	说    明 : 头文件
 *
 *********************************************************************************************************
 */
#ifndef __IOSTREAM_H__
#define __IOSTREAM_H__

#include "project.h"

//--------------------------------------------------------------------------
#define RESETTINGS 72 //'r'=72

#define KEY_UP_H 10
#define KEY_UP_L 11

#define KEY_DOWN_H 20
#define KEY_DOWN_L 21

#define KEY_ENTER_H 30
#define KEY_ENTER_L 31

#define KEY_ESC_H 40
#define KEY_ESC_L 41

#define KEY_ENTER_UP_H 50
#define KEY_ENTER_UP_L 51

#define KEY_ENTER_DOWN_H 60
#define KEY_ENTER_DOWN_L 61

//--------------------------------------------------------------------------
#define KEY1 (GPIO_PINS_8 & GPIOC->idt)	 //
#define KEY2 (GPIO_PINS_7 & GPIOC->idt)	 //
#define KEY3 (GPIO_PINS_6 & GPIOC->idt)	 //
#define KEY4 (GPIO_PINS_13 & GPIOD->idt) //

#define DUT_POWER(n) (n) > 0 ? (GPIOE->scr = GPIO_PINS_3) : (GPIOE->clr = GPIO_PINS_3) //

#define DUT_D0(n) (n) > 0 ? (GPIOE->scr = GPIO_PINS_13) : (GPIOE->clr = GPIO_PINS_13)	 //
#define DUT_D1(n) (n) > 0 ? (GPIOA->scr = GPIO_PINS_7) : (GPIOA->clr = GPIO_PINS_7)		 //
#define DUT_D2(n) (n) > 0 ? (GPIOC->scr = GPIO_PINS_5) : (GPIOC->clr = GPIO_PINS_5)		 //
#define DUT_D3(n) (n) > 0 ? (GPIOB->scr = GPIO_PINS_1) : (GPIOB->clr = GPIO_PINS_1)		 //
#define DUT_D4(n) (n) > 0 ? (GPIOB->scr = GPIO_PINS_0) : (GPIOB->clr = GPIO_PINS_0)		 //
#define DUT_D5(n) (n) > 0 ? (GPIOE->scr = GPIO_PINS_12) : (GPIOE->clr = GPIO_PINS_12)	 //
#define DUT_D6(n) (n) > 0 ? (GPIOE->scr = GPIO_PINS_11) : (GPIOE->clr = GPIO_PINS_11)	 //
#define DUT_D7(n) (n) > 0 ? (GPIOB->scr = GPIO_PINS_2) : (GPIOB->clr = GPIO_PINS_2)		 //
#define DUT_RESET(n) (n) > 0 ? (GPIOD->scr = GPIO_PINS_10) : (GPIOD->clr = GPIO_PINS_10) //
#define DUT_STROBE(n) (n) > 0 ? (GPIOD->scr = GPIO_PINS_9) : (GPIOD->clr = GPIO_PINS_9)	 //

#define DUT_BUSY (GPIO_PINS_14 & GPIOE->idt)  //
#define DUT_ALARM (GPIO_PINS_15 & GPIOE->idt) //

//--------------------------------------------------------------------------
typedef union
{
	unsigned short int regis; // 16 bit
	struct
	{
		unsigned short int b0 : 1;
		unsigned short int b1 : 1;
		unsigned short int b2 : 1;
		unsigned short int b3 : 1;
		unsigned short int b4 : 1;
		unsigned short int b5 : 1;
		unsigned short int b6 : 1;
		unsigned short int b7 : 1;
		unsigned short int b8 : 1;
		unsigned short int b9 : 1;
		unsigned short int b10 : 1;
		unsigned short int b11 : 1;
		unsigned short int b12 : 1;
		unsigned short int b13 : 1;
		unsigned short int b14 : 1;
		unsigned short int b15 : 1;
	} bit;
} BitStructure16;

extern BitStructure16 erCode; //
//-------------------------------------------------------------------------------
typedef struct
{
	unsigned int cn[8];
	unsigned int time; // time
	unsigned char value;
	union
	{
		unsigned short fb;
		struct
		{
			unsigned short b0 : 1; // ESC
			unsigned short b1 : 1; // ENTER
			unsigned short b2 : 1; // DOWN
			unsigned short b3 : 1; // UP
			unsigned short b4 : 1;
			unsigned short b5 : 1;
			unsigned short b6 : 1;
			unsigned short b7 : 1;

			unsigned short esc : 1;	  // ESC
			unsigned short enter : 1; // ENTER
			unsigned short down : 1;  // DOWN
			unsigned short up : 1;	  // UP
			unsigned short b12 : 1;
			unsigned short b13 : 1;
			unsigned short b14 : 1;
			unsigned short b15 : 1;

		} b;
	} f;
} ButtonManage;

extern ButtonManage *pkey;
//-------------------------------------------------------------------------------

void ioConfig(void);
void BatteryConfig(void);
void InputIOScan(void);
void KeyCallback(void);
void exint_line15_config(void);

#endif
