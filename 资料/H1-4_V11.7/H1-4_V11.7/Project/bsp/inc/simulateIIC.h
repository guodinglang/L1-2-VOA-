
#ifndef __IICBUSDRIVE_H
#define __IICBUSDRIVE_H

#include "project.h"

//-------------------------------------------------------------------------
#define SimulateIIC1 1
#define AT24CXXX 8
#define IIC0 0

//-------------------------------------------------------------------------
#define GPIO_EERAM_SCL GPIO_PINS_8
#define GPIO_EERAM_SDA GPIO_PINS_9
#define GPIOSDA GPIOB
#define GPIOSCL GPIOB

//-------------------------------------------------------------------------
// #define I2C_CW    0xA0	   //写
// #define I2C_CR    0xA1	   //读

//====================================================================================
#define INITALADD 0 // EEPROM初始化

// 预留1~9地址

#define ETHER_ADD_MAC 10  // 系数地址 占6字节
#define ETHER_ADD_IP 17   // 占4字节local IP本地IP地址
#define ETHER_ADD_SUB 21  // 占4字节 // 子网掩码
#define ETHER_ADD_GW 25   // 占4字节 // 网关
#define ETHER_ADD_DNS 29  // 占4字节 // DNS服务器地址
#define ETHER_ADD_RIP 33  // 占4字节 // remote IP远程IP地址
#define ETHER_ADD_PORT 37 // 占2字节 // 端口号
#define ETHER_ADD_VER 39  // 占2字节 // 软件版本号

#define LCD_ADD_BLK 60 // 占2字节

#define PRG_ADD_LOCK 62     // 占1字节
#define PRG_ADD_SCAN 63     // 占1字节
#define PRG_ADD_GAP 64      // 占8字节
#define PRG_ADD_SCH 72      // 占2字节
#define PRG_ADD_ECH 75      // 占2字节
#define PRG_ADD_LANGUAGE 77 // 占1字节
#define PRG_ADD_BR_UART 78  // 占8字节
#define PRG_ADD_BR_USB 86   // 占8字节
#define PRG_ADD_BR_DUT 94   // 占8字节
#define PRG_ADD_SPEAK 102   // 占1字节

// #define  MEMS_ADD_MAX           95	//占2字节

#define LCD_ADD_LOGO 103  // 占1字节
#define LCD_ADD_TITLE 104 // 占16字节

#define BOARD_ADD_D 120    // 1字节
#define BOARD_ADD_N 121    // 1字节
#define BOARD_ADD_T 122    // 2字节
#define PRG_ADD_CAN_ID 124 // 1字节
#define PRG_ADD_SBN 125    // 1字节

// #define  BUZZERADD				5  //71 72
// #define  PRGADD(a,b)       ((a)*12)+((b)*2+61)     //偶数//MAX 5*12+61=121
////#define  OPERATEAddO(a,b)       (((a)+1)*61)+((b)*2-1) 	 //奇数 not used

// #define   SNADD				  66	//+12=
// #define	  SN_DISCERN		  79	//+12=
// #define	  MTYPE_ADD		      92	//+12=
////====================================================================================
// #define	  MEM_NUM_ADD         105	    	//20个数据个数
// #define	  MEM_I2C_ADD(a)	  ((a)*4+106)	//20*4+105=185 个数据地址

////====================================================================================
// #define MEMAX      20 	//峰值最大存储个数

//====================================================================================
extern uint8_t IICx;
extern uint8_t iicWcmd;
extern uint8_t iicRcmd;

//====================================================================================
/**********************************************************************/
void swIIC_config(void);
void IIC_Start(void);
void IIC_Stop(void);

unsigned char IIC_Recelve_Ack(void);
void IIC_WRITE_BYTE(unsigned char txd);
unsigned char IIC_Read_Byte(unsigned char ack);

char IIC_Write_Data(unsigned int RomAddress, unsigned char data);
unsigned char IIC_Read_Data(unsigned int RomAddress);

void IIC_Write_2Byte(unsigned int RomAddress, uint16_t udata);
uint16_t IIC_Read_2Byte(unsigned int RomAddress);

void IIC_Write_4Byte(unsigned int RomAddress, unsigned int udata);
unsigned int IIC_Read_4Byte(unsigned int RomAddress);

char IIC_Write_double(unsigned int RomAddress, double udata);
double IIC_Read_double(unsigned int RomAddress);

void IIC_Write_Nbyte(unsigned char *pc, unsigned int Addr, unsigned char number);
void IIC_Read_Nbyte(unsigned char *pc, unsigned int Addr, unsigned char number);
void IIC_Read_Ntwobyte(uint16_t *pc, unsigned int Addr, unsigned char number);

void Clr_IIC_SDA(void);
void Set_IIC_SDA(void);
void Clr_IIC_SCL(void);
void Set_IIC_SCL(void);
// uint8_t READ_SDA(void);

#endif
