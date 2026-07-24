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

#ifndef __INTERIOR_DAC_H__
#define __INTERIOR_DAC_H__

#include "project.h"

//===============================================================================
// #define	 DAC_ENABLE_1	1	//
// #define	 DAC_ENABLE_2	2	//

#define DAC_DHR12R1_Address 0x40007408 // DAC_1模块基址
#define DAC_DHR12R2_Address 0x40007414 // DAC模块基址
#define DAC1_BUFFER_SIZE 1             // 360
#define DAC2_BUFFER_SIZE 1             // 360

//===============================================================================
void DAC1_Config(void);
void DAC2_Config(void);
void DAC1_StartSineWave(float frq, float amp);
void DAC2_StartSineWave(float frq, float amp);
void DAC1_Stop(void);
void DAC2_Stop(void);
void SetOutputVoltageDAC1(uint16_t d);
void SetOutputVoltageDAC2(float v);

#endif
