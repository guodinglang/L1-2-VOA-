#ifndef __APPDWIN_H__
#define __APPDWIN_H__

#include "stdint.h"
#include "stdbool.h"

typedef enum
{
  AppDwin_Page_Main = 0, // 主页
  AppDwin_Page_Common,   // 通讯
  AppDwin_Page_Info,     // 信息
  AppDwin_Page_Alarm,    // 警告
  AppDwin_Page_Setting,  // 设置
  AppDwin_Page_Log = 7,  // 日志
} AppDwin_Page_E;

typedef struct
{
  uint8_t ucLanguage;
  AppDwin_Page_E CurrentPage;
  AppDwin_Page_E TargetPage;
  uint8_t ucFuncIdx; // 功能菜单索引(0,1,2)
} AppDwin_Control_S;

extern AppDwin_Control_S AppDwin_Control;

/*串口屏变量地址列表(文本控件(TW),数字控件(NW),进度条控件(PW),下拉框控件(DW))*/

typedef enum
{
  AppDwin_VP_TW_Logo_Loading = 0x7000,
} AppDwin_VP_E;

/*串口屏按键返回值列表*/

typedef enum
{
  AppDwin_KV_Main_F1 = 0x010F, // 功能1
} AppDwin_KV_E;

bool AppDwin_WriteString(uint16_t usAddr, const char *p_caString);
bool AppDwin_PrintString(uint16_t usAddr, const char *p_caString, ...);
bool AppDwin_Write2Bytes(uint16_t usAddr, uint16_t usValue);
bool AppDwin_Write4Bytes(uint16_t usAddr, uint32_t ulValue);
uint16_t AppDwin_PageRead(void);
bool AppDwin_PageSet(uint16_t usPageCode);
bool AppDwin_TouchEnable(uint16_t usPageCode, uint8_t ucWidgetId, uint8_t ucWidgetType, bool bNewState);
uint32_t AppDwin_WidgetMovePos(uint16_t usSpAddr, uint32_t ulNewPos);
bool AppDwin_PageOverlay(uint16_t usPageCode);
bool AppDwin_PageOverlay_Disable(void);

void AppDwin_Init(void);
void AppDwin_Proc(void);

#endif /*AppDwin.h*/
