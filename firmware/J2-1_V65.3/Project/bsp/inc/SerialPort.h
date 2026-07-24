#ifndef   __SERIALPORT_H__
#define  __SERIALPORT_H__

#include "project.h"

//#include "stdint.h"
//#include "stm32f10x.h"

//========================================================================
#define	RX_MAX_FIFO     128
//#define	RESTR           32
//#define print1(n)    printx(USART1,n)
//#define printf1(n)   printfx(USART1,n)
//#define sprintf1(n)  sprintfx(USART1,n)

//#define print2(n)    printx(USART2,n)
//#define printf2(n)   printfx(USART2,n)
//#define sprintf2(n)  sprintfx(USART2,n)

//#define print3(n)    printx(USART3,n)
//#define printf3(n)   printfx(USART3,n)
//#define sprintf3(n)  sprintfx(USART3,n)

//#define print4(n)    printx(UART4,n)
//#define printf4(n)   printfx(UART4,n)
//#define sprintf4(n)  sprintfx(UART4,n)


//========================================================================
typedef struct{
	bool                feelback;
//	unsigned char       send;		//发送使能
	unsigned char       rxFIFO[RX_MAX_FIFO];
	unsigned char       len;   		//接收总长度
	unsigned char       rxn;   		//单次接收个数	
	unsigned char       reTx; 		//返回字符位置
	uint16_t            TimeOut;	//超时
	
}rxStructure;

extern rxStructure   *tPort,*pUART,*pCAN1;//,*pDUT,*pUSB,*pEther,*pDUT2;
//========================================================================





//========================================================================
void usart1_config(uint32_t baud_rate);
void usart2_config(uint32_t baud_rate);
void usart3_config(uint32_t baud_rate);
void uart4_config(uint32_t baud_rate);
void printx(uint16_t ch);
void printfx(char *st);
void sprintfx(char *s, ...);




#endif




