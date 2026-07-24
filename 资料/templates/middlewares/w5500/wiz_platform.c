#include "BspConfig.h"
#include "wiz_platform.h"
#include "wizchip_conf.h"
#include "wiz_interface.h"
#include "dhcp.h"

void debug_usart_init(void)
{
}

int fputc(int ch, FILE *f)
{
  BspUart_SendChar(BspUartCom_RS232, ch);

  return (ch);
}

int fgetc(FILE *f)
{
  uint8_t ucByte;

  if (BspUart_GetChar(BspUartCom_RS232, &ucByte) == false)
    return -1;

  return (int)ucByte;
}

void wiz_timer_init(void)
{
}

void wiz_spi_init(void)
{
}

void wiz_rst_int_init(void)
{
}

/**
 * @brief   delay init
 * @param   none
 * @return  none
 */
void delay_init(void)
{
}

/**
 * @brief   delay us
 * @param   none
 * @return  none
 */
void delay_us(uint32_t nus)
{
  // BspDwt_DelayUS(nus);
}

/**
 * @brief   delay ms
 * @param   none
 * @return  none
 */
void delay_ms(uint32_t nms)
{
  // BspDwt_DelayMS(nms);
  rt_thread_delay(nms);
}

/**
 * @brief   delay s
 * @param   none
 * @return  none
 */
void delay_s(uint32_t ns)
{
  while (ns--)
  {
    BspDwt_DelayMS(1000);
  }
}

/**
 * @brief   SPI select wizchip
 * @param   none
 * @return  none
 */
void wizchip_select(void)
{
  gpio_bits_reset(GpioPortDescLib[BoardGpio_W5500_CS].p_Port, GpioPortDescLib[BoardGpio_W5500_CS].usPins);
}

/**
 * @brief   SPI deselect wizchip
 * @param   none
 * @return  none
 */
void wizchip_deselect(void)
{
  gpio_bits_set(GpioPortDescLib[BoardGpio_W5500_CS].p_Port, GpioPortDescLib[BoardGpio_W5500_CS].usPins);
}

/**
 * @brief   SPI write 1 byte to wizchip
 * @param   ucByte:1 byte data
 * @return  none
 */
void wizchip_write_byte(uint8_t ucByte)
{
  while (spi_i2s_flag_get(SPI2, SPI_I2S_TDBE_FLAG) == RESET)
    ;
  spi_i2s_data_transmit(SPI2, ucByte);
  while (spi_i2s_flag_get(SPI2, SPI_I2S_RDBF_FLAG) == RESET)
    ;
  spi_i2s_data_receive(SPI2);
}

/**
 * @brief   SPI read 1 byte from wizchip
 * @param   none
 * @return  1 byte data
 */
uint8_t wizchip_read_byte(void)
{
  while (spi_i2s_flag_get(SPI2, SPI_I2S_TDBE_FLAG) == RESET)
    ;
  spi_i2s_data_transmit(SPI2, 0xFF);
  while (spi_i2s_flag_get(SPI2, SPI_I2S_RDBF_FLAG) == RESET)
    ;
  return spi_i2s_data_receive(SPI2);
}

/**
 * @brief   SPI write buff from wizchip
 * @param   buff:write buff
 * @param   len:write len
 * @return  none
 */
void wizchip_write_buff(uint8_t *buf, uint16_t len)
{
  uint16_t idx = 0;
  for (idx = 0; idx < len; idx++)
  {
    wizchip_write_byte(buf[idx]);
  }
}

/**
 * @brief   SPI read buff from wizchip
 * @param   buff:read buff
 * @param   len:read len
 * @return  none
 */
void wizchip_read_buff(uint8_t *buf, uint16_t len)
{
  uint16_t idx = 0;
  for (idx = 0; idx < len; idx++)
  {
    buf[idx] = wizchip_read_byte();
  }
}

/**
 * @brief   hardware reset wizchip
 * @param   none
 * @return  none
 */
void wizchip_reset(void)
{
  gpio_bits_set(GpioPortDescLib[BoardGpio_W5500_RST].p_Port, GpioPortDescLib[BoardGpio_W5500_RST].usPins);
  delay_ms(10);
  gpio_bits_reset(GpioPortDescLib[BoardGpio_W5500_RST].p_Port, GpioPortDescLib[BoardGpio_W5500_RST].usPins);
  delay_ms(10);
  gpio_bits_set(GpioPortDescLib[BoardGpio_W5500_RST].p_Port, GpioPortDescLib[BoardGpio_W5500_RST].usPins);
  delay_ms(10);
}

/**
 * @brief   wizchip spi callback register
 * @param   none
 * @return  none
 */
void wizchip_spi_cb_reg(void)
{
  reg_wizchip_cs_cbfunc(wizchip_select, wizchip_deselect);
  reg_wizchip_spi_cbfunc(wizchip_read_byte, wizchip_write_byte);
  reg_wizchip_spiburst_cbfunc(wizchip_read_buff, wizchip_write_buff);
}

/**
 * @brief   Hardware Platform Timer Interrupt Callback Function
 */
void wizchip_timer_callback(void)
{ // 1s 调用一次
  DHCP_time_handler();
}
