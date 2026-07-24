#ifndef __MUTICHANNELOPTICALPOWERMETER_H__
#define __MUTICHANNELOPTICALPOWERMETER_H__

#define OPM_PORT Port_DUT
#define OPM_pPORT pDUT

#define OPM_CHANNEL_NUM 2

#define OPM_UNIT_NUM 5
typedef enum
{
    OPM_Unit_dBm = 0,
    OPM_Unit_dB,
    OPM_Unit_W,
    OPM_Unit_mW,
    OPM_Unit_uW,
} OPM_Unit_E;

typedef enum
{
    OPM_Param_Power = 0,
    OPM_Param_WavLen,
    OPM_Param_Unit,
    OPM_Param_Ref,
    OPM_Param_PN,
    OPM_Param_SN,
    OPM_Param_IDN,
    OPM_Param_Unknow,
} OPM_Param_E;

typedef struct
{
    bool bReady;
    int32_t laPowerValue[OPM_CHANNEL_NUM];
    uint32_t ulaWavLen[OPM_CHANNEL_NUM];
    OPM_Unit_E aUnit[OPM_CHANNEL_NUM];
    int32_t laRefValue[OPM_CHANNEL_NUM];
    uint8_t ucaPN[32];
    uint8_t ucaSN[32];
    uint8_t ucaIDN[32];
} OpticalPowerMeter_S;

bool OpticalPowerMeter_Init(void);
bool OpticalPowerMeter_Param_Read(uint8_t ucChannel, OPM_Param_E Param, void *p_aParamList);
bool OpticalPowerMeter_String_Read(OPM_Param_E Param, char *p_caString);
bool OpticalPowerMeter_Param_Write(uint8_t ucChannel, OPM_Param_E Param, void *p_Param);
bool OpticalPowerMeter_PowerValue_Update(void);

#endif
