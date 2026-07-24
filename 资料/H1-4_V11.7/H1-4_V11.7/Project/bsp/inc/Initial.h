
#ifndef __INITIAL__
#define __INITIAL__

#include "project.h"
//--------------------------------------------------------------------------
#define ON 1
#define OFF 0
#define CH_NUM 12 //

#define PORT_UART 2
#define PORT_ETHER 3
#define PORT_USB 4

#define INVALID 0xff

#define VOA_NUM 5 //

//--------------------------------------------------------------------------
#define VERSION "PCBA:H1-4, PRG:V11.7"

//--------------------------------------------------------------------------
typedef struct
{
	uint16_t ch;
	uint16_t wl; // wave
	float min;	 //
	float max;	 //

} SturctTOF;

extern SturctTOF TOF;
//--------------------------------------------------------------------------
// typedef struct{
//	bool		flag;
//	uint16_t	ht;
//	uint16_t	lt;
//	uint16_t    cyc;
//}TimeSturct;

// extern TimeSturct  sTime[];
//-------------------------------------------------------------------------
extern uint8_t BoardIndex;
extern uint32_t IndexTimeDec;

//-------------------------------------------------------------------------
void SysTickConfigure(void);
void configWDT(uint16_t d);
void epramInitialize(void);
void bsp_Init(void);
double ffp(double fm, int leng);
char ftoa(double fv, unsigned char decimals, char *str);
char itoa(int tv, char *str);
char itoa_32(int tv, char *str);
void sformat(char *o, char *s, ...);
char ftoa_nr(double fv, unsigned char decimals, char *str);

#endif
