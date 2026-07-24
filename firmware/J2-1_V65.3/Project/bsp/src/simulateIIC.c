
//#include <pulicinclude.h>
#include "simulateIIC.h"

//=========================================================================
uint8_t IICx=0;
uint8_t iicWcmd;
uint8_t iicRcmd;


/***************************************************************************
;** 函数名称: 	
;** 功能描述:  	i2c I/O配置
;** 输入参数: 
;** 返 回 值: 
;** 全局变量: 
;** 调用模块: 
;** 作　  者:   M-L-A
;** 日　  期:  2012-6-29
;** 修改原因：
;** 说    明:
;***************************************************************************/
void swIIC_config(void)
{
	gpio_init_type gpio_init_struct; //定义变量

	crm_periph_clock_enable(CRM_GPIOA_PERIPH_CLOCK, TRUE); //时钟使能
	crm_periph_clock_enable(CRM_GPIOB_PERIPH_CLOCK, TRUE); //时钟使能
	crm_periph_clock_enable(CRM_GPIOC_PERIPH_CLOCK, TRUE); //时钟使能
	crm_periph_clock_enable(CRM_GPIOD_PERIPH_CLOCK, TRUE); //时钟使能
//	crm_periph_clock_enable(CRM_GPIOE_PERIPH_CLOCK, TRUE); //时钟使能
	
	
	gpio_init_struct.gpio_pins = GPIO_EERAM_SCL;	////SCL
	gpio_init_struct.gpio_mode = GPIO_MODE_OUTPUT;
	gpio_init_struct.gpio_pull = GPIO_PULL_UP;
	gpio_init_struct.gpio_out_type = GPIO_OUTPUT_PUSH_PULL;
	gpio_init_struct.gpio_drive_strength = GPIO_DRIVE_STRENGTH_STRONGER;
	gpio_init(GPIOSCL, &gpio_init_struct);
			
	gpio_init_struct.gpio_pins = GPIO_PINS_1|GPIO_PINS_4|GPIO_PINS_6|GPIO_PINS_13|GPIO_PINS_15;	////SCL
	gpio_init(GPIOB, &gpio_init_struct);	
	
//------------------------------------------------------------------------------------------------------------	
	gpio_init_struct.gpio_pins = GPIO_EERAM_SDA;	////SDA
	gpio_init_struct.gpio_mode = GPIO_MODE_INPUT;
	gpio_init_struct.gpio_pull = GPIO_PULL_UP;
	gpio_init_struct.gpio_out_type = GPIO_OUTPUT_PUSH_PULL;
	gpio_init_struct.gpio_drive_strength = GPIO_DRIVE_STRENGTH_STRONGER;
	gpio_init(GPIOSDA, &gpio_init_struct);
	
	gpio_init_struct.gpio_pins = GPIO_PINS_0|GPIO_PINS_3|GPIO_PINS_5|GPIO_PINS_12|GPIO_PINS_14;	////SDA
	gpio_init_struct.gpio_mode = GPIO_MODE_INPUT;
	gpio_init_struct.gpio_pull = GPIO_PULL_UP;
	gpio_init_struct.gpio_out_type = GPIO_OUTPUT_PUSH_PULL;
	gpio_init_struct.gpio_drive_strength = GPIO_DRIVE_STRENGTH_STRONGER;
	gpio_init(GPIOB, &gpio_init_struct);
	
}
/***************************************************************************
;** 函数名称: 	
;** 功能描述:  	SDA 做为输入口
;** 输入参数: 
;** 返 回 值: 
;** 全局变量: 
;** 调用模块: 
;** 作　  者:   M-L-A
;** 日　  期:  2012-6-29
;** 修改原因：
;** 说    明:
;***************************************************************************/
void SDA_IN(void)  
{	
	gpio_init_type gpio_init_struct; //定义变量
	
	switch(IICx)
	{
		case 0:
		{
			gpio_init_struct.gpio_pins = GPIO_EERAM_SDA;	////SDA
			gpio_init_struct.gpio_mode = GPIO_MODE_INPUT;
			gpio_init_struct.gpio_pull = GPIO_PULL_UP;
			gpio_init_struct.gpio_out_type = GPIO_OUTPUT_PUSH_PULL;
			gpio_init_struct.gpio_drive_strength = GPIO_DRIVE_STRENGTH_STRONGER;
			gpio_init(GPIOSDA, &gpio_init_struct);
			iicWcmd = 0xA0;
			iicRcmd = 0xA1;
		}break;	
		case 1:
		{
			gpio_init_struct.gpio_pins = GPIO_PINS_5;	////SDA
			gpio_init_struct.gpio_mode = GPIO_MODE_INPUT;
			gpio_init_struct.gpio_pull = GPIO_PULL_UP;
			gpio_init_struct.gpio_out_type = GPIO_OUTPUT_PUSH_PULL;
			gpio_init_struct.gpio_drive_strength = GPIO_DRIVE_STRENGTH_STRONGER;
			gpio_init(GPIOB, &gpio_init_struct);
		}break;	
		case 2:
		{
			gpio_init_struct.gpio_pins = GPIO_PINS_3;	////SDA
			gpio_init_struct.gpio_mode = GPIO_MODE_INPUT;
			gpio_init_struct.gpio_pull = GPIO_PULL_UP;
			gpio_init_struct.gpio_out_type = GPIO_OUTPUT_PUSH_PULL;
			gpio_init_struct.gpio_drive_strength = GPIO_DRIVE_STRENGTH_STRONGER;
			gpio_init(GPIOB, &gpio_init_struct);
		}break;	
		case 3:
		{
			gpio_init_struct.gpio_pins = GPIO_PINS_14;	////SDA
			gpio_init_struct.gpio_mode = GPIO_MODE_INPUT;
			gpio_init_struct.gpio_pull = GPIO_PULL_UP;
			gpio_init_struct.gpio_out_type = GPIO_OUTPUT_PUSH_PULL;
			gpio_init_struct.gpio_drive_strength = GPIO_DRIVE_STRENGTH_STRONGER;
			gpio_init(GPIOB, &gpio_init_struct);
		}break;	
		case 4:
		{
			gpio_init_struct.gpio_pins = GPIO_PINS_12;	////SDA
			gpio_init_struct.gpio_mode = GPIO_MODE_INPUT;
			gpio_init_struct.gpio_pull = GPIO_PULL_UP;
			gpio_init_struct.gpio_out_type = GPIO_OUTPUT_PUSH_PULL;
			gpio_init_struct.gpio_drive_strength = GPIO_DRIVE_STRENGTH_STRONGER;
			gpio_init(GPIOB, &gpio_init_struct);
		}break;	
		case 5:
		{
			gpio_init_struct.gpio_pins = GPIO_PINS_0;	////SDA
			gpio_init_struct.gpio_mode = GPIO_MODE_INPUT;
			gpio_init_struct.gpio_pull = GPIO_PULL_UP;
			gpio_init_struct.gpio_out_type = GPIO_OUTPUT_PUSH_PULL;
			gpio_init_struct.gpio_drive_strength = GPIO_DRIVE_STRENGTH_STRONGER;
			gpio_init(GPIOB, &gpio_init_struct);
		}break;	
		
	}
}

/***************************************************************************
;** 函数名称: 	
;** 功能描述:  	SDA 做为输出口
;** 输入参数: 
;** 返 回 值: 
;** 全局变量: 
;** 调用模块: 
;** 作　  者:   M-L-A
;** 日　  期:  2012-6-29
;** 修改原因：
;** 说    明:
;***************************************************************************/
void SDA_OUT(void) 
{	
	gpio_init_type gpio_init_struct;  //定义变量
	
	switch(IICx)
	{
		case 0:
		{
			gpio_init_struct.gpio_pins = GPIO_EERAM_SDA;	////SDA
			gpio_init_struct.gpio_mode = GPIO_MODE_OUTPUT;
			gpio_init_struct.gpio_pull = GPIO_PULL_UP;
			gpio_init_struct.gpio_out_type = GPIO_OUTPUT_PUSH_PULL;
			gpio_init_struct.gpio_drive_strength = GPIO_DRIVE_STRENGTH_STRONGER;
			gpio_init(GPIOSDA, &gpio_init_struct);
			iicWcmd = 0xA0;
			iicRcmd = 0xA1;			
		}break;		
		case 1:
		{
			gpio_init_struct.gpio_pins = GPIO_PINS_5;	////SDA
			gpio_init_struct.gpio_mode = GPIO_MODE_OUTPUT;
			gpio_init_struct.gpio_pull = GPIO_PULL_UP;
			gpio_init_struct.gpio_out_type = GPIO_OUTPUT_PUSH_PULL;
			gpio_init_struct.gpio_drive_strength = GPIO_DRIVE_STRENGTH_STRONGER;
			gpio_init(GPIOB, &gpio_init_struct);
		}break;	
		case 2:
		{
			gpio_init_struct.gpio_pins = GPIO_PINS_3;	////SDA
			gpio_init_struct.gpio_mode = GPIO_MODE_OUTPUT;
			gpio_init_struct.gpio_pull = GPIO_PULL_UP;
			gpio_init_struct.gpio_out_type = GPIO_OUTPUT_PUSH_PULL;
			gpio_init_struct.gpio_drive_strength = GPIO_DRIVE_STRENGTH_STRONGER;
			gpio_init(GPIOB, &gpio_init_struct);
		}break;	
		case 3:
		{
			gpio_init_struct.gpio_pins = GPIO_PINS_14;	////SDA
			gpio_init_struct.gpio_mode = GPIO_MODE_OUTPUT;
			gpio_init_struct.gpio_pull = GPIO_PULL_UP;
			gpio_init_struct.gpio_out_type = GPIO_OUTPUT_PUSH_PULL;
			gpio_init_struct.gpio_drive_strength = GPIO_DRIVE_STRENGTH_STRONGER;
			gpio_init(GPIOB, &gpio_init_struct);
		}break;	
		case 4:
		{
			gpio_init_struct.gpio_pins = GPIO_PINS_12;	////SDA
			gpio_init_struct.gpio_mode = GPIO_MODE_OUTPUT;
			gpio_init_struct.gpio_pull = GPIO_PULL_UP;
			gpio_init_struct.gpio_out_type = GPIO_OUTPUT_PUSH_PULL;
			gpio_init_struct.gpio_drive_strength = GPIO_DRIVE_STRENGTH_STRONGER;
			gpio_init(GPIOB, &gpio_init_struct);
		}break;	
		case 5:
		{
			gpio_init_struct.gpio_pins = GPIO_PINS_0;	////SDA
			gpio_init_struct.gpio_mode = GPIO_MODE_OUTPUT;
			gpio_init_struct.gpio_pull = GPIO_PULL_UP;
			gpio_init_struct.gpio_out_type = GPIO_OUTPUT_PUSH_PULL;
			gpio_init_struct.gpio_drive_strength = GPIO_DRIVE_STRENGTH_STRONGER;
			gpio_init(GPIOB, &gpio_init_struct);
		}break;	
		
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
;** 日　  期:  2012-6-29
;** 修改原因：
;** 说    明:
             （2）在SCL为高电平期间，SDA有下降沿的变化
;***************************************************************************/
void Set_IIC_SDA(void)
{
	switch(IICx)
	{
		case 0:gpio_bits_set(GPIOSDA,GPIO_EERAM_SDA);break;
		case 1:gpio_bits_set(GPIOB,GPIO_PINS_5);break;
		case 2:gpio_bits_set(GPIOB,GPIO_PINS_3);break;
		case 3:gpio_bits_set(GPIOB,GPIO_PINS_14);break;
		case 4:gpio_bits_set(GPIOB,GPIO_PINS_12);break;
		case 5:gpio_bits_set(GPIOB,GPIO_PINS_0);break;

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
;** 日　  期:  2012-6-29
;** 修改原因：
;** 说    明:
             （2）在SCL为高电平期间，SDA有下降沿的变化
;***************************************************************************/
void Clr_IIC_SDA(void)
{
	switch(IICx)
	{
		case 0:gpio_bits_reset(GPIOSDA,GPIO_EERAM_SDA);break;
		case 1:gpio_bits_reset(GPIOB,GPIO_PINS_5);break;
		case 2:gpio_bits_reset(GPIOB,GPIO_PINS_3);break;
		case 3:gpio_bits_reset(GPIOB,GPIO_PINS_14);break;
		case 4:gpio_bits_reset(GPIOB,GPIO_PINS_12);break;
		case 5:gpio_bits_reset(GPIOB,GPIO_PINS_0);break;
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
;** 日　  期:  2012-6-29
;** 修改原因：
;** 说    明:
             （2）在SCL为高电平期间，SDA有下降沿的变化
;***************************************************************************/
void Clr_IIC_SCL(void)
{
	switch(IICx)
	{
		case 0:gpio_bits_reset(GPIOSCL,GPIO_EERAM_SCL);break;
		case 1:gpio_bits_reset(GPIOB,GPIO_PINS_6);break;
		case 2:gpio_bits_reset(GPIOB,GPIO_PINS_4);break;
		case 3:gpio_bits_reset(GPIOB,GPIO_PINS_15);break;
		case 4:gpio_bits_reset(GPIOB,GPIO_PINS_13);break;
		case 5:gpio_bits_reset(GPIOB,GPIO_PINS_1);break;

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
;** 日　  期:  2012-6-29
;** 修改原因：
;** 说    明:
             （2）在SCL为高电平期间，SDA有下降沿的变化
;***************************************************************************/
void Set_IIC_SCL(void)
{
	switch(IICx)
	{
		case 0:gpio_bits_set(GPIOSCL,GPIO_EERAM_SCL);break;		
		case 1:gpio_bits_set(GPIOB,GPIO_PINS_6);break;
		case 2:gpio_bits_set(GPIOB,GPIO_PINS_4);break;
		case 3:gpio_bits_set(GPIOB,GPIO_PINS_15);break;
		case 4:gpio_bits_set(GPIOB,GPIO_PINS_13);break;
		case 5:gpio_bits_set(GPIOB,GPIO_PINS_1);break;
				
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
;** 日　  期:  2012-6-29
;** 修改原因：
;** 说    明:
             （2）在SCL为高电平期间，SDA有下降沿的变化
;***************************************************************************/
uint8_t readSDA(void)
{
	uint8_t ck=0;
	switch(IICx)
	{
		case 0:ck=gpio_input_data_bit_read(GPIOSDA,GPIO_EERAM_SDA);break;
		case 1:ck=gpio_input_data_bit_read(GPIOB,GPIO_PINS_5);break;
		case 2:ck=gpio_input_data_bit_read(GPIOB,GPIO_PINS_3);break;
		case 3:ck=gpio_input_data_bit_read(GPIOB,GPIO_PINS_14);break;
		case 4:ck=gpio_input_data_bit_read(GPIOB,GPIO_PINS_12);break;
		case 5:ck=gpio_input_data_bit_read(GPIOB,GPIO_PINS_0);break;
		
	}
	return ck;
}


 /***************************************************************************
;** 函数名称: 	
;** 功能描述:  	i2c start
;** 输入参数: 
;** 返 回 值: 
;** 全局变量: 
;** 调用模块: 
;** 作　  者:   M-L-A
;** 日　  期:  2012-6-29
;** 修改原因：
;** 说    明:（1）首先将SDA配置为输出
             （2）在SCL为高电平期间，SDA有下降沿的变化
;***************************************************************************/
void IIC_Start(void)
{
	 SDA_OUT();     //sda线输出
	 Set_IIC_SDA();      
	 Set_IIC_SCL();
	 delay_us(5);
	 Clr_IIC_SDA(); //START:when CLK is high,DATA change form high to low 
	 delay_us(5);
	 Clr_IIC_SCL(); //钳住I2C总线，准备发送或接收数据 
} 
 /***************************************************************************
;** 函数名称: 	
;** 功能描述:  	i2c Stop
;** 输入参数: 
;** 返 回 值: 
;** 全局变量: 
;** 调用模块: 
;** 作　  者:   M-L-A
;** 日　  期:  2012-6-29
;** 修改原因：
;** 说    明:
  （1）首先将SDA配置为输出
  （2）在SCL为高电平期间，SDA有上升沿的变化
;***************************************************************************/
void IIC_Stop(void)
{
	 SDA_OUT();//sda线输出

	 Clr_IIC_SDA();//STOP:when CLK is high DATA change form low to high
	 Set_IIC_SCL();	 
	 delay_us(5);
	 Set_IIC_SDA();//发送I2C总线结束信号
	 delay_us(5);  
	 Set_IIC_SCL(); 	          
}
 /***************************************************************************
;** 函数名称: 	
;** 功能描述:  	recelve_ ck
;** 输入参数: 
;** 返 回 值: 	1，接收应答失败；0，接收应答成功
;** 全局变量: 
;** 调用模块: 
;** 作　  者:   M-L-A
;** 日　  期:  2012-6-29
;** 修改原因：
;** 说    明:
  （1）首先将SDA配置为输入
  （2）如果返回0，表示接收应答成功；如果为1，接收应答失败
  （3）注意在IIC_STOP()中 ,将SDA置为了输出，所以再满足250条件后，产中IIC停止线号，
    对输出线SDA读SDA输入值是为0的，所以才退出循环。
  （4）此函数为STM32主机等待从机的ACK函数
;***************************************************************************/
 unsigned char IIC_Recelve_Ack(void)
{
	 unsigned int ucErrTime=0;
	
	 SDA_IN();      //SDA设置为输入  
	 Set_IIC_SDA();
	 Clr_IIC_SCL();
	 delay_us(5);    
	 Set_IIC_SCL();
	 delay_us(5);  
	 while(readSDA())  //6T=1us
	 {
		ucErrTime++;
		if(ucErrTime > 8000)   //600/6=100uS
		{
			Clr_IIC_SCL();//时钟输出0
			return 1;
		}
	 }
	 Clr_IIC_SCL();//时钟输出0     
	 return 0;  
} 
/***************************************************************************
;** 函数名称: 	
;** 功能描述:  	ack
;** 输入参数: 
;** 返 回 值: 
;** 全局变量: 
;** 调用模块: 
;** 作　  者:   M-L-A
;** 日　  期:  2012-6-29
;** 修改原因：
;** 说    明:
  （1）首先将SDA配置为输出
  （2）在SCL的一个时钟周期期间，SDA为低 
  （3）此函数为STM32主机向从机发送ACK函数
;***************************************************************************/
void IIC_Ack(void)
{
	 Clr_IIC_SCL();
	 SDA_OUT();
	 Clr_IIC_SDA();
	 delay_us(5);
	 Set_IIC_SCL();
	 delay_us(5);
	 Clr_IIC_SCL();
}
/***************************************************************************
;** 函数名称: 	void IIC_Nack(void)
;** 功能描述:  	Nack  不产生ACK应答	
;** 输入参数: 
;** 返 回 值: 
;** 全局变量: 
;** 调用模块: 
;** 作　  者:   M-L-A
;** 日　  期:  2012-6-29
;** 修改原因：
;** 说    明:
;***************************************************************************/
void IIC_Nack(void)
{
	 Clr_IIC_SCL();
	 SDA_OUT();
	 Set_IIC_SDA();
	 delay_us(5);
	 Set_IIC_SCL();
	 delay_us(5);
	 Clr_IIC_SCL();
}
/***************************************************************************
;** 函数名称: 	
;** 功能描述:  	WRITE BYTE
;** 输入参数: 
;** 返 回 值: 
;** 全局变量: 
;** 调用模块: 
;** 作　  者:   M-L-A
;** 日　  期:  2012-6-29
;** 修改原因：
;** 说    明:
  （1）首先将SDA配置为输出
  （2）在SCL为低电平期间，置位SDA的数据为0或者1，延时后拉高SCL,取走数据，循环8次
;***************************************************************************/
void IIC_WRITE_BYTE(unsigned char txd)
{
    unsigned char  t;  
	 
    SDA_OUT();      
    Clr_IIC_SCL();//拉低时钟开始数据传输
    for(t=0;t<8;t++)
    {              	        
	  if(txd&0x80)	//(((txd&0x80)>>7)==1)  
	  {Set_IIC_SDA();}
	  else 
	  {Clr_IIC_SDA();}
	  txd<<=1;    
	  delay_us(5);   
	  Set_IIC_SCL();
	  delay_us(5); 
	  Clr_IIC_SCL(); 
	  delay_us(5);
    }  
}
/***************************************************************************
;** 函数名称: 	
;** 功能描述:  	Read Byte
;** 输入参数: 
;** 返 回 值: 
;** 全局变量: 
;** 调用模块: 
;** 作　  者:   M-L-A
;** 日　  期:  2012-6-29
;** 修改原因：
;** 说    明:
  （1）首先将SDA配置为输入
  （2）在SCL的一个时钟周期后，读SDA的数据，保存在receive中
  （3）读1个字节，ack=1时，发送ACK，ack=0，发送nACK  
;***************************************************************************/
unsigned char IIC_Read_Byte(unsigned char ack)
{
	unsigned char i,receive=0;

	SDA_IN();//SDA设置为输入
	for(i=0;i<8;i++ )
	{
	  Clr_IIC_SCL(); 
	  delay_us(5);
	  Set_IIC_SCL();
	  delay_us(5);
	  receive<<=1;
	  if(readSDA()==1)
	  {receive|=0x01;}   
	  delay_us(5); 
	}  
    if(ack)
	{IIC_Ack();} //发送ACK   		  	
    else
    {IIC_Nack();}//发送NaCK      
	return receive;
}


/***************************************************************************
;** 函数名称: 	
;** 功能描述:  	写数据
;** 输入参数: 
;** 返 回 值:  0--error; >1--ok
;** 全局变量: 
;** 调用模块: 
;** 作　  者:   M-L-A
;** 日　  期:  2012-6-29
;** 修改原因：
;** 说    明:	 AT24C256 地址：0--32768 
				
;***************************************************************************/
char IIC_Write_Data(unsigned int RomAddress,unsigned char data)
{
	uint8_t  ErrCount=3,result=0,t=0;
	
#if AT24CXXX == 8
	t =RomAddress>>8;
	t=t<<1;
	t=t&0x06;
#endif	
	
	while(ErrCount>0)
	{
		IIC_Start();
		IIC_WRITE_BYTE(iicWcmd|t);	 //写操作   
		if(IIC_Recelve_Ack()==0)  		//判断ACK
		{
#if AT24CXXX > 16
	      IIC_WRITE_BYTE((unsigned char)(RomAddress>>8));	  //写H地址
		  if(IIC_Recelve_Ack()==0)  //判断ACK
	  	  {
#endif
			IIC_WRITE_BYTE((unsigned char)RomAddress);	  //写L地址
			if(IIC_Recelve_Ack()==0)  //判断ACK
			{
				IIC_WRITE_BYTE(data);
			    if(IIC_Recelve_Ack()==0)  //判断ACK
			    {
					result=ErrCount;
					ErrCount=0;
				}
			    else
			    {ErrCount--;}
			}
			else
			{ErrCount--;}	
#if AT24CXXX > 16			
		  }	
		  else
		  {ErrCount--;}
#endif			
		}
		else
		{ErrCount--;}
		IIC_Stop();      //停止
		delay_ms(1);
	}	
	delay_ms(3);
//	OSTimeDlyHMSM(0, 0, 0, 10);	
	delay_us(100);
	
	return result;

}

/***************************************************************************
;** 函数名称: 	
;** 功能描述:  	读数据
;** 输入参数: 
;** 返 回 值: 
;** 全局变量: 
;** 调用模块: 
;** 作　  者:   M-L-A
;** 日　  期:  2012-6-29
;** 修改原因：
;** 说    明:	 AT24C256 地址：0--32768

;***************************************************************************/
unsigned char IIC_Read_Data(unsigned int RomAddress)
{
	unsigned char ErrCount=3,data=0,t=0;

#if AT24CXXX == 8
	t =RomAddress>>8;
	t=t<<1;
	t=t&0x06;
#endif	
	
	while(ErrCount>0)
	{
		IIC_Start();
		IIC_WRITE_BYTE(iicWcmd|t);	 //写操作 
		if(IIC_Recelve_Ack()==0)  		//判断ACK
		{
#if AT24CXXX > 16
			IIC_WRITE_BYTE((unsigned char)(RomAddress>>8));		//写H地址
			if(IIC_Recelve_Ack()==0)  //判断ACK
			{
#endif
				IIC_WRITE_BYTE((unsigned int)RomAddress);		//写L地址
				if(IIC_Recelve_Ack()==0)  //判断ACK
				{
					IIC_Start();
					IIC_WRITE_BYTE(iicRcmd);   //读操作
					if(IIC_Recelve_Ack()==0)  //判断ACK
					{
						data=IIC_Read_Byte(0);
						ErrCount=0;				
					}
					else
					{ErrCount--;}  
				}
				else
				{ErrCount--;} 	
#if AT24CXXX > 16
			}
			else
			{ErrCount--;}
#endif 
		}
		else
	    {ErrCount--;}
		
		IIC_Stop();   //停止
		delay_us(100);
	}
	
	return data;
}
/***************************************************************************
;** 函数名称: 	
;** 功能描述:  	写2byte数据
;** 输入参数: 
;** 返 回 值: 
;** 全局变量: 
;** 调用模块: 
;** 作　  者:   M-L-A
;** 日　  期:  2012-6-29
;** 修改原因：
;** 说    明:	   高位在前，低位在后
;***************************************************************************/
void IIC_Write_2Byte(unsigned int RomAddress, uint16_t udata)
{
	unsigned char i;
		
	for(i=0;i<16;i+=8)
	{
	  IIC_Write_Data(RomAddress,((unsigned char)(udata>>i))); 
	  RomAddress++; 
	}  
}
/***************************************************************************
;** 函数名称: 	
;** 功能描述:  	读2byte数据
;** 输入参数: 
;** 返 回 值: 
;** 全局变量: 
;** 调用模块: 
;** 作　  者:   M-L-A
;** 日　  期:  2012-6-29
;** 修改原因：
;** 说    明:
;***************************************************************************/
uint16_t IIC_Read_2Byte(unsigned int RomAddress)
{
	uint8_t BufData,i;
	uint16_t data=0;
		
	for(i=0;i<16;i+=8)
	{
	  BufData=IIC_Read_Data(RomAddress); 
	  RomAddress++; 
	  data|=((uint16_t)BufData)<<i;
	}
	
	return data;
}
/***************************************************************************
;** 函数名称: 	
;** 功能描述:  	写4byte数据
;** 输入参数: 
;** 返 回 值: 
;** 全局变量: 
;** 调用模块: 
;** 作　  者:   M-L-A
;** 日　  期:  2012-6-29
;** 修改原因：
;** 说    明:	   高位在前，低位在后
;***************************************************************************/
void IIC_Write_4Byte(unsigned int RomAddress,unsigned int udata)	
{		
	unsigned char i;
		
	for(i=0;i<=24;i+=8)
	{
	  IIC_Write_Data(RomAddress,((unsigned char)(udata>>i))); 
	  RomAddress++; 
	}  
}
/***************************************************************************
;** 函数名称: 	
;** 功能描述:  	读4byte数据
;** 输入参数: 
;** 返 回 值: 
;** 全局变量: 
;** 调用模块: 
;** 作　  者:   M-L-A
;** 日　  期:  2012-6-29
;** 修改原因：
;** 说    明:
;***************************************************************************/
unsigned int IIC_Read_4Byte(unsigned int RomAddress)
{
	unsigned char BufData,i;
	unsigned long data=0;
		
	for(i=0;i<=24;i+=8)
	{
	  BufData=IIC_Read_Data(RomAddress); 
	  RomAddress++; 
	  data|=((unsigned long)BufData)<<i;
	}
	return data;
}
/***************************************************************************
;** 函数名称: 	
;** 功能描述:  	写double数据
;** 输入参数: 
;** 返 回 值: 
;** 全局变量: 
;** 调用模块: 
;** 作　  者:   M-L-A
;** 日　  期:  2012-6-29
;** 修改原因：
;** 说    明:	double为 8 byte ,
;***************************************************************************/
char IIC_Write_double(unsigned int RomAddress,double udata)
{
	unsigned char i,er;
	void *p;

	p=&udata;	
	for(i=0;i<sizeof(double);i++)
	{
		er=IIC_Write_Data(RomAddress+i,*((char *)p+i));
		if(er<=0)
		{break;}
	}
	return er;
}
/***************************************************************************
;** 函数名称: 	
;** 功能描述:  	读double数据
;** 输入参数: 
;** 返 回 值: 
;** 全局变量: 
;** 调用模块: 
;** 作　  者:   M-L-A
;** 日　  期:  2012-6-29
;** 修改原因：
;** 说    明:	double为 8 byte ,
;***************************************************************************/
double IIC_Read_double(unsigned int RomAddress)
{
	unsigned char i;
	double data=0.0;
	void *p;

	p=&data;
	for(i=0;i<sizeof(double);i++)
	{*((char *)p+i)=IIC_Read_Data(RomAddress+i);}	
	
	return data;
}
/***************************************************************************
;** 函数名称: 	
;** 功能描述:  	写连续数据模块
;** 输入参数: 
;** 返 回 值: 
;** 全局变量: 
;** 调用模块: 
;** 作　  者:   M-L-A
;** 日　  期:  2012-6-29
;** 修改原因：
;** 说    明:	 高位在前，低位在后
;***************************************************************************/
void IIC_Write_Nbyte(unsigned char *pc,unsigned int Addr,unsigned char number) 
{
	unsigned char i;		
    
	for(i=0;i<number;i++)
	{
		IIC_Write_Data(Addr,pc[i]);
		Addr++;
	}
}
/***************************************************************************
;** 函数名称: 	
;** 功能描述:  	连续读字符模块
;** 输入参数: 
;** 返 回 值: 
;** 全局变量: 
;** 调用模块: 
;** 作　  者:   M-L-A
;** 日　  期:  2012-6-29
;** 修改原因：
;** 说    明:	 AT24C256 地址：0--32768 
;***************************************************************************/
void IIC_Read_Nbyte(unsigned char *pc,unsigned int Addr,unsigned char number) 
{
	unsigned char i;
	
	for(i=0;i<number;i++)
	{
		pc[i]=IIC_Read_Data(Addr);
		Addr++;
	}		
} 
/***************************************************************************
;** 函数名称: 	
;** 功能描述:  	连续读n个双字节
;** 输入参数: 
;** 返 回 值: 
;** 全局变量: 
;** 调用模块: 
;** 作　  者:   M-L-A
;** 日　  期:  2012-6-29
;** 修改原因：
;** 说    明:	 AT24C256 地址：0--32768 
;***************************************************************************/
void IIC_Read_Ntwobyte(uint16_t *pc,unsigned int Addr,unsigned char number) 
{
	uint8_t i,buff1,buff2;
//	uint16_t t;
	
	for(i=0;i<number;i++)
	{
		buff1=0;buff2=0;
		buff1=IIC_Read_Data(Addr); 
		Addr++;
		buff2=IIC_Read_Data(Addr); 
		Addr++;
		pc[i]=(buff2<<8)|buff1;
	}		
} 




