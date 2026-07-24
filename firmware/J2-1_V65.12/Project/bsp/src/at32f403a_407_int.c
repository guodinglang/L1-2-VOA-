/**
  **************************************************************************
  * @file     at32f403a_407_int.c
  * @version  v2.1.2
  * @date     2022-08-16
  * @brief    main interrupt service routines.
  **************************************************************************
  *                       Copyright notice & Disclaimer
  *
  * The software Board Support Package (BSP) that is made available to
  * download from Artery official website is the copyrighted work of Artery.
  * Artery authorizes customers to use, copy, and distribute the BSP
  * software and its related documentation for the purpose of design and
  * development in conjunction with Artery microcontrollers. Use of the
  * software is governed by this copyright notice and the following disclaimer.
  *
  * THIS SOFTWARE IS PROVIDED ON "AS IS" BASIS WITHOUT WARRANTIES,
  * GUARANTEES OR REPRESENTATIONS OF ANY KIND. ARTERY EXPRESSLY DISCLAIMS,
  * TO THE FULLEST EXTENT PERMITTED BY LAW, ALL EXPRESS, IMPLIED OR
  * STATUTORY OR OTHER WARRANTIES, GUARANTEES OR REPRESENTATIONS,
  * INCLUDING BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY,
  * FITNESS FOR A PARTICULAR PURPOSE, OR NON-INFRINGEMENT.
  *
  **************************************************************************
  */

/* includes ------------------------------------------------------------------*/
#include "at32f403a_407_int.h"
#include "project.h"

/** @addtogroup AT32F403A_periph_template
  * @{
  */

/** @addtogroup 403A_LED_toggle
  * @{
  */

/**
  * @brief  this function handles nmi exception.
  * @param  none
  * @retval none
  */
void NMI_Handler(void)
{
	
}

/**
  * @brief  this function handles hard fault exception.
  * @param  none
  * @retval none
  */
void HardFault_Handler(void)
{
  /* go to infinite loop when hard fault exception occurs */
  while(1)
  {
//	  ALR_LED(1);
	  ALARM(1);
  }
}

/**
  * @brief  this function handles memory manage exception.
  * @param  none
  * @retval none
  */
void MemManage_Handler(void)
{
  /* go to infinite loop when memory manage exception occurs */
  while(1)
  {
//	  ALR_LED(1);
	  ALARM(1);
  }
}

/**
  * @brief  this function handles bus fault exception.
  * @param  none
  * @retval none
  */
void BusFault_Handler(void)
{
  /* go to infinite loop when bus fault exception occurs */
  while(1)
  {
//	  ALR_LED(1);
	  ALARM(1);
  }
}

/**
  * @brief  this function handles usage fault exception.
  * @param  none
  * @retval none
  */
void UsageFault_Handler(void)
{
  /* go to infinite loop when usage fault exception occurs */
  while(1)
  {
//	  ALR_LED(1);
	  ALARM(1);
  }
}

/**
  * @brief  this function handles svcall exception.
  * @param  none
  * @retval none
  */
void SVC_Handler(void)
{
	
}

/**
  * @brief  this function handles debug monitor exception.
  * @param  none
  * @retval none
  */
void DebugMon_Handler(void)
{
	
}

/**
  * @brief  this function handles pendsv_handler exception.
  * @param  none
  * @retval none
  */
void PendSV_Handler(void)
{
	
}

/**
  * @brief  this function handles systick handler.
  * @param  none
  * @retval none
  */
void SysTick_Handler(void)
{
    static uint32_t ticks = 0;
    system_tick++;
    ticks ++;

    if(pUART->TimeOut > 0)
    {
		pUART->TimeOut--;
		if(pUART->TimeOut == 0)
		{
			memset(pUART->rxFIFO,0,RX_MAX_FIFO);
			pUART->len = 0;
			pUART->rxn = 0;
		}
    }
    /* toggle led */
    if(ticks >= DELAY)
    {
		ticks = 0;
    }
	
//	if((system_tick % 1000) == 0)
//	{
//		int32_t cnt = Encoder_AB_GetCount();
//        sprintfx("enc=%ld\r\n", cnt);
//		sprintfx("loc=%d\r\n", motor_status.position);
//	}
}

/**
  * @}
  */

/**
  * @brief  this function handles usart handler.
  * @param  none
  * @retval none
  */
void USART1_IRQHandler(void)
{
	if(usart_flag_get(USART1, USART_RDBF_FLAG) != RESET)
	{
		uint8_t s = USART1->dt;
		pUART->TimeOut=8000;	//1ms*x
//		
		if(s == '>')
        {pUART->rxn=1;}
		else if((s=='\r')||(s=='\n'))	//else if((s == '\r')&&(!pUART->len))
		{pUART->rxn=2;}
		else if(s == 0x08)
		{
			if(pUART->len >0)
			{
				pUART->len--;
				pUART->rxFIFO[pUART->len]=0;
			}
		}
		else if(pUART->len < RX_MAX_FIFO)
		{pUART->rxFIFO[pUART->len++]=s;}	
		
		usart_flag_clear(USART1, USART_RDBF_FLAG);
	}
}
bool g_origin_location_flag;
void EXINT3_IRQHandler(void)
{
	if(exint_flag_get(EXINT_LINE_3) != RESET)
	{
		exint_flag_clear(EXINT_LINE_3);
		
//		pin_states.org_state = 1;
		g_origin_location_flag = 1;
	}
}

void EXINT9_5_IRQHandler(void)
{
	if(exint_flag_get(EXINT_LINE_5) != RESET)
	{
		exint_flag_clear(EXINT_LINE_5);
	}
}

void EXINT15_10_IRQHandler(void)
{
    if (exint_flag_get(EXINT_LINE_11) != RESET) 
    {
        // ????§Ø???
        exint_flag_clear(EXINT_LINE_11); // M_DIAG ??????????§Ø?
        
        // ????????
        tmc2209_stall_detected();
    }
	else if (exint_flag_get(EXINT_LINE_12) != RESET)
	{
		exint_flag_clear(EXINT_LINE_12); // M_ORG
		g_origin_location_flag = 1;
	}
}

/**
  * @brief  this function handles usart handler.
  * @param  none
  * @retval none
  */
void USART2_IRQHandler(void)
{//DUT
//	uint8_t s;
	if(usart_flag_get(USART2, USART_RDBF_FLAG) != RESET)
	{
//		s = USART2->dt;
//		pUART->TimeOut=10;	//1ms*x
		
//		if((s=='\r')||(s=='\n'))
//        {urStruct2.rxn++;}
//		else if(urStruct2.len < RX_MAX_FIFO)
//		{urStruct2.rxFIFO[urStruct2.len++]=s;}
		
//		if(pDUT->len < RX_MAX_FIFO)
//		{pDUT->rxFIFO[pDUT->len++] = USART2->dt;}	  
//		send(SOCK_TCPS,(uint8_t *)&s,1);
		usart_flag_clear(USART2, USART_RDBF_FLAG);
	}
}

/**
  * @brief  this function handles usart handler.
  * @param  none
  * @retval none
  */
//void USART3_IRQHandler(void)
//{//USB TO USART
//	if(usart_flag_get(USART3, USART_RDBF_FLAG) != RESET)
//	{
//		uint8_t s = USART3->dt;
//		pUSB->TimeOut=5000;	//1ms*x
//		
//		if((s=='\r')||(s=='\n'))
//        {pUSB->rxn = 2;}
//		else if(s=='>')
//		{	
//			pUSB->rxFIFO[pUSB->len++]=s;
//			pUSB->rxn = 3;
//		}
//		else if(s == 0x08)
//		{
//			if(pUSB->len >0)
//			{
//				pUSB->len--;
//				pUSB->rxFIFO[pUSB->len]=0;
//			}
//		}
//		else if(pUSB->len < RX_MAX_FIFO)
//		{pUSB->rxFIFO[pUSB->len++]=s;}	 
		
//		if(pUSB->len < RX_MAX_FIFO)
//		{pUSB->rxFIFO[pUSB->len++] = USART3->dt;}
		
//		usart_flag_clear(USART3, USART_RDBF_FLAG);
//	}
//}

void UART4_IRQHandler(void)
{
//	uint8_t s;
	if(usart_flag_get(UART4, USART_RDBF_FLAG) != RESET)
	{
//		s = UART4->dt;
//		pUART->TimeOut=10;	//1ms*x
		
//		if((s=='\r')||(s=='\n'))
//        {pUSB->rxn++;}
//		else if(pUSB->len < RX_MAX_FIFO)
//		{pUSB->rxFIFO[pUSB->len++]=s;}	 
		
//		if(pUSB->len < RX_MAX_FIFO)
//		{pUSB->rxFIFO[pUSB->len++] = USART3->dt;}
		
//		if(pDUT2->len < RX_MAX_FIFO)
//		{pDUT2->rxFIFO[pDUT2->len++] = UART4->dt;}
		
		usart_flag_clear(UART4, USART_RDBF_FLAG);
	}
}





/**
  * @}
  */
