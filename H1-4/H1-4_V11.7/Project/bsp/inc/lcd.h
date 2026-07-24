

#ifndef __LCD_H__
#define __LCD_H__

#include "project.h"

/* the address of write data & command (xmc_a0) */
#define XMC_LCD_COMMAND 0x6c000000
#define XMC_LCD_DATA 0x6c000001

/** @defgroup XMC_lcd_8bit_reset_line
 * @{
 */

/* the lcd reset line */
#define LCD_RESET_HIGH gpio_bits_set(GPIOA, GPIO_PINS_5)
#define LCD_RESET_LOW gpio_bits_reset(GPIOA, GPIO_PINS_5)

#define USE_HORIZONTAL 2 // 设置横屏或者竖屏显示 0或1为竖屏 2或3为横屏

#if USE_HORIZONTAL == 0 || USE_HORIZONTAL == 1
#define LCD_W 240
#define LCD_H 320

#else
#define LCD_W 320
#define LCD_H 240
#endif

// 画笔颜色
#define WHITE 0xFFFF
#define BLACK 0x0000
#define BLUE 0x001F
#define BRED 0XF81F
#define GRED 0XFFE0
#define GBLUE 0X07FF
#define RED 0xF800
#define MAGENTA 0xF81F
#define GREEN 0x07E0
#define CYAN 0x7FFF
#define YELLOW 0xFFE0
#define BROWN 0XBC40	  // 棕色
#define BRRED 0XFC07	  // 棕红色
#define GRAY 0X8430		  // 灰色
#define DARKBLUE 0X01CF	  // 深蓝色
#define LIGHTBLUE 0X7D7C  // 浅蓝色
#define GRAYBLUE 0X5458	  // 灰蓝色
#define LIGHTGREEN 0X841F // 浅绿色
#define LGRAY 0XC618	  // 浅灰色(PANNEL),窗体背景色
#define LGRAYBLUE 0XA651  // 浅灰蓝色(中间层颜色)
#define LBBLUE 0X2B12	  // 浅棕蓝色(选择条目的反色)

#define GRAY0 0xEF7D // 灰色0 3165 00110 001011 00101
#define GRAY1 0x8410 // 灰色1      00000 000000 00000
#define GRAY2 0x4208 // 灰色2  	 11111 111110 11111
#define GRAY3 0xad55 // 深灰色

#define GREEN0 0x471a // 绿宝石
#define ORANGE 0xfd20 // 橙色
#define KHAKI 0xf731  // 卡其布
#define LEMON 0xffd9  // 柠檬薄纱

#define BLK_MIN 155				 // 310	//620	//1240			//最小值
#define BLK_SRV (4095 - BLK_MIN) // 背光亮度设置范围值

//-------------------------------------------------------------------------------
#define ASC_8X16 16
#define ASC_12X24 24
#define ASC_16X32 32

//-------------------------------------------------------------------------------
typedef struct
{
	uint8_t title[17]; // 标题
	uint8_t blink;
	uint8_t logo;
	uint8_t page; // 主界面显示通道
	uint16_t blk; // back light
	uint16_t time;

} lcdStruct;

extern lcdStruct *pLCD;

extern const unsigned char gImage_logo[];

//-------------------------------------------------------------------------------
void lcd_io_config(void);
void lcd_init(void);
void LCD_WR_REG(u8 dat);
void LCD_WR_bDATA(u8 dat);
void LCD_Fill(u16 xsta, u16 ysta, u16 xend, u16 yend, u16 color);  // 指定区域填充颜色
void LCD_DrawPoint(u16 x, u16 y, u16 color);					   // 在指定位置画一个点
void LCD_DrawLine(u16 x1, u16 y1, u16 x2, u16 y2, u16 color);	   // 在指定位置画一条线
void LCD_DrawRectangle(u16 x1, u16 y1, u16 x2, u16 y2, u16 color); // 在指定位置画一个矩形
void Draw_Circle(u16 x0, u16 y0, u8 r, u16 color);				   // 在指定位置画一个圆

void LCD_ShowChinese(u16 x, u16 y, u8 *s, u16 fc, u16 bc, u8 sizey, u8 mode);	   // 显示汉字串
void LCD_ShowChinese16x16(u16 x, u16 y, u8 *s, u16 fc, u16 bc, u8 sizey, u8 mode); // 显示单个16x16汉字
void LCD_ShowChinese24x24(u16 x, u16 y, u8 *s, u16 fc, u16 bc, u8 sizey, u8 mode); // 显示单个24x24汉字
void LCD_ShowChinese32x32(u16 x, u16 y, u8 *s, u16 fc, u16 bc, u8 sizey, u8 mode); // 显示单个32x32汉字

void LCD_ShowChar(u16 x, u16 y, u8 num, u16 fc, u16 bc, u8 sizey, u8 mode);		   // 显示一个字符
void LCD_ShowString(u16 x, u16 y, const u8 *p, u16 fc, u16 bc, u8 sizey, u8 mode); // 显示字符串
u32 mypow(u8 m, u8 n);															   // 求幂
void LCD_ShowIntNum(u16 x, u16 y, u16 num, u8 len, u16 fc, u16 bc, u8 sizey);	   // 显示整数变量
void LCD_ShowFloatNum1(u16 x, u16 y, float num, u8 len, u16 fc, u16 bc, u8 sizey); // 显示两位小数变量

void LCD_ShowPicture(u16 x, u16 y, u16 length, u16 width, const u8 pic[]); // 显示图片

void LCD_ShowASCII(u16 x, u16 y, u8 *s, u16 fc, u16 bc, u8 size, u8 mode);

#endif
