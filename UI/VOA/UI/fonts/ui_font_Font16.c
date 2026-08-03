/*******************************************************************************
 * Size: 16 px
 * Bpp: 1
 * Opts: --bpp 1 --size 16 --font C:/Users/Administrator/Desktop/SQL studio/VOA/assets/AlibabaPuHuiTi-3-65-Medium.ttf -o C:/Users/Administrator/Desktop/SQL studio/VOA/assets\ui_font_Font16.c --format lvgl -r 0x20-0x7f --symbols 波长衰减矫正通断波长选择输出光功率功率偏移补偿设备名称：序列号：端口号：IP地址：语言选择：亮度：中文 --no-compress --no-prefilter
 ******************************************************************************/

#include "../ui.h"

#ifndef UI_FONT_FONT16
#define UI_FONT_FONT16 1
#endif

#if UI_FONT_FONT16

/*-----------------
 *    BITMAPS
 *----------------*/

/*Store the image of the glyphs*/
static LV_ATTRIBUTE_LARGE_CONST const uint8_t glyph_bitmap[] = {
    /* U+0020 " " */
    0x0,

    /* U+0021 "!" */
    0xff, 0xff, 0x3c,

    /* U+0022 "\"" */
    0xd6, 0xb5, 0xad, 0x0,

    /* U+0023 "#" */
    0x11, 0x19, 0xbf, 0xe6, 0x42, 0x21, 0x10, 0x89,
    0xff, 0x66, 0x32, 0x11, 0x0,

    /* U+0024 "$" */
    0x10, 0x21, 0xf6, 0x8d, 0x1a, 0x3c, 0x3e, 0x1e,
    0x2c, 0x58, 0xbf, 0xc2, 0x4, 0x8,

    /* U+0025 "%" */
    0x60, 0x92, 0x32, 0x44, 0x49, 0x9, 0x20, 0xc9,
    0x82, 0x48, 0x49, 0x11, 0x26, 0x24, 0x83, 0x0,

    /* U+0026 "&" */
    0x3c, 0x19, 0x86, 0x61, 0xb8, 0x3c, 0x1e, 0x6f,
    0x9b, 0x36, 0xc7, 0x31, 0xc7, 0xdc,

    /* U+0027 "'" */
    0xff, 0xc0,

    /* U+0028 "(" */
    0x31, 0x98, 0xcc, 0x63, 0x18, 0xc6, 0x30, 0xc6,
    0x18, 0xc0,

    /* U+0029 ")" */
    0x63, 0xc, 0x61, 0x8c, 0x63, 0x18, 0xc6, 0x63,
    0x31, 0x80,

    /* U+002A "*" */
    0x10, 0x21, 0xf1, 0xc2, 0xc5, 0x0,

    /* U+002B "+" */
    0x18, 0x18, 0x18, 0xff, 0x18, 0x18, 0x18, 0x18,

    /* U+002C "," */
    0x6d, 0x68,

    /* U+002D "-" */
    0xf8,

    /* U+002E "." */
    0xf0,

    /* U+002F "/" */
    0xc, 0x30, 0x86, 0x10, 0x43, 0x8, 0x21, 0x84,
    0x10, 0xc0,

    /* U+0030 "0" */
    0x3c, 0x66, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3,
    0xc3, 0x66, 0x3c,

    /* U+0031 "1" */
    0x7f, 0xc6, 0x31, 0x8c, 0x63, 0x18, 0xc6,

    /* U+0032 "2" */
    0x7c, 0x1c, 0x18, 0x30, 0x61, 0x87, 0x1c, 0x71,
    0xc3, 0xf8,

    /* U+0033 "3" */
    0xfc, 0xc, 0x18, 0x77, 0x81, 0x81, 0x83, 0x6,
    0x1b, 0xe0,

    /* U+0034 "4" */
    0xe, 0xe, 0x16, 0x36, 0x66, 0x46, 0xc6, 0xff,
    0x6, 0x6, 0x6,

    /* U+0035 "5" */
    0x7c, 0x83, 0x6, 0xf, 0x81, 0xc1, 0x83, 0x6,
    0x1b, 0xe0,

    /* U+0036 "6" */
    0x1c, 0x30, 0x60, 0xc0, 0xfe, 0xe7, 0xc3, 0xc3,
    0xc3, 0x66, 0x3c,

    /* U+0037 "7" */
    0xfe, 0xc, 0x10, 0x60, 0xc1, 0x6, 0x8, 0x30,
    0x61, 0x80,

    /* U+0038 "8" */
    0x7e, 0xc3, 0xc3, 0xc3, 0x3c, 0x66, 0xc3, 0xc3,
    0xc3, 0xe7, 0x3c,

    /* U+0039 "9" */
    0x3c, 0x66, 0xc3, 0xc3, 0xc3, 0xe7, 0x7f, 0x3,
    0x6, 0xc, 0x38,

    /* U+003A ":" */
    0xf0, 0x3, 0xc0,

    /* U+003B ";" */
    0x6c, 0x0, 0x1b, 0x5a, 0x0,

    /* U+003C "<" */
    0x3, 0xf, 0x78, 0xe0, 0xc0, 0x78, 0x1e, 0x3,

    /* U+003D "=" */
    0xff, 0x0, 0x0, 0x0, 0xff,

    /* U+003E ">" */
    0xc0, 0xf0, 0x1e, 0x7, 0x3, 0x1e, 0x78, 0xc0,

    /* U+003F "?" */
    0xfc, 0xc, 0x18, 0x30, 0xe3, 0x8c, 0x18, 0x0,
    0x60, 0xc0,

    /* U+0040 "@" */
    0xf, 0xc0, 0xc3, 0x8c, 0xc, 0xcf, 0xbc, 0xc9,
    0xec, 0x4f, 0x62, 0x7b, 0x13, 0xd9, 0xb6, 0x77,
    0x18, 0x0, 0x60, 0x1, 0xfc, 0x0,

    /* U+0041 "A" */
    0xe, 0x1, 0x40, 0x6c, 0xd, 0x81, 0x10, 0x63,
    0xc, 0x63, 0xfe, 0x60, 0xcc, 0x1b, 0x1, 0x80,

    /* U+0042 "B" */
    0xfc, 0xc6, 0xc6, 0xc6, 0xc6, 0xfc, 0xc7, 0xc3,
    0xc3, 0xc3, 0xfe,

    /* U+0043 "C" */
    0x3f, 0x60, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0,
    0xc0, 0x60, 0x3f,

    /* U+0044 "D" */
    0xfe, 0x61, 0xb0, 0xf8, 0x3c, 0x1e, 0xf, 0x7,
    0x83, 0xc3, 0x61, 0xbf, 0x0,

    /* U+0045 "E" */
    0xff, 0x83, 0x6, 0xc, 0x1f, 0xb0, 0x60, 0xc1,
    0x83, 0xf8,

    /* U+0046 "F" */
    0xff, 0x83, 0x6, 0xc, 0x1f, 0xb0, 0x60, 0xc1,
    0x83, 0x0,

    /* U+0047 "G" */
    0x1f, 0xb0, 0x18, 0x18, 0xc, 0x6, 0x3f, 0x7,
    0x83, 0xc1, 0xb0, 0xcf, 0xe0,

    /* U+0048 "H" */
    0xc1, 0xe0, 0xf0, 0x78, 0x3f, 0xfe, 0xf, 0x7,
    0x83, 0xc1, 0xe0, 0xf0, 0x60,

    /* U+0049 "I" */
    0xff, 0xff, 0xfc,

    /* U+004A "J" */
    0x18, 0xc6, 0x31, 0x8c, 0x63, 0x18, 0xc6, 0x31,
    0xf8,

    /* U+004B "K" */
    0xc3, 0x63, 0x31, 0x19, 0x8d, 0x87, 0x83, 0x61,
    0x98, 0xc6, 0x63, 0xb0, 0xc0,

    /* U+004C "L" */
    0xc1, 0x83, 0x6, 0xc, 0x18, 0x30, 0x60, 0xc1,
    0x83, 0xf8,

    /* U+004D "M" */
    0xe0, 0xfe, 0x3f, 0xc7, 0xe8, 0xbd, 0xb7, 0xb6,
    0xf2, 0x9e, 0x73, 0xcc, 0x78, 0xf, 0x1, 0x80,

    /* U+004E "N" */
    0xe1, 0xf8, 0xfc, 0x7b, 0x3d, 0x9e, 0x6f, 0x37,
    0x8b, 0xc7, 0xe1, 0xf0, 0xe0,

    /* U+004F "O" */
    0x3f, 0x18, 0x6c, 0xf, 0x3, 0xc0, 0xf0, 0x3c,
    0xf, 0x3, 0xc0, 0xd8, 0x63, 0xf0,

    /* U+0050 "P" */
    0xfe, 0xc7, 0xc3, 0xc3, 0xc3, 0xc7, 0xfe, 0xc0,
    0xc0, 0xc0, 0xc0,

    /* U+0051 "Q" */
    0x3f, 0x18, 0x6c, 0xf, 0x3, 0xc0, 0xf0, 0x3c,
    0xf, 0x3, 0xc0, 0xd8, 0x63, 0xf0, 0x18, 0x3,
    0x0,

    /* U+0052 "R" */
    0xfe, 0x63, 0xb0, 0xd8, 0x6c, 0x77, 0xf3, 0x31,
    0x8c, 0xc6, 0x61, 0xb0, 0xe0,

    /* U+0053 "S" */
    0x7d, 0x83, 0x6, 0xf, 0x8f, 0x87, 0x83, 0x6,
    0xf, 0xf0,

    /* U+0054 "T" */
    0xff, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18,
    0x18, 0x18, 0x18,

    /* U+0055 "U" */
    0xc1, 0xe0, 0xf0, 0x78, 0x3c, 0x1e, 0xf, 0x7,
    0x83, 0xc1, 0xb1, 0x8f, 0x80,

    /* U+0056 "V" */
    0xc0, 0xd8, 0x36, 0x19, 0x86, 0x31, 0x8c, 0xc3,
    0x30, 0x6c, 0x1e, 0x3, 0x80, 0xc0,

    /* U+0057 "W" */
    0xc0, 0xd, 0x8e, 0x36, 0x38, 0xd8, 0xe2, 0x66,
    0x98, 0x9b, 0x63, 0x4d, 0x8d, 0x36, 0x3c, 0x50,
    0x71, 0xc1, 0x87, 0x0,

    /* U+0058 "X" */
    0x60, 0xcc, 0x63, 0x30, 0x6c, 0x1e, 0x3, 0x81,
    0xe0, 0x6c, 0x33, 0x18, 0x66, 0xc,

    /* U+0059 "Y" */
    0xc0, 0xd8, 0x63, 0x30, 0xcc, 0x1e, 0x7, 0x80,
    0xc0, 0x30, 0xc, 0x3, 0x0, 0xc0,

    /* U+005A "Z" */
    0xff, 0x3, 0x81, 0x81, 0x80, 0xc0, 0xc0, 0xc0,
    0x60, 0x60, 0x60, 0x3f, 0xe0,

    /* U+005B "[" */
    0xfc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xf0,

    /* U+005C "\\" */
    0x40, 0x40, 0x60, 0x20, 0x30, 0x10, 0x18, 0x8,
    0x8, 0xc, 0x4, 0x6, 0x2, 0x3,

    /* U+005D "]" */
    0xf3, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0xf0,

    /* U+005E "^" */
    0x38, 0x51, 0xb3, 0x64, 0x58, 0xc0,

    /* U+005F "_" */
    0xff,

    /* U+0060 "`" */
    0xcc, 0x80,

    /* U+0061 "a" */
    0x3e, 0x3, 0x3, 0x3, 0x7f, 0xc3, 0xc3, 0xc7,
    0x7b,

    /* U+0062 "b" */
    0xc0, 0xc0, 0xc0, 0xde, 0xe6, 0xc3, 0xc3, 0xc3,
    0xc3, 0xc3, 0xe6, 0xde,

    /* U+0063 "c" */
    0x3e, 0xc3, 0x6, 0xc, 0x18, 0x30, 0x30, 0x3e,

    /* U+0064 "d" */
    0x3, 0x3, 0x3, 0x7b, 0x67, 0xc3, 0xc3, 0xc3,
    0xc3, 0xc3, 0x67, 0x7b,

    /* U+0065 "e" */
    0x3e, 0x66, 0xc3, 0xc3, 0xff, 0xc0, 0xc0, 0x60,
    0x3e,

    /* U+0066 "f" */
    0x3d, 0x86, 0x3e, 0x61, 0x86, 0x18, 0x61, 0x86,
    0x18,

    /* U+0067 "g" */
    0x7b, 0x67, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0x67,
    0x7b, 0x3, 0x6, 0x7c,

    /* U+0068 "h" */
    0xc1, 0x83, 0x7, 0xee, 0x78, 0xf1, 0xe3, 0xc7,
    0x8f, 0x1e, 0x30,

    /* U+0069 "i" */
    0xf3, 0xff, 0xff,

    /* U+006A "j" */
    0x33, 0x3, 0x33, 0x33, 0x33, 0x33, 0x33, 0xe0,

    /* U+006B "k" */
    0xc1, 0x83, 0x6, 0x3c, 0xdb, 0x34, 0x78, 0xd9,
    0xbb, 0x36, 0x30,

    /* U+006C "l" */
    0xdb, 0x6d, 0xb6, 0xdb, 0x30,

    /* U+006D "m" */
    0xfd, 0xee, 0x63, 0xc6, 0x3c, 0x63, 0xc6, 0x3c,
    0x63, 0xc6, 0x3c, 0x63, 0xc6, 0x30,

    /* U+006E "n" */
    0xfd, 0xcf, 0x1e, 0x3c, 0x78, 0xf1, 0xe3, 0xc6,

    /* U+006F "o" */
    0x3c, 0x66, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0x66,
    0x3c,

    /* U+0070 "p" */
    0xde, 0xe6, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0xe6,
    0xde, 0xc0, 0xc0, 0xc0,

    /* U+0071 "q" */
    0x7b, 0x67, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0x67,
    0x7b, 0x3, 0x3, 0x3,

    /* U+0072 "r" */
    0xdf, 0x31, 0x8c, 0x63, 0x18, 0xc0,

    /* U+0073 "s" */
    0x7f, 0xc, 0x3c, 0x7c, 0x70, 0xc3, 0xf8,

    /* U+0074 "t" */
    0x63, 0x3e, 0xc6, 0x31, 0x8c, 0x63, 0xe,

    /* U+0075 "u" */
    0xc7, 0x8f, 0x1e, 0x3c, 0x78, 0xf1, 0xe7, 0x7e,

    /* U+0076 "v" */
    0xc1, 0x21, 0x98, 0xcc, 0x42, 0x61, 0xb0, 0xd0,
    0x38, 0x1c, 0x0,

    /* U+0077 "w" */
    0xc3, 0x1a, 0x38, 0xd9, 0xc6, 0xcb, 0x26, 0x5b,
    0x16, 0x58, 0xe3, 0x87, 0x1c, 0x18, 0x60,

    /* U+0078 "x" */
    0x63, 0x33, 0xd, 0x83, 0x81, 0xc1, 0xe0, 0xd8,
    0xc6, 0x43, 0x0,

    /* U+0079 "y" */
    0xc1, 0x43, 0x63, 0x62, 0x26, 0x34, 0x34, 0x1c,
    0x18, 0x18, 0x10, 0x60,

    /* U+007A "z" */
    0x7e, 0xc, 0x30, 0xc1, 0x86, 0x1c, 0x70, 0xfe,

    /* U+007B "{" */
    0x36, 0x66, 0x66, 0x6c, 0x66, 0x66, 0x66, 0x30,

    /* U+007C "|" */
    0xff, 0xff, 0xff, 0xfc,

    /* U+007D "}" */
    0xc6, 0x66, 0x66, 0x63, 0x66, 0x66, 0x66, 0xc0,

    /* U+007E "~" */
    0x79, 0xa7, 0xb1, 0xc0,

    /* U+4E2D "中" */
    0x6, 0x0, 0x60, 0x6, 0xf, 0xff, 0xc6, 0x3c,
    0x63, 0xc6, 0x3c, 0x63, 0xc6, 0x3f, 0xff, 0x6,
    0x0, 0x60, 0x6, 0x0, 0x60, 0x6, 0x0,

    /* U+4EAE "亮" */
    0x2, 0x7, 0xff, 0xc0, 0x0, 0x7f, 0xc2, 0x2,
    0x1f, 0xf0, 0x0, 0x1f, 0xff, 0xc0, 0x1e, 0xfc,
    0xc6, 0x22, 0x61, 0x1e, 0xf, 0x80,

    /* U+504F "偏" */
    0x0, 0x0, 0x86, 0xd, 0xfe, 0x48, 0x16, 0x7f,
    0xb2, 0x1, 0x90, 0x1c, 0xff, 0x26, 0xa9, 0x35,
    0x4b, 0xfe, 0x55, 0x53, 0xaa, 0x91, 0x5c,

    /* U+507F "偿" */
    0x10, 0xc0, 0xcb, 0x62, 0x2d, 0xb, 0xff, 0x6c,
    0xd, 0xb0, 0x3e, 0x3f, 0x28, 0x0, 0x20, 0x0,
    0xbf, 0xf2, 0x18, 0x8, 0xcc, 0x26, 0x18, 0x9f,
    0xe2, 0x0, 0x80,

    /* U+5149 "光" */
    0x1, 0x0, 0x84, 0x23, 0x11, 0x86, 0x4c, 0xd,
    0x60, 0x4, 0x87, 0xff, 0xc1, 0x30, 0xc, 0xc0,
    0x33, 0x0, 0xcc, 0x46, 0x31, 0x30, 0xc7, 0x81,
    0xf0,

    /* U+51CF "减" */
    0x0, 0x28, 0x80, 0x51, 0x3f, 0xf3, 0x41, 0x2,
    0x82, 0x1, 0x7d, 0x2, 0xa, 0x14, 0x14, 0x6b,
    0xe8, 0xd5, 0xe1, 0x2b, 0x46, 0x5f, 0xad, 0x5,
    0x42, 0x11, 0x80,

    /* U+51FA "出" */
    0x2, 0x0, 0x10, 0x18, 0x84, 0xc4, 0x26, 0x21,
    0x31, 0x9, 0xff, 0xc0, 0x40, 0x2, 0x6, 0x10,
    0xf0, 0x87, 0x84, 0x3c, 0x21, 0xff, 0xfc, 0x0,
    0x60,

    /* U+5217 "列" */
    0x0, 0x5, 0xfe, 0x11, 0x82, 0x46, 0x9, 0x1f,
    0x24, 0xfc, 0x92, 0x32, 0x5c, 0xc9, 0xda, 0x25,
    0x38, 0x90, 0xc2, 0x46, 0x1, 0x30, 0x5, 0x80,
    0xf0, 0x0, 0x0,

    /* U+529F "功" */
    0x0, 0xc0, 0x3, 0x7, 0xcc, 0x4, 0xff, 0x10,
    0xcc, 0x43, 0x31, 0xc, 0xc4, 0x33, 0x10, 0xcc,
    0x76, 0x37, 0x98, 0xc0, 0xc3, 0x6, 0x3c, 0x30,
    0x80,

    /* U+53E3 "口" */
    0xff, 0xfc, 0x3, 0xc0, 0x3c, 0x3, 0xc0, 0x3c,
    0x3, 0xc0, 0x3c, 0x3, 0xc0, 0x3c, 0x3, 0xff,
    0xfc, 0x3,

    /* U+53F7 "号" */
    0x3f, 0xf0, 0xc0, 0xc3, 0x3, 0xf, 0xfc, 0x0,
    0x0, 0x0, 0xf, 0xff, 0xc4, 0x0, 0x3f, 0xf0,
    0x0, 0xc0, 0x3, 0x0, 0xc, 0x0, 0x20, 0xf,
    0x80,

    /* U+540D "名" */
    0x4, 0x0, 0x40, 0xf, 0xf1, 0x3, 0x78, 0x64,
    0xdc, 0x3, 0x0, 0xe0, 0x7f, 0xfd, 0x1, 0x10,
    0x11, 0x1, 0x10, 0x11, 0xff, 0x10, 0x10,

    /* U+5730 "地" */
    0x0, 0x40, 0x81, 0x2, 0x24, 0x8, 0x92, 0x22,
    0x7b, 0xcf, 0x22, 0xe4, 0x88, 0x92, 0x22, 0x48,
    0x89, 0x63, 0xa4, 0x5c, 0x81, 0xc2, 0x4, 0xf,
    0xf0,

    /* U+5740 "址" */
    0x20, 0x60, 0x40, 0xc0, 0x81, 0x81, 0x3, 0xf,
    0xa6, 0x1f, 0x4f, 0x88, 0x98, 0x11, 0x30, 0x22,
    0x60, 0x44, 0xc0, 0xa9, 0x81, 0xd3, 0xe, 0x26,
    0x3, 0xff, 0xc0,

    /* U+5907 "备" */
    0xc, 0x0, 0x3f, 0xf0, 0xe0, 0xe3, 0x63, 0x4,
    0x7c, 0x0, 0xf8, 0x1f, 0x3f, 0x70, 0xf, 0x3f,
    0xf8, 0x42, 0x30, 0xff, 0xe1, 0x8, 0xc2, 0x11,
    0x87, 0xff, 0x8, 0x6, 0x0,

    /* U+5E8F "序" */
    0x1, 0x80, 0xff, 0xf2, 0x0, 0xb, 0xfe, 0x22,
    0x30, 0x8d, 0x82, 0x18, 0xf, 0xff, 0x20, 0x88,
    0x82, 0x66, 0x8, 0x10, 0x20, 0xc3, 0x80,

    /* U+5EA6 "度" */
    0x0, 0x80, 0x1, 0x0, 0xff, 0xf1, 0x0, 0x2,
    0x21, 0x5, 0xff, 0x88, 0x84, 0x11, 0xf8, 0x20,
    0x0, 0x5f, 0xf0, 0x98, 0x61, 0x1b, 0x4, 0x1e,
    0xb, 0xe7, 0xd4, 0x0, 0x0,

    /* U+62E9 "择" */
    0x10, 0x0, 0x27, 0xf8, 0x46, 0x33, 0xe6, 0xc1,
    0x7, 0x2, 0x1f, 0x5, 0xe3, 0x9c, 0x10, 0x53,
    0xfc, 0x20, 0x40, 0x40, 0x80, 0x9f, 0xf1, 0x2,
    0xe, 0x4, 0x8, 0x8, 0x0,

    /* U+6587 "文" */
    0x3, 0x0, 0x2, 0x1, 0xff, 0xf0, 0xc1, 0x80,
    0x82, 0x1, 0x8c, 0x1, 0x10, 0x3, 0x60, 0x3,
    0x80, 0x7, 0x0, 0x3b, 0x81, 0xe3, 0xc7, 0x1,
    0xc8, 0x0, 0x0,

    /* U+65AD "断" */
    0x8, 0xa, 0x21, 0xee, 0xaf, 0x2b, 0xa0, 0xbc,
    0x82, 0x22, 0xf, 0xef, 0xe6, 0x24, 0x9c, 0x93,
    0xba, 0x4e, 0x89, 0x22, 0x64, 0x81, 0x13, 0xfc,
    0x40, 0x31, 0x0,

    /* U+6B63 "正" */
    0x7f, 0xf8, 0x4, 0x0, 0x10, 0x0, 0x40, 0x31,
    0x0, 0xc4, 0x3, 0x1f, 0x8c, 0x40, 0x31, 0x0,
    0xc4, 0x3, 0x10, 0xc, 0x40, 0xff, 0xfc,

    /* U+6CE2 "波" */
    0x0, 0x41, 0x81, 0x3, 0x7f, 0xc1, 0x12, 0xc4,
    0x49, 0x91, 0x3, 0x7f, 0x81, 0xc4, 0x35, 0x90,
    0x96, 0xc6, 0xce, 0x1a, 0x7c, 0x5b, 0x99, 0x78,
    0x30,

    /* U+7387 "率" */
    0x0, 0x0, 0xc, 0xf, 0xff, 0xc1, 0x82, 0x64,
    0xd8, 0xfe, 0xc0, 0x32, 0xd, 0xbc, 0xef, 0xdd,
    0x21, 0x0, 0x30, 0x3f, 0xff, 0x3, 0x0, 0xc,
    0x0, 0x30, 0x0,

    /* U+77EB "矫" */
    0x20, 0x8, 0xc7, 0xf1, 0xf1, 0x3, 0x82, 0xf,
    0x4, 0x16, 0xff, 0x8c, 0x3c, 0x7e, 0xc8, 0x33,
    0x18, 0x6f, 0x3c, 0xd6, 0x41, 0xcc, 0x86, 0xd9,
    0x18, 0x62, 0x21, 0x84, 0x0,

    /* U+79F0 "称" */
    0x1, 0x83, 0xe4, 0x2, 0x3f, 0x88, 0x82, 0x26,
    0x1b, 0xf9, 0x42, 0x4, 0x1c, 0xd4, 0x7a, 0x53,
    0xb9, 0x6a, 0x64, 0xab, 0x12, 0x2c, 0x4c, 0x87,
    0x2, 0x18, 0x0,

    /* U+79FB "移" */
    0x0, 0x0, 0x18, 0xc1, 0xe3, 0xf0, 0x8c, 0x61,
    0x3d, 0x8f, 0x86, 0x4, 0x38, 0x1d, 0xf0, 0x3c,
    0xfe, 0xeb, 0x9, 0x4f, 0x32, 0x92, 0xc1, 0x6,
    0x2, 0x38, 0x5, 0xc0, 0x0,

    /* U+7AEF "端" */
    0x60, 0x40, 0x89, 0x22, 0x24, 0xbe, 0xfe, 0x0,
    0x3, 0x60, 0xd, 0xff, 0xd4, 0x10, 0x57, 0xf9,
    0x5a, 0xa3, 0x6a, 0x9f, 0xaa, 0xe6, 0xa8, 0x18,
    0x60, 0x61, 0x80,

    /* U+8865 "补" */
    0x10, 0x40, 0x20, 0x80, 0x41, 0x3, 0xe2, 0x0,
    0x84, 0x3, 0xc, 0xd, 0x9e, 0x1a, 0x26, 0x78,
    0x45, 0xbc, 0x80, 0x59, 0x0, 0x82, 0x1, 0x4,
    0x2, 0x8, 0x4, 0x10, 0x0,

    /* U+8870 "衰" */
    0x0, 0x0, 0xc, 0xf, 0xff, 0x80, 0x0, 0x3f,
    0xf0, 0x80, 0xcf, 0xff, 0xc8, 0xc, 0x3f, 0xf0,
    0x1c, 0x41, 0xdf, 0x3e, 0x30, 0xd9, 0x78, 0x7c,
    0x71, 0x80, 0x0,

    /* U+8A00 "言" */
    0x3, 0x0, 0xc, 0xf, 0xff, 0xc0, 0x0, 0x3f,
    0xf0, 0x0, 0x3, 0xff, 0xf, 0xfc, 0x0, 0x0,
    0xff, 0xc2, 0x1, 0x8, 0x4, 0x20, 0x10, 0xff,
    0xc2, 0x1, 0x0,

    /* U+8BBE "设" */
    0x0, 0x1, 0x8f, 0xc3, 0x31, 0x4, 0xc4, 0x2,
    0x1f, 0x98, 0xe, 0x40, 0x9, 0xfe, 0x22, 0x18,
    0x8c, 0xc2, 0x1a, 0xf, 0x38, 0x3b, 0xf0, 0xbc,
    0x70, 0xc0, 0x40,

    /* U+8BED "语" */
    0x0, 0x1, 0xbf, 0xe2, 0x10, 0x8, 0x40, 0x7,
    0xf3, 0x8c, 0x42, 0xff, 0xcb, 0xff, 0x20, 0x0,
    0x9f, 0xc2, 0xc1, 0xf, 0x4, 0x34, 0x10, 0x9f,
    0xc0, 0x41, 0x0,

    /* U+8F93 "输" */
    0x10, 0x60, 0x21, 0x41, 0xf6, 0xc3, 0xe8, 0xc2,
    0x3f, 0xec, 0x0, 0x16, 0xff, 0x3f, 0x7e, 0x1b,
    0xfc, 0x3d, 0xf9, 0xef, 0xf0, 0xd6, 0x61, 0xac,
    0xc3, 0x59, 0x86, 0xe6, 0x0,

    /* U+9009 "选" */
    0x0, 0x81, 0xa, 0x6, 0x68, 0xd, 0xfe, 0x4,
    0x80, 0x12, 0xe, 0xff, 0xc8, 0x50, 0x21, 0x40,
    0x85, 0x12, 0x24, 0x4b, 0x1e, 0x58, 0x3, 0x3f,
    0xf0,

    /* U+901A "通" */
    0x67, 0xf8, 0x8c, 0xc1, 0x1c, 0x1, 0xfe, 0xe4,
    0x88, 0x9f, 0xe2, 0x48, 0x89, 0x22, 0x27, 0xf8,
    0x92, 0x22, 0x4b, 0x94, 0x0, 0x8f, 0xfc,

    /* U+957F "长" */
    0x30, 0x10, 0xc0, 0xc3, 0xe, 0xd, 0xe0, 0x36,
    0x0, 0xc0, 0xf, 0xff, 0xcc, 0xc0, 0x31, 0x80,
    0xc3, 0x3, 0xe, 0xd, 0xce, 0x3e, 0x1c, 0xc0,
    0x10,

    /* U+FF1A "：" */
    0xf0, 0x3, 0xc0
};


/*---------------------
 *  GLYPH DESCRIPTION
 *--------------------*/

static const lv_font_fmt_txt_glyph_dsc_t glyph_dsc[] = {
    {.bitmap_index = 0, .adv_w = 0, .box_w = 0, .box_h = 0, .ofs_x = 0, .ofs_y = 0} /* id = 0 reserved */,
    {.bitmap_index = 0, .adv_w = 66, .box_w = 1, .box_h = 1, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1, .adv_w = 93, .box_w = 2, .box_h = 11, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 4, .adv_w = 105, .box_w = 5, .box_h = 5, .ofs_x = 1, .ofs_y = 7},
    {.bitmap_index = 8, .adv_w = 154, .box_w = 9, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 21, .adv_w = 149, .box_w = 7, .box_h = 16, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 35, .adv_w = 211, .box_w = 11, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 51, .adv_w = 164, .box_w = 10, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 65, .adv_w = 62, .box_w = 2, .box_h = 5, .ofs_x = 1, .ofs_y = 7},
    {.bitmap_index = 67, .adv_w = 95, .box_w = 5, .box_h = 15, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 77, .adv_w = 95, .box_w = 5, .box_h = 15, .ofs_x = 0, .ofs_y = -3},
    {.bitmap_index = 87, .adv_w = 113, .box_w = 7, .box_h = 6, .ofs_x = 0, .ofs_y = 6},
    {.bitmap_index = 93, .adv_w = 144, .box_w = 8, .box_h = 8, .ofs_x = 1, .ofs_y = 1},
    {.bitmap_index = 101, .adv_w = 80, .box_w = 3, .box_h = 5, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 103, .adv_w = 113, .box_w = 5, .box_h = 1, .ofs_x = 1, .ofs_y = 5},
    {.bitmap_index = 104, .adv_w = 80, .box_w = 2, .box_h = 2, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 105, .adv_w = 128, .box_w = 6, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 115, .adv_w = 149, .box_w = 8, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 126, .adv_w = 149, .box_w = 5, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 133, .adv_w = 149, .box_w = 7, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 143, .adv_w = 149, .box_w = 7, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 153, .adv_w = 149, .box_w = 8, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 164, .adv_w = 149, .box_w = 7, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 174, .adv_w = 149, .box_w = 8, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 185, .adv_w = 149, .box_w = 7, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 195, .adv_w = 149, .box_w = 8, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 206, .adv_w = 149, .box_w = 8, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 217, .adv_w = 99, .box_w = 2, .box_h = 9, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 220, .adv_w = 99, .box_w = 3, .box_h = 11, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 225, .adv_w = 144, .box_w = 8, .box_h = 8, .ofs_x = 1, .ofs_y = 1},
    {.bitmap_index = 233, .adv_w = 144, .box_w = 8, .box_h = 5, .ofs_x = 1, .ofs_y = 2},
    {.bitmap_index = 238, .adv_w = 144, .box_w = 8, .box_h = 8, .ofs_x = 1, .ofs_y = 1},
    {.bitmap_index = 246, .adv_w = 112, .box_w = 7, .box_h = 11, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 256, .adv_w = 220, .box_w = 13, .box_h = 13, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 278, .adv_w = 176, .box_w = 11, .box_h = 11, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 294, .adv_w = 161, .box_w = 8, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 305, .adv_w = 154, .box_w = 8, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 316, .adv_w = 180, .box_w = 9, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 329, .adv_w = 143, .box_w = 7, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 339, .adv_w = 136, .box_w = 7, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 349, .adv_w = 176, .box_w = 9, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 362, .adv_w = 184, .box_w = 9, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 375, .adv_w = 73, .box_w = 2, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 378, .adv_w = 72, .box_w = 5, .box_h = 14, .ofs_x = -2, .ofs_y = -3},
    {.bitmap_index = 387, .adv_w = 161, .box_w = 9, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 400, .adv_w = 132, .box_w = 7, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 410, .adv_w = 217, .box_w = 11, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 426, .adv_w = 191, .box_w = 9, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 439, .adv_w = 191, .box_w = 10, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 453, .adv_w = 156, .box_w = 8, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 464, .adv_w = 191, .box_w = 10, .box_h = 13, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 481, .adv_w = 161, .box_w = 9, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 494, .adv_w = 146, .box_w = 7, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 504, .adv_w = 137, .box_w = 8, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 515, .adv_w = 182, .box_w = 9, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 528, .adv_w = 166, .box_w = 10, .box_h = 11, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 542, .adv_w = 235, .box_w = 14, .box_h = 11, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 562, .adv_w = 166, .box_w = 10, .box_h = 11, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 576, .adv_w = 158, .box_w = 10, .box_h = 11, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 590, .adv_w = 162, .box_w = 9, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 603, .adv_w = 79, .box_w = 4, .box_h = 15, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 611, .adv_w = 130, .box_w = 8, .box_h = 14, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 625, .adv_w = 79, .box_w = 4, .box_h = 15, .ofs_x = 0, .ofs_y = -3},
    {.bitmap_index = 633, .adv_w = 144, .box_w = 7, .box_h = 6, .ofs_x = 1, .ofs_y = 5},
    {.bitmap_index = 639, .adv_w = 128, .box_w = 8, .box_h = 1, .ofs_x = 0, .ofs_y = -3},
    {.bitmap_index = 640, .adv_w = 97, .box_w = 3, .box_h = 3, .ofs_x = 1, .ofs_y = 10},
    {.bitmap_index = 642, .adv_w = 157, .box_w = 8, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 651, .adv_w = 163, .box_w = 8, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 663, .adv_w = 127, .box_w = 7, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 671, .adv_w = 163, .box_w = 8, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 683, .adv_w = 149, .box_w = 8, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 692, .adv_w = 90, .box_w = 6, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 701, .adv_w = 164, .box_w = 8, .box_h = 12, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 713, .adv_w = 160, .box_w = 7, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 724, .adv_w = 70, .box_w = 2, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 727, .adv_w = 70, .box_w = 4, .box_h = 15, .ofs_x = -1, .ofs_y = -3},
    {.bitmap_index = 735, .adv_w = 137, .box_w = 7, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 746, .adv_w = 75, .box_w = 3, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 751, .adv_w = 238, .box_w = 12, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 765, .adv_w = 160, .box_w = 7, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 773, .adv_w = 158, .box_w = 8, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 782, .adv_w = 163, .box_w = 8, .box_h = 12, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 794, .adv_w = 163, .box_w = 8, .box_h = 12, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 806, .adv_w = 99, .box_w = 5, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 812, .adv_w = 124, .box_w = 6, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 819, .adv_w = 88, .box_w = 5, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 826, .adv_w = 159, .box_w = 7, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 834, .adv_w = 140, .box_w = 9, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 845, .adv_w = 216, .box_w = 13, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 860, .adv_w = 139, .box_w = 9, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 871, .adv_w = 140, .box_w = 8, .box_h = 12, .ofs_x = 0, .ofs_y = -3},
    {.bitmap_index = 883, .adv_w = 133, .box_w = 7, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 891, .adv_w = 81, .box_w = 4, .box_h = 15, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 899, .adv_w = 51, .box_w = 2, .box_h = 15, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 903, .adv_w = 81, .box_w = 4, .box_h = 15, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 911, .adv_w = 144, .box_w = 9, .box_h = 3, .ofs_x = 0, .ofs_y = 4},
    {.bitmap_index = 915, .adv_w = 252, .box_w = 12, .box_h = 15, .ofs_x = 2, .ofs_y = -2},
    {.bitmap_index = 938, .adv_w = 252, .box_w = 13, .box_h = 13, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 960, .adv_w = 252, .box_w = 13, .box_h = 14, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 983, .adv_w = 252, .box_w = 14, .box_h = 15, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 1010, .adv_w = 252, .box_w = 14, .box_h = 14, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 1035, .adv_w = 252, .box_w = 15, .box_h = 14, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 1062, .adv_w = 252, .box_w = 13, .box_h = 15, .ofs_x = 2, .ofs_y = -2},
    {.bitmap_index = 1087, .adv_w = 252, .box_w = 14, .box_h = 15, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 1114, .adv_w = 252, .box_w = 14, .box_h = 14, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 1139, .adv_w = 252, .box_w = 12, .box_h = 12, .ofs_x = 2, .ofs_y = -1},
    {.bitmap_index = 1157, .adv_w = 252, .box_w = 14, .box_h = 14, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 1182, .adv_w = 252, .box_w = 12, .box_h = 15, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 1205, .adv_w = 252, .box_w = 14, .box_h = 14, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 1230, .adv_w = 252, .box_w = 15, .box_h = 14, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 1257, .adv_w = 252, .box_w = 15, .box_h = 15, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 1286, .adv_w = 252, .box_w = 14, .box_h = 13, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 1309, .adv_w = 252, .box_w = 15, .box_h = 15, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 1338, .adv_w = 252, .box_w = 15, .box_h = 15, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 1367, .adv_w = 252, .box_w = 15, .box_h = 14, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 1394, .adv_w = 252, .box_w = 14, .box_h = 15, .ofs_x = 2, .ofs_y = -2},
    {.bitmap_index = 1421, .adv_w = 252, .box_w = 14, .box_h = 13, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 1444, .adv_w = 252, .box_w = 14, .box_h = 14, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 1469, .adv_w = 252, .box_w = 14, .box_h = 15, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 1496, .adv_w = 252, .box_w = 15, .box_h = 15, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 1525, .adv_w = 252, .box_w = 14, .box_h = 15, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 1552, .adv_w = 252, .box_w = 15, .box_h = 15, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 1581, .adv_w = 252, .box_w = 14, .box_h = 15, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 1608, .adv_w = 252, .box_w = 15, .box_h = 15, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 1637, .adv_w = 252, .box_w = 14, .box_h = 15, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 1664, .adv_w = 252, .box_w = 14, .box_h = 15, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 1691, .adv_w = 252, .box_w = 14, .box_h = 15, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 1718, .adv_w = 252, .box_w = 14, .box_h = 15, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 1745, .adv_w = 252, .box_w = 15, .box_h = 15, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 1774, .adv_w = 252, .box_w = 14, .box_h = 14, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 1799, .adv_w = 252, .box_w = 14, .box_h = 13, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 1822, .adv_w = 252, .box_w = 14, .box_h = 14, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 1847, .adv_w = 252, .box_w = 2, .box_h = 9, .ofs_x = 3, .ofs_y = 0}
};

/*---------------------
 *  CHARACTER MAPPING
 *--------------------*/

static const uint16_t unicode_list_1[] = {
    0x0, 0x81, 0x222, 0x252, 0x31c, 0x3a2, 0x3cd, 0x3ea,
    0x472, 0x5b6, 0x5ca, 0x5e0, 0x903, 0x913, 0xada, 0x1062,
    0x1079, 0x14bc, 0x175a, 0x1780, 0x1d36, 0x1eb5, 0x255a, 0x29be,
    0x2bc3, 0x2bce, 0x2cc2, 0x3a38, 0x3a43, 0x3bd3, 0x3d91, 0x3dc0,
    0x4166, 0x41dc, 0x41ed, 0x4752, 0xb0ed
};

/*Collect the unicode lists and glyph_id offsets*/
static const lv_font_fmt_txt_cmap_t cmaps[] =
{
    {
        .range_start = 32, .range_length = 95, .glyph_id_start = 1,
        .unicode_list = NULL, .glyph_id_ofs_list = NULL, .list_length = 0, .type = LV_FONT_FMT_TXT_CMAP_FORMAT0_TINY
    },
    {
        .range_start = 20013, .range_length = 45294, .glyph_id_start = 96,
        .unicode_list = unicode_list_1, .glyph_id_ofs_list = NULL, .list_length = 37, .type = LV_FONT_FMT_TXT_CMAP_SPARSE_TINY
    }
};

/*-----------------
 *    KERNING
 *----------------*/


/*Pair left and right glyphs for kerning*/
static const uint8_t kern_pair_glyph_ids[] =
{
    3, 3,
    3, 8,
    3, 13,
    3, 15,
    8, 3,
    8, 8,
    8, 13,
    8, 15,
    9, 75,
    13, 3,
    13, 8,
    13, 18,
    13, 24,
    13, 26,
    15, 3,
    15, 8,
    15, 18,
    15, 24,
    15, 26,
    16, 16,
    18, 13,
    18, 15,
    18, 27,
    18, 28,
    24, 13,
    24, 15,
    24, 27,
    24, 28,
    27, 18,
    27, 24,
    28, 18,
    28, 24,
    34, 3,
    34, 8,
    34, 36,
    34, 40,
    34, 48,
    34, 50,
    34, 53,
    34, 54,
    34, 55,
    34, 56,
    34, 58,
    34, 71,
    34, 77,
    34, 85,
    34, 87,
    34, 90,
    35, 36,
    35, 40,
    35, 48,
    35, 50,
    35, 53,
    35, 55,
    35, 57,
    35, 58,
    37, 13,
    37, 15,
    37, 34,
    37, 53,
    37, 55,
    37, 56,
    37, 57,
    37, 58,
    37, 59,
    37, 66,
    38, 75,
    39, 13,
    39, 15,
    39, 34,
    39, 66,
    39, 73,
    39, 76,
    40, 55,
    40, 58,
    43, 43,
    44, 34,
    44, 36,
    44, 40,
    44, 48,
    44, 50,
    44, 53,
    44, 54,
    44, 55,
    44, 56,
    44, 58,
    44, 68,
    44, 69,
    44, 70,
    44, 72,
    44, 77,
    44, 80,
    44, 82,
    44, 84,
    44, 85,
    44, 86,
    44, 87,
    44, 88,
    44, 90,
    45, 3,
    45, 8,
    45, 34,
    45, 36,
    45, 40,
    45, 48,
    45, 50,
    45, 53,
    45, 54,
    45, 55,
    45, 56,
    45, 58,
    45, 87,
    45, 88,
    45, 90,
    48, 13,
    48, 15,
    48, 34,
    48, 53,
    48, 55,
    48, 56,
    48, 57,
    48, 58,
    48, 59,
    48, 66,
    49, 13,
    49, 15,
    49, 34,
    49, 53,
    49, 55,
    49, 56,
    49, 57,
    49, 58,
    49, 59,
    49, 66,
    50, 13,
    50, 15,
    50, 34,
    50, 43,
    50, 53,
    50, 55,
    50, 56,
    50, 57,
    50, 58,
    50, 59,
    50, 66,
    51, 36,
    51, 40,
    51, 48,
    51, 50,
    51, 53,
    51, 54,
    51, 55,
    51, 56,
    51, 57,
    51, 58,
    51, 68,
    51, 69,
    51, 70,
    51, 72,
    51, 80,
    51, 82,
    51, 85,
    51, 86,
    51, 87,
    51, 89,
    51, 90,
    52, 13,
    52, 15,
    52, 52,
    52, 53,
    52, 55,
    52, 56,
    52, 58,
    52, 85,
    52, 87,
    52, 88,
    52, 89,
    52, 90,
    53, 3,
    53, 8,
    53, 13,
    53, 15,
    53, 34,
    53, 36,
    53, 40,
    53, 48,
    53, 50,
    53, 52,
    53, 66,
    53, 68,
    53, 69,
    53, 70,
    53, 72,
    53, 74,
    53, 75,
    53, 78,
    53, 79,
    53, 80,
    53, 81,
    53, 82,
    53, 83,
    53, 84,
    53, 85,
    53, 86,
    53, 87,
    53, 88,
    53, 89,
    53, 90,
    53, 91,
    54, 34,
    54, 57,
    54, 89,
    55, 13,
    55, 15,
    55, 27,
    55, 28,
    55, 34,
    55, 36,
    55, 40,
    55, 48,
    55, 50,
    55, 52,
    55, 66,
    55, 68,
    55, 69,
    55, 70,
    55, 72,
    55, 73,
    55, 76,
    55, 80,
    55, 82,
    55, 84,
    55, 87,
    55, 90,
    56, 13,
    56, 15,
    56, 27,
    56, 28,
    56, 34,
    56, 36,
    56, 40,
    56, 48,
    56, 50,
    56, 66,
    56, 68,
    56, 69,
    56, 70,
    56, 72,
    56, 80,
    56, 82,
    56, 84,
    57, 34,
    57, 36,
    57, 40,
    57, 48,
    57, 50,
    57, 53,
    57, 54,
    57, 55,
    57, 56,
    57, 58,
    57, 68,
    57, 69,
    57, 70,
    57, 72,
    57, 77,
    57, 80,
    57, 82,
    57, 84,
    57, 85,
    57, 86,
    57, 87,
    57, 88,
    57, 90,
    58, 3,
    58, 8,
    58, 13,
    58, 15,
    58, 27,
    58, 28,
    58, 34,
    58, 36,
    58, 40,
    58, 48,
    58, 50,
    58, 52,
    58, 66,
    58, 68,
    58, 69,
    58, 70,
    58, 71,
    58, 72,
    58, 73,
    58, 74,
    58, 76,
    58, 78,
    58, 79,
    58, 80,
    58, 81,
    58, 82,
    58, 83,
    58, 84,
    58, 85,
    58, 86,
    58, 87,
    58, 89,
    58, 90,
    58, 91,
    59, 36,
    59, 40,
    59, 48,
    59, 50,
    60, 75,
    66, 53,
    66, 55,
    66, 58,
    66, 87,
    66, 88,
    66, 90,
    67, 13,
    67, 15,
    67, 53,
    67, 55,
    67, 56,
    67, 57,
    67, 58,
    67, 87,
    67, 89,
    67, 90,
    70, 13,
    70, 15,
    70, 53,
    70, 58,
    70, 75,
    71, 3,
    71, 8,
    71, 10,
    71, 11,
    71, 13,
    71, 15,
    71, 32,
    71, 53,
    71, 55,
    71, 56,
    71, 57,
    71, 58,
    71, 62,
    71, 66,
    71, 68,
    71, 69,
    71, 70,
    71, 71,
    71, 72,
    71, 73,
    71, 74,
    71, 75,
    71, 76,
    71, 77,
    71, 80,
    71, 82,
    71, 84,
    71, 85,
    71, 87,
    71, 90,
    71, 94,
    73, 53,
    73, 58,
    73, 87,
    73, 88,
    73, 90,
    74, 3,
    74, 8,
    74, 10,
    74, 32,
    74, 53,
    74, 62,
    74, 94,
    75, 53,
    76, 53,
    76, 54,
    76, 56,
    76, 66,
    76, 68,
    76, 69,
    76, 70,
    76, 72,
    76, 77,
    76, 80,
    76, 82,
    76, 86,
    77, 71,
    77, 85,
    77, 87,
    77, 88,
    77, 90,
    78, 53,
    78, 58,
    78, 87,
    78, 88,
    78, 90,
    79, 53,
    79, 58,
    79, 87,
    79, 88,
    79, 90,
    80, 13,
    80, 15,
    80, 53,
    80, 55,
    80, 56,
    80, 57,
    80, 58,
    80, 87,
    80, 89,
    80, 90,
    81, 13,
    81, 15,
    81, 53,
    81, 55,
    81, 56,
    81, 57,
    81, 58,
    81, 87,
    81, 89,
    81, 90,
    82, 53,
    82, 58,
    82, 75,
    83, 3,
    83, 8,
    83, 13,
    83, 15,
    83, 66,
    83, 68,
    83, 69,
    83, 70,
    83, 71,
    83, 80,
    83, 82,
    83, 85,
    83, 87,
    83, 90,
    84, 53,
    84, 55,
    84, 56,
    84, 57,
    84, 58,
    84, 87,
    84, 89,
    84, 90,
    85, 71,
    85, 85,
    86, 53,
    86, 58,
    87, 13,
    87, 15,
    87, 53,
    87, 57,
    87, 66,
    87, 68,
    87, 69,
    87, 70,
    87, 80,
    87, 82,
    88, 13,
    88, 15,
    88, 53,
    88, 57,
    88, 66,
    89, 53,
    89, 54,
    89, 56,
    89, 66,
    89, 68,
    89, 69,
    89, 70,
    89, 72,
    89, 77,
    89, 80,
    89, 82,
    89, 86,
    90, 13,
    90, 15,
    90, 53,
    90, 57,
    90, 66,
    90, 68,
    90, 69,
    90, 70,
    90, 80,
    90, 82,
    91, 53,
    92, 73,
    92, 75,
    92, 76
};

/* Kerning between the respective left and right glyphs
 * 4.4 format which needs to scaled with `kern_scale`*/
static const int8_t kern_pair_values[] =
{
    -8, -10, -45, -45, -8, -10, -45, -45,
    15, -41, -41, -36, -13, -9, -41, -41,
    -36, -13, -9, -31, -23, -23, -24, -24,
    -41, -41, -23, -23, -19, -14, -19, -14,
    -26, -26, -5, -5, -5, -5, -20, -2,
    -18, -8, -22, -5, -3, -5, -5, -5,
    -2, -2, -2, -2, -10, -5, -5, -6,
    -14, -14, -5, -9, -8, -4, -6, -10,
    -5, -8, 4, -39, -39, -10, -14, 1,
    1, -4, -7, 4, -4, -6, -6, -6,
    -6, -4, -9, -8, -8, -10, -9, -9,
    -9, -9, -9, -9, -9, -4, -3, -10,
    -15, -10, -15, -24, -24, 5, -13, -13,
    -13, -13, -18, -4, -19, -9, -26, -12,
    -6, -12, -14, -14, -5, -9, -8, -4,
    -6, -10, -5, -8, -49, -49, -15, -6,
    -2, -2, -13, -5, -9, -15, -14, -14,
    -5, 4, -9, -8, -4, -6, -10, -5,
    -8, -4, -4, -4, -4, -10, -3, -6,
    -3, -6, -12, -5, -5, -5, -5, -5,
    -5, -5, -2, -3, 5, -3, -5, -5,
    -1, -2, -6, -3, -6, -1, -5, -3,
    -1, -5, 4, 4, -38, -38, -20, -5,
    -5, -5, -5, -1, -20, -14, -14, -14,
    -14, -5, -4, -14, -14, -14, -12, -14,
    -14, -15, 5, -18, -8, -4, -8, -8,
    -14, -2, -4, -1, -36, -36, -12, -12,
    -18, -8, -8, -8, -8, -3, -13, -6,
    -6, -6, -6, 2, 2, -6, -6, -6,
    -2, -2, -19, -19, -8, -8, -10, -4,
    -4, -4, -4, -10, -5, -5, -5, -5,
    -5, -5, -5, -4, -6, -6, -6, -6,
    -4, -9, -8, -8, -10, -9, -9, -9,
    -9, -9, -9, -9, -4, -3, -10, -15,
    -10, -15, 2, 2, -38, -38, -15, -15,
    -22, -10, -10, -10, -10, -1, -27, -15,
    -15, -15, -2, -15, 1, -4, 1, -12,
    -12, -15, -10, -15, -12, -17, -1, -10,
    -10, -12, -10, -12, -5, -5, -5, -5,
    20, -15, -6, -18, -3, -3, -3, -10,
    -10, -14, -7, -5, -9, -15, -3, -5,
    -3, -5, -5, -13, -10, 5, 5, 5,
    2, 17, -2, -2, 10, 10, 6, 6,
    6, 2, 7, -6, -4, -4, -4, 2,
    -8, -3, -4, -4, -3, -4, -4, -4,
    -4, 2, 1, 1, 5, -12, -8, -3,
    -1, -3, 4, 4, 4, 5, -5, 13,
    9, -5, -8, -1, -5, -5, -5, -5,
    -5, -5, -5, -5, -5, -3, -5, -1,
    -4, -2, -4, -12, -8, -3, -1, -3,
    -12, -8, -3, -1, -3, -10, -10, -14,
    -7, -5, -9, -15, -3, -5, -3, -10,
    -10, -14, -7, -5, -9, -15, -3, -5,
    -3, -4, -4, 5, 4, 4, -24, -24,
    -12, -4, -4, -4, 1, -4, -4, 5,
    1, 1, -14, -6, -5, -4, -15, -4,
    -3, -4, 1, 1, -10, -4, -23, -23,
    -8, -8, -9, -3, -3, -3, -3, -3,
    -13, -13, -4, -8, -8, -8, -1, -5,
    -5, -5, -5, -5, -5, -5, -5, -5,
    -3, -23, -23, -8, -8, -9, -3, -3,
    -3, -3, -3, -14, 4, 19, 4
};

/*Collect the kern pair's data in one place*/
static const lv_font_fmt_txt_kern_pair_t kern_pairs =
{
    .glyph_ids = kern_pair_glyph_ids,
    .values = kern_pair_values,
    .pair_cnt = 495,
    .glyph_ids_size = 0
};

/*--------------------
 *  ALL CUSTOM DATA
 *--------------------*/

#if LVGL_VERSION_MAJOR == 8
/*Store all the custom data of the font*/
static  lv_font_fmt_txt_glyph_cache_t cache;
#endif

#if LVGL_VERSION_MAJOR >= 8
static const lv_font_fmt_txt_dsc_t font_dsc = {
#else
static lv_font_fmt_txt_dsc_t font_dsc = {
#endif
    .glyph_bitmap = glyph_bitmap,
    .glyph_dsc = glyph_dsc,
    .cmaps = cmaps,
    .kern_dsc = &kern_pairs,
    .kern_scale = 16,
    .cmap_num = 2,
    .bpp = 1,
    .kern_classes = 0,
    .bitmap_format = 0,
#if LVGL_VERSION_MAJOR == 8
    .cache = &cache
#endif
};



/*-----------------
 *  PUBLIC FONT
 *----------------*/

/*Initialize a public general font descriptor*/
#if LVGL_VERSION_MAJOR >= 8
const lv_font_t ui_font_Font16 = {
#else
lv_font_t ui_font_Font16 = {
#endif
    .get_glyph_dsc = lv_font_get_glyph_dsc_fmt_txt,    /*Function pointer to get glyph's data*/
    .get_glyph_bitmap = lv_font_get_bitmap_fmt_txt,    /*Function pointer to get glyph's bitmap*/
    .line_height = 16,          /*The maximum line height required by the font*/
    .base_line = 3,             /*Baseline measured from the bottom of the line*/
#if !(LVGL_VERSION_MAJOR == 6 && LVGL_VERSION_MINOR == 0)
    .subpx = LV_FONT_SUBPX_NONE,
#endif
#if LV_VERSION_CHECK(7, 4, 0) || LVGL_VERSION_MAJOR >= 8
    .underline_position = -1,
    .underline_thickness = 1,
#endif
    .dsc = &font_dsc,          /*The custom font data. Will be accessed by `get_glyph_bitmap/dsc` */
#if LV_VERSION_CHECK(8, 2, 0) || LVGL_VERSION_MAJOR >= 9
    .fallback = NULL,
#endif
    .user_data = NULL,
};



#endif /*#if UI_FONT_FONT16*/

