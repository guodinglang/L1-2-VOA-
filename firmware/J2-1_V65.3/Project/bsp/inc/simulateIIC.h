
#ifndef __IICBUSDRIVE_H
#define __IICBUSDRIVE_H

#include "project.h"

//-------------------------------------------------------------------------
//#define SimulateIIC0  1	
#define		AT24CXXX	8
#define		IIC0		0

//-------------------------------------------------------------------------
#define GPIO_EERAM_SCL    GPIO_PINS_14
#define GPIO_EERAM_SDA    GPIO_PINS_15
#define GPIOSDA           GPIOC
#define GPIOSCL           GPIOC

//-------------------------------------------------------------------------
//#define I2C_CW    0xA0	   //写
//#define I2C_CR    0xA1	   //读

//====================================================================================
#define  INITALADD				0 //EEPROM初始化

//预留1~9地址
#define  VOA_ADD_MCH            10	 //占1字节 最大通道
#define	 VOA_ADD_BR				11	 //串口波特率 占1字节
#define  VOA_ADD_VER            12	 //占24字节 
#define	 VOA_ADD_IDN			36	 //占128字节
//#define	 VOA_ADD_PN			    100  //占16字节
//#define	 VOA_ADD_SN			    116	 //占16字节 
#define	 VOA_ADD_SAVE			164	 //占1字节
#define	 VOA_ADD_NWL			165	 //占1字节
#define	 VOA_ADD_MPN			166	 //占2字节
#define	 VOA_ADD_ID			    168	 //占1字节
#define	 VOA_ADD_SS			    169	 //占1字节
#define	 VOA_ADD_WL			    170	 //占2字节

//#define	 ETHER_ADD_GW			25	//占4字节 // 网关  
//#define	 ETHER_ADD_DNS			29	//占4字节 // DNS服务器地址
//#define	 ETHER_ADD_RIP			33	//占4字节 // remote IP远程IP地址
//#define	 ETHER_ADD_PORT			37	//占2字节 // 端口号
//#define	 ETHER_ADD_VER			39	//占2字节 // 软件版本号



//#define  BUZZERADD				5  //71 72

//#define  IIC_INDEX_N(n)         (((n)/2)+1)     //n:0~15
//#define  IIC_INDEX_M(n)         ((33-(n))/2)	//n:0~15

//#define  OPERATEAddO(a,b)       (((a)+1)*61)+((b)*2-1) 	 //奇数 not used

//#define   SNADD				  66	//+12=
//#define	  SN_DISCERN		  79	//+12=
//#define	  MTYPE_ADD		      92	//+12=
////====================================================================================
//#define	  MEM_NUM_ADD         105	    	//20个数据个数 
//#define	  MEM_I2C_ADD(a)	  ((a)*4+106)	//20*4+105=185 个数据地址


////====================================================================================
//#define MEMAX      20 	//峰值最大存储个数



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
 
char IIC_Write_Data(unsigned int RomAddress,unsigned char data);
unsigned char IIC_Read_Data(unsigned int RomAddress);

void IIC_Write_2Byte(unsigned int RomAddress, uint16_t udata);
uint16_t IIC_Read_2Byte(unsigned int RomAddress);

void IIC_Write_4Byte(unsigned int RomAddress,unsigned int udata);
unsigned int IIC_Read_4Byte(unsigned int RomAddress);

char IIC_Write_double(unsigned int RomAddress,double udata);
double IIC_Read_double(unsigned int RomAddress);

void IIC_Write_Nbyte(unsigned char *pc,unsigned int Addr,unsigned char number);
void IIC_Read_Nbyte(unsigned char *pc,unsigned int Addr,unsigned char number);
void IIC_Read_Ntwobyte(uint16_t *pc,unsigned int Addr,unsigned char number);

void Clr_IIC_SDA(void);
void Set_IIC_SDA(void);
void Clr_IIC_SCL(void);
void Set_IIC_SCL(void);
//uint8_t READ_SDA(void);







#endif
