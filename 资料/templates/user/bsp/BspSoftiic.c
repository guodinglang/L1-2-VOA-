#include "BspConfig.h"

#define I2C_SCL_L gpio_bits_reset(GpioPortDescLib[BoardGpio_I2C_SCL].p_Port, GpioPortDescLib[BoardGpio_I2C_SCL].usPins)
#define I2C_SCL_H gpio_bits_set(GpioPortDescLib[BoardGpio_I2C_SCL].p_Port, GpioPortDescLib[BoardGpio_I2C_SCL].usPins)

#define I2C_SDA_L gpio_bits_reset(GpioPortDescLib[BoardGpio_I2C_SDA].p_Port, GpioPortDescLib[BoardGpio_I2C_SDA].usPins)
#define I2C_SDA_H gpio_bits_set(GpioPortDescLib[BoardGpio_I2C_SDA].p_Port, GpioPortDescLib[BoardGpio_I2C_SDA].usPins)

#define READ_I2C_SCL() gpio_input_data_bit_read(GpioPortDescLib[BoardGpio_I2C_SCL].p_Port, GpioPortDescLib[BoardGpio_I2C_SCL].usPins)
#define READ_I2C_SDA() gpio_input_data_bit_read(GpioPortDescLib[BoardGpio_I2C_SDA].p_Port, GpioPortDescLib[BoardGpio_I2C_SDA].usPins)

#define I2C_SCL_IN                                  \
  gpio_init_struct_SCL.gpio_mode = GPIO_MODE_INPUT; \
  gpio_init(GpioPortDescLib[BoardGpio_I2C_SCL].p_Port, &gpio_init_struct_SCL);

#define I2C_SCL_OUT                                  \
  gpio_init_struct_SCL.gpio_mode = GPIO_MODE_OUTPUT; \
  gpio_init(GpioPortDescLib[BoardGpio_I2C_SCL].p_Port, &gpio_init_struct_SCL);

#define I2C_SDA_IN                                  \
  gpio_init_struct_SDA.gpio_mode = GPIO_MODE_INPUT; \
  gpio_init(GpioPortDescLib[BoardGpio_I2C_SDA].p_Port, &gpio_init_struct_SDA);

#define I2C_SDA_OUT                                  \
  gpio_init_struct_SDA.gpio_mode = GPIO_MODE_OUTPUT; \
  gpio_init(GpioPortDescLib[BoardGpio_I2C_SDA].p_Port, &gpio_init_struct_SDA);

gpio_init_type gpio_init_struct_SCL;
gpio_init_type gpio_init_struct_SDA;

void BspSoftiic_Init(void)
{
  gpio_default_para_init(&gpio_init_struct_SCL);
  gpio_default_para_init(&gpio_init_struct_SDA);

  I2C_SCL_H;
  gpio_init_struct_SCL.gpio_mode = GPIO_MODE_OUTPUT;
  gpio_init_struct_SCL.gpio_pins = GpioPortDescLib[BoardGpio_I2C_SCL].usPins;
  gpio_init_struct_SCL.gpio_out_type = GPIO_OUTPUT_PUSH_PULL;
  gpio_init_struct_SCL.gpio_pull = GPIO_PULL_UP;
  gpio_init_struct_SCL.gpio_drive_strength = GPIO_DRIVE_STRENGTH_MODERATE;
  gpio_init(GpioPortDescLib[BoardGpio_I2C_SCL].p_Port, &gpio_init_struct_SCL);

  I2C_SDA_H;
  gpio_init_struct_SDA.gpio_mode = GPIO_MODE_OUTPUT;
  gpio_init_struct_SDA.gpio_pins = GpioPortDescLib[BoardGpio_I2C_SDA].usPins;
  gpio_init_struct_SDA.gpio_out_type = GPIO_OUTPUT_PUSH_PULL;
  gpio_init_struct_SDA.gpio_pull = GPIO_PULL_UP;
  gpio_init_struct_SDA.gpio_drive_strength = GPIO_DRIVE_STRENGTH_MODERATE;
  gpio_init(GpioPortDescLib[BoardGpio_I2C_SDA].p_Port, &gpio_init_struct_SDA);

  BspSoftiic_Stop();
}

void BspSoftiic_DeInit(void)
{
  gpio_default_para_init(&gpio_init_struct_SCL);
  gpio_default_para_init(&gpio_init_struct_SDA);

  gpio_init_struct_SCL.gpio_mode = GPIO_MODE_INPUT;
  gpio_init_struct_SCL.gpio_pins = GpioPortDescLib[BoardGpio_I2C_SCL].usPins;
  gpio_init_struct_SCL.gpio_out_type = GPIO_OUTPUT_PUSH_PULL;
  gpio_init_struct_SCL.gpio_pull = GPIO_PULL_NONE;
  gpio_init_struct_SCL.gpio_drive_strength = GPIO_DRIVE_STRENGTH_MODERATE;
  gpio_init(GpioPortDescLib[BoardGpio_I2C_SCL].p_Port, &gpio_init_struct_SCL);

  gpio_init_struct_SDA.gpio_mode = GPIO_MODE_INPUT;
  gpio_init_struct_SDA.gpio_pins = GpioPortDescLib[BoardGpio_I2C_SDA].usPins;
  gpio_init_struct_SDA.gpio_out_type = GPIO_OUTPUT_PUSH_PULL;
  gpio_init_struct_SDA.gpio_pull = GPIO_PULL_NONE;
  gpio_init_struct_SDA.gpio_drive_strength = GPIO_DRIVE_STRENGTH_MODERATE;
  gpio_init(GpioPortDescLib[BoardGpio_I2C_SDA].p_Port, &gpio_init_struct_SDA);
}

static inline void BspSoftiic_Delay(void)
{
  BspDwt_DelayUS(10);
}

void BspSoftiic_Start(void)
{
  I2C_SDA_H;
  I2C_SDA_OUT;
  I2C_SCL_H;
  BspSoftiic_Delay();
  I2C_SDA_L;
  BspSoftiic_Delay();
  I2C_SCL_L;
  BspSoftiic_Delay();
}

void BspSoftiic_Stop(void)
{
  I2C_SDA_L;
  I2C_SDA_OUT;
  I2C_SCL_H;
  BspSoftiic_Delay();
  I2C_SDA_H;
}

void BspSoftiic_SendByte(uint8_t ucByte)
{
  uint8_t i;

  I2C_SDA_OUT;

  for (i = 0; i < 8; i++)
  {
    if (ucByte & 0x80)
    {
      I2C_SDA_H;
    }
    else
    {
      I2C_SDA_L;
    }
    BspSoftiic_Delay();
    I2C_SCL_H;
    BspSoftiic_Delay();
    I2C_SCL_L;
    if (i == 7)
    {
      I2C_SDA_H; // ÊÍ·Å×ÜÏß
    }
    ucByte <<= 1;
    BspSoftiic_Delay();
  }
}

uint8_t BspSoftiic_ReadByte(void)
{
  uint8_t i;
  uint8_t ucByte = 0;

  I2C_SDA_IN;

  for (i = 0; i < 8; i++)
  {
    ucByte <<= 1;
    I2C_SCL_H;
    BspSoftiic_Delay();
    if (READ_I2C_SDA())
    {
      ucByte++;
    }
    I2C_SCL_L;
    BspSoftiic_Delay();
  }

  return ucByte;
}

uint8_t BspSoftiic_WaitAck(void)
{
  uint8_t ucAck;

  I2C_SDA_H;
  I2C_SDA_OUT;
  BspSoftiic_Delay();
  I2C_SCL_H;
  I2C_SDA_IN;
  BspSoftiic_Delay();
  if (READ_I2C_SDA())
  {
    ucAck = 1;
  }
  else
  {
    ucAck = 0;
  }
  I2C_SCL_L;
  BspSoftiic_Delay();

  return ucAck;
}

void BspSoftiic_Ack(void)
{
  I2C_SDA_L;
  I2C_SDA_OUT;
  BspSoftiic_Delay();
  I2C_SCL_H;
  BspSoftiic_Delay();
  I2C_SCL_L;
  BspSoftiic_Delay();
  I2C_SDA_H;
}

void BspSoftiic_NAck(void)
{
  I2C_SDA_H;
  I2C_SDA_OUT;
  BspSoftiic_Delay();
  I2C_SCL_H;
  BspSoftiic_Delay();
  I2C_SCL_L;
  BspSoftiic_Delay();
}

bool BspSoftiic_CheckDevice(uint8_t ucAddr)
{
  uint8_t ucAck;

  bool bBusIdle = false;

  I2C_SCL_H;
  I2C_SCL_OUT;
  I2C_SDA_IN;

  if ((READ_I2C_SCL()) && (READ_I2C_SDA()))
  {
    bBusIdle = true;
  }

  if (bBusIdle == true)
  {
    BspSoftiic_Start();

    BspSoftiic_SendByte(ucAddr | I2C_WR);

    ucAck = BspSoftiic_WaitAck();

    BspSoftiic_Stop();

    return (ucAck) ? false : true;
  }

  return false;
}

bool BspSoftiic_WriteData(uint8_t ucAddr, uint8_t *p_ucaBuff, uint8_t ucBuffLen)
{
  uint8_t i;
  uint8_t ucTryTimes;

  BspSoftiic_Stop();

  for (ucTryTimes = 0; ucTryTimes < 3; ucTryTimes++)
  {
    BspSoftiic_Start();

    BspSoftiic_SendByte(ucAddr | I2C_WR);

    if (BspSoftiic_WaitAck() == 0)
    {
      break;
    }

    BspSoftiic_Stop();
  }
  if (ucTryTimes == 3)
  {
    BspSoftiic_Stop();
    return false;
  }

  for (i = 0; i < ucBuffLen; i++)
  {
    BspSoftiic_SendByte(p_ucaBuff[i]);
    if (BspSoftiic_WaitAck() != 0)
    {
      BspSoftiic_Stop();
      return false;
    }
  }
  BspSoftiic_Stop();

  return true;
}

bool BspSoftiic_ReadData(uint8_t ucAddr, uint8_t *p_ucaBuff, uint8_t ucBuffLen)
{
  uint8_t i;
  uint8_t ucTryTimes;

  for (ucTryTimes = 0; ucTryTimes < 3; ucTryTimes++)
  {
    BspSoftiic_Start();

    BspSoftiic_SendByte(ucAddr | I2C_RD);

    if (BspSoftiic_WaitAck() == 0)
    {
      break;
    }

    BspSoftiic_Stop();
  }
  if (ucTryTimes == 3)
  {
    BspSoftiic_Stop();
    return false;
  }
  for (i = 0; i < ucBuffLen; i++)
  {
    p_ucaBuff[i] = BspSoftiic_ReadByte();
    if (i == (ucBuffLen - 1))
    {
      BspSoftiic_NAck();
    }
    else
    {
      BspSoftiic_Ack();
    }
  }
  BspSoftiic_Stop();

  return true;
}

bool BspSoftiic_ReadData_Delay(uint8_t ucAddr, uint8_t *p_ucaBuff, uint8_t ucBuffLen, uint16_t usDelay)
{
  uint8_t i;
  uint8_t ucTryTimes;

  for (ucTryTimes = 0; ucTryTimes < 3; ucTryTimes++)
  {
    BspSoftiic_Start();

    BspSoftiic_SendByte(ucAddr | I2C_RD);

    if (BspSoftiic_WaitAck() == 0)
    {
      break;
    }

    BspSoftiic_Stop();
  }
  if (ucTryTimes == 3)
  {
    BspSoftiic_Stop();
    return false;
  }
  for (i = 0; i < ucBuffLen; i++)
  {
    p_ucaBuff[i] = BspSoftiic_ReadByte();
    if (i == (ucBuffLen - 1))
    {
      BspSoftiic_NAck();
    }
    else
    {
      BspSoftiic_Ack();
    }

    BspDwt_DelayUS(usDelay);
  }
  BspSoftiic_Stop();

  return true;
}

bool BspSoftiic_WriteReg(uint8_t ucDeviceAddr, uint8_t uccRegAddr, uint8_t *p_ucaBuff, uint8_t ucRegNum)
{
  uint8_t i;
  uint8_t ucTryTimes;

  BspSoftiic_Stop();

  for (ucTryTimes = 0; ucTryTimes < 3; ucTryTimes++)
  {
    BspSoftiic_Start();

    BspSoftiic_SendByte(ucDeviceAddr | I2C_WR);

    if (BspSoftiic_WaitAck() == 0)
    {
      break;
    }

    BspSoftiic_Stop();
  }
  if (ucTryTimes == 3)
  {
    BspSoftiic_Stop();
    return false;
  }

  BspSoftiic_SendByte(uccRegAddr);
  if (BspSoftiic_WaitAck() != 0)
  {
    BspSoftiic_Stop();
    return false;
  }

  for (i = 0; i < ucRegNum; i++)
  {
    BspSoftiic_SendByte(p_ucaBuff[i]);
    if (BspSoftiic_WaitAck() != 0)
    {
      BspSoftiic_Stop();
      return false;
    }
  }
  BspSoftiic_Stop();
  return true;
}

bool BspSoftiic_ReadReg(uint8_t ucDeviceAddr, uint8_t ucRegAddr, uint8_t *p_ucaBuff, uint8_t ucRegNum)
{
  if (BspSoftiic_WriteData(ucDeviceAddr, (uint8_t *)&ucRegAddr, 1) == false)
    return false;

  if (BspSoftiic_ReadData(ucDeviceAddr, p_ucaBuff, ucRegNum) == false)
    return false;

  return true;
}

bool BspSoftiic_ReadReg_Delay(uint8_t ucDeviceAddr, uint8_t ucRegAddr, uint8_t *p_ucaBuff, uint8_t ucRegNum, uint16_t usDelay)
{
  if (BspSoftiic_WriteData(ucDeviceAddr, (uint8_t *)&ucRegAddr, 1) == false)
    return false;

  if (BspSoftiic_ReadData_Delay(ucDeviceAddr, p_ucaBuff, ucRegNum, usDelay) == false)
    return false;

  return true;
}
