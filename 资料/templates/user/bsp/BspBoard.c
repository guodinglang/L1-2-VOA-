#include "BspConfig.h"

const GpioPortDesc_S GpioPortDescLib[BOARD_GPIO_NUM] =
    {
        {CRM_GPIOA_PERIPH_CLOCK, GPIOA, GPIO_PINS_7, "DUT_D1", GPIO_MODE_OUTPUT, GPIO_PULL_NONE, GPIO_OUTPUT_PUSH_PULL, GPIO_DRIVE_STRENGTH_MODERATE, TRUE},

        {CRM_GPIOB_PERIPH_CLOCK, GPIOB, GPIO_PINS_0, "DUT_D4", GPIO_MODE_OUTPUT, GPIO_PULL_NONE, GPIO_OUTPUT_PUSH_PULL, GPIO_DRIVE_STRENGTH_MODERATE, TRUE},
        {CRM_GPIOB_PERIPH_CLOCK, GPIOB, GPIO_PINS_1, "DUT_D3", GPIO_MODE_OUTPUT, GPIO_PULL_NONE, GPIO_OUTPUT_PUSH_PULL, GPIO_DRIVE_STRENGTH_MODERATE, TRUE},
        {CRM_GPIOB_PERIPH_CLOCK, GPIOB, GPIO_PINS_2, "DUT_D7", GPIO_MODE_OUTPUT, GPIO_PULL_NONE, GPIO_OUTPUT_PUSH_PULL, GPIO_DRIVE_STRENGTH_MODERATE, TRUE},
        {CRM_GPIOB_PERIPH_CLOCK, GPIOB, GPIO_PINS_6, "CH9434_CS", GPIO_MODE_OUTPUT, GPIO_PULL_NONE, GPIO_OUTPUT_PUSH_PULL, GPIO_DRIVE_STRENGTH_MODERATE, TRUE},
        {CRM_GPIOB_PERIPH_CLOCK, GPIOB, GPIO_PINS_7, "LED_STA", GPIO_MODE_OUTPUT, GPIO_PULL_NONE, GPIO_OUTPUT_OPEN_DRAIN, GPIO_DRIVE_STRENGTH_MODERATE, TRUE},
        {CRM_GPIOB_PERIPH_CLOCK, GPIOB, GPIO_PINS_8, "I2C_SCL", GPIO_MODE_OUTPUT, GPIO_PULL_NONE, GPIO_OUTPUT_PUSH_PULL, GPIO_DRIVE_STRENGTH_MODERATE, TRUE},
        {CRM_GPIOB_PERIPH_CLOCK, GPIOB, GPIO_PINS_9, "I2C_SDA", GPIO_MODE_OUTPUT, GPIO_PULL_NONE, GPIO_OUTPUT_PUSH_PULL, GPIO_DRIVE_STRENGTH_MODERATE, TRUE},
        {CRM_GPIOB_PERIPH_CLOCK, GPIOB, GPIO_PINS_12, "W5500_CS", GPIO_MODE_OUTPUT, GPIO_PULL_NONE, GPIO_OUTPUT_PUSH_PULL, GPIO_DRIVE_STRENGTH_MODERATE, TRUE},

        {CRM_GPIOC_PERIPH_CLOCK, GPIOC, GPIO_PINS_5, "DUT_D2", GPIO_MODE_OUTPUT, GPIO_PULL_NONE, GPIO_OUTPUT_PUSH_PULL, GPIO_DRIVE_STRENGTH_MODERATE, TRUE},
        {CRM_GPIOC_PERIPH_CLOCK, GPIOC, GPIO_PINS_9, "BUZZER", GPIO_MODE_OUTPUT, GPIO_PULL_NONE, GPIO_OUTPUT_PUSH_PULL, GPIO_DRIVE_STRENGTH_MODERATE, FALSE},
        {CRM_GPIOC_PERIPH_CLOCK, GPIOC, GPIO_PINS_12, "W5500_RST", GPIO_MODE_OUTPUT, GPIO_PULL_NONE, GPIO_OUTPUT_PUSH_PULL, GPIO_DRIVE_STRENGTH_MODERATE, TRUE},

        {CRM_GPIOD_PERIPH_CLOCK, GPIOD, GPIO_PINS_7, "CH9434_INT", GPIO_MODE_INPUT, GPIO_PULL_UP, GPIO_OUTPUT_PUSH_PULL, GPIO_DRIVE_STRENGTH_MODERATE, TRUE},
        {CRM_GPIOD_PERIPH_CLOCK, GPIOD, GPIO_PINS_8, "W5500_INT", GPIO_MODE_INPUT, GPIO_PULL_UP, GPIO_OUTPUT_PUSH_PULL, GPIO_DRIVE_STRENGTH_MODERATE, TRUE},
        {CRM_GPIOD_PERIPH_CLOCK, GPIOD, GPIO_PINS_9, "DUT_STROBE", GPIO_MODE_OUTPUT, GPIO_PULL_NONE, GPIO_OUTPUT_OPEN_DRAIN, GPIO_DRIVE_STRENGTH_MODERATE, TRUE},
        {CRM_GPIOD_PERIPH_CLOCK, GPIOD, GPIO_PINS_10, "DUT_NRST", GPIO_MODE_OUTPUT, GPIO_PULL_NONE, GPIO_OUTPUT_OPEN_DRAIN, GPIO_DRIVE_STRENGTH_MODERATE, TRUE},
        {CRM_GPIOD_PERIPH_CLOCK, GPIOD, GPIO_PINS_12, "SPK", GPIO_MODE_OUTPUT, GPIO_PULL_NONE, GPIO_OUTPUT_PUSH_PULL, GPIO_DRIVE_STRENGTH_MODERATE, FALSE},

        {CRM_GPIOE_PERIPH_CLOCK, GPIOE, GPIO_PINS_2, "USB_DET", GPIO_MODE_INPUT, GPIO_PULL_UP, GPIO_OUTPUT_PUSH_PULL, GPIO_DRIVE_STRENGTH_MODERATE, TRUE},
        {CRM_GPIOE_PERIPH_CLOCK, GPIOE, GPIO_PINS_3, "DUT_POW", GPIO_MODE_OUTPUT, GPIO_PULL_NONE, GPIO_OUTPUT_PUSH_PULL, GPIO_DRIVE_STRENGTH_MODERATE, TRUE},
        {CRM_GPIOE_PERIPH_CLOCK, GPIOE, GPIO_PINS_11, "DUT_D6", GPIO_MODE_OUTPUT, GPIO_PULL_NONE, GPIO_OUTPUT_PUSH_PULL, GPIO_DRIVE_STRENGTH_MODERATE, TRUE},
        {CRM_GPIOE_PERIPH_CLOCK, GPIOE, GPIO_PINS_12, "DUT_D5", GPIO_MODE_OUTPUT, GPIO_PULL_NONE, GPIO_OUTPUT_PUSH_PULL, GPIO_DRIVE_STRENGTH_MODERATE, TRUE},
        {CRM_GPIOE_PERIPH_CLOCK, GPIOE, GPIO_PINS_13, "DUT_D0", GPIO_MODE_OUTPUT, GPIO_PULL_NONE, GPIO_OUTPUT_PUSH_PULL, GPIO_DRIVE_STRENGTH_MODERATE, TRUE},
        {CRM_GPIOE_PERIPH_CLOCK, GPIOE, GPIO_PINS_14, "DUT_BUSY", GPIO_MODE_INPUT, GPIO_PULL_UP, GPIO_OUTPUT_PUSH_PULL, GPIO_DRIVE_STRENGTH_MODERATE, TRUE},
        {CRM_GPIOE_PERIPH_CLOCK, GPIOE, GPIO_PINS_15, "DUT_ALARM", GPIO_MODE_INPUT, GPIO_PULL_UP, GPIO_OUTPUT_PUSH_PULL, GPIO_DRIVE_STRENGTH_MODERATE, TRUE},
};

spi_init_type spi_init_struct_ch9434;
spi_init_type spi_init_struct_w5500;

crm_clocks_freq_type crm_clocks_freq_struct = {0};

static void BspBoard_Gpio_Init(void)
{
  uint8_t i;
  gpio_init_type gpio_init_struct;

  {
    crm_periph_clock_enable(CRM_GPIOA_PERIPH_CLOCK, TRUE);
    crm_periph_clock_enable(CRM_GPIOB_PERIPH_CLOCK, TRUE);
    crm_periph_clock_enable(CRM_GPIOC_PERIPH_CLOCK, TRUE);
    crm_periph_clock_enable(CRM_GPIOD_PERIPH_CLOCK, TRUE);
    crm_periph_clock_enable(CRM_GPIOE_PERIPH_CLOCK, TRUE);
    crm_periph_clock_enable(CRM_IOMUX_PERIPH_CLOCK, TRUE);

    gpio_pin_remap_config(SWJTAG_MUX_010, TRUE);
  }

  for (i = 0; i < BOARD_GPIO_NUM; i++)
  {
    gpio_default_para_init(&gpio_init_struct);

    if (GpioPortDescLib[i].gpio_mode == GPIO_MODE_OUTPUT)
    {
      gpio_bits_write(GpioPortDescLib[i].p_Port, GpioPortDescLib[i].usPins, GpioPortDescLib[i].RstState_Out);
    }

    gpio_init_struct.gpio_mode = GpioPortDescLib[i].gpio_mode;
    gpio_init_struct.gpio_pull = GpioPortDescLib[i].gpio_pull;
    gpio_init_struct.gpio_out_type = GpioPortDescLib[i].gpio_out_type;
    gpio_init_struct.gpio_drive_strength = GpioPortDescLib[i].gpio_drive_strength;
    gpio_init_struct.gpio_pins = GpioPortDescLib[i].usPins;

    gpio_init(GpioPortDescLib[i].p_Port, &gpio_init_struct);
  }
}

static void BspBoard_Timer_Init(void)
{
  /* get system clock */
  crm_clocks_freq_get(&crm_clocks_freq_struct);

  { // Tmr3 APB1(DIV2)
    crm_periph_clock_enable(CRM_TMR3_PERIPH_CLOCK, TRUE);

    tmr_counter_enable(TMR3, FALSE);
    tmr_base_init(TMR3, 1000 - 1, (uint16_t)((crm_clocks_freq_struct.apb1_freq * 2) / 1000000) - 1); // 1KHz
    tmr_cnt_dir_set(TMR3, TMR_COUNT_UP);

    tmr_interrupt_enable(TMR3, TMR_OVF_INT, TRUE);

    nvic_irq_enable(TMR3_GLOBAL_IRQn, 0, 0);

    tmr_counter_enable(TMR3, TRUE);
  }

  { // Tmr4 APB1(DIV2)
    crm_periph_clock_enable(CRM_TMR3_PERIPH_CLOCK, TRUE);

    tmr_counter_enable(TMR4, FALSE);
    tmr_base_init(TMR4, 10000 - 1, (uint16_t)((crm_clocks_freq_struct.apb1_freq * 2) / 10000) - 1); // 1Hz
    tmr_cnt_dir_set(TMR4, TMR_COUNT_UP);

    tmr_interrupt_enable(TMR4, TMR_OVF_INT, TRUE);

    nvic_irq_enable(TMR4_GLOBAL_IRQn, 0, 0);

    tmr_counter_enable(TMR4, TRUE);
  }
}

static void BspBoard_Uart_Init(void)
{
  gpio_init_type gpio_init_struct;

  { // UART1
    /* enable the usart1 and gpio clock */
    crm_periph_clock_enable(CRM_USART1_PERIPH_CLOCK, TRUE);

    gpio_default_para_init(&gpio_init_struct);

    /* configure the usart1 tx pin */
    gpio_init_struct.gpio_drive_strength = GPIO_DRIVE_STRENGTH_STRONGER;
    gpio_init_struct.gpio_out_type = GPIO_OUTPUT_PUSH_PULL;
    gpio_init_struct.gpio_mode = GPIO_MODE_MUX;
    gpio_init_struct.gpio_pins = GPIO_PINS_9;
    gpio_init_struct.gpio_pull = GPIO_PULL_NONE;
    gpio_init(GPIOA, &gpio_init_struct);

    /* configure the usart1 rx pin */
    gpio_init_struct.gpio_drive_strength = GPIO_DRIVE_STRENGTH_STRONGER;
    gpio_init_struct.gpio_out_type = GPIO_OUTPUT_PUSH_PULL;
    gpio_init_struct.gpio_mode = GPIO_MODE_INPUT;
    gpio_init_struct.gpio_pins = GPIO_PINS_10;
    gpio_init_struct.gpio_pull = GPIO_PULL_UP;
    gpio_init(GPIOA, &gpio_init_struct);

    /* configure usart1 param */
    usart_init(USART1, gUart1_Setting.baud_rate, gUart1_Setting.data_bit, gUart1_Setting.stop_bit);
    usart_parity_selection_config(USART1, gUart1_Setting.parity);
    usart_transmitter_enable(USART1, TRUE);
    usart_receiver_enable(USART1, TRUE);

    usart_enable(USART1, TRUE);

    /* config usart nvic interrupt */
    nvic_irq_enable(USART1_IRQn, 0, 0);
  }

  { // UART2
    /* enable the usart2 and gpio clock */
    crm_periph_clock_enable(CRM_USART2_PERIPH_CLOCK, TRUE);

    gpio_default_para_init(&gpio_init_struct);

    /* configure the usart2 tx pin */
    gpio_init_struct.gpio_drive_strength = GPIO_DRIVE_STRENGTH_STRONGER;
    gpio_init_struct.gpio_out_type = GPIO_OUTPUT_PUSH_PULL;
    gpio_init_struct.gpio_mode = GPIO_MODE_MUX;
    gpio_init_struct.gpio_pins = GPIO_PINS_2;
    gpio_init_struct.gpio_pull = GPIO_PULL_NONE;
    gpio_init(GPIOA, &gpio_init_struct);

    /* configure the usart2 rx pin */
    gpio_init_struct.gpio_drive_strength = GPIO_DRIVE_STRENGTH_STRONGER;
    gpio_init_struct.gpio_out_type = GPIO_OUTPUT_PUSH_PULL;
    gpio_init_struct.gpio_mode = GPIO_MODE_INPUT;
    gpio_init_struct.gpio_pins = GPIO_PINS_3;
    gpio_init_struct.gpio_pull = GPIO_PULL_UP;
    gpio_init(GPIOA, &gpio_init_struct);

    /* configure usart2 param */
    usart_init(USART2, gUart2_Setting.baud_rate, gUart2_Setting.data_bit, gUart2_Setting.stop_bit);
    usart_parity_selection_config(USART2, gUart2_Setting.parity);
    usart_transmitter_enable(USART2, TRUE);
    usart_receiver_enable(USART2, TRUE);

    usart_enable(USART2, TRUE);

    /* config usart nvic interrupt */
    nvic_irq_enable(USART2_IRQn, 0, 0);
  }

  { // UART3
    /* enable the usart3 and gpio clock */
    crm_periph_clock_enable(CRM_USART3_PERIPH_CLOCK, TRUE);

    gpio_default_para_init(&gpio_init_struct);

    /* configure the usart3 tx pin */
    gpio_init_struct.gpio_drive_strength = GPIO_DRIVE_STRENGTH_STRONGER;
    gpio_init_struct.gpio_out_type = GPIO_OUTPUT_PUSH_PULL;
    gpio_init_struct.gpio_mode = GPIO_MODE_MUX;
    gpio_init_struct.gpio_pins = GPIO_PINS_10;
    gpio_init_struct.gpio_pull = GPIO_PULL_NONE;
    gpio_init(GPIOB, &gpio_init_struct);

    /* configure the usart3 rx pin */
    gpio_init_struct.gpio_drive_strength = GPIO_DRIVE_STRENGTH_STRONGER;
    gpio_init_struct.gpio_out_type = GPIO_OUTPUT_PUSH_PULL;
    gpio_init_struct.gpio_mode = GPIO_MODE_INPUT;
    gpio_init_struct.gpio_pins = GPIO_PINS_11;
    gpio_init_struct.gpio_pull = GPIO_PULL_UP;
    gpio_init(GPIOB, &gpio_init_struct);

    /* configure usart3 param */
    usart_init(USART3, gUart3_Setting.baud_rate, gUart3_Setting.data_bit, gUart3_Setting.stop_bit);
    usart_parity_selection_config(USART3, gUart3_Setting.parity);
    usart_transmitter_enable(USART3, TRUE);
    usart_receiver_enable(USART3, TRUE);

    usart_enable(USART3, TRUE);

    /* config usart nvic interrupt */
    nvic_irq_enable(USART3_IRQn, 0, 0);
  }

  { // UART4
    /* enable the uart4 and gpio clock */
    crm_periph_clock_enable(CRM_UART4_PERIPH_CLOCK, TRUE);

    gpio_default_para_init(&gpio_init_struct);

    /* configure the uart4 tx pin */
    gpio_init_struct.gpio_drive_strength = GPIO_DRIVE_STRENGTH_STRONGER;
    gpio_init_struct.gpio_out_type = GPIO_OUTPUT_PUSH_PULL;
    gpio_init_struct.gpio_mode = GPIO_MODE_MUX;
    gpio_init_struct.gpio_pins = GPIO_PINS_10;
    gpio_init_struct.gpio_pull = GPIO_PULL_NONE;
    gpio_init(GPIOC, &gpio_init_struct);

    /* configure the uart4 rx pin */
    gpio_init_struct.gpio_drive_strength = GPIO_DRIVE_STRENGTH_STRONGER;
    gpio_init_struct.gpio_out_type = GPIO_OUTPUT_PUSH_PULL;
    gpio_init_struct.gpio_mode = GPIO_MODE_INPUT;
    gpio_init_struct.gpio_pins = GPIO_PINS_11;
    gpio_init_struct.gpio_pull = GPIO_PULL_UP;
    gpio_init(GPIOC, &gpio_init_struct);

    /* configure uart4 param */
    usart_init(UART4, gUart4_Setting.baud_rate, gUart4_Setting.data_bit, gUart4_Setting.stop_bit);
    usart_parity_selection_config(UART4, gUart4_Setting.parity);
    usart_transmitter_enable(UART4, TRUE);
    usart_receiver_enable(UART4, TRUE);

    usart_enable(UART4, TRUE);

    /* config usart nvic interrupt */
    nvic_irq_enable(UART4_IRQn, 0, 0);
  }
}

static void BspBoard_Spi_Init(void)
{
  { // CH9343 (PB3/PB4/PB5)
    gpio_init_type gpio_initstructure;

    crm_periph_clock_enable(CRM_SPI3_PERIPH_CLOCK, TRUE);

    gpio_default_para_init(&gpio_initstructure);
    /* spi3 sck pin */
    gpio_initstructure.gpio_out_type = GPIO_OUTPUT_PUSH_PULL;
    gpio_initstructure.gpio_drive_strength = GPIO_DRIVE_STRENGTH_STRONGER;
    gpio_initstructure.gpio_pull = GPIO_PULL_UP;
    gpio_initstructure.gpio_mode = GPIO_MODE_MUX;
    gpio_initstructure.gpio_pins = GPIO_PINS_3;
    gpio_init(GPIOB, &gpio_initstructure);

    /* spi3 miso pin */
    gpio_initstructure.gpio_pull = GPIO_PULL_NONE;
    gpio_initstructure.gpio_pins = GPIO_PINS_4;
    gpio_init(GPIOB, &gpio_initstructure);

    /* spi3 mosi pin */
    gpio_initstructure.gpio_pull = GPIO_PULL_NONE;
    gpio_initstructure.gpio_pins = GPIO_PINS_5;
    gpio_init(GPIOB, &gpio_initstructure);

    spi_default_para_init(&spi_init_struct_ch9434);
    spi_init_struct_ch9434.transmission_mode = SPI_TRANSMIT_FULL_DUPLEX;
    spi_init_struct_ch9434.master_slave_mode = SPI_MODE_MASTER;
    spi_init_struct_ch9434.mclk_freq_division = SPI_MCLK_DIV_8;
    spi_init_struct_ch9434.first_bit_transmission = SPI_FIRST_BIT_MSB;
    spi_init_struct_ch9434.frame_bit_num = SPI_FRAME_8BIT;
    spi_init_struct_ch9434.clock_polarity = SPI_CLOCK_POLARITY_LOW;
    spi_init_struct_ch9434.clock_phase = SPI_CLOCK_PHASE_1EDGE;
    spi_init_struct_ch9434.cs_mode_selection = SPI_CS_SOFTWARE_MODE;
    spi_init(SPI3, &spi_init_struct_ch9434);

    spi_i2s_dma_transmitter_enable(SPI3, FALSE);
    spi_i2s_dma_receiver_enable(SPI3, FALSE);

    spi_enable(SPI3, TRUE);
  }

  { // W5500 (PB13/PB14/PB15)
    gpio_init_type gpio_initstructure;

    crm_periph_clock_enable(CRM_SPI2_PERIPH_CLOCK, TRUE);

    gpio_default_para_init(&gpio_initstructure);
    /* spi2 sck pin */
    gpio_initstructure.gpio_out_type = GPIO_OUTPUT_PUSH_PULL;
    gpio_initstructure.gpio_drive_strength = GPIO_DRIVE_STRENGTH_STRONGER;
    gpio_initstructure.gpio_pull = GPIO_PULL_UP;
    gpio_initstructure.gpio_mode = GPIO_MODE_MUX;
    gpio_initstructure.gpio_pins = GPIO_PINS_13;
    gpio_init(GPIOB, &gpio_initstructure);

    /* spi2 miso pin */
    gpio_initstructure.gpio_pull = GPIO_PULL_NONE;
    gpio_initstructure.gpio_pins = GPIO_PINS_14;
    gpio_init(GPIOB, &gpio_initstructure);

    /* spi2 mosi pin */
    gpio_initstructure.gpio_pull = GPIO_PULL_NONE;
    gpio_initstructure.gpio_pins = GPIO_PINS_15;
    gpio_init(GPIOB, &gpio_initstructure);

    spi_default_para_init(&spi_init_struct_w5500);
    spi_init_struct_w5500.transmission_mode = SPI_TRANSMIT_FULL_DUPLEX;
    spi_init_struct_w5500.master_slave_mode = SPI_MODE_MASTER;
    spi_init_struct_w5500.mclk_freq_division = SPI_MCLK_DIV_16;
    spi_init_struct_w5500.first_bit_transmission = SPI_FIRST_BIT_MSB;
    spi_init_struct_w5500.frame_bit_num = SPI_FRAME_8BIT;
    spi_init_struct_w5500.clock_polarity = SPI_CLOCK_POLARITY_LOW;
    spi_init_struct_w5500.clock_phase = SPI_CLOCK_PHASE_1EDGE;
    spi_init_struct_w5500.cs_mode_selection = SPI_CS_SOFTWARE_MODE;
    spi_init(SPI2, &spi_init_struct_w5500);

    spi_i2s_dma_transmitter_enable(SPI2, FALSE);
    spi_i2s_dma_receiver_enable(SPI2, FALSE);

    spi_enable(SPI2, TRUE);
  }
}

void BspBoard_Init(void)
{
  nvic_priority_group_config(NVIC_PRIORITY_GROUP_4);

  BspEvent_Init();

  BspDwt_Init();
  BspBoard_Gpio_Init();
  BspBoard_Timer_Init();
  BspBoard_Uart_Init();
  BspBoard_Spi_Init();

  BspKey_Init();
  BspUart_Init();
  BspSoftiic_Init();
}
