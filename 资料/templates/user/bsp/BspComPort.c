#include "BspConfig.h"

/*
定义一种单生产单消费的低速接口,接收方向使用fifo(超时空闲认为接收完毕),发送方向使用阻塞

if (BspComPort_RxDoneCheck(BspComPort_Name2Handle("uart_lcd"), true) == true)
{
  {
    uint16_t usRxLen;
    uint8_t *tp_ucaRxBuff = rt_malloc(64);

    if (tp_ucaRxBuff)
    {
      do
      {
        usRxLen = BspComPort_Read(BspComPort_Name2Handle("uart_lcd"), tp_ucaRxBuff, 64);
        if (!usRxLen)
          break;

        BspUart_SendBuff(BspUartCom_RS232, tp_ucaRxBuff, usRxLen);
      } while (1);
    }

    rt_free(tp_ucaRxBuff);
  }
}

*/

BspComPort_S BspComPort[BSPCOMPORT_NUM] = {0};

/// @brief 创建接口
/// @param p_Param 参数列表
/// @return =0 :创建失败 <=BSPCOMPORT_NUM :句柄
uint8_t BspComPort_Create(BspComPort_Param_S *p_Param)
{
  if (!p_Param)
    return 0;
  if (!p_Param->p_caName)
    return 0;
  if (!p_Param->p_ucaBuff)
    return 0;
  if (!p_Param->usSize)
    return 0;
  if (!p_Param->usTimeOut)
    return 0;
  if (!p_Param->p_Send)
    return 0;

  for (uint8_t i = 0; i < BSPCOMPORT_NUM; i++)
  {
    if (BspComPort[i].Flag.bRdy == true)
      continue;

    memset(&BspComPort[i], 0, sizeof(BspComPort_S));

    if (chry_ringbuffer_init(&BspComPort[i].RxFifo, p_Param->p_ucaBuff, p_Param->usSize) == 0)
    {

      BspComPort[i].p_caName = p_Param->p_caName;
      BspComPort[i].usIdleLimit = p_Param->usTimeOut;
      BspComPort[i].p_Send = p_Param->p_Send;
      BspComPort[i].Flag.bRdy = true;

      return (i + 1);
    }

    return 0;
  }

  return 0;
}

/// @brief 删除接口
/// @param ucHandle 句柄
/// @return true:删除成功
bool BspComPort_Delete(uint8_t ucHandle)
{
  if ((ucHandle > BSPCOMPORT_NUM) || (!ucHandle))
    return false;

  ucHandle -= 1;

  memset(&BspComPort[ucHandle], 0, sizeof(BspComPort_S));

  return true;
}

/// @brief 从接口读取数据
/// @param ucHandle 句柄
/// @param p_ucaBuff 缓冲
/// @param usSize 缓冲大小
/// @return 实际读取到的数据长度
uint16_t BspComPort_Read(uint8_t ucHandle, uint8_t *p_ucaBuff, uint16_t usSize)
{
  if ((ucHandle > BSPCOMPORT_NUM) || (!ucHandle))
    return 0;
  if (!p_ucaBuff)
    return 0;

  ucHandle -= 1;

  if (BspComPort[ucHandle].Flag.bRdy == false)
    return 0;

  return (uint16_t)chry_ringbuffer_read(&BspComPort[ucHandle].RxFifo, p_ucaBuff, usSize);
}

/// @brief 获取接口收到的数据个数
/// @param ucHandle 句柄
/// @return 收到的数据个数
uint16_t BspComPort_GetRxCount(uint8_t ucHandle)
{
  if ((ucHandle > BSPCOMPORT_NUM) || (!ucHandle))
    return 0;

  ucHandle -= 1;

  if (BspComPort[ucHandle].Flag.bRdy == false)
    return 0;

  return (uint16_t)chry_ringbuffer_get_used(&BspComPort[ucHandle].RxFifo);
}

/// @brief 检查接口是否接收完毕
/// @param ucHandle 句柄
/// @param bClrDone 检查后是否清除标志
/// @return true:接收完毕
bool BspComPort_RxDoneCheck(uint8_t ucHandle, bool bClrDone)
{
  bool bDone = false;

  if ((ucHandle > BSPCOMPORT_NUM) || (!ucHandle))
    return false;

  ucHandle -= 1;

  bDone = BspComPort[ucHandle].Flag.bRxDone;

  if (bClrDone == true)
  {
    BspComPort[ucHandle].Flag.bRxDone = false;
  }

  return bDone;
}

/// @brief 清除接口的接收完毕标记
/// @param ucHandle 句柄
/// @return
bool BspComPort_RxDoneClr(uint8_t ucHandle)
{
  if ((ucHandle > BSPCOMPORT_NUM) || (!ucHandle))
    return false;

  BspComPort[ucHandle].Flag.bRxDone = false;

  return true;
}

/// @brief 接收完成判断
/// @param
void BspComPort_RxIdleDec(void)
{
  for (uint8_t i = 0; i < BSPCOMPORT_NUM; i++)
  {
    if (BspComPort[i].Flag.bRdy == false)
      continue;

    if (BspComPort[i].usIdleCnt)
    {
      if (--BspComPort[i].usIdleCnt == 0)
      {
        BspComPort[i].Flag.bRxStart = false;
        BspComPort[i].Flag.bRxDone = true;
      }
    }
  }
}

/// @brief 标记接收开始
/// @param ucHandle 句柄
void BspComPort_RxStart(uint8_t ucHandle)
{
  if ((ucHandle > BSPCOMPORT_NUM) || (!ucHandle))
    return;

  ucHandle -= 1;

  BspComPort[ucHandle].Flag.bRxStart = true;
  BspComPort[ucHandle].Flag.bRxDone = false;
  BspComPort[ucHandle].usIdleCnt = BspComPort[ucHandle].usIdleLimit;
}

/// @brief 往接收缓冲中写入一个字节
/// @param ucHandle 句柄
/// @param ucByte 字节
/// @return true:写入成功
bool BspComPort_RxBuffWriteByte(uint8_t ucHandle, uint8_t ucByte)
{
  if ((ucHandle > BSPCOMPORT_NUM) || (!ucHandle))
    return false;

  ucHandle -= 1;

  return chry_ringbuffer_write_byte(&BspComPort[ucHandle].RxFifo, ucByte);
}

/// @brief 获取最大可用的线性缓冲
/// @param ucHandle 句柄
/// @param p_usSize 缓冲大小
/// @return !=0 :获取成功 0:满了?
uint8_t *BspComPort_RxBuffGetLinear(uint8_t ucHandle, uint16_t *p_usSize)
{
  uint8_t *p_ucaLinearBuff;
  uint32_t ulSize;

  if ((ucHandle > BSPCOMPORT_NUM) || (!ucHandle))
    return 0;
  if (!p_usSize)
    return 0;

  ucHandle -= 1;

  if (BspComPort[ucHandle].Flag.bRdy == false)
    return 0;

  p_ucaLinearBuff = (uint8_t *)chry_ringbuffer_linear_write_setup(&BspComPort[ucHandle].RxFifo, &ulSize);

  if (!p_ucaLinearBuff)
    return 0;

  *p_usSize = ulSize;

  return p_ucaLinearBuff;
}

/// @brief 标记线性缓冲写完
/// @param ucHandle 句柄
/// @param ulSize 线性缓冲用了多少?
/// @return true:标记成功
bool BspComPort_RxBuffLinearWriteDone(uint8_t ucHandle, uint16_t usSize)
{
  if ((ucHandle > BSPCOMPORT_NUM) || (!ucHandle))
    return false;

  ucHandle -= 1;

  if (BspComPort[ucHandle].Flag.bRdy == false)
    return false;

  return (bool)chry_ringbuffer_linear_write_done(&BspComPort[ucHandle].RxFifo, usSize);
}

/// @brief 打印数据到接口
/// @param ucHandle 句柄
/// @param p_caBuff 打印缓冲
/// @param usBuffSize 打印缓冲大小
/// @param p_caString 格式化字符串
/// @param
/// @return true:打印成功
bool BspComPort_Printf(uint8_t ucHandle, char *p_caBuff, uint16_t usBuffSize, char *p_caString, ...)
{
  va_list args;

  if ((ucHandle > BSPCOMPORT_NUM) || (!ucHandle))
    return false;
  if (!p_caBuff)
    return false;
  if (!p_caString)
    return false;

  ucHandle -= 1;

  memset(p_caBuff, 0, usBuffSize);

  va_start(args, p_caString);
  rt_vsnprintf(p_caBuff, usBuffSize, (const char *)p_caString, args);
  va_end(args);

  if (BspComPort[ucHandle].p_Send)
  {
    if (BspComPort[ucHandle].p_Send((uint8_t *)p_caBuff, strlen((const char *)p_caBuff)) == strlen((const char *)p_caBuff))
      return true;
  }

  return false;
}

/// @brief 发送数据到接口
/// @param ucHandle 句柄
/// @param p_ucaBuff 缓冲
/// @param usBuffLen 缓冲长度
/// @return
bool BspComPort_Send(uint8_t ucHandle, uint8_t *p_ucaBuff, uint16_t usBuffLen)
{
  if ((ucHandle > BSPCOMPORT_NUM) || (!ucHandle))
    return false;
  if (!p_ucaBuff)
    return false;
  if (!usBuffLen)
    return false;

  ucHandle -= 1;

  if (BspComPort[ucHandle].p_Send)
  {
    if (BspComPort[ucHandle].p_Send((uint8_t *)p_ucaBuff, usBuffLen) == usBuffLen)
      return true;
  }

  return false;
}

/// @brief 从名字匹配句柄
/// @param p_caName 名字
/// @return =0 :匹配失败 <=BSPCOMPORT_NUM :句柄
uint8_t BspComPort_Name2Handle(const char *p_caName)
{
  if (!p_caName)
    return 0;

  for (uint8_t i = 0; i < BSPCOMPORT_NUM; i++)
  {
    if (BspComPort[i].Flag.bRdy == false)
      continue;
    if (strcmp(p_caName, BspComPort[i].p_caName) == 0)
      return (i + 1);
  }

  return 0;
}
