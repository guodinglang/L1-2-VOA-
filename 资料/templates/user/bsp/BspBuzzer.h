#ifndef __BSPBUZZER_H__
#define __BSPBUZZER_H__

#define BSPBUZZER_ON() (GPIOC->scr = GPIO_PINS_9)  /* Ê¹ÄÜ·äÃùÆ÷Ãù½Ð */
#define BSPBUZZER_OFF() (GPIOC->clr = GPIO_PINS_9) /* ½ûÖ¹·äÃùÆ÷Ãù½Ð */

typedef struct
{
  bool bState;
  bool bEnable;
  uint16_t usStart;
  uint16_t usStop;
  int8_t cCycle;
  uint16_t usTime;
} BspBuzzer_S;

void BspBuzzer_Start(uint16_t usBeepTime, uint16_t usStopTime, int8_t cCycle);
void BspBuzzer_Stop(void);
void BspBuzzer_Irq(void);
void BspBuzzer_Proc(void);

#endif /*BspBuzzer.h*/
