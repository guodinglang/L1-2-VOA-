#include "BspConfig.h"

static uint8_t ucaSectorBuff[BSPFLASH_SECTOR_SIZE] = {0};

inline static uint32_t BspFlash_GetSector(uint32_t ulFlashAddr)
{
  return (ulFlashAddr & BSPFLASH_SECTOR_MASK);
}
//擦除目标地址所在扇区
bool BspFlash_Erase(uint32_t ulFlashAddr)
{
  flash_unlock();
  
  if(flash_sector_erase(BspFlash_GetSector(ulFlashAddr)) == false)return false;
  
  flash_lock();

  return true;
}
//随意读,只要地址合法
bool BspFlash_Read(uint32_t ulFlashAddr,uint8_t *p_Buff,uint32_t ulBuffLen)
{
  uint32_t i;
  
  if(!p_Buff)return false;
  if(!ulBuffLen)return true;
  if((ulFlashAddr+ulBuffLen) > (FLASH_BASE+BSPFLASH_SIZE))return false;

  for(i=0;i<ulBuffLen;i++)
  {
    *p_Buff++ = *(uint8_t *)ulFlashAddr++;
  }

  return true;
}
//比较两块flash数据,判断是否需要擦写
static BspFlash_CmpResult_E BspFlash_Cmp(uint32_t ulFlashAddr,uint8_t *p_Buff,uint16_t usBuffLen)
{
  uint16_t i;
  uint8_t ucByte;
  bool bEqual = true;

  if(!p_Buff)return BspFlash_CmpResult_Error;
  if(!usBuffLen)return BspFlash_CmpResult_Equal;
  if((ulFlashAddr+usBuffLen) > (FLASH_BASE+BSPFLASH_SIZE))return BspFlash_CmpResult_Error;

  for(i=0;i<usBuffLen;i++)
  {
    ucByte = *(uint8_t *)ulFlashAddr++;

    if(ucByte == p_Buff[i])
    {
      continue;
    }

    bEqual = false;

    {//编程前必须擦写,除非写入的值为全0
      if(p_Buff[i])
      {
        return BspFlash_CmpResult_Erase;
      }
    }
  }

  if(bEqual == true)
  {
    return BspFlash_CmpResult_Equal;
  }

  return BspFlash_CmpResult_Write;
}
//写入一串头尾均在同一片扇区的数据
static bool BspFlash_WriteWithinSector(uint32_t ulFlashAddr,uint8_t *p_Buff,uint16_t usBuffLen)
{
  uint16_t i;
  uint8_t ucByte;
  BspFlash_CmpResult_E CmpResult;

  if(!p_Buff)return false;
  if(!usBuffLen)return true;
  if((ulFlashAddr+usBuffLen) > (FLASH_BASE+BSPFLASH_SIZE))return false;
  //跨扇区写,返回
  if(BspFlash_GetSector(ulFlashAddr) != BspFlash_GetSector(ulFlashAddr+(usBuffLen-1)))return false;

  CmpResult = BspFlash_Cmp(ulFlashAddr,p_Buff,usBuffLen);

  switch(CmpResult)
  {
    default:break;
    case BspFlash_CmpResult_Equal:return true;
    case BspFlash_CmpResult_Write:
    {
      flash_unlock();
      
      for(i=0;i<usBuffLen;i++)
      {
        {
          ucByte = *(uint8_t *)ulFlashAddr;
          if(ucByte == p_Buff[i])
          {
            ulFlashAddr++;
            continue;
          }
        }

        if(flash_byte_program(ulFlashAddr,p_Buff[i]) != FLASH_OPERATE_DONE) 
        {
          return false;
        }
        
        ulFlashAddr++;
      }
      
      flash_lock();
    }break;
    case BspFlash_CmpResult_Erase:
    {
      memset(ucaSectorBuff,0,sizeof(ucaSectorBuff));
      
      BspFlash_Read(BspFlash_GetSector(ulFlashAddr),ucaSectorBuff,sizeof(ucaSectorBuff));

      memcpy((uint8_t *)&ucaSectorBuff[ulFlashAddr-BspFlash_GetSector(ulFlashAddr)],p_Buff,usBuffLen);

      BspFlash_Erase(ulFlashAddr);

      flash_unlock();
      
      for(i=0;i<BSPFLASH_SECTOR_SIZE;i++)
      {
        {
          ucByte = *(uint8_t *)ulFlashAddr;
          if(ucByte == ucaSectorBuff[i])
          {
            ulFlashAddr++;
            continue;
          }
        }

        if(flash_byte_program(ulFlashAddr,ucaSectorBuff[i]) != FLASH_OPERATE_DONE) 
        {
          return false;
        }

        ulFlashAddr++;
      }
      
      flash_lock();
    }break;
  }

  return true;
}
//任意写,只要地址合法
bool BspFlash_Write(uint32_t ulFlashAddr,uint8_t *p_Buff,uint32_t ulBuffLen)
{
  uint16_t usOffsetAddrInSector;//扇区内偏移地址
  uint16_t usRemainAddrInSector;
  uint16_t usNumOfSector;
  uint16_t usNumOfSingle;

  uint16_t usTemp;
  
  if(!p_Buff)return false;
  if(!ulBuffLen)return true;
  if((ulFlashAddr+ulBuffLen) > (FLASH_BASE+BSPFLASH_SIZE))return false;

  usOffsetAddrInSector = ulFlashAddr % BSPFLASH_SECTOR_SIZE;
  usRemainAddrInSector = BSPFLASH_SECTOR_SIZE - usOffsetAddrInSector;
  usNumOfSector = ulBuffLen / BSPFLASH_SECTOR_SIZE;
  usNumOfSingle = ulBuffLen % BSPFLASH_SECTOR_SIZE;

  if(usOffsetAddrInSector == 0)//起始地址位于扇区首地址
  {
    if(usNumOfSector == 0)//写入数据长度小于一个扇区
    {
      if(BspFlash_WriteWithinSector(ulFlashAddr,p_Buff,ulBuffLen) == false)return false;
    }
    else//写入数据长度大于等于一个扇区
    {
      while(usNumOfSector--)
      {
        if(BspFlash_WriteWithinSector(ulFlashAddr,p_Buff,BSPFLASH_SECTOR_SIZE) == false)return false;
        ulFlashAddr += BSPFLASH_SECTOR_SIZE;
        p_Buff += BSPFLASH_SECTOR_SIZE;
      }

      if(BspFlash_WriteWithinSector(ulFlashAddr,p_Buff,usNumOfSingle) == false)return false;
    }
  }
  else//起始地址不位于扇区首地址
  {
    if(usNumOfSector == 0)//写入数据长度小于一个扇区
    {
      if(usNumOfSingle > usRemainAddrInSector)//需要跨扇区
      {
        usTemp = usNumOfSingle - usRemainAddrInSector;//下一个扇区需要写入的数据长度

        if(BspFlash_WriteWithinSector(ulFlashAddr,p_Buff,usRemainAddrInSector) == false)return false;
        ulFlashAddr += usRemainAddrInSector;
        p_Buff += usRemainAddrInSector;

        if(BspFlash_WriteWithinSector(ulFlashAddr,p_Buff,usTemp) == false)return false;
      }
      else
      {
        if(BspFlash_WriteWithinSector(ulFlashAddr,p_Buff,ulBuffLen) == false)return false;
      }
    }
    else//写入数据长度大于等于一个扇区
    {
      ulBuffLen -= usRemainAddrInSector;
      usNumOfSector = ulBuffLen / BSPFLASH_SECTOR_SIZE;
      usNumOfSingle = ulBuffLen % BSPFLASH_SECTOR_SIZE;

      if(BspFlash_WriteWithinSector(ulFlashAddr,p_Buff,usRemainAddrInSector) == false)return false;
      ulFlashAddr += usRemainAddrInSector;
      p_Buff += usRemainAddrInSector;

      while(usNumOfSector--)
      {
        if(BspFlash_WriteWithinSector(ulFlashAddr,p_Buff,BSPFLASH_SECTOR_SIZE) == false)return false;
        ulFlashAddr += BSPFLASH_SECTOR_SIZE;
        p_Buff += BSPFLASH_SECTOR_SIZE;
      }

      if(BspFlash_WriteWithinSector(ulFlashAddr,p_Buff,usNumOfSingle) == false)return false;
    }
  }

  return true;
}
//源区域与目标区域地址不重叠且地址合法,随意复制,但是目标区域所在的扇区的其他信息会被清空...(如果存在擦除的情况下),请谨慎使用!
bool BspFlash_Copy(uint32_t ulFlashAddr_Target,uint32_t ulFlashAddr_Source,uint32_t ulCopySize,uint8_t *p_WorkBuff,uint16_t usWorkBuffSize)
{
  uint32_t ulCopySize_ThisTime;
  uint32_t ulCopySize_Already = 0;
  bool bTheLastTime = false;

  if(!ulCopySize)return true;
  if((ulFlashAddr_Target+ulCopySize) > (FLASH_BASE+BSPFLASH_SIZE))return false;
  if((ulFlashAddr_Source+ulCopySize) > (FLASH_BASE+BSPFLASH_SIZE))return false;
  if(!p_WorkBuff)return false;

  do
  {
    ulCopySize_ThisTime = ulCopySize - ulCopySize_Already;

    if(ulCopySize_ThisTime >= usWorkBuffSize)
    {
      ulCopySize_ThisTime = usWorkBuffSize;
    }

    if(ulCopySize_ThisTime == (ulCopySize - ulCopySize_Already))    
    {
      bTheLastTime = true;
    }

    if(BspFlash_Read(ulFlashAddr_Source,p_WorkBuff,ulCopySize_ThisTime) == false)return false;
    if(BspFlash_Write(ulFlashAddr_Target,p_WorkBuff,ulCopySize_ThisTime) == false)return false;

    ulFlashAddr_Source += ulCopySize_ThisTime;
    ulFlashAddr_Target += ulCopySize_ThisTime;
    ulCopySize_Already += ulCopySize_ThisTime;

    if(bTheLastTime == true)
    {
      break;
    }
  }while(1);  

  return true;
}

