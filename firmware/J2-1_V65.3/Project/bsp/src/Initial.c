
/****************************************************************************************
*
*	模块名称 : BSP(Board Support Package)
*	文件名称 : 
*	版    本 : V0.1
*	说    明 : BSP 板级支持包(Board Support Package)
*	修改记录 :
*   版 本 号 :  
*   日    期 :     
*   作    者 :   
*	说    明 :
*
*****************************************************************************************/

#include "Initial.h"
#include "spiFlash.h"

//--------------------------------------------------------------------------
ParameterSturct  params;
VOAsturct  slvd,sVOA[VOA_NUM];
//LevelSturct  sLevel;	//


/***************************************************************************
;** 函数名称: 	SysTickConfigure
;** 功能描述:   SysTick Time Configure
;** 输入参数: 
;** 返 回 值: 
;** 全局变量: 
;** 调用模块: 
;** 作　  者:   M-L-A
;** 日　  期:  2022-5-26
;** 修改原因:
;** 说    明:  	
;***************************************************************************/
void SysTickConfigure(void)
{
  /* configure systick */
	systick_clock_source_config(SYSTICK_CLOCK_SOURCE_AHBCLK_NODIV);
//  SysTick->LOAD = (uint32_t)(system_core_clock / (1000U));
//  SysTick->VAL = 0x00;
//  SysTick->CTRL |= SysTick_CTRL_ENABLE_Msk ;
	SysTick_Config(system_core_clock / 1000U);	//1ms

}

/***************************************************************************
;** 函数名称: 	configWDT
;** 功能描述:   config WDT
;** 输入参数: 
;** 返 回 值: 
;** 全局变量: 
;** 调用模块: 
;** 作　  者:   M-L-A
;** 日　  期:  2022-5-26
;** 修改原因:
;** 说    明:  	
;***************************************************************************/
void configWDT(uint16_t d)
{
	/* reset from wdt */
	crm_flag_clear(CRM_WDT_RESET_FLAG);
	/* disable register write protection */
	wdt_register_write_enable(TRUE);

	/* set the wdt divider value */
	wdt_divider_set(WDT_CLK_DIV_32);	//0.8ms*d

	/* set reload value

	timeout = reload_value * (divider / lick_freq )    (s)

	lick_freq    = 40000 Hz
	divider      = 64		//1.6ms*d
	reload_value = d		//12bit=4095

	timeout = d * (64 / 40000 ) = max:6.552s = 6552ms
	*/
	wdt_reload_value_set(d - 1);

	/* reload wdt counter */
	wdt_counter_reload();

	/* enable wdt */
	wdt_enable();
	
}


/***************************************************************************
;** 函数名称: 
;** 功能描述:  取出EEPRAM 数据
;** 输入参数: 
;** 返 回 值: 
;** 全局变量: 
;** 调用模块: 
;** 作　  者:   M-L-A
;** 日　  期:  2013-4-17
;** 修改原因：
;** 说    明:  	AT24C256	  (65535 byte )
;***************************************************************************/
void epramInitialize(void)
{
#ifdef SimulateIIC0	
	
	IICx=IIC0; 
	if(0x65 != IIC_Read_Data(0))
	{			
		char str[25]={0};
		IIC_Write_Data(0,0x65);
		
		params.ID = 0;	//Encoder
		IIC_Write_Data(VOA_ADD_ID,params.ID);
		params.baud = 9;	//115200
		IIC_Write_Data(VOA_ADD_BR,params.baud);
		params.cp = 16;
		IIC_Write_Data(VOA_ADD_MCH,params.cp);
		params.nwl = 16;
		IIC_Write_Data(VOA_ADD_NWL,params.nwl);
		params.mpn = 100;
		IIC_Write_Data(VOA_ADD_MPN,params.mpn);
		memset(str,0,sizeof(str));
		memcpy(str,"PCB:J2-1,PRG:V65.1",18);
		IIC_Write_Nbyte((uint8_t *)str,VOA_ADD_VER,sizeof(str)-1);
		memset(params.IDN,0,25);
		memcpy(params.IDN,"VOA_5",6);
		IIC_Write_Nbyte(params.IDN,VOA_ADD_IDN,sizeof(params.IDN)-1);
//		memset(params.PN,0,17);
//		memcpy(params.PN,"PN:123456",9);
//		IIC_Write_Nbyte(params.PN,VOA_ADD_PN,sizeof(params.PN)-1);
//		memset(params.SN,0,17);
//		memcpy(params.SN,"SN:123456",9);
//		IIC_Write_Nbyte(params.SN,VOA_ADD_SN,sizeof(params.SN)-1);
		
		params.ss = 0;	//not save
		IIC_Write_Data(VOA_ADD_SS,params.ss);
		
	}
	
	params.ID = IIC_Read_Data(VOA_ADD_ID);
	params.baud = IIC_Read_Data(VOA_ADD_BR);
	params.cp	= IIC_Read_Data(VOA_ADD_MCH);
	params.nwl = IIC_Read_Data(VOA_ADD_NWL);
	params.mpn = IIC_Read_2Byte(VOA_ADD_MPN);
	params.ss = IIC_Read_Data(VOA_ADD_SS);
	IIC_Read_Nbyte(params.IDN,VOA_ADD_IDN,sizeof(params.IDN)-1);

	
	
#else
	
	spiflash_wait_busy();
	spi_flash_read(&params.fInitial,FLASH_SECTION_FACTORY,1);
	if(0x53 != params.fInitial)
	{
		params.fInitial=0x53;	//标记初始化
		
		params.ID = 0;	//Encoder
		params.baud = 9;	//115200
		params.cp = 5;	//器件
		params.nwl = 16; //波长
		params.mpn = 400;	//点数
		params.ss = 0;
		params.wl = 1550;
		memset(params.IDN,0,sizeof(params.IDN));
		memcpy(params.IDN,"VOA_5",6);
		
		memset(params.ver,0,sizeof(params.ver));
		memcpy(params.ver,"PCB:J2-1,PRG:V65.3",18);
		
		SaveParamet(FLASH_SECTION_FACTORY,&params);
		SaveParamet(FLASH_SECTION_PARAMETER,&params);
	}
	
	ReadParamet(FLASH_SECTION_PARAMETER,&params);
	
	if(!params.baud)
	{params.baud=9;}
	if(params.ss >=255)
	{params.ss = 0;}
	
	
#endif	

	
}

/***************************************************************************
;** 函数名称: 
;** 功能描述:  硬件的初始化
;** 输入参数: 
;** 返 回 值: 
;** 全局变量: 
;** 调用模块: 
;** 作　  者:   M-L-A
;** 日　  期:  2013-3-17
;** 修改原因:
;** 说    明:  
;***************************************************************************/
void bsp_Init(void)
{	
	uint8_t i;
	uint16_t c,tar[2]={0,0};
	
	//tPort = 0;	//
	DAC_POWER(1); 	//DAC POWER ON
	memset(pUART,0,sizeof(rxStructure));
	delay_ms(300);
//	spi_flash_mode_4byte();	//4byte地址
	
	c=0;
	for(i=0;i<params.cp;i++)
	{
		c += GP8211S_Power(10,i+1);
		delay_ms(10);
		c += IIC_WriteGP8211S(tar,i+1);
		delay_ms(10);
	}
	
	if(params.ss ==1)
	{//已保存，上电恢复状态
		stateVOA('r');
		for(i=0;i<params.cp;i++)
		{
			IIC_WriteGP8211S(&sVOA[i].vo,i+1);
			delay_ms(10);
		}
	}
	else
	{
		ParameterSturct tpar;//工厂模式
		ReadParamet(FLASH_SECTION_FACTORY,&tpar);
		if(tpar.ss >0)
		{
			uint8_t tar[10]={0};
			uint16_t vo;
			for(i=0;i<params.cp;i++)
			{
				memset(tar,0,sizeof(tar));
				spi_flash_read(tar,SPIF_SECTION_FCH + i*10,10);
				vo=(tar[0]<<8)|tar[1];
				IIC_WriteGP8211S(&vo,i+1);
				delay_ms(10);
				sVOA[i].wl = tpar.wl;
			}
		}
		else
		{
			for(i=0;i<params.cp;i++)
			{
				memset(&sVOA[i],0,sizeof(sVOA[i]));
				sVOA[i].cp = i+1;
			} 
		}
	}	
	
	
//	if(c)
//	{printfx("<Initial fail>");}
//	else
	{printfx("<Initial OK>");}
	

	
}


/***************************************************************************
;** 函数名称: 
;** 功能描述:  浮点型格式化小数点 带四舍五入
;** 输入参数: 
;** 返 回 值: 
;** 全局变量: 
;** 调用模块: 
;** 作　  者:   M-L-A
;** 日　  期:  2013-3-17
;** 修改原因：
;** 说    明:  	 leng 保几位小数点
;***************************************************************************/
double ffp(double fm, int leng)
{
	double  ft=0.0;
    unsigned long ul=0;

	if(fabs(fm)>0.0)
	{
		if(leng>=0)
		{
			if(leng>=5)	 //只允许保留5位小数点
			{leng=5;}
			leng++;
			ul=(unsigned long)(fabs(fm)*pow(10,leng));	  //10的leng次方
			if((ul%10)>=5)
			{ul=ul/10+1;}	  //四舍五入
			else
			{ul=ul/10;}
			ft=(double)(ul/pow(10,leng-1)); //保留的小数点
			if(fm<0.0)
			{ft=-ft;}
		}
		else 
		{ft=fm*pow(10,leng);}	  //负次方
	}
	return ft;
}

/***************************************************************************
** 函数名称:  	
** 功能描述:  	转换浮点数n 为字符串str。
** 输入参数: 	 
** 返 回 值: 	 无
** 全局变量: 
** 调用模块: 
** 作　  者:   M-L-A
** 日　  期:   2013-4-25
** 修改原因：
** 说    明:    字符串表示为科学计数法形式，由decimals指定四舍五入保留小数位（最多五位）。
;***************************************************************************/
char ftoa(double fv,unsigned char decimals,char *str)
{
	double fd;
	unsigned char i,n,c,k;
	unsigned int v,pw;
	
	c=0;
	if(fv<0.0)
	{str[c++]='-';}
	fv=fabs(fv);
	v=fv;
	fd=fv-v;
	v=fd*pow(10,decimals+1); //四舍五入
	if((v%10)>=5)
	{fv=fv+1/pow(10,decimals);}		
	v=fv;k=0;
	for(i=0;i<10;i++)	//0xffffffff=4 294 967 295
	{
		pw=pow(10,9-i);
		n=v/pw;
		v=v%pw;
		if((n>0)||(k>0))
		{str[c+k]=n+'0';k++;}
	}	
	c=c+k;
	if(k<=0)
	{str[c++]='0';}	
	if(decimals>0)
	{
		str[c++]='.';
		v=fv;
		fd=fv-v;
		for(i=0;i<decimals;i++)
		{
			fd=fd*10;
			v=fd;
			n=v%10;
			str[c++]=n+'0';
		}	
	}
	return c;

}
/***************************************************************************
** 函数名称:  	char itoa(int tv,char *str)
** 功能描述:  	整数 为字符串string。
** 输入参数:    tv--需要转换的整型；
** 返 回 值: 	c--返回个数； *str--返回字符串
** 全局变量: 	
** 调用模块: 
** 作　  者:   M-L-A
** 日　  期:   2019-9-13
** 修改原因：
** 说    明:    
			0xffffffff = 4 294 967 295;
;***************************************************************************/
char itoa(int tv,char *str)
{
	unsigned char i,n,c;
	unsigned int v;
	
	v=abs(tv);
	for(i=0;i<10;i++)	//0xffffffff=4 294 967 295
	{
		str[i]=(v%10)+'0';
		v=v/10;
		if(v<=0)
		{break;}
	}
	c=i+1;	
	if(tv<0)
	{str[c]='-';c++;}	
	for(i=0;i<(c/2);i++)
	{//高低位互换
		n=str[i];
		str[i]=str[c-i-1];
		str[c-i-1]=n;
	}	
	
	return c;
}
/***************************************************************************
** 函数名称:  	char itoa_32(int tv,char *str)
** 功能描述:  	整数 为字符串string。
** 输入参数:    tv--需要转换的整型；
** 返 回 值: 	c--返回个数； *str--返回字符串
** 全局变量: 	
** 调用模块: 
** 作　  者:   M-L-A
** 日　  期:   2019-9-13
** 修改原因：
** 说    明:    
			0xffffffff = 4 294 967 295;
;***************************************************************************/
char itoa_32(int tv,char *str)
{
	unsigned char i,n,c;
	unsigned int v,pw;
	
	c=0;
	v=abs(tv);
	for(i=0;i<10;i++)	//0xffffffff=4 294 967 295
	{
		pw=pow(10,9-i);
		n=v/pw;
		v=v%pw;
		if((n>0) || (c>0))
		{str[c++]=n+0x30;}
	}
	if(c>0)
	{
		for(i=0;i<c;i++)
		{
			n=str[i];
			str[i]=str[c-i-1];
			str[c-i-1]=n;
		}	
		if(tv<0)
		{str[c]='-';}
	}
	else
	{str[0]='0';}
	return c;
}
/***************************************************************************
;** 函数名称: 	
;** 功能描述:  USARTx printf	
;** 输入参数: 
;** 返 回 值: 
;** 全局变量: 
;** 调用模块: 
;** 作　  者:   M-L-A
;** 日　  期:  2012-6-29
;** 修改原因：
;** 说    明:
;***************************************************************************/
void sformat(char *o,char *s, ...)
{
	char buf[128]={0};   // 分配512字节的字符串缓存
	
    va_list ap;	
    va_start(ap, s);
    vsprintf(buf, (const char *)s, ap);    // 将格式字符串与后面的参数绑定为一个字符串，拷贝到输出缓存
    va_end(ap);
	
	strncat(o,buf,strlen(buf));
	
}

