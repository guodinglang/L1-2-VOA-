


#include "InsideCAN.h"

//===================================================
uint8_t  target_id = 0;
uint32_t can_res = 0;


/***************************************************************************
;** 函数名称: 	
;** 功能描述:  	
;** 输入参数: 
;** 返 回 值: 
;** 全局变量: 
;** 调用模块: 
;** 作　  者:   M-L-A
;** 日　  期:  2024-3-6
;** 修改原因：
;** 说    明: 	

ID： 从MSB开始，禁止高7位都为隐性，即不能ID=1111111XXXX;
RTR: 0-数据帧；1-遥控帧；
SRR: 替代远程请求位；设置为1；
IDE: 0-标准帧；1-扩展帧；


;***************************************************************************/
void can_config(void)
{
	gpio_init_type gpio_init_struct;
	can_base_type can_base_struct;
	can_baudrate_type can_baudrate_struct;
	can_filter_init_type can_filter_init_struct;
	
	uint32_t i;
	
	crm_periph_clock_enable(CRM_GPIOA_PERIPH_CLOCK, TRUE);
	crm_periph_clock_enable(CRM_IOMUX_PERIPH_CLOCK, TRUE);
	//  gpio_pin_remap_config(CAN1_GMUX_0010,TRUE);

	gpio_default_para_init(&gpio_init_struct);
	/* can tx pin */
	gpio_init_struct.gpio_drive_strength = GPIO_DRIVE_STRENGTH_STRONGER;
	gpio_init_struct.gpio_out_type = GPIO_OUTPUT_PUSH_PULL;
	gpio_init_struct.gpio_mode = GPIO_MODE_MUX;
	gpio_init_struct.gpio_pins = GPIO_PINS_12;//9;
	gpio_init_struct.gpio_pull = GPIO_PULL_NONE;
	gpio_init(GPIOA, &gpio_init_struct);
	/* can rx pin */
	gpio_init_struct.gpio_drive_strength = GPIO_DRIVE_STRENGTH_STRONGER;
	gpio_init_struct.gpio_mode = GPIO_MODE_INPUT;
	gpio_init_struct.gpio_pins = GPIO_PINS_11;//8;
	gpio_init_struct.gpio_pull = GPIO_PULL_UP;
	gpio_init(GPIOA, &gpio_init_struct);
	
//------------------------------------------------------------------------------------------------

	crm_periph_clock_enable(CRM_CAN1_PERIPH_CLOCK, TRUE);
	/* can base init */
	can_default_para_init(&can_base_struct);
	can_base_struct.mode_selection = CAN_MODE_COMMUNICATE;
	can_base_struct.ttc_enable = FALSE; //时间触发通信模式使能
	can_base_struct.aebo_enable = TRUE;	//自动退出离线状态使能
	can_base_struct.aed_enable = TRUE;	//自动退出睡眠模式使能
	can_base_struct.prsf_enable = FALSE; //发送失败时禁止重传使能 0-重传，1-不重传
	can_base_struct.mdrsel_selection = CAN_DISCARDING_FIRST_RECEIVED;
	can_base_struct.mmssr_selection = CAN_SENDING_BY_ID;
	can_base_init(CAN1, &can_base_struct);

	/* can baudrate, set baudrate = pclk/(baudrate_div *(1 + bts1_size + bts2_size)) */
	can_baudrate_struct.baudrate_div = 20; 			//120mhz/240 = 500KHZ
	can_baudrate_struct.rsaw_size = CAN_RSAW_3TQ;
	can_baudrate_struct.bts1_size = CAN_BTS1_8TQ;
	can_baudrate_struct.bts2_size = CAN_BTS2_3TQ;
	can_baudrate_set(CAN1, &can_baudrate_struct);

	/* can filter init */
	i=(params.ID<<3)|CAN_IDE_IDT|CAN_RTR_DATA;
	can_filter_init_struct.filter_activate_enable = TRUE;
	can_filter_init_struct.filter_mode = CAN_FILTER_MODE_ID_MASK;
	can_filter_init_struct.filter_fifo = CAN_FILTER_FIFO0;
	can_filter_init_struct.filter_number = 0;
	can_filter_init_struct.filter_bit = CAN_FILTER_32BIT;
	can_filter_init_struct.filter_id_high = i>>16;
	can_filter_init_struct.filter_id_low = i;
	can_filter_init_struct.filter_mask_high = 0;
	can_filter_init_struct.filter_mask_low = 0x7F8;	//过滤本地ID
	can_filter_init(CAN1, &can_filter_init_struct);

	/* can interrupt config */
//	nvic_irq_enable(CAN1_SE_IRQn,0,0);
	nvic_irq_enable(USBFS_L_CAN1_RX0_IRQn,0,0);
	can_interrupt_enable(CAN1, CAN_RF0MIEN_INT, TRUE);

//	/* error interrupt enable */
//	can_interrupt_enable(CAN1, CAN_ETRIEN_INT, TRUE);
//	can_interrupt_enable(CAN1, CAN_EOIEN_INT, TRUE);
}
	


/***************************************************************************
;** 函数名称: 	
;** 功能描述:  	
;** 输入参数: 
;** 返 回 值: 
;** 全局变量: 
;** 调用模块: 
;** 作　  者:   M-L-A
;** 日　  期:  2024-3-6
;** 修改原因：
;** 说    明: 	
;***************************************************************************/
uint8_t txCAN1(uint8_t *sd,uint16_t num)
{
	uint8_t r=0,n,mailbox;
	uint16_t i,j,m;
	can_tx_message_type ts;
	
	m = num;
	for(i=0;i<num;)
	{
		ts.standard_id = params.ID;
		ts.extended_id = (params.ID<<8)|target_id;
		ts.id_type = CAN_ID_EXTENDED;	//CAN_ID_STANDARD;
		ts.frame_type = CAN_TFT_DATA;
		memset(&ts.dlc,0,sizeof(ts.dlc));
		if(m >8)
		{ts.dlc = 8;m -=8;}
		else
		{ts.dlc = m;}
		
		for(n=0;n<ts.dlc;n++)
		{ts.data[n] = sd[i++];}
		
		for(n=0;n<2;n++)
		{//当次发送失败重发一次
			for(j=0;j<20000;j++)
			{//等待邮箱为空 400MS
				mailbox = can_message_transmit(CAN1, &ts); 
				if(mailbox != CAN_TX_STATUS_NO_EMPTY)
				{break;}
				delay_us(20);
			}
			if(j < 20000)
			{
				for(j=0;j<20000;j++)
				{//等待发送数据完成 400ms
					if(can_transmit_status_get(CAN1, (can_tx_mailbox_num_type)mailbox) == CAN_TX_STATUS_SUCCESSFUL)
					{break;}
					delay_us(20);
				}
				if(j < 20000)
				{break;}
			}
		}
		
		if(j >= 20000)
		{r =1;break;}
		
	}
	
	return r;
}


/***************************************************************************
;** 函数名称: 	
;** 功能描述:  	
;** 输入参数: 
;** 返 回 值: 
;** 全局变量: 
;** 调用模块: 
;** 作　  者:   M-L-A
;** 日　  期:  2024-3-6
;** 修改原因：
;** 说    明: 	
;***************************************************************************/
void USBFS_L_CAN1_RX0_IRQHandler (void)
{
	if(can_flag_get(CAN1,CAN_RF0MN_FLAG) != RESET)
	{
		uint8_t i;
		can_rx_message_type  ts;
		
		can_message_receive(CAN1, CAN_RX_FIFO0, &ts);
		
		if(((ts.standard_id&0xff) == params.ID)||((ts.extended_id&0xff) == params.ID))
		{
			if(ts.id_type == CAN_ID_EXTENDED)
			{target_id = ts.extended_id >> 8;}
			else if(ts.id_type == CAN_ID_STANDARD)
			{target_id = ts.standard_id >> 8;}
			
			if(ts.dlc >0)
			{
				for(i=0;i<ts.dlc;i++)
				{
					if((ts.data[i]=='\r')||(ts.data[i]=='\n'))
					{pCAN1->rxn++;}
					else if(ts.data[i] == 0x08)
					{
						if(pCAN1->len >0)
						{
							pCAN1->len--;
							pCAN1->rxFIFO[pCAN1->len]=0;
						}
					}
					else if(pCAN1->len < RX_MAX_FIFO)
					{pCAN1->rxFIFO[pCAN1->len++] = ts.data[i];}	
				}
				pCAN1->TimeOut=8000;	//10ms
			}
		}
		//can_flag_clear(CAN1, CAN_ETR_FLAG);
	}
}

 
/**
  *  @brief  can1 interrupt function se
  *  @param  none
  *  @retval none
  */
void CAN1_SE_IRQHandler(void)
{
	if(can_flag_get(CAN1,CAN_ETR_FLAG) != RESET)
	{
		can_res = CAN1->ests & 0x70;
		
		can_flag_clear(CAN1, CAN_ETR_FLAG);
//		/* error type is stuff error */
//		if(can_res == 0x00000010)
//		{
//		  /* when stuff error occur: in order to ensure communication normally,
//		  user must restart can or send a frame of highest priority message here */
//		}
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
;** 日　  期:  2024-3-6
;** 修改原因：
;** 说    明: 	
ETR: 位 [6：4]
	000： 没有错误；
	001： 位填充错误；
	010： 格式错误；
	011： 确认错误；
	100： 隐性位错误；
	101： 显性位错误；
	110： CRC 错误；
	111： 由软件设置。

;***************************************************************************/
void ResetCAN1(void)
{
	if(can_res)
	{
		
//		if(can_res  == 0x00000011)
//		{can_config();}

		tPort=0; sprintfx("CAN_ER:%d\r\n",can_res);
		can_res = 0;
	}
}



 
