#include "includes.h"

static char AppCmdLine_CB_Help(void *p, ...);
static char AppCmdLine_CB_Rbc(void *p, ...);
static char AppCmdLine_CB_Ver(void *p, ...);
static char AppCmdLine_CB_Srw(void *p, ...);
static char AppCmdLine_CB_Ethn(void *p, ...);
static char AppCmdLine_CB_Dut(void *p, ...);
static char AppCmdLine_CB_BoardIdx(void *p, ...);

static const AppCmdLine_S AppCmdLineList[] =
    {
        {"help:", AppCmdLine_CB_Help,
         "help:                       //all command\r\n"},
        {"rbc:", AppCmdLine_CB_Rbc,
         "rbc: x                      //reback every character x(1-true;0-false)\r\n"},
        {"ver:", AppCmdLine_CB_Ver,
         "ver:                        //firmware version\r\n"},
        {"srw:", AppCmdLine_CB_Srw,
         "srw: x x x                  //Set read write x(w/r) x(err/language/brUART/brUSB/brDUT/brDUT2/spk) x(par)\r\n"},
        {"ethn:", AppCmdLine_CB_Ethn,
         "ethn: x x x x               //etherner parameter x(w/r) x(mac/ip/sm/gw/rip/port) x(par)\r\n"},
        {"dut:", AppCmdLine_CB_Dut,
         "dut: x x x                  //Setup DUT x(w) x(spp/pow) x(par)\r\n"},
        {"##:", AppCmdLine_CB_BoardIdx,
         "##: x x                     //set board index x(?/w) x(0/1/2/3/4/5/6)\r\n"},
};

static const uint16_t usCmdNum = sizeof(AppCmdLineList) / sizeof(AppCmdLine_S);

AppCmdLine_Decode_S AppCmdLine_Decode[APPCMDLINE_PORTNUM];
AppCmdLine_Port_E AppCmdLine_Port = AppCmdLine_Port_Unknow;
AppCmdLine_Mgr_S AppCmdLine_Mgr;

AppCmdLine_Port_E AppCmdLine_PortGet(void)
{
  return AppCmdLine_Port;
}

bool AppCmdLine_Send(uint8_t *p_ucaBuff, uint16_t usBuffLen)
{
  switch (AppCmdLine_Port)
  {
  default:
    return false;
  case AppCmdLine_Port_RS232:
    BspUart_SendBuff(BspUartCom_RS232, p_ucaBuff, usBuffLen);
    break;
  case AppCmdLine_Port_USB:
    BspUart_SendBuff(BspUartCom_USB, p_ucaBuff, usBuffLen);
    break;
  case AppCmdLine_Port_ETH_S0:
  case AppCmdLine_Port_ETH_S1:
  case AppCmdLine_Port_ETH_S2:
  case AppCmdLine_Port_ETH_S3:
  case AppCmdLine_Port_ETH_S4:
  case AppCmdLine_Port_ETH_S5:
  case AppCmdLine_Port_ETH_S6:
  case AppCmdLine_Port_ETH_S7:
  {
    extern const char *p_caSocketName[_WIZCHIP_SOCK_NUM_];
    BspComPort_Send(BspComPort_Name2Handle(p_caSocketName[AppCmdLine_Port - AppCmdLine_Port_ETH_S0]), p_ucaBuff, usBuffLen);
  }
  break;
  }

  return true;
}

bool AppCmdLine_SendString(char *p_caString)
{
  uint16_t usStrLen = strlen((const char *)p_caString);

  switch (AppCmdLine_Port)
  {
  default:
    return false;
  case AppCmdLine_Port_RS232:
    BspUart_SendBuff(BspUartCom_RS232, (uint8_t *)p_caString, usStrLen);
    break;
  case AppCmdLine_Port_USB:
    BspUart_SendBuff(BspUartCom_USB, (uint8_t *)p_caString, usStrLen);
    break;
  case AppCmdLine_Port_ETH_S0:
  case AppCmdLine_Port_ETH_S1:
  case AppCmdLine_Port_ETH_S2:
  case AppCmdLine_Port_ETH_S3:
  case AppCmdLine_Port_ETH_S4:
  case AppCmdLine_Port_ETH_S5:
  case AppCmdLine_Port_ETH_S6:
  case AppCmdLine_Port_ETH_S7:
  {
    extern const char *p_caSocketName[_WIZCHIP_SOCK_NUM_];
    BspComPort_Send(BspComPort_Name2Handle(p_caSocketName[AppCmdLine_Port - AppCmdLine_Port_ETH_S0]), (uint8_t *)p_caString, usStrLen);
  }
  break;
  }

  return true;
}

static bool AppCmdLine_Printf(char *p_caString, ...)
{
  char *p_caBuff = &AppCmdLine_Mgr.caPrintfBuff[AppCmdLine_Port][0];
  va_list args;

  memset(p_caBuff, 0, 64);

  va_start(args, p_caString);
  rt_vsnprintf(p_caBuff, 64, (const char *)p_caString, args);
  va_end(args);

  switch (AppCmdLine_Port)
  {
  default:
    break;
  case AppCmdLine_Port_RS232:
    return BspUart_SendBuff(BspUartCom_RS232, (uint8_t *)p_caBuff, strlen((const char *)p_caBuff));
  case AppCmdLine_Port_USB:
    return BspUart_SendBuff(BspUartCom_USB, (uint8_t *)p_caBuff, strlen((const char *)p_caBuff));
  case AppCmdLine_Port_ETH_S0:
  case AppCmdLine_Port_ETH_S1:
  case AppCmdLine_Port_ETH_S2:
  case AppCmdLine_Port_ETH_S3:
  case AppCmdLine_Port_ETH_S4:
  case AppCmdLine_Port_ETH_S5:
  case AppCmdLine_Port_ETH_S6:
  case AppCmdLine_Port_ETH_S7:
  {
    extern const char *p_caSocketName[_WIZCHIP_SOCK_NUM_];
    return BspComPort_Send(BspComPort_Name2Handle(p_caSocketName[AppCmdLine_Port - AppCmdLine_Port_ETH_S0]), (uint8_t *)p_caBuff, strlen((const char *)p_caBuff));
  }
  }

  return false;
}

uint16_t AppCmdLine_Read(uint8_t *p_ucaBuff, uint16_t usBuffSize)
{
  switch (AppCmdLine_Port)
  {
  default:
    break;
  case AppCmdLine_Port_RS232:
    return BspUart_GetBuff(BspUartCom_RS232, p_ucaBuff, usBuffSize);
  case AppCmdLine_Port_USB:
    return BspUart_GetBuff(BspUartCom_USB, p_ucaBuff, usBuffSize);
  case AppCmdLine_Port_ETH_S0:
  case AppCmdLine_Port_ETH_S1:
  case AppCmdLine_Port_ETH_S2:
  case AppCmdLine_Port_ETH_S3:
  case AppCmdLine_Port_ETH_S4:
  case AppCmdLine_Port_ETH_S5:
  case AppCmdLine_Port_ETH_S6:
  case AppCmdLine_Port_ETH_S7:
  {
    extern const char *p_caSocketName[_WIZCHIP_SOCK_NUM_];
    return BspComPort_Read(BspComPort_Name2Handle(p_caSocketName[AppCmdLine_Port - AppCmdLine_Port_ETH_S0]), p_ucaBuff, usBuffSize);
  }
  }

  return 0;
}

uint16_t AppCmdLine_GetRxCount(AppCmdLine_Port_E Port)
{
  switch (Port)
  {
  default:
    break;
  case AppCmdLine_Port_RS232:
    return BspUart_GetRxCount(BspUartCom_RS232);
  case AppCmdLine_Port_USB:
    return BspUart_GetRxCount(BspUartCom_USB);
  case AppCmdLine_Port_ETH_S0:
  case AppCmdLine_Port_ETH_S1:
  case AppCmdLine_Port_ETH_S2:
  case AppCmdLine_Port_ETH_S3:
  case AppCmdLine_Port_ETH_S4:
  case AppCmdLine_Port_ETH_S5:
  case AppCmdLine_Port_ETH_S6:
  case AppCmdLine_Port_ETH_S7:
  {
    extern const char *p_caSocketName[_WIZCHIP_SOCK_NUM_];
    return BspComPort_GetRxCount(BspComPort_Name2Handle(p_caSocketName[Port - AppCmdLine_Port_ETH_S0]));
  }
  }

  return 0;
}

bool AppCmdLine_RecvDoneCheck(void)
{
  bool bRecvDone = false;

  switch (AppCmdLine_Port)
  {
  default:
    return bRecvDone;
  case AppCmdLine_Port_RS232:
  {
    if (BspUart_GetRxState(BspUartCom_RS232) == true)
    {
      bRecvDone = true;
      BspUart_ClrRxState(BspUartCom_RS232);
    }
  }
  break;
  case AppCmdLine_Port_USB:
  {
    if (BspUart_GetRxState(BspUartCom_USB) == true)
    {
      bRecvDone = true;
      BspUart_ClrRxState(BspUartCom_USB);
    }
  }
  break;
  case AppCmdLine_Port_ETH_S0:
  case AppCmdLine_Port_ETH_S1:
  case AppCmdLine_Port_ETH_S2:
  case AppCmdLine_Port_ETH_S3:
  case AppCmdLine_Port_ETH_S4:
  case AppCmdLine_Port_ETH_S5:
  case AppCmdLine_Port_ETH_S6:
  case AppCmdLine_Port_ETH_S7:
  {
    extern const char *p_caSocketName[_WIZCHIP_SOCK_NUM_];
    bRecvDone = BspComPort_RxDoneCheck(BspComPort_Name2Handle(p_caSocketName[AppCmdLine_Port - AppCmdLine_Port_ETH_S0]), true);
  }
  break;
  }

  return bRecvDone;
}

static void AppCmdLine_GetLowerCaseString(char *p_caString)
{
  while (*p_caString)
  {
    if ((*p_caString >= 'A') && (*p_caString <= 'Z'))
    {
      *p_caString += 0x20;
    }

    p_caString += 1;
  }
}

static char AppCmdLine_CB_Help(void *p, ...)
{
  for (uint16_t i = 0; i < usCmdNum; i++)
  {
    AppCmdLine_Send((uint8_t *)AppCmdLineList[i].p_caHintStr, strlen(AppCmdLineList[i].p_caHintStr));
  }

  return 0;
}

static char AppCmdLine_CB_Rbc(void *p, ...)
{
  int lRes;
  bool bResult = true;

  sscanf(p, "%*s %d", &lRes);

  switch (lRes)
  {
  default:
  {
    bResult = false;
  }
  break;
  case 0:
    AppCmdLine_Mgr.bReturnRecv = false;
    break;
  case 1:
    AppCmdLine_Mgr.bReturnRecv = true;
    break;
  }

  AppCmdLine_SendString(p);

  if (bResult == true)
  {
    AppCmdLine_SendString(" pass\r\n");
  }
  else
  {
    AppCmdLine_SendString(" fail\r\n");
  }

  return 0;
}

static char AppCmdLine_CB_Ver(void *p, ...)
{
  AppCmdLine_SendString(APPINFO_VERSION);
  AppCmdLine_SendString("\r\n");

  return 0;
}

static char AppCmdLine_CB_Srw(void *p, ...)
{
  int lRes;
  char caStr_Action[8] = {0};
  char caStr_Object[16] = {0};

  bool bResult = false;

  sscanf(p, "%*s %s %s %d", caStr_Action, caStr_Object, &lRes);
  AppCmdLine_GetLowerCaseString(caStr_Action);
  AppCmdLine_GetLowerCaseString(caStr_Object);

  if (strcmp(caStr_Action, "w") == 0)
  {
    if (strcmp(caStr_Object, "dport") == 0)
    {
      if ((lRes > 0) && (lRes < 5))
      {
        AppInfo.ucDefaultPort = lRes;

        AppInfo_Write(OFFSETOF(AppInfo_S, ucDefaultPort), &AppInfo.ucDefaultPort, sizeof(AppInfo.ucDefaultPort));

        bResult = true;
      }
    }
    else if (strcmp(caStr_Object, "nport") == 0)
    {
      if ((lRes > 0) && (lRes <= 16))
      {
        AppInfo.ucPortNum = lRes;

        AppInfo_Write(OFFSETOF(AppInfo_S, ucPortNum), &AppInfo.ucPortNum, sizeof(AppInfo.ucPortNum));

        bResult = true;
      }
    }
    else if (strcmp(caStr_Object, "btime") == 0)
    {
      if (lRes > 0)
      {
        AppInfo.usBoardTimeOut = lRes;

        AppInfo_Write(OFFSETOF(AppInfo_S, usBoardTimeOut), (uint8_t *)&AppInfo.usBoardTimeOut, sizeof(AppInfo.usBoardTimeOut));

        bResult = true;
      }
    }
    else if (strcmp(caStr_Object, "language") == 0)
    {
      if (lRes < 0)
        lRes = 0;
      if (lRes > 1)
        lRes = 1;

      AppInfo.ucLanguage = lRes;

      AppInfo_Write(OFFSETOF(AppInfo_S, ucLanguage), &AppInfo.ucLanguage, sizeof(AppInfo.ucLanguage));

      bResult = true;
    }
    else if (strcmp(caStr_Object, "spk") == 0)
    {
      if (lRes < 0)
        lRes = 0;
      if (lRes > 1)
        lRes = 1;

      AppInfo.ucSpeak = lRes;

      AppInfo_Write(OFFSETOF(AppInfo_S, ucSpeak), &AppInfo.ucSpeak, sizeof(AppInfo.ucSpeak));

      bResult = true;
    }
    else if (strcmp(caStr_Object, "bruart") == 0)
    {
      AppInfo.ulBaudRate_UART = lRes;

      AppInfo_Write(OFFSETOF(AppInfo_S, ulBaudRate_UART), (uint8_t *)&AppInfo.ulBaudRate_UART, sizeof(AppInfo.ulBaudRate_UART));

      bResult = true;
    }
    else if (strcmp(caStr_Object, "brusb") == 0)
    {
      AppInfo.ulBaudRate_USB = lRes;

      AppInfo_Write(OFFSETOF(AppInfo_S, ulBaudRate_USB), (uint8_t *)&AppInfo.ulBaudRate_USB, sizeof(AppInfo.ulBaudRate_USB));

      bResult = true;
    }
    else if (strcmp(caStr_Object, "brdut") == 0)
    {
      AppInfo.ulBaudRate_DUT = lRes;

      AppInfo_Write(OFFSETOF(AppInfo_S, ulBaudRate_DUT), (uint8_t *)&AppInfo.ulBaudRate_DUT, sizeof(AppInfo.ulBaudRate_DUT));

      bResult = true;
    }
    else if (strcmp(caStr_Object, "brdut2") == 0)
    {
      AppInfo.ulBaudRate_DUT2 = lRes;

      AppInfo_Write(OFFSETOF(AppInfo_S, ulBaudRate_DUT2), (uint8_t *)&AppInfo.ulBaudRate_DUT2, sizeof(AppInfo.ulBaudRate_DUT2));

      bResult = true;
    }
  }
  else if (strcmp(caStr_Action, "r") == 0)
  {
    bResult = true;

    if (strcmp(caStr_Object, "err") == 0)
    {
    }
    else if (strcmp(caStr_Object, "dport") == 0)
    {
      AppCmdLine_Printf("dport:%d\r\n", AppInfo.ucDefaultPort);
    }
    else if (strcmp(caStr_Object, "nport") == 0)
    {
      AppCmdLine_Printf("nport:%d\r\n", AppInfo.ucPortNum);
    }
    else if (strcmp(caStr_Object, "btime") == 0)
    {
      AppCmdLine_Printf("bTime:%d\r\n", AppInfo.usBoardTimeOut);
    }
    else if (strcmp(caStr_Object, "language") == 0)
    {
      AppCmdLine_Printf("language:%d\r\n", AppInfo.ucLanguage);
    }
    else if (strcmp(caStr_Object, "spk") == 0)
    {
      AppCmdLine_Printf("speak:%d\r\n", AppInfo.ucSpeak);
    }
    else if (strcmp(caStr_Object, "bruart") == 0)
    {
      AppCmdLine_Printf("UART:%d\r\n", AppInfo.ulBaudRate_UART);
    }
    else if (strcmp(caStr_Object, "brusb") == 0)
    {
      AppCmdLine_Printf("USB:%d\r\n", AppInfo.ulBaudRate_USB);
    }
    else if (strcmp(caStr_Object, "brdut") == 0)
    {
      AppCmdLine_Printf("DUT:%d\r\n", AppInfo.ulBaudRate_DUT);
    }
    else if (strcmp(caStr_Object, "brdut2") == 0)
    {
      AppCmdLine_Printf("DUT2:%d\r\n", AppInfo.ulBaudRate_DUT2);
    }
    else
    {
      bResult = false;
    }

    if (bResult == true)
      return 0;
  }

  AppCmdLine_SendString(p);

  if (bResult == true)
  {
    AppCmdLine_SendString(" pass\r\n");
  }
  else
  {
    AppCmdLine_SendString(" fail\r\n");
  }

  return 0;
}

static char AppCmdLine_CB_Ethn(void *p, ...)
{
  char caStr_Action[8] = {0};
  char caStr_Object[16] = {0};
  char caStr_Content[32] = {0};

  bool bResult = false;
  wiz_NetInfo *p_Net = &AppInfo.NetInfo;

  // ============================================================
  // 写命令处理：w <对象> <内容>
  // 示例：w ip 192.168.1.100
  //       w mac 00-11-22-33-44-55
  //       w port 8080
  // ============================================================

  sscanf(p, "%*s %s %s %s", caStr_Action, caStr_Object, caStr_Content);
  AppCmdLine_GetLowerCaseString(caStr_Action);
  AppCmdLine_GetLowerCaseString(caStr_Object);
  AppCmdLine_GetLowerCaseString(caStr_Content);

  if (strcmp(caStr_Action, "w") == 0)
  {
    if (strcmp(caStr_Object, "mac") == 0)
    {
      // 格式：XX-XX-XX-XX-XX-XX 或 XX:XX:XX:XX:XX:XX
      uint8_t mac[6];
      int count = sscanf(caStr_Content, "%hhx-%hhx-%hhx-%hhx-%hhx-%hhx",
                         &mac[0], &mac[1], &mac[2], &mac[3], &mac[4], &mac[5]);

      if (count == 6)
      {
        memcpy(p_Net->mac, mac, 6);
        AppInfo_Write(OFFSETOF(AppInfo_S, NetInfo), (uint8_t *)&AppInfo.NetInfo, sizeof(wiz_NetInfo));

        bResult = true;
      }
      else
      {
        // 尝试冒号分隔符
        count = sscanf(caStr_Content, "%hhx:%hhx:%hhx:%hhx:%hhx:%hhx",
                       &mac[0], &mac[1], &mac[2], &mac[3], &mac[4], &mac[5]);
        if (count == 6)
        {
          memcpy(p_Net->mac, mac, 6);
          AppInfo_Write(OFFSETOF(AppInfo_S, NetInfo), (uint8_t *)&AppInfo.NetInfo, sizeof(wiz_NetInfo));
          bResult = true;
        }
        else
        {
          AppCmdLine_Printf("error: invalid mac format, use XX-XX-XX-XX-XX-XX\r\n");
          return 0;
        }
      }
    }
    else if (strcmp(caStr_Object, "ip") == 0 ||
             strcmp(caStr_Object, "sm") == 0 ||
             strcmp(caStr_Object, "gw") == 0 ||
             strcmp(caStr_Object, "dns") == 0 ||
             strcmp(caStr_Object, "rip") == 0)
    {
      uint8_t addr[4];
      int count = sscanf(caStr_Content, "%hhu.%hhu.%hhu.%hhu",
                         &addr[0], &addr[1], &addr[2], &addr[3]);

      if (count == 4)
      {
        // 根据对象名存入不同字段
        if (strcmp(caStr_Object, "ip") == 0)
        {
          memcpy(p_Net->ip, addr, 4);
          AppInfo_Write(OFFSETOF(AppInfo_S, NetInfo), (uint8_t *)&AppInfo.NetInfo, sizeof(wiz_NetInfo));
        }
        else if (strcmp(caStr_Object, "sm") == 0)
        {
          memcpy(p_Net->sn, addr, 4);
          AppInfo_Write(OFFSETOF(AppInfo_S, NetInfo), (uint8_t *)&AppInfo.NetInfo, sizeof(wiz_NetInfo));
        }
        else if (strcmp(caStr_Object, "gw") == 0)
        {
          memcpy(p_Net->gw, addr, 4);
          AppInfo_Write(OFFSETOF(AppInfo_S, NetInfo), (uint8_t *)&AppInfo.NetInfo, sizeof(wiz_NetInfo));
        }
        else if (strcmp(caStr_Object, "dns") == 0)
        {
          memcpy(p_Net->dns, addr, 4);
          AppInfo_Write(OFFSETOF(AppInfo_S, NetInfo), (uint8_t *)&AppInfo.NetInfo, sizeof(wiz_NetInfo));
        }
        else if (strcmp(caStr_Object, "rip") == 0)
        {
          memcpy(AppInfo.ucaRip, addr, 4);
          AppInfo_Write(OFFSETOF(AppInfo_S, ucaRip), AppInfo.ucaRip, sizeof(AppInfo.ucaRip));
        }
        bResult = true;
      }
      else
      {
        AppCmdLine_Printf("error: invalid ip format, use xxx.xxx.xxx.xxx\r\n");
        return 0;
      }
    }
    else if (strcmp(caStr_Object, "port") == 0)
    {
      uint16_t port;
      if (sscanf(caStr_Content, "%hu", &port) == 1)
      {
        AppInfo.usLocalPort = port;
        AppInfo_Write(OFFSETOF(AppInfo_S, usLocalPort), (uint8_t *)&AppInfo.usLocalPort, sizeof(AppInfo.usLocalPort));
        bResult = true;
      }
      else
      {
        AppCmdLine_Printf("error: invalid port, must be 1-65535\r\n");
        return 0;
      }
    }

    if (bResult == true)
    {
      if ((AppCmdLine_Port >= AppCmdLine_Port_ETH_S0) && (AppCmdLine_Port <= AppCmdLine_Port_ETH_S7))
      {
      }
      else
      { // 应用参数
        AppEth_Init();
      }
    }
  }
  else if (strcmp(caStr_Action, "r") == 0)
  {
    bResult = true;

    if (strcmp(caStr_Object, "mac") == 0)
    {
      AppCmdLine_Printf("mac:%02X-%02X-%02X-%02X-%02X-%02X\r\n", p_Net->mac[0], p_Net->mac[1], p_Net->mac[2], p_Net->mac[3], p_Net->mac[4], p_Net->mac[5]);
    }
    else if (strcmp(caStr_Object, "ip") == 0)
    {
      AppCmdLine_Printf("IP:%d.%d.%d.%d\r\n", p_Net->ip[0], p_Net->ip[1], p_Net->ip[2], p_Net->ip[3]);
    }
    else if (strcmp(caStr_Object, "sm") == 0)
    {
      AppCmdLine_Printf("sm:%d.%d.%d.%d\r\n", p_Net->sn[0], p_Net->sn[1], p_Net->sn[2], p_Net->sn[3]);
    }
    else if (strcmp(caStr_Object, "gw") == 0)
    {
      AppCmdLine_Printf("gw:%d.%d.%d.%d\r\n", p_Net->gw[0], p_Net->gw[1], p_Net->gw[2], p_Net->gw[3]);
    }
    else if (strcmp(caStr_Object, "dns") == 0)
    {
      AppCmdLine_Printf("dns:%d.%d.%d.%d\r\n", p_Net->dns[0], p_Net->dns[1], p_Net->dns[2], p_Net->dns[3]);
    }
    else if (strcmp(caStr_Object, "rip") == 0)
    {
      AppCmdLine_Printf("rip:%d.%d.%d.%d\r\n", AppInfo.ucaRip[0], AppInfo.ucaRip[1], AppInfo.ucaRip[2], AppInfo.ucaRip[3]);
    }
    else if (strcmp(caStr_Object, "port") == 0)
    {
      AppCmdLine_Printf("port:%d\r\n", AppInfo.usLocalPort);
    }
    else if (strcmp(caStr_Object, "all") == 0)
    {
      AppCmdLine_Printf("mac:%02X-%02X-%02X-%02X-%02X-%02X\r\n", p_Net->mac[0], p_Net->mac[1], p_Net->mac[2], p_Net->mac[3], p_Net->mac[4], p_Net->mac[5]);
      AppCmdLine_Printf("IP:%d.%d.%d.%d\r\n", p_Net->ip[0], p_Net->ip[1], p_Net->ip[2], p_Net->ip[3]);
      AppCmdLine_Printf("sm:%d.%d.%d.%d\r\n", p_Net->sn[0], p_Net->sn[1], p_Net->sn[2], p_Net->sn[3]);
      AppCmdLine_Printf("gw:%d.%d.%d.%d\r\n", p_Net->gw[0], p_Net->gw[1], p_Net->gw[2], p_Net->gw[3]);
      AppCmdLine_Printf("dns:%d.%d.%d.%d\r\n", p_Net->dns[0], p_Net->dns[1], p_Net->dns[2], p_Net->dns[3]);
      AppCmdLine_Printf("rip:%d.%d.%d.%d\r\n", AppInfo.ucaRip[0], AppInfo.ucaRip[1], AppInfo.ucaRip[2], AppInfo.ucaRip[3]);
      AppCmdLine_Printf("port:%d\r\n", AppInfo.usLocalPort);
    }
    else
    {
      bResult = false;
    }

    if (bResult == true)
      return 0;
  }

  AppCmdLine_SendString(p);

  if (bResult == true)
  {
    AppCmdLine_SendString(" pass\r\n");
  }
  else
  {
    AppCmdLine_SendString(" fail\r\n");
  }

  return 0;
}

static char AppCmdLine_CB_Dut(void *p, ...)
{
  int lRes;
  char caStr_Action[8] = {0};
  char caStr_Object[16] = {0};
  bool bResult = false;
  uint16_bits_u uint16_bits;

  sscanf(p, "%*s %s %s %d", caStr_Action, caStr_Object, &lRes);
  AppCmdLine_GetLowerCaseString(caStr_Action);
  AppCmdLine_GetLowerCaseString(caStr_Object);

  if (strcmp(caStr_Action, "w") == 0)
  {
    if (strcmp(caStr_Object, "spp") == 0)
    {
      uint16_bits.usValue = (uint16_t)lRes;
      APPDUT_D0(uint16_bits.b0);
      APPDUT_D1(uint16_bits.b1);
      APPDUT_D2(uint16_bits.b2);
      APPDUT_D3(uint16_bits.b3);
      APPDUT_D4(uint16_bits.b4);
      APPDUT_D5(uint16_bits.b5);
      APPDUT_D6(uint16_bits.b6);
      APPDUT_D7(uint16_bits.b7);

      BspDwt_DelayMS(1);
      APPDUT_STROBE(0);
      BspDwt_DelayMS(3);
      APPDUT_STROBE(1);

      bResult = true;
    }
    else if (strcmp(caStr_Object, "pow") == 0)
    {
      APPDUT_POWER(lRes);

      bResult = true;
    }
    else
    {
    }
  }

  AppCmdLine_SendString(p);

  if (bResult == true)
  {
    AppCmdLine_SendString(" pass\r\n");
  }
  else
  {
    AppCmdLine_SendString(" fail\r\n");
  }

  return 0;
}

static char AppCmdLine_CB_BoardIdx(void *p, ...)
{
  char caStr[16] = {0};
  int lRes;
  bool bResult = true;

  sscanf(p, "%*s %s", caStr);
  AppCmdLine_GetLowerCaseString(caStr);

  if (strcmp(caStr, "?") == 0)
  {
    AppCmdLine_Printf("##:%d\r\n", AppCmdLine_Mgr.ucBoardIdx);
    return 0;
  }
  else if (strcmp(caStr, "w") == 0)
  {
    sscanf(p, "%*s %*s %d", &lRes);
    if ((lRes < AppInfo.ucDefaultPort) || (lRes >= (AppInfo.ucDefaultPort + AppInfo.ucPortNum)))
    {
      bResult = false;
    }
    else
    {
      AppCmdLine_Mgr.ucBoardIdx = lRes;
      if (AppCmdLine_Mgr.ucBoardIdx > 0)
      {
        AppCmdLine_Mgr.usBoardTimeCnt = AppInfo.usBoardTimeOut;
      }
    }
  }
  else
  {
    bResult = false;
  }

  AppCmdLine_SendString(p);

  if (bResult == true)
  {
    AppCmdLine_SendString(" pass\r\n");
  }
  else
  {
    AppCmdLine_SendString(" fail\r\n");
  }

  return 0;
}

void AppCmdLine_Init(void)
{
  memset(&AppCmdLine_Mgr, 0, sizeof(AppCmdLine_Mgr_S));

  AppCmdLine_Mgr.ucBoardIdx = AppInfo.ucDefaultPort;
}

void AppCmdLine_Proc(AppCmdLine_Port_E Port)
{
  uint8_t ucByte;
  bool bDecode = false;
  AppCmdLine_Decode_S *p_Decode;

  if (AppCmdLine_GetRxCount(Port) == 0)
    return;

  AppCmdLine_Port = Port;
  p_Decode = &AppCmdLine_Decode[Port];

  // 逐字节解析
  while (bDecode == false)
  {
    if (AppCmdLine_Read(&ucByte, 1) == false)
      break;

    switch (ucByte)
    {
    default:
    {
      p_Decode->ucaRecvBuff[p_Decode->ucWriteIdx] = ucByte;
      if (++p_Decode->ucWriteIdx >= (APPCMDLINE_RECVBUFF_SIZE - 1))
      {
        bDecode = true;
      }
    }
    break;
    case '\r':
    case '\n':
    case '>':
    {
      if (p_Decode->ucWriteIdx)
      {
        p_Decode->ucEndByte = ucByte;

        bDecode = true;
      }
    }
    break;
    case 0x08:
    { // 删除一个字符
      if (p_Decode->ucWriteIdx)
      {
        p_Decode->ucWriteIdx -= 1;
        p_Decode->ucaRecvBuff[p_Decode->ucWriteIdx] = 0;
      }
    }
    break;
    }
  }

  if ((bDecode == true) && (p_Decode->ucWriteIdx))
  {
    uint8_t ucCnt = 0;
    char caCmd[16] = {0};
    bDecode = false;

    AppCmdLine_Mgr.usBoardTimeCnt = AppInfo.usBoardTimeOut;

    if (AppCmdLine_Mgr.bReturnRecv)
    {
      AppCmdLine_Send(p_Decode->ucaRecvBuff, p_Decode->ucWriteIdx);
      AppCmdLine_SendString("\r\n");
    }

    if (strstr((char *)p_Decode->ucaRecvBuff, "##:") == 0)
    {
      for (uint8_t i = 0; i < p_Decode->ucWriteIdx; i++)
      {
        if ((p_Decode->ucaRecvBuff[i] >= 'a') && (p_Decode->ucaRecvBuff[i] <= 'z'))
          break;
        if ((p_Decode->ucaRecvBuff[i] >= 'A') && (p_Decode->ucaRecvBuff[i] <= 'Z'))
          break;
        ucCnt += 1;
      }
    }

    if (ucCnt >= p_Decode->ucWriteIdx)
    {
      AppCmdLine_SendString("command is illegal\r\n");
    }
    else
    {
      for (uint8_t i = 0; i < 9; i++)
      {
        ucByte = p_Decode->ucaRecvBuff[ucCnt + i];
        if ((ucByte == '_') || (ucByte == ' ') || (ucByte == '\0'))
        {
          break;
        }

        caCmd[i] = ucByte;
      }

      AppCmdLine_GetLowerCaseString(caCmd);

      if (strstr(caCmd, ":") != 0)
      {
        uint8_t ucCmdIdx = usCmdNum;
        for (uint8_t i = 0; i < usCmdNum; i++)
        {
          if (strcmp(caCmd, AppCmdLineList[i].p_caCmdStr) == 0)
          {
            ucCmdIdx = i;
            break;
          }
        }

        if (ucCmdIdx == usCmdNum)
        {
          AppCmdLine_SendString("command is illegal\r\n");
        }
        else
        {
          if (AppCmdLineList[ucCmdIdx].p_Func)
          {
            AppCmdLineList[ucCmdIdx].p_Func(p_Decode->ucaRecvBuff);
          }
        }
      }
      else
      {
        switch (AppCmdLine_Mgr.ucBoardIdx)
        {
        default:
        case 0:
          AppCmdLine_SendString("BoardIdx is 0\r\n");
          break;
        case 1:
          BspUart_SendBuff(BspUartCom_DUT, p_Decode->ucaRecvBuff, p_Decode->ucWriteIdx);
          BspUart_SendBuff(BspUartCom_DUT, "\r\n", 2);
          break;
        case 2:
          BspUart_SendBuff(BspUartCom_DUT2, p_Decode->ucaRecvBuff, p_Decode->ucWriteIdx);
          BspUart_SendBuff(BspUartCom_DUT2, "\r\n", 2);
          break;
        case 3:
          BspComPort_Send(BspComPort_Name2Handle("uart_lcd"), p_Decode->ucaRecvBuff, p_Decode->ucWriteIdx);
          break;
        case 4:
          BspComPort_Send(BspComPort_Name2Handle("ext_2"), p_Decode->ucaRecvBuff, p_Decode->ucWriteIdx);
          break;
        case 5:
          BspComPort_Send(BspComPort_Name2Handle("ext_3"), p_Decode->ucaRecvBuff, p_Decode->ucWriteIdx);
          break;
        case 6:
          BspComPort_Send(BspComPort_Name2Handle("ext_4"), p_Decode->ucaRecvBuff, p_Decode->ucWriteIdx);
          break;
        }
      }
    }

    memset(p_Decode, 0, sizeof(AppCmdLine_Decode_S));
  }
}
