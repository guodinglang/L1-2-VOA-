#ifndef __BSPFLASH_H__
#define __BSPFLASH_H__

/* 对于AT32F421C8T7，    64K FLASH , 每个PAGE = 1K 字节，总共 64个 PAGE  */
/* 对于AT32F415CBT7，    128K FLASH , 每个PAGE = 1K 字节，总共 128个 PAGE  */
/* 对于AT32F415RBT7，    128K FLASH , 每个PAGE = 1K 字节，总共 128个 PAGE  */
/* 对于AT32F403ARCT7，  256K FLASH , 每个PAGE = 2K 字节，总共 128个 PAGE  */
/* 对于AT32F403ARGT7，  1024K FLASH , 每个PAGE = 2K 字节，总共 512个 PAGE  */
/* 对于AT32F435VGT7，    1024K FLASH , 每个PAGE = 2K 字节，总共 512个 PAGE  */
/* 对于AT32F437ZMT7，    4032K FLASH , 每个PAGE = 4K 字节，总共 1008个 PAGE  */

#define BSPFLASH_SIZE (128*1024)

#define BSPFLASH_SECTOR_SIZE    1024

#define BSPFLASH_SECTOR_MASK		0xFFFFFC00

typedef enum
{
  BspFlash_CmpResult_Equal = 0,/* Flash内容和待写入的数据相等,不需要擦除和写操作 */
  BspFlash_CmpResult_Write,/* Flash不需要擦除,直接写 */
  BspFlash_CmpResult_Erase,/* Flash需要先擦除,再写 */
  BspFlash_CmpResult_Error,/* 函数参数错误 */
}BspFlash_CmpResult_E;

bool BspFlash_Erase(uint32_t ulFlashAddr);
bool BspFlash_Read(uint32_t ulFlashAddr,uint8_t *p_Buff,uint32_t ulBuffLen);
bool BspFlash_Write(uint32_t ulFlashAddr,uint8_t *p_Buff,uint32_t ulBuffLen);
bool BspFlash_Copy(uint32_t ulFlashAddr_Target,uint32_t ulFlashAddr_Source,uint32_t ulCopySize,uint8_t *p_WorkBuff,uint16_t usWorkBuffSize);

#endif /*BspFlash.h*/
