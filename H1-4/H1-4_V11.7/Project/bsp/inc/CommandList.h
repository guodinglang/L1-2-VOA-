
#ifndef __COMMANDLIST_H__
#define __COMMANDLIST_H__

#include "SerialPort.h"

typedef struct
{
	const char *cmdStr;
	char (*func)(void *p, ...);
	const char *rChar;

} cmdStructure;

//*******************************************************************************************//
const cmdStructure cmdMessage[] = {
	{"help:", help,
	 "help:                       //all command\r\n"},
	{"rbc:", RebackCharacter,
	 "rbc: x                      //reback every character x(1-true;0-false)\r\n"},
	{"ver:", ReadVersion,
	 "ver:                        //firmware version\r\n"},
	{"srw:", SetReadWrite,
	 "srw: x x x                  //Set read write x(w/r) x(err/lock/scan/tgap/sch/ech/language/brUART/brUSB/brDUT/spk/logo/pdn) x(par)\r\n"},
	{"ethn:", EthernerParameter,
	 "ethn: x x x x               //etherner parameter x(w/r) x(mac/ip/sm/gw/rip/port) x(par)\r\n"},

	{"dut:", SetupDUT,
	 "dut: x x x                  //Setup DUT x(w) x(spp/pow) x(par)\r\n"},

	{"lcd:", SetupLCD,
	 "lcd: x x x                  //Setup LCD x(w/r) x(blk--0~100/title) x(par)\r\n"},
	{"key:", SendButtonValue,
	 "key: x                      //Send button value x(par)\r\n"},

	{"##:", SetBoardIndex,
	 "##: x x                     //set board index x(?/w) x(0/1/2/3/4/5/6)\r\n"},

};

//*******************************************************************************************//
// unsigned short int cmdStrLen=sizeof(cmdMessage)/sizeof(cmdStructure);
const int cmdStrLen = sizeof(cmdMessage) / sizeof(cmdStructure);

#endif
