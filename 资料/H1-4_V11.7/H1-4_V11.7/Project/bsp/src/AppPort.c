#include "includes.h"
#include "SerialPort.h"

uint16_t usPortTick = 0;
uint32_t ulSysTick = 0;
ChannelParamList_S ChannelParam[CHANNEL_NUM];
uint8_t ucExecuteDelay = 0;
bool bUppercaseCmd = false;
CalibrationInfo_t CalibrationInfo;
uint32_t ulScaner_StepNum = 0;
uint32_t ulScaner_StepCnt = 0;

void PortTickUpdate(void)
{
    if (usPortTick)
    {
        usPortTick -= 1;
    }

    ulSysTick += 1;
}

uint16_t PortTickGet(void)
{
    return usPortTick;
}

void PortTickSet(uint16_t usTick)
{
    usPortTick = usTick;
}

void PortTickDelay(uint16_t usDelay)
{
    usPortTick = usDelay;
    while (usPortTick)
        ;
}

uint32_t SysTickGet(void)
{
    return ulSysTick;
}

/***************************************************************************
;** 函数名称:  void PortSelect(Port_E Port)
;** 功能描述:  选择串口
;** 输入参数:  Port 串口代号
;** 返 回 值:
;** 全局变量:
;** 调用模块:
;** 作　  者:  huangjian
;** 日　  期:  2026-6-24
;** 修改原因：
;** 说    明:
;***************************************************************************/
void PortSelect(Port_E Port)
{
    uint8_t i;
    rxStructure *p_Port;
    extern rxStructure urStruct[9];

    for (i = 0; i < PORT_NUM; i++)
    {
        p_Port = &urStruct[i];

        if (Port == (Port_E)i)
        {
            p_Port->send = 1;
        }
        else
        {
            p_Port->send = 0;
        }
    }
}

/***************************************************************************
;** 函数名称:  void PortSelect_ClrRecvFifo(Port_E Port)
;** 功能描述:  选择串口(选择前会清空接收缓冲和接收计数器)
;** 输入参数:  Port 串口代号
;** 返 回 值:
;** 全局变量:
;** 调用模块:
;** 作　  者:  huangjian
;** 日　  期:  2026-6-24
;** 修改原因：
;** 说    明:
;***************************************************************************/
void PortSelect_ClrRecvFifo(Port_E Port)
{
    uint8_t i;
    rxStructure *p_Port;
    extern rxStructure urStruct[9];

    for (i = 0; i < PORT_NUM; i++)
    {
        p_Port = &urStruct[i];

        if (Port == (Port_E)i)
        {
            p_Port->send = 1;

            p_Port->len = 0;
            memset(p_Port->rxFIFO, 0, sizeof(p_Port->rxFIFO));
        }
        else
        {
            p_Port->send = 0;
        }
    }
}

/***************************************************************************
;** 函数名称:  bool PortWait(Port_E Port, uint16_t usMax, uint8_t ucIdle)
;** 功能描述:  等待串口回应()
;** 输入参数:  Port 串口代号
;** 输入参数:  usMax 最大等待时间(ms)
;** 输入参数:  ucIdle 串口空闲超过这个时间则认为接收完毕(ms)
;** 返 回 值:  true 在预期的时间内得到了回应
;** 全局变量:
;** 调用模块:
;** 作　  者:  huangjian
;** 日　  期:  2026-6-24
;** 修改原因：
;** 说    明:
;***************************************************************************/
bool PortWait(Port_E Port, uint16_t usMax, uint8_t ucIdle)
{
    uint8_t i;
    uint8_t ucRecvLen;
    uint16_t usTick;
    bool bRecvStart = false;
    rxStructure *p_Port = 0;
    extern rxStructure urStruct[9];

    if (ucIdle < 5)
        ucIdle = 5;

    for (i = 0; i < PORT_NUM; i++)
    {
        if (Port == (Port_E)i)
        {
            p_Port = &urStruct[i];
        }
    }

    if (!p_Port)
        return false;

    {
        ucRecvLen = p_Port->len;

        usTick = usMax;
        PortTickSet(usTick);

        while (PortTickGet())
        {
            if (ucRecvLen != p_Port->len)
            {
                ucRecvLen = p_Port->len;
                usTick = PortTickGet();
                bRecvStart = true;
            }
            else if (bRecvStart == true)
            {
                if ((usTick - PortTickGet()) > ucIdle)
                {
                    break;
                }
            }
        }
    }

    return bRecvStart;
}

/***************************************************************************
;** 函数名称:  bool ListVoltage(ChannelParamList_S *p_List, uint8_t ucPointNum)
;** 功能描述:  列出模块中的定标点电压
;** 输入参数:  p_List 定标点列表
;** 输入参数:  ucPointNum 定标点个数
;** 返 回 值:  true 拉取完毕
;** 全局变量:
;** 调用模块:
;** 作　  者:  huangjian
;** 日　  期:  2026-6-24
;** 修改原因：
;** 说    明:
;***************************************************************************/
bool ListVoltage(ChannelParamList_S *p_List, uint8_t ucPointNum)
{
    uint8_t i;

    if (!p_List)
        return false;
    if (!ucPointNum)
        return false;

    for (i = 0; i < ucPointNum; i++)
    {
        {
            PortSelect_ClrRecvFifo(Port_DUT2);
            sprintfx("lvd r c%02u\r\n", i + 1);
            PortSelect(Port_Release);

            if (PortWait(Port_DUT2, 500, 20) == true)
            {
                if ((strstr((char *)pDUT2->rxFIFO, "\r")) || (strstr((char *)pDUT2->rxFIFO, "\n")))
                {
                    char *p_Idx;

                    p_Idx = strstr((char *)pDUT2->rxFIFO, "X+:");
                    if (p_Idx)
                    {
                        p_Idx += strlen("X+:");
                        p_List[i].fXp = atof((const char *)p_Idx);
                    }

                    p_Idx = strstr((char *)pDUT2->rxFIFO, "X-:");
                    if (p_Idx)
                    {
                        p_Idx += strlen("X-:");
                        p_List[i].fXn = atof((const char *)p_Idx);
                    }

                    p_Idx = strstr((char *)pDUT2->rxFIFO, "W:");
                    if (p_Idx)
                    {
                        p_Idx += strlen("W:");
                        p_List[i].fWaveLength = atof((const char *)p_Idx);
                    }

                    // sscanf((char *)pDUT2->rxFIFO, "%*s %f %*s %f %*s %f", &p_List[i].fXp, &p_List[i].fXn, &p_List[i].fWaveLength);
                }
            }

            PortTickDelay(10);
        }

        {
            PortSelect_ClrRecvFifo(Port_DUT2);
            sprintfx("set c%02u\r\n", i + 1);
            PortSelect(Port_Release);

            if (PortWait(Port_DUT2, 500, 20) == true)
            {
                if (strstr((char *)pDUT2->rxFIFO, "pass"))
                {
                }
            }

            PortTickDelay(10);
        }

        {
            PortSelect_ClrRecvFifo(Port_DUT2);
            sprintfx("read wln\r\n");
            PortSelect(Port_Release);

            if (PortWait(Port_DUT2, 500, 20) == true)
            {
                if ((strstr((char *)pDUT2->rxFIFO, "\r")) || (strstr((char *)pDUT2->rxFIFO, "\n")))
                {
                    char *p_Idx = strstr((char *)pDUT2->rxFIFO, "read wln ");
                    if (p_Idx)
                    {
                        p_Idx += strlen("read wln ");
                        p_List[i].fWaveLength_ITU = atof((const char *)p_Idx);
                    }
                }
            }

            PortTickDelay(10);
        }
    }

    return true;
}

/***************************************************************************
;** 函数名称:  bool SimulateVoltage(float fXpBegin, float fXpEnd, float fXnBegin, float fXnEnd, ChannelParamList_S *p_List, uint8_t ucPointNum)
;** 功能描述:  模拟定标
;** 输入参数:  fXpBegin x+电压起始
;** 输入参数:  fXpEnd x+电压终止
;** 输入参数:  fXnBegin x-电压起始
;** 输入参数:  fXnEnd x-电压终止
;** 输入参数:  p_List 定标点列表
;** 输入参数:  ucPointNum 定标点格式
;** 返 回 值:  true 填充完毕
;** 全局变量:
;** 调用模块:
;** 作　  者:  huangjian
;** 日　  期:  2026-6-24
;** 修改原因：
;** 说    明:
;***************************************************************************/
bool SimulateVoltage(float fXpBegin, float fXpEnd, float fXnBegin, float fXnEnd, ChannelParamList_S *p_List, uint8_t ucPointNum)
{
    uint8_t i;
    float fXpGap;
    float fXnGap;

    uint8_t ucPassNum = 0;

    if (!p_List)
        return false;
    if (!ucPointNum)
        return false;

    fXpGap = (fXpEnd - fXpBegin) / ucPointNum;
    fXnGap = (fXnEnd - fXnBegin) / ucPointNum;

    for (i = 0; i < ucPointNum; i++)
    {
        PortSelect_ClrRecvFifo(Port_DUT2);
        sprintfx("lvd w c%02u %.2f %.2f %.2f\r\n", i + 1, p_List[i].fWaveLength_ITU, fXpBegin + (fXpGap * i), fXnBegin + (fXnGap * i));
        PortSelect(Port_Release);

        if (PortWait(Port_DUT2, 500, 20) == true)
        {
            if (strstr((char *)pDUT2->rxFIFO, "pass"))
            {
                ucPassNum += 1;
            }
        }

        PortTickDelay(10);
    }

    if (ucPassNum == ucPointNum)
    {
        ListVoltage(p_List, ucPointNum);

        { // 保存电压
            PortSelect_ClrRecvFifo(Port_DUT2);
            sprintfx("srw w ls\r\n");
            PortSelect(Port_Release);

            if (PortWait(Port_DUT2, 500, 20) == true)
            {
                if (strstr((char *)pDUT2->rxFIFO, "pass"))
                {
                    return true;
                }
            }
        }

        return false;
    }

    return false;
}

void SwitchToExecuteAfter(uint8_t ucDelay, bool bUppercase)
{
    ucExecuteDelay = ucDelay;
    bUppercaseCmd = bUppercase;
}

bool SwitchToExecuteCheck(bool *bUppercase)
{
    if (ucExecuteDelay)
    {
        if (--ucExecuteDelay == 0)
        {
            if (bUppercase)
            {
                *bUppercase = bUppercaseCmd;
            }

            return true;
        }
    }

    return false;
}

/*
当前扫描流程概要(当前进度条通过扫描次数模拟)

命令行发送扫描命令->自动跳转到"峰值搜索"页面并停留600ms展示参数,然后自动跳转到"执行"页面
界面操作->进入"峰值搜索"页面,输入参数,点击执行按钮跳转到"执行"页面

DisplayUARTHMI函数内收到"执行"页面ID后,构造scan命令发送给模块,并等待回应

如果回应pass则替换状态为"扫描中",按钮变成"暂停",接着调用ScanerStart,模拟进度条
如果回应fail则替换状态为"参数错误",按钮保持"返回"

UpdateUARTHMI中HMI_Page_Execute_CN分支中刷新扫描进度,扫描进度为100时替换状态为"完成",按钮变成"返回"

如果收到了"执行"页面的按钮按下事件,判断当前是否在扫描
如果未在扫描(scan返回fail,没能调用ScanerStart),则返回"峰值搜索"页面
如果正在扫描,则构造scan stop命令发送给模块,并等待回应,然后停止扫描(调用ScanerStop),替换状态为"中断",按钮变成"返回"
*/

/***************************************************************************
;** 函数名称:  bool ScanerStart(uint32_t ulStepNum)
;** 功能描述:  开始扫描
;** 输入参数:  步进个数
;** 返 回 值:  true 启动成功
;** 全局变量:
;** 调用模块:
;** 作　  者:  huangjian
;** 日　  期:  2026-6-25
;** 修改原因：
;** 说    明:
;***************************************************************************/
bool ScanerStart(uint32_t ulStepNum)
{
    if (ulStepNum)
    {
        ulScaner_StepNum = ulStepNum;
        ulScaner_StepCnt = 0;

        return true;
    }

    return false;
}

/***************************************************************************
;** 函数名称:  void ScanerStop(void)
;** 功能描述:  停止扫描
;** 输入参数:  步进个数
;** 返 回 值:
;** 全局变量:
;** 调用模块:
;** 作　  者:  huangjian
;** 日　  期:  2026-6-25
;** 修改原因：
;** 说    明:
;***************************************************************************/
void ScanerStop(void)
{
    ulScaner_StepNum = 0;
    ulScaner_StepCnt = 0;
}

/***************************************************************************
;** 函数名称:  bool ScanerProgressCheck(uint8_t *p_ucProgress)
;** 功能描述:  检查扫描进度
;** 输出参数:  扫描进度
;** 返 回 值:  true 扫描进行中或扫描完成(此时输出的进度有意义) false 不在扫描中
;** 全局变量:
;** 调用模块:
;** 作　  者:  huangjian
;** 日　  期:  2026-6-25
;** 修改原因：
;** 说    明:
;***************************************************************************/
bool ScanerProgressCheck(uint8_t *p_ucProgress)
{
    uint32_t ulProgress;

    if (!ulScaner_StepNum)
        return false;

    if (ulScaner_StepCnt == ulScaner_StepNum)
    {
        if ((ulScaner_StepCnt) && (p_ucProgress))
        {
            *p_ucProgress = 100;
        }

        ScanerStop();

        return true;
    }

    if (p_ucProgress)
    {
        ulProgress = ulScaner_StepCnt * 100;
        ulProgress /= ulScaner_StepNum;

        if (ulProgress > 100)
            ulProgress = 100;

        *p_ucProgress = ulProgress;

        if (ulScaner_StepCnt < ulScaner_StepNum)
        {
            ulScaner_StepCnt += 1;
        }
    }

    return true;
}

/***************************************************************************
;** 函数名称:  bool ScanerOngoingCheck(void)
;** 功能描述:  检查是否在扫描
;** 输入参数:
;** 返 回 值:  true 扫描进行中 false 不在扫描中或扫描完成
;** 全局变量:
;** 调用模块:
;** 作　  者:  huangjian
;** 日　  期:  2026-6-25
;** 修改原因：
;** 说    明:
;***************************************************************************/
bool ScanerOngoingCheck(void)
{
    if (ulScaner_StepCnt < ulScaner_StepNum)
        return true;

    return false;
}

/***************************************************************************
;** 函数名称:  bool get_max_channel(int *p_count)
;** 功能描述:  获取模块中的定标点"槽位"
;** 输入参数:  p_count 定标点"槽位"
;** 返 回 值:  true 获取成功
;** 全局变量:
;** 调用模块:
;** 作　  者:  huangjian
;** 日　  期:  2026-6-24
;** 修改原因：
;** 说    明:
;***************************************************************************/
bool get_max_channel(int *p_count)
{
    if (!p_count)
        return false;

    *p_count = 0;

    PortSelect_ClrRecvFifo(Port_DUT2);
    sprintfx("max ?\r\n");
    PortSelect(Port_Release);

    if (PortWait(Port_DUT2, 500, 20) == true)
    {
        if (strstr((char *)pDUT2->rxFIFO, "max"))
        {
            sscanf((char *)pDUT2->rxFIFO, "%*s %d", p_count);

            return true;
        }
    }

    return false;
}

/***************************************************************************
;** 函数名称:  bool get_wavelength_at_channel(int index, int *p_wl)
;** 功能描述:  获取模块中的定标点信息中的波长
;** 输入参数:  index 定标点序号(1...)
;** 输入参数:  p_wl 定标点中心波长
;** 返 回 值:  true 获取成功且定标点信息有效
;** 全局变量:
;** 调用模块:
;** 作　  者:  huangjian
;** 日　  期:  2026-6-24
;** 修改原因：
;** 说    明:
;***************************************************************************/
bool get_wavelength_at_channel(int index, int *p_wl)
{
    if (index < 1)
        return false;
    if (!p_wl)
        return false;

    *p_wl = 0;

    for (uint8_t i = 0; i < 3; i++)
    {
        PortSelect_ClrRecvFifo(Port_DUT2);
        sprintfx("lvd r c%02u\r\n", index);
        PortSelect(Port_Release);

        if (PortWait(Port_DUT2, 500, 20) == true)
        {
            // PortSelect(Port_UART);
            // sprintfx("lvd r c%02u\r\n", index);
            // sprintfx((char *)pDUT2->rxFIFO);
            // PortSelect(Port_Release);

            if ((strstr((char *)pDUT2->rxFIFO, "\r")) || (strstr((char *)pDUT2->rxFIFO, "\n")))
            {
                char *p_Idx = strstr((char *)pDUT2->rxFIFO, "W:");
                if (p_Idx)
                {
                    p_Idx += strlen("W:");
                    *p_wl = (int)(atof((const char *)p_Idx) * 1000);

                    if (*p_wl == 0)
                        return false;

                    return true;
                }
            }
        }

        PortTickDelay(10);
    }

    return true;
}

/***************************************************************************
;** 函数名称:  bool CalibrationStatistics(CalibrationInfo_t *info)
;** 功能描述:  获取模块中的最大最小定标点信息和有效点数
;** 输入参数:  info 统计信息
;** 返 回 值:  true 获取成功
;** 全局变量:
;** 调用模块:
;** 作　  者:  huangjian
;** 日　  期:  2026-6-24
;** 修改原因：
;** 说    明:
;***************************************************************************/
bool CalibrationStatistics(CalibrationInfo_t *info)
{
    int wavelength;
    int left;
    int right;

    if (!info)
        return false;

    // 初始化统计信息
    info->max_count = 0;
    info->valid_count = 0;
    info->first_valid = 1;
    info->last_valid = -1;
    info->wl_max = 0;
    info->wl_min = 0;

    if (get_max_channel(&info->max_count) == false)
        return false;

    // 1. 二分查找最后一个有效点(默认定标从1号开始,没有间断)
    left = 1;
    right = info->max_count;

    while (left <= right)
    {
        int mid = (left + right) / 2;

        if (get_wavelength_at_channel(mid, &wavelength))
        {
            // 有效
            info->last_valid = mid;
            // 更新统计...
            left = mid + 1; // 向右找
        }
        else
        {
            right = mid - 1; // 向左找
        }
    }

    if (get_wavelength_at_channel(info->first_valid, &info->wl_max) == false)
        return false;

    if (get_wavelength_at_channel(info->last_valid, &info->wl_min) == false)
        return false;

    // 3. 计算有效点数（在边界确定后）
    if (info->first_valid > 0 && info->last_valid > 0)
    {
        info->valid_count = info->last_valid - info->first_valid + 1;

        return true;
    }

    return false;
}

/***************************************************************************
;** 函数名称:  bool InputWavLenCheck(uint32_t ulwl)
;** 功能描述:  判断输入的波长是否在模块的定标范围内
;** 输入参数:  ulwl 波长(pm为单位的整数,1577.03nm需要输入1577030)
;** 返 回 值:  true 在范围内
;** 全局变量:
;** 调用模块:
;** 作　  者:  huangjian
;** 日　  期:  2026-6-24
;** 修改原因：
;** 说    明:
;***************************************************************************/
bool InputWavLenCheck(uint32_t ulwl)
{
    if (!CalibrationInfo.valid_count)
        return false;

    if ((ulwl < CalibrationInfo.wl_min) || (ulwl > CalibrationInfo.wl_max))
        return false;

    return true;
}

/***************************************************************************
;** 函数名称:  bool CenterWavLenOffset_Read(int32_t *p_lOffset)
;** 功能描述:  从模块中读取中心波长偏移值
;** 输出参数:  p_lOffset 波长偏移(pm为单位的整数,1577.03nm需要输入1577030)
;** 返 回 值:
;** 全局变量:
;** 调用模块:
;** 作　  者:  huangjian
;** 日　  期:  2026-6-25
;** 修改原因：
;** 说    明:
;***************************************************************************/
bool CenterWavLenOffset_Read(int32_t *p_lOffset)
{
    return false;
}

/***************************************************************************
;** 函数名称:  bool CenterWavLenOffset_Write(int32_t lOffset)
;** 功能描述:  写入中心波长偏移值到模块
;** 输入参数:  lOffset 波长偏移(pm为单位的整数,1577.03nm需要输入1577030)
;** 返 回 值:
;** 全局变量:
;** 调用模块:
;** 作　  者:  huangjian
;** 日　  期:  2026-6-25
;** 修改原因：
;** 说    明:
;***************************************************************************/
bool CenterWavLenOffset_Write(int32_t lOffset)
{
    return false;
}
