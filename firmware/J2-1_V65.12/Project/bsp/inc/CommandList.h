
#ifndef  __COMMANDLIST_H__
#define  __COMMANDLIST_H__

#include "SerialPort.h"

typedef struct 
{
	const char     *cmdStr;
          char     (*func)(void *p,...);	
	const char     *rChar;	
	
}cmdStructure;

//*******************************************************************************************//
const cmdStructure cmdMessage[] = {
{"help",help,
 "<help>                     //all command\r\n"
},	
{"rbc",RebackCharacter,
 "<RBC x>                    //reback every character x(1-true;0-false)\r\n"
},
{"ver",ReadVersion,
 "<VER x>                    //firmware version x(?/w)\r\n"
},
{"reset",SystemReset,
 "<RESET>                    //System Reset\r\n"
},
{"restore",FactoryReset,
 "<RESTORE>                  //Factory Reset\r\n"
},
{"voa",ReadSelectSwitch,
 "<VOA_x_x_x>                //OSW x(CH) x(W/ATT/A) x(par)\r\n"
},
{"info",ReadWriteBoardIDN,
 "<INFO_x_x>                 //Info x(?/w) x(par)\r\n"
},
//{"baud",BaudrateUART,
// "<BAUD_x>                   //UART Baudrate x(?/1~9)\r\n"
//},
{"save",SaveSelectSwitch,
 "<SAVE_x>                   //save select switch x(ALL)\r\n"
},
{"max",ReadWriteMaxCH,
 "<Max x x>                  //set max channel x(?/W)\r\n"
},
{"lvd",LevelValueDispose,
 "<LVD x x x x x>            //Set group voltage x(w/r) x(CH) x(X+) x(X-) x(Y+) x(Y-) x(Nx/Mx)\r\n"
},
{"ofs",OffsetChannel,
 "ofs x x x                  //offset channel voltage x(od-dac out/wk--coff/wl--level/rk/rl/cb--calculation k) x(index) x(par)\r\n"
},
{"srw",SetReadWrite,
 "<SRW x x x x>              //Set read write x(W/R) x[res/ls/ver/info/id/baud/max/fmdp/wl/dacp/svo/ss/cs/cf/temp]\r\n"
},



};



//*******************************************************************************************//
//unsigned short int cmdStrLen=sizeof(cmdMessage)/sizeof(cmdStructure);
const int cmdStrLen=sizeof(cmdMessage)/sizeof(cmdStructure);



#endif

