

#ifndef   __INSIDE_CAN__H__
#define   __INSIDE_CAN__H__



#include "project.h"

//========================================================================
#define CAN_IDE_IDT			0x0004
#define CAN_RTR_DATA		0x0000





//========================================================================
extern uint8_t    target_id;
extern uint32_t   can_res;





//========================================================================
void can_config(void);
uint8_t txCAN1(uint8_t *sd,uint16_t num);
void ResetCAN1(void);






#endif




