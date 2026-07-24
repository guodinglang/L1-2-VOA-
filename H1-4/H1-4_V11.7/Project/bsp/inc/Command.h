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

#ifndef __COMMAND_H__
#define __COMMAND_H__

#include "project.h"

/*********************************************************************************/
int gLowerCaseString(char *str);
void rxCommandDispose(void *pt);
char help(void *p, ...);
char ReadVersion(void *p, ...);
char RebackCharacter(void *p, ...);
char SetReadWrite(void *p, ...);
// char LoopCycle(void *p,...);
char EthernerParameter(void *p, ...);
char SetupDUT(void *p, ...);
char SetupLCD(void *p, ...);
char SendButtonValue(void *p, ...);
char SetBoardIndex(void *p, ...);

#endif
