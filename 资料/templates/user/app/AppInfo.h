#ifndef __APPINFO_H__
#define __APPINFO_H__

#include "wizchip_conf.h"

#define APPINFO_ADDR 512
#define APPINFO_CHECKSUM 0x66

#define APPINFO_VERSION "PCBA:H1-4, PRG:V11.7"

// 需要掉电记录的信息在AppInfo_S中的后段添加,但需要在ucCheckSum之前,不能影响已有数据的顺序

typedef struct
{
  uint8_t ucLanguage;
  uint8_t ucSpeak;
  uint8_t ucBackLight;
  uint16_t usSleepTime;

  uint16_t usBoardTimeOut;
  uint8_t ucDefaultPort;
  uint8_t ucPortNum;

  uint32_t ulBaudRate_UART;
  uint32_t ulBaudRate_USB;
  uint32_t ulBaudRate_DUT;
  uint32_t ulBaudRate_DUT2;

  wiz_NetInfo NetInfo;
  uint16_t usLocalPort;
  uint16_t usRemotePort;
  uint8_t ucaRip[4]; ///< Remote IP Address

  uint8_t ucCheckSum;
} AppInfo_S;

extern AppInfo_S AppInfo;

bool AppInfo_Read(uint16_t usAddr, uint8_t *p_ucaBuff, uint16_t usBuffLen);
bool AppInfo_Write(uint16_t usAddr, uint8_t *p_ucaBuff, uint16_t usBuffLen);
void AppInfo_Init(void);
void AppInfo_TrigStorage(uint16_t usDelay);
void AppInfo_Proc(void);

#endif /*AppInfo.h*/
