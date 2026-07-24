#ifndef __APPPORT_H__
#define __APPPORT_H__

bool AppPort_Wdt_IsTrig(void);
void AppPort_Wdt_Start(void);
void AppPort_Wdt_Feed(void);

bool AppPort_AT24C08C_Write_Byte(uint16_t usAddr, uint8_t ucByte);
bool AppPort_AT24C08C_Read_Byte(uint16_t usAddr, uint8_t *p_ucByte);
bool AppPort_AT24C08C_Write_MutiByte(uint16_t usAddr, uint8_t *p_ucaBuff, uint16_t usSize);
bool AppPort_AT24C08C_Read_MutiByte(uint16_t usAddr, uint8_t *p_ucaBuff, uint16_t usSize);
bool AppPort_AT24C08C_Write_Buff(uint16_t usAddr, uint8_t *p_ucaBuff, uint16_t usSize);
bool AppPort_AT24C08C_Read_Buff(uint16_t usAddr, uint8_t *p_ucaBuff, uint16_t usSize);

void AppPort_MessageTrans(void);

double CalcFreqTHzFromWaveLen(double fWaveLen);
uint32_t CalcFreqMHzFromWaveLen(double fWaveLen);
double CalcWaveLenFromFreqMHz(uint32_t ulFreq);
double nmToTHz(double fnm);
double ThzTonm(double fthz);
double dBmToMW(double fdBm);
double mWToDBm(double fmW);

#endif /**/
