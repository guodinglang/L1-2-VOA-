
#ifndef   __SPIFLASH__H__
#define   __SPIFLASH__H__

#include "project.h"

#define SPIFLASH_128
//========================================================================
//#define SPIF_CHIP_SIZE                   0x1000000
//#define SPIF_SECTOR_SIZE                 4096
//#define SPIF_PAGE_SIZE                   256

//#define SPIF_WRITEENABLE                 0x06
//#define SPIF_WRITEDISABLE                0x04
///* s7-s0 */
//#define SPIF_READSTATUSREG1              0x05
//#define SPIF_WRITESTATUSREG1             0x01
///* s15-s8 */
//#define SPIF_READSTATUSREG2              0x35
//#define SPIF_WRITESTATUSREG2             0x31
///* s23-s16 */
//#define SPIF_READSTATUSREG3              0x15
//#define SPIF_WRITESTATUSREG3             0x11

//#define SPIF_READDATA                    0x03
#define SPIF_READDATA_4B				 0x13	//Read Data with 4-Byte Address
//#define SPIF_FASTREADDATA                0x0B
#define SPIF_FASTREAD_4B                 0x0C	//Fast Read with 4-Byte Address

//#define SPIF_PAGEPROGRAM                 0x02
#define SPIF_PAGEPROGRAM_4B				 0x12	//Page Program with 4-Byte Address

/* block size:64kb */
//#define SPIF_CHIPERASE					 0xC7	//Chip Erase
#define SPIF_CHIPERASE1					 0x60	//Chip Erase
//#define SPIF_BLOCKERASE                  0xD8	//Block Erase (64KB)
#define SPIF_BLOCKERASE_4B               0xDC	//Block Erase (64KB) with 4-Byte Address
//#define SPIF_SECTORERASE                 0x20	//Sector Erase (4KB)/* 擦除扇区命令 */
#define SPIF_SECTORERASE_4B              0x21	//Sector Erase (4KB) with 4-Byte Address
//#define SPIF_POWERDOWN                   0xB9	//Power-down
//#define SPIF_RELEASEPOWERDOWN            0xAB	//Release Power-down / ID
//#define SPIF_DEVICEID                    0xAB
//#define SPIF_MANUFACTDEVICEID            0x90	//Manufacturer/Device ID
//#define SPIF_JEDECDEVICEID               0x9F	//JEDEC ID

#define	SPIF_MODE_ADD_4BYTE			     0xB7	//Enter 4-Byte Address Mode
#define	SPIF_4BYTE_MODE_EXIT			 0xE9	//Exit 4-Byte Address Mode

#define SPIF_GlobalBlockLock			 0x7E
#define SPIF_GlobalBlockUnlock			 0x98

#define SPIF_DUMMY_BYTE                  0x00	//A5/* 哑命令，可以为任意值，用于读操作 */

//========================================================================
//#define W25Q256JV_ID					 0xEF4019
#define W25Q128JV_ID					 0xEF4018

//#define SPIF_SECTION_INTERIM	  		 0x01F50000		//Block 501, 64KB
//#define SPIF_SECTION_CCH	  		     0x01F60000		//save current channel
#define SPIF_SECTION_INTERIM	  		 0xFE0000	//0xFE0000		//Block 254, 64KB
#define SPIF_SECTION_CCH	  		     0xFD0000		//save current channel 253
#define FLASH_SECTION_FACTORY     		 0xFC0000		//252
#define FLASH_SECTION_PARAMETER   		 0xFB0000		//251
#define SPIF_SECTION_FCH	  		     0xFA0000		//save factory current channel 250

#define FLASH_SECTION_LEVEL_N1  		 0x010000		//Block 1, 64KB

#define FLASH_SECTION_LEVEL_M1  		 0x020000		//Block 2, 64KB
#define FLASH_SECTION_LEVEL_M2  		 0x030000		//Block 3, 64KB
#define FLASH_SECTION_LEVEL_M3  		 0x040000		//Block 4, 64KB
#define FLASH_SECTION_LEVEL_M4  		 0x050000		//Block 5, 64KB



//========================================================================
#define SPI_FLASH_CS(n)  n>0? (GPIOB->scr = GPIO_PINS_12):(GPIOB->clr = GPIO_PINS_12)    //





//========================================================================
uint32_t spiflash_read_reg(void);
uint32_t spiflash_id(void);
void spi_flash_mode_4byte(void);
void spi_flash_erase_sector(uint32_t add);
void spi_flash_erase_block(uint32_t add);
void spi_flash_erase_chip(void);
void spi_flash_write(uint8_t *wd,uint32_t add,uint16_t num);
void spi_flash_read(uint8_t *rd,uint32_t add,uint16_t num);
int8_t StorageDevice(VOAsturct *ts);
int8_t CalculatingLevel(VOAsturct *ts);
int8_t QueryPoint(VOAsturct *ts);
int8_t stateVOA(uint8_t s);
int8_t spiflash_wait_busy(void);



#endif



