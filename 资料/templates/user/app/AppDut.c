#include "includes.h"

void AppDut_Init(void)
{
  APPDUT_POWER(1);
}

void AppDut_ChannelSelect(uint16_t usChannel)
{
  char caPrintfBuff[32] = {0};
  BspUart_Printf(BspUartCom_DUT, caPrintfBuff, sizeof(caPrintfBuff), "*SW%03u", usChannel);
}
