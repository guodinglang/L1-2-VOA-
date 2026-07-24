/**
******************************************************************************
* @file         w5500_conf.c
* @version      V1.0
* @date         2020-06-05
* @brief        配置MCU，移植w5500程序需要修改的文件，配置w5500的MAC和IP地址
*
* @company      深圳炜世科技有限公司
* @information  WIZnet W5500官方代理商，全程技术支持，价格优势大！
* @website      www.wisioe.com
* @forum        www.w5500.cn
* @qqGroup      579842114
* @Support      QQ:2571856470；Mob:18998931307
* @Email        support@wisioe.com
******************************************************************************
*/
#include <stdio.h>
#include <string.h>
#include "w5500_conf.h"
// #include "utility.h"
#include "w5500.h"
#include "socket.h"
#include "SPIdrive.h"
// #include "bsp_TiMbase.h"
// #include "bsp_flash.h"
// #include "dhcp.h"

CONFIG_MSG ethernet;						   // 配置结构体
rxStructure rxEthernet, *pEther = &rxEthernet; //
socket_data_struct eSRDB[8] = {0};
uint8_t sockn = 0; // socket number
uint8_t socku = 0; // use socket

// uint16 rxlen=0;
// uint8 rxbuf[1024];

/*MAC地址首字节必须为偶数
  如果多块w5500网络适配板在同一现场工作，请使用不同的MAC地址
*/
// uint8 mac[6]={0x00,0x08,0xdc,0x11,0x11,0x11};

///*定义默认IP信息*/
// uint8 local_ip[4] = {192,168,1,232};                        // 定义w5500默认IP地址
// uint8 subnet[4] = {255,255,255,0};                          // 定义w5500默认子网掩码
// uint8 gateway[4] = {192,168,1,1};                           // 定义w5500默认网关
// uint8 dns_server[4] = {114,114,114,114};                    // 定义w5500默认DNS

// uint16 local_port = 8080;                                   // 定义本地端口

///*定义远端IP信息*/
// uint8  remote_ip[4] = {192,168,1,100};                      // 远端IP地址
// uint16 remote_port = 8080;                                  // 远端端口号

///*IP配置方法选择，请自行选择*/
// uint8  ip_from=IP_FROM_DEFINE;

// uint32 ms=0;                                                // 毫秒计数
// vu8    ntptimer = 0;                                        // NPT秒计数

/**
 *@brief  初始化W5500的复位与中断管脚
 *@param  无
 *@return 无
 */
void reset_break_gpio_init(void)
{
	//  GPIO_InitTypeDef GPIO_InitStructure;
	//  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB | RCC_APB2Periph_GPIOC,ENABLE);
	//  /* PB_01 -> RST */
	//  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;
	//  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	//  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	//  GPIO_Init(GPIOB, &GPIO_InitStructure);
	//  /* PC_05 -> INT */
	//  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;
	//  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
	//  GPIO_Init(GPIOC, &GPIO_InitStructure);
}

/**
 *@brief  配置W5500的IP地址
 *@param  无
 *@return 无
 */
void set_w5500_netinfo(void)
{
	// #ifdef  _HTTP_SERVER_H_
	//	uint8 temp;
	// #endif
	//   // 复制定义的配置信息到配置结构体
	//   memcpy(ethernet.mac, mac, 6);
	//   memcpy(ethernet.lip,local_ip,4);
	//   memcpy(ethernet.sub,subnet,4);
	//   memcpy(ethernet.gw,gateway,4);
	//   memcpy(ethernet.dns,dns_server,4);
	//
	// #ifdef  _HTTP_SERVER_H_
	///*仅在使用HTTP Server例程时生效，使用请检查"http_server.h"头文件的引用*/
	//  ReadFlashNBtye(0,&temp,1);
	//  if(temp != 255)
	//    ip_from = IP_FROM_FLASH;
	//  else
	//    ip_from = IP_FROM_DEFINE;
	// #endif
	//  switch(ip_from)
	//  {
	//    case IP_FROM_DEFINE:
	//      printf(" 使用定义的IP信息配置W5500：\r\n");
	//      break;
	// #ifdef  _HTTP_SERVER_H_
	//    case IP_FROM_FLASH:
	//      printf(" 使用Flash内IP信息配置W5500：\r\n");
	//      ReadFlashNBtye(0,ethernet.lip,12);
	//      break;
	// #endif
	//  }
	memset(eSRDB, 0, sizeof(eSRDB));
	sockn = 0;
	socku = 0;
	iinchip_init(); // initial
	delay_ms(10);
	//--------write-------------------------------------
	setSHAR(ethernet.mac);
	setSHAR(ethernet.mac);
	setSUBR(ethernet.sm);
	setGAR(ethernet.gw);
	setSIPR(ethernet.ip);
	socket_buf_init(txsize, rxsize); // 初始化8个Socket的发送接收缓存大小

	setRTR(2000); // 设置超时时间
	setRCR(3);	  // 设置最大重新发送次数

	setKPALVTR(SOCK_TCPS, 1);
	setKPALVTR(SOCK_TCPC, 1);
	setKPALVTR(SOCK_ARP, 1);
	setKPALVTR(SOCK_DHCP, 1);
	setKPALVTR(SOCK_DNS, 1);
	setKPALVTR(SOCK_HTTPC, 1);
	setKPALVTR(SOCK_NTP, 1);
	setKPALVTR(SOCK_WEBSOCKET, 1);

	//--------read check--------------------------------
	getSHAR(ethernet.mac);
	printf("MAC_ADD: %02x-%02x-%02x-%02x-%02x-%02x\r\n", ethernet.mac[0], ethernet.mac[1], ethernet.mac[2], ethernet.mac[3], ethernet.mac[4], ethernet.mac[5]);
	getSIPR(ethernet.ip);
	printf("IP_ADD:  %d.%d.%d.%d\r\n", ethernet.ip[0], ethernet.ip[1], ethernet.ip[2], ethernet.ip[3]);
	getSUBR(ethernet.sm);
	printf("SubMask: %d.%d.%d.%d\r\n", ethernet.sm[0], ethernet.sm[1], ethernet.sm[2], ethernet.sm[3]);
	getGAR(ethernet.gw);
	printf("gateway: %d.%d.%d.%d\r\n", ethernet.gw[0], ethernet.gw[1], ethernet.gw[2], ethernet.gw[3]);
}

/**
 *@brief  配置W5500的MAC地址
 *@param  无
 *@return 无
 */
void set_w5500_mac(void)
{
	uint8 mac[6] = {0x00, 0x08, 0xdc, 0x11, 0x11, 0x11};

	memcpy(ethernet.mac, mac, 6);
	setSHAR(ethernet.mac);

	getSHAR(mac);
	printf("MAC地址  : %02x.%02x.%02x.%02x.%02x.%02x\r\n", mac[0], mac[1], mac[2], mac[3], mac[4], mac[5]);
}

/**
 *@brief  W5500复位设置函数
 *@param  无
 *@return 无
 */
void reset_w5500(void)
{
	//  GPIO_ResetBits(GPIOB, GPIO_Pin_1);
	//  delay_ms(500);
	//  GPIO_SetBits(GPIOB, GPIO_Pin_1);
	//  delay_ms(1500);
}

/**
 *@brief		设置W5500的片选端口SCSn为低
 *@param		无
 *@return	无
 */
void iinchip_csoff(void)
{
	cs_low();
}

/**
 *@brief		设置W5500的片选端口SCSn为高
 *@param		无
 *@return	无
 */
void iinchip_cson(void)
{
	cs_high();
}

/**
 *@brief		STM32 SPI1读写8位数据
 *@param		dat：写入的8位数据
 *@return	无
 */
uint8 IINCHIP_SpiSendData(uint8 dat)
{
	return (spi_read_send_byte(dat));
}

/**
 *@brief		写入一个8位数据到W5500
 *@param		addrbsb: 写入数据的地址
 *@param   data：写入的8位数据
 *@return	无
 */
void IINCHIP_WRITE(uint32 addrbsb, uint8 data)
{
	iinchip_csoff();
	IINCHIP_SpiSendData((addrbsb & 0x00FF0000) >> 16);
	IINCHIP_SpiSendData((addrbsb & 0x0000FF00) >> 8);
	IINCHIP_SpiSendData((addrbsb & 0x000000F8) + 4);
	IINCHIP_SpiSendData(data);
	iinchip_cson();
}

/**
 *@brief		从W5500读出一个8位数据
 *@param		addrbsb: 写入数据的地址
 *@param   data：从写入的地址处读取到的8位数据
 *@return	无
 */
uint8 IINCHIP_READ(uint32 addrbsb)
{
	uint8 data = 0;
	iinchip_csoff();
	IINCHIP_SpiSendData((addrbsb & 0x00FF0000) >> 16);
	IINCHIP_SpiSendData((addrbsb & 0x0000FF00) >> 8);
	IINCHIP_SpiSendData((addrbsb & 0x000000F8));
	data = IINCHIP_SpiSendData(0x00);
	iinchip_cson();
	return data;
}

/**
 *@brief		向W5500写入len字节数据
 *@param		addrbsb: 写入数据的地址
 *@param   buf：写入字符串
 *@param   len：字符串长度
 *@return	len：返回字符串长度
 */
uint16 wiz_write_buf(uint32 addrbsb, uint8 *buf, uint16 len)
{
	uint16 idx = 0;
	if (len == 0)
		printf(" Unexpected2 length 0\r\n");
	iinchip_csoff();
	IINCHIP_SpiSendData((addrbsb & 0x00FF0000) >> 16);
	IINCHIP_SpiSendData((addrbsb & 0x0000FF00) >> 8);
	IINCHIP_SpiSendData((addrbsb & 0x000000F8) + 4);
	for (idx = 0; idx < len; idx++)
	{
		IINCHIP_SpiSendData(buf[idx]);
	}
	iinchip_cson();

	return len;
}

/**
 *@brief		从W5500读出len字节数据
 *@param		addrbsb: 读取数据的地址
 *@param 	buf：存放读取数据
 *@param		len：字符串长度
 *@return	len：返回字符串长度
 */
uint16 wiz_read_buf(uint32 addrbsb, uint8 *buf, uint16 len)
{
	uint16 idx = 0;
	if (len == 0)
	{
		printf(" Unexpected2 length 0\r\n");
	}
	iinchip_csoff();
	IINCHIP_SpiSendData((addrbsb & 0x00FF0000) >> 16);
	IINCHIP_SpiSendData((addrbsb & 0x0000FF00) >> 8);
	IINCHIP_SpiSendData((addrbsb & 0x000000F8));
	for (idx = 0; idx < len; idx++)
	{
		buf[idx] = IINCHIP_SpiSendData(0x00);
	}
	iinchip_cson();
	return len;
}

/**
 *@brief  STM32系统软复位函数
 *@param  无
 *@return 无
 */
void reboot(void)
{
	pFunction Jump_To_Application;
	uint32 JumpAddress;
	printf("system restarting……\r\n");
	JumpAddress = *(vu32 *)(0x00000004);
	Jump_To_Application = (pFunction)JumpAddress;
	Jump_To_Application();
}

/**
 *@brief  dhcp用到的定时器初始化
 *@param  无
 *@return 无
 */
void dhcp_timer_init(void)
{
	timer2_init();
}

/**
 *@brief  ntp用到的定时器初始化
 *@param  无
 *@return 无
 */
void ntp_timer_init(void)
{
	timer2_init();
}

/**
 *@brief  STM32定时器2初始化
 *@param  无
 *@return 无
 */
void timer2_init(void)
{
	//  TIM2_Configuration();                                        //  TIM2 定时配置
	//  TIM2_NVIC_Configuration();                                   //  定时器的中断优先级
	//  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2 , ENABLE);        //  TIM2 重新开时钟，开始计时
}

/**
 *@brief  定时器2中断函数
 *@param  无
 *@return 无
 */
void timer2_isr(void)
{
	//  ms++;
	//  if(ms>=1000)
	//  {
	//    ms=0;
	//    dhcp_time++;             // DHCP定时加1S
	// #ifndef __NTP_H__
	//    ntptimer++;              // NTP重试时间加1S
	// #endif
	//  }
}

/**
 *@brief  检测物理层连接
 *@param  无
 *@return 无
 */
void PHY_check(void)
{
	uint8 PHY_connect = 0;
	PHY_connect = 0x01 & getPHYStatus();
	if (PHY_connect == 0)
	{
		printf(" \r\nCheck whether the network cable is connected\r\n");
		PHY_connect = 0;
		do
		{
			close(PHY_connect++);
		} while (PHY_connect < 4);
		PHY_connect = 0;
		while (PHY_connect == 0)
		{
			PHY_connect = 0x01 & getPHYStatus();
			printf(" .");
			delay_ms(500);
		}
		printf(" \r\n");
	}
}

/**
 *@brief  读取PHY寄存器数据
 *@param  无
 *@return PHYSR寄存器数值
 */
uint8 getPHYStatus(void)
{
	return IINCHIP_READ(PHYCFGR);
}

/**
 *@brief  配置KPALVIR寄存器
 *@param  i：配置的socket号码
 *@param  val：设置的时间(5s单位)
 *@return 无
 */
void setKPALVTR(SOCKET i, uint8 val)
{
	IINCHIP_WRITE(Sn_KPALVTR(i), val);
}

/**
 *@brief  ethernet_tcp_server
 *@param  SOCK_TCPS 0
 *@param
 *@return 无
 */
void ethernet_tcp_server(void)
{
	uint8_t i, len = 0, buff[128] = {0};

	switch (getSn_SR(sockn)) // SOCK_TCPS))                             	// 获取socket的状态
	{
	case SOCK_CLOSED:									   // socket处于关闭状态
		setKPALVTR(sockn, 1);							   // SOCK_TCPS,1);                            // KEEP ALIVE配置(需由W5500主动发送过一次数据后生效)
		socket(sockn, Sn_MR_TCP, ethernet.port, Sn_MR_ND); // 打开socket
		break;

	case SOCK_INIT:	   // socket已初始化状态
		listen(sockn); // SOCK_TCPS);                                  // socket建立监听
		break;

	case SOCK_ESTABLISHED: // socket处于连接建立状态
		if (getSn_IR(sockn) & Sn_IR_CON)
		{
			setSn_IR(sockn, Sn_IR_CON); // 清除接收中断标志位
		}
		len = getSn_RX_RSR(sockn); // 定义len为已接收数据的长度
		if (len > 0)
		{
			memset(buff, 0, sizeof(buff));
			recv(sockn, buff, len);
			// 接收来自Client的数据
			for (i = 0; i < len; i++)
			{
				if ((buff[i] == '\r') || (buff[i] == '\n'))
				{
					if (eSRDB[sockn].len > 0)
					{
						eSRDB[sockn].rf = 2;
					}
				}
				else if (buff[i] == '>')
				{
					eSRDB[sockn].rf = 3;
					eSRDB[sockn].rBuf[eSRDB[sockn].len++] = buff[i];
				}
				else if (buff[i] == 0x08)
				{
					if (eSRDB[sockn].len > 0)
					{
						eSRDB[sockn].len--;
						eSRDB[sockn].rBuf[eSRDB[sockn].len] = 0;
					}
				}
				else if (eSRDB[sockn].len < 128) //((eSRDB[sockn].len < 128)&&(eSRDB[sockn].rf==0))
				{
					eSRDB[sockn].rBuf[eSRDB[sockn].len++] = buff[i];
				}
				else
				{
					break;
				}
			}
			//				send(SOCK_TCPS,buff,len);            			// 向Client发送数据
		}
		break;

	case SOCK_CLOSE_WAIT:  // socket处于等待关闭状态
		disconnect(sockn); // 断开当前TCP连接
		close(sockn);	   // 关闭当前所使用socket
		break;
	}
	if (eSRDB[sockn].rf > 0)
	{
		if (pEther->rxn == 0)
		{
			pEther->TimeOut = 5000; // 10ms

			memcpy(pEther->rxFIFO, eSRDB[sockn].rBuf, eSRDB[sockn].len);
			pEther->len = eSRDB[sockn].len;
			pEther->rxn = eSRDB[sockn].rf;
			socku = sockn;
			memset(eSRDB[sockn].rBuf, 0, 128);
			eSRDB[sockn].len = 0;
			eSRDB[sockn].rf = 0;
		}
	}
	else
	{
		if (eSRDB[sockn].len > 127)
		{
			memset(eSRDB[sockn].rBuf, 0, 128);
			eSRDB[sockn].len = 0;
			eSRDB[sockn].rf = 0;
		}
	}

	sockn++; // 8 socket
	if (sockn >= MAX_SOCK_NUM)
	{
		sockn = 0;
	}
}
