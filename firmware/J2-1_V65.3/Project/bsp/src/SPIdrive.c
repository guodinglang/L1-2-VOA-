

#include "SPIdrive.h"

/***************************************************************************
;** 函数名称:  	
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
void SPI1_Config(void)
{	 
	gpio_init_type gpio_initstructure;
//	dma_init_type dma_init_struct;
	spi_init_type spi_init_struct;
	
	crm_periph_clock_enable(CRM_GPIOA_PERIPH_CLOCK, TRUE);
//	crm_periph_clock_enable(CRM_DMA1_PERIPH_CLOCK, TRUE);
	
	/* master sck pin */
	gpio_initstructure.gpio_out_type       = GPIO_OUTPUT_PUSH_PULL;
	gpio_initstructure.gpio_pull           = GPIO_PULL_DOWN;
	gpio_initstructure.gpio_mode           = GPIO_MODE_MUX;
	gpio_initstructure.gpio_drive_strength = GPIO_DRIVE_STRENGTH_STRONGER;
	gpio_initstructure.gpio_pins           = GPIO_PINS_5;
	gpio_init(GPIOA, &gpio_initstructure);

	/* master miso pin */
	gpio_initstructure.gpio_pull           = GPIO_PULL_DOWN;
	gpio_initstructure.gpio_mode           = GPIO_MODE_INPUT;
	gpio_initstructure.gpio_pins           = GPIO_PINS_6;
	gpio_init(GPIOA, &gpio_initstructure);

	/* master mosi pin */
	gpio_initstructure.gpio_pull           = GPIO_PULL_DOWN;
	gpio_initstructure.gpio_mode           = GPIO_MODE_MUX;
	gpio_initstructure.gpio_pins           = GPIO_PINS_7;
	gpio_init(GPIOA, &gpio_initstructure);

	/* master cs pin */
	gpio_initstructure.gpio_pull           = GPIO_PULL_UP;
	gpio_initstructure.gpio_mode           = GPIO_MODE_OUTPUT;	//GPIO_MODE_MUX;
	gpio_initstructure.gpio_pins           = GPIO_PINS_4;
	gpio_init(GPIOA, &gpio_initstructure);
	gpio_bits_set(GPIOA,GPIO_PINS_4);
//----------------------------------------------------------------------------------------  
//	dma_reset(DMA1_CHANNEL3);
//	dma_default_para_init(&dma_init_struct);
//	dma_init_struct.buffer_size = BUFFER_SIZE;
//	dma_init_struct.direction = DMA_DIR_PERIPHERAL_TO_MEMORY;
//	dma_init_struct.memory_base_addr = (uint32_t)&level[0].xp;
//	dma_init_struct.memory_data_width = DMA_MEMORY_DATA_WIDTH_BYTE;
//	dma_init_struct.memory_inc_enable = TRUE;
//	dma_init_struct.peripheral_base_addr = (uint32_t)(&SPI1->dt);
//	dma_init_struct.peripheral_data_width = DMA_PERIPHERAL_DATA_WIDTH_HALFWORD;
//	dma_init_struct.peripheral_inc_enable = FALSE;
//	dma_init_struct.priority = DMA_PRIORITY_MEDIUM;
//	dma_init_struct.loop_mode_enable = FALSE;
//	dma_init(DMA1_CHANNEL3, &dma_init_struct);

	crm_periph_clock_enable(CRM_SPI1_PERIPH_CLOCK, TRUE);
	spi_default_para_init(&spi_init_struct);
	spi_init_struct.transmission_mode = SPI_TRANSMIT_FULL_DUPLEX;//SPI_TRANSMIT_HALF_DUPLEX_TX;
	spi_init_struct.master_slave_mode = SPI_MODE_MASTER;
	spi_init_struct.mclk_freq_division = SPI_MCLK_DIV_16;
	spi_init_struct.first_bit_transmission = SPI_FIRST_BIT_MSB;
	spi_init_struct.frame_bit_num = SPI_FRAME_8BIT;	//SPI_FRAME_16BIT;
	spi_init_struct.clock_polarity = SPI_CLOCK_POLARITY_HIGH;	//SPI_CLOCK_POLARITY_LOW;
	spi_init_struct.clock_phase = SPI_CLOCK_PHASE_2EDGE;
	spi_init_struct.cs_mode_selection = SPI_CS_SOFTWARE_MODE;	//SPI_CS_HARDWARE_MODE;//	
	spi_init(SPI1, &spi_init_struct);
	
//	spi_hardware_cs_output_enable(SPI1,TRUE);
//	spi_software_cs_internal_level_set(SPI1,SPI_SWCS_INTERNAL_LEVEL_HIGHT);
//	spi_i2s_dma_receiver_enable(SPI2, TRUE);
	spi_enable(SPI1, TRUE);
//	dma_channel_enable(DMA1_CHANNEL3, TRUE);

  
}

/***************************************************************************
;** 函数名称:  	SPI_ReadWriteByte
;** 功能描述:   SPI读写N个字节（发送完成后返回本次通讯读取的数据）
;** 输入参数: 	uint8_t TxData 待发送的数
;** 返 回 值: 	
;** 优 先 级：  
;** 全局变量: 
;** 调用模块: 
;** 作　  者:   M-L-A
;** 日　  期:   2017-12-27
;** 修改原因：
;** 说    明:    
;***************************************************************************/ 
void SPI1_Write_Nbyte(uint16_t *wd, uint8_t num)
{ 
//	uint8_t i;
//	uint32_t e;
//	
//	for(i=0;i<num;i++)
//	{
////		DAC_CS(1);	//20nS enable DAC
//		delay_us(1);
//		DAC_CS(0);
//		
//		e=1800000;	//100ms
//		while(spi_i2s_flag_get(SPI1, SPI_I2S_TDBE_FLAG) == RESET)
//		{
//			if(e>0){e--;}
//			else{ALARM(1);}
//		}
//		spi_i2s_data_transmit(SPI1, wd[i]);
//		
//		e=1800000;	//100ms
//		while(spi_i2s_flag_get(SPI1, SPI_I2S_RDBF_FLAG) == RESET)
//		{
//			if(e>0){e--;}
//			else{ALARM(1);}
//		}
//		e = spi_i2s_data_receive(SPI1);	
//		delay_us(1);
//	}

}

/***************************************************************************
;** 函数名称:  	SPI2_Config
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
void SPI2_Config(void)
{	 
	gpio_init_type gpio_initstructure;
//	dma_init_type dma_init_struct;
	spi_init_type spi_init_struct;
	
	crm_periph_clock_enable(CRM_GPIOB_PERIPH_CLOCK, TRUE);
//	crm_periph_clock_enable(CRM_DMA1_PERIPH_CLOCK, TRUE);
	
	/* master sck pin */
	gpio_initstructure.gpio_out_type       = GPIO_OUTPUT_PUSH_PULL;
	gpio_initstructure.gpio_pull           = GPIO_PULL_DOWN;
	gpio_initstructure.gpio_mode           = GPIO_MODE_MUX;
	gpio_initstructure.gpio_drive_strength = GPIO_DRIVE_STRENGTH_STRONGER;
	gpio_initstructure.gpio_pins           = GPIO_PINS_13;
	gpio_init(GPIOB, &gpio_initstructure);

	/* master miso pin */
	gpio_initstructure.gpio_pull           = GPIO_PULL_DOWN;
	gpio_initstructure.gpio_mode           = GPIO_MODE_INPUT;
	gpio_initstructure.gpio_pins           = GPIO_PINS_14;
	gpio_init(GPIOB, &gpio_initstructure);

	/* master mosi pin */
	gpio_initstructure.gpio_pull           = GPIO_PULL_DOWN;
	gpio_initstructure.gpio_mode           = GPIO_MODE_MUX;
	gpio_initstructure.gpio_pins           = GPIO_PINS_15;
	gpio_init(GPIOB, &gpio_initstructure);

	/* master cs pin */
	gpio_initstructure.gpio_pull           = GPIO_PULL_UP;
	gpio_initstructure.gpio_mode           = GPIO_MODE_OUTPUT;//GPIO_MODE_MUX;
	gpio_initstructure.gpio_pins           = GPIO_PINS_12;
	gpio_init(GPIOB, &gpio_initstructure);
	
//----------------------------------------------------------------------------------------  
//	dma_reset(DMA1_CHANNEL3);
//	dma_default_para_init(&dma_init_struct);
//	dma_init_struct.buffer_size = BUFFER_SIZE;
//	dma_init_struct.direction = DMA_DIR_PERIPHERAL_TO_MEMORY;
//	dma_init_struct.memory_base_addr = (uint32_t)&level[0].xp;
//	dma_init_struct.memory_data_width = DMA_MEMORY_DATA_WIDTH_BYTE;
//	dma_init_struct.memory_inc_enable = TRUE;
//	dma_init_struct.peripheral_base_addr = (uint32_t)(&SPI1->dt);
//	dma_init_struct.peripheral_data_width = DMA_PERIPHERAL_DATA_WIDTH_HALFWORD;
//	dma_init_struct.peripheral_inc_enable = FALSE;
//	dma_init_struct.priority = DMA_PRIORITY_MEDIUM;
//	dma_init_struct.loop_mode_enable = FALSE;
//	dma_init(DMA1_CHANNEL3, &dma_init_struct);

	crm_periph_clock_enable(CRM_SPI2_PERIPH_CLOCK, TRUE);
	spi_default_para_init(&spi_init_struct);
	spi_init_struct.transmission_mode = SPI_TRANSMIT_FULL_DUPLEX;//SPI_TRANSMIT_HALF_DUPLEX_TX;
	spi_init_struct.master_slave_mode = SPI_MODE_MASTER;
	spi_init_struct.mclk_freq_division = SPI_MCLK_DIV_16;
	spi_init_struct.first_bit_transmission = SPI_FIRST_BIT_MSB;
	spi_init_struct.frame_bit_num = SPI_FRAME_16BIT;
	spi_init_struct.clock_polarity = SPI_CLOCK_POLARITY_HIGH;	//SPI_CLOCK_POLARITY_LOW;
	spi_init_struct.clock_phase = SPI_CLOCK_PHASE_2EDGE;
	spi_init_struct.cs_mode_selection = SPI_CS_SOFTWARE_MODE;	//SPI_CS_HARDWARE_MODE;//	
	spi_init(SPI2, &spi_init_struct);
	
//	spi_hardware_cs_output_enable(SPI1,TRUE);
//	spi_software_cs_internal_level_set(SPI1,SPI_SWCS_INTERNAL_LEVEL_HIGHT);
//	spi_i2s_dma_receiver_enable(SPI2, TRUE);
	spi_enable(SPI2, TRUE);
//	dma_channel_enable(DMA1_CHANNEL3, TRUE);


}
/***************************************************************************
;** 函数名称:  	SPI4_Config
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
void SPI4_Config(void)
{	 
	gpio_init_type gpio_initstructure;
//	dma_init_type dma_init_struct;
	spi_init_type spi_init_struct;
	
	crm_periph_clock_enable(CRM_GPIOE_PERIPH_CLOCK, TRUE);
//	crm_periph_clock_enable(CRM_DMA1_PERIPH_CLOCK, TRUE);
	
//	gpio_pin_remap_config(SPI4_GMUX_0001,TRUE);
	/* master sck pin */
	gpio_initstructure.gpio_out_type       = GPIO_OUTPUT_PUSH_PULL;
	gpio_initstructure.gpio_pull           = GPIO_PULL_DOWN;
	gpio_initstructure.gpio_mode           = GPIO_MODE_MUX;
	gpio_initstructure.gpio_drive_strength = GPIO_DRIVE_STRENGTH_STRONGER;
	gpio_initstructure.gpio_pins           = GPIO_PINS_2;
	gpio_init(GPIOE, &gpio_initstructure);

	/* master miso pin */
	gpio_initstructure.gpio_pull           = GPIO_PULL_UP;
	gpio_initstructure.gpio_mode           = GPIO_MODE_INPUT;
	gpio_initstructure.gpio_pins           = GPIO_PINS_5;
	gpio_init(GPIOE, &gpio_initstructure);

	/* master mosi pin */
	gpio_initstructure.gpio_pull           = GPIO_PULL_UP;
	gpio_initstructure.gpio_mode           = GPIO_MODE_MUX;
	gpio_initstructure.gpio_pins           = GPIO_PINS_6;
	gpio_init(GPIOE, &gpio_initstructure);

	/* master cs pin */
	gpio_initstructure.gpio_pull           = GPIO_PULL_UP;
	gpio_initstructure.gpio_mode           = GPIO_MODE_OUTPUT;//GPIO_MODE_MUX;
	gpio_initstructure.gpio_pins           = GPIO_PINS_4;
	gpio_init(GPIOE, &gpio_initstructure);
	gpio_bits_set(GPIOE,GPIO_PINS_4);
	
//----------------------------------------------------------------------------------------  
//	dma_reset(DMA1_CHANNEL3);
//	dma_default_para_init(&dma_init_struct);
//	dma_init_struct.buffer_size = BUFFER_SIZE;
//	dma_init_struct.direction = DMA_DIR_PERIPHERAL_TO_MEMORY;
//	dma_init_struct.memory_base_addr = (uint32_t)&level[0].xp;
//	dma_init_struct.memory_data_width = DMA_MEMORY_DATA_WIDTH_BYTE;
//	dma_init_struct.memory_inc_enable = TRUE;
//	dma_init_struct.peripheral_base_addr = (uint32_t)(&SPI1->dt);
//	dma_init_struct.peripheral_data_width = DMA_PERIPHERAL_DATA_WIDTH_HALFWORD;
//	dma_init_struct.peripheral_inc_enable = FALSE;
//	dma_init_struct.priority = DMA_PRIORITY_MEDIUM;
//	dma_init_struct.loop_mode_enable = FALSE;
//	dma_init(DMA1_CHANNEL3, &dma_init_struct);

	crm_periph_clock_enable(CRM_SPI4_PERIPH_CLOCK, TRUE);
	spi_default_para_init(&spi_init_struct);
	spi_init_struct.transmission_mode = SPI_TRANSMIT_FULL_DUPLEX;//SPI_TRANSMIT_HALF_DUPLEX_TX;
	spi_init_struct.master_slave_mode = SPI_MODE_MASTER;
	spi_init_struct.mclk_freq_division = SPI_MCLK_DIV_8;
	spi_init_struct.first_bit_transmission = SPI_FIRST_BIT_MSB;
	spi_init_struct.frame_bit_num = SPI_FRAME_8BIT;
	spi_init_struct.clock_polarity = SPI_CLOCK_POLARITY_HIGH;//SPI_CLOCK_POLARITY_LOW;	
	spi_init_struct.clock_phase = SPI_CLOCK_PHASE_2EDGE;
	spi_init_struct.cs_mode_selection = SPI_CS_SOFTWARE_MODE;	//SPI_CS_HARDWARE_MODE;//	
	spi_init(SPI4, &spi_init_struct);
	
//	spi_hardware_cs_output_enable(SPI1,TRUE);
//	spi_software_cs_internal_level_set(SPI1,SPI_SWCS_INTERNAL_LEVEL_HIGHT);
//	spi_i2s_dma_receiver_enable(SPI2, TRUE);
	spi_enable(SPI4, TRUE);
//	dma_channel_enable(DMA1_CHANNEL3, TRUE);

}

/***************************************************************************
;** 函数名称:  	SPI2_Config
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
uint8_t spi_read_send_byte(uint8_t d)
{
	while(spi_i2s_flag_get(SPI2, SPI_I2S_TDBE_FLAG) == RESET);
	spi_i2s_data_transmit(SPI2, d);
	while(spi_i2s_flag_get(SPI2, SPI_I2S_RDBF_FLAG) == RESET);
	return (uint8_t)spi_i2s_data_receive(SPI2);	
}

/***************************************************************************
;** 函数名称:  	SPI2_Config
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
uint8_t spi4_wrByte(uint8_t d)
{
	while(spi_i2s_flag_get(SPI4, SPI_I2S_TDBE_FLAG) == RESET);
	spi_i2s_data_transmit(SPI4, d);
	while(spi_i2s_flag_get(SPI4, SPI_I2S_RDBF_FLAG) == RESET);
	
	return (uint8_t)spi_i2s_data_receive(SPI4);	
}


/***************************************************************************
;** 函数名称:  	cs_low
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
void cs_low(void)
{
	gpio_bits_reset(GPIOB,GPIO_PINS_12);
}
/***************************************************************************
;** 函数名称:  	cs_high
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
void cs_high(void)
{
	gpio_bits_set(GPIOB,GPIO_PINS_12);
}
