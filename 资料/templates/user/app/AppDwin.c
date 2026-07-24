#include "includes.h"

AppDwin_Control_S AppDwin_Control;

static char caPrintBuff[128];

static void AppDwin_Send(uint8_t *p_ucaBuff, uint16_t usBuffLen)
{
  BspComPort_Send(BspComPort_Name2Handle("uart_lcd"), p_ucaBuff, usBuffLen);
}

static uint16_t AppDwin_Recv(uint8_t *p_ucaBuff, uint16_t usBuffSize, uint8_t ucTimeOut)
{
  if (!p_ucaBuff)
    return 0;
  if (!usBuffSize)
    return 0;
  if (!ucTimeOut)
    return 0;

  while (ucTimeOut--)
  {
    rt_thread_delay(1);

    if (BspComPort_RxDoneCheck(BspComPort_Name2Handle("uart_lcd"), true) == true)
    {
      return BspComPort_Read(BspComPort_Name2Handle("uart_lcd"), p_ucaBuff, usBuffSize);
    }
  }

  return 0;
}

static bool AppDwin_ReadByte(uint8_t *p_ucByte)
{
  if (!p_ucByte)
    return false;

  return (bool)BspComPort_Read(BspComPort_Name2Handle("uart_lcd"), p_ucByte, 1);
}

static bool AppDwin_WriteRam_CheckRsult(uint16_t usAddr, uint8_t *p_ucaBuff, uint16_t usBuffLen)
{
  uint8_t ucaBuff[6] = {0x5A, 0xA5, 0x03, 0x82, 0x00, 0x00};
  const uint8_t ucResult[6] = {0x5A, 0xA5, 0x03, 0x82, 0x4F, 0x4B};

  if (!p_ucaBuff)
    return false;
  if (!usBuffLen)
    return false;

  ucaBuff[2] += usBuffLen;
  ucaBuff[4] = SH8(usAddr);
  ucaBuff[5] = SL8(usAddr);

  AppDwin_Send(ucaBuff, sizeof(ucaBuff));
  AppDwin_Send(p_ucaBuff, usBuffLen);

  if (AppDwin_Recv(ucaBuff, sizeof(ucaBuff), 200) == 6)
  {
    if (memcmp(ucaBuff, ucResult, sizeof(ucResult)) == 0)
    {
      return true;
    }
  }

  return false;
}

static bool AppDwin_WriteRam(uint16_t usAddr, uint8_t *p_ucaBuff, uint16_t usBuffLen)
{
  uint8_t ucaBuff[6] = {0x5A, 0xA5, 0x03, 0x82, 0x00, 0x00};

  if (!p_ucaBuff)
    return false;
  if (!usBuffLen)
    return false;

  ucaBuff[2] += usBuffLen;
  ucaBuff[4] = SH8(usAddr);
  ucaBuff[5] = SL8(usAddr);

  AppDwin_Send(ucaBuff, sizeof(ucaBuff));
  AppDwin_Send(p_ucaBuff, usBuffLen);

  return true;
}

static bool AppDwin_WriteRam_AppendFFFF(uint16_t usAddr, uint8_t *p_ucaBuff, uint16_t usBuffLen)
{
  uint8_t ucaBegin[6] = {0x5A, 0xA5, 0x03, 0x82, 0x00, 0x00};

  if (!p_ucaBuff)
    return false;
  if (!usBuffLen)
    return false;

  ucaBegin[2] += (usBuffLen + 2);
  ucaBegin[4] = SH8(usAddr);
  ucaBegin[5] = SL8(usAddr);

  AppDwin_Send(ucaBegin, sizeof(ucaBegin));
  AppDwin_Send(p_ucaBuff, usBuffLen);
  AppDwin_Send("\xFF\xFF", 2);

  return true;
}

static bool AppDwin_ReadRam(uint16_t usAddr, uint8_t ucReadCount, uint8_t *p_ucaBuff, uint16_t usBuffSize)
{
  uint8_t ucaBegin[6] = {0x5A, 0xA5, 0x04, 0x83, 0x00, 0x00};

  if (!ucReadCount)
    return false;
  if (!p_ucaBuff)
    return false;
  if (usBuffSize < (ucReadCount * 2))
    return false;

  BspComPort_RxDoneClr(BspComPort_Name2Handle("uart_lcd"));

  ucaBegin[4] = SH8(usAddr);
  ucaBegin[5] = SL8(usAddr);

  AppDwin_Send(ucaBegin, sizeof(ucaBegin));
  AppDwin_Send(&ucReadCount, sizeof(uint8_t));

  if (AppDwin_Recv(p_ucaBuff, usBuffSize, 200) == (7 + (ucReadCount * 2)))
  {
    memmove(p_ucaBuff, &p_ucaBuff[7], (ucReadCount * 2));
    memset(&p_ucaBuff[ucReadCount * 2], 0, usBuffSize - (ucReadCount * 2));

    return true;
  }

  return false;
}

/// @brief 写字符串(中英文混编)到文本控件
/// @param usAddr 变量地址
/// @param p_caString 字符串
/// @return
bool AppDwin_WriteString(uint16_t usAddr, const char *p_caString)
{
  if (usAddr < 0x6000)
    return false; // 定义文本类控件的变量范围为6000以后的区域
  if (!p_caString)
    return false;

  return AppDwin_WriteRam_AppendFFFF(usAddr, (uint8_t *)p_caString, strlen((const char *)p_caString));
}

bool AppDwin_PrintString(uint16_t usAddr, const char *p_caString, ...)
{
  if (usAddr < 0x6000)
    return false; // 定义文本类控件的变量范围为6000以后的区域
  if (!p_caString)
    return false;

  va_list ap;
  memset(caPrintBuff, 0, sizeof(caPrintBuff));
  va_start(ap, p_caString);
  vsprintf(caPrintBuff, (const char *)p_caString, ap); // 将格式字符串与后面的参数绑定为一个字符串，拷贝到输出缓存
  va_end(ap);

  return AppDwin_WriteRam_AppendFFFF(usAddr, (uint8_t *)caPrintBuff, strlen((const char *)caPrintBuff));
}

bool AppDwin_Write2Bytes(uint16_t usAddr, uint16_t usValue)
{
  uint8_t ucaValueBuff[2];

  ucaValueBuff[0] = SH8(usValue);
  ucaValueBuff[1] = SL8(usValue);

  return AppDwin_WriteRam(usAddr, ucaValueBuff, sizeof(uint16_t));
}

bool AppDwin_Write4Bytes(uint16_t usAddr, uint32_t ulValue)
{
  uint8_t ucaValueBuff[4];

  ucaValueBuff[0] = LHH8(ulValue);
  ucaValueBuff[1] = LH8(ulValue);
  ucaValueBuff[2] = LM8(ulValue);
  ucaValueBuff[3] = LL8(ulValue);

  return AppDwin_WriteRam(usAddr, ucaValueBuff, sizeof(uint32_t));
}

/// @brief 读取当前页面
/// @param
/// @return
uint16_t AppDwin_PageRead(void)
{
  /*
  指令示例：
  读：5AA5 04 83 0014 01
  应答：5AA5 06 83 0014 01 0007(0007 为 07 号页面)
  */
  uint8_t ucaRecvBuff[16] = {0};

  if (AppDwin_ReadRam(0x14, 1, ucaRecvBuff, sizeof(ucaRecvBuff)) == true)
  {
    return C2S(ucaRecvBuff[0], ucaRecvBuff[1]);
  }

  return 0xFFFF;
}

/// @brief 设置页面
/// @param usPageCode 页面
/// @return
bool AppDwin_PageSet(uint16_t usPageCode)
{
  uint8_t ucaBuff[4] = {0x5A, 0x01, 0x00, 0x00};

  ucaBuff[2] = SH8(usPageCode);
  ucaBuff[3] = SL8(usPageCode);

  return AppDwin_WriteRam(0x84, ucaBuff, sizeof(ucaBuff));
}

/// @brief 打开或关闭触控控件的触控功能(基础触控不适用,当页面存在基础触控时,统计控件序号需要剔除)
/// @param usPageCode 页面
/// @param ucWidgetId 控件序号
/// @param ucWidgetType 控件类型(应用开发指南2024 6.1 触控功能一览表)
/// @param bNewState true:打开触控功能
/// @return
bool AppDwin_TouchEnable(uint16_t usPageCode, uint8_t ucWidgetId, uint8_t ucWidgetType, bool bNewState)
{
  uint8_t ucaBuff[8] = {0};

  ucaBuff[0] = 0x5A;
  ucaBuff[1] = 0xA5;
  ucaBuff[2] = SH8(usPageCode);
  ucaBuff[3] = SL8(usPageCode);
  ucaBuff[4] = ucWidgetId;
  ucaBuff[5] = ucWidgetType;
  if (bNewState == true)
  {
    ucaBuff[7] = 1;
  }

  if (AppDwin_WriteRam(0xB0, ucaBuff, sizeof(ucaBuff)) == false)
    return false;

  {
    uint8_t ucTimeOut = 25;
    uint8_t ucaRecvBuff[16] = {0};

    while (ucTimeOut--)
    {
      rt_thread_delay(1);

      if (AppDwin_ReadRam(0xB0, 1, ucaRecvBuff, sizeof(ucaRecvBuff)) == true)
      {
        if (ucaRecvBuff[0] == 0)
          return true;
      }
    }
  }

  return false;
}

/// @brief 移动控件位置(常用于隐藏,移到屏幕的物理分辨率外就是隐藏)
/// @param usSpAddr 描述指针
/// @param ulNewPos 新位置(X,Y)
/// @return 返回移动前的位置
uint32_t AppDwin_WidgetMovePos(uint16_t usSpAddr, uint32_t ulNewPos)
{
  uint32_t ulOrgPos = 0;
  uint8_t ucaRecvBuff[16] = {0};

  usSpAddr += 1; // 移动到X,Y描述位置

  if (AppDwin_ReadRam(usSpAddr, 2, ucaRecvBuff, sizeof(ucaRecvBuff)) == true)
  {
    ulOrgPos = C2L(ucaRecvBuff[0], ucaRecvBuff[1], ucaRecvBuff[2], ucaRecvBuff[3]);
  }

  AppDwin_Write4Bytes(usSpAddr, ulNewPos);

  return ulOrgPos;
}

void AppDwin_BackLightSet(uint8_t ucPercent)
{
  if (ucPercent > 100)
    ucPercent = 100;
  if (ucPercent < 1)
    ucPercent = 1;

  AppDwin_WriteRam(0x82, &ucPercent, sizeof(uint8_t));
}

bool AppDwin_PageOverlay(uint16_t usPageCode)
{
  uint8_t ucaBuff[4] = {0x5A, 0x01, 0x00, 0x00};

  ucaBuff[2] = SH8(usPageCode);
  ucaBuff[3] = SL8(usPageCode);

  return AppDwin_WriteRam_CheckRsult(0x00E8, ucaBuff, 4);
}

bool AppDwin_PageOverlay_Disable(void)
{
  uint8_t ucaBuff[4] = {0x00};

  return AppDwin_WriteRam_CheckRsult(0x00E8, ucaBuff, 4);
}

static void AppDwin_PageChange(AppDwin_Page_E TargetPage)
{
  if (AppDwin_Control.CurrentPage == TargetPage)
    return;

  AppDwin_Control.TargetPage = TargetPage;

  switch (AppDwin_Control.TargetPage)
  {
  default:
    break;
  case AppDwin_Page_Main:
    break;
  case AppDwin_Page_Common:
  {
    wiz_NetInfo *p_Net = &AppInfo.NetInfo;

    AppDwin_PrintString(0x6000, "%u", AppInfo.usLocalPort);
    AppDwin_PrintString(0x6040, "%d.%d.%d.%d", p_Net->ip[0], p_Net->ip[1], p_Net->ip[2], p_Net->ip[3]);
    AppDwin_PrintString(0x6080, "%d.%d.%d.%d", p_Net->sn[0], p_Net->sn[1], p_Net->sn[2], p_Net->sn[3]);
    AppDwin_PrintString(0x6100, "%d.%d.%d.%d", p_Net->gw[0], p_Net->gw[1], p_Net->gw[2], p_Net->gw[3]);
  }
  break;
  case AppDwin_Page_Info:
  {
    AppDwin_PrintString(0x6140, "123456789"); // 序列号
    AppDwin_PrintString(0x6180, "%s", ((uint32_t)strstr(APPINFO_VERSION, "PRG:") + strlen("PRG:")));
  }
  break;
  case AppDwin_Page_Alarm:
    break;
  case AppDwin_Page_Setting:
  {
    AppDwin_WriteString(0x61C0, "中文");
    AppDwin_WriteString(0x6200, "English");

    if (AppDwin_Control.ucLanguage)
    {
      AppDwin_WriteString(0x6240, "Manual");
      AppDwin_WriteString(0x6280, "Auto");
    }
    else
    {
      AppDwin_WriteString(0x6240, "手动");
      AppDwin_WriteString(0x6280, "自动");
    }
  }
  break;
  case AppDwin_Page_Log:
    break;
  }
}

void AppDwin_Init(void)
{
  memset(&AppDwin_Control, 0, sizeof(AppDwin_Control_S));

  {
    uint16_t usValue;
    AppDwin_Control.ucLanguage = AppInfo.ucLanguage;
    usValue = AppDwin_Control.ucLanguage;
    if (usValue > 1)
      usValue = 1;
    AppDwin_Write2Bytes(0x0FFF, usValue); // 同步语言

    AppDwin_Write2Bytes(0xC080, 17 + usValue); // 更新色块位置
  }

  AppDwin_PageChange(AppDwin_Page_Main);

  AppDwin_PageSet(AppDwin_Page_Main);
}

static void AppDwin_Decode(uint16_t usRegAddr, uint8_t ucRegNum, uint8_t *p_ucaRegValue)
{
  // BspUart_SendBuff(BspUartCom_RS232, (uint8_t *)&usRegAddr, sizeof(usRegAddr));
  // BspUart_SendBuff(BspUartCom_RS232, (uint8_t *)&ucRegNum, sizeof(ucRegNum));
  // BspUart_SendBuff(BspUartCom_RS232, p_ucaRegValue, ucRegNum * 2);

  if (ucRegNum == 1)
  {
    // BspBuzzer_Start(20, 0, 1);

    uint16_t usRegValue = C2S(p_ucaRegValue[0], p_ucaRegValue[1]);

    switch (usRegAddr)
    {
    default:
      break;
    case 0xC000: // 触摸按键
    {
      switch (usRegValue)
      {
      default:
        break;
      case 0x0100:
      case 0x0200:
      case 0x0300:
      case 0x0400:
      {
        AppDwin_PageChange(AppDwin_Page_Main);
      }
      break;
      case 0x0017:
      case 0x0201:
      case 0x0301:
      case 0x0401:
      {
        AppDwin_PageChange(AppDwin_Page_Common);
      }
      break;
      case 0x0018:
      case 0x0101:
      case 0x0302:
      case 0x0402:
      {
        AppDwin_PageChange(AppDwin_Page_Info);
      }
      break;
      case 0x0019:
      case 0x0102:
      case 0x0202:
      case 0x0403:
      {
        AppDwin_PageChange(AppDwin_Page_Alarm);
      }
      break;
      case 0x0020:
      case 0x0103:
      case 0x0203:
      case 0x0303:
      {
        AppDwin_PageChange(AppDwin_Page_Setting);
      }
      break;
      case 0x0304:
      {
        AppDwin_PageChange(AppDwin_Page_Log);
      }
      break;
      case 0x0700:
      {
        AppDwin_PageChange(AppDwin_Page_Alarm);
      }
      break;
      case 0x0800:
      {
        AppDwin_PageOverlay_Disable();
      }
      }
    }
    break;
    case 0xC080:
    {
      switch (usRegValue)
      {
      default:
        break;
      case 0x0011:
      { // 中文
        uint16_t usValue = 0;
        if (AppInfo.ucLanguage != usValue)
        {
          AppInfo.ucLanguage = (uint8_t)usValue;
          AppDwin_Control.ucLanguage = (uint8_t)usValue;

          AppInfo_Write(OFFSETOF(AppInfo_S, ucLanguage), &AppInfo.ucLanguage, sizeof(AppInfo.ucLanguage));
          AppDwin_Write2Bytes(0x0FFF, usValue); // 同步语言

          // 同步文本框
          AppDwin_WriteString(0x6240, "手动");
          AppDwin_WriteString(0x6280, "自动");
        }
      }
      break;
      case 0x0012:
      { // 英文
        uint16_t usValue = 1;
        if (AppInfo.ucLanguage != usValue)
        {
          AppInfo.ucLanguage = (uint8_t)usValue;
          AppDwin_Control.ucLanguage = (uint8_t)usValue;

          AppInfo_Write(OFFSETOF(AppInfo_S, ucLanguage), &AppInfo.ucLanguage, sizeof(AppInfo.ucLanguage));
          AppDwin_Write2Bytes(0x0FFF, usValue); // 同步语言

          // 同步文本框
          AppDwin_WriteString(0x6240, "Manual");
          AppDwin_WriteString(0x6280, "Auto");
        }
      }
      break;
      }
    }
    break;
    case 0xC100:
    {
      switch (usRegValue)
      {
      default:
        break;
      case 0x0011:
      { // 手动
      }
      break;
      case 0x0012:
      { // 自动
      }
      break;
      }
    }
    break;
    case 0xC180:
    {
      if ((usRegValue >= 1) && (usRegValue <= 16))
      {
        AppDut_ChannelSelect(usRegValue);
      }
    }
    break;
    case 0x0014: // 返回页面ID
    {
    }
    break;
    }
  }
  else if (ucRegNum == 2)
  { // 键盘输入
    uint32_t ulInPutValue = C2L(p_ucaRegValue[0], p_ucaRegValue[1], p_ucaRegValue[2], p_ucaRegValue[3]);
  }
}

void AppDwin_Proc(void)
{
  uint8_t ucByte;
  static uint8_t ucDecodeStep = 0;
  static uint8_t ucLength;
  static uint8_t ucCmd;
  static uint16_t usRegAddr;
  static uint8_t ucRegNum;
  static uint16_t usReadIdx;
  static uint8_t ucaRegValue[64];

  while (1)
  {
    if (AppDwin_ReadByte(&ucByte) == false)
      break;

    switch (ucDecodeStep)
    {
    default:
    case 0:
    { // 帧头 H
      ucDecodeStep = 0;

      if (ucByte == 0x5A)
      {
        ucDecodeStep += 1;
      }
      else
      {
        ucDecodeStep = 0;
      }
    }
    break;
    case 1:
    { // 帧头 L
      if (ucByte == 0xA5)
      {
        ucDecodeStep += 1;
      }
      else
      {
        ucDecodeStep = 0;
      }
    }
    break;
    case 2:
    { // 长度
      ucLength = ucByte;
      ucDecodeStep += 1;
    }
    break;
    case 3:
    { // 命令
      ucCmd = ucByte;
      if ((ucCmd == 0x82) || (ucCmd == 0x83))
      {
        ucDecodeStep += 1;
      }
      else
      {
        ucDecodeStep = 0;
      }
    }
    break;
    case 4:
    { // 变量地址 H
      usRegAddr = ucByte;
      ucDecodeStep += 1;
    }
    break;
    case 5:
    { // 变量地址 L
      usRegAddr <<= 8;
      usRegAddr |= ucByte;

      if (ucCmd == 0x82)
      {
        ucDecodeStep = 0; // 写指令固定返回0x4F 0x4B
      }
      else
      {
        ucDecodeStep += 1;
      }
    }
    break;
    case 6:
    { // 寄存器个数
      ucRegNum = ucByte;
      ucDecodeStep += 1;

      ucLength -= 4; // 减去命令和地址,寄存器个数的长度
      usReadIdx = 0;
      memset(ucaRegValue, 0, sizeof(ucaRegValue));
    }
    break;
    case 7:
    { // 寄存器数据
      ucaRegValue[usReadIdx++] = ucByte;

      if ((usReadIdx >= ucLength) || (usReadIdx >= sizeof(ucaRegValue)))
      {
        ucDecodeStep = 0; // 这帧数据完毕

        AppDwin_Decode(usRegAddr, ucRegNum, ucaRegValue);
      }
    }
    break;
    }
  }
}
