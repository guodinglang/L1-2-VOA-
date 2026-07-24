#ifndef __BSPCONFIG_H__
#define __BSPCONFIG_H__

// rtthread nano 3.1.5
#include "rtthread.h"

#include "BspBoard.h"
#include "BspEvent.h"
#include "BspDwt.h"
#include "BspFlash.h"
#include "BspKey.h"
#include "BspSoftiic.h"
#include "BspUart.h"
#include "BspCH9434.h"
#include "BspComPort.h"
#include "BspBuzzer.h"

typedef enum
{
  Sys_Event_None = 0,
} Sys_Event_E;

#define BSPCONFIG_MUTEX_NUM 16

void default_process(void);
void EnterCritical(void);
void ExitCritical(void);

uint8_t BspConfig_MutexCreat(char *p_caName);
bool BspConfig_MutexTake(uint8_t ucIdx);
bool BspConfig_MutexRelease(uint8_t ucIdx);

#endif
