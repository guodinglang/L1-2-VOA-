#include "includes.h"
#include "SerialPort.h"

/*
当前驱动参考文档:两通道光功率计模块 规格书.doc 2026-03-04

修改OPM_CHANNEL_NUM可以兼容更多通道的功率计

初始化阶段调用OpticalPowerMeter_Init获取模块参数(阻塞)
周期调用OpticalPowerMeter_PowerValue_Update刷新光功率值(阻塞)
调用OpticalPowerMeter_Param_Read读取数据(读缓存)
调用OpticalPowerMeter_String_Read读取数据(读缓存)
调用OpticalPowerMeter_Param_Write写参数(阻塞)

不要在文件外直接读写OpticalPowerMeter
*/

const char *p_caOPMUnitString[OPM_UNIT_NUM] =
    {
        "dBm",
        "dB",
        "W",
        "mW",
        "uW",
};

OpticalPowerMeter_S OpticalPowerMeter;

/***************************************************************************
;** 函数名称:  bool OpticalPowerMeter_Init(void)
;** 功能描述:  初始化光功率计
;** 输入参数:
;** 返 回 值:  true 初始化成功
;** 全局变量:
;** 调用模块:
;** 作　  者:  huangjian
;** 日　  期:  2026-6-25
;** 修改原因：
;** 说    明:
;***************************************************************************/
bool OpticalPowerMeter_Init(void)
{
    bool bSuccess;
    OPM_Param_E Param;

    memset(&OpticalPowerMeter, 0, sizeof(OpticalPowerMeter_S));

    for (uint8_t i = 0; i <= OPM_Param_Ref; i++)
    {
        Param = (OPM_Param_E)i;

        for (uint8_t j = 0; j < OPM_CHANNEL_NUM; j++)
        {
            bSuccess = false;

            PortSelect_ClrRecvFifo(OPM_PORT);
            switch (Param)
            {
            default:
                break;
            case OPM_Param_Power:
                sprintfx("PD %u ?\r\n", (j + 1));
                break;
            case OPM_Param_WavLen:
                sprintfx("PD %u WL ?\r\n", (j + 1));
                break;
            case OPM_Param_Unit:
                sprintfx("PD %u UNIT ?\r\n", (j + 1));
                break;
            case OPM_Param_Ref:
                sprintfx("PD %u REF ?\r\n", (j + 1));
                break;
            }
            PortSelect(Port_Release);

            if (PortWait(OPM_PORT, 500, 20) == true)
            {
                if (strstr((char *)OPM_pPORT->rxFIFO, "fail") != 0)
                {
                }
                else if (strstr((char *)OPM_pPORT->rxFIFO, "PD") != 0)
                {
                    switch (Param)
                    {
                    default:
                        break;
                    case OPM_Param_Power:
                    {
                        float fPowerValue;
                        sscanf((char *)OPM_pPORT->rxFIFO, "%*s %f", &fPowerValue);
                        OpticalPowerMeter.laPowerValue[j] = fPowerValue * 1000;
                    }
                    break;
                    case OPM_Param_WavLen:
                    {
                        float fWavLen;
                        sscanf((char *)OPM_pPORT->rxFIFO, "%*s %f", &fWavLen);
                        OpticalPowerMeter.ulaWavLen[j] = fWavLen * 1000;
                    }
                    break;
                    case OPM_Param_Unit:
                    {
                        uint8_t k;

                        for (k = 0; k < OPM_UNIT_NUM; k++)
                        {
                            if (strstr((const char *)OPM_pPORT->rxFIFO, p_caOPMUnitString[k]))
                            {
                                OpticalPowerMeter.aUnit[j] = (OPM_Unit_E)k;
                                break;
                            }
                        }

                        if (k == OPM_UNIT_NUM)
                            return false;
                    }
                    break;
                    case OPM_Param_Ref:
                    {
                        float fRefValue;
                        sscanf((char *)OPM_pPORT->rxFIFO, "%*s %f", &fRefValue);
                        OpticalPowerMeter.laRefValue[j] = fRefValue * 1000;
                    }
                    break;
                    }

                    bSuccess = true;
                }
            }

            if (bSuccess == false)
                return false;
        }
    }

    {
        char *p_Idx;
        uint8_t ucCopyLen;
        uint8_t *const p_ucaTarget[] = {
            OpticalPowerMeter.ucaPN,
            OpticalPowerMeter.ucaSN,
            OpticalPowerMeter.ucaIDN,
        };
        const uint16_t usTargetSize[] = {
            sizeof(OpticalPowerMeter.ucaPN),
            sizeof(OpticalPowerMeter.ucaSN),
            sizeof(OpticalPowerMeter.ucaIDN),
        };
        const char *p_caPrefix[] = {
            "PN:",
            "SN:",
            "IDN:",
        };

        for (uint8_t i = OPM_Param_PN; i <= OPM_Param_IDN; i++)
        {
            bSuccess = false;
            Param = (OPM_Param_E)i;

            PortSelect_ClrRecvFifo(OPM_PORT);
            switch (Param)
            {
            default:
                break;
            case OPM_Param_PN:
                sprintfx("PN ?\r\n");
                break;
            case OPM_Param_SN:
                sprintfx("SN ?\r\n");
                break;
            case OPM_Param_IDN:
                sprintfx("IDN ?\r\n");
                break;
            }
            PortSelect(Port_Release);

            if (PortWait(OPM_PORT, 500, 20) == true)
            {
                if (strstr((char *)OPM_pPORT->rxFIFO, "fail") != 0)
                {
                }
                else if (strstr((char *)OPM_pPORT->rxFIFO, ":") != 0)
                {
                    switch (Param)
                    {
                    default:
                        break;
                    case OPM_Param_PN:
                    case OPM_Param_SN:
                    case OPM_Param_IDN:
                    {
                        p_Idx = strstr((char *)OPM_pPORT->rxFIFO, p_caPrefix[Param - OPM_Param_PN]);
                        if (p_Idx)
                        {
                            ucCopyLen = strlen((const char *)p_Idx);
                            if (ucCopyLen >= usTargetSize[Param - OPM_Param_PN] - 1)
                            {
                                ucCopyLen = usTargetSize[Param - OPM_Param_PN] - 1;
                            }

                            memcpy(p_ucaTarget[Param - OPM_Param_PN], (uint8_t *)((uint32_t)p_Idx + strlen(p_caPrefix[Param - OPM_Param_PN])), ucCopyLen);
                        }
                    }
                    break;
                    }

                    bSuccess = true;
                }
            }

            if (bSuccess == false)
                return false;
        }
    }

    OpticalPowerMeter.bReady = true;

    return true;
}

/***************************************************************************
;** 函数名称:  bool OpticalPowerMeter_Param_Read(uint8_t ucChannel, OPM_Param_E Param, void *p_aParamList)
;** 功能描述:  读取各通道各类型参数值
;** 输入参数:  ucChannel 通道序号(0,1读指定通道 2读所有通道)
;** 输入参数:  Param 参数类型
;** 输出参数:  p_aParamList 参数列表
;** 返 回 值:  true 读取成功
;** 全局变量:
;** 调用模块:
;** 作　  者:  huangjian
;** 日　  期:  2026-6-25
;** 修改原因：
;** 说    明:
;***************************************************************************/
bool OpticalPowerMeter_Param_Read(uint8_t ucChannel, OPM_Param_E Param, void *p_aParamList)
{
    if (ucChannel > OPM_CHANNEL_NUM)
        return false;
    if (Param >= OPM_Param_Unknow)
        return false;

    if (OpticalPowerMeter.bReady == false)
        return false;

    if (ucChannel == OPM_CHANNEL_NUM)
    {
        for (uint8_t i = 0; i < OPM_CHANNEL_NUM; i++)
        {
            switch (Param)
            {
            default:
                return false;
            case OPM_Param_Power:
            {
                int32_t *p_lTemp = (int32_t *)((uint32_t)p_aParamList + (i * sizeof(int32_t)));

                if (!p_lTemp)
                    return false;

                *(int32_t *)p_lTemp = OpticalPowerMeter.laPowerValue[i];
            }
            break;
            case OPM_Param_WavLen:
            {
                uint32_t *p_lTemp = (uint32_t *)((uint32_t)p_aParamList + (i * sizeof(uint32_t)));

                if (!p_lTemp)
                    return false;

                *(uint32_t *)p_lTemp = OpticalPowerMeter.ulaWavLen[i];
            }
            break;
            case OPM_Param_Unit:
            {
                OPM_Unit_E *p_lTemp = (OPM_Unit_E *)((uint32_t)p_aParamList + (i * sizeof(OPM_Unit_E)));

                if (!p_lTemp)
                    return false;

                *(OPM_Unit_E *)p_lTemp = OpticalPowerMeter.aUnit[i];
            }
            break;
            case OPM_Param_Ref:
            {
                int32_t *p_lTemp = (int32_t *)((uint32_t)p_aParamList + (i * sizeof(int32_t)));

                if (!p_lTemp)
                    return false;

                *(int32_t *)p_lTemp = OpticalPowerMeter.laRefValue[i];
            }
            break;
            }
        }
    }
    else if (p_aParamList)
    {
        switch (Param)
        {
        default:
            return false;
        case OPM_Param_Power:
            *(int32_t *)p_aParamList = OpticalPowerMeter.laPowerValue[ucChannel];
            break;
        case OPM_Param_WavLen:
            *(uint32_t *)p_aParamList = OpticalPowerMeter.ulaWavLen[ucChannel];
            break;
        case OPM_Param_Unit:
            *(OPM_Unit_E *)p_aParamList = OpticalPowerMeter.aUnit[ucChannel];
            break;
        case OPM_Param_Ref:
            *(int32_t *)p_aParamList = OpticalPowerMeter.laRefValue[ucChannel];
            break;
        }
    }

    return true;
}

/***************************************************************************
;** 函数名称:  bool OpticalPowerMeter_String_Read(OPM_Param_E Param, char *p_caString)
;** 功能描述:  读取字符串信息
;** 输入参数:  Param 参数类型
;** 输入参数:  p_caString 接收缓冲
;** 返 回 值:  true 读取成功
;** 全局变量:
;** 调用模块:
;** 作　  者:  huangjian
;** 日　  期:  2026-6-25
;** 修改原因：
;** 说    明:
;***************************************************************************/
bool OpticalPowerMeter_String_Read(OPM_Param_E Param, char *p_caString)
{
    if (Param >= OPM_Param_Unknow)
        return false;
    if (!p_caString)
        return false;
    if (OpticalPowerMeter.bReady == false)
        return false;

    switch (Param)
    {
    default:
        return false;
    case OPM_Param_PN:
        strcpy(p_caString, (const char *)OpticalPowerMeter.ucaPN);
        break;
    case OPM_Param_SN:
        strcpy(p_caString, (const char *)OpticalPowerMeter.ucaSN);
        break;
    case OPM_Param_IDN:
        strcpy(p_caString, (const char *)OpticalPowerMeter.ucaIDN);
        break;
    }

    return true;
}

/***************************************************************************
;** 函数名称:  bool OpticalPowerMeter_Param_Write(uint8_t ucChannel, OPM_Param_E Param, void *p_Param)
;** 功能描述:  写参数
;** 输入参数:  ucChannel 通道序号
;** 输入参数:  Param 参数类型
;** 输入参数:  p_Param 参数值
;** 返 回 值:  true 读取成功
;** 全局变量:
;** 调用模块:
;** 作　  者:  huangjian
;** 日　  期:  2026-6-25
;** 修改原因：
;** 说    明:
;***************************************************************************/
bool OpticalPowerMeter_Param_Write(uint8_t ucChannel, OPM_Param_E Param, void *p_Param)
{
    bool bSuccess = false;

    if (ucChannel >= OPM_CHANNEL_NUM)
        return false;
    if (Param >= OPM_Param_Unknow)
        return false;

    if (OpticalPowerMeter.bReady == false)
        return false;

    PortSelect_ClrRecvFifo(OPM_PORT);
    switch (Param)
    {
    default:
        return false;
    case OPM_Param_WavLen:
    {
        uint32_t ulWavLen = *(uint32_t *)p_Param;
        sprintfx("PD %u WL %f\r\n", ucChannel, (float)ulWavLen / 1000);
    }
    break;
    case OPM_Param_Unit:
    {
        OPM_Unit_E Unit = *(OPM_Unit_E *)p_Param;
        sprintfx("PD %u UNIT %s\r\n", ucChannel, p_caOPMUnitString[Unit]);
    }
    break;
    case OPM_Param_Ref:
    {
        sprintfx("PD %u REF\r\n", ucChannel);
    }
    break;
    }
    PortSelect(Port_Release);

    if (PortWait(OPM_PORT, 500, 20) == true)
    {
        if ((strstr((char *)OPM_pPORT->rxFIFO, "ok") != 0) || (strstr((char *)OPM_pPORT->rxFIFO, "OK") != 0))
        {
            switch (Param)
            {
            default:
                return false;
            case OPM_Param_WavLen:
            {
                OpticalPowerMeter.ulaWavLen[ucChannel] = *(uint32_t *)p_Param;
            }
            break;
            case OPM_Param_Unit:
            {
                OpticalPowerMeter.aUnit[ucChannel] = *(OPM_Unit_E *)p_Param;
            }
            break;
            case OPM_Param_Ref:
                break;
            }

            bSuccess = true;
        }
    }

    return bSuccess;
}

/***************************************************************************
;** 函数名称:  bool OpticalPowerMeter_PowerValue_Update(void)
;** 功能描述:  触发更新光功率值
;** 输入参数:
;** 返 回 值:  true 读取成功
;** 全局变量:
;** 调用模块:
;** 作　  者:  huangjian
;** 日　  期:  2026-6-25
;** 修改原因：
;** 说    明:
;***************************************************************************/
bool OpticalPowerMeter_PowerValue_Update(void)
{
    bool bSuccess = false;

    PortSelect_ClrRecvFifo(OPM_PORT);
    sprintfx("PD ALL ?\r\n");
    PortSelect(Port_Release);

    if (PortWait(OPM_PORT, 500, 20) == true)
    {
        if (strstr((char *)OPM_pPORT->rxFIFO, "fail") != 0)
        {
        }
        else if (strstr((char *)OPM_pPORT->rxFIFO, "PD") != 0)
        {
            char cChar;
            uint8_t ucRead = 0;
            bool bConvert = false;
            bool bContinue = true;
            uint8_t ucChannel = 0;

            while (bContinue)
            {
                cChar = OPM_pPORT->rxFIFO[ucRead];

                switch (cChar)
                {
                default:
                    if (bConvert == true)
                    {
                        OpticalPowerMeter.laPowerValue[ucChannel] = (int32_t)(atof((const char *)&OPM_pPORT->rxFIFO[ucRead]) * 1000);

                        if (++ucChannel >= OPM_CHANNEL_NUM)
                            bContinue = false;

                        bConvert = false;
                    }
                    break;
                case '\0':
                case '\r':
                case '\n':
                    bContinue = false;
                    break;
                case ' ':
                {
                    bConvert = true;
                }
                break;
                }

                if (++ucRead >= sizeof(OPM_pPORT->rxFIFO))
                    break;
            }

            bSuccess = true;
        }
    }

    return bSuccess;
}
