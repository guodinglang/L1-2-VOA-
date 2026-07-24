#ifndef __APPDUT_H__
#define __APPDUT_H__

#define APPDUT_POWER(n) (n) > 0 ? (GPIOE->scr = GPIO_PINS_3) : (GPIOE->clr = GPIO_PINS_3)

#define APPDUT_D0(n) (n) > 0 ? (GPIOE->scr = GPIO_PINS_13) : (GPIOE->clr = GPIO_PINS_13)
#define APPDUT_D1(n) (n) > 0 ? (GPIOA->scr = GPIO_PINS_7) : (GPIOA->clr = GPIO_PINS_7)
#define APPDUT_D2(n) (n) > 0 ? (GPIOC->scr = GPIO_PINS_5) : (GPIOC->clr = GPIO_PINS_5)
#define APPDUT_D3(n) (n) > 0 ? (GPIOB->scr = GPIO_PINS_1) : (GPIOB->clr = GPIO_PINS_1)
#define APPDUT_D4(n) (n) > 0 ? (GPIOB->scr = GPIO_PINS_0) : (GPIOB->clr = GPIO_PINS_0)
#define APPDUT_D5(n) (n) > 0 ? (GPIOE->scr = GPIO_PINS_12) : (GPIOE->clr = GPIO_PINS_12)
#define APPDUT_D6(n) (n) > 0 ? (GPIOE->scr = GPIO_PINS_11) : (GPIOE->clr = GPIO_PINS_11)
#define APPDUT_D7(n) (n) > 0 ? (GPIOB->scr = GPIO_PINS_2) : (GPIOB->clr = GPIO_PINS_2)
#define APPDUT_RESET(n) (n) > 0 ? (GPIOD->scr = GPIO_PINS_10) : (GPIOD->clr = GPIO_PINS_10)
#define APPDUT_STROBE(n) (n) > 0 ? (GPIOD->scr = GPIO_PINS_9) : (GPIOD->clr = GPIO_PINS_9)

#define APPDUT_BUSY (GPIO_PINS_14 & GPIOE->idt)
#define APPDUT_ALARM (GPIO_PINS_15 & GPIOE->idt)

void AppDut_Init(void);
void AppDut_ChannelSelect(uint16_t usChannel);

#endif /**/
