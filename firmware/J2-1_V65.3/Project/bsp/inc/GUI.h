
#ifndef	 __GUI_H__
#define  __GUI_H__


#include "project.h"


//------------------------------------------------------------------------------
uint8_t BlackLightOutlineGUI(uint16_t color);
uint8_t BringhtnessGUI(uint16_t cl1,uint16_t cl2);
void LCD_ShowImage(uint16_t x,uint16_t y,uint16_t w,uint16_t h,const unsigned char *p);
void MachineTypeGUI(uint16_t fc,uint16_t bc);
void SetupGUI(uint8_t pg,uint16_t fc,uint16_t bc);
void MainGUI(uint16_t fc,uint16_t bc);
void SelectMarkGUI(uint8_t s,uint16_t fc,uint16_t bc);
void SelectOptionGUI(uint8_t s,uint16_t fc,uint16_t bc);
void SubSelectGUI(uint8_t s,uint8_t loc,char *es,uint16_t fc,uint16_t bc);
void CurrentChannelGUI(uint16_t ch,uint16_t fc,uint16_t bc);
void EndpointGUI(void);

#endif


