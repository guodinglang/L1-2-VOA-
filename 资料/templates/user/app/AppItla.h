#ifndef __APPITLA_H__
#define __APPITLA_H__

typedef enum
{
  AppItla_String_Manufacturet = 0,
  AppItla_String_Model,
  AppItla_String_SN,
  AppItla_String_ProductDate,
  AppItla_String_Version,
  AppItla_String_Unknow,
} AppItla_String_E;

typedef enum
{
  AppItla_Value_Temp = 0,
  AppItla_Value_CurrFreqStep,
  AppItla_Value_MinFreqStep,
  AppItla_Value_FirstChannelFreq,
  AppItla_Value_CurrPower,
  AppItla_Value_CurrFreq,
  AppItla_Value_PowerRange,
  AppItla_Value_FreqRange,
  AppItla_Value_Age,
  AppItla_Value_FineTune,
} AppItla_Value_E;

typedef struct
{
  bool bRdy;
  // void *p_Mutex;

  char caManufacturetString[32]; // 制造商信息
  char caModelString[32];        // 型号信息
  char caSNString[32];           // SN信息
  char caProductDateString[32];  // 生产日期
  char caVersionString[32];      // 版本信息

  int32_t lTemp;           // 温度 单位℃ 值1000 = 10.00℃
  uint32_t ulCurrFreqStep; // 当前频率步进 单位MHz 值1000 = 1000MHz
  uint32_t ulMinFreqStep;  // 模块支持的最小频率步进 单位MHz 值1000 = 1000MHz

  uint32_t ulFirstChannelFreq; // 第一个通道的频率 单位MHz 值1000 = 1000Mhz

  int16_t sCurrPower_dBm; // 当前功率 单位dBm 值1000 = 10.00dBm
  uint32_t ulCurrFreq;    // 当前频率 单位MHz 值1000 = 1000Mhz

  int16_t sMinPower_dBm; // 模块最小功率 单位dBm 值1000 = 10.00dBm
  int16_t sMaxPower_dBm; // 模块最大功率 单位dBm 值1000 = 10.00dBm

  uint32_t ulMinFreq; // 模块最小频率 单位MHz 值1000 = 1000Mhz
  uint32_t ulMaxFreq; // 模块最大频率 单位MHz 值1000 = 1000Mhz

  double dMaxWaveLen; // 模块最大波长 单位nm 换算值
  double dMinWaveLen; // 模块最小波长 单位nm 换算值

  uint16_t usAge;         // 寿命(百分比)
  int16_t sFineTuneValue; // 微调值 单位MHz 值1000 = 1000Mhz

  uint32_t ulSwitchCost; // 切换时间开销(ms)
  bool bSwitchOnGoing;
  bool bSwitchSuccess;
  int16_t sTargetPower_dBm; // 目标功率值
  uint32_t ulTargetFreq;    // 目标频率
} AppItla_S;

extern AppItla_S AppItla_C;
extern AppItla_S AppItla_L;

typedef enum
{
  AppItla_Request_PowerSet = 0,
  AppItla_Request_FreqSet,
} AppItla_Request_E;

bool AppItla_ReadString(AppItla_String_E String, AppItla_S *p_Itla);
bool AppItla_ReadValue(AppItla_Value_E Value, AppItla_S *p_Itla);
bool AppItla_WriteValue(AppItla_Value_E Value, void *p_Value, AppItla_S *p_Itla);
bool AppItla_Output_Enable(AppItla_S *p_Itla, bool bNewState);
bool AppItla_PowerSet(AppItla_S *p_Itla, int16_t sPower);
bool AppItla_FreqSet(AppItla_S *p_Itla, uint32_t ulFreq);
bool AppItla_FineTuneSet(AppItla_S *p_Itla, int16_t sFineTune);
bool AppItla_ReadStatus(AppItla_S *p_Itla, uint16_t *p_usStatus);
bool AppItla_PollDone(AppItla_S *p_Itla, uint16_t usTimeOut);
bool AppItla_CheckExist(AppItla_S *p_Itla);
bool AppItla_Init(AppItla_S *p_Itla);
bool AppItla_RequestPut(AppItla_S *p_Itla, AppItla_Request_E Request, void *p_Value);
void AppItla_Proc(AppItla_S *p_Itla);

#endif /*AppItal.h*/
