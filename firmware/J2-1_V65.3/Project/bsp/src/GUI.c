

#include "GUI.h"
#include "PictureGUI.h"

/***************************************************************************
;** 函数名称:  	mode GUI
;** 功能描述:  	模式界面
;** 输入参数: 	
;** 返 回 值: 	
;** 优 先 级：  
;** 全局变量: 
;** 调用模块: 
;** 作　  者:   M-L-A
;** 日　  期:   2019-11-18
;** 修改原因：
;***************************************************************************/
void SelectMarkGUI(uint8_t s,uint16_t fc,uint16_t bc)
{	
	if(s>0)
	{
		LCD_Fill(0,0,16,240,GRAY0);
		
		if(s <= 3)
		{
			switch(s)
			{
				case 1:LCD_ShowASCII(0,44,(u8 *)">",fc,bc,24,0);break;
				case 2:LCD_ShowASCII(0,124,(u8 *)">",fc,bc,24,0);break;
				case 3:LCD_ShowASCII(0,205,(u8 *)">",fc,bc,24,0);break;
			}
		}
		else if(s <= 9)
		{LCD_ShowASCII(0,55+30*(s-4),(u8 *)">",fc,bc,24,0);	}
	}
}

/***************************************************************************
;** 函数名称: 	
;** 功能描述:  	
;** 输入参数: 
;** 返 回 值: 
;** 全局变量: 
;** 调用模块: 
;** 作　  者:   M-L-A
;** 日　  期:  2022-9-29
;** 修改原因:
;** 说    明:	 
;***************************************************************************/
void SelectOptionGUI(uint8_t s,uint16_t fc,uint16_t bc)
{
	switch(s)
	{
		case 0:break;
		case 1:{	
			if(setups.language)
			{LCD_ShowASCII(16,44,(u8 *)"Input Endpoint:",fc,bc,24,0);}
			else
			{
				LCD_ShowChinese(16,44,(u8 *)"输入端点",fc,bc,24,0);
//				LCD_ShowASCII(112,44,(u8 *)":",fc,bc,24,0);
			}
		}break;
		case 2:{	
			if(setups.language)
			{LCD_ShowASCII(16,124,(u8 *)"Output Endpoint:",fc,bc,24,0);}
			else
			{
				LCD_ShowChinese(16,124,(u8 *)"输出端点",fc,bc,24,0);
//				LCD_ShowASCII(112,124,(u8 *)":",fc,bc,24,0);
			}
		}break;		
		case 3:{	
			if(setups.language)
			{LCD_ShowASCII(16,205,(u8 *)"Backlight",fc,bc,24,0);}
			else
			{LCD_ShowChinese(16,205,(u8 *)"屏幕亮度",fc,bc,24,0);}			
		}break;
		case 4:{	
			if(setups.language)
			{LCD_ShowASCII(16,55,(u8 *)"Language:",fc,bc,24,0);}
			else
			{LCD_ShowChinese(16,55,(u8 *)"语言选择",fc,bc,24,0);}			
		}break;	
		case 5:{	
			if(setups.language)
			{LCD_ShowASCII(16,85,(u8 *)"BaudrateUART:",fc,bc,24,0);}
			else
			{LCD_ShowChinese(16,85,(u8 *)"串口波特率",fc,bc,24,0);}			
		}break;
		case 6:{	
			if(setups.language)
			{LCD_ShowASCII(16,115,(u8 *)"BaudrateUSB:",fc,bc,24,0);}
			else
			{
				LCD_ShowASCII(16,115,(u8 *)"USB",fc,bc,24,0);
				LCD_ShowChinese(52,115,(u8 *)"波特率",fc,bc,24,0);
			}			
		}break;		
		case 7:{	
			if(setups.language)
			{LCD_ShowASCII(16,145,(u8 *)"Net_IP:",fc,bc,24,0);}
			else
			{
				LCD_ShowChinese(16,145,(u8 *)"网口",fc,bc,24,0);
				LCD_ShowASCII(64,145,(u8 *)"IP:",fc,bc,24,0);
			}
			setups.index = 3;
		}break;	
		case 8:{	
			if(setups.language)
			{LCD_ShowASCII(16,175,(u8 *)"Net_Port:",fc,bc,24,0);}
			else
			{LCD_ShowChinese(16,175,(u8 *)"网口端口",fc,bc,24,0);}			
		}break;		
		case 9:{
			if(setups.language)
			{LCD_ShowASCII(16,205,(u8 *)"speaker:",fc,bc,24,0);}
			else
			{LCD_ShowChinese(16,205,(u8 *)"蜂鸣器",fc,bc,24,0);}
		}break;
	}
}
/***************************************************************************
;** 函数名称: 	void SubSelectGUI(uint8_t s,uint8_t loc,char *es,uint16_t fc,uint16_t bc)
;** 功能描述:  	s--reel;loc--IP0~3;es--enter string;
;** 输入参数: 
;** 返 回 值: 
;** 全局变量: 
;** 调用模块: 
;** 作　  者:   M-L-A
;** 日　  期:  2022-9-29
;** 修改原因:
;** 说    明:	 
;***************************************************************************/
void SubSelectGUI(uint8_t s,uint8_t loc,char *es,uint16_t fc,uint16_t bc)
{
	char str[10]={0};
	
	switch(s)
	{
		case 0:break;
		case 1:{	

		}break;
		case 2:{	
			if(loc < 8)
			{LCD_ShowASCII(22+loc*36,148,(u8 *)es,fc,bc,24,0);}
			else
			{LCD_ShowASCII(22+(loc-8)*36,174,(u8 *)es,fc,bc,24,0);}		
		}break;		

		case 3:{	
			BringhtnessGUI(GREEN,BLACK);	
		}break;
		
		case 4:{	
			if(setups.language)
			{
				LCD_ShowChinese(136,55,(u8 *)"中文",fc,bc,24,0);
				LCD_ShowASCII(208,55,(u8 *)"English",fc,LEMON,24,0);
			}
			else
			{
				LCD_ShowChinese(136,55,(u8 *)"中文",fc,LEMON,24,0);
				LCD_ShowASCII(208,55,(u8 *)"English",fc,bc,24,0);
			}			
		}break;	
		case 5:{
			memset(str,0,sizeof(str));
			if(setups.language)
			{
				LCD_Fill(184,85,320,109,GRAY0);
				itoa_32(setups.brUART,str);
				LCD_ShowASCII(184,85,(u8 *)str,fc,bc,24,0);
			}
			else
			{
				LCD_Fill(160,85,320,109,GRAY0);
				itoa_32(setups.brUART,str);
				LCD_ShowASCII(160,85,(u8 *)str,fc,bc,24,0);
			}			
		}break;
		case 6:{	
			memset(str,0,sizeof(str));			
			if(setups.language)
			{
				LCD_Fill(172,115,320,139,GRAY0);
				itoa_32(setups.brUSB,str);
				LCD_ShowASCII(172,115,(u8 *)str,fc,bc,24,0);	
			}
			else
			{
				LCD_Fill(160,115,320,139,GRAY0);
				itoa_32(setups.brUSB,str);
				LCD_ShowASCII(160,115,(u8 *)str,fc,bc,24,0);	
			}			
		}break;		
		case 7:{	
			switch(loc)
			{
				case 0:LCD_ShowASCII(112,145,(u8 *)es,fc,bc,24,0);break;	//192	
				case 1:LCD_ShowASCII(160,145,(u8 *)es,fc,bc,24,0);break;	//168	
				case 2:LCD_ShowASCII(208,145,(u8 *)es,fc,bc,24,0);break;	//1	
				case 3:LCD_ShowASCII(258,145,(u8 *)es,fc,bc,24,0);break;	//1	
			}					
//			LCD_ShowASCII(150,145,(u8 *)".",fc,bc,24,0);	//.					
//			LCD_ShowASCII(198,145,(u8 *)".",fc,bc,24,0);	//.					
//			LCD_ShowASCII(246,145,(u8 *)".",fc,bc,24,0);	//.								
		}break;	
		
		case 8:{	
			LCD_ShowASCII(136,175,(u8 *)es,fc,bc,24,0);			
		}break;	
		
		case 9:{
			if(setups.language)
			{
				if(setups.speak)
				{
					LCD_ShowASCII(144,205,(u8 *)"ON",fc,LEMON,24,0);
					LCD_ShowASCII(220,205,(u8 *)"OFF",fc,bc,24,0);
				}
				else
				{
					LCD_ShowASCII(144,205,(u8 *)"ON",fc,bc,24,0);
					LCD_ShowASCII(220,205,(u8 *)"OFF",fc,LEMON,24,0);
				}
			}
			else
			{
				if(setups.speak)
				{
					LCD_ShowChinese(124,205,(u8 *)"开启",fc,LEMON,24,0);
					LCD_ShowChinese(208,205,(u8 *)"关闭",fc,bc,24,0);
				}
				else
				{
					LCD_ShowChinese(124,205,(u8 *)"开启",fc,bc,24,0);
					LCD_ShowChinese(208,205,(u8 *)"关闭",fc,LEMON,24,0);
				}
			}
		}break;
	}
}
	

/***************************************************************************
;** 函数名称:  	Setup GUI
;** 功能描述:   设定界面
;** 输入参数: 	pg--page
;** 返 回 值: 	
;** 优 先 级：  
;** 全局变量: 
;** 调用模块: 
;** 作　  者:   M-L-A
;** 日　  期:   2019-11-20
;** 修改原因：
;***************************************************************************/
void SetupGUI(uint8_t pg,uint16_t fc,uint16_t bc)
{	
	char str[25]={0};
	uint8_t i,c,n;
	
	if((swMes.iep[0]+swMes.iep[1]) > (swMes.oep[0]+swMes.oep[1]))
	{n=swMes.oep[0]+swMes.oep[1];}
	else
	{n=swMes.iep[0]+swMes.iep[1];}
	
	LCD_Fill(0,0,320,240,GRAY0);
	if(!pg)
	{				
		if(setups.language)
		{
			LCD_ShowASCII(160-15*8,10,(u8 *)"Parameter Setup",fc,bc,32,0);			
			
			LCD_ShowASCII(16,44,(u8 *)"Input Endpoint:",fc,bc,24,0);	
			memset(str,0,25);
			for(c=0,i=0;i<n;i++)
			{
				str[c++] = (i+1)/10 + '0';
				str[c++] = (i+1)%10 + '0';
				str[c++] = '_';
				if(c >= 24)
				{break;}
			}
			if((++i) >= n)
			{str[c-1] = 0;}
			LCD_ShowASCII(22,68,(u8 *)str,fc,bc,24,0);		
			memset(str,0,25);
			for(c=0;i<n;i++)
			{
				str[c++] = (i+1)/10 + '0';
				str[c++] = (i+1)%10 + '0';
				str[c++] = '_';
				if(c >= 24)
				{break;}
			}
			if((++i) >= n)
			{str[c-1] = 0;}
			LCD_ShowASCII(22,94,(u8 *)str,fc,bc,24,0);		
			
			LCD_ShowASCII(16,124,(u8 *)"Output Endpoint::",fc,bc,24,0);			
			memset(str,0,25);
			for(c=0,i=0;i<n;i++)
			{
				str[c++] = swMes.ocr[i]/10 + '0';
				str[c++] = swMes.ocr[i]%10 + '0';
				str[c++] = '_';
				if(c >= 24)
				{break;}
			}
			if((++i) >= n)
			{str[c-1] = 0;}
			LCD_ShowASCII(22,148,(u8 *)str,fc,bc,24,0);		
			memset(str,0,25);
			for(c=0;i<n;i++)
			{
				str[c++] = swMes.ocr[i]/10 + '0';
				str[c++] = swMes.ocr[i]%10 + '0';
				str[c++] = '_';
				if(c >= 24)
				{break;}
			}
			if((++i) >= n)
			{str[c-1] = 0;}
			LCD_ShowASCII(22,174,(u8 *)str,fc,bc,24,0);				
						
			LCD_ShowASCII(16,205,(u8 *)"Backlight",fc,bc,24,0);
			LCD_DrawRectangle(124,205,265,230,BLACK);
			BringhtnessGUI(GREEN,BLACK);			
		}
		else
		{
			LCD_ShowChinese(160-32*2,8,(u8 *)"参数设置",fc,bc,32,0);
		
			LCD_ShowASCII(0,44,(u8 *)">",fc,bc,24,0);
			LCD_ShowChinese(16,44,(u8 *)"输入端点",fc,bc,24,0);
			LCD_ShowASCII(112,44,(u8 *)":",fc,bc,24,0);	
			memset(str,0,25);
			for(c=0,i=0;i<n;i++)
			{
				str[c++] = (i+1)/10 + '0';
				str[c++] = (i+1)%10 + '0';
				str[c++] = '_';
				if(c >= 24)
				{break;}
			}
			if((++i) >= n)
			{str[c-1] = 0;}
			LCD_ShowASCII(22,68,(u8 *)str,fc,bc,24,0);		
			memset(str,0,25);
			for(c=0;i<n;i++)
			{
				str[c++] = (i+1)/10 + '0';
				str[c++] = (i+1)%10 + '0';
				str[c++] = '_';
				if(c >= 24)
				{break;}
			}
			if((++i) >= n)
			{str[c-1] = 0;}
			LCD_ShowASCII(22,94,(u8 *)str,fc,bc,24,0);		
			
			
			LCD_ShowChinese(16,124,(u8 *)"输出端点",fc,bc,24,0);	
			LCD_ShowASCII(112,124,(u8 *)":",fc,bc,24,0);			
			memset(str,0,25);
			for(c=0,i=0;i<n;i++)
			{
				str[c++] = swMes.ocr[i]/10 + '0';
				str[c++] = swMes.ocr[i]%10 + '0';
				str[c++] = '_';
				if(c >= 24)
				{break;}
			}
			if((++i) >= n)
			{str[c-1] = 0;}
			LCD_ShowASCII(22,148,(u8 *)str,fc,bc,24,0);		
			memset(str,0,25);
			for(c=0;i<n;i++)
			{
				str[c++] = swMes.ocr[i]/10 + '0';
				str[c++] = swMes.ocr[i]%10 + '0';
				str[c++] = '_';
				if(c >= 24)
				{break;}
			}
			if((++i) >= n)
			{str[c-1] = 0;}
			LCD_ShowASCII(22,174,(u8 *)str,fc,bc,24,0);		
			
			LCD_ShowChinese(16,205,(u8 *)"屏幕亮度",fc,bc,24,0);
			LCD_ShowASCII(112,205,(u8 *)":",fc,bc,24,0);
			LCD_DrawRectangle(124,205,265,230,BLACK);
			BringhtnessGUI(GREEN,BLACK);
		}
	}
	else if(pg==1)
	{		
		LCD_ShowASCII(0,55,(u8 *)">",fc,bc,24,0);
		
		if(setups.language)
		{
			LCD_ShowASCII(160-15*8,10,(u8 *)"Parameter Setup",fc,bc,32,0);
			
			LCD_ShowASCII(16,55,(u8 *)"Language:",fc,bc,24,0);
			if(setups.language)
			{
				LCD_ShowChinese(136,55,(u8 *)"中文",fc,bc,24,0);
				LCD_ShowASCII(208,55,(u8 *)"English",fc,LEMON,24,0);
			}
			else
			{
				LCD_ShowChinese(136,55,(u8 *)"中文",fc,LEMON,24,0);
				LCD_ShowASCII(208,55,(u8 *)"English",fc,bc,24,0);
			}		
			
			LCD_ShowASCII(16,85,(u8 *)"BaudrateUART:",fc,bc,24,0);
			memset(str,0,sizeof(str));
			itoa_32(setups.brUART,str);
			LCD_ShowASCII(184,85,(u8 *)str,fc,bc,24,0);
					
			LCD_ShowASCII(16,115,(u8 *)"BaudrateUSB:",fc,bc,24,0);
			memset(str,0,sizeof(str));
			itoa_32(setups.brUSB,str);
			LCD_ShowASCII(172,115,(u8 *)str,fc,bc,24,0);		
			
			LCD_ShowASCII(16,145,(u8 *)"Net_IP:",fc,bc,24,0);
			memset(str,0,sizeof(str));
			itoa_32(ethernet.ip[0],str);
			LCD_ShowASCII(112,145,(u8 *)str,fc,bc,24,0);	//192			
			LCD_ShowASCII(150,145,(u8 *)".",fc,bc,24,0);	//.			
			memset(str,0,sizeof(str));
			itoa_32(ethernet.ip[1],str);
			LCD_ShowASCII(160,145,(u8 *)str,fc,bc,24,0);			
			LCD_ShowASCII(198,145,(u8 *)".",fc,bc,24,0);	//.			
			memset(str,0,sizeof(str));
			itoa_32(ethernet.ip[2],str);
			LCD_ShowASCII(208,145,(u8 *)str,fc,bc,24,0);			
			LCD_ShowASCII(246,145,(u8 *)".",fc,bc,24,0);	//.			
			memset(str,0,sizeof(str));
			itoa_32(ethernet.ip[3],str);
			LCD_ShowASCII(258,145,(u8 *)str,fc,bc,24,0);			
			
			LCD_ShowASCII(16,175,(u8 *)"Net_Port:",fc,bc,24,0);	
			memset(str,0,sizeof(str));
			itoa_32(ethernet.port,str);
			LCD_ShowASCII(136,175,(u8 *)str,fc,bc,24,0);	

			LCD_ShowASCII(16,205,(u8 *)"speaker:",fc,bc,24,0);
			if(setups.speak)
			{
				LCD_ShowASCII(144,205,(u8 *)"ON",fc,LEMON,24,0);
				LCD_ShowASCII(220,205,(u8 *)"OFF",fc,bc,24,0);
			}
			else
			{
				LCD_ShowASCII(144,205,(u8 *)"ON",fc,bc,24,0);
				LCD_ShowASCII(220,205,(u8 *)"OFF",fc,LEMON,24,0);
			}
			
		}
		else
		{			
			LCD_ShowChinese(160-32*2,10,(u8 *)"参数设置",fc,bc,32,0);
			LCD_ShowChinese(16,55,(u8 *)"语言选择",fc,bc,24,0);
			LCD_ShowASCII(112,55,(u8 *)":",fc,bc,24,0);
			if(setups.language)
			{
				LCD_ShowChinese(136,55,(u8 *)"中文",fc,bc,24,0);
				LCD_ShowASCII(208,55,(u8 *)"English",fc,LEMON,24,0);
			}
			else
			{
				LCD_ShowChinese(136,55,(u8 *)"中文",fc,LEMON,24,0);
				LCD_ShowASCII(208,55,(u8 *)"English",fc,bc,24,0);
			}		
			
			LCD_ShowChinese(16,85,(u8 *)"串口波特率",fc,bc,24,0);
			LCD_ShowASCII(136,85,(u8 *)":",fc,bc,24,0);
			memset(str,0,sizeof(str));
			itoa_32(setups.brUART,str);
			LCD_ShowASCII(160,85,(u8 *)str,fc,bc,24,0);
					
			LCD_ShowASCII(16,115,(u8 *)"USB",fc,bc,24,0);
			LCD_ShowChinese(52,115,(u8 *)"波特率",fc,bc,24,0);
			LCD_ShowASCII(124,115,(u8 *)":",fc,bc,24,0);
			memset(str,0,sizeof(str));
			itoa_32(setups.brUSB,str);
			LCD_ShowASCII(160,115,(u8 *)str,fc,bc,24,0);		
			
			LCD_ShowChinese(16,145,(u8 *)"网口",fc,bc,24,0);
			LCD_ShowASCII(64,145,(u8 *)"IP:",fc,bc,24,0);
			memset(str,0,sizeof(str));
			itoa_32(ethernet.ip[0],str);
			LCD_ShowASCII(112,145,(u8 *)str,fc,bc,24,0);	//192			
			LCD_ShowASCII(150,145,(u8 *)".",fc,bc,24,0);	//.			
			memset(str,0,sizeof(str));
			itoa_32(ethernet.ip[1],str);
			LCD_ShowASCII(160,145,(u8 *)str,fc,bc,24,0);			
			LCD_ShowASCII(198,145,(u8 *)".",fc,bc,24,0);	//.			
			memset(str,0,sizeof(str));
			itoa_32(ethernet.ip[2],str);
			LCD_ShowASCII(208,145,(u8 *)str,fc,bc,24,0);			
			LCD_ShowASCII(246,145,(u8 *)".",fc,bc,24,0);	//.			
			memset(str,0,sizeof(str));
			itoa_32(ethernet.ip[3],str);
			LCD_ShowASCII(258,145,(u8 *)str,fc,bc,24,0);			
			
			LCD_ShowChinese(16,175,(u8 *)"网口端口",fc,bc,24,0);
			LCD_ShowASCII(112,175,(u8 *)":",fc,bc,24,0);	
			memset(str,0,sizeof(str));
			itoa_32(ethernet.port,str);
			LCD_ShowASCII(136,175,(u8 *)str,fc,bc,24,0);
			
			LCD_ShowChinese(16,205,(u8 *)"蜂鸣器",fc,bc,24,0);
			LCD_ShowASCII(88,205,(u8 *)":",fc,bc,24,0);
			if(setups.speak)
			{
				LCD_ShowChinese(124,205,(u8 *)"开启",fc,LEMON,24,0);
				LCD_ShowChinese(208,205,(u8 *)"关闭",fc,bc,24,0);
			}
			else
			{
				LCD_ShowChinese(124,205,(u8 *)"开启",fc,bc,24,0);
				LCD_ShowChinese(208,205,(u8 *)"关闭",fc,LEMON,24,0);
			}
		}		
	}
}

/***************************************************************************
;** 函数名称:  	BlackLightOutlineGUI
;** 功能描述:   背光界面边框
;** 输入参数: 	
;** 返 回 值: 	
;** 优 先 级：  
;** 全局变量: 
;** 调用模块: 
;** 作　  者:   M-L-A
;** 日　  期:   2019-11-20
;** 修改原因：
;***************************************************************************/
uint8_t BlackLightOutlineGUI(uint16_t color)
{
//	uint8_t x,y;
//	for(x=108;x<240;x++)
//	{
//		LCD_DrawPoint(x,142,color);
////		LCD_DrawPoint(x,143,color);
////		LCD_DrawPoint(x,182,color);
//		LCD_DrawPoint(x,183,color);
//	}
//	for(y=205;y<229;y++)
//	{
//		LCD_DrawPoint(10,y,color);
////		LCD_DrawPoint(11,y,color);
////		LCD_DrawPoint(239,y,color);
//		LCD_DrawPoint(240,y,color);
//	}
	return 0;
}
/***************************************************************************
;** 函数名称:  	BlackLightGUI
;** 功能描述:   背光界面
;** 输入参数: 	
;** 返 回 值: 	
;** 优 先 级：  
;** 全局变量: 
;** 调用模块: 
;** 作　  者:   M-L-A
;** 日　  期:   2019-11-20
;** 修改原因：
;***************************************************************************/
uint8_t BringhtnessGUI(uint16_t cl1,uint16_t cl2)
{
	char str[6]={0};
	uint16_t x,y,i;
	
//	i = (pLCD->blk-BLK_MIN)*(265-126)/BLK_SRV+126;	
	i = (pLCD->blk)*(265-126)/100+126;
	if(i>263)
	{i=263;}
	for(y=207;y<228;y++)
	{
		for(x=126;x<i;x++)
		{LCD_DrawPoint(x,y,cl1);}
		for(x=i;x<263;x++)
		{LCD_DrawPoint(x,y,GRAY0);}
	}
	memset(str,0,6);
//	i=((double)(pLCD->blk-BLK_MIN))*1000/BLK_SRV;
//	if((i%10)>5)
//	{i=i/10+1;}
//	else
//	{i=i/10;}
	itoa_32(pLCD->blk,str);
	strcat(str,"%");
	LCD_Fill(266,205,320,240,GRAY0);	
	LCD_ShowASCII(268,205,(uint8_t *)str,cl2,GRAY0,24,0);
	
	return 0;
}

/***************************************************************************
;** 函数名称:  	MainGUI
;** 功能描述:   主界面
;** 输入参数: 	gui--choose GUI; r--record GUI;
;** 返 回 值: 	
;** 优 先 级：  
;** 全局变量:  
;** 调用模块: 
;** 作　  者:   M-L-A
;** 日　  期:   2019-11-20
;** 修改原因：
;***************************************************************************/
void MainGUI(uint16_t fc,uint16_t bc)
{	
	char astr[25]={0};
	uint8_t i,c,n;
	
	if((swMes.iep[0]+swMes.iep[1]) > (swMes.oep[0]+swMes.oep[1]))
	{n=swMes.oep[0]+swMes.oep[1];}
	else
	{n=swMes.iep[0]+swMes.iep[1];}
	
	LCD_Fill(0,0,320,240,GRAY0);

	i=strlen((char *)pLCD->title);
	i=i/2+1;
	i=i*16;//8;
	LCD_ShowASCII(160-i,6,pLCD->title,fc,bc,ASC_16X32,0);
	
	if(setups.language)
	{		
		LCD_ShowASCII(2,48,(u8 *)"Input Endpoint:",fc,bc,24,0);		
		memset(astr,0,25);
		for(c=0,i=0;i<n;i++)
		{
			astr[c++] = (i+1)/10 + '0';
			astr[c++] = (i+1)%10 + '0';
			astr[c++] = '_';
			if(c >= 24)
			{break;}
		}
		if((++i) >= n)
		{astr[c-1] = 0;}
		LCD_ShowASCII(14,78,(u8 *)astr,fc,bc,24,0);		
		memset(astr,0,25);
		for(c=0;i<n;i++)
		{
			astr[c++] = (i+1)/10 + '0';
			astr[c++] = (i+1)%10 + '0';
			astr[c++] = '_';
			if(c >= 24)
			{break;}
		}
		if((++i) >= n)
		{astr[c-1] = 0;}
		LCD_ShowASCII(14,108,(u8 *)astr,fc,bc,24,0);	
		
		
		LCD_ShowASCII(2,142,(u8 *)"Output Endpoint:",fc,bc,24,0);		
		memset(astr,0,25);
		for(c=0,i=0;i<n;i++)
		{
			astr[c++] = swMes.ocr[i]/10 + '0';
			astr[c++] = swMes.ocr[i]%10 + '0';
			astr[c++] = '_';
			if(c >= 24)
			{break;}
		}
		if((++i) >= n)
		{astr[c-1] = 0;}
		LCD_ShowASCII(14,172,(u8 *)astr,fc,bc,24,0);				
		memset(astr,0,25);
		for(c=0;i<n;i++)
		{
			astr[c++] = swMes.ocr[i]/10 + '0';
			astr[c++] = swMes.ocr[i]%10 + '0';
			astr[c++] = '_';
			if(c >= 24)
			{break;}
		}
		if((++i) >= n)
		{astr[c-1] = 0;}
		LCD_ShowASCII(14,202,(u8 *)astr,fc,bc,24,0);
	
	}
	else
	{	
		LCD_ShowChinese(2,48,(u8 *)"输入端点",fc,bc,24,0);	
		LCD_ShowASCII(96,48,(u8 *)":",fc,bc,24,0);		
		memset(astr,0,25);
		for(c=0,i=0;i<n;i++)
		{
			astr[c++] = (i+1)/10 + '0';
			astr[c++] = (i+1)%10 + '0';
			astr[c++] = '_';
			if(c >= 24)
			{break;}
		}
		if((++i) >= n)	
		{astr[c-1] = 0;}
		LCD_ShowASCII(14,78,(u8 *)astr,fc,bc,24,0);		
		memset(astr,0,25);
		for(c=0;i<n;i++)
		{
			astr[c++] = (i+1)/10 + '0';
			astr[c++] = (i+1)%10 + '0';
			astr[c++] = '_';
			if(c >= 24)
			{break;}
		}
		if((++i) >= n)
		{astr[c-1] = 0;}
		LCD_ShowASCII(14,108,(u8 *)astr,fc,bc,24,0);		
		
		
		LCD_ShowChinese(2,142,(u8 *)"输出端点",fc,bc,24,0);	
		LCD_ShowASCII(96,142,(u8 *)":",fc,bc,24,0);			
		memset(astr,0,25);
		for(c=0,i=0;i<n;i++)
		{
			astr[c++] = swMes.ocr[i]/10 + '0';
			astr[c++] = swMes.ocr[i]%10 + '0';
			astr[c++] = '_';
			if(c >= 24)
			{break;}
		}
		if((++i) >= n)
		{astr[c-1] = 0;}
		LCD_ShowASCII(14,172,(u8 *)astr,fc,bc,24,0);		
		memset(astr,0,25);
		for(c=0;i<n;i++)
		{
			astr[c++] = swMes.ocr[i]/10 + '0';
			astr[c++] = swMes.ocr[i]%10 + '0';
			astr[c++] = '_';
			if(c >= 24)
			{break;}
		}
		if((++i) >= n)
		{astr[c-1] = 0;}
		LCD_ShowASCII(14,202,(u8 *)astr,fc,bc,24,0);
	}
	
}
/***************************************************************************
;** 函数名称:  	CurrentChannelGUI
;** 功能描述:   
;** 输入参数: 	
;** 返 回 值: 	
;** 优 先 级：  
;** 全局变量:  
;** 调用模块: 
;** 作　  者:   M-L-A
;** 日　  期:   2019-11-20
;** 修改原因：
;***************************************************************************/
void CurrentChannelGUI(uint16_t ch,uint16_t fc,uint16_t bc)
{
	char tstr[6]={0};
	
	if(setups.language)
	{
//		LCD_ShowASCII(0,55,(u8 *)"CurrentChannel:",fc,bc,32,0);
		memset(tstr,0,sizeof(tstr));
		LCD_Fill(252,55,320,100,GRAY0);
		itoa_32(ch,tstr);
		LCD_ShowASCII(252,55,(u8 *)tstr,fc,bc,32,0);
	}
	else
	{
//		LCD_ShowChinese(0,55,(u8 *)"当前通道",fc,bc,32,0);
//		LCD_ShowASCII(128,55,(u8 *)":",fc,bc,32,0);
		memset(tstr,0,sizeof(tstr));
		LCD_Fill(150,55,320,100,GRAY0);
		itoa_32(ch,tstr);
		LCD_ShowASCII(150,55,(u8 *)tstr,fc,bc,32,0);
	}	
	
}
/***************************************************************************
;** 函数名称:  	EndpointGUI
;** 功能描述:   
;** 输入参数: 	
;** 返 回 值: 	
;** 优 先 级：  
;** 全局变量:  
;** 调用模块: 
;** 作　  者:   M-L-A
;** 日　  期:   2019-11-20
;** 修改原因：
;***************************************************************************/
void EndpointGUI(void)
{
	char i,n,c,str[64]={0};
	
	n = swMes.iep[0]+swMes.iep[1];
	if(!setups.step)
	{//主界面						
		LCD_Fill(14,172,320,240,GRAY0);
		
		memset(str,0,sizeof(str));
		for(c=0,i=0;i<n;i++)
		{
			str[c++] = swMes.ocr[i]/10 + '0';
			str[c++] = swMes.ocr[i]%10 + '0';
			str[c++] = '_';
			if(c >= 24)
			{break;}
		}
		if((++i) >= n)
		{str[c-1] = 0;}
		LCD_ShowASCII(14,172,(u8 *)str,GRAYBLUE,GRAY0,24,0);				
		memset(str,0,sizeof(str));
		for(c=0;i<n;i++)
		{
			str[c++] = swMes.ocr[i]/10 + '0';
			str[c++] = swMes.ocr[i]%10 + '0';
			str[c++] = '_';
			if(c >= 24)
			{break;}
		}
		if((++i) >= n)
		{str[c-1] = 0;}
		LCD_ShowASCII(14,202,(u8 *)str,GRAYBLUE,GRAY0,24,0);
	}	
	else if((setups.page==0)&&(setups.step !=3))
	{//选顶菜单
		memset(str,0,sizeof(str));
		for(c=0,i=0;i<n;i++)
		{
			str[c++] = swMes.ocr[i]/10 + '0';
			str[c++] = swMes.ocr[i]%10 + '0';
			str[c++] = '_';
			if(c >= 24)
			{break;}
		}
		if((++i) >= n)
		{str[c-1] = 0;}
		LCD_ShowASCII(22,148,(u8 *)str,BROWN,GRAY0,24,0);		
		memset(str,0,sizeof(str));
		for(c=0;i<n;i++)
		{
			str[c++] = swMes.ocr[i]/10 + '0';
			str[c++] = swMes.ocr[i]%10 + '0';
			str[c++] = '_';
			if(c >= 24)
			{break;}
		}
		if((++i) >= n)
		{str[c-1] = 0;}
		LCD_ShowASCII(22,174,(u8 *)str,BROWN,GRAY0,24,0);	
	}
}
