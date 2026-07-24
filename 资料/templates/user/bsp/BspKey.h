#ifndef __BSPKEY_H__
#define __BSPKEY_H__

#define BSPKEY_FIFO_NUM 4

#define BSPKEY_NUM 1

typedef enum
{
  BspKey_Func = 0,
} BspKey_E;

typedef enum
{
  BspKeyPortSta_Init = 0,
  BspKeyPortSta_Low,
  BspKeyPortSta_High,
} BspKeyPortSta_E; // 按键电平状态

typedef enum
{
  BspKeyActiveLevel_Low = 0, // 低电平为激活状态
  BspKeyActiveLevel_High,    // 高电平为激活状态
} BspKeyActiveLevel_E;

#define BSPKEY_VALUE_NUM 5

typedef enum
{
  BspKeyValue_Release = 0,    // 按键释放
  BspKeyValue_Press,          // 按键按下
  BspKeyValue_Click,          // 按键点击(若干次)
  BspKeyValue_LongPressStart, // 长按触发
  BspKeyValue_LongPressBurst, // 长按连发
} BspKeyValue_E;

typedef union
{
  uint16_t usValue;
  struct
  {
    uint16_t Valid : 1;
    uint16_t PortStaActive : 1;
    uint16_t PortStaStable : 1;
    uint16_t ClrClickAfterLongPress : 1;
    uint16_t IgnoreNextClick : 1;
    uint16_t LongPressStart : 1;
    uint16_t PortStaLast : 2;
    uint16_t ActiveLevel : 1;
    uint16_t Reserve : 7;
  };
} BspKeyConfig_U;

typedef union
{
  uint16_t usValue;
  struct
  {
    uint16_t Name : 5;
    uint16_t Value : 3;
    uint16_t Param : 8;
  };
} BspKeyValue_U;

typedef struct
{
  BspKeyConfig_U Config[BSPKEY_NUM];

  uint8_t ucaConfirmDelay[BSPKEY_NUM];    // 按键电平状态确认延迟
  uint8_t ucaConfirmDelayCnt[BSPKEY_NUM]; // 按键电平状态确认延迟(计时器)

  uint8_t ucaMaxBatterTimes[BSPKEY_NUM]; // 按键最大连击次数
  uint8_t ucaBatterTimesCnt[BSPKEY_NUM]; // 按键连击次数(计数器)
  uint16_t usaMaxBatterGap[BSPKEY_NUM];  // 按键连击间的最大间隔时间
  uint16_t usaBatterGapCnt[BSPKEY_NUM];  // 按键连击间的间隔时间(计时器)

  uint16_t usaLongPressTime[BSPKEY_NUM];      // 按键长按时间
  uint16_t usaLongPressTimeCnt[BSPKEY_NUM];   // 按键长按时间(计时器)
  uint16_t usaLongPressBurstTime[BSPKEY_NUM]; // 按键长按后连发时间

  uint16_t usaValueBuff[BSPKEY_FIFO_NUM];

  uint8_t ucRead;
  uint8_t ucWrite;
  uint8_t ucCount;
} BspKey_Mgr_S;

typedef struct
{
  BspKeyActiveLevel_E ActiveLevel;
  uint8_t ucConfirmDelay;
  uint8_t ucMaxBatterTimes;
  uint16_t usMaxBatterGap;
} BspKey_BaseParam_S;

extern const uint8_t ucaBspKeyName[BSPKEY_NUM][16];
extern const uint8_t ucaBspKeyValue[BSPKEY_VALUE_NUM][16];

typedef struct
{
  bool bValid;
  bool bScanFinish;

  uint8_t ucRowNum;
  uint8_t ucColNum;

  uint8_t ucRowMask;
  uint8_t ucRowState;
  uint32_t ulRowBuff; // 最多32个按键

  uint8_t ucScanIndex;
} BspKey_Matrix_S;

bool BspKey_GetKey(uint16_t *p_BspKeyValue);
bool BspKey_PutKey(uint16_t usKeyValue);
void BspKey_ClrKey(void);
bool BspKey_HasKey(void);
void BspKey_Proc(void);
bool BspKey_IsActive(uint8_t ucIndex);
bool BspKey_IsStable(uint8_t ucIndex);
bool BspKey_Config_Base(uint8_t ucIndex, BspKeyActiveLevel_E ActiveLevel, uint8_t ucConfirmDelay, uint8_t ucMaxBatterTimes, uint16_t usMaxBatterGap);
bool BspKey_Config_LongPress(uint8_t ucIndex, uint16_t usLimitTime, uint16_t usBurstTime, bool bClrClickAfterLongPress);
void BspKey_Init(void);
void BspKey_Reset(BspKey_E Name);

#endif /*BspKey.h*/
