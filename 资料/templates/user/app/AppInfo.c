#include "includes.h"

AppInfo_S AppInfo;

static const wiz_NetInfo default_net_info = {
    .mac = {0x00, 0x08, 0xdc, 0x12, 0x22, 0x12},
    .ip = {192, 168, 1, 30},
    .gw = {192, 168, 1, 1},
    .sn = {255, 255, 255, 0},
    .dns = {8, 8, 8, 8},
    .dhcp = NETINFO_STATIC};

bool AppInfo_Read(uint16_t usAddr, uint8_t *p_ucaBuff, uint16_t usBuffLen)
{
  if (!p_ucaBuff)
    return false;

  return AppPort_AT24C08C_Read_MutiByte(APPINFO_ADDR + usAddr, p_ucaBuff, usBuffLen);
}

bool AppInfo_Write(uint16_t usAddr, uint8_t *p_ucaBuff, uint16_t usBuffLen)
{
  if (!p_ucaBuff)
    return false;

  return AppPort_AT24C08C_Write_MutiByte(APPINFO_ADDR + usAddr, p_ucaBuff, usBuffLen);
}

void AppInfo_Init(void)
{
  uint8_t ucCheckSum;
  AppInfo_Read(OFFSETOF(AppInfo_S, ucCheckSum), &ucCheckSum, 1);

  if (ucCheckSum != APPINFO_CHECKSUM)
  {
    memset(&AppInfo, 0, sizeof(AppInfo_S));

    AppInfo.ucBackLight = 100;
    AppInfo.usBoardTimeOut = 10000; // 计时精度1ms
    AppInfo.ucDefaultPort = 0;
    AppInfo.ucPortNum = 6;

    AppInfo.ulBaudRate_UART = 115200;
    AppInfo.ulBaudRate_USB = 115200;
    AppInfo.ulBaudRate_DUT = 115200;
    AppInfo.ulBaudRate_DUT2 = 115200;

    memcpy(&AppInfo.NetInfo, &default_net_info, sizeof(wiz_NetInfo));
    AppInfo.usLocalPort = 8080;
    AppInfo.ucaRip[0] = 192;
    AppInfo.ucaRip[1] = 168;
    AppInfo.ucaRip[2] = 1;
    AppInfo.ucaRip[3] = 100;

    AppInfo.ucCheckSum = APPINFO_CHECKSUM;

    AppInfo_Write(0, (uint8_t *)&AppInfo, sizeof(AppInfo_S));

    return;
  }

  AppInfo_Read(0, (uint8_t *)&AppInfo, sizeof(AppInfo_S));
}

void AppInfo_TrigStorage(uint16_t usDelay)
{
  (void)usDelay;
}

void AppInfo_Proc(void)
{
}
