#ifndef __BSPSOFTIIC_H__
#define __BSPSOFTIIC_H__

#define I2C_WR 0
#define I2C_RD 1

#define BSPSOFTIIC_NUM 2

typedef enum
{
  BspSoftiic_OnBoard = 0,
  BspSoftiic_Export,
} BspSoftiic_E;

void BspSoftiic_Init(void);
void BspSoftiic_DeInit(void);
void BspSoftiic_Start(void);
void BspSoftiic_Stop(void);
void BspSoftiic_SendByte(uint8_t ucByte);
uint8_t BspSoftiic_ReadByte(void);
uint8_t BspSoftiic_WaitAck(void);
void BspSoftiic_Ack(void);
void BspSoftiic_NAck(void);
bool BspSoftiic_CheckDevice(uint8_t ucAddr);
bool BspSoftiic_WriteData(uint8_t ucAddr, uint8_t *p_ucaBuff, uint8_t ucBuffLen);
bool BspSoftiic_ReadData(uint8_t ucAddr, uint8_t *p_ucaBuff, uint8_t ucBuffLen);
bool BspSoftiic_ReadData_Delay(uint8_t ucAddr, uint8_t *p_ucaBuff, uint8_t ucBuffLen, uint16_t usDelay);
bool BspSoftiic_WriteReg(uint8_t ucDeviceAddr, uint8_t uccRegAddr, uint8_t *p_ucaBuff, uint8_t ucRegNum);
bool BspSoftiic_ReadReg(uint8_t ucDeviceAddr, uint8_t ucRegAddr, uint8_t *p_ucaBuff, uint8_t ucRegNum);
bool BspSoftiic_ReadReg_Delay(uint8_t ucDeviceAddr, uint8_t ucRegAddr, uint8_t *p_ucaBuff, uint8_t ucRegNum, uint16_t usDelay);

#endif /*BspSoftiic.h*/
