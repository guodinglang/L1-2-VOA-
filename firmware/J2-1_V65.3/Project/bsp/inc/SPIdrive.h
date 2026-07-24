 /*
*********************************************************************************************************
*	                                  
*	模块名称 :     
*	文件名称 : 
*	版    本 : V1.0
*	说    明 : 头文件
*
*********************************************************************************************************
*/
#ifndef __SPIDRIVE_H__
#define __SPIDRIVE_H__

#include "project.h" 

//----------------------------------------------------------------------------------
#define BUFFER_SIZE 4





//----------------------------------------------------------------------------------
void SPI1_Config(void);
void SPI2_Config(void);
void SPI4_Config(void);
//void SPI1_Write_Nbyte(uint16_t *wd, uint8_t num);
uint8_t spi_read_send_byte(uint8_t d);
void cs_low(void);
void cs_high(void);
uint8_t spi4_wrByte(uint8_t d);


#endif


