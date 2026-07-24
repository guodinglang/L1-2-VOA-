

#include "GP8211S.h"


/***************************************************************************
;** 函数名称:  	IIC_WriteGP8403
;** 功能描述:   
;** 输入参数: 	chip--(0,1)奇数chip2,偶数chip1;
;** 返 回 值: 	
;** 优 先 级:  
;** 全局变量: 
;** 调用模块: 
;** 作　  者:   M-L-A
;** 日　  期:   2017-12-27
;** 修改原因：
;** 说    明:    
;***************************************************************************/ 
uint8_t IIC_WriteGP8211S(uint16_t *wd,uint8_t chip)
{ 
	uint8_t r=0, i,ErrCount,bd[4]={0};
		
	IICx = chip;
	bd[0] = 0xB0; 		//写指令
	bd[1] = DAC_CH_A; 	//通道1
	bd[2] = wd[0]&0xff;
	bd[3] = (wd[0]>>8)&0x7f;
	
	IIC_Start();
	for(i=0;i<4;i++)
	{
		ErrCount=3;
		while(ErrCount>0)
		{
			IIC_WRITE_BYTE(bd[i]);
			if(IIC_Recelve_Ack()!=0)  		//判断ACK
			{
				ErrCount--;
				if(ErrCount<=0)
				{
					//ALARM(1);
					r=1;
				}
			}
			else 
			{ErrCount=0;}
		}		
	}
	IIC_Stop();

	return r;
	
}


/***************************************************************************
;** 函数名称:  	GP8403_Power
;** 功能描述:   
;** 输入参数: 	ov--5V(0x55);	ov--10V(0x77); chip--
;** 返 回 值: 	
;** 优 先 级:  
;** 全局变量: 
;** 调用模块: 
;** 作　  者:   M-L-A
;** 日　  期:   2022-5-31
;** 修改原因：
;** 说    明:    
;***************************************************************************/ 
uint8_t GP8211S_Power(uint8_t ov,uint8_t chip)
{ 
	uint8_t r=0;
	uint16_t i,ErrCount,bd[3]={0,0,0};
	
	IICx=chip;
	bd[0]=0xB0; 	//写指令
	bd[1]=DAC_POWER_ADD; //
	if(ov>5)
	{bd[2]=DAC_0_10V;}
	else
	{bd[2]=DAC_0_5V;}
	
	IIC_Start();
	for(i=0;i<3;i++)
	{
		ErrCount=3;
		while(ErrCount > 0)
		{
			IIC_WRITE_BYTE(bd[i]);
			if(IIC_Recelve_Ack() != 0) //判断ACK
			{
				ErrCount--;
				if(ErrCount <= 0)
				{
					//ALARM(1);
					r=1;
				}
			}
			else 
			{ErrCount=0;}
		}		
	}
	IIC_Stop();
	
	
	return r;
	
}











