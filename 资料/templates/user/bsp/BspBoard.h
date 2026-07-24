#ifndef __BSPBOARD_H__
#define __BSPBOARD_H__

#include "at32f403a_407.h"

#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include "chry_ringbuffer.h"

#define ENABLE_INT() __enable_irq();   /* 使能中断 */
#define DISABLE_INT() __disable_irq(); /* 关闭中断 */

#define BV(n) (1 << (n))

#define SH8(n) ((uint8_t)(n >> 8))
#define SL8(n) ((uint8_t)(n))

#define C2S(h8, l8) ((uint16_t)(((uint16_t)h8 << 8) | ((uint16_t)l8)))

#define LH16(n) ((uint16_t)((uint32_t)n >> 16))
#define LL16(n) ((uint16_t)((uint32_t)n))

#define S2L(h16, l16) ((uint32_t)(((uint32_t)h16 << 16) | ((uint32_t)l16)))

#define LHH8(n) ((uint8_t)((uint32_t)n >> 24))
#define LH8(n) ((uint8_t)((uint32_t)n >> 16))
#define LM8(n) ((uint8_t)((uint32_t)n >> 8))
#define LL8(n) ((uint8_t)((uint32_t)n))

#define ABS(n) ((n < 0) ? (-n) : (n))
#define MIN(m, n) ((n < m) ? (n) : (m))

#define DIFF(m, n) (ABS((m - n)))

#define C2L(hh8, h8, m8, l8) ((uint32_t)(((uint32_t)hh8 << 24) | ((uint32_t)h8 << 16) | ((uint32_t)m8 << 8) | ((uint32_t)l8)))

#define OFFSETOF(struct_type, member) ((size_t)&((struct_type *)0)->member)

#define BOARD_GPIO_NUM 24

typedef enum
{
  BoardGpio_DUT_D1, // PA7

  BoardGpio_DUT_D4,    // PB0
  BoardGpio_DUT_D3,    // PB1
  BoardGpio_DUT_D7,    // PB2
  BoardGpio_CH9434_CS, // PB6
  BoardGpio_LED_STA,   // PB7
  BoardGpio_I2C_SCL,   // PB8
  BoardGpio_I2C_SDA,   // PB9
  BoardGpio_W5500_CS,  // PB12

  BoardGpio_DUT_D2,    // PC5
  BoardGpio_BUZZER,    // PC9
  BoardGpio_W5500_RST, // PC12

  BoardGpio_CH9434_INT, // PD7
  BoardGpio_W5500_INT,  // PD8
  BoardGpio_DUT_STROBE, // PD9
  BoardGpio_DUT_NRST,   // PD10
  BoardGpio_SPK,        // PD12

  BoardGpio_USB_DET,   // PE2
  BoardGpio_DUT_POW,   // PE3
  BoardGpio_DUT_D6,    // PE11
  BoardGpio_DUT_D5,    // PE12
  BoardGpio_DUT_D0,    // PE13
  BoardGpio_DUT_BUSY,  // PE14
  BoardGpio_DUT_ALARM, // PE15
} BoardGpio_E;

#define DMA_MOVE_SIZE_MAX 64000

typedef struct
{
  crm_periph_clock_type Clock;
  gpio_type *p_Port;
  uint16_t usPins;
  uint8_t ucaName[16];

  gpio_mode_type gpio_mode;            /*!< mode selection */
  gpio_pull_type gpio_pull;            /*!< pull type selection */
  gpio_output_type gpio_out_type;      /*!< output type selection */
  gpio_drive_type gpio_drive_strength; /*!< drive strength selection */

  confirm_state RstState_Out;
} GpioPortDesc_S;
extern const GpioPortDesc_S GpioPortDescLib[BOARD_GPIO_NUM];

typedef union
{
  float fData;
  uint32_t ulData;
} FloatLongType;

typedef union
{
  uint16_t usValue;
  struct
  {
    uint16_t b0 : 1;
    uint16_t b1 : 1;
    uint16_t b2 : 1;
    uint16_t b3 : 1;
    uint16_t b4 : 1;
    uint16_t b5 : 1;
    uint16_t b6 : 1;
    uint16_t b7 : 1;
    uint16_t b8 : 1;
    uint16_t b9 : 1;
    uint16_t b10 : 1;
    uint16_t b11 : 1;
    uint16_t b12 : 1;
    uint16_t b13 : 1;
    uint16_t b14 : 1;
    uint16_t b15 : 1;
  };
} uint16_bits_u;

extern crm_clocks_freq_type crm_clocks_freq_struct;

void BspBoard_Init(void);

#endif
