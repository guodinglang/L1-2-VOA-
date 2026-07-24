#include "BspConfig.h"

uint8_t ucaEventPool[config_EVENT_NUM >> 3];

static bool BspEvent_Find(uint8_t EventCode, uint8_t *p_Num, uint8_t *p_Bit)
{
  uint8_t ucNum = 0;

  if (EventCode > config_EVENT_NUM)
    return false;

  while (EventCode > 7)
  {
    EventCode -= 8;
    ucNum++;
  }

  *p_Num = ucNum;
  *p_Bit = EventCode;

  return true;
}

bool BspEvent_Clr(uint8_t EventCode)
{
  uint8_t ucNum;
  uint8_t ucBit;

  if (BspEvent_Find(EventCode, &ucNum, &ucBit) == false)
    return false;

  ucaEventPool[ucNum] &= ~(1 << ucBit);
  return true;
}

bool BspEvent_Set(uint8_t EventCode)
{
  uint8_t ucNum;
  uint8_t ucBit;

  if (BspEvent_Find(EventCode, &ucNum, &ucBit) == false)
    return false;

  ucaEventPool[ucNum] |= (1 << ucBit);
  return true;
}

bool BspEvent_Check(uint8_t EventCode)
{
  uint8_t ucNum;
  uint8_t ucBit;

  if (BspEvent_Find(EventCode, &ucNum, &ucBit) == false)
    return false;

  if (ucaEventPool[ucNum] & (1 << ucBit))
    return true;
  return false;
}

void BspEvent_Init(void)
{
  uint8_t i;
  for (i = 0; i < config_EVENT_NUM; i++)
  {
    BspEvent_Clr(i);
  }
}
