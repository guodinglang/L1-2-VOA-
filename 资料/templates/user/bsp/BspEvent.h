#ifndef __BSPEVENT_H__
#define __BSPEVENT_H__

#define	config_EVENT_NUM	 8//8µÄÕûÊý±¶

bool BspEvent_Clr(uint8_t EventCode);
bool BspEvent_Set(uint8_t EventCode);
bool BspEvent_Check(uint8_t EventCode);
void BspEvent_Init(void);

#endif /*BspEvent.h*/
