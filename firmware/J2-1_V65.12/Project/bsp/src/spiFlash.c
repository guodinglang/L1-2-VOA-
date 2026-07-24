
//#include "Initial.h"
//#include "IOstream.h"
#include "spiFlash.h"
//#include "project.h"

uint8_t spiFlash_wrByte(uint8_t d)
{
	while(spi_i2s_flag_get(SPI_SEL, SPI_I2S_TDBE_FLAG) == RESET);
	spi_i2s_data_transmit(SPI_SEL, d);
	while(spi_i2s_flag_get(SPI_SEL, SPI_I2S_RDBF_FLAG) == RESET);
	return (uint8_t)spi_i2s_data_receive(SPI_SEL);	
}

/***************************************************************************
;** 函数名称: 	
;** 功能描述:  	
;** 输入参数: 
;** 返 回 值: 
;** 全局变量: 
;** 调用模块: 
;** 作　  者:   M-L-A
;** 日　  期:  2024-2-27
;** 修改原因：
;** 说    明:
;***************************************************************************/
uint32_t spiflash_read_reg(void)
{
	uint32_t r = 0;

	SPI_FLASH_CS(0);
	spiFlash_wrByte(SPIF_READSTATUSREG1);
	r = spiFlash_wrByte(SPIF_DUMMY_BYTE);
	SPI_FLASH_CS(1);
	r <<=8;
	SPI_FLASH_CS(0);
	spiFlash_wrByte(SPIF_READSTATUSREG2);
	r |= spiFlash_wrByte(SPIF_DUMMY_BYTE);
	SPI_FLASH_CS(1);
	r <<=8;
	SPI_FLASH_CS(0);
	spiFlash_wrByte(SPIF_READSTATUSREG3);
	r |= spiFlash_wrByte(SPIF_DUMMY_BYTE);
	SPI_FLASH_CS(1);

	return r;
}

/***************************************************************************
;** 函数名称: 	
;** 功能描述:  	
;** 输入参数: 
;** 返 回 值: 
;** 全局变量: 
;** 调用模块: 
;** 作　  者:   M-L-A
;** 日　  期:  2024-2-27
;** 修改原因：
;** 说    明:
;***************************************************************************/
int8_t spiflash_wait_busy(void)
{
	int8_t r=0;
	uint16_t i;
	
	SPI_FLASH_CS(0);
	spiFlash_wrByte(SPIF_READSTATUSREG1);
	for(i=0;i<50000;i++)
	{
		r = spiFlash_wrByte(SPIF_DUMMY_BYTE);
		if((r&0x01) <=0)
		{break;}
		delay_us(10);
	}
	SPI_FLASH_CS(1);
	if(i >=50000)
	{r = -1;}
	
	return r;
}

/***************************************************************************
;** 函数名称: 	
;** 功能描述:  	
;** 输入参数: 
;** 返 回 值: 
;** 全局变量: 
;** 调用模块: 
;** 作　  者:   M-L-A
;** 日　  期:  2024-2-27
;** 修改原因：
;** 说    明:
;***************************************************************************/
uint32_t spiflash_id(void)
{
	uint32_t r = 0;

	SPI_FLASH_CS(0);
	spiFlash_wrByte(SPIF_JEDECDEVICEID);
	
	r |= spiFlash_wrByte(SPIF_DUMMY_BYTE);
	r <<=8;
	r |= spiFlash_wrByte(SPIF_DUMMY_BYTE);
	r <<=8;
	r |= spiFlash_wrByte(SPIF_DUMMY_BYTE);
	
	SPI_FLASH_CS(1);
	
	return r;
}


/***************************************************************************
;** 函数名称: 	
;** 功能描述:  	
;** 输入参数: 
;** 返 回 值: 
;** 全局变量: 
;** 调用模块: 
;** 作　  者:   M-L-A
;** 日　  期:  2024-2-27
;** 修改原因：
;** 说    明:
;***************************************************************************/
void spi_flash_mode_4byte(void)
{
	uint8_t i;
	
	SPI_FLASH_CS(0);
	spiFlash_wrByte(SPIF_READSTATUSREG3);
	i = spiFlash_wrByte(SPIF_DUMMY_BYTE);
	SPI_FLASH_CS(1);
	if((0x01 & i) <=0)
	{//4 byte setup
		SPI_FLASH_CS(0);
		spiFlash_wrByte(SPIF_MODE_ADD_4BYTE);
		SPI_FLASH_CS(1);
		if(spiflash_wait_busy() >=0)
		{
			SPI_FLASH_CS(0);
			spiFlash_wrByte(SPIF_WRITEENABLE);
			SPI_FLASH_CS(1);
			if(spiflash_wait_busy()>=0)
			{
				SPI_FLASH_CS(0);
				spiFlash_wrByte(SPIF_WRITESTATUSREG3);
				spiFlash_wrByte(i|0x02);	//ADP=1
				SPI_FLASH_CS(1);
			}
			spiflash_wait_busy();	
		}
	}
	
	SPI_FLASH_CS(1);
}


/***************************************************************************
;** 函数名称: 	
;** 功能描述:  	
;** 输入参数: 
;** 返 回 值: 
;** 全局变量: 
;** 调用模块: 
;** 作　  者:   M-L-A
;** 日　  期:  2024-2-27
;** 修改原因：
;** 说    明:	扇区：4KB;	ADD: 0x000 ~ 0xFFF
;***************************************************************************/
void spi_flash_erase_sector(uint32_t add)
{
	SPI_FLASH_CS(0);
	spiFlash_wrByte(SPIF_WRITEENABLE);
	SPI_FLASH_CS(1);
	if(spiflash_wait_busy() >=0)
	{
		SPI_FLASH_CS(0);
		#ifdef SPIFLASH_256
			spiFlash_wrByte(SPIF_SECTORERASE_4B);
			spiFlash_wrByte(add >> 24);
		#else 
			spiFlash_wrByte(SPIF_SECTORERASE);
		#endif
		spiFlash_wrByte(add >> 16);
		spiFlash_wrByte(add >> 8);
		spiFlash_wrByte(add);
		SPI_FLASH_CS(1);
		
		spiflash_wait_busy();
	}
	
	SPI_FLASH_CS(0);
	spiFlash_wrByte(SPIF_WRITEDISABLE);
	SPI_FLASH_CS(1);
}

/***************************************************************************
;** 函数名称: 	
;** 功能描述:  	
;** 输入参数: 
;** 返 回 值: 
;** 全局变量: 
;** 调用模块: 
;** 作　  者:   M-L-A
;** 日　  期:  2024-2-27
;** 修改原因：
;** 说    明: 	64KB; add-0x0000 ~ 0xFFFF
;***************************************************************************/
void spi_flash_erase_block(uint32_t add)
{
	SPI_FLASH_CS(0);
	spiFlash_wrByte(SPIF_WRITEENABLE);
	SPI_FLASH_CS(1);
	if(spiflash_wait_busy()>=0)
	{
		SPI_FLASH_CS(0);
		#ifdef SIPFLASH_256
			spiFlash_wrByte(SPIF_BLOCKERASE_4B);
			spiFlash_wrByte(add >> 24);
		#else
			spiFlash_wrByte(SPIF_BLOCKERASE);
		#endif
		spiFlash_wrByte(add >> 16);
		spiFlash_wrByte(add >> 8);
		spiFlash_wrByte(add);
		SPI_FLASH_CS(1);
		spiflash_wait_busy();
	}
	
	SPI_FLASH_CS(0);
	spiFlash_wrByte(SPIF_WRITEDISABLE);
	SPI_FLASH_CS(1);
}

/***************************************************************************
;** 函数名称: 	
;** 功能描述:  	
;** 输入参数: 
;** 返 回 值: 
;** 全局变量: 
;** 调用模块: 
;** 作　  者:   M-L-A
;** 日　  期:  2024-2-27
;** 修改原因：
;** 说    明: 	64KB; add-0x0000 ~ 0xFFFF
;***************************************************************************/
void spi_flash_erase_chip(void)
{
	SPI_FLASH_CS(0);
	spiFlash_wrByte(SPIF_WRITEENABLE);
	SPI_FLASH_CS(1);
	if(spiflash_wait_busy() >=0)
	{
		SPI_FLASH_CS(0);
		spiFlash_wrByte(SPIF_CHIPERASE);
		SPI_FLASH_CS(1);
		spiflash_wait_busy();
	}
	
	SPI_FLASH_CS(0);
	spiFlash_wrByte(SPIF_WRITEDISABLE);
	SPI_FLASH_CS(1);
}

/***************************************************************************
;** 函数名称: 	
;** 功能描述:  	
;** 输入参数: 
;** 返 回 值: 
;** 全局变量: 
;** 调用模块: 
;** 作　  者:   M-L-A
;** 日　  期:  2024-2-27
;** 修改原因：
;** 说    明: 	64KB; add-0x0000 ~ 0xFFFF
;***************************************************************************/
void spi_flash_read(uint8_t *rd,uint32_t add,uint16_t num)
{
	uint16_t i;
	
	SPI_FLASH_CS(0);
	#ifdef SPIFLASH_256
		spiFlash_wrByte(SPIF_FASTREAD_4B);
		spiFlash_wrByte(add >> 24);
	#else
		spiFlash_wrByte(SPIF_FASTREADDATA);
	#endif
	spiFlash_wrByte(add >> 16);
	spiFlash_wrByte(add >> 8);
	spiFlash_wrByte(add);
	spiFlash_wrByte(SPIF_DUMMY_BYTE);	//Fast
	
	for(i=0;i<num;i++)
	{rd[i]=spiFlash_wrByte(SPIF_DUMMY_BYTE);}
	
	SPI_FLASH_CS(1);
}

/***************************************************************************
;** 函数名称: 	
;** 功能描述:  	
;** 输入参数: 
;** 返 回 值: 
;** 全局变量: 
;** 调用模块: 
;** 作　  者:   M-L-A
;** 日　  期:  2024-2-27
;** 修改原因：
;** 说    明: Block: 64KB; add-0x0000 ~ 0xFFFF ; sector:4KB(4096) ;page:16*256
;***************************************************************************/
void spi_flash_write(uint8_t *wd,uint32_t add,uint16_t num)
{
	uint16_t i,n,s=0;
	
	do{
		SPI_FLASH_CS(0);
		spiFlash_wrByte(SPIF_WRITEENABLE);
		SPI_FLASH_CS(1);
		if(spiflash_wait_busy()>=0)
		{
			n = 256 - (((add % 65536) % 4096) % 256); //获取位置
			if(num > n)		//超页处理
			{num = num - n;}
			else
			{n = num;num = 0;}
			
			SPI_FLASH_CS(0);
			#ifdef SPIFLASH_256
				spiFlash_wrByte(SPIF_PAGEPROGRAM_4B);
				spiFlash_wrByte(add >> 24);
			#else
				spiFlash_wrByte(SPIF_PAGEPROGRAM);
			#endif
			spiFlash_wrByte(add >> 16);
			spiFlash_wrByte(add >> 8);
			spiFlash_wrByte(add);
			for(i=0;i<n;i++)
			{
				spiFlash_wrByte(wd[s++]);
				add++;
			}
			SPI_FLASH_CS(1);
			
			spiflash_wait_busy();
		}
	}while(num>0);
	
	SPI_FLASH_CS(0);
	spiFlash_wrByte(SPIF_WRITEDISABLE);
	SPI_FLASH_CS(1);
}


/***************************************************************************
;** 函数名称:  	SaveParamet
;** 功能描述:  	Flash Write Section
;** 输入参数: 	
;** 返 回 值: 	
;** 优 先 级：  
;** 全局变量: 
;** 调用模块: 
;** 作　  者:   M-L-A
;** 日　  期:   2022-5-26
;** 修改原因：
;***************************************************************************/
void ReadParamet(uint32_t d,ParameterSturct *par)
{
	W25Q128_ReadMulByte(d + 0,&par->fInitial,1);
	
	W25Q128_ReadMulByte(d + VOA_ADD_MCH,&par->cp,1);
	W25Q128_ReadMulByte(d + VOA_ADD_BR,&par->baud,1);
	memset(par->ver,0,sizeof(par->ver));
	W25Q128_ReadMulByte(d + VOA_ADD_VER,par->ver,sizeof(par->ver));
	memset(par->IDN,0,sizeof(par->IDN));
	W25Q128_ReadMulByte(d + VOA_ADD_IDN,par->IDN,sizeof(par->IDN));
	W25Q128_ReadMulByte(d + VOA_ADD_NWL,&par->nwl,1);
	W25Q128_ReadMulByte(d + VOA_ADD_MPN,(uint8_t *)&par->mpn,2);
	W25Q128_ReadMulByte(d + VOA_ADD_ID,&par->ID,1);
	W25Q128_ReadMulByte(d + VOA_ADD_SS,&par->ss,1);
	W25Q128_ReadMulByte(d + VOA_ADD_WL,(uint8_t *)&par->wl,2);
	
}	

/***************************************************************************
;** 函数名称:  	SaveParamet
;** 功能描述:  	Flash Write Section
;** 输入参数: 	
;** 返 回 值: 	
;** 优 先 级：  
;** 全局变量: 
;** 调用模块: 
;** 作　  者:   M-L-A
;** 日　  期:   2022-5-26
;** 修改原因：
;***************************************************************************/
void SaveParamet(uint32_t d,ParameterSturct *par)
{
	uint32_t addr=d; 	//FLASH_SECTION_PARAMETER;

//	spi_flash_erase_block(addr);
	W25Q128_SectorErase(addr);
	
	addr = d + 0;   //保存初始化动作
	W25Q128_ReadMulByte(addr,&par->fInitial,1);
	
	addr=d + VOA_ADD_MCH;   
	W25Q128_ReadMulByte(addr,&par->cp,1);
	
	addr=d + VOA_ADD_BR;   
	W25Q128_ReadMulByte(addr,&par->baud,1);
	
	addr=d + VOA_ADD_VER;   
	W25Q128_ReadMulByte(addr,par->ver,sizeof(par->ver));
	
	addr=d + VOA_ADD_IDN;   
	W25Q128_ReadMulByte(addr,par->IDN,sizeof(par->IDN));
	
	addr=d + VOA_ADD_NWL;   
	W25Q128_ReadMulByte(addr,&par->nwl,1);
		
	addr=d + VOA_ADD_MPN;   
	W25Q128_ReadMulByte(addr,(uint8_t *)&par->mpn,2);
	
	addr=d + VOA_ADD_ID;   
	W25Q128_ReadMulByte(addr,&par->ID,1);
	
	addr=d + VOA_ADD_SS;   
	W25Q128_ReadMulByte(addr,&par->ss,1);
	
	addr=d + VOA_ADD_WL;   
	W25Q128_ReadMulByte(addr,(uint8_t *)&par->wl,2);
	
}


/***************************************************************************
;** 函数名称: 	
;** 功能描述:  	
;** 输入参数: sq-sequence; cp-component; vo-voltage; wl-wavelenght; db-DB
;** 返 回 值: 
;** 全局变量: 
;** 调用模块: 
;** 作　  者:   M-L-A
;** 日　  期:  2024-2-27
;** 修改原因：
;** 说    明: 	64KB; add-0x0000 ~ 0xFFFF;	64KB = 16*4KB; 256b= 512*64KB*8*1024

Point:10 Byte; 
sector(4KB): 400 Point; 
Block: 16 WaveLenght + 400 Point
	
可存500个VOA器件,每个VOA器件可存16种不同波长，每种波长可存400点;

;***************************************************************************/
int8_t StorageDevice(VOAsturct *ts)
{
	uint8_t *tp,tar[10]={0};
	uint16_t i;
	uint32_t add=0;
	
	if((ts->cp >0)&&(ts->wp >0))
	{
		add = 65536 * (ts->cp -1);	//cp 器件基地址
		add += 4096 * (ts->wp -1);		//wp 波长基地址
		
		W25Q128_SectorErase(SPIF_SECTION_INTERIM);  // 备份存储tp
		for(i=0;i<406;i++)
		{
			W25Q128_ReadMulByte(add+i*10,tar,10);
			W25Q128_WriteMulByte(SPIF_SECTION_INTERIM+i*10,tar,10);
		}
		W25Q128_SectorErase(add);
		
		for(i=0;i<ts->sq;i++)
		{
			W25Q128_ReadMulByte(SPIF_SECTION_INTERIM + i*10,tar,10);
			W25Q128_WriteMulByte(add + i*10,tar,10);
		}
		memset(tar,0,sizeof(tar));
		tar[0]=ts->vo>>8;
		tar[1]=ts->vo;
		tar[2]=ts->wl>>8;
		tar[3]=ts->wl;
		tp=(uint8_t *)&ts->db;
		tar[4]=tp[0];
		tar[5]=tp[1];
		tar[6]=tp[2];
		tar[7]=tp[3];
		W25Q128_WriteMulByte(add + ts->sq*10,tar,10);
		
		for(i++;i<406;i++)
		{
			W25Q128_ReadMulByte(SPIF_SECTION_INTERIM + i*10,tar,10);
			W25Q128_WriteMulByte(add + i*10,tar,10);
		}
	}
	
	return 0;
	
}

/***************************************************************************
;** 函数名称: 	
;** 功能描述:  	
;** 输入参数: sq-sequence; cp-component; vo-voltage; wl-wavelenght; db-DB
;** 返 回 值: 
;** 全局变量: 
;** 调用模块: 
;** 作　  者:   M-L-A
;** 日　  期:  2024-2-27
;** 修改原因：
;** 说    明: 	64KB; add-0x0000 ~ 0xFFFF;	64KB = 16*4KB; 256b= 512*64KB*8*1024

Point:10 Byte; 
sector(4KB): 400 Point; 
Block: 16 WaveLenght + 400 Point
	
可存500个VOA器件,每个VOA器件可存16种不同波长，每种波长可存400点;

;***************************************************************************/
int8_t CalculatingLevel(VOAsturct *ts)
{
	int8_t r;
	uint8_t j,*tp,tar[10]={0};
	uint16_t i,n;
	uint32_t add=0,ra;
	float db,fv;
	
	if(ts->cp >0)
	{
		r = -1;
		add = 65536 * (ts->cp -1);	//器件在block;
		for(i=0;i<params.nwl;i++)
		{//获取波长位置
			r = 0;
			ra = add + 4096*i;
			for(j=0;j<3;j++)
			{
				memset(tar,0,10);
				W25Q128_ReadMulByte(ra+j*10,tar,10);	
				n = (tar[2]<<8)|tar[3];
				if(n>0 && n<0xffff)
				{
					if(ts->wl == n)
					{r++;}
				}
			}
			if(r >1) //3次2胜
			{add = ra;ts->wp = i+1;break;}
			else
			{r = -1;}
		}
		if(r > 0)
		{
			uint16_t m,x;
			fv = 0.0;n=0;r=-1;
			tp = (uint8_t *)&db;
			for(i=0;i<=params.mpn;i++)
			{//计算DAC电压
				memset(tar,0,10);
				ra = add + 10*i;
				W25Q128_ReadMulByte(ra,tar,10);
				if((tar[4]&tar[5]&tar[6]&tar[7]) != 0xff)
				{
					tp[0]=tar[4]; 
					tp[1]=tar[5]; 
					tp[2]=tar[6]; 
					tp[3]=tar[7]; 		
					if(db >= ts->db)
					{
						m = (tar[0]<<8)|tar[1];
						x = (ts->db - fv)*(m - n)/(db-fv);	
						if(abs(n+x)<=0)
						{ts->vo = m;}
						else
						{ts->vo = n+x;}
						ts->sq = i;
						r = 0; 			//sprintfx("v %d\r\n",ts->vo);
						break;
					}
					else
					{fv = db; n = (tar[0]<<8)|tar[1];}
				}
			}
		}
		else
		{ts->vo = 0;r = -1;}	//未找到
	}
	return r;
}

/***************************************************************************
;** 函数名称: 	
;** 功能描述:  	
;** 输入参数: sq-sequence; cp-component; vo-voltage; wl-wavelenght; db-DB
;** 返 回 值: 
;** 全局变量: 
;** 调用模块: 
;** 作　  者:   M-L-A
;** 日　  期:  2024-2-27
;** 修改原因：
;** 说    明: 	64KB; add-0x0000 ~ 0xFFFF;	64KB = 16*4KB; 256b= 512*64KB*8*1024

Point:10 Byte; 
sector(4KB): 400 Point; 
Block: 16 WaveLenght + 400 Point
	
可存500个VOA器件,每个VOA器件可存16种不同波长，每种波长可存400点;

;***************************************************************************/
int8_t QueryPoint(VOAsturct *ts)
{
	int8_t r = 0;
	uint8_t *tp,tar[10]={0};
	uint32_t add=0;
	float db;
	
	if((ts->cp >0)&&(ts->wp >0))
	{
		add = 65536 * (ts->cp -1);	//器件在block;
		add += 4096*(ts->wp -1);
		add += ts->sq*10;
		
		memset(tar,add,10);
		W25Q128_ReadMulByte(add,tar,10);
		ts->vo = (tar[0]<<8)|tar[1];
		if(ts->vo >0x7FFF)
		{ts->vo = 0;r = -1;}
		ts->wl = (tar[2]<<8)|tar[3];
		if(ts->wl >=0xffff)
		{ts->wl = 0;r = -1;}
		tp = (uint8_t *)&db;
		tp[0]=tar[4];
		tp[1]=tar[5];
		tp[2]=tar[6];
		tp[3]=tar[7];
		if(db >=0.0f)
		{ts->db = db;}
		else
		{r = -1;}
	}
	else
	{r = -1;}
	
//	for(i=0;i<params.nwl;i++)
//	{//获取波长位置
//		memset(tar,0,10);
//		ra = add + 4096*i;
//		spi_flash_read(tar,ra,10);
//		if(ts->wl == ((tar[2]<<8)|tar[3]))
//		{
//			ts->wp = i;	//波长位置
//			add = ra;
//			r=1;
//			break;
//		}
//	}	
	
//	if(r > 0)
//	{
//		tp = (uint8_t *)&db;
//		ra = add + ts->sq*10;
//		spi_flash_read(tar,ra,10);
//		tp[0]=tar[4];
//		tp[1]=tar[5];
//		tp[2]=tar[6];
//		tp[3]=tar[7];
//		if(db >=0.0f)
//		{ts->db = db;}
//		ts->vo = (tar[0]<<8)|tar[1];
//		if(ts->vo >0x7FFF)
//		{ts->vo = 0;}
//		r=0;
//	}
//	else
//	{//未找到	
//		memset(ts,0,sizeof(VOAsturct));
//		r = -1;
//	}	
	
	return r;
}


/***************************************************************************
;** 函数名称: 	
;** 功能描述:  	
;** 输入参数: c--'w'/'r'/'c'
;** 返 回 值: 0--OK
;** 全局变量: 
;** 调用模块: 
;** 作　  者:   M-L-A
;** 日　  期:  2024-2-27
;** 修改原因：
;** 说    明: 	64KB; add-0x0000 ~ 0xFFFF;	64KB = 16*4KB; 256b= 512*64KB*8*1024

;***************************************************************************/
int8_t stateVOA(uint8_t s)
{
	uint8_t r=0,*tp,tar[10]={0};
	uint16_t i;
	uint32_t add = SPIF_SECTION_CCH;
	
	if(s=='w')
	{
		W25Q128_SectorErase(add);
		for(i=0;i<params.cp;i++)
		{
			memset(tar,0,sizeof(tar));
			tar[0]=sVOA[i].vo>>8;
			tar[1]=sVOA[i].vo;
			tar[2]=sVOA[i].wl>>8;
			tar[3]=sVOA[i].wl;
			tp=(uint8_t *)&sVOA[i].db;
			tar[4]=tp[0];
			tar[5]=tp[1];
			tar[6]=tp[2];
			tar[7]=tp[3];
			W25Q128_WriteMulByte(add + i*10,tar,10);
		}
		
		params.ss = 1; //保存状态位
		W25Q128_SaveParamet(FLASH_SECTION_PARAMETER,(uint8_t *)&params);
	}
	else if(s=='r')
	{
		for(i=0;i<params.cp;i++)
		{
			memset(tar,0,sizeof(tar));
			W25Q128_ReadMulByte(add + i*10,tar,10);
			
			sVOA[i].vo = (tar[0]<<8)|tar[1];
			sVOA[i].wl = (tar[2]<<8)|tar[3];
			tp=(uint8_t *)&sVOA[i].db;
			tp[0]=tar[4];
			tp[1]=tar[5];
			tp[2]=tar[6];
			tp[3]=tar[7];
		}
	}
	else if(s=='c')
	{
		W25Q128_SectorErase(add);
		for(i=0;i<params.cp;i++)
		{
			memset(&sVOA[i],0,sizeof(sVOA[i]));
			sVOA[i].cp = i+1;
		} 
		
		params.ss = 0;
		W25Q128_SaveParamet(FLASH_SECTION_PARAMETER,(uint8_t *)&params);
	}
	else
	{r=1;}
	
	return r;
}










