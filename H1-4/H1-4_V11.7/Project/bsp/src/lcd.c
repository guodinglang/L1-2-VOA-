
#include "lcd.h"
#include "lcdfont.h"
// #include "PictureGUI.h"

//--------------------------------------------------------------------------------

lcdStruct lcdMes, *pLCD = &lcdMes;

/***************************************************************************
;** 函数名称: 	xmc_init
;** 功能描述:   configures the xmc and gpios to interface with the lcd.
				this function must be called before any write/read operation on the lcd.
;** 输入参数:
;** 返 回 值:
;** 全局变量:
;** 调用模块:
;** 作　  者:   M-L-A
;** 日　  期:  2022-9-23
;** 修改原因:
;** 说    明:
;***************************************************************************/
void lcd_io_config(void)
{
	gpio_init_type gpio_init_struct = {0};
	xmc_norsram_init_type xmc_norsram_init_struct;
	xmc_norsram_timing_init_type rw_timing_struct, w_timing_struct;

	/* enable the gpio clock */
	crm_periph_clock_enable(CRM_GPIOA_PERIPH_CLOCK, TRUE);
	crm_periph_clock_enable(CRM_GPIOB_PERIPH_CLOCK, TRUE);
	crm_periph_clock_enable(CRM_GPIOC_PERIPH_CLOCK, TRUE);
	crm_periph_clock_enable(CRM_GPIOD_PERIPH_CLOCK, TRUE);
	crm_periph_clock_enable(CRM_IOMUX_PERIPH_CLOCK, TRUE);
	/* enable the xmc clock */
	crm_periph_clock_enable(CRM_XMC_PERIPH_CLOCK, TRUE);

	/* remap */
	//	gpio_pin_remap_config(XMC_GMUX_001, TRUE);

	/*-- gpio configuration ------------------------------------------------------*/
	/* lcd data lines configuration */
	gpio_init_struct.gpio_pins = GPIO_PINS_0 | GPIO_PINS_1 | GPIO_PINS_14 | GPIO_PINS_15;
	gpio_init_struct.gpio_mode = GPIO_MODE_MUX;
	gpio_init_struct.gpio_out_type = GPIO_OUTPUT_PUSH_PULL;
	gpio_init_struct.gpio_pull = GPIO_PULL_NONE;
	gpio_init_struct.gpio_drive_strength = GPIO_DRIVE_STRENGTH_STRONGER;
	gpio_init(GPIOD, &gpio_init_struct);

	gpio_init_struct.gpio_pins = GPIO_PINS_7 | GPIO_PINS_8 | GPIO_PINS_9 | GPIO_PINS_10;
	gpio_init_struct.gpio_mode = GPIO_MODE_MUX;
	gpio_init_struct.gpio_out_type = GPIO_OUTPUT_PUSH_PULL;
	gpio_init_struct.gpio_pull = GPIO_PULL_NONE;
	gpio_init_struct.gpio_drive_strength = GPIO_DRIVE_STRENGTH_STRONGER;
	gpio_init(GPIOE, &gpio_init_struct);

	//	gpio_init_struct.gpio_pins = GPIO_PINS_3;
	//	gpio_init_struct.gpio_mode = GPIO_MODE_MUX;
	//	gpio_init_struct.gpio_out_type = GPIO_OUTPUT_PUSH_PULL;
	//	gpio_init_struct.gpio_pull = GPIO_PULL_NONE;
	//	gpio_init_struct.gpio_drive_strength = GPIO_DRIVE_STRENGTH_STRONGER;
	//	gpio_init(GPIOC, &gpio_init_struct);

	/* lcd rs/cs/wr/rd lines configuration */
	gpio_init_struct.gpio_pins = GPIO_PINS_3 | GPIO_PINS_4;
	gpio_init_struct.gpio_mode = GPIO_MODE_MUX;
	gpio_init_struct.gpio_out_type = GPIO_OUTPUT_PUSH_PULL;
	gpio_init_struct.gpio_pull = GPIO_PULL_NONE;
	gpio_init_struct.gpio_drive_strength = GPIO_DRIVE_STRENGTH_STRONGER;
	gpio_init(GPIOC, &gpio_init_struct);

	gpio_init_struct.gpio_pins = GPIO_PINS_4 | GPIO_PINS_5;
	gpio_init_struct.gpio_mode = GPIO_MODE_MUX;
	gpio_init_struct.gpio_out_type = GPIO_OUTPUT_PUSH_PULL;
	gpio_init_struct.gpio_pull = GPIO_PULL_NONE;
	gpio_init_struct.gpio_drive_strength = GPIO_DRIVE_STRENGTH_STRONGER;
	gpio_init(GPIOD, &gpio_init_struct);

	/* lcd reset lines configuration */
	gpio_init_struct.gpio_pins = GPIO_PINS_5;
	gpio_init_struct.gpio_mode = GPIO_MODE_OUTPUT;
	gpio_init_struct.gpio_out_type = GPIO_OUTPUT_PUSH_PULL;
	gpio_init_struct.gpio_pull = GPIO_PULL_NONE;
	gpio_init_struct.gpio_drive_strength = GPIO_DRIVE_STRENGTH_STRONGER;
	gpio_init(GPIOA, &gpio_init_struct);

	/* lcd TE lines configuration */
	gpio_init_struct.gpio_pins = GPIO_PINS_6;
	gpio_init_struct.gpio_mode = GPIO_MODE_INPUT;
	gpio_init_struct.gpio_out_type = GPIO_OUTPUT_PUSH_PULL;
	gpio_init_struct.gpio_pull = GPIO_PULL_NONE;
	gpio_init_struct.gpio_drive_strength = GPIO_DRIVE_STRENGTH_STRONGER;
	gpio_init(GPIOA, &gpio_init_struct);

	/*-- xmc configuration ------------------------------------------------------*/
	xmc_norsram_default_para_init(&xmc_norsram_init_struct);
	xmc_norsram_init_struct.subbank = XMC_BANK1_NOR_SRAM4;
	xmc_norsram_init_struct.data_addr_multiplex = XMC_DATA_ADDR_MUX_DISABLE;
	xmc_norsram_init_struct.device = XMC_DEVICE_SRAM;
	xmc_norsram_init_struct.bus_type = XMC_BUSTYPE_8_BITS;
	xmc_norsram_init_struct.burst_mode_enable = XMC_BURST_MODE_DISABLE;
	xmc_norsram_init_struct.asynwait_enable = XMC_ASYN_WAIT_DISABLE;
	xmc_norsram_init_struct.wait_signal_lv = XMC_WAIT_SIGNAL_LEVEL_LOW;
	xmc_norsram_init_struct.wrapped_mode_enable = XMC_WRAPPED_MODE_DISABLE;
	xmc_norsram_init_struct.wait_signal_config = XMC_WAIT_SIGNAL_SYN_BEFORE;
	xmc_norsram_init_struct.write_enable = XMC_WRITE_OPERATION_ENABLE;
	xmc_norsram_init_struct.wait_signal_enable = XMC_WAIT_SIGNAL_DISABLE;
	xmc_norsram_init_struct.write_timing_enable = XMC_WRITE_TIMING_ENABLE;
	xmc_norsram_init_struct.write_burst_syn = XMC_WRITE_BURST_SYN_DISABLE;
	xmc_nor_sram_init(&xmc_norsram_init_struct);

	/* timing configuration */
	xmc_norsram_timing_default_para_init(&rw_timing_struct, &w_timing_struct);
	rw_timing_struct.subbank = XMC_BANK1_NOR_SRAM4;
	rw_timing_struct.write_timing_enable = XMC_WRITE_TIMING_ENABLE;
	rw_timing_struct.addr_setup_time = 0x0f;
	rw_timing_struct.addr_hold_time = 0x00;
	rw_timing_struct.data_setup_time = 0xf;
	rw_timing_struct.bus_latency_time = 0x0;
	rw_timing_struct.clk_psc = 0x0;
	rw_timing_struct.data_latency_time = 0x0;
	rw_timing_struct.mode = XMC_ACCESS_MODE_A;
	w_timing_struct.subbank = XMC_BANK1_NOR_SRAM4;
	w_timing_struct.write_timing_enable = XMC_WRITE_TIMING_ENABLE;
	w_timing_struct.addr_setup_time = 0x0f;
	w_timing_struct.addr_hold_time = 0x00;
	w_timing_struct.data_setup_time = 0xf;
	w_timing_struct.bus_latency_time = 0x0;
	w_timing_struct.clk_psc = 0x0;
	w_timing_struct.data_latency_time = 0x0;
	w_timing_struct.mode = XMC_ACCESS_MODE_A;
	xmc_nor_sram_timing_config(&rw_timing_struct, &w_timing_struct);

	/* bus turnaround phase for consecutive read duration and consecutive write duration */
	xmc_ext_timing_config(XMC_BANK1_NOR_SRAM4, 0x08, 0x08);

	/* enable xmc_bank1_nor_sram4 */
	xmc_nor_sram_enable(XMC_BANK1_NOR_SRAM4, TRUE);
}

/******************************************************************************
	  函数说明：LCD写入数据
	  入口数据：dat 写入的数据
	  返回值：  无
******************************************************************************/
void LCD_WR_bDATA(u8 dat)
{
	*(__IO uint8_t *)XMC_LCD_DATA = dat;
}

/******************************************************************************
	  函数说明：LCD写入数据
	  入口数据：dat 写入的数据
	  返回值：  无
******************************************************************************/
void LCD_WR_wDATA(u16 dat)
{
	*(__IO uint8_t *)XMC_LCD_DATA = dat >> 8;
	*(__IO uint8_t *)XMC_LCD_DATA = dat;
}

/******************************************************************************
	  函数说明：LCD写入命令
	  入口数据：dat 写入的命令
	  返回值：  无
******************************************************************************/
void LCD_WR_REG(u8 dat)
{
	*(__IO uint8_t *)XMC_LCD_COMMAND = dat;
}

/******************************************************************************
	  函数说明：设置起始和结束地址
	  入口数据：x1,x2 设置列的起始和结束地址
				y1,y2 设置行的起始和结束地址
	  返回值：  无
******************************************************************************/
void LCD_Address_Set(u16 x1, u16 y1, u16 x2, u16 y2)
{
	if (USE_HORIZONTAL == 0)
	{
		LCD_WR_REG(0x2a); // 列地址设置
		LCD_WR_wDATA(x1);
		LCD_WR_wDATA(x2);
		LCD_WR_REG(0x2b); // 行地址设置
		LCD_WR_wDATA(y1);
		LCD_WR_wDATA(y2);
		LCD_WR_REG(0x2c); // 储存器写
	}
	else if (USE_HORIZONTAL == 1)
	{
		LCD_WR_REG(0x2a); // 列地址设置
		LCD_WR_wDATA(x1);
		LCD_WR_wDATA(x2);
		LCD_WR_REG(0x2b); // 行地址设置
		LCD_WR_wDATA(y1);
		LCD_WR_wDATA(y2);
		LCD_WR_REG(0x2c); // 储存器写
	}
	else if (USE_HORIZONTAL == 2)
	{
		LCD_WR_REG(0x2a); // 列地址设置
		LCD_WR_wDATA(x1);
		LCD_WR_wDATA(x2);
		LCD_WR_REG(0x2b); // 行地址设置
		LCD_WR_wDATA(y1);
		LCD_WR_wDATA(y2);
		LCD_WR_REG(0x2c); // 储存器写
	}
	else
	{
		LCD_WR_REG(0x2a); // 列地址设置
		LCD_WR_wDATA(x1);
		LCD_WR_wDATA(x2);
		LCD_WR_REG(0x2b); // 行地址设置
		LCD_WR_wDATA(y1);
		LCD_WR_wDATA(y2);
		LCD_WR_REG(0x2c); // 储存器写
	}
}

/******************************************************************************
	  函数说明：在指定区域填充颜色
	  入口数据：xsta,ysta   起始坐标
				xend,yend   终止坐标
								color       要填充的颜色
	  返回值：  无
******************************************************************************/
void LCD_Fill(u16 xsta, u16 ysta, u16 xend, u16 yend, u16 color)
{
	u16 i, j;
	LCD_Address_Set(xsta, ysta, xend - 1, yend - 1); // 设置显示范围
	for (i = ysta; i < yend; i++)
	{
		for (j = xsta; j < xend; j++)
		{
			LCD_WR_wDATA(color);
		}
	}
}

/******************************************************************************
	  函数说明：在指定位置画点
	  入口数据：x,y 画点坐标
				color 点的颜色
	  返回值：  无
******************************************************************************/
void LCD_DrawPoint(u16 x, u16 y, u16 color)
{
	LCD_Address_Set(x, y, x, y); // 设置光标位置
	LCD_WR_wDATA(color);
}

/******************************************************************************
	  函数说明：画线
	  入口数据：x1,y1   起始坐标
				x2,y2   终止坐标
				color   线的颜色
	  返回值：  无
******************************************************************************/
void LCD_DrawLine(u16 x1, u16 y1, u16 x2, u16 y2, u16 color)
{
	u16 t;
	int xerr = 0, yerr = 0, delta_x, delta_y, distance;
	int incx, incy, uRow, uCol;
	delta_x = x2 - x1; // 计算坐标增量
	delta_y = y2 - y1;
	uRow = x1; // 画线起点坐标
	uCol = y1;
	if (delta_x > 0)
		incx = 1; // 设置单步方向
	else if (delta_x == 0)
		incx = 0; // 垂直线
	else
	{
		incx = -1;
		delta_x = -delta_x;
	}
	if (delta_y > 0)
		incy = 1;
	else if (delta_y == 0)
		incy = 0; // 水平线
	else
	{
		incy = -1;
		delta_y = -delta_x;
	}
	if (delta_x > delta_y)
		distance = delta_x; // 选取基本增量坐标轴
	else
		distance = delta_y;
	for (t = 0; t < distance + 1; t++)
	{
		LCD_DrawPoint(uRow, uCol, color); // 画点
		xerr += delta_x;
		yerr += delta_y;
		if (xerr > distance)
		{
			xerr -= distance;
			uRow += incx;
		}
		if (yerr > distance)
		{
			yerr -= distance;
			uCol += incy;
		}
	}
}

/******************************************************************************
	  函数说明：画矩形
	  入口数据：x1,y1   起始坐标
				x2,y2   终止坐标
				color   矩形的颜色
	  返回值：  无
******************************************************************************/
void LCD_DrawRectangle(u16 x1, u16 y1, u16 x2, u16 y2, u16 color)
{
	LCD_DrawLine(x1, y1, x2, y1, color);
	LCD_DrawLine(x1, y1, x1, y2, color);
	LCD_DrawLine(x1, y2, x2, y2, color);
	LCD_DrawLine(x2, y1, x2, y2, color);
}

/******************************************************************************
	  函数说明：画圆
	  入口数据：x0,y0   圆心坐标
				r       半径
				color   圆的颜色
	  返回值：  无
******************************************************************************/
void Draw_Circle(u16 x0, u16 y0, u8 r, u16 color)
{
	int a, b;
	a = 0;
	b = r;
	while (a <= b)
	{
		LCD_DrawPoint(x0 - b, y0 - a, color); // 3
		LCD_DrawPoint(x0 + b, y0 - a, color); // 0
		LCD_DrawPoint(x0 - a, y0 + b, color); // 1
		LCD_DrawPoint(x0 - a, y0 - b, color); // 2
		LCD_DrawPoint(x0 + b, y0 + a, color); // 4
		LCD_DrawPoint(x0 + a, y0 - b, color); // 5
		LCD_DrawPoint(x0 + a, y0 + b, color); // 6
		LCD_DrawPoint(x0 - b, y0 + a, color); // 7
		a++;
		if ((a * a + b * b) > (r * r)) // 判断要画的点是否过远
		{
			b--;
		}
	}
}

/******************************************************************************
	  函数说明：显示汉字串
	  入口数据：x,y显示坐标
				*s 要显示的汉字串
				fc 字的颜色
				bc 字的背景色
				sizey 字号 可选 16 24 32
				mode:  0非叠加模式  1叠加模式
	  返回值：  无
******************************************************************************/
void LCD_ShowChinese(u16 x, u16 y, u8 *s, u16 fc, u16 bc, u8 sizey, u8 mode)
{
	while (*s != 0)
	{
		if (sizey == 16)
			LCD_ShowChinese16x16(x, y, s, fc, bc, sizey, mode);
		else if (sizey == 24)
			LCD_ShowChinese24x24(x, y, s, fc, bc, sizey, mode);
		else if (sizey == 32)
			LCD_ShowChinese32x32(x, y, s, fc, bc, sizey, mode);
		else
			return;
		s += 2;
		x += sizey;
	}
}

/******************************************************************************
	  函数说明：显示单个16x16汉字
	  入口数据：x,y显示坐标
				*s 要显示的汉字
				fc 字的颜色
				bc 字的背景色
				sizey 字号
				mode:  0非叠加模式  1叠加模式
	  返回值：  无
******************************************************************************/
void LCD_ShowChinese16x16(u16 x, u16 y, u8 *s, u16 fc, u16 bc, u8 sizey, u8 mode)
{
	u8 i, j;
	u16 k;
	u16 HZnum;		 // 汉字数目
	u16 TypefaceNum; // 一个字符所占字节大小
	u16 x0 = x;
	TypefaceNum = sizey / 8 * sizey;			   // 此算法只适用于字宽等于字高，且字高是8的倍数的字，
												   // 也建议用户使用这样大小的字,否则显示容易出问题！
	HZnum = sizeof(tfont16) / sizeof(typFNT_GB16); // 统计汉字数目
	for (k = 0; k < HZnum; k++)
	{
		if ((tfont16[k].Index[0] == *(s)) && (tfont16[k].Index[1] == *(s + 1)))
		{
			LCD_Address_Set(x, y, x + sizey - 1, y + sizey - 1);
			for (i = 0; i < TypefaceNum; i++)
			{
				for (j = 0; j < 8; j++)
				{
					if (!mode) // 非叠加方式
					{
						if (tfont16[k].Msk[i] & (0x01 << j))
							LCD_WR_wDATA(fc);
						else
							LCD_WR_wDATA(bc);
					}
					else // 叠加方式
					{
						if (tfont16[k].Msk[i] & (0x01 << j))
							LCD_DrawPoint(x, y, fc); // 画一个点
						x++;
						if ((x - x0) == sizey)
						{
							x = x0;
							y++;
							break;
						}
					}
				}
			}
		}
		continue; // 查找到对应点阵字库立即退出，防止多个汉字重复取模带来影响
	}
}

/******************************************************************************
	  函数说明：显示单个24x24汉字
	  入口数据：x,y显示坐标
				*s 要显示的汉字
				fc 字的颜色
				bc 字的背景色
				sizey 字号
				mode:  0非叠加模式  1叠加模式
	  返回值：  无
******************************************************************************/
void LCD_ShowChinese24x24(u16 x, u16 y, u8 *s, u16 fc, u16 bc, u8 sizey, u8 mode)
{
	u8 i, j;
	u16 k;
	u16 HZnum;		 // 汉字数目
	u16 TypefaceNum; // 一个字符所占字节大小
	u16 x0 = x;
	TypefaceNum = sizey / 8 * sizey;			   // 此算法只适用于字宽等于字高，且字高是8的倍数的字，
												   // 也建议用户使用这样大小的字,否则显示容易出问题！
	HZnum = sizeof(tfont24) / sizeof(typFNT_GB24); // 统计汉字数目
	for (k = 0; k < HZnum; k++)
	{
		if ((tfont24[k].Index[0] == *(s)) && (tfont24[k].Index[1] == *(s + 1)))
		{
			LCD_Address_Set(x, y, x + sizey - 1, y + sizey - 1);
			for (i = 0; i < TypefaceNum; i++)
			{
				for (j = 0; j < 8; j++)
				{
					if (!mode) // 非叠加方式
					{
						if (tfont24[k].Msk[i] & (0x01 << j))
							LCD_WR_wDATA(fc);
						else
							LCD_WR_wDATA(bc);
					}
					else // 叠加方式
					{
						if (tfont24[k].Msk[i] & (0x01 << j))
							LCD_DrawPoint(x, y, fc); // 画一个点
						x++;
						if ((x - x0) == sizey)
						{
							x = x0;
							y++;
							break;
						}
					}
				}
			}
		}
		continue; // 查找到对应点阵字库立即退出，防止多个汉字重复取模带来影响
	}
}

/******************************************************************************
	  函数说明：显示单个32x32汉字
	  入口数据：x,y显示坐标
				*s 要显示的汉字
				fc 字的颜色
				bc 字的背景色
				sizey 字号
				mode:  0非叠加模式  1叠加模式
	  返回值：  无
******************************************************************************/
void LCD_ShowChinese32x32(u16 x, u16 y, u8 *s, u16 fc, u16 bc, u8 sizey, u8 mode)
{
	u8 i, j;
	u16 k;
	u16 HZnum;		 // 汉字数目
	u16 TypefaceNum; // 一个字符所占字节大小
	u16 x0 = x;
	TypefaceNum = sizey / 8 * sizey;			   // 此算法只适用于字宽等于字高，且字高是8的倍数的字，
												   // 也建议用户使用这样大小的字,否则显示容易出问题！
	HZnum = sizeof(tfont32) / sizeof(typFNT_GB32); // 统计汉字数目
	for (k = 0; k < HZnum; k++)
	{
		if ((tfont32[k].Index[0] == *(s)) && (tfont32[k].Index[1] == *(s + 1)))
		{
			LCD_Address_Set(x, y, x + sizey - 1, y + sizey - 1);
			for (i = 0; i < TypefaceNum; i++)
			{
				for (j = 0; j < 8; j++)
				{
					if (!mode) // 非叠加方式
					{
						if (tfont32[k].Msk[i] & (0x01 << j))
							LCD_WR_wDATA(fc);
						else
							LCD_WR_wDATA(bc);
					}
					else // 叠加方式
					{
						if (tfont32[k].Msk[i] & (0x01 << j))
							LCD_DrawPoint(x, y, fc); // 画一个点
						x++;
						if ((x - x0) == sizey)
						{
							x = x0;
							y++;
							break;
						}
					}
				}
			}
		}
		continue; // 查找到对应点阵字库立即退出，防止多个汉字重复取模带来影响
	}
}

/******************************************************************************
	  函数说明：显示单个字符
	  入口数据：x,y显示坐标
				num 要显示的字符
				fc 字的颜色
				bc 字的背景色
				sizey 字号
				mode:  0非叠加模式  1叠加模式
	  返回值：  无
******************************************************************************/
void LCD_ShowChar(u16 x, u16 y, u8 num, u16 fc, u16 bc, u8 sizey, u8 mode)
{
	u8 temp, sizex, t;
	u16 i, TypefaceNum; // 一个字符所占字节大小
	u16 x0 = x;
	sizex = sizey / 2;
	TypefaceNum = sizex / 8 * sizey;
	num = num - ' ';									 // 得到偏移后的值
	LCD_Address_Set(x, y, x + sizex - 1, y + sizey - 1); // 设置光标位置
	for (i = 0; i < TypefaceNum; i++)
	{
		if (sizey == 16)
			temp = ascii_08X16[num][i]; // 调用8x16字体
		else if (sizey == 32)
			temp = ascii_16X32[num][i]; // 调用16x32字体
		else
			return;
		for (t = 0; t < 8; t++)
		{
			if (!mode) // 非叠加模式
			{
				if (temp & (0x01 << t))
					LCD_WR_wDATA(fc);
				else
					LCD_WR_wDATA(bc);
			}
			else // 叠加模式
			{
				if (temp & (0x01 << t))
					LCD_DrawPoint(x, y, fc); // 画一个点
				x++;
				if ((x - x0) == sizex)
				{
					x = x0;
					y++;
					break;
				}
			}
		}
	}
}

/******************************************************************************
	  函数说明：显示字符串
	  入口数据：x,y显示坐标
				*p 要显示的字符串
				fc 字的颜色
				bc 字的背景色
				sizey 字号
				mode:  0非叠加模式  1叠加模式
	  返回值：  无
******************************************************************************/
void LCD_ShowString(u16 x, u16 y, const u8 *p, u16 fc, u16 bc, u8 sizey, u8 mode)
{
	while (*p != '\0')
	{
		LCD_ShowChar(x, y, *p, fc, bc, sizey, mode);
		x += sizey / 2;
		p++;
	}
}

/******************************************************************************
	  函数说明：显示数字
	  入口数据：m底数，n指数
	  返回值：  无
******************************************************************************/
u32 mypow(u8 m, u8 n)
{
	u32 result = 1;
	while (n--)
		result *= m;
	return result;
}

/******************************************************************************
	  函数说明：显示整数变量
	  入口数据：x,y显示坐标
				num 要显示整数变量
				len 要显示的位数
				fc 字的颜色
				bc 字的背景色
				sizey 字号
	  返回值：  无
******************************************************************************/
void LCD_ShowIntNum(u16 x, u16 y, u16 num, u8 len, u16 fc, u16 bc, u8 sizey)
{
	u8 t, temp;
	u8 enshow = 0;
	u8 sizex = sizey / 2;
	for (t = 0; t < len; t++)
	{
		temp = (num / mypow(10, len - t - 1)) % 10;
		if (enshow == 0 && t < (len - 1))
		{
			if (temp == 0)
			{
				LCD_ShowChar(x + t * sizex, y, ' ', fc, bc, sizey, 0);
				continue;
			}
			else
				enshow = 1;
		}
		LCD_ShowChar(x + t * sizex, y, temp + 48, fc, bc, sizey, 0);
	}
}

/******************************************************************************
	  函数说明：显示两位小数变量
	  入口数据：x,y显示坐标
				num 要显示小数变量
				len 要显示的位数
				fc 字的颜色
				bc 字的背景色
				sizey 字号
	  返回值：  无
******************************************************************************/
void LCD_ShowFloatNum1(u16 x, u16 y, float num, u8 len, u16 fc, u16 bc, u8 sizey)
{
	u8 t, temp, sizex;
	u16 num1;

	sizex = sizey / 2;
	num1 = num * 100;
	for (t = 0; t < len; t++)
	{
		temp = (num1 / mypow(10, len - t - 1)) % 10;
		if (t == (len - 2))
		{
			LCD_ShowChar(x + (len - 2) * sizex, y, '.', fc, bc, sizey, 0);
			t++;
			len += 1;
		}
		LCD_ShowChar(x + t * sizex, y, temp + 48, fc, bc, sizey, 0);
	}
}

/******************************************************************************
	  函数说明：显示图片
	  入口数据：x,y起点坐标
				length 图片长度
				width  图片宽度
				pic[]  图片数组
	  返回值：  无
******************************************************************************/
void LCD_ShowPicture(u16 x, u16 y, u16 length, u16 width, const u8 pic[])
{
	u16 i, j, k = 0;

	LCD_Address_Set(x, y, x + length - 1, y + width - 1);
	for (i = 0; i < length; i++)
	{
		for (j = 0; j < width; j++)
		{
			LCD_WR_bDATA(pic[k * 2]);
			LCD_WR_bDATA(pic[k * 2 + 1]);
			k++;
		}
	}
}
/***************************************************************************
;** 函数名称:  	showimage
;** 功能描述:
;** 输入参数: 	sx,sy--起始坐标；ex,ey--宽高；*s--字符串
;** 返 回 值:
;** 优 先 级：
;** 全局变量:
;** 调用模块:
;** 作　  者:   M-L-A
;** 日　  期:   2017-10-19
;** 修改原因：
;***************************************************************************/
void LCD_ShowImage(uint16_t x, uint16_t y, uint16_t w, uint16_t h, const unsigned char *p)
{
	unsigned int i, len;
	unsigned char picH, picL;

	LCD_Address_Set(x, y, x + w - 1, y + h - 1);
	len = w * h;
	for (i = 0; i < len; i++)
	{
		picH = *(p + i * 2 + 1);
		LCD_WR_bDATA(picH);
		picL = *(p + i * 2); // 数据低位在前
		LCD_WR_bDATA(picL);
	}
}

/******************************************************************************
	  函数说明：显示单个字符
	  入口数据：x,y显示坐标
				*str 要显示的字符串
				fc 字的颜色
				bc 字的背景色
				sizey 字号
				mode:  0非叠加模式  1叠加模式
	  返回值：  无
******************************************************************************/
void LCD_ShowASCII(u16 x, u16 y, u8 *str, u16 fc, u16 bc, u8 size, u8 mode)
{
	u8 n, b, t, *pt;
	u16 i, sx, sy, tn, x0, len;

	if (size == ASC_8X16) // 调用8x16字体
	{
		pt = (u8 *)ascii_08X16;
		tn = 16; // 一个字符所占字节大小
		sx = 8;
		sy = 16;
	}
	else if (size == ASC_12X24) // 调用12x24字体
	{
		pt = (u8 *)ascii_12X24;
		tn = 48; // 一个字符所占字节大小
		sx = 16; // 12 //8的倍数
		sy = 24;
	}
	else if (size == ASC_16X32) // 调用16x32字体
	{
		pt = (u8 *)ascii_16X32;
		tn = 64; // 一个字符所占字节大小
		sx = 16;
		sy = 32;
	}
	else
	{
		return;
	}

	len = strlen((char *)str);
	while (len--)
	{
		n = *str;
		n = n - ' ';								   // 得到偏移后的值
		LCD_Address_Set(x, y, x + sx - 1, y + sy - 1); // 设置光标位置
		x0 = x;
		for (i = 0; i < tn; i++)
		{
			b = *(pt + n * tn + i);
			for (t = 0; t < 8; t++)
			{
				if (!mode) // 非叠加模式
				{
					if (b & (0x01 << t))
					{
						LCD_WR_wDATA(fc);
					}
					else
					{
						LCD_WR_wDATA(bc);
					}
				}
				else // 叠加模式
				{
					if (b & (0x01 << t))
					{
						LCD_DrawPoint(x, y, fc);
					} // 画一个点
					x++;
					if ((x - x0) == sx)
					{
						x = x0;
						y++;
						break;
					}
				}
			}
		}
		str++;
		x += sy / 2;
	}
}

/***************************************************************************
;** 函数名称: 	xmc_init
;** 功能描述:   this function must be called before any write/read operation
;** 输入参数:
;** 返 回 值:
;** 全局变量:
;** 调用模块:
;** 作　  者:   M-L-A
;** 日　  期:  2022-9-23
;** 修改原因:
;** 说    明:
;***************************************************************************/
void lcd_init(void)
{
	/* init xmc */
	lcd_io_config();
	delay_ms(50);

	/* reset lcd */
	LCD_RESET_HIGH;
	delay_ms(1);
	LCD_RESET_LOW;
	delay_ms(100);
	LCD_RESET_HIGH;
	delay_ms(1);

	SetOutputVoltageDAC1(0); // 打开背光
	delay_ms(100);

	LCD_WR_REG(0x11);
	delay_ms(120);
	LCD_WR_REG(0x36);

	if (USE_HORIZONTAL == 0)
		LCD_WR_bDATA(0x00);
	else if (USE_HORIZONTAL == 1)
		LCD_WR_bDATA(0xC0);
	else if (USE_HORIZONTAL == 2)
		LCD_WR_bDATA(0x70);
	else
		LCD_WR_bDATA(0xA0);

	LCD_WR_REG(0x3A);
	LCD_WR_bDATA(0x05);

	LCD_WR_REG(0xB2);
	LCD_WR_bDATA(0x0C);
	LCD_WR_bDATA(0x0C);
	LCD_WR_bDATA(0x00);
	LCD_WR_bDATA(0x33);
	LCD_WR_bDATA(0x33);

	LCD_WR_REG(0xB7);
	LCD_WR_bDATA(0x35);

	LCD_WR_REG(0xBB);
	LCD_WR_bDATA(0x19);

	LCD_WR_REG(0xC0);
	LCD_WR_bDATA(0x2C);

	LCD_WR_REG(0xC2);
	LCD_WR_bDATA(0x01);

	LCD_WR_REG(0xC3);
	LCD_WR_bDATA(0x12);

	LCD_WR_REG(0xC4);
	LCD_WR_bDATA(0x20);

	LCD_WR_REG(0xC6);
	LCD_WR_bDATA(0x0F);

	LCD_WR_REG(0xD0);
	LCD_WR_bDATA(0xA4);
	LCD_WR_bDATA(0xA1);

	LCD_WR_REG(0xE0);
	LCD_WR_bDATA(0xD0);
	LCD_WR_bDATA(0x04);
	LCD_WR_bDATA(0x0D);
	LCD_WR_bDATA(0x11);
	LCD_WR_bDATA(0x13);
	LCD_WR_bDATA(0x2B);
	LCD_WR_bDATA(0x3F);
	LCD_WR_bDATA(0x54);
	LCD_WR_bDATA(0x4C);
	LCD_WR_bDATA(0x18);
	LCD_WR_bDATA(0x0D);
	LCD_WR_bDATA(0x0B);
	LCD_WR_bDATA(0x1F);
	LCD_WR_bDATA(0x23);

	LCD_WR_REG(0xE1);
	LCD_WR_bDATA(0xD0);
	LCD_WR_bDATA(0x04);
	LCD_WR_bDATA(0x0C);
	LCD_WR_bDATA(0x11);
	LCD_WR_bDATA(0x13);
	LCD_WR_bDATA(0x2C);
	LCD_WR_bDATA(0x3F);
	LCD_WR_bDATA(0x44);
	LCD_WR_bDATA(0x51);
	LCD_WR_bDATA(0x2F);
	LCD_WR_bDATA(0x1F);
	LCD_WR_bDATA(0x1F);
	LCD_WR_bDATA(0x20);
	LCD_WR_bDATA(0x23);

	LCD_WR_REG(0x21);

	LCD_WR_REG(0x29);

	if (pLCD->logo)
	{
		LCD_ShowImage(0, 0, 320, 240, gImage_logo);
	}
	else
	{
		LCD_Fill(0, 0, 320, 240, BLACK);
		LCD_ShowASCII(0, 0, (u8 *)" Initial - - - - -", WHITE, BLACK, 32, 0);
	}
	delay_ms(100);
	SetOutputVoltageDAC1(pLCD->blk * BLK_SRV / 100 + BLK_MIN); // 打开背光

	//	pLCD->time=200;//0;
}
