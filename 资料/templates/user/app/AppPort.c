#include "includes.h"

static uint8_t ucaMessageTransBuff[128];

bool AppPort_Wdt_IsTrig(void)
{
  if (crm_flag_get(CRM_WDT_RESET_FLAG) != RESET)
  {
    /* reset from wdt */
    crm_flag_clear(CRM_WDT_RESET_FLAG);

    return true;
  }

  /* reset from other mode */
  return false;
}

void AppPort_Wdt_Start(void)
{
#if (WDT_ENABLE == 1)
  /* disable register write protection */
  wdt_register_write_enable(TRUE);

  /* set the wdt divider value */
  wdt_divider_set(WDT_CLK_DIV_128);

  /* set reload value

   timeout = reload_value * (divider / lick_freq )    (s)

   lick_freq    = 40000 Hz
   divider      = 128
   reload_value = 500

   timeout = 500 * (128 / 40000 ) = 1.6s
  */
  wdt_reload_value_set(500 - 1);

  /* reload wdt counter */
  wdt_counter_reload();

  /* enable wdt */
  wdt_enable();
#endif
}

void AppPort_Wdt_Feed(void)
{
#if (WDT_ENABLE == 1)
  /* reload wdt counter */
  wdt_counter_reload();
#endif
}

bool AppPort_AT24C08C_Write_Byte(uint16_t usAddr, uint8_t ucByte)
{
  const uint8_t ucDeviceAddr = 0xA0;
  uint8_t ucPage = usAddr >> 8;
  uint8_t ucWaitCnt = 0;

  if (BspSoftiic_WriteReg(ucDeviceAddr | ((ucPage & 0x03) << 1), (uint8_t)usAddr, &ucByte, 1) == true)
  {
    while (1)
    {
      rt_thread_delay(1);

      if (BspSoftiic_CheckDevice(ucDeviceAddr) == true)
        break;

      if (++ucWaitCnt >= 10)
        return false;
    }

    return true;
  }

  return false;
}

bool AppPort_AT24C08C_Read_Byte(uint16_t usAddr, uint8_t *p_ucByte)
{
  const uint8_t ucDeviceAddr = 0xA0;
  uint8_t ucPage = usAddr >> 8;

  return BspSoftiic_ReadReg(ucDeviceAddr | ((ucPage & 0x03) << 1), (uint8_t)usAddr, p_ucByte, 1);
}

bool AppPort_AT24C08C_Write_MutiByte(uint16_t usAddr, uint8_t *p_ucaBuff, uint16_t usSize)
{
  for (uint16_t i = 0; i < usSize; i++)
  {
    if (AppPort_AT24C08C_Write_Byte(usAddr++, p_ucaBuff[i]) == false)
      return false;
  }

  return true;
}

bool AppPort_AT24C08C_Read_MutiByte(uint16_t usAddr, uint8_t *p_ucaBuff, uint16_t usSize)
{
  for (uint16_t i = 0; i < usSize; i++)
  {
    if (AppPort_AT24C08C_Read_Byte(usAddr++, p_ucaBuff++) == false)
      return false;
  }

  return true;
}

bool AppPort_AT24C08C_Write_Buff(uint16_t usAddr, uint8_t *p_ucaBuff, uint16_t usSize)
{
  const uint8_t ucDeviceAddr = 0xA0;
  const uint8_t ucBlockSize = 16;
  uint8_t ucPage;
  uint8_t ucWaitCnt = 0;
  uint16_t usBlockNum = usSize / ucBlockSize;
  uint8_t ucRemainBytes = usSize % ucBlockSize;
  bool bResult = true;

  for (uint16_t i = 0; i < usBlockNum; i++)
  {
    p_ucaBuff += ucBlockSize;
    usAddr += ucBlockSize;
    ucPage = usAddr >> 8;

    if (BspSoftiic_WriteReg(ucDeviceAddr | ((ucPage & 0x03) << 1), (uint8_t)usAddr, p_ucaBuff, ucBlockSize) == true)
    {
      while (1)
      {
        rt_thread_delay(1);

        if (BspSoftiic_CheckDevice(ucDeviceAddr) == true)
          break;

        if (++ucWaitCnt >= 20)
          return false;
      }
    }
    else
    {
      bResult = false;
      break;
    }
  }

  if (ucRemainBytes)
  {
    ucPage = usAddr >> 8;

    if (BspSoftiic_WriteReg(ucDeviceAddr | ((ucPage & 0x03) << 1), (uint8_t)usAddr, p_ucaBuff, ucRemainBytes) == true)
    {
      while (1)
      {
        rt_thread_delay(1);

        if (BspSoftiic_CheckDevice(ucDeviceAddr) == true)
          break;

        if (++ucWaitCnt >= 20)
          return false;
      }
    }
    else
    {
      bResult = false;
    }
  }

  return bResult;
}

bool AppPort_AT24C08C_Read_Buff(uint16_t usAddr, uint8_t *p_ucaBuff, uint16_t usSize)
{
  const uint8_t ucDeviceAddr = 0xA0;
  uint8_t ucPage = usAddr >> 8;

  return BspSoftiic_ReadReg_Delay(ucDeviceAddr | ((ucPage & 0x03) << 1), (uint8_t)usAddr, p_ucaBuff, usSize, 100);
}

void AppPort_MessageTrans(void)
{
  uint16_t usRecvCnt;

  {
    // static bool bOverlay = false;

    // if (AppCmdLine_Mgr.ucBoardIdx)
    // {
    //   if (bOverlay == false)
    //   {
    //     if (AppDwin_PageOverlay(0x0008) == true)
    //     { // 打开页面叠加
    //       bOverlay = true;
    //     }
    //   }
    // }
    // else
    // {
    //   if (bOverlay == true)
    //   {
    //     if (AppDwin_PageOverlay_Disable() == true)
    //     { // 关闭页面叠加
    //       bOverlay = false;
    //     }
    //   }
    // }
  }

  if (AppCmdLine_Mgr.ucBoardIdx == 1)
  { // DUT响应转发
    if (BspUart_GetRxCount(BspUartCom_DUT))
    {
      usRecvCnt = BspUart_GetBuff(BspUartCom_DUT, ucaMessageTransBuff, sizeof(ucaMessageTransBuff));
      AppCmdLine_Send(ucaMessageTransBuff, usRecvCnt);
    }
  }
  else if (AppCmdLine_Mgr.ucBoardIdx == 2)
  {
    if (BspUart_GetRxCount(BspUartCom_DUT2))
    {
      usRecvCnt = BspUart_GetBuff(BspUartCom_DUT2, ucaMessageTransBuff, sizeof(ucaMessageTransBuff));
      AppCmdLine_Send(ucaMessageTransBuff, usRecvCnt);
    }
  }
  else if (AppCmdLine_Mgr.ucBoardIdx == 3)
  {
    if (BspComPort_GetRxCount(BspComPort_Name2Handle("uart_lcd")))
    {
      usRecvCnt = BspComPort_Read(BspComPort_Name2Handle("uart_lcd"), ucaMessageTransBuff, sizeof(ucaMessageTransBuff));
      AppCmdLine_Send(ucaMessageTransBuff, usRecvCnt);
    }
  }
}

double CalcFreqTHzFromWaveLen(double fWaveLen)
{
  return (299792.458 / fWaveLen);
}

uint32_t CalcFreqMHzFromWaveLen(double fWaveLen)
{
  return (uint32_t)(299792.458 / fWaveLen * 1000000 + 0.5);
}

double CalcWaveLenFromFreqMHz(uint32_t ulFreq)
{
  return (double)299792458000 / ulFreq;
}

// 波长 (nm) 转频率 (THz)
double nmToTHz(double fnm)
{
  return 299792.458 / fnm; // 光速常数 / 波长(nm)
}

// 频率 (THz) 转波长 (nm)
double ThzTonm(double fthz)
{
  return 299792.458 / fthz; // 光速常数 / 频率(THz)
}

double dBmToMW(double fdBm)
{
  return pow(10.0, fdBm / 10.0);
}

double mWToDBm(double fmW)
{
  return 10.0 * log10(fmW);
}
