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
#include "includes.h"

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
	while (1)
	{
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
	while (1)
	{
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
	while (1)
	{
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
	while (1)
	{
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
	{
		PortTickUpdate();
		time_wheel_tick_isr(&tw);
	}

	if (pBuz->time > 0)
	{
		pBuz->time--;
	}
	if (pkey->time > 0)
	{
		pkey->time--;
	}
	if (pLCD->time > 0)
	{
		pLCD->time--;
	}
	if (pUART->TimeOut > 0)
	{
		pUART->TimeOut--;
	}
	if (pUSB->TimeOut > 0)
	{
		pUSB->TimeOut--;
	}
	if (pEther->TimeOut > 0)
	{
		pEther->TimeOut--;
	}
	if (pDUT->TimeOut > 0)
	{
		pDUT->TimeOut--;
	}
	if (pDUT2->TimeOut > 0)
	{
		pDUT2->TimeOut--;
	}

	if (pCAN1->TimeOut > 0)
	{
		pCAN1->TimeOut--;
	}

	if (pMultPort1->TimeOut > 0)
	{
		pMultPort1->TimeOut--;
	}
	if (pMultPort2->TimeOut > 0)
	{
		pMultPort2->TimeOut--;
	}
	if (pMultPort3->TimeOut > 0)
	{
		pMultPort3->TimeOut--;
	}
	if (pMultPort3->TimeOut > 0)
	{
		pMultPort3->TimeOut--;
	}

	if (IndexTimeDec > 0)
	{
		IndexTimeDec--;
	}

	if (pUART->ep > 0)
	{
		pUART->ep--;
	}
	if (pUSB->ep > 0)
	{
		pUSB->ep--;
	}
	if (pEther->ep > 0)
	{
		pEther->ep--;
	}

	if (hmi.to > 0)
	{
		hmi.to--;
	}

	//	SLED;
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
	uint8_t s;
	if (usart_flag_get(USART1, USART_RDBF_FLAG) != RESET)
	{
		s = USART1->dt;
		pUART->TimeOut = 5000; // 1ms*x

		if ((s == '\r') || (s == '\n'))
		{
			if (!pUART->ep)
			{
				pUART->rxn = 2;
			} // È¥µô'\r¡¯or '\n' one of
			pUART->ep = 10;
		}
		else if (s == '>')
		{
			pUART->rxn = 3;
			pUART->rxFIFO[pUART->len++] = s;
		}
		else if (s == 0x08)
		{
			if (pUART->len > 0)
			{
				pUART->len--;
				pUART->rxFIFO[pUART->len] = 0;
			}
		}
		else if (pUART->len < RX_MAX_FIFO)
		{
			pUART->rxFIFO[pUART->len++] = s;
		}

		//		if(pUART->len < RX_MAX_FIFO)
		//		{pUART->rxFIFO[pUART->len++] = USART1->dt;}

		usart_flag_clear(USART1, USART_RDBF_FLAG);
	}
}

/**
 * @brief  this function handles usart handler.
 * @param  none
 * @retval none
 */
void USART2_IRQHandler(void)
{ // DUT
	//	uint8_t s;
	if (usart_flag_get(USART2, USART_RDBF_FLAG) != RESET)
	{
		//		s = USART2->dt;
		pDUT->TimeOut = 500; // 1ms*x

		//		if((s=='\r')||(s=='\n'))
		//        {urStruct2.rxn++;}
		//		else if(urStruct2.len < RX_MAX_FIFO)
		//		{urStruct2.rxFIFO[urStruct2.len++]=s;}

		//		if(pDUT->len < RX_MAX_FIFO)
		{
			pDUT->rxFIFO[pDUT->len++] = USART2->dt;
		}
		if (pDUT->len >= RX_MAX_FIFO)
		{
			pDUT->len = 0;
		} //
		  //		usart_data_transmit(USART1, USART2->dt);
		  //		send(SOCK_TCPS,(uint8_t *)&s,1);
		usart_flag_clear(USART2, USART_RDBF_FLAG);
	}
}

/**
 * @brief  this function handles usart handler.
 * @param  none
 * @retval none
 */
void USART3_IRQHandler(void)
{ // USB TO USART
	uint8_t s;
	if (usart_flag_get(USART3, USART_RDBF_FLAG) != RESET)
	{
		s = USART3->dt;
		pUSB->TimeOut = 500; // 1ms*x

		if ((s == '\r') || (s == '\n'))
		{
			if (!pUSB->ep)
			{
				pUSB->rxn = 2;
			}
			pUSB->ep = 10;
		}
		else if (s == '>')
		{
			pUSB->rxn = 3;
			pUSB->rxFIFO[pUSB->len++] = s;
		}
		else if (s == 0x08)
		{
			if (pUSB->len > 0)
			{
				pUSB->len--;
				pUSB->rxFIFO[pUSB->len] = 0;
			}
		}
		else if (pUSB->len < RX_MAX_FIFO)
		{
			pUSB->rxFIFO[pUSB->len++] = s;
		}
		//		pUSB->rxFIFO[pUSB->len++] = s;
		//		if(pUSB->len >= RX_MAX_FIFO)
		//		{pUSB->len=0;}

		usart_flag_clear(USART3, USART_RDBF_FLAG);
	}
}

void UART4_IRQHandler(void)
{ // DUT2
	uint8_t s;
	if (usart_flag_get(UART4, USART_RDBF_FLAG) != RESET)
	{
		s = UART4->dt;

		// {
		// 	extern void UartRecvCallBack(uint8_t ucChar);

		// 	UartRecvCallBack(s);
		// }

		pDUT2->TimeOut = 500; // 1ms*x

		//		if((s=='\r')||(s=='\n'))
		//        {pUSB->rxn++;}
		//		else if(pUSB->len < RX_MAX_FIFO)
		//		{pUSB->rxFIFO[pUSB->len++]=s;}

		//		if(pUSB->len < RX_MAX_FIFO)
		//		{pUSB->rxFIFO[pUSB->len++] = USART3->dt;}

		//		if(pDUT2->len < RX_MAX_FIFO)
		{
			pDUT2->rxFIFO[pDUT2->len++] = s;
		}
		if (pDUT2->len >= RX_MAX_FIFO)
		{
			pDUT2->len = 0;
		}

		usart_flag_clear(UART4, USART_RDBF_FLAG);
	}
}

/**
 * @}
 */
