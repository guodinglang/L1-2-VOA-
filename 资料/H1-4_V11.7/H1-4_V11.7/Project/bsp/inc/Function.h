

#ifndef __FUNCTION_H_
#define __FUNCTION_H_

#include "project.h"

//--------------------------------------------------------------------------
#define SLED (GPIOB->odt ^= GPIO_PINS_7)

//--------------------------------------------------------------------------
typedef struct
{
	uint8_t step; //
				  //	uint16_t  rch;			//记录通道
				  //	uint8_t   cpn;			//PD器件总和
				  //	uint8_t   len;			//长度
	char buf[32]; // 数据保存
	//	uint16_t  max;			//最大通道
	//	uint8_t   iep[2];		//Input endpoint
	//	uint8_t   oep[2];		//output endpoint
	//	uint8_t   icr[32];	    //input channle record
	//	uint8_t   ocr[32];	    //output channle record
	uint32_t sv[3]; // setupt valuev
	//	uint16_t  toc;			//time out count
	//	char  	  buf[40];
	//	uint8_t   len2;
	uint8_t ben; // board enable
	//	uint8_t   msrc;			//MEMS switch record channle
	//	uint16_t  tlimit;		//time limit
	uint8_t cp[2];	 // 记录子板PD器件个数 component
	uint8_t nwl[2];	 // 记录各子板波长
	uint16_t mpn[2]; // 记录各子板点数

	uint16_t rwl[16]; // 定标波长
	double sul;		  // set uplimit VOA

} SwitchStruct;

extern SwitchStruct swMes;
//--------------------------------------------------------------------------
typedef struct
{
	uint8_t lock;	  // 通道锁
	uint8_t scan;	  // 通道切换
	uint32_t Tgap;	  // 扫描间隔
	uint16_t sch;	  // 起始通道
	uint16_t ech;	  // 结束通道
	uint8_t language; // 语言
	uint32_t brUART;  // UART波特率
	uint32_t brUSB;	  // UART波特率
	uint32_t brDUT;	  // DUT波特率
	uint8_t speak;	  // 蜂鸣器
	uint8_t step;	  //
	uint8_t reel;	  // 选项
	uint8_t page;	  // 菜单页
	uint8_t digit;	  //
	uint8_t index;	  //
	uint8_t refresh;  //
	uint8_t dport;	  // default port position
	uint8_t nport;	  // port number
	uint32_t bTime;	  // ##: select borad time
	uint8_t idCAN;	  // CAN id
					  //	uint8_t     sbn;		//suboard number

} SetupStruct;

extern SetupStruct setups;
//--------------------------------------------------------------------------
typedef enum
{
	HMI_Page_Main_EN = 0, // 主页(英文)
	HMI_Page_Search_EN,	  // 峰值搜索(英文)
	HMI_Page_KeyBoard,	  // 键盘
	HMI_Page_Execute_EN,  // 执行(英文)
	HMI_Page_Language,	  // 语言
	HMI_Page_Main_CN,	  // 主页(中文)
	HMI_Page_Search_CN,	  // 峰值搜索(中文)
	HMI_Page_Execute_CN,  // 执行(中文)
	HMI_Page_Bright,	  // 亮度
	HMI_Page_Offset,	  // 偏移
	HMI_Page_Curve,		  // 光谱图
	HMI_Page_Maint,		  // 维护信息
	HMI_Page_Info,		  // 系统信息
	HMI_Page_LAN,		  // 网络信息
	HMI_Page_OPEN,		  // 开屏
} HMI_Page_E;

typedef struct
{
	uint32_t ulwl_Start;  // 起始波长
	uint32_t ulwl_End;	  // 终止波长
	uint32_t ulwl_Center; // 中心波长
	uint32_t ulwl_Range;  // 波长范围

	int16_t sMaxdB; // Y轴 dB最大刻度
	int16_t sMindB; // Y轴 dB最小刻度

	uint16_t usGriddB; // dB栅格
	uint16_t usGridnm; // nm栅格

	uint16_t usResolution;	   // 分辨率
	uint16_t usSamplePointNum; // 采样点数
	uint16_t usSensitivity;	   // 灵敏度

	uint32_t ulwl_L; // 起始波长?
	uint32_t ulwl_C; // 中心波长?
	uint32_t ulwl_R; // 终止波长
} OpticalSpectrum_S;

typedef struct
{
	char buf[128]; // data buffer
	uint8_t len;   // buffer len
	uint8_t count; //
	uint8_t page;  // 显示界面页

	uint32_t swl;				 // 起始波长
	uint32_t ewl;				 // 结束波长
	uint32_t iwl;				 // 间隔波长
	uint16_t itim;				 // 间隔时间 interval time
	uint8_t scan;				 // 扫描方式
	uint16_t to;				 // time out
	int32_t lCenterWavLenOffset; // 中心波长偏移
	char sn[17];				 // 序列号
	char ver[24];				 // 版本
	char rwl[24];				 // 波长范围
	char bb[24];				 // boardband 宽带
	char temp[8];				 // 温度
	uint8_t language;			 // 语言

	OpticalSpectrum_S OpticalSpectrum;

	HMI_Page_E CurrentPage;
} hmiSturct;

extern hmiSturct hmi;
//--------------------------------------------------------------------------
void WorkStateLED(void);
void SwitchMessage(void);
void ParameterSetup(void);
uint32_t SelectBaudrate(uint32_t br, int s);
uint32_t IndexToBaudrate(uint8_t br);
uint8_t BaudrateToIndex(uint32_t br);
void BlinkBit(uint32_t *v, char *str, uint8_t num, uint8_t loc, uint8_t *bl, int8_t as);
void MainInterfaceLCD(void);
void DisplayUARTHMI(void);
void UpdateUARTHMI(void);

#endif
