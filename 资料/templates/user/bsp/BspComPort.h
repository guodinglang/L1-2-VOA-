#ifndef __BSPCOMPORT_H__
#define __BSPCOMPORT_H__

#include "BspBoard.h"

#define BSPCOMPORT_NUM 16

typedef union
{
  uint8_t ucValue;
  struct
  {
    uint8_t bRdy : 1;
    uint8_t bRxStart : 1;
    uint8_t bRxDone : 1;
  };
} BspComPort_Flag_U;

typedef struct
{
  const char *p_caName;
  uint8_t *p_ucaBuff;
  uint16_t usSize;
  uint16_t usTimeOut;
  uint16_t (*p_Send)(uint8_t *p_ucaBuff, uint16_t usLen);
} BspComPort_Param_S;

typedef struct
{
  const char *p_caName;
  uint16_t usIdleCnt;
  uint16_t usIdleLimit;
  BspComPort_Flag_U Flag;
  chry_ringbuffer_t RxFifo;

  uint16_t (*p_Send)(uint8_t *p_ucaBuff, uint16_t usLen);
} BspComPort_S;

typedef uint16_t (*pBspComPort_Send)(uint8_t *p_ucaBuff, uint16_t usLen);

uint8_t BspComPort_Create(BspComPort_Param_S *p_Param);                                            // 创建缓冲(管理员)
bool BspComPort_Delete(uint8_t ucIdx);                                                             // 删除缓冲(管理员)
uint16_t BspComPort_Read(uint8_t ucIdx, uint8_t *p_ucaBuff, uint16_t usSize);                      // 读取接口的数据(消费端,命令解析用途)
uint16_t BspComPort_GetRxCount(uint8_t ucHandle);                                                  // 读取接口的数据个数(消费端,命令解析用途)
bool BspComPort_RxDoneCheck(uint8_t ucIdx, bool bClrDone);                                         // 检查接收是否完成(消费端)
bool BspComPort_RxDoneClr(uint8_t ucHandle);                                                       // 清除接口的接收完毕标记(消费端)
void BspComPort_RxIdleDec(void);                                                                   // 接收完成逻辑(框架)
void BspComPort_RxStart(uint8_t ucIdx);                                                            // 接收开始(生产端)
bool BspComPort_RxBuffWriteByte(uint8_t ucIdx, uint8_t ucByte);                                    // 往rxfifo写一个字节(生产端)
uint8_t *BspComPort_RxBuffGetLinear(uint8_t ucHandle, uint16_t *p_usSize);                         // 往rxfifo写一串字节(前 生产端)
bool BspComPort_RxBuffLinearWriteDone(uint8_t ucHandle, uint16_t usSize);                          // 往rxfifo写一串字节(后 生产端)
bool BspComPort_Printf(uint8_t ucIdx, char *p_caBuff, uint16_t usBuffSize, char *p_caString, ...); // 打印数据到接口(消费端,命令响应用途)
bool BspComPort_Send(uint8_t ucHandle, uint8_t *p_ucaBuff, uint16_t usBuffLen);                    // 发送数据到接口(消费端,命令响应用途)
uint8_t BspComPort_Name2Handle(const char *p_caName);                                              // 从名字匹配句柄

#endif /*BspComPort.h*/
