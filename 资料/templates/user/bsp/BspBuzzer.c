#include "BspConfig.h"

BspBuzzer_S Buzzer;

void BspBuzzer_Start(uint16_t usBeepTime, uint16_t usStopTime, int8_t cCycle)
{
  if (usBeepTime > 0)
  {
    Buzzer.bState = false;
    Buzzer.bEnable = true;
    Buzzer.usStart = usBeepTime;
    Buzzer.usStop = usStopTime;
    Buzzer.cCycle = cCycle;
    Buzzer.usTime = usBeepTime;
    BSPBUZZER_ON(); /* 开始发声 */
  }
}

void BspBuzzer_Stop(void)
{
  Buzzer.bState = false;
  Buzzer.bEnable = false;
  Buzzer.usStart = 0;
  Buzzer.usStop = 0;
  Buzzer.cCycle = 0;
  Buzzer.usTime = 0;
  BSPBUZZER_OFF(); /* 必须在清控制标志后再停止发声，避免停止后在中断中又开启 */
}

void BspBuzzer_Irq(void)
{
  if (Buzzer.usTime)
    Buzzer.usTime -= 1;
}

void BspBuzzer_Proc(void)
{
  if (Buzzer.bEnable == true)
  {
    if (Buzzer.usTime <= 0)
    {
      if (Buzzer.bState != true)
      {
        if (Buzzer.cCycle > 0)
        {
          Buzzer.cCycle--;
          if (Buzzer.cCycle <= 0)
          {
            BspBuzzer_Stop();
          }
          else if (Buzzer.usStop > 0)
          {
            Buzzer.bState = true;
            Buzzer.usTime = Buzzer.usStop;
            BSPBUZZER_OFF(); /* 停止发声 */
          }
        }
        else if (Buzzer.cCycle == -1) // 表示持续鸣叫
        {
          if (Buzzer.usStop > 0)
          {
            Buzzer.bState = true;
            Buzzer.usTime = Buzzer.usStop;
            BSPBUZZER_OFF(); /* 停止发声 */
          }
        }
      }
      else
      {
        Buzzer.bState = false;
        if (Buzzer.usStart > 0)
        {
          Buzzer.usTime = Buzzer.usStart;
          BSPBUZZER_ON(); /* 开始发声 */
        }
        else
        {
          BspBuzzer_Stop();
        }
      }
    }
  }
}
