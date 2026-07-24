
#ifndef  __INITIAL__
#define  __INITIAL__


#include "project.h"
//--------------------------------------------------------------------------
#define ON          	1
#define OFF         	0

#define VOA_NUM   	    5	//


#define LEVEL_NUM   	128	//电平数量
#define REFERENCE	 	10.000	
#define SEGMENT_NUM		1210	//分段校准数量,0-117000微步，每段1000


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
    int32_t     db[SEGMENT_NUM];		//校准点 DB衰减值
	uint32_t    lc[SEGMENT_NUM];		//校准点 马达位置
//	uint32_t    BaudRate;   //UART1波特率
	uint8_t     ver[24];	//version
	
}ParameterSturct;

extern ParameterSturct  params;
//--------------------------------------------------------------------------
typedef struct{	
	
	uint32_t	vo;	//DAC电压
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
void W25Q128_ParametInit(void);
void M_DIAG_exti_config(void);
void D_EZ_exti_config(void);
void M_ORG_exti_config(void);
void Time3_Init(void);

#endif





