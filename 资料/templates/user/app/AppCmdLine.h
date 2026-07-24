#ifndef __APPCMDLINE_H__
#define __APPCMDLINE_H__

#define APPCMDLINE_PORTNUM 10

typedef enum
{
  AppCmdLine_Port_RS232 = 0,
  AppCmdLine_Port_USB,
  AppCmdLine_Port_ETH_S0, // Socket0
  AppCmdLine_Port_ETH_S1, // Socket1
  AppCmdLine_Port_ETH_S2, // Socket2
  AppCmdLine_Port_ETH_S3, // Socket3
  AppCmdLine_Port_ETH_S4, // Socket4
  AppCmdLine_Port_ETH_S5, // Socket5
  AppCmdLine_Port_ETH_S6, // Socket6
  AppCmdLine_Port_ETH_S7, // Socket7
  AppCmdLine_Port_Unknow,
} AppCmdLine_Port_E;

typedef struct
{
  const char *p_caCmdStr;       // 命令符
  char (*p_Func)(void *p, ...); // 回调
  const char *p_caHintStr;      // 提示符
} AppCmdLine_S;

#define APPCMDLINE_RECVBUFF_SIZE 128

typedef struct
{
  uint8_t ucWriteIdx;
  uint8_t ucaRecvBuff[APPCMDLINE_RECVBUFF_SIZE];

  uint8_t ucEndByte;
} AppCmdLine_Decode_S;

typedef struct
{
  bool bReturnRecv;
  uint8_t ucBoardIdx;
  uint16_t usBoardTimeCnt;

  char caPrintfBuff[APPCMDLINE_PORTNUM][64];
} AppCmdLine_Mgr_S;
extern AppCmdLine_Mgr_S AppCmdLine_Mgr;

AppCmdLine_Port_E AppCmdLine_PortGet(void);
bool AppCmdLine_Send(uint8_t *p_ucaBuff, uint16_t usBuffLen);
void AppCmdLine_Init(void);
void AppCmdLine_Proc(AppCmdLine_Port_E Port);

#endif /*AppCmdLine.h*/
