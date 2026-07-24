

#include "InteriorDAC.h"

/***************************************************************************
** 函数名称:  	
** 功能描述:   	 配置DAC 外设 
** 输入参数: 	 无
** 返 回 值: 	 无
** 全局变量: 
** 调用模块: 
** 作　  者:   M-L-A
** 日　  期:   2017-12-10
** 修改原因：
** 说    明:    
;***************************************************************************/
void DAC1_Config(void)
{
	gpio_init_type gpio_init_struct;
	/* enable dac/gpioa clock */
	crm_periph_clock_enable(CRM_DAC_PERIPH_CLOCK, TRUE);
	crm_periph_clock_enable(CRM_GPIOA_PERIPH_CLOCK, TRUE);
	
	gpio_init_struct.gpio_pins = GPIO_PINS_4;
	gpio_init_struct.gpio_mode = GPIO_MODE_ANALOG;
	gpio_init_struct.gpio_out_type = GPIO_OUTPUT_PUSH_PULL;
	gpio_init_struct.gpio_pull = GPIO_PULL_NONE;
	gpio_init_struct.gpio_drive_strength = GPIO_DRIVE_STRENGTH_STRONGER;
	gpio_init(GPIOA, &gpio_init_struct);
	
	/* dac1 configuration */
	dac_trigger_select(DAC1_SELECT, DAC_SOFTWARE_TRIGGER);
	dac_trigger_enable(DAC1_SELECT, TRUE);
	dac_wave_generate(DAC1_SELECT, DAC_WAVE_GENERATE_NONE);
	dac_mask_amplitude_select(DAC1_SELECT, DAC_LSFR_BITB0_AMPLITUDE_4095);
	dac_output_buffer_enable(DAC1_SELECT, FALSE);	
	dac_enable(DAC1_SELECT, TRUE);
  
}

/***************************************************************************
** 函数名称:  	
** 功能描述:   	 配置DAC 外设 
** 输入参数: 	 无
** 返 回 值: 	 无
** 全局变量: 
** 调用模块: 
** 作　  者:   M-L-A
** 日　  期:   2017-12-10
** 修改原因：
** 说    明:    
;***************************************************************************/
void DAC2_Config(void)
{

}


/***************************************************************************
** 函数名称:  	
** 功能描述:  	 DAC1 定时器初始化
** 输入参数: 	 无
** 返 回 值: 	 无
** 全局变量: 
** 调用模块: 
** 作　  者:   M-L-A
** 日　  期:   2013-5-21
** 修改原因：
** 说    明:    FSMC 影响PB7
;***************************************************************************/
void DAC1_TIM_Initil(double divfreq)
{	
//	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
//	TIM_OCInitTypeDef        TIM_OCInitStructure;
//	  	
//	uint8_t  i;
//	double   dd=0.0,ck;

//	dd=72000000;							
//	i=0;				  
//	ck=0.0;
//	do 
//	{
//		i++;		//取出分频系数
//		ck=dd/divfreq;
//		ck=ck/i;	  
//	}while(ck>60000.0);
//	if(i>=1)
//	{i=i-1;}
//	if(ck>1)
//	{ck=ck-1;}
//	
//	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM6, ENABLE);   	  //使能TIM4的时钟	
//	TIM_DeInit(TIM6);	                      //复位时钟TIM2，恢复到初始状态	
//	/*-------------------------------------------------------------------
//	TIM3CLK=72MHz  预分频系数Prescaler=2 经过分频 定时器时钟为24MHz
//	根据公式 通道输出占空比=TIM4_CCR2/(TIM_Period+1),可以得到TIM_Pulse的计数值	 
//	捕获/比较寄存器2 TIM4_CCR2= CCR1_Val 	 
//	 T= fCK/TIM_Prescaler-1/TIM_Period   
//	-------------------------------------------------------------------*/
//	TIM_TimeBaseStructure.TIM_Prescaler = i;		          //预分频器TIM4_PSC=3 计数器的时钟频率CK_CNT等于fCK_PSC/(PSC[15:0]+1)。
//	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;	  //计数器向上计数模式 TIM4_CR1[4]=0
//	TIM_TimeBaseStructure.TIM_Period = ck;			          //自动重装载寄存器TIM4_APR  确定频率为1KHz 
//	TIM_TimeBaseStructure.TIM_ClockDivision = 0x0;				  //时钟分频因子 TIM4_CR1[9:8]=00
//	TIM_TimeBaseStructure.TIM_RepetitionCounter = 0x0;
//	TIM_TimeBaseInit(TIM6,&TIM_TimeBaseStructure);				  //写TIM6各寄存器参数
//	
//    TIM_SelectOutputTrigger(TIM6, TIM_TRGOSource_Update);
//	
////	TIM_Cmd(TIM6,ENABLE);
	
}
/***************************************************************************
** 函数名称:  	
** 功能描述:  	 DAC2 定时器初始化
** 输入参数: 	 无
** 返 回 值: 	 无
** 全局变量: 
** 调用模块: 
** 作　  者:   M-L-A
** 日　  期:   2013-5-21
** 修改原因：
** 说    明:    FSMC 影响PB7
;***************************************************************************/
void DAC2_TIM_Initil(double divfreq)
{	
//	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
//	TIM_OCInitTypeDef        TIM_OCInitStructure;
//	  	
//	uint8_t  i;
//	double  dd=0.0,ck;

//	dd=72000000;							
//	i=0;				  
//	ck=0.0;
//	do 
//	{
//		i++;		//取出分频系数
//		ck=dd/divfreq;
//		ck=ck/i;	  
//	}while(ck>60000.0);
//	if(i>=1)
//	{i=i-1;}
//	if(ck>1)
//	{ck=ck-1;}
//	
//	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM7, ENABLE);   	  //使能TIM4的时钟	
//	TIM_DeInit(TIM7);	                      //复位时钟TIM2，恢复到初始状态	
//	/*-------------------------------------------------------------------
//	TIM3CLK=72MHz  预分频系数Prescaler=2 经过分频 定时器时钟为24MHz
//	根据公式 通道输出占空比=TIM4_CCR2/(TIM_Period+1),可以得到TIM_Pulse的计数值	 
//	捕获/比较寄存器2 TIM4_CCR2= CCR1_Val 	 
//	 T= fCK/TIM_Prescaler-1/TIM_Period   
//	-------------------------------------------------------------------*/
//	TIM_TimeBaseStructure.TIM_Prescaler = i;		          //预分频器TIM4_PSC=3 计数器的时钟频率CK_CNT等于fCK_PSC/(PSC[15:0]+1)。
//	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;	  //计数器向上计数模式 TIM4_CR1[4]=0
//	TIM_TimeBaseStructure.TIM_Period = ck;			          //自动重装载寄存器TIM4_APR  确定频率为1KHz 
//	TIM_TimeBaseStructure.TIM_ClockDivision = 0x0;				  //时钟分频因子 TIM4_CR1[9:8]=00
//	TIM_TimeBaseStructure.TIM_RepetitionCounter = 0x0;
//	TIM_TimeBaseInit(TIM7,&TIM_TimeBaseStructure);				  //写TIM6各寄存器参数
//	 
//    TIM_SelectOutputTrigger(TIM7, TIM_TRGOSource_Update);
//////	TIM_Cmd(TIM7,ENABLE);

}
/***************************************************************************
;** 函数名称:  
;** 功能描述:  
;** 输入参数:  无
;** 返 回 值: 
;** 全局变量: 
;** 调用模块: 
;** 作　  者:   
;** 日　  期:  2017-10-18
;** 修改原因：
;** 说    明:

;***************************************************************************/
void DAC1_StartDMA(uint16_t Sample_Number)                                                 
{
#ifdef DAC_ENABLE_1
    DMA_InitTypeDef DMA_InitStructure;                                  /* DMA 数据结构 */

	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA2, ENABLE);

    DMA_DeInit(DMA2_Channel3);
    DMA_InitStructure.DMA_PeripheralBaseAddr = DAC_DHR12R1_Address;
    DMA_InitStructure.DMA_MemoryBaseAddr = (uint32_t)&DAC1_Buffer;
    DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralDST;
    DMA_InitStructure.DMA_BufferSize = Sample_Number;
    DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
    DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;
    DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord;
    DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord;
    DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;
    DMA_InitStructure.DMA_Priority = DMA_Priority_High;
    DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;
    DMA_Init(DMA2_Channel3, &DMA_InitStructure);

    DMA_Cmd(DMA2_Channel3, ENABLE);
    DAC_DMACmd(DAC_Channel_1, ENABLE);
	
	TIM_Cmd(TIM6,ENABLE); /* 开始采样 */
#endif
}
/***************************************************************************
;** 函数名称:  
;** 功能描述:  
;** 输入参数:  无
;** 返 回 值: 
;** 全局变量: 
;** 调用模块: 
;** 作　  者:   
;** 日　  期:  2017-10-18
;** 修改原因：
;** 说    明:

;***************************************************************************/
void DAC2_StartDMA(uint16_t Sample_Number) 
{
#ifdef DAC_ENABLE_2
    DMA_InitTypeDef DMA_InitStructure;                                  /* DMA 数据结构 */
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA2, ENABLE);

    DMA_DeInit(DMA2_Channel4);
    DMA_InitStructure.DMA_PeripheralBaseAddr = DAC_DHR12R2_Address;
    DMA_InitStructure.DMA_MemoryBaseAddr = (uint32_t)&DAC2_Buffer;
    DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralDST;
    DMA_InitStructure.DMA_BufferSize = Sample_Number;
    DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
    DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;
    DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord;
    DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord;
    DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;
    DMA_InitStructure.DMA_Priority = DMA_Priority_High;
    DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;
    DMA_Init(DMA2_Channel4, &DMA_InitStructure);

    DMA_Cmd(DMA2_Channel4, ENABLE);
    DAC_DMACmd(DAC_Channel_2, ENABLE);
	
#endif	
}

/***************************************************************************
;** 函数名称:  
;** 功能描述:  
;** 输入参数:  amp
;** 返 回 值: 
;** 全局变量: 
;** 调用模块: 
;** 作　  者:   
;** 日　  期:  2017-10-18
;** 修改原因：
;** 说    明:

//DAC输出频率=72M/DAC1_BUFFER_SIZE/定时器频率 ；
//定时器重装数值=72M/DAC1_BUFFER_SIZE/DAC输出频率-1
//定时器的频率=DAC输出频率 * DAC1_BUFFER_SIZE;

//y=sin(2*3.1415926/DAC1_BUFFER_SIZE*i)正弦函数 ;2047是1.65V中点电压值；

frq<=10khz
amp<=2047

;***************************************************************************/
void DAC1_StartSineWave(float frq,float amp)
{
#ifdef DAC_ENABLE_1
	
	uint16_t i;
		
	DAC1_TIM_Initil(frq*DAC1_BUFFER_SIZE);	
		
	for (i=0; i<DAC1_BUFFER_SIZE; i++) 
	{
        DAC1_Buffer[i]= (uint16_t)(amp* sin(i*6.2832/(float)DAC1_BUFFER_SIZE) + 2047);     
    }
	DAC1_StartDMA(DAC1_BUFFER_SIZE);
	TIM_Cmd(TIM6,ENABLE); //output
	
#endif
}

/***************************************************************************
;** 函数名称:  
;** 功能描述:  
;** 输入参数:  amp
;** 返 回 值: 
;** 全局变量: 
;** 调用模块: 
;** 作　  者:   
;** 日　  期:  2017-10-18
;** 修改原因：
;** 说    明:

//DAC输出频率=72M/DAC1_BUFFER_SIZE/定时器频率 ；
//定时器重装数值=72M/DAC1_BUFFER_SIZE/DAC输出频率-1
//定时器的频率=DAC输出频率 * DAC1_BUFFER_SIZE;

//y=sin(2*3.1415926/DAC1_BUFFER_SIZE*i)正弦函数 ;2047是1.65V中点电压值；

frq<=10khz
amp<=2047

;***************************************************************************/
void DAC2_StartSineWave(float frq,float amp)
{
#ifdef DAC_ENABLE_2
	uint16_t i;
	
	DAC2_TIM_Initil(frq*DAC2_BUFFER_SIZE);	
		
	for (i=0; i<DAC2_BUFFER_SIZE; i++) 
	{
        DAC2_Buffer[i]= (uint16_t)((amp*2047/1.65/2)* sin(6.2832*i/DAC2_BUFFER_SIZE) + 2047);     
    }
	DAC2_StartDMA(DAC2_BUFFER_SIZE);
	TIM_Cmd(TIM7,ENABLE); //output
	
#endif
	
}

/***************************************************************************
;** 函数名称:  
;** 功能描述:  
;** 输入参数:  无
;** 返 回 值: 
;** 全局变量: 
;** 调用模块: 
;** 作　  者:   
;** 日　  期:  2017-10-18
;** 修改原因：
;** 说    明:

;***************************************************************************/
void DAC1_Stop(void)
{
//    TIM_Cmd(TIM6, DISABLE);
} 
/***************************************************************************
;** 函数名称:  
;** 功能描述:  
;** 输入参数:  无
;** 返 回 值: 
;** 全局变量: 
;** 调用模块: 
;** 作　  者:   
;** 日　  期:  2017-10-18
;** 修改原因：
;** 说    明:

;***************************************************************************/
void DAC2_Stop(void)
{
//	GPIO_ResetBits(GPIOA,GPIO_Pin_5);
//	TIM_Cmd(TIM7, DISABLE);
} 

/***************************************************************************
;** 函数名称:  
;** 功能描述:  
;** 输入参数:  无
;** 返 回 值: 
;** 全局变量: 
;** 调用模块: 
;** 作　  者:   
;** 日　  期:  2017-10-18
;** 修改原因：
;** 说    明:

;***************************************************************************/
void SetOutputVoltageDAC1(uint16_t d)
{
//	uint16_t d;
		
//	v=(v-1.21)/6.0;
//	d = (uint16_t)(v*4095/3.299);
	dac_1_data_set(DAC1_12BIT_RIGHT,d);
	dac_output_buffer_enable(DAC1_SELECT, TRUE);
	dac_software_trigger_generate(DAC1_SELECT);
}

/***************************************************************************
;** 函数名称:  
;** 功能描述:  
;** 输入参数:  无
;** 返 回 值: 
;** 全局变量: 
;** 调用模块: 
;** 作　  者:   
;** 日　  期:  2017-10-18
;** 修改原因：
;** 说    明:

;***************************************************************************/
void SetOutputVoltageDAC2(float v)
{
//	uint16_t d;
//	
//	v=(v-0.14)/4.0;
//	d = (int)(v*4095/3.3);
//	DAC_SetChannel2Data(DAC_Align_12b_R,d);  

}

	   
	   
	   
	   
	   
