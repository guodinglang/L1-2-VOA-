

#include "GP8403.h"


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
uint8_t IIC_WriteGP8403(uint16_t *wd, uint8_t num,uint8_t chip)
{ 
	uint8_t r=0, i,ErrCount,n=0,bd[8]={0};
		
	if(chip&0x01)
	{bd[0]=0xB2;}
	else
	{bd[0]=0xB0;} 	//写指令
	
	bd[1]=DAC_CH_A; //通道1可以连续写到通道2
	for(i=0;i<2;i++)
	{
		bd[2+i*2]=(wd[i]&0x000f)<<4;
		bd[3+i*2]=wd[i]>>4;
	}		
	if(num >= 2)
	{n=2+2*2;}
	else
	{n=2+2*1;}
	
	IIC_Start();
	for(i=0;i<n;i++)
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
					ALARM(1);
					r=1;
				}
			}
			else 
			{ErrCount=0;}
		}		
	}
	IIC_Stop();
	
#if AXLE_NUM == 4	//DAC2
	if(num > 2)
	{
		bd[0]=0xB2; 	//写指令
		bd[1]=DAC_CH_A; //通道1可以连续写到通道2
		for(i=0;i<2;i++)
		{
			bd[2+i*2]=(wd[2+i]&0x000f)<<4;
			bd[3+i*2]=wd[2+i]>>4;
		}
		
		if(num >= 3)
		{n=2+2*2;}
		else
		{n=2+2*1;}
		
		IICx=IIC0;
		IIC_Start();
		for(i=0;i<n;i++)
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
						ALARM(1);
						i=num;
					}
				}
				else 
				{ErrCount=0;}
			}		
		}
		IIC_Stop();
	}
#endif	

	return r;
	
}


/***************************************************************************
;** 函数名称:  	GP8403_Power
;** 功能描述:   
;** 输入参数: 	ov--5V(0x00);	ov--10V(0x11); chip--(0,1)奇数chip2,偶数chip1;
;** 返 回 值: 	
;** 优 先 级:  
;** 全局变量: 
;** 调用模块: 
;** 作　  者:   M-L-A
;** 日　  期:   2022-5-31
;** 修改原因：
;** 说    明:    
;***************************************************************************/ 
uint8_t GP8403_Power(uint8_t ov,uint8_t chip)
{ 
	uint8_t r=0;
	uint16_t i,ErrCount,bd[3]={0,0,0};
	
	if(chip & 0x01)
	{bd[0]=0xB2;} //奇数 chip2
	else
	{bd[0]=0xB0;} 	//写指令
	bd[1]=DAC_POWER_ADD; //
	bd[2]=ov;
	
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
					ALARM(1);
					r=1;
				}
			}
			else 
			{ErrCount=0;}
		}		
	}
	IIC_Stop();
	
#if AXLE_NUM == 4	//DAC2
	
	bd[0]=0xB2; 	//写指令
	iicWcmd = 0xB2;	//DAC2
	iicRcmd = 0xB3;
	
	IICx=IIC0;
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
					ALARM(1);
					i=4;
				}
			}
			else 
			{ErrCount=0;}
		}		
	}
	IIC_Stop();	
#endif
	
	return r;
	
}











