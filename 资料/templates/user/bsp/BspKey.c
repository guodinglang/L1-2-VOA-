#include "BspConfig.h"

BspKey_Mgr_S BspKey_Mgr;

const uint8_t ucaBspKeyName[BSPKEY_NUM][16] =
    {
        "Btn_Func",
};

const uint8_t ucaBspKeyValue[BSPKEY_VALUE_NUM][16] =
    {
        "Release",
        "Press",
        "Click",
        "LPStart",
        "LPBurst",
};

static BspKeyPortSta_E BspKey_Scan(BspKey_E Name)
{
  BspKeyPortSta_E BspKeyPortSta = BspKeyPortSta_Init;

  { // 独立按键
    switch (Name)
    {
    default:
      break;
    }
  }

  return BspKeyPortSta;
}

bool BspKey_GetKey(uint16_t *p_BspKeyValue)
{
  if (!p_BspKeyValue)
    return false;
  if (!BspKey_Mgr.ucCount)
    return false;

  *p_BspKeyValue = BspKey_Mgr.usaValueBuff[BspKey_Mgr.ucRead];

  if (++BspKey_Mgr.ucRead >= BSPKEY_FIFO_NUM)
  {
    BspKey_Mgr.ucRead = 0;
  }

  BspKey_Mgr.ucCount--;

  return true;
}

bool BspKey_PutKey(uint16_t usKeyValue)
{
  if (BspKey_Mgr.ucCount >= BSPKEY_FIFO_NUM)
    return false;

  BspKey_Mgr.usaValueBuff[BspKey_Mgr.ucWrite] = usKeyValue;

  if (++BspKey_Mgr.ucWrite >= BSPKEY_FIFO_NUM)
  {
    BspKey_Mgr.ucWrite = 0;
  }

  BspKey_Mgr.ucCount++;

  return true;
}

void BspKey_ClrKey(void)
{
  BspKey_Mgr.ucRead = 0;
  BspKey_Mgr.ucWrite = 0;
  BspKey_Mgr.ucCount = 0;
}

bool BspKey_HasKey(void)
{
  if (BspKey_Mgr.ucCount)
  {
    return true;
  }

  return false;
}

void BspKey_Proc(void)
{
  uint8_t i;
  BspKeyPortSta_E KeyPortStaNow;
  BspKeyValue_U BspKeyValue;

  for (i = 0; i < BSPKEY_NUM; i++)
  {
    if (BspKey_Mgr.Config[i].Valid == false)
    {
      continue; // 按键配置无效
    }

    KeyPortStaNow = BspKey_Scan((BspKey_E)i);

    if (KeyPortStaNow == BspKeyPortSta_Init)
    {
      continue; // 按键扫描无效
    }

    { // 消抖
      BspKey_Mgr.Config[i].PortStaActive = false;

      if (KeyPortStaNow == (BspKey_Mgr.Config[i].ActiveLevel + 1))
      {
        BspKey_Mgr.Config[i].PortStaActive = true;
      }

      if (KeyPortStaNow != BspKey_Mgr.Config[i].PortStaLast)
      {
        BspKey_Mgr.ucaConfirmDelayCnt[i] = 0;

        BspKey_Mgr.Config[i].PortStaStable = false;
      }
      else
      {
        if (BspKey_Mgr.ucaConfirmDelayCnt[i] < BspKey_Mgr.ucaConfirmDelay[i])
        {
          if (++BspKey_Mgr.ucaConfirmDelayCnt[i] >= BspKey_Mgr.ucaConfirmDelay[i])
          {
            BspKey_Mgr.Config[i].PortStaStable = true;
          }
        }
      }

      BspKey_Mgr.Config[i].PortStaLast = KeyPortStaNow;
    }

    { // 分配键值
      if (BspKey_Mgr.Config[i].PortStaStable == true)
      {
        if (BspKey_Mgr.Config[i].PortStaActive == true)
        {
          if (!BspKey_Mgr.usaLongPressTimeCnt[i])
          {
            { // 按压
              BspKeyValue.Name = (BspKey_E)i;
              BspKeyValue.Value = BspKeyValue_Press;
              BspKeyValue.Param = 0;

              BspKey_PutKey(BspKeyValue.usValue);
            }
          }
          if (BspKey_Mgr.usaLongPressTimeCnt[i] < BspKey_Mgr.usaLongPressTime[i])
          {
            if (++BspKey_Mgr.usaLongPressTimeCnt[i] >= BspKey_Mgr.usaLongPressTime[i])
            {
              BspKey_Mgr.usaLongPressTimeCnt[i] -= BspKey_Mgr.usaLongPressBurstTime[i];

              if (BspKey_Mgr.Config[i].LongPressStart == false)
              {
                { // 长按
                  BspKeyValue.Name = (BspKey_E)i;
                  BspKeyValue.Value = BspKeyValue_LongPressStart;
                  BspKeyValue.Param = 0;

                  BspKey_PutKey(BspKeyValue.usValue);
                }
              }
              else
              {
                { // 连发
                  BspKeyValue.Name = (BspKey_E)i;
                  BspKeyValue.Value = BspKeyValue_LongPressBurst;
                  BspKeyValue.Param = 0;

                  BspKey_PutKey(BspKeyValue.usValue);
                }
              }
              BspKey_Mgr.Config[i].LongPressStart = true;

              // 长按触发后取消下一次点按
              BspKey_Mgr.Config[i].IgnoreNextClick = BspKey_Mgr.Config[i].ClrClickAfterLongPress;
            }
          }
        }
        else
        {
          if (BspKey_Mgr.usaLongPressTimeCnt[i])
          {
            { // 释放
              BspKeyValue.Name = (BspKey_E)i;
              BspKeyValue.Value = BspKeyValue_Release;
              BspKeyValue.Param = 0;

              BspKey_PutKey(BspKeyValue.usValue);
            }
          }

          if ((!BspKey_Mgr.Config[i].IgnoreNextClick)                                  // 没有被设置为长按后取消短按
              && (BspKey_Mgr.usaLongPressTimeCnt[i])                                   // 被按下过
              && (BspKey_Mgr.usaLongPressTimeCnt[i] <= BspKey_Mgr.usaMaxBatterGap[i])) // 被按下的时间小于最大连击间隔
          {
            if (BspKey_Mgr.ucaMaxBatterTimes[i] == 1)
            {
              { // 单击
                BspKeyValue.Name = (BspKey_E)i;
                BspKeyValue.Value = BspKeyValue_Click;
                BspKeyValue.Param = 1;

                BspKey_PutKey(BspKeyValue.usValue);
              }
            }
            else
            {
              if (BspKey_Mgr.ucaBatterTimesCnt[i] < BspKey_Mgr.ucaMaxBatterTimes[i])
              {
                BspKey_Mgr.ucaBatterTimesCnt[i]++;
              }
              BspKey_Mgr.usaBatterGapCnt[i] = BspKey_Mgr.usaMaxBatterGap[i];
            }
          }

          if (BspKey_Mgr.usaBatterGapCnt[i])
          {
            BspKey_Mgr.usaBatterGapCnt[i]--;

            if (!BspKey_Mgr.usaBatterGapCnt[i])
            {
              { // 连击
                BspKeyValue.Name = (BspKey_E)i;
                BspKeyValue.Value = BspKeyValue_Click;
                BspKeyValue.Param = BspKey_Mgr.ucaBatterTimesCnt[i];

                BspKey_PutKey(BspKeyValue.usValue);
              }

              BspKey_Mgr.ucaBatterTimesCnt[i] = 0;
            }
          }

          BspKey_Mgr.Config[i].LongPressStart = false;
          BspKey_Mgr.Config[i].IgnoreNextClick = false;
          BspKey_Mgr.usaLongPressTimeCnt[i] = 0;
        }
      }
    }
  }
}

bool BspKey_IsActive(uint8_t ucIndex)
{
  if (ucIndex >= BSPKEY_NUM)
    return false;

  return BspKey_Mgr.Config[ucIndex].PortStaActive;
}

bool BspKey_IsStable(uint8_t ucIndex)
{
  if (ucIndex >= BSPKEY_NUM)
    return false;

  return BspKey_Mgr.Config[ucIndex].PortStaStable;
}
// 按键点按配置(激活电平,确认延迟,最大连击次数,最大连击间隔)
bool BspKey_Config_Base(uint8_t ucIndex, BspKeyActiveLevel_E ActiveLevel, uint8_t ucConfirmDelay, uint8_t ucMaxBatterTimes, uint16_t usMaxBatterGap)
{
  if (ucIndex >= BSPKEY_NUM)
    return false;
  if (!ucMaxBatterTimes)
    return false;
  if (!usMaxBatterGap)
    return false;

  BspKey_Mgr.Config[ucIndex].Valid = false;

  BspKey_Mgr.Config[ucIndex].ActiveLevel = ActiveLevel;
  BspKey_Mgr.ucaConfirmDelay[ucIndex] = ucConfirmDelay;
  BspKey_Mgr.ucaConfirmDelayCnt[ucIndex] = 0;
  BspKey_Mgr.ucaMaxBatterTimes[ucIndex] = ucMaxBatterTimes;
  BspKey_Mgr.ucaBatterTimesCnt[ucIndex] = 0;
  BspKey_Mgr.usaMaxBatterGap[ucIndex] = usMaxBatterGap;
  BspKey_Mgr.usaBatterGapCnt[ucIndex] = 0;

  BspKey_Mgr.Config[ucIndex].Valid = true;

  return true;
}
// 按键长按配置(长按触发时间,连发间隔时间,长按后是否清除单击)
bool BspKey_Config_LongPress(uint8_t ucIndex, uint16_t usLimitTime, uint16_t usBurstTime, bool bClrClickAfterLongPress)
{
  if (ucIndex >= BSPKEY_NUM)
    return false;
  if (!usLimitTime)
    return false;
  if (usBurstTime >= usLimitTime)
    return false;

  BspKey_Mgr.Config[ucIndex].Valid = false;

  BspKey_Mgr.usaLongPressTime[ucIndex] = usLimitTime;
  BspKey_Mgr.usaLongPressTimeCnt[ucIndex] = 0;
  BspKey_Mgr.usaLongPressBurstTime[ucIndex] = usBurstTime;
  BspKey_Mgr.Config[ucIndex].ClrClickAfterLongPress = bClrClickAfterLongPress;

  BspKey_Mgr.Config[ucIndex].Valid = true;

  return true;
}
// 初始化
void BspKey_Init(void)
{
  uint8_t i;

  BspKey_Mgr.ucRead = 0;
  BspKey_Mgr.ucWrite = 0;
  BspKey_Mgr.ucCount = 0;

  for (i = 0; i < BSPKEY_NUM; i++)
  {
    BspKey_Mgr.Config[i].usValue = 0;
    BspKey_Config_Base(i, BspKeyActiveLevel_Low, 10, 1, 300); // 低电平有效,(10*2)ms消抖,最大连击次数1,最大连击间隔(300*2)ms
    BspKey_Config_LongPress(i, 500, 100, true);               //(500*2)ms长按触发,(100*2)ms连发触发,长按后忽略下一次点按
  }
}

void BspKey_Reset(BspKey_E Name)
{
  if (Name >= BSPKEY_NUM)
    return;

  BspKey_Mgr.Config[Name].PortStaStable = false;
  BspKey_Mgr.Config[Name].LongPressStart = false;
  BspKey_Mgr.Config[Name].PortStaLast = BspKeyPortSta_Init;

  BspKey_Mgr.ucaConfirmDelayCnt[Name] = 0;
  BspKey_Mgr.ucaBatterTimesCnt[Name] = 0;
  BspKey_Mgr.usaBatterGapCnt[Name] = 0;
  BspKey_Mgr.usaLongPressTimeCnt[Name] = 0;
}
