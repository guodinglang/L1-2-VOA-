
/****************************************************************************************
*
*	模块名称 : BSP(Board Support Package)
*	文件名称 : bsp.c
*	版    本 : V1.0
*	说    明 : BSP 板级支持包(Board Support Package)
*	修改记录 :
*   版 本 号 :  
*   日    期 :     
*   作    者 :   
*	说    明 :
*
*****************************************************************************************/

//#include <pulicinclude.h>

#include "IOstream.h"

//--------------------------------------------------------------------------
//BitStructure16    erCode; //记录错误代码
ButtonManage  	  button,*pkey=&button;

uint8_t encoder;

//uint16_t keycn[4]={0};
//uint16_t PinStruct[CH_NUM]={GPIO_PINS_8,GPIO_PINS_7,GPIO_PINS_6,GPIO_PINS_15,GPIO_PINS_14,GPIO_PINS_13,GPIO_PINS_12,GPIO_PINS_11,GPIO_PINS_10,GPIO_PINS_1,GPIO_PINS_0,GPIO_PINS_5};
//gpio_type *gpioStruct[CH_NUM]={GPIOC,GPIOC,GPIOC,GPIOB,GPIOB,GPIOB,GPIOB,GPIOB,GPIOB,GPIOB,GPIOB,GPIOC};


/***************************************************************************
;** 函数名称:  keyConfig
;** 功能描述:  
;** 输入参数:  无
;** 返 回 值: 
;** 全局变量: 
;** 调用模块: 
;** 作　  者:   M-LA
;** 日　  期:  2022-2-13
;** 修改原因：
;** 说    明:
;***************************************************************************/
void ioConfig(void)
{
	gpio_init_type gpio_init_struct;
	
	crm_periph_clock_enable(CRM_GPIOA_PERIPH_CLOCK, TRUE);
	crm_periph_clock_enable(CRM_GPIOB_PERIPH_CLOCK, TRUE);
	crm_periph_clock_enable(CRM_GPIOC_PERIPH_CLOCK, TRUE);
	crm_periph_clock_enable(CRM_GPIOD_PERIPH_CLOCK, TRUE);
//	crm_periph_clock_enable(CRM_GPIOE_PERIPH_CLOCK, TRUE);
	crm_periph_clock_enable(CRM_IOMUX_PERIPH_CLOCK, TRUE);
	
	
	/* configure PA Input*/
	gpio_init_struct.gpio_pins = GPIO_PINS_1|GPIO_PINS_2|GPIO_PINS_3|GPIO_PINS_6|GPIO_PINS_8|GPIO_PINS_11|GPIO_PINS_12;//
	gpio_init_struct.gpio_mode = GPIO_MODE_INPUT;
	gpio_init_struct.gpio_pull = GPIO_PULL_UP;
	gpio_init_struct.gpio_out_type = GPIO_OUTPUT_PUSH_PULL;
	gpio_init_struct.gpio_drive_strength = GPIO_DRIVE_STRENGTH_STRONGER;
	gpio_init(GPIOA, &gpio_init_struct);
	
	/* configure PA Output*/
	gpio_init_struct.gpio_pins = GPIO_PINS_0|GPIO_PINS_4|GPIO_PINS_5|GPIO_PINS_7;//
	gpio_init_struct.gpio_mode = GPIO_MODE_OUTPUT;
	gpio_init_struct.gpio_pull = GPIO_PULL_NONE;
	gpio_init_struct.gpio_out_type = GPIO_OUTPUT_PUSH_PULL;
	gpio_init_struct.gpio_drive_strength = GPIO_DRIVE_STRENGTH_STRONGER;
	gpio_init(GPIOA, &gpio_init_struct);
	
	
	/* configure PB  Input*/
	gpio_init_struct.gpio_pins = GPIO_PINS_0|GPIO_PINS_2|GPIO_PINS_3|GPIO_PINS_5|GPIO_PINS_9|GPIO_PINS_10|GPIO_PINS_11|GPIO_PINS_12|GPIO_PINS_14;
	gpio_init_struct.gpio_mode = GPIO_MODE_INPUT;	//GPIO_MODE_OUTPUT;
	gpio_init_struct.gpio_pull = GPIO_PULL_UP;
	gpio_init_struct.gpio_out_type = GPIO_OUTPUT_PUSH_PULL; //
	gpio_init_struct.gpio_drive_strength = GPIO_DRIVE_STRENGTH_STRONGER;
	gpio_init(GPIOB, &gpio_init_struct);	
	
	/* configure PB Output*/
	gpio_init_struct.gpio_pins = GPIO_PINS_1|GPIO_PINS_4|GPIO_PINS_6|GPIO_PINS_7|GPIO_PINS_8|GPIO_PINS_13|GPIO_PINS_15;
	gpio_init_struct.gpio_mode = GPIO_MODE_OUTPUT;
	gpio_init_struct.gpio_pull = GPIO_PULL_NONE;
	gpio_init_struct.gpio_out_type = GPIO_OUTPUT_PUSH_PULL;
	gpio_init_struct.gpio_drive_strength = GPIO_DRIVE_STRENGTH_STRONGER;
	gpio_init(GPIOB, &gpio_init_struct);
	
	gpio_pin_remap_config(SWJTAG_MUX_010, TRUE);
//	/* configure PC Input*/
//	gpio_init_struct.gpio_pins = GPIO_PINS_6|GPIO_PINS_7|GPIO_PINS_8;
//	gpio_init_struct.gpio_mode = GPIO_MODE_INPUT;
//	gpio_init_struct.gpio_pull = GPIO_PULL_UP;//GPIO_PULL_NONE;
//	gpio_init_struct.gpio_out_type = GPIO_OUTPUT_PUSH_PULL;
//	gpio_init_struct.gpio_drive_strength = GPIO_DRIVE_STRENGTH_STRONGER;
//	gpio_init(GPIOC, &gpio_init_struct);
	
	/* configure PC Output*/
	gpio_init_struct.gpio_pins = GPIO_PINS_13;
	gpio_init_struct.gpio_mode = GPIO_MODE_OUTPUT;
	gpio_init_struct.gpio_pull = GPIO_PULL_NONE;
	gpio_init_struct.gpio_out_type = GPIO_OUTPUT_PUSH_PULL;
	gpio_init_struct.gpio_drive_strength = GPIO_DRIVE_STRENGTH_STRONGER;
	gpio_init(GPIOC, &gpio_init_struct);
	
//	/* configure PC Output open*/
//	gpio_init_struct.gpio_pins = GPIO_PINS_4|GPIO_PINS_5;
//	gpio_init_struct.gpio_mode = GPIO_MODE_OUTPUT;
//	gpio_init_struct.gpio_pull = GPIO_PULL_NONE;
//	gpio_init_struct.gpio_out_type = GPIO_OUTPUT_OPEN_DRAIN;
//	gpio_init_struct.gpio_drive_strength = GPIO_DRIVE_STRENGTH_STRONGER;
//	gpio_init(GPIOC, &gpio_init_struct);
	
//	/* configure PD Input*/
//	gpio_init_struct.gpio_pins = GPIO_PINS_13;
//	gpio_init_struct.gpio_mode = GPIO_MODE_INPUT;
//	gpio_init_struct.gpio_pull = GPIO_PULL_UP;//GPIO_PULL_NONE;
//	gpio_init_struct.gpio_out_type = GPIO_OUTPUT_PUSH_PULL;
//	gpio_init_struct.gpio_drive_strength = GPIO_DRIVE_STRENGTH_STRONGER;
//	gpio_init(GPIOD, &gpio_init_struct);

//	/* configure PD Output*/
//	gpio_init_struct.gpio_pins = GPIO_PINS_7|GPIO_PINS_12;
//	gpio_init_struct.gpio_mode = GPIO_MODE_OUTPUT;
//	gpio_init_struct.gpio_pull = GPIO_PULL_NONE;
//	gpio_init_struct.gpio_out_type = GPIO_OUTPUT_PUSH_PULL;
//	gpio_init_struct.gpio_drive_strength = GPIO_DRIVE_STRENGTH_STRONGER;
//	gpio_init(GPIOD, &gpio_init_struct);
	
//	/* configure PD Output open*/
//	gpio_init_struct.gpio_pins = GPIO_PINS_9|GPIO_PINS_10;
//	gpio_init_struct.gpio_mode = GPIO_MODE_OUTPUT;
//	gpio_init_struct.gpio_pull = GPIO_PULL_NONE;
//	gpio_init_struct.gpio_out_type = GPIO_OUTPUT_OPEN_DRAIN;
//	gpio_init_struct.gpio_drive_strength = GPIO_DRIVE_STRENGTH_STRONGER;
//	gpio_init(GPIOD, &gpio_init_struct);
////	gpio_pin_remap_config(PD01_MUX, TRUE);

//	/* configure PE Input*/
//	gpio_init_struct.gpio_pins = GPIO_PINS_2|GPIO_PINS_14;
//	gpio_init_struct.gpio_mode = GPIO_MODE_INPUT;
//	gpio_init_struct.gpio_pull = GPIO_PULL_NONE;
//	gpio_init_struct.gpio_out_type = GPIO_OUTPUT_PUSH_PULL;
//	gpio_init_struct.gpio_drive_strength = GPIO_DRIVE_STRENGTH_STRONGER;
//	gpio_init(GPIOE, &gpio_init_struct);
	
//	/* configure PE Input*/
//	gpio_init_struct.gpio_pins = GPIO_PINS_15;
//	gpio_init_struct.gpio_mode = GPIO_MODE_INPUT;
//	gpio_init_struct.gpio_pull = GPIO_PULL_DOWN;
//	gpio_init_struct.gpio_out_type = GPIO_OUTPUT_PUSH_PULL;
//	gpio_init_struct.gpio_drive_strength = GPIO_DRIVE_STRENGTH_STRONGER;
//	gpio_init(GPIOE, &gpio_init_struct);
	
//	/* configure PE Output*/
//	gpio_init_struct.gpio_pins = GPIO_PINS_4;
//	gpio_init_struct.gpio_mode = GPIO_MODE_OUTPUT;
//	gpio_init_struct.gpio_pull = GPIO_PULL_NONE;
//	gpio_init_struct.gpio_out_type = GPIO_OUTPUT_PUSH_PULL;
//	gpio_init_struct.gpio_drive_strength = GPIO_DRIVE_STRENGTH_STRONGER;
//	gpio_init(GPIOE, &gpio_init_struct);
	
//	/* configure PE Output open*/
//	gpio_init_struct.gpio_pins = GPIO_PINS_11|GPIO_PINS_12|GPIO_PINS_13;
//	gpio_init_struct.gpio_mode = GPIO_MODE_OUTPUT;
//	gpio_init_struct.gpio_pull = GPIO_PULL_NONE;
//	gpio_init_struct.gpio_out_type = GPIO_OUTPUT_OPEN_DRAIN;
//	gpio_init_struct.gpio_drive_strength =  GPIO_DRIVE_STRENGTH_STRONGER;
//	gpio_init(GPIOE, &gpio_init_struct);	

	
	DAC_POWER(0);
}

/***************************************************************************
;** 函数名称:  keyConfig
;** 功能描述:  
;** 输入参数:  无
;** 返 回 值: 
;** 全局变量: 
;** 调用模块: 
;** 作　  者:   M-LA
;** 日　  期:  2022-2-13
;** 修改原因：
;** 说    明:
;***************************************************************************/
void exint_line15_config(void)
{
  exint_init_type exint_init_struct;

  crm_periph_clock_enable(CRM_IOMUX_PERIPH_CLOCK, TRUE);
  crm_periph_clock_enable(CRM_GPIOA_PERIPH_CLOCK, TRUE);

  gpio_exint_line_config(GPIO_PORT_SOURCE_GPIOA, GPIO_PINS_SOURCE15);

  exint_default_para_init(&exint_init_struct);
  exint_init_struct.line_enable = TRUE;
  exint_init_struct.line_mode = EXINT_LINE_INTERRUPUT;
  exint_init_struct.line_select = EXINT_LINE_15;
  exint_init_struct.line_polarity = EXINT_TRIGGER_FALLING_EDGE;
  exint_init(&exint_init_struct);

  nvic_priority_group_config(NVIC_PRIORITY_GROUP_4);
  nvic_irq_enable(EXINT15_10_IRQn, 1, 0);
	
}


/***************************************************************************
;** 函数名称:  	
;** 功能描述:  	
;** 输入参数: 	无
;** 返 回 值: 	
;** 优 先 级：  
;** 全局变量: 
;** 调用模块: 
;** 作　  者:   M-L-A
;** 日　  期:   2022-2-13
;** 修改原因：
;***************************************************************************/
void InputIOScan(void)
{	
//	uint8_t u= 0x0F & (GPIOA->idt);//(0x0F && GPIOA->idt);
//	if(u != encoder)
//	{
//		if(pkey->cn[0] > 0)
//		{pkey->cn[0]--;}
//		else
//		{
//			encoder = 0x0F & (GPIOA->idt);
//			pkey->cn[0]=0;
//		}
//	}
//	else
//	{
//		if(pkey->cn[0] < 20000)
//		{
//			pkey->cn[0]++;
//			if(pkey->cn[0] == 19998)
//			{
//				uint8_t i,t;
//				
//				t = 0;
//				for(i=0;i<4;i++)
//				{
//					t <<= 1;
//					t |= (0x01&(u>>i));
//				}
//				t=~t;
//				t &= 0x0F;
//				if(params.ID != t)
//				{
//					params.ID = t;
//					can_config(); //reset CAN
//				}
//			}
//		}
//	}
//	
//	
////-----DUT ALAMR------------------------------------
//	if(DUT_ALARM)
//	{
//		if(pkey->cn[4] < 10000)
//		{
//			pkey->cn[4]++;
//			if(pkey->cn[4]==9990)
//			{erCode.bit.b0=true;}
//		}	
//	}
//	else
//	{
//		if(pkey->cn[4] > 0)
//		{
//			pkey->cn[4]--;
//			if(pkey->cn[4]==1)
//			{erCode.bit.b0=false;}
//		}
//	}
	
	
}

/***************************************************************************
;** 函数名称:  void KeyValueDispose(void) 
;** 功能描述:  按键处理 
;** 输入参数: 
;** 返 回 值: 
;** 全局变量: 
;** 调用模块: 
;** 作　  者:  M-L-A 
;** 日　  期:  2022-2-14
;** 修改原因：
;** 说    明: 
;***************************************************************************/
void KeyCallback(void)
{	
//	switch(pkey->value)
//	{
//		case 0:break;
//		case KEY_ESC_L:{
//			pkey->f.b.esc=true;
//			if(setups.speak)
//			{
//				if(setups.step)
//				{BuzStart(30,0,1);}
//				else
//				{BuzStart(20,50,3);}
//			}
//		}break;
//		case KEY_ESC_H:{
//			pkey->f.b.esc=false;
//			
//		}break;
//		case KEY_ENTER_L:{
//			pkey->f.b.enter=true;
//			
//			if(!setups.step)
//			{setups.step=1;}
//			
//			if(setups.speak)
//			{BuzStart(30,0,1);}
//			
//		}break;
//		case KEY_ENTER_H:{
//			pkey->f.b.enter=false;
//			
//		}break;
//		case KEY_DOWN_L:{			
//			pkey->f.b.down=true;
//			
//			if(setups.speak)
//			{
//				if(setups.step)
//				{
////					if(setups.lock || setups.scan||(swMes.scc <= 0))
////					{BuzStart(20,50,3);}
////					else
//					{BuzStart(30,0,1);}
//				}
////				else if(setups.lock || setups.scan||(swMes.scc <= 0))	//(swMes.scc <= 0)
////				{BuzStart(20,50,3);}
//				else
//				{BuzStart(30,0,1);}
//			}
//			
//		}break;
//		case KEY_DOWN_H:{
//			pkey->f.b.down=false;
//			
//		}break;
//		case KEY_UP_L:{
//			pkey->f.b.up=true;
//			
//			if(setups.speak)
//			{
//				if(setups.step)
//				{
////					if(setups.lock || setups.scan||(swMes.scc >= swMes.max))
////					{BuzStart(20,50,3);}
////					else
//					{BuzStart(30,0,1);}
//				}
////				else if(setups.lock || setups.scan||(swMes.scc >= swMes.max))	//(swMes.scc >= swMes.max)
////				{BuzStart(20,50,3);}
//				else
//				{BuzStart(30,0,1);}
//			}
//			
//		}break;
//		case KEY_UP_H:{
//			pkey->f.b.up=false;
//			
//		}break;		
//	}
//	if(pkey->value)
//	{
////		printf("key:%d\r\n",pkey->value);
//		pkey->value=0;
//	}
}



