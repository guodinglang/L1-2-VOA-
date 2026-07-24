#include "includes.h"

AppItla_S AppItla_C;
AppItla_S AppItla_L;

/// @brief 发送数据
/// @param p_ucaBuff
/// @param ucBuffLen
static void AppItla_Send(AppItla_S *p_Itla, uint8_t *p_ucaBuff, uint8_t ucBuffLen)
{
  if (!p_Itla)
    return;
  if (!p_ucaBuff)
    return;

  if (p_Itla == &AppItla_C)
  {
    BspUart_ClrRxState(BspUartCom_DUT2);
    BspUart_SendBuff(BspUartCom_DUT2, p_ucaBuff, ucBuffLen);
  }
  else if (p_Itla == &AppItla_L)
  {
    BspUart_ClrRxState(BspUartCom_DUT2);
    BspUart_SendBuff(BspUartCom_DUT2, p_ucaBuff, ucBuffLen);
  }
}

/// @brief 接收数据
/// @param p_ucaBuff
/// @param ucBuffSize
/// @return
static uint8_t AppItla_Recv(AppItla_S *p_Itla, uint8_t *p_ucaBuff, uint8_t ucBuffSize, uint16_t usTimeOut)
{
  uint32_t ulTick;
  if (!p_ucaBuff)
    return 0;
  if (!ucBuffSize)
    return 0;
  if (!usTimeOut)
    return 0;

  if (p_Itla == &AppItla_C)
  {
    ulTick = rt_tick_get();

    while (1)
    {
      rt_thread_delay(1);

      if (BspUart_GetRxState(BspUartCom_DUT2) == true)
      {
        BspUart_ClrRxState(BspUartCom_DUT2);
        return BspUart_GetBuff(BspUartCom_DUT2, p_ucaBuff, ucBuffSize);
      }

      if ((rt_tick_get() - ulTick) >= usTimeOut)
        break;
    }
  }
  else if (p_Itla == &AppItla_L)
  {
    ulTick = rt_tick_get();

    while (1)
    {
      rt_thread_delay(1);

      if (BspUart_GetRxState(BspUartCom_DUT2) == true)
      {
        BspUart_ClrRxState(BspUartCom_DUT2);
        return BspUart_GetBuff(BspUartCom_DUT2, p_ucaBuff, ucBuffSize);
      }

      if ((rt_tick_get() - ulTick) >= usTimeOut)
        break;
    }
  }

  return 0;
}

/// @brief itla模块计算校验码
/// @param p_ucaCmd 数据流
static void AppItla_CheckSumCalc(uint8_t *p_ucaCmd)
{
  uint8_t ucBip8 = (p_ucaCmd[0] & 0x0F) ^ p_ucaCmd[1] ^ p_ucaCmd[2] ^ p_ucaCmd[3];
  p_ucaCmd[0] &= ~0xF0;
  p_ucaCmd[0] |= (((ucBip8 & 0xF0) >> 4) ^ (ucBip8 & 0x0F)) << 4;
}

/// @brief itla模块读取寄存器
/// @param ucReg 寄存器
/// @param p_usValue 寄存器值
/// @param p_ucStatus 返回的状态
/// @return
static bool AppItla_ReadReg(AppItla_S *p_Itla, uint8_t ucReg, uint16_t *p_usValue, uint8_t *p_ucStatus)
{
  uint8_t ucRecvCnt;
  uint8_t ucaCmdBuff[4] = {0};

  if (!p_usValue)
    return false;

  ucaCmdBuff[1] = ucReg;

  AppItla_CheckSumCalc(ucaCmdBuff);

  AppItla_Send(p_Itla, ucaCmdBuff, sizeof(ucaCmdBuff));
  ucRecvCnt = AppItla_Recv(p_Itla, ucaCmdBuff, sizeof(ucaCmdBuff), 200);

  if (ucRecvCnt == sizeof(ucaCmdBuff))
  {
    if (p_ucStatus)
    {
      *p_ucStatus = ucaCmdBuff[0] & 0x03;
    }

    *p_usValue = ucaCmdBuff[2];
    *p_usValue <<= 8;
    *p_usValue |= ucaCmdBuff[3];

    return true;
  }

  return false;
}

/// @brief itla模块读取寄存器(扩展地址模式下)
/// @param p_ucaBuff 寄存器数据
/// @param ucBuffSize 缓冲长度
/// @param ucTimes 数据总长度/2
/// @return
static bool AppItla_ReadBuff(AppItla_S *p_Itla, uint8_t *p_ucaBuff, uint8_t ucBuffSize, uint8_t ucTimes)
{
  uint8_t ucRecvCnt;
  uint8_t ucaCmdBuff[4] = {0};
  uint8_t *p_ucaSource = p_ucaBuff;
  bool bResult = true;

  if (!p_ucaBuff)
    return false;
  if (!ucTimes)
    return false;

  ucaCmdBuff[1] = 0x0B;

  AppItla_CheckSumCalc(ucaCmdBuff);

  for (uint8_t i = 0; i < ucTimes; i++)
  {
    AppItla_Send(p_Itla, ucaCmdBuff, sizeof(ucaCmdBuff));
    ucRecvCnt = AppItla_Recv(p_Itla, ucaCmdBuff, sizeof(ucaCmdBuff), 200);

    if (ucRecvCnt == sizeof(ucaCmdBuff))
    {
      *p_ucaBuff = ucaCmdBuff[2];
      p_ucaBuff += 1;

      if ((p_ucaBuff - p_ucaSource) >= ucBuffSize)
        break;

      *p_ucaBuff = ucaCmdBuff[3];
      p_ucaBuff += 1;

      if ((p_ucaBuff - p_ucaSource) >= ucBuffSize)
        break;
    }
    else
    {
      bResult = false;
      break;
    }
  }

  return bResult;
}

/// @brief itla模块写寄存器
/// @param ucReg 寄存器地址
/// @param usValue 寄存器数据
/// @param p_ucStatus 模块返回的状态(可选)
/// @return
static bool AppItla_WriteReg(AppItla_S *p_Itla, uint8_t ucReg, uint16_t usValue, uint8_t *p_ucStatus)
{
  uint8_t ucRecvCnt;
  uint8_t ucaCmdBuff[4] = {0};

  ucaCmdBuff[0] = 0x01;
  ucaCmdBuff[1] = ucReg;
  ucaCmdBuff[2] = (uint8_t)(usValue >> 8);
  ucaCmdBuff[3] = (uint8_t)(usValue);

  AppItla_CheckSumCalc(ucaCmdBuff);

  AppItla_Send(p_Itla, ucaCmdBuff, sizeof(ucaCmdBuff));
  ucRecvCnt = AppItla_Recv(p_Itla, ucaCmdBuff, sizeof(ucaCmdBuff), 200);

  if (ucRecvCnt == sizeof(ucaCmdBuff))
  {
    if (p_ucStatus)
    {
      *p_ucStatus = ucaCmdBuff[0] & 0x03;
    }

    if ((ucaCmdBuff[2] != (uint8_t)(usValue >> 8)) || (ucaCmdBuff[3] != (uint8_t)(usValue)))
    {
      return false;
    }

    return true;
  }

  return false;
}

/// @brief itla模块读字符串
/// @param String 字符串类型
/// @param p_Itla itla对象
/// @return
bool AppItla_ReadString(AppItla_String_E String, AppItla_S *p_Itla)
{
  uint16_t usCount;
  uint8_t *p_ucaDest;
  const uint8_t ucaStringRegList[] = {0x02, 0x03, 0x04, 0x05, 0x06};
  const uint16_t usaOffsetList[] = {
      OFFSETOF(AppItla_S, caManufacturetString),
      OFFSETOF(AppItla_S, caModelString),
      OFFSETOF(AppItla_S, caSNString),
      OFFSETOF(AppItla_S, caProductDateString),
      OFFSETOF(AppItla_S, caVersionString),
  };
  const uint8_t ucaDestSize[] = {
      sizeof(p_Itla->caManufacturetString),
      sizeof(p_Itla->caModelString),
      sizeof(p_Itla->caSNString),
      sizeof(p_Itla->caProductDateString),
      sizeof(p_Itla->caVersionString),
  };

  if (String >= AppItla_String_Unknow)
    return false;
  if (!p_Itla)
    return false;

  p_ucaDest = (uint8_t *)((uint32_t)p_Itla + usaOffsetList[String]);

  if (AppItla_ReadReg(p_Itla, ucaStringRegList[String], &usCount, 0) == false)
    return false;

  if (usCount % 2)
    usCount += 1;
  usCount /= 2;
  usCount += 1;

  if (AppItla_ReadBuff(p_Itla, p_ucaDest, (ucaDestSize[String] - 1), usCount) == false)
    return false;

  return true;
}

/// @brief itla模块读值
/// @param Value 值类型
/// @param p_Itla itla对象
/// @return
bool AppItla_ReadValue(AppItla_Value_E Value, AppItla_S *p_Itla)
{
  uint16_t usValue;
  uint16_t usValueH;

  if (!p_Itla)
    return false;

  switch (Value)
  {
  default:
    break;
  case AppItla_Value_Temp:
  {
    if (AppItla_ReadReg(p_Itla, 0x43, &usValue, 0) == false)
      return false;

    p_Itla->lTemp = (int32_t)usValue;
  }
  break;
  case AppItla_Value_CurrFreqStep:
  {
    if (AppItla_ReadReg(p_Itla, 0x34, &usValue, 0) == false)
      return false;

    p_Itla->ulCurrFreqStep = (uint32_t)usValue * 100;
  }
  break;
  case AppItla_Value_MinFreqStep:
  {
    if (AppItla_ReadReg(p_Itla, 0x56, &usValue, 0) == false)
      return false;

    p_Itla->ulMinFreqStep = (uint32_t)usValue * 100;
  }
  break;
  case AppItla_Value_FirstChannelFreq:
  {
    if (AppItla_ReadReg(p_Itla, 0x35, &usValueH, 0) == false)
      return false;
    if (AppItla_ReadReg(p_Itla, 0x36, &usValue, 0) == false)
      return false;

    p_Itla->ulFirstChannelFreq = (usValueH * 1000000) + (usValue * 100);
  }
  break;
  case AppItla_Value_CurrPower:
  {
    if (AppItla_ReadReg(p_Itla, 0x42, &usValue, 0) == false)
      return false;

    p_Itla->sCurrPower_dBm = (int16_t)usValue;
  }
  break;
  case AppItla_Value_CurrFreq:
  {
    if (AppItla_ReadReg(p_Itla, 0x40, &usValueH, 0) == false)
      return false;
    if (AppItla_ReadReg(p_Itla, 0x41, &usValue, 0) == false)
      return false;

    p_Itla->ulCurrFreq = (usValueH * 1000000) + (usValue * 100);
  }
  break;
  case AppItla_Value_PowerRange:
  {
    if (AppItla_ReadReg(p_Itla, 0x50, &usValue, 0) == false)
      return false;
    if (AppItla_ReadReg(p_Itla, 0x51, &usValueH, 0) == false)
      return false;

    p_Itla->sMinPower_dBm = (int16_t)usValue;
    p_Itla->sMaxPower_dBm = (int16_t)usValueH;
  }
  break;
  case AppItla_Value_FreqRange:
  {
    if (AppItla_ReadReg(p_Itla, 0x52, &usValueH, 0) == false)
      return false;
    if (AppItla_ReadReg(p_Itla, 0x53, &usValue, 0) == false)
      return false;

    p_Itla->ulMinFreq = (usValueH * 1000000) + (usValue * 100);

    if (AppItla_ReadReg(p_Itla, 0x54, &usValueH, 0) == false)
      return false;
    if (AppItla_ReadReg(p_Itla, 0x55, &usValue, 0) == false)
      return false;

    p_Itla->ulMaxFreq = (usValueH * 1000000) + (usValue * 100);
  }
  break;
  case AppItla_Value_Age:
  {
    if (AppItla_ReadReg(p_Itla, 0x61, &usValue, 0) == false)
      return false;

    p_Itla->usAge = (uint16_t)usValue;
  }
  break;
  case AppItla_Value_FineTune:
  {
    if (AppItla_ReadReg(p_Itla, 0x62, &usValue, 0) == false)
      return false;

    p_Itla->sFineTuneValue = (int16_t)usValue;
  }
  break;
  }

  return true;
}

/// @brief itla模块写值
/// @param Value 值类型
/// @param p_Value 值数值
/// @param p_Itla itla对象
/// @return
bool AppItla_WriteValue(AppItla_Value_E Value, void *p_Value, AppItla_S *p_Itla)
{
  uint16_t usValue;
  uint16_t usValueH;

  if (!p_Itla)
    return false;

  switch (Value)
  {
  default:
    break;
  case AppItla_Value_CurrFreqStep:
  {
    uint16_t usValue = *(uint32_t *)p_Value / 100;

    if (AppItla_WriteReg(p_Itla, 0x34, usValue, 0) == false)
      return false;

    p_Itla->ulCurrFreqStep = (uint32_t)usValue * 100;
  }
  break;
  case AppItla_Value_FirstChannelFreq:
  {
    usValueH = *(uint32_t *)p_Value / 1000000;
    usValue = *(uint32_t *)p_Value % 1000000 / 100;

    if (AppItla_WriteReg(p_Itla, 0x35, usValueH, 0) == false)
      return false;
    if (AppItla_WriteReg(p_Itla, 0x36, usValue, 0) == false)
      return false;

    p_Itla->ulFirstChannelFreq = (usValueH * 1000000) + (usValue * 100);
  }
  break;
  case AppItla_Value_CurrPower:
  {
    usValue = (uint16_t)*(int16_t *)p_Value;

    if (AppItla_WriteReg(p_Itla, 0x31, usValue, 0) == false)
      return false;

    p_Itla->sCurrPower_dBm = (int16_t)usValue;
  }
  break;
  case AppItla_Value_CurrFreq:
  {
    uint32_t ulFreq = *(uint32_t *)p_Value;

    ulFreq = ulFreq - p_Itla->ulFirstChannelFreq;
    ulFreq /= 100;

    usValue = ulFreq + 1;

    if (AppItla_WriteReg(p_Itla, 0x30, usValue, 0) == false)
      return false;
  }
  break;
  case AppItla_Value_FineTune:
  {
    usValue = (uint16_t)*(int16_t *)p_Value;

    if (AppItla_WriteReg(p_Itla, 0x62, usValue, 0) == false)
      return false;

    p_Itla->sFineTuneValue = (int16_t)usValue;
  }
  break;
  }

  return true;
}

/// @brief itla模块输出使能
/// @param p_Itla itla对象
/// @param bNewState 开关状态
/// @return
bool AppItla_Output_Enable(AppItla_S *p_Itla, bool bNewState)
{
  uint16_t usValue = 0;

  if (!p_Itla)
    return false;

  if (bNewState == true)
  {
    usValue = 0x0008;
  }

  if (AppItla_WriteReg(p_Itla, 0x32, usValue, 0) == false)
    return false;

  return true;
}

/// @brief itla模块功率设置
/// @param p_Itla itla对象
/// @param sPower 功率(1000=10.00dBm)
/// @return
bool AppItla_PowerSet(AppItla_S *p_Itla, int16_t sPower)
{
  if ((sPower < p_Itla->sMinPower_dBm) || (sPower > p_Itla->sMinPower_dBm))
    return false;

  return AppItla_WriteValue(AppItla_Value_CurrPower, &sPower, p_Itla);
}

/// @brief itla模块频率设置
/// @param p_Itla itla对象
/// @param ulFreq 频率(191300000 = 191.300GHz)
/// @return
bool AppItla_FreqSet(AppItla_S *p_Itla, uint32_t ulFreq)
{
  if ((ulFreq < p_Itla->ulMinFreq) || (ulFreq > p_Itla->ulMaxFreq))
    return false;

  return AppItla_WriteValue(AppItla_Value_CurrFreq, &ulFreq, p_Itla);
}

/// @brief itla频率微调
/// @param p_Itla itla对象
/// @param sFineTune 频率微调(MHz)
/// @return
bool AppItla_FineTuneSet(AppItla_S *p_Itla, int16_t sFineTune)
{
  return AppItla_WriteValue(AppItla_Value_FineTune, &sFineTune, p_Itla);
}

/// @brief itla模块读状态
/// @param p_Itla itla对象
/// @param p_usStatus 模块状态
/// @return
bool AppItla_ReadStatus(AppItla_S *p_Itla, uint16_t *p_usStatus)
{
  uint16_t usValue;

  if (!p_Itla)
    return false;

  if (AppItla_ReadReg(p_Itla, 0, &usValue, 0) == false)
    return false;

  if (p_usStatus)
  {
    *p_usStatus = usValue;
  }

  return true;
}

/// @brief itla模块查询上一个操作是否完成
/// @param p_Itla itla对象
/// @param usTimeOut 超时
/// @return
bool AppItla_PollDone(AppItla_S *p_Itla, uint16_t usTimeOut)
{
  uint16_t usStatus;

  if (!usTimeOut)
    usTimeOut += 1;

  while (usTimeOut--)
  {
    rt_thread_delay(1);

    if (AppItla_ReadStatus(p_Itla, &usStatus) == false)
      return false;

    if (usStatus & 0x0100)
    {
    }
    else
    {
      return true;
    }
  }

  return false;
}

/// @brief itla模块检查是否存在
/// @param p_Itla itla对象
/// @return
bool AppItla_CheckExist(AppItla_S *p_Itla)
{
  return AppItla_ReadStatus(p_Itla, 0);
}

/// @brief itla模块初始化
/// @param p_Itla itla对象
/// @return
bool AppItla_Init(AppItla_S *p_Itla)
{
  if (!p_Itla)
    return false;

  {
    memset(p_Itla, 0, sizeof(AppItla_S));

    if (AppItla_CheckExist(p_Itla) == false)
      return false;

    if (AppItla_Output_Enable(p_Itla, false) == false)
      return false;
  }

  {
    if (AppItla_ReadString(AppItla_String_Manufacturet, p_Itla) == false)
      return false;
    if (AppItla_ReadString(AppItla_String_Model, p_Itla) == false)
      return false;
    if (AppItla_ReadString(AppItla_String_SN, p_Itla) == false)
      return false;
    if (AppItla_ReadString(AppItla_String_ProductDate, p_Itla) == false)
      return false;
    if (AppItla_ReadString(AppItla_String_Version, p_Itla) == false)
      return false;

    if (AppItla_ReadValue(AppItla_Value_Temp, p_Itla) == false)
      return false;
    if (AppItla_ReadValue(AppItla_Value_CurrFreqStep, p_Itla) == false)
      return false;
    if (AppItla_ReadValue(AppItla_Value_MinFreqStep, p_Itla) == false)
      return false;
    if (AppItla_ReadValue(AppItla_Value_FirstChannelFreq, p_Itla) == false)
      return false;
    if (AppItla_ReadValue(AppItla_Value_CurrPower, p_Itla) == false)
      return false;
    if (AppItla_ReadValue(AppItla_Value_CurrFreq, p_Itla) == false)
      return false;
    if (AppItla_ReadValue(AppItla_Value_PowerRange, p_Itla) == false)
      return false;
    if (AppItla_ReadValue(AppItla_Value_FreqRange, p_Itla) == false)
      return false;
    if (AppItla_ReadValue(AppItla_Value_Age, p_Itla) == false)
      return false;
    if (AppItla_ReadValue(AppItla_Value_FineTune, p_Itla) == false)
      return false;
  }

  {
    if (AppItla_WriteValue(AppItla_Value_FirstChannelFreq, &p_Itla->ulMinFreq, p_Itla) == false)
      return false;
  }

  p_Itla->bRdy = true;

  return true;
}

bool AppItla_RequestPut(AppItla_S *p_Itla, AppItla_Request_E Request, void *p_Value)
{
  if (!p_Itla)
    return false;
  if (!p_Value)
    return false;
  if (p_Itla->bSwitchOnGoing == true)
    return false;

  switch (Request)
  {
  default:
    return false;
  case AppItla_Request_PowerSet:
  {
    int16_t sPower = *(int16_t *)p_Value;

    if ((sPower < p_Itla->sMinPower_dBm) || (sPower > p_Itla->sMaxPower_dBm))
      return false;
    if (p_Itla->sTargetPower_dBm == sPower)
      return true;

    p_Itla->sTargetPower_dBm = sPower;
  }
  break;
  case AppItla_Request_FreqSet:
  {
    uint32_t ulFreq = *(uint32_t *)p_Value;

    if ((ulFreq < p_Itla->ulMinFreq) || (ulFreq > p_Itla->ulMaxFreq))
      return false;
    if (p_Itla->ulTargetFreq == ulFreq)
      return true;

    p_Itla->ulTargetFreq = ulFreq;
  }
  break;
  }

  p_Itla->bSwitchSuccess = false;
  p_Itla->bSwitchOnGoing = true;

  p_Itla->ulSwitchCost = rt_tick_get();

  AppItla_Output_Enable(p_Itla, false);

  if (p_Itla->sTargetPower_dBm != p_Itla->sCurrPower_dBm)
  {
    AppItla_PowerSet(p_Itla, p_Itla->sTargetPower_dBm);
  }

  if (p_Itla->ulTargetFreq != p_Itla->ulCurrFreq)
  {
    AppItla_FreqSet(p_Itla, p_Itla->ulTargetFreq);
  }

  AppItla_Output_Enable(p_Itla, true);

  return true;
}

void AppItla_Proc(AppItla_S *p_Itla)
{
  uint16_t usStatus;

  if (p_Itla->bRdy == false)
    return;
  if (p_Itla->bSwitchOnGoing == false)
    return;

  {
    AppItla_ReadStatus(p_Itla, &usStatus);

    if (usStatus & 0x0100)
    {
      // Busy
    }
    else
    {
      p_Itla->bSwitchOnGoing = false;

      // AppItla_ReadValue(AppItla_Value_CurrFreq, p_Itla);
      // AppItla_ReadValue(AppItla_Value_CurrPower, p_Itla);

      // AppDwin_Control.ulFreq = p_Itla->ulCurrFreq;
      // AppDwin_Control.dWaveLen = CalcWaveLenFromFreqMHz(AppDwin_Control.ulFreq);
      // AppDwin_Write4Bytes(AppDwin_VP_NW_Main_WaveLen, (uint32_t)(AppDwin_Control.dWaveLen * 10000));
      // AppDwin_Write4Bytes(AppDwin_VP_NW_Main_Freq, AppDwin_Control.ulFreq / 100);

      // AppDwin_Control.dPower_dBm = (double)AppItla_C.sCurrPower_dBm / 100;
      // AppDwin_Control.dPower_mW = dBmToMW(AppDwin_Control.dPower_dBm);
      // AppDwin_Write4Bytes(AppDwin_VP_NW_Main_Power_dBm, (uint32_t)(AppDwin_Control.dPower_dBm * 100 + 0.5));
      // AppDwin_Write4Bytes(AppDwin_VP_NW_Main_Power_mW, (uint32_t)(AppDwin_Control.dPower_mW * 100 + 0.5));

      p_Itla->bSwitchSuccess = true;

      p_Itla->ulSwitchCost = rt_tick_get() - p_Itla->ulSwitchCost;
    }
  }
}
