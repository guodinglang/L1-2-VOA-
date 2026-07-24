

#ifndef  __FUNCTION_H_
#define  __FUNCTION_H_
  
#include "project.h"  

//--------------------------------------------------------------------------
#define SLED     (GPIOC->odt ^= GPIO_PINS_13)


//--------------------------------------------------------------------------
//typedef struct{
////	uint8_t  step;			//
////	uint16_t  rch;			//记录通道
////	uint8_t   cn;			//count
////	uint8_t   len;			//长度
////	char      buf[64];		//数据保存
////	uint16_t  max;			//最大通道
////	uint8_t   index[16];	//index
//	uint16_t  wl[16];		//wave length
//	float     db[32];	    //
////	uint8_t   ocr[32];	    //output channle record
////	uint8_t   sv[32];	    //setupt valuev
////	uint16_t  toc;			//time out count
////	uint32_t  time;

//}SwitchStruct;

//extern SwitchStruct  swMes;
//--------------------------------------------------------------------------
//typedef struct{
//	uint8_t  	lock;		//通道锁
//	uint8_t		scan;		//通道切换
//	uint32_t    Tgap;		//扫描间隔
//	uint16_t    sch;		//起始通道
//	uint16_t	ech;		//结束通道
//	uint8_t     language;	//语言
//	uint32_t    brUART; 	//UART波特率
//	uint32_t    brUSB; 	    //UART波特率
//	uint32_t    brDUT; 		//DUT波特率
//	uint8_t     speak;		//蜂鸣器
//	uint8_t  	step;		//
//	uint8_t  	reel;		//选项
//	uint8_t     page;		//菜单页
//	uint8_t  	digit;		//
//	uint8_t  	index;		//	
//	uint8_t  	refresh;	//
//	
//}SetupStruct;

//extern SetupStruct    setups;
//--------------------------------------------------------------------------
void WorkStateLED(void);
void SwitchMessage(void);
uint32_t SelectBaudrate(uint32_t br,int s);
uint32_t IndexToBaudrate(uint8_t br);
uint8_t BaudrateToIndex(uint32_t br);
int8_t getEncoder(void);



#endif




