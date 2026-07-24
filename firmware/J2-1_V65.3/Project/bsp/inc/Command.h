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

#ifndef  __COMMAND_H__
#define  __COMMAND_H__

#include "project.h"

/*********************************************************************************/
int gLowerCaseString(char *str);
void rxCommand(void);
char help(void *p,...);
char ReadVersion(void *p,...);
char RebackCharacter(void *p,...);
char ReadWriteBoardIDN(void *p,...);
//char ReadWriteBoardPN(void *p,...);
//char ReadWriteBoardSN(void *p,...);
char ReadSelectSwitch(void *p,...);
char ReadWriteMaxCH(void *p,...);
char LevelValueDispose(void *p,...);
char OffsetChannel(void *p,...);
char SetReadWrite(void *p,...);
//char SimpleResponse(void *p,...);
char SystemReset(void *p,...);
char FactoryReset(void *p,...);
char BaudrateUART(void *p,...);
char SaveSelectSwitch(void *p,...);



#endif


