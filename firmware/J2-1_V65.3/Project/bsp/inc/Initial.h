
#ifndef  __INITIAL__
#define  __INITIAL__


#include "project.h"
//--------------------------------------------------------------------------
#define ON          	1
#define OFF         	0

#define VOA_NUM   	    5	//


#define LEVEL_NUM   	128	//电平数量
#define REFERENCE	 	10.000	


//--------------------------------------------------------------------------
typedef struct{	
	uint8_t 	fInitial;	//flash initial
	uint8_t  	IDN[128];	//产品信息128 字节
//	uint8_t  	PN[17];	    //产品编号16 字节
//	uint8_t  	SN[17];	    //产品序列号16 字节	
	uint8_t		ID;			//encoder 
	uint8_t     baud;		//波特率下标
	uint8_t     cp;			//VOA器件个数 component
	uint8_t     nwl;		//波长个数
	uint16_t	mpn;		//Maximum point number
	uint8_t     ss;		    //save state
	uint16_t    wl;			//wave length
//	int16_t     k[4];		//设定通道比例 保留4位小数点
//	uint16_t    ol[4];		//offset level voltage
//	uint32_t    BaudRate;   //UART1波特率
	uint8_t     ver[24];	//version
	
}ParameterSturct;

extern ParameterSturct  params;
//--------------------------------------------------------------------------
typedef struct{	
	
	uint16_t	vo;	//DAC电压
	uint16_t	wl;	//设置波长
	float		db;	//衰减
	
	uint8_t     cp;	//器件序号 block(0~511)
	uint8_t 	wp;	//波长放在哪个表格（0~15） sector
	uint16_t    sq;	//在表格的序号(1~400)
	
}VOAsturct;

extern VOAsturct  slvd,sVOA[];

//-------------------------------------------------------------------------
void SysTickConfigure(void);
void configWDT(uint16_t d);
void epramInitialize(void);
void bsp_Init(void);
double ffp(double fm, int leng);
char ftoa(double fv,unsigned char decimals,char *str);
char itoa(int tv,char *str);
char itoa_32(int tv,char *str);
void sformat(char *o,char *s, ...);
void ReadParamet(uint32_t d,ParameterSturct *par);
void SaveParamet(uint32_t d,ParameterSturct *par);



#endif





