#ifndef __APPPORT_H__
#define __APPPORT_H__

#include "stdint.h"
#include "stdbool.h"

#define PORT_NUM 9

typedef enum
{
    Port_UART = 0,
    Port_DUT,
    Port_USB,
    Port_DUT2,
    Port_MultiPort1,
    Port_MultiPort2,
    Port_MultiPort3,
    Port_MultiPort4,
    Port_CAN1,
    Port_Release,
} Port_E;

#define CHANNEL_NUM 62

typedef struct
{
    float fWaveLength_ITU;
    float fWaveLength;
    float fXp;
    float fXn;
} ChannelParamList_S;

extern ChannelParamList_S ChannelParam[CHANNEL_NUM];

// 数据结构
typedef struct
{
    int max_count;   // 最大点数
    int valid_count; // 有效点数
    int first_valid; // 第一个有效通道
    int last_valid;  // 最后一个有效通道
    int wl_max;
    int wl_min;
} CalibrationInfo_t;

extern CalibrationInfo_t CalibrationInfo;

void PortTickUpdate(void);
uint16_t PortTickGet(void);
void PortTickSet(uint16_t usTick);
void PortTickDelay(uint16_t usDelay);
uint32_t SysTickGet(void);

void PortSelect(Port_E Port);
void PortSelect_ClrRecvFifo(Port_E Port);
bool PortWait(Port_E Port, uint16_t usMax, uint8_t ucIdle);

bool ListVoltage(ChannelParamList_S *p_List, uint8_t ucPointNum);
bool SimulateVoltage(float fXpBegin, float fXpEnd, float fXnBegin, float fXnEnd, ChannelParamList_S *p_List, uint8_t ucPointNum);

void SwitchToExecuteAfter(uint8_t ucDelay, bool bUppercase);
bool SwitchToExecuteCheck(bool *bUppercase);

bool ScanerStart(uint32_t ulStepNum);
void ScanerStop(void);
bool ScanerProgressCheck(uint8_t *p_ucProgress);
bool ScanerOngoingCheck(void);

bool CalibrationStatistics(CalibrationInfo_t *info);

bool InputWavLenCheck(uint32_t ulwl);

bool CenterWavLenOffset_Read(int32_t *p_lOffset);
bool CenterWavLenOffset_Write(int32_t lOffset);

#endif
