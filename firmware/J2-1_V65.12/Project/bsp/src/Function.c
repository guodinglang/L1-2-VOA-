
#include "Function.h"
//#include "spiFlash.h"

//--------------------------------------------------------------------------
//SwitchStruct   swMes;
//SetupStruct    setups;


/***************************************************************************
;** 函数名称:  	WorkStateLED
;** 功能描述:  	
;** 输入参数: 	
;** 返 回 值: 	
;** 优 先 级：  
;** 全局变量: 
;** 调用模块: 
;** 作　  者:   M-L-A
;** 日　  期:   2022-5-26
;** 修改原因：
;***************************************************************************/
void WorkStateLED(void)
{
	static uint32_t count;
	
	if(count > 200000)
	{SLED;count=0;}
	else
	{count++;}
	
}

/***************************************************************************
;** 函数名称:  	getEncoder
;** 功能描述:  	
;** 输入参数: 	
;** 返 回 值: 	
;** 优 先 级：  
;** 全局变量: 
;** 调用模块: 
;** 作　  者:   M-L-A
;** 日　  期:   2024-2-26
;** 修改原因：
;***************************************************************************/
int8_t getEncoder(void)
{
	int8_t i,r,t,c=0;
	
	for(i=0;i<10;i++)
	{
		r = (0x0F && GPIOA->idt);	
		if(t != r)
		{t = r;	c = 0;}
		else
		{c++;}
		delay_ms(1);
	}
	
	if(c > 8)
	{
		for(t=0,i=0;i<4;i++)
		{
			t <<= 1;
			t |= (0x01&(r>>i));
		}
		t=~t;
		t &= 0xf;
	}
	else
	{t = -1;}
	
	return t;
}


/***************************************************************************
;** 函数名称:  void SwitchMessage(void) 
;** 功能描述:  switch message 
;** 输入参数: 
;** 返 回 值: 
;** 全局变量: 
;** 调用模块: 
;** 作　  者:  M-L-A 
;** 日　  期:  2022-2-14
;** 修改原因：
;** 说    明: 
;***************************************************************************/
void SwitchMessage(void)
{		
	
	
}

/***************************************************************************
;** 函数名称:  void BaudrateToIndex(void) 
;** 功能描述:  Baudrate To Index
;** 输入参数: 
;** 返 回 值: 
;** 全局变量: 
;** 调用模块: 
;** 作　  者:  M-L-A 
;** 日　  期:  2022-2-14
;** 修改原因：
;** 说    明: 
;***************************************************************************/
uint8_t BaudrateToIndex(uint32_t br)
{
	uint8_t r=0;
	
	switch(br)
	{
		case 0:break;
		case 2400:r=1;break;
		case 4800:r=2;break;
		case 9600:r=3;break;
		case 14400:r=4;break;
		case 19200:r=5;break;
		case 38400:r=6;break;
		case 56000:r=7;break;
		case 57600:r=8;break;
		case 115200:r=9;break;
		case 128000:r=10;break;
		case 230400:r=11;break;
		case 256000:r=12;break;
		case 460800:r=13;break;
		case 500000:r=14;break;
		case 512000:r=15;break;
		case 600000:r=16;break;
		case 750000:r=17;break;
		case 921600:r=18;break;
		case 1000000:r=19;break;
		case 1500000:r=20;break;
		case 2000000:r=21;break;
	}
	
	return r;
}
/***************************************************************************
;** 函数名称:  void IndexToBaudrate(void) 
;** 功能描述:  IndexToBaudrate
;** 输入参数: 
;** 返 回 值: 
;** 全局变量: 
;** 调用模块: 
;** 作　  者:  M-L-A 
;** 日　  期:  2022-2-14
;** 修改原因：
;** 说    明: 
;***************************************************************************/
uint32_t IndexToBaudrate(uint8_t br)
{
	uint32_t r=0;
	
	switch(br)
	{
		case 0:break;
		case 1:r=2400;break;
		case 2:r=4800;break;
		case 3:r=9600;break;
		case 4:r=14400;break;
		case 5:r=19200;break;
		case 6:r=38400;break;
		case 7:r=56000;break;
		case 8:r=57600;break;
		case 9:r=115200;break;
		case 10:r=128000;break;
		case 11:r=230400;break;
		case 12:r=256000;break;
		case 13:r=460800;break;
		case 14:r=500000;break;
		case 15:r=512000;break;
		case 16:r=600000;break;
		case 17:r=750000;break;
		case 18:r=921600;break;
		case 19:r=1000000;break;
		case 20:r=1500000;break;
		case 21:r=2000000;break;
	}
	
	return r;
}
/***************************************************************************
;** 函数名称:  void SelectBaudrate(void) 
;** 功能描述:  SelectBaudrate
;** 输入参数: 
;** 返 回 值: 
;** 全局变量: 
;** 调用模块: 
;** 作　  者:  M-L-A 
;** 日　  期:  2022-2-14
;** 修改原因：
;** 说    明: 
;***************************************************************************/
uint32_t SelectBaudrate(uint32_t br,int s)
{
	int i=0;
	uint32_t r=0;
	
	switch(br)
	{
		case 0:break;
		case 2400:i=1;break;
		case 4800:i=2;break;
		case 9600:i=3;break;
		case 14400:i=4;break;
		case 19200:i=5;break;
		case 38400:i=6;break;
		case 56000:i=7;break;
		case 57600:i=8;break;
		case 115200:i=9;break;
		case 128000:i=10;break;
		case 230400:i=11;break;
		case 256000:i=12;break;
		case 460800:i=13;break;
		case 500000:i=14;break;
		case 512000:i=15;break;
		case 600000:i=16;break;
		case 750000:i=17;break;
		case 921600:i=18;break;
		case 1000000:i=19;break;
		case 1500000:i=20;break;
		case 2000000:i=21;break;
		
		default:i=-1;break;
	}
	
	i=i+s;
	if(i<0)
	{i=0;}
	
	switch(i)
	{
		case 0:break;
		case 1:r=2400;break;
		case 2:r=4800;break;
		case 3:r=9600;break;
		case 4:r=14400;break;
		case 5:r=19200;break;
		case 6:r=38400;break;
		case 7:r=56000;break;
		case 8:r=57600;break;
		case 9:r=115200;break;
		case 10:r=128000;break;
		case 11:r=230400;break;
		case 12:r=256000;break;
		case 13:r=460800;break;
		case 14:r=500000;break;
		case 15:r=512000;break;
		case 16:r=600000;break;
		case 17:r=750000;break;
		case 18:r=921600;break;
		case 19:r=1000000;break;
		case 20:r=1500000;break;
		case 21:r=2000000;break;
		
		default:r=br;break;
	}	
	
	return r;
}





