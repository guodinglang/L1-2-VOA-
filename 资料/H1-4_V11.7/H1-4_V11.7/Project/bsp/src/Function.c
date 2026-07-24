#include "Function.h"
#include "includes.h"

//--------------------------------------------------------------------------
// SwitchStruct   	swMes;
SetupStruct setups;
hmiSturct hmi;
const uint8_t ucaWaveInputSource[3] = {0, 1, 2};
bool bScanCmdUppercase = false;

/***************************************************************************
;** 函数名称:  	WorkStateLED
;** 功能描述:
;** 输入参数:
;** 返 回 值:
;** 优 先 级：
;** 全局变量:
;** 调用模块:
;** 作　  者:   M-L-A
;** 日　  期:   2022-5-26
;** 修改原因：
;***************************************************************************/
void WorkStateLED(void)
{
  static uint16_t count;

  if (count > 20000)
  {
    SLED;
    count = 0;
  }
  else
  {
    count++;
  }
}

/***************************************************************************
;** 函数名称:  void SwitchMessage(void)
;** 功能描述:  switch message
;** 输入参数:
;** 返 回 值:
;** 全局变量:
;** 调用模块:
;** 作　  者:  M-L-A
;** 日　  期:  2022-2-14
;** 修改原因：
;** 说    明:
;***************************************************************************/
void SwitchMessage(void)
{
  if (BoardIndex != setups.dport)
  { // select port to default
    if (!IndexTimeDec)
    {
      BoardIndex = setups.dport;
    }
  }
  if (tPort == NULL)
  {
    tPort = pUART;
  }
  //------------------------------------------------------------------------------
  while (pDUT->len != pDUT->reTx)
  {
    if (pDUT->len > pDUT->reTx)
    {
      uint8_t s = pDUT->len - pDUT->reTx;
      tPort->send = 1; // printx(s);
      printfn(&pDUT->rxFIFO[pDUT->reTx], s);
      memset(&pDUT->rxFIFO[pDUT->reTx], 0, s);
      pDUT->reTx += s;
      if (pDUT->reTx > RX_MAX_FIFO)
      {
        pDUT->reTx = 0;
      }
      tPort->send = 0;
    }
    else
    {
      tPort->send = 1;
      printfn(&pDUT->rxFIFO[pDUT->reTx], RX_MAX_FIFO - pDUT->reTx);
      memset(&pDUT->rxFIFO[pDUT->reTx], 0, RX_MAX_FIFO - pDUT->reTx);
      pDUT->reTx = 0;
      tPort->send = 0;
    }
  }
  if (pDUT->len > 0 || pDUT->reTx > 0)
  {
    if (pDUT->len == pDUT->reTx)
    {
      pDUT->len = 0;
      pDUT->reTx = 0;
    }
  }

  //------------------------------------------------------------------------------
  while (pDUT2->len != pDUT2->reTx)
  {
    if (pDUT2->len > pDUT2->reTx)
    {
      uint16_t s = pDUT2->len - pDUT2->reTx;
      tPort->send = 1; // printx(s);
      printfn(&pDUT2->rxFIFO[pDUT2->reTx], s);
      memset(&pDUT2->rxFIFO[pDUT2->reTx], 0, s);
      pDUT2->reTx += s;
      if (pDUT2->reTx > RX_MAX_FIFO)
      {
        pDUT2->reTx = 0;
      }
      tPort->send = 0;
    }
    else
    {
      tPort->send = 1;
      printfn(&pDUT2->rxFIFO[pDUT2->reTx], RX_MAX_FIFO - pDUT2->reTx);
      memset(&pDUT2->rxFIFO[pDUT2->reTx], 0, RX_MAX_FIFO - pDUT2->reTx);
      pDUT2->reTx = 0;
      tPort->send = 0;
    }
  }
  if (pDUT2->len > 0 || pDUT2->reTx > 0)
  {
    if (pDUT2->len == pDUT2->reTx)
    {
      pDUT2->len = 0;
      pDUT2->reTx = 0;
    }
  }
}
/***************************************************************************
;** 函数名称:  void BaudrateToIndex(void)
;** 功能描述:  Baudrate To Index
;** 输入参数:
;** 返 回 值:
;** 全局变量:
;** 调用模块:
;** 作　  者:  M-L-A
;** 日　  期:  2022-2-14
;** 修改原因：
;** 说    明:
;***************************************************************************/
uint8_t BaudrateToIndex(uint32_t br)
{
  uint8_t r = 0;

  switch (br)
  {
  case 0:
    break;
  case 2400:
    r = 1;
    break;
  case 4800:
    r = 2;
    break;
  case 9600:
    r = 3;
    break;
  case 14400:
    r = 4;
    break;
  case 19200:
    r = 5;
    break;
  case 38400:
    r = 6;
    break;
  case 56000:
    r = 7;
    break;
  case 57600:
    r = 8;
    break;
  case 115200:
    r = 9;
    break;
  case 128000:
    r = 10;
    break;
  case 230400:
    r = 11;
    break;
  case 256000:
    r = 12;
    break;
  case 460800:
    r = 13;
    break;
  case 500000:
    r = 14;
    break;
  case 512000:
    r = 15;
    break;
  case 600000:
    r = 16;
    break;
  case 750000:
    r = 17;
    break;
  case 921600:
    r = 18;
    break;
  case 1000000:
    r = 19;
    break;
  case 1500000:
    r = 20;
    break;
  case 2000000:
    r = 21;
    break;
  }

  return r;
}
/***************************************************************************
;** 函数名称:  void IndexToBaudrate(void)
;** 功能描述:  IndexToBaudrate
;** 输入参数:
;** 返 回 值:
;** 全局变量:
;** 调用模块:
;** 作　  者:  M-L-A
;** 日　  期:  2022-2-14
;** 修改原因：
;** 说    明:
;***************************************************************************/
uint32_t IndexToBaudrate(uint8_t br)
{
  uint32_t r = 0;

  switch (br)
  {
  case 0:
    break;
  case 1:
    r = 2400;
    break;
  case 2:
    r = 4800;
    break;
  case 3:
    r = 9600;
    break;
  case 4:
    r = 14400;
    break;
  case 5:
    r = 19200;
    break;
  case 6:
    r = 38400;
    break;
  case 7:
    r = 56000;
    break;
  case 8:
    r = 57600;
    break;
  case 9:
    r = 115200;
    break;
  case 10:
    r = 128000;
    break;
  case 11:
    r = 230400;
    break;
  case 12:
    r = 256000;
    break;
  case 13:
    r = 460800;
    break;
  case 14:
    r = 500000;
    break;
  case 15:
    r = 512000;
    break;
  case 16:
    r = 600000;
    break;
  case 17:
    r = 750000;
    break;
  case 18:
    r = 921600;
    break;
  case 19:
    r = 1000000;
    break;
  case 20:
    r = 1500000;
    break;
  case 21:
    r = 2000000;
    break;
  }

  return r;
}
/***************************************************************************
;** 函数名称:  void SelectBaudrate(void)
;** 功能描述:  SelectBaudrate
;** 输入参数:
;** 返 回 值:
;** 全局变量:
;** 调用模块:
;** 作　  者:  M-L-A
;** 日　  期:  2022-2-14
;** 修改原因：
;** 说    明:
;***************************************************************************/
uint32_t SelectBaudrate(uint32_t br, int s)
{
  int i = 0;
  uint32_t r = 0;

  switch (br)
  {
  case 0:
    break;
  case 2400:
    i = 1;
    break;
  case 4800:
    i = 2;
    break;
  case 9600:
    i = 3;
    break;
  case 14400:
    i = 4;
    break;
  case 19200:
    i = 5;
    break;
  case 38400:
    i = 6;
    break;
  case 56000:
    i = 7;
    break;
  case 57600:
    i = 8;
    break;
  case 115200:
    i = 9;
    break;
  case 128000:
    i = 10;
    break;
  case 230400:
    i = 11;
    break;
  case 256000:
    i = 12;
    break;
  case 460800:
    i = 13;
    break;
  case 500000:
    i = 14;
    break;
  case 512000:
    i = 15;
    break;
  case 600000:
    i = 16;
    break;
  case 750000:
    i = 17;
    break;
  case 921600:
    i = 18;
    break;
  case 1000000:
    i = 19;
    break;
  case 1500000:
    i = 20;
    break;
  case 2000000:
    i = 21;
    break;

  default:
    i = -1;
    break;
  }

  i = i + s;
  if (i < 0)
  {
    i = 0;
  }

  switch (i)
  {
  case 0:
    break;
  case 1:
    r = 2400;
    break;
  case 2:
    r = 4800;
    break;
  case 3:
    r = 9600;
    break;
  case 4:
    r = 14400;
    break;
  case 5:
    r = 19200;
    break;
  case 6:
    r = 38400;
    break;
  case 7:
    r = 56000;
    break;
  case 8:
    r = 57600;
    break;
  case 9:
    r = 115200;
    break;
  case 10:
    r = 128000;
    break;
  case 11:
    r = 230400;
    break;
  case 12:
    r = 256000;
    break;
  case 13:
    r = 460800;
    break;
  case 14:
    r = 500000;
    break;
  case 15:
    r = 512000;
    break;
  case 16:
    r = 600000;
    break;
  case 17:
    r = 750000;
    break;
  case 18:
    r = 921600;
    break;
  case 19:
    r = 1000000;
    break;
  case 20:
    r = 1500000;
    break;
  case 21:
    r = 2000000;
    break;

  default:
    r = br;
    break;
  }

  return r;
}

/***************************************************************************
;** 函数名称:  void BlinkBit(void)
;** 功能描述:  BlinkBit
;** 输入参数:
;** 返 回 值: *str
;** 全局变量:
;** 调用模块:
;** 作　  者:  M-L-A
;** 日　  期:  2022-2-14
;** 修改原因：
;** 说    明:
;***************************************************************************/
void BlinkBit(uint32_t *v, char *str, uint8_t num, uint8_t loc, uint8_t *bl, int8_t as)
{
  int8_t i, k;
  uint32_t t;

  t = *v;
  for (i = 0; i < num; i++)
  {
    str[i] = (t % 10) + '0';
    t = t / 10;
  }
  i = str[loc] - '0';
  i = i + as;
  if (i < 0)
  {
    i = 9;
  }
  else if (i > 9)
  {
    i = 0;
  }
  str[loc] = i + '0';

  t = 0;
  for (i = num - 1; i >= 0; i--)
  {
    t = t * 10 + str[i] - '0';
  }
  *v = t;

  if (*bl)
  {
    *bl = 0;
  }
  else
  {
    str[loc] = ' ';
    *bl = 1;
  }

  k = num / 2;
  for (i = 0; i < k; i++)
  {
    t = str[i];
    str[i] = str[num - 1 - i];
    str[num - 1 - i] = t;
  }
}

/***************************************************************************
;** 函数名称:  void ParameterSetup(void)
;** 功能描述:  Parameter Setup
;** 输入参数:
;** 返 回 值:
;** 全局变量:
;** 调用模块:
;** 作　  者:  M-L-A
;** 日　  期:  2022-2-14
;** 修改原因：
;** 说    明:
;***************************************************************************/
void ParameterSetup(void)
{
  char /*i=0,*/ tstr[9] = {0};
  uint32_t v;

  switch (setups.step)
  {
  case 0:
    break;
  case 1:
  {
    setups.page = 0;
    SetupGUI(setups.page, BROWN, GRAY0);
    pkey->f.b.enter = false;
    setups.reel = 1;
    setups.step++;
  }
  break;

  case 2:
  { // 参数选项选择
    if (pkey->f.b.up == true)
    { // button up
      if (setups.page == 0)
      {
        setups.reel--;
        if (setups.reel > 0)
        {
          SelectMarkGUI(setups.reel, BROWN, GRAY0);
        }
        else
        {
          setups.page = 1;
          setups.reel = 9;
          SetupGUI(setups.page, BROWN, GRAY0);
          SelectMarkGUI(setups.reel, BROWN, GRAY0);
        }
      }
      else if (setups.page == 1)
      {
        setups.reel--;
        if (setups.reel > 3)
        {
          SelectMarkGUI(setups.reel, BROWN, GRAY0);
        }
        else
        {
          setups.page = 0;
          setups.reel = 3;
          SetupGUI(setups.page, BROWN, GRAY0);
          SelectMarkGUI(setups.reel, BROWN, GRAY0);
        }
      }
      pkey->f.b.up = false;
    }

    if (pkey->f.b.down == true)
    { // button down
      if (setups.page == 0)
      {
        setups.reel++;
        if (setups.reel < 4)
        {
          SelectMarkGUI(setups.reel, BROWN, GRAY0);
        }
        else
        {
          setups.page = 1;
          SetupGUI(setups.page, BROWN, GRAY0);
          setups.reel = 4;
        }
      }
      else if (setups.page == 1)
      {
        setups.reel++;
        if (setups.reel < 10)
        {
          SelectMarkGUI(setups.reel, BROWN, GRAY0);
        }
        else
        {
          setups.page = 0;
          setups.reel = 1;
          SetupGUI(setups.page, BROWN, GRAY0);
          SelectMarkGUI(setups.reel, BROWN, GRAY0);
        }
      }
      pkey->f.b.down = false;
    }

    if (pkey->f.b.enter == true)
    { // button enter
      //				SelectOptionGUI(setups.reel,BROWN,KHAKI);
      //				setups.step++;
      //
      //				setups.refresh=0;
      //
      //				if(setups.reel==2) //output endpoint
      //				{
      //					setups.index=0;
      //					v = sizeof(swMes.sv);
      //					for(i=0;i<v;i++)
      //					{swMes.sv[i]=swMes.ocr[i];}
      //				}

      pkey->f.b.enter = false;
    }

    if (pkey->f.b.esc == true)
    { // button esc
      MainGUI(GRAYBLUE, GRAY0);
      setups.step = 0;
      pkey->f.b.esc = false;
    }
  }
  break;
    //---------------------------------------------------------------------------------------
  case 3:
  { // 进入选项
    switch (setups.reel)
    {
    case 0:
      break;
    case 1:
    { // input endpoint
      if (pkey->f.b.up == true)
      {
        if (setups.speak)
        {
          BuzStart(20, 50, 3);
        }
        pkey->f.b.up = false;
      }
      if (pkey->f.b.down == true)
      {
        if (setups.speak)
        {
          BuzStart(20, 50, 3);
        }
        pkey->f.b.down = false;
      }
    }
    break;
      //---------------------------------------------------------------------------------------
    case 2:
    { // output endpoint
      //					if(pkey->f.b.enter==true)
      //					{
      //						memset(tstr,0,sizeof(tstr));
      //						tstr[0]=swMes.sv[setups.index]/10+'0';
      //						tstr[1]=swMes.sv[setups.index]%10+'0';
      //						SubSelectGUI(setups.reel,setups.index,tstr,BROWN,GRAY0);
      //						setups.digit=0;
      //
      //						if((swMes.iep[0]+swMes.iep[1]) > (swMes.oep[0]+swMes.oep[1]))
      //						{
      //							setups.index++;
      //							if(setups.index >= (swMes.oep[0]+swMes.oep[1]))
      //							{setups.index=0;}
      //						}
      //						else
      //						{
      //							setups.index++;
      //							if(setups.index >= (swMes.iep[0]+swMes.iep[1]))
      //							{setups.index=0;}
      //						}
      //
      //						pkey->f.b.enter=false;
      //					}
      //					if(pkey->f.b.up==true)
      //					{
      //						swMes.sv[setups.index]++;
      //						if(swMes.sv[setups.index] > (swMes.oep[0]+swMes.oep[1]))
      //						{swMes.sv[setups.index]=0;}
      //						setups.refresh=2;
      //
      //						pkey->f.b.up=false;
      //					}
      //					if(pkey->f.b.down==true)
      //					{
      //						if(swMes.sv[setups.index] > 0)
      //						{swMes.sv[setups.index]--;}
      //						else
      //						{swMes.sv[setups.index] = swMes.oep[0]+swMes.oep[1];}
      //						setups.refresh=2;
      //
      //						pkey->f.b.down=false;
      //					}
      //					if(pkey->time <= 0)
      //					{//闪烁
      //						memset(tstr,0,sizeof(tstr));
      //						if(setups.digit)
      //						{
      //							tstr[0] = ' ';
      //							tstr[1] = ' ';
      //							setups.digit=0;
      //						}
      //						else
      //						{
      //							tstr[0]=swMes.sv[setups.index]/10+'0';
      //							tstr[1]=swMes.sv[setups.index]%10+'0';
      //							setups.digit=1;
      //						}
      //						SubSelectGUI(setups.reel,setups.index,tstr,BROWN,GRAY0);
      //
      //						pkey->time=500;
      //					}
    }
    break;
      //---------------------------------------------------------------------------------------
    case 3:
    { // 背光
      if (pkey->f.b.up == true)
      {
        if ((pLCD->blk < 100) && (!pkey->time))
        {
          pLCD->blk++;
          SetOutputVoltageDAC1(pLCD->blk * BLK_SRV / 100 + BLK_MIN);
          SubSelectGUI(setups.reel, 0, tstr, BROWN, GRAY0);
          IICx = IIC0;
          IIC_Write_2Byte(LCD_ADD_BLK, pLCD->blk);
          pkey->f.b.down = false;
          pkey->time = 300;
        }
      }
      if (pkey->f.b.down == true)
      {
        if ((pLCD->blk > 0) && (!pkey->time))
        {
          pLCD->blk--;
          SetOutputVoltageDAC1(pLCD->blk * BLK_SRV / 100 + BLK_MIN);
          SubSelectGUI(setups.reel, 0, tstr, BROWN, GRAY0);
          IICx = IIC0;
          IIC_Write_2Byte(LCD_ADD_BLK, pLCD->blk);
          pkey->f.b.up = false;
          pkey->time = 300;
        }
      }
      if (pkey->f.b.down != true && pkey->f.b.up != true)
      {
        if (pkey->time)
        {
          pkey->time = 0;
        }
      }
    }
    break;
      //---------------------------------------------------------------------------------------
    case 4:
    { // 语言
      if (pkey->f.b.up == true)
      {
        setups.language++;
        if (setups.language > 1)
        {
          setups.language = 0;
        }
        SubSelectGUI(setups.reel, 0, tstr, BROWN, GRAY0);
        IICx = IIC0;
        IIC_Write_Data(PRG_ADD_LANGUAGE, setups.language);
        pkey->f.b.up = false;
      }
      if (pkey->f.b.down == true)
      {
        if (setups.language > 0)
        {
          setups.language--;
        }
        else
        {
          setups.language++;
        }
        SubSelectGUI(setups.reel, 0, tstr, BROWN, GRAY0);
        IICx = IIC0;
        IIC_Write_Data(PRG_ADD_LANGUAGE, setups.lock);
        pkey->f.b.down = false;
      }
      if (pkey->f.b.enter == true)
      { // 实行
        SetupGUI(setups.page, BROWN, GRAY0);
        SelectMarkGUI(setups.reel, BROWN, GRAY0);
        SelectOptionGUI(setups.reel, BROWN, KHAKI);
        SubSelectGUI(setups.reel, 0, tstr, BROWN, GRAY0);
        pkey->f.b.enter = false;
      }
    }
    break;
      //---------------------------------------------------------------------------------------
    case 5:
    { // UART
      if (pkey->f.b.up == true)
      {
        setups.brUART = SelectBaudrate(setups.brUART, 1);
        SubSelectGUI(setups.reel, 0, tstr, BROWN, GRAY0);
        //						IICx=IIC0;
        //						IIC_Write_4Byte(PRG_ADD_BR_UART,setups.brUART);
        //						usart1_config(setups.brUART);
        setups.refresh = 5;
        pkey->f.b.up = false;
      }
      if (pkey->f.b.down == true)
      {
        setups.brUART = SelectBaudrate(setups.brUART, -1);
        SubSelectGUI(setups.reel, 0, tstr, BROWN, GRAY0);
        //						IICx=IIC0;
        //						IIC_Write_4Byte(PRG_ADD_BR_UART,setups.brUART);
        //						usart1_config(setups.brUART);
        setups.refresh = 5;
        pkey->f.b.down = false;
      }
    }
    break;
      //---------------------------------------------------------------------------------------
    case 6:
    { // USB
      if (pkey->f.b.up == true)
      {
        setups.brUSB = SelectBaudrate(setups.brUSB, 1);
        SubSelectGUI(setups.reel, 0, tstr, BROWN, GRAY0);
        //						IICx=IIC0;
        //						IIC_Write_4Byte(PRG_ADD_BR_USB,setups.brUSB);
        //						usart3_config(setups.brUSB);
        setups.refresh = 6;
        pkey->f.b.up = false;
      }
      if (pkey->f.b.down == true)
      {
        setups.brUSB = SelectBaudrate(setups.brUSB, -1);
        SubSelectGUI(setups.reel, 0, tstr, BROWN, GRAY0);
        //						IICx=IIC0;
        //						IIC_Write_4Byte(PRG_ADD_BR_USB,setups.brUSB);
        //						usart3_config(setups.brUSB);
        setups.refresh = 6;
        pkey->f.b.down = false;
      }
    }
    break;
      //---------------------------------------------------------------------------------------
    case 7:
    { // IP
      if (pkey->f.b.enter == true)
      {
        setups.digit++;
        if (setups.digit > 2)
        {
          setups.digit = 0;
          pLCD->blink = 1;
          v = ethernet.ip[setups.index];
          BlinkBit(&v, tstr, 3, setups.digit, &pLCD->blink, 0);
          SubSelectGUI(setups.reel, setups.index, tstr, BROWN, GRAY0);
          if (setups.index > 0)
          {
            setups.index--;
          }
          else
          {
            setups.index = 3;
          }
        }
        pkey->f.b.enter = false;
      }
      if (pkey->f.b.up == true)
      {
        memset(tstr, 0, sizeof(tstr));
        v = ethernet.ip[setups.index];
        pLCD->blink = 1;
        BlinkBit(&v, tstr, 3, setups.digit, &pLCD->blink, 1);
        ethernet.ip[setups.index] = v;
        SubSelectGUI(setups.reel, setups.index, tstr, BROWN, GRAY0);
        IICx = IIC0;
        IIC_Write_Nbyte(ethernet.ip, ETHER_ADD_IP, 4);
        setups.refresh = 7;
        pkey->f.b.up = false;
      }
      if (pkey->f.b.down == true)
      {
        memset(tstr, 0, sizeof(tstr));
        v = ethernet.ip[setups.index];
        pLCD->blink = 1;
        BlinkBit(&v, tstr, 3, setups.digit, &pLCD->blink, -1);
        ethernet.ip[setups.index] = v;
        SubSelectGUI(setups.reel, setups.index, tstr, BROWN, GRAY0);
        IICx = IIC0;
        IIC_Write_Nbyte(ethernet.ip, ETHER_ADD_IP, 4);
        setups.refresh = 7;
        pkey->f.b.down = false;
      }
      if (pkey->time <= 0)
      { // 闪烁
        v = ethernet.ip[setups.index];
        BlinkBit(&v, tstr, 3, setups.digit, &pLCD->blink, 0);
        SubSelectGUI(setups.reel, setups.index, tstr, BROWN, GRAY0);
        pkey->time = 500;
      }
    }
    break;
      //---------------------------------------------------------------------------------------
    case 8:
    { // IP PORT
      if (pkey->f.b.enter == true)
      {
        setups.digit++;
        if (setups.digit > 3)
        {
          setups.digit = 0;
        }
        pkey->f.b.enter = false;
      }

      if (pkey->f.b.up == true)
      {
        memset(tstr, 0, sizeof(tstr));
        v = ethernet.port;
        pLCD->blink = 1;
        BlinkBit(&v, tstr, 4, setups.digit, &pLCD->blink, 1);
        ethernet.port = v;
        SubSelectGUI(setups.reel, 0, tstr, BROWN, GRAY0);
        IICx = IIC0;
        IIC_Write_2Byte(ETHER_ADD_PORT, ethernet.port);
        setups.refresh = 8;
        pkey->f.b.up = false;
      }
      if (pkey->f.b.down == true)
      {
        memset(tstr, 0, sizeof(tstr));
        v = ethernet.port;
        pLCD->blink = 1;
        BlinkBit(&v, tstr, 4, setups.digit, &pLCD->blink, -1);
        ethernet.port = v;
        SubSelectGUI(setups.reel, 0, tstr, BROWN, GRAY0);
        IICx = IIC0;
        IIC_Write_2Byte(ETHER_ADD_PORT, ethernet.port);
        setups.refresh = 8;
        pkey->f.b.down = false;
      }

      if (pkey->time <= 0)
      { // 闪烁
        v = ethernet.port;
        BlinkBit(&v, tstr, 4, setups.digit, &pLCD->blink, 0);
        SubSelectGUI(setups.reel, 0, tstr, BROWN, GRAY0);
        pkey->time = 500;
      }
    }
    break;
      //---------------------------------------------------------------------------------------
    case 9:
    { // speaker
      if (pkey->f.b.up == true)
      {
        setups.speak++;
        if (setups.speak > 1)
        {
          setups.speak = 0;
        }
        SubSelectGUI(setups.reel, 0, tstr, BROWN, GRAY0);
        IICx = IIC0;
        IIC_Write_Data(PRG_ADD_SPEAK, setups.speak);
        pkey->f.b.up = false;
      }
      if (pkey->f.b.down == true)
      {
        if (setups.speak > 0)
        {
          setups.speak--;
        }
        else
        {
          setups.speak++;
        }
        SubSelectGUI(setups.reel, 0, tstr, BROWN, GRAY0);
        IICx = IIC0;
        IIC_Write_Data(PRG_ADD_SPEAK, setups.speak);
        pkey->f.b.down = false;
      }
    }
    break;
    }
    //-------------button esc------------------------------------------------------------------------------
    if (pkey->f.b.esc == true)
    {
      //				if(setups.refresh == 2)
      //				{
      //					char j,k,x,n;
      //
      //					if((swMes.iep[0]+swMes.iep[1]) > (swMes.oep[0]+swMes.oep[1]))
      //					{n=swMes.oep[0]+swMes.oep[1];}
      //					else
      //					{n=swMes.iep[0]+swMes.iep[1];}
      //
      //					i=n; x=0;
      //					for(k=0;k<i-1;k++)
      //					{
      //						for(j=k+1;j<i;j++)
      //						{
      //							if((swMes.sv[k]==swMes.sv[j])&&(swMes.sv[k] != 0))
      //							{x++;}
      //						}
      //					}
      //					if(!x)
      //					{
      ////						memset(swMes.buf,0,sizeof(swMes.buf));
      ////						memcpy(swMes.buf,"<OSW_SW",7);
      ////						for(i=0;i<n;i++)
      ////						{sformat(swMes.buf,"_%d",swMes.sv[i]);}
      ////						swMes.step=1;
      //						if(tPort==NULL)
      //						{tPort = pUART;}
      //					}
      //				}
      //
      //				if(setups.refresh == 5)
      //				{//uart
      //					IICx=0;
      //					IIC_Write_4Byte(PRG_ADD_BR_UART,setups.brUART);
      //					if(setups.brDUT > setups.brUART)
      //					{
      //						pDUT->send=1;pDUT2->send=1;
      //						i=BaudrateToIndex(setups.brUART);
      //						sprintfx("<osw_baud_%d>",i);
      //						pDUT->send=0;pDUT2->send=0;
      //					}
      ////					else
      ////					{usart1_config(setups.brUART);}
      //				}
      //
      //				if(setups.refresh == 6)
      //				{//usb
      //					IICx=0;
      //					IIC_Write_4Byte(PRG_ADD_BR_USB,setups.brUSB);
      //					if(setups.brDUT > setups.brUSB)
      //					{
      //						pDUT->send=1;pDUT2->send=1;
      //						i=BaudrateToIndex(setups.brUSB);
      //						sprintfx("<osw_baud_%d>",i);
      //						pDUT->send=0;pDUT2->send=0;
      //					}
      ////					else
      ////					{usart3_config(setups.brUSB);}
      //				}
      //
      //				if((setups.refresh == 7)||(setups.refresh == 8))
      //				{set_w5500_netinfo();}
      //
      //				setups.refresh=0;
      //				SetupGUI(setups.page,BROWN,GRAY0);
      //				SelectMarkGUI(setups.reel,BROWN,GRAY0);
      //				setups.digit=0;
      //				pkey->time=0;
      //				setups.step--;

      pkey->f.b.esc = false;
    }
  }
  break;

  default:
    setups.step = 0;
    break;
  }
}

/***************************************************************************
;** 函数名称:  void ClrWavlenOverRangeErrorAfter(void *arg)
;** 功能描述:  稍后清除扫描参数错误
;** 输入参数:  *arg (main/主页/峰值搜索 会手动输入波长 0:main 1:主页 2:峰值搜索)
;** 返 回 值:
;** 全局变量:
;** 调用模块:
;** 作　  者:  huangjian
;** 日　  期:  2026-6-25
;** 修改原因：
;** 说    明:
;***************************************************************************/
void ClrWavlenOverRangeErrorAfter(void *arg)
{
  if (!arg)
    return;

  uint8_t ucSource = *(uint8_t *)arg;

  switch (ucSource)
  {
  default:
    break;
  case 0:
  {
    PortSelect(Port_MultiPort1);
    sprintfx("main.t9.txt=\"\"\xFF\xFF\xFF");
    sprintfx("main.x0.val=%d\xFF\xFF\xFF", hmi.ewl); // 连带还原波长显示
    PortSelect(Port_Release);
  }
  break;
  case 1:
  {
    PortSelect(Port_MultiPort1);
    sprintfx("主页.t9.txt=\"\"\xFF\xFF\xFF");
    sprintfx("主页.x0.val=%d\xFF\xFF\xFF", hmi.ewl); // 连带还原波长显示
    PortSelect(Port_Release);
  }
  break;
  case 2:
  {
    PortSelect(Port_MultiPort1);
    sprintfx("峰值搜索.t9.txt=\"\"\xFF\xFF\xFF");
    sprintfx("峰值搜索.x0.val=%d\xFF\xFF\xFF", hmi.swl); // 连带还原波长显示
    sprintfx("峰值搜索.x1.val=%d\xFF\xFF\xFF", hmi.ewl); // 连带还原波长显示
    sprintfx("峰值搜索.x2.val=%d\xFF\xFF\xFF", hmi.iwl); // 连带还原波长显示
    PortSelect(Port_Release);
  }
  break;
  }
}

/***************************************************************************
;** 函数名称:  void ScanParamInvalid(uint8_t ucSource)
;** 功能描述:  扫描参数不合理
;** 输入参数:  参数源(0:main 1:主页 2:峰值搜索)
;** 返 回 值:
;** 全局变量:
;** 调用模块:
;** 作　  者:  huangjian
;** 日　  期:  2026-6-27
;** 修改原因：
;** 说    明:
;***************************************************************************/
void ScanParamInvalid(uint8_t ucSource)
{
  if (ucSource >= sizeof(ucaWaveInputSource))
    return;

  PortSelect(Port_MultiPort1);
  if (hmi.language)
  {
    switch (ucSource)
    {
    default:
      break;
    case 0:
      sprintfx("main.t9.txt=\"Wavelength out of range\"\xFF\xFF\xFF");
      break;
    case 1:
      sprintfx("主页.t9.txt=\"Wavelength out of range\"\xFF\xFF\xFF");
      break;
    case 2:
      sprintfx("峰值搜索.t9.txt=\"Wavelength out of range\"\xFF\xFF\xFF");
      break;
    }
  }
  else
  {
    switch (ucSource)
    {
    default:
      break;
    case 0:
      sprintfx("main.t9.txt=\"波长超出范围\"\xFF\xFF\xFF");
      break;
    case 1:
      sprintfx("主页.t9.txt=\"波长超出范围\"\xFF\xFF\xFF");
      break;
    case 2:
      sprintfx("峰值搜索.t9.txt=\"波长超出范围\"\xFF\xFF\xFF");
      break;
    }
  }
  PortSelect(Port_Release);

  {
    uint16_t ucIdx = find_timer_by_callbackinfo(&tw, ClrWavlenOverRangeErrorAfter, (void *)&ucaWaveInputSource[ucSource]);

    if (ucIdx)
    {
      cancel_timer(&tw, ucIdx);
    }

    add_timer(&tw, 1000, 0, ClrWavlenOverRangeErrorAfter, (void *)&ucaWaveInputSource[ucSource]); // 1000ms后清空上述提示
  }
}

/***************************************************************************
;** 函数名称:  bool ScanExecuteCheck(void)
;** 功能描述:  跳转到执行页面前检查扫描参数是否合理
;** 输入参数:
;** 返 回 值:  true 参数合理
;** 全局变量:
;** 调用模块:
;** 作　  者:  huangjian
;** 日　  期:  2026-6-27
;** 修改原因：
;** 说    明:
;***************************************************************************/
bool ScanExecuteCheck(void)
{
  bool bExecute = false;

  do
  {
    if (InputWavLenCheck(hmi.swl) == false)
      break;
    if (InputWavLenCheck(hmi.ewl) == false)
      break;
    if (hmi.swl > hmi.ewl)
      break;

    bExecute = true;
  } while (0);

  if (bExecute == true)
  {
    PortSelect(Port_MultiPort1);
    printfx("page 7\xFF\xFF\xFF"); // 扫描页面
    PortSelect(Port_Release);
  }
  else
  {
    ScanParamInvalid(2);
  }

  return bExecute;
}

/***************************************************************************
;** 函数名称:  void ScanParamDisplay(void)
;** 功能描述:  刷新峰值搜索页面的参数
;** 输入参数:
;** 返 回 值:
;** 全局变量:
;** 调用模块:
;** 作　  者:  huangjian
;** 日　  期:  2026-6-27
;** 修改原因：
;** 说    明:
;***************************************************************************/
void ScanParamDisplay(void)
{
  PortSelect(Port_MultiPort1);
  sprintfx("峰值搜索.x0.val=%d\xFF\xFF\xFF", hmi.swl);
  sprintfx("峰值搜索.x1.val=%d\xFF\xFF\xFF", hmi.ewl);
  sprintfx("峰值搜索.x2.val=%d\xFF\xFF\xFF", hmi.iwl);

  {
    if (hmi.itim < 1)
    {
      hmi.itim = 1;
    }
    sprintfx("峰值搜索.x4.val=%d\xFF\xFF\xFF", hmi.itim);
  }

  if (hmi.language)
  {
    if (hmi.scan)
    {
      sprintfx("峰值搜索.bt0.txt=\"loop\"\xFF\xFF\xFF");
    }
    else
    {
      sprintfx("峰值搜索.bt0.txt=\"single\"\xFF\xFF\xFF");
    }
  }
  else
  {
    if (hmi.scan)
    {
      sprintfx("峰值搜索.bt0.txt=\"循环\"\xFF\xFF\xFF");
    }
    else
    {
      sprintfx("峰值搜索.bt0.txt=\"单次\"\xFF\xFF\xFF");
    }
  }
  PortSelect(Port_Release);
}

/***************************************************************************
;** 函数名称:  void ScanStateDisplay(uint8_t ucState)
;** 功能描述:  刷新搜索页面的搜索状态
;** 输入参数:  ucState(0扫描中 1中断 2完成 3错误)
;** 返 回 值:
;** 全局变量:
;** 调用模块:
;** 作　  者:  huangjian
;** 日　  期:  2026-6-27
;** 修改原因：
;** 说    明:
;***************************************************************************/
void ScanStateDisplay(uint8_t ucState)
{
  PortSelect(Port_MultiPort1);

  switch (ucState)
  {
  default:
    break;
  case 0:
  {
    if (hmi.language)
    {
      sprintfx("执行.t12.txt=\"Scanning...\"\xFF\xFF\xFF");
      sprintfx("执行.b0.txt=\"Stop\"\xFF\xFF\xFF");
    }
    else
    {
      sprintfx("执行.t12.txt=\"扫描中...\"\xFF\xFF\xFF");
      sprintfx("执行.b0.txt=\"暂停\"\xFF\xFF\xFF");
    }
  }
  break;
  case 1:
  {
    if (hmi.language)
    {
      sprintfx("执行.t12.txt=\"Terminate\"\xFF\xFF\xFF");
      sprintfx("执行.b0.txt=\"Back\"\xFF\xFF\xFF");
    }
    else
    {
      sprintfx("执行.t12.txt=\"中断\"\xFF\xFF\xFF");
      sprintfx("执行.b0.txt=\"返回\"\xFF\xFF\xFF");
    }
  }
  break;
  case 2:
  {
    if (hmi.language)
    {
      sprintfx("执行.t12.txt=\"Done\"\xFF\xFF\xFF");
      sprintfx("执行.b0.txt=\"Back\"\xFF\xFF\xFF");
    }
    else
    {
      sprintfx("执行.t12.txt=\"完成\"\xFF\xFF\xFF");
      sprintfx("执行.b0.txt=\"返回\"\xFF\xFF\xFF");
    }
  }
  break;
  case 3:
  {
    if (hmi.language)
    {
      sprintfx("执行.t12.txt=\"Error\"\xFF\xFF\xFF");
      sprintfx("执行.b0.txt=\"Back\"\xFF\xFF\xFF");
    }
    else
    {
      sprintfx("执行.t12.txt=\"参数错误\"\xFF\xFF\xFF");
      sprintfx("执行.b0.txt=\"返回\"\xFF\xFF\xFF");
    }
  }
  break;
  }

  PortSelect(Port_Release);
}

/***************************************************************************
;** 函数名称:  void dBmDisplay(uint8_t ucPage)
;** 功能描述:  刷新页面上的dBm显示值
;** 输入参数:  ucPage 页面
;** 输入参数:  ldBm 功率值(输入100实际屏幕显示1.00dBm 1.26mW (理论值1.258mW,四舍五入成1.26mW))
;** 返 回 值:
;** 全局变量:
;** 调用模块:
;** 作　  者:  huangjian
;** 日　  期:  2026-7-1
;** 修改原因：
;** 说    明:
;***************************************************************************/
void dBmDisplay(uint8_t ucPage, int32_t ldBm)
{
  PortSelect(Port_MultiPort1);

  switch (ucPage)
  {
  default:
    break;
  case 0:
  {
    double d = (double)ldBm / 100 / 10;

    sprintfx("main.x2.val=%d\xFF\xFF\xFF", ldBm);
    sprintfx("main.x5.val=%d\xFF\xFF\xFF", (int32_t)((pow(10, d) * 100) + 0.5));
  }
  break; // main
  case 5:
  {
    double d = (double)ldBm / 100 / 10;

    sprintfx("主页.x2.val=%d\xFF\xFF\xFF", ldBm);
    sprintfx("主页.x5.val=%d\xFF\xFF\xFF", (int32_t)((pow(10, d) * 100) + 0.5));
  }
  break; // 主页
  case 6:
  {
    sprintfx("峰值搜索.x2.val=%d\xFF\xFF\xFF", ldBm);
  }
  break; // 峰值搜索
  }

  PortSelect(Port_Release);
}

/***************************************************************************
;** 函数名称:  void DisplayUARTHMI(void)
;** 功能描述:   UARTHMI Display funtion
;** 输入参数:
;** 返 回 值:
;** 全局变量:
;** 调用模块:
;** 作　  者:  M-L-A
;** 日　  期:  2026-1-9
;** 修改原因：
;** 说    明:
00 FF FF FF 无效指令
01 FF FF FF 指令成功执行
02 FF FF FF 控件ID无效
03 FF FF FF 页面ID无效
04 FF FF FF 图片ID无效
05 FF FF FF 字库ID无效
06 FF FF FF 文件操作失败
09 FF FF FF CRC校验失败
11 FF FF FF 波特率设置无效
12 FF FF FF 曲线控件ID号或通道号无效
1A FF FF FF 变量名称无效
1B FF FF FF 变量运算无效
1C FF FF FF 赋值操作失败
1D FF FF FF 掉电存储空间操作失败
1E FF FF FF 参数数量无效
1F FF FF FF IO操作失败
20 FF FF FF 转义字符使用错误
23 FF FF FF 变量名称太长
24 FF FF FF 串口缓冲区溢出
0X65 控件点击事件返回
0X66 当前页面的ID号返回
0X67 触摸坐标数据返回
0X68 睡眠模式触摸事件
0X70 字符串变量数据返回
0X71 数值变量数据返回
0X86 设备自动进入睡眠模式
0X87 设备自动唤醒
0X88 系统启动成功
0X89 开始SD卡升级
0XFD 透传数据完成
0XFE 数据透传就绪
;***************************************************************************/
void DisplayUARTHMI(void)
{
  while (pMultPort1->len != pMultPort1->reTx)
  {
    if (pMultPort1->rxFIFO[pMultPort1->reTx] == 0xff)
    {
      if (++hmi.count >= 3)
      { // 结束符 0xff 0xff 0xff
        switch (hmi.buf[0])
        {
        case 0:
          break;
        case 0x65:
        { // 控件点击
          switch (hmi.buf[1])
          { // 页面
          case 0x04:
          { // 语言
            switch (hmi.buf[2])
            { // 控件
            case 0x05:
              hmi.language = hmi.buf[3];
              setups.language = hmi.language;
              IICx = IIC0;
              IIC_Write_Data(PRG_ADD_LANGUAGE, setups.language);
              break;
            }
          }
          break;
          case 0x06:
          { // 峰值搜索
            switch (hmi.buf[2])
            { // 控件
            case 0x04:
            {
              if (hmi.buf[3])
              { // 接管"执行"按钮,检查峰值搜索参数,再决定是否跳转到执行页面
                ScanExecuteCheck();
              }
            }
            break;
            }
          }
          break;
          case 0x07:
          { // 执行页面
            switch (hmi.buf[2])
            { // 控件
            case 0x01:
            {
              if (hmi.buf[3])
              {
                if (ScanerOngoingCheck() == true)
                { // 正在扫描中则取消扫描
                  PortSelect_ClrRecvFifo(Port_DUT2);
                  printfx("reset scan\r\n");
                  PortSelect(Port_Release);

                  if (PortWait(Port_DUT2, 500, 20) == true)
                  {
                    if (strstr((char *)pDUT2->rxFIFO, "pass") != 0)
                    {
                      ScanerStop();

                      ScanStateDisplay(1);
                    }
                  }
                }
                else
                { // 不在扫描则返回上一页
                  PortSelect(Port_MultiPort1);
                  printfx("page 6\xFF\xFF\xFF"); // 峰值搜索
                  PortSelect(Port_Release);
                }
              }
            }
            break;
            }
          }
          break;

          case 0x08:
          { // 系统温度
          }
          break;
          }
        }
        break;
          //-------------------------------------------------------------------
        case 0x66:
        { // 页面(静态显示的,动态刷新放在UpdateUARTHMI)
          if (hmi.buf[1] <= (uint8_t)HMI_Page_OPEN)
          {
            hmi.CurrentPage = (HMI_Page_E)hmi.buf[1];
          }

          switch (hmi.buf[1])
          {
          case 0x00:
          { // main页
            double f;

            PortSelect(Port_MultiPort1);
            sprintfx("main.x0.val=%d\xFF\xFF\xFF", hmi.ewl);
            f = hmi.ewl; // f=2.99792*pow(8)/wl
            f = f / 1000;
            f = 2.99792 / f;
            f = f * 100000;
            sprintfx("main.x3.val=%d\xFF\xFF\xFF", (uint32_t)(f * 10000));
            PortSelect(Port_Release);
          }
          break;
          case 0x05:
          { // 主页
            double f;

            PortSelect(Port_MultiPort1);
            sprintfx("主页.x0.val=%d\xFF\xFF\xFF", hmi.ewl);
            f = hmi.ewl; // f=2.99792*pow(8)/wl
            f = f / 1000;
            f = 2.99792 / f;
            f = f * 100000;
            sprintfx("主页.x3.val=%d\xFF\xFF\xFF", (uint32_t)(f * 10000));
            PortSelect(Port_Release);
          }
          break;
          case 0x06:
          { // 峰值搜索
            ScanParamDisplay();
          }
          break;
          case 0x07:
          { // 执行
            bool bSuccess = false;
            double v1, v2, v3;

            v1 = hmi.swl;
            v1 = v1 / 1000; // 三位小数点
            v2 = hmi.ewl;
            v2 = v2 / 1000;
            v3 = hmi.iwl;
            v3 = v3 / 1000;

            if (hmi.itim < 1)
              hmi.itim = 1;

            PortSelect_ClrRecvFifo(Port_DUT2);
            if (bScanCmdUppercase == true)
            {
              bScanCmdUppercase = false;
              sprintfx("SCAN %0.3lf %0.3lf %0.3lf 0 %d %d\r\n", v1, v2, v3, hmi.itim, hmi.scan);
            }
            else
            {
              sprintfx("scan %0.3lf %0.3lf %0.3lf 0 %d %d\r\n", v1, v2, v3, hmi.itim, hmi.scan);
            }
            PortSelect(Port_Release);

            if (PortWait(Port_DUT2, 500, 20) == true)
            {
              if (strstr((char *)pDUT2->rxFIFO, "pass") != 0)
              {
                bSuccess = true;
              }
            }

            if (bSuccess == true)
            {
              ScanStateDisplay(0);

              { // 通过扫描步进和波长间隔模拟进度条填充时间
                int32_t lGap;
                uint32_t ulStepNum;

                lGap = hmi.ewl;
                lGap -= hmi.swl;

                if (lGap < 0)
                  lGap = -lGap;

                ulStepNum = lGap / hmi.iwl;
                ulStepNum *= hmi.itim;
                ulStepNum /= 25;

                if (ulStepNum < 1)
                  ulStepNum = 1;

                ScanerStart(ulStepNum);
              }
            }
            else
            {
              ScanStateDisplay(3);
            }
          }
          break;
          case 0x0A:
          {   // 光谱图
            { // 测量范围
              hmi.OpticalSpectrum.ulwl_Start = CalibrationInfo.wl_min;
              hmi.OpticalSpectrum.ulwl_End = CalibrationInfo.wl_max;
              hmi.OpticalSpectrum.ulwl_Center = (CalibrationInfo.wl_min + CalibrationInfo.wl_max) / 2;
              hmi.OpticalSpectrum.ulwl_Range = CalibrationInfo.wl_max - CalibrationInfo.wl_min;

              PortSelect(Port_MultiPort1);
              sprintfx("光谱图.x0.val=%u\xFF\xFF\xFF", hmi.OpticalSpectrum.ulwl_Start);  // 开始波长
              sprintfx("光谱图.x5.val=%u\xFF\xFF\xFF", hmi.OpticalSpectrum.ulwl_End);    // 终止波长
              sprintfx("光谱图.x6.val=%u\xFF\xFF\xFF", hmi.OpticalSpectrum.ulwl_Center); // 中心波长
              sprintfx("光谱图.x7.val=%u\xFF\xFF\xFF", hmi.OpticalSpectrum.ulwl_Range);  // 波长范围
              PortSelect(Port_Release);
            }

            { // 刷新刻度
              {
                const uint8_t ucScalePointNum = 6;
                const uint8_t ucaNumberMap[ucScalePointNum] = {0, 4, 6, 8, 9, 7};

                hmi.OpticalSpectrum.sMaxdB = 0;   // Y轴刻度 最大dB填这里
                hmi.OpticalSpectrum.sMindB = -80; // Y轴刻度 最小dB填这里

                int16_t sMaxdB = hmi.OpticalSpectrum.sMaxdB;
                int16_t sMindB = hmi.OpticalSpectrum.sMindB;
                int16_t sStepdB = (sMaxdB - sMindB) / (ucScalePointNum - 1);

                int16_t sdBValue;

                PortSelect(Port_MultiPort1);
                for (uint8_t i = 0; i < ucScalePointNum; i++)
                {
                  if (i == 0)
                  {
                    sdBValue = sMindB;
                  }
                  else if (i == (ucScalePointNum - 1))
                  {
                    sdBValue = sMaxdB;
                  }
                  else
                  {
                    sdBValue = sMindB + (sStepdB * i);
                  }
                  sprintfx("光谱图.n%u.val=%d\xFF\xFF\xFF", ucaNumberMap[i], sdBValue);
                }
                PortSelect(Port_Release);
              }

              hmi.OpticalSpectrum.usGriddB = 80;
              hmi.OpticalSpectrum.usResolution = 60;
              hmi.OpticalSpectrum.usSamplePointNum = 100;
              hmi.OpticalSpectrum.usSensitivity = 50;

              PortSelect(Port_MultiPort1);
              sprintfx("光谱图.x1.val=%u\xFF\xFF\xFF", hmi.OpticalSpectrum.usGriddB);         // dB/D
              sprintfx("光谱图.x8.val=%u\xFF\xFF\xFF", hmi.OpticalSpectrum.usResolution);     // 分辨率
              sprintfx("光谱图.x9.val=%u\xFF\xFF\xFF", hmi.OpticalSpectrum.usSamplePointNum); // 采样点数
              sprintfx("光谱图.x10.val=%u\xFF\xFF\xFF", hmi.OpticalSpectrum.usSensitivity);   // 灵敏度
              PortSelect(Port_Release);

              hmi.OpticalSpectrum.ulwl_L = CalibrationInfo.wl_min;
              hmi.OpticalSpectrum.ulwl_R = CalibrationInfo.wl_max;
              hmi.OpticalSpectrum.ulwl_C = (CalibrationInfo.wl_min + CalibrationInfo.wl_max) / 2;
              hmi.OpticalSpectrum.usGridnm = (CalibrationInfo.wl_max - CalibrationInfo.wl_min) / 10; // 横向10个栅格

              PortSelect(Port_MultiPort1);
              sprintfx("光谱图.x2.val=%u\xFF\xFF\xFF", hmi.OpticalSpectrum.ulwl_L);    //
              sprintfx("光谱图.x3.val=%u\xFF\xFF\xFF", hmi.OpticalSpectrum.ulwl_C);    //
              sprintfx("光谱图.x12.val=%u\xFF\xFF\xFF", hmi.OpticalSpectrum.usGridnm); // nm/D
              sprintfx("光谱图.x4.val=%u\xFF\xFF\xFF", hmi.OpticalSpectrum.ulwl_R);    //
              PortSelect(Port_Release);
            }
          }
          case 0x0B:
          { // 维护信息
          }
          break;
          case 0x0C:
          { // 系统信息
            PortSelect(Port_MultiPort1);
            sprintfx("系统信息.t6.txt=\"%s\"\xFF\xFF\xFF", hmi.sn);
            sprintfx("系统信息.t9.txt=\"%s\"\xFF\xFF\xFF", (char *)((uint32_t)strstr(VERSION, "PRG:") + strlen("PRG:")));
            sprintfx("系统信息.t8.txt=\"%s\"\xFF\xFF\xFF", hmi.rwl);
            sprintfx("系统信息.t7.txt=\"%s\"\xFF\xFF\xFF", hmi.bb);
            sprintfx("系统信息.t10.txt=\"None\"\xFF\xFF\xFF");
            PortSelect(Port_Release);
          }
          break;
          case 0x0D:
          { // 网络协议
            PortSelect(Port_MultiPort1);
            sprintfx("网络协议.t7.txt=\"%02X-%02X-%02X-%02X-%02X-%02X\"\xFF\xFF\xFF",
                     ethernet.mac[0], ethernet.mac[1], ethernet.mac[2], ethernet.mac[3], ethernet.mac[4], ethernet.mac[5]);           // 物理地址
            sprintfx("网络协议.t8.txt=\"%d\"\xFF\xFF\xFF", ethernet.port);                                                            // 端口号
            sprintfx("网络协议.t10.txt=\"%d.%d.%d.%d\"\xFF\xFF\xFF", ethernet.ip[0], ethernet.ip[1], ethernet.ip[2], ethernet.ip[3]); // ip
            sprintfx("网络协议.t11.txt=\"%d.%d.%d.%d\"\xFF\xFF\xFF", ethernet.sm[0], ethernet.sm[1], ethernet.sm[2], ethernet.sm[3]); // 子网掩码
            sprintfx("网络协议.t12.txt=\"%d.%d.%d.%d\"\xFF\xFF\xFF", ethernet.gw[0], ethernet.gw[1], ethernet.gw[2], ethernet.gw[3]); // 网关地址
            PortSelect(Port_Release);
          }
          break;
          }
        }
        break;
          //-------------------------------------------------------------------
        case 0x70:
        { // 字符串变量数据
          switch (hmi.buf[1])
          { // 页面
          case 0x0D:
          { ////连接属性
            switch (hmi.buf[2])
            { // 控件
            case 0x08:
            { // 端口
              int k;
              sscanf(&hmi.buf[3], "%d", &k);
              ethernet.port = k;
              IICx = IIC0;
              IIC_Write_2Byte(ETHER_ADD_PORT, ethernet.port);
            }
            break;
            case 0x09:
            { // IP
              int i, k[4] = {0};
              sscanf(&hmi.buf[3], "%d.%d.%d.%d", &k[0], &k[1], &k[2], &k[3]);
              for (i = 0; i < 4; i++)
              {
                ethernet.ip[i] = k[i];
              }
              IICx = IIC0;
              IIC_Write_Nbyte(ethernet.ip, ETHER_ADD_IP, 4);
            }
            break;
            case 0x0A:
            { // sw
              int i, k[4] = {0};
              sscanf(&hmi.buf[3], "%d.%d.%d.%d", &k[0], &k[1], &k[2], &k[3]);
              for (i = 0; i < 4; i++)
              {
                ethernet.sm[i] = k[i];
              }
              IICx = IIC0;
              IIC_Write_Nbyte(ethernet.sm, ETHER_ADD_SUB, 4);
            }
            break;
            case 0x0B:
            { // gw
              int i, k[4] = {0};
              sscanf(&hmi.buf[3], "%d.%d.%d.%d", &k[0], &k[1], &k[2], &k[3]);
              for (i = 0; i < 4; i++)
              {
                ethernet.gw[i] = k[i];
              }
              IICx = IIC0;
              IIC_Write_Nbyte(ethernet.gw, ETHER_ADD_GW, 4);
            }
            break;
            }
          }
          break;
          }
        }
        break;
          //-------------------------------------------------------------------
        case 0x71:
        { // 数值变量数据
          switch (hmi.buf[1])
          { // 页面
          case 0:
          {
            switch (hmi.buf[2])
            { // 控件
            case 0x0A:
            { // 设置波长
              bool bSuccess = false;
              uint32_t ulTemp_ewl = 0;

              ulTemp_ewl |= hmi.buf[6];
              ulTemp_ewl <<= 8;
              ulTemp_ewl |= hmi.buf[5];
              ulTemp_ewl <<= 8;
              ulTemp_ewl |= hmi.buf[4];
              ulTemp_ewl <<= 8;
              ulTemp_ewl |= hmi.buf[3];

              if (InputWavLenCheck(ulTemp_ewl) == true)
              { // 波长在定标范围内
                hmi.ewl = ulTemp_ewl;

                PortSelect_ClrRecvFifo(Port_DUT2);
                sprintfx("set %0.3lf\r\n", (double)hmi.ewl / 1000);
                PortSelect(Port_Release);

                if (PortWait(Port_DUT2, 500, 20) == true)
                {
                  if (strstr((char *)pDUT2->rxFIFO, "pass") != 0)
                  {
                    bSuccess = true;
                  }
                }
              }

              if (bSuccess == false)
              { // 切换失败则提示,提示完了再还原波长
                ScanParamInvalid(0);
              }

              { // 任何时刻都换算频率
                double f;

                PortSelect(Port_MultiPort1);
                f = hmi.ewl; // f=2.99792*pow(8)/wl
                f = f / 1000;
                f = 2.99792 / f;
                f = f * 100000;
                sprintfx("main.x3.val=%d\xFF\xFF\xFF", (uint32_t)(f * 10000));
                PortSelect(Port_Release);
              }
            }
            break;
            }
          }
          break;
          case 0x05:
          { // 主页
            switch (hmi.buf[2])
            { // 控件
            case 0x01:
            { // 设置波长
              bool bSuccess = false;
              uint32_t ulTemp_ewl = 0;

              ulTemp_ewl |= hmi.buf[6];
              ulTemp_ewl <<= 8;
              ulTemp_ewl |= hmi.buf[5];
              ulTemp_ewl <<= 8;
              ulTemp_ewl |= hmi.buf[4];
              ulTemp_ewl <<= 8;
              ulTemp_ewl |= hmi.buf[3];

              if (InputWavLenCheck(ulTemp_ewl) == true)
              { // 波长在定标范围内
                hmi.ewl = ulTemp_ewl;

                PortSelect_ClrRecvFifo(Port_DUT2);
                sprintfx("set %0.3lf\r\n", (double)hmi.ewl / 1000);
                PortSelect(Port_Release);

                if (PortWait(Port_DUT2, 500, 20) == true)
                {
                  if (strstr((char *)pDUT2->rxFIFO, "pass") != 0)
                  {
                    bSuccess = true;
                  }
                }
              }

              if (bSuccess == false)
              { // 不在范围内则还原显示的波长
                ScanParamInvalid(1);
              }

              { // 任何时刻都换算频率
                double f;

                PortSelect(Port_MultiPort1);
                f = hmi.ewl; // f=2.99792*pow(8)/wl
                f = f / 1000;
                f = 2.99792 / f;
                f = f * 100000;
                sprintfx("主页.x3.val=%d\xFF\xFF\xFF", (uint32_t)(f * 10000));
                PortSelect(Port_Release);
              }
            }
            break;
            }
          }
          break;
          case 0x06:
          { // 峰值搜索
            switch (hmi.buf[2])
            {
            case 0x05:
            { // 起始波长
              uint32_t ulTemp_swl = 0;

              ulTemp_swl |= hmi.buf[6];
              ulTemp_swl <<= 8;
              ulTemp_swl |= hmi.buf[5];
              ulTemp_swl <<= 8;
              ulTemp_swl |= hmi.buf[4];
              ulTemp_swl <<= 8;
              ulTemp_swl |= hmi.buf[3];

              if (InputWavLenCheck(ulTemp_swl) == true)
              {
                if (!hmi.ewl)
                {
                  hmi.swl = ulTemp_swl;
                }
                else
                {
                  if (ulTemp_swl <= hmi.ewl)
                  {
                    hmi.swl = ulTemp_swl;
                  }
                  else
                  {
                    ScanParamInvalid(2);
                  }
                }
              }
              else
              {
                ScanParamInvalid(2);
              }
            }
            break;
            case 0x06:
            { // 结束波长
              uint32_t ulTemp_ewl = 0;

              ulTemp_ewl |= hmi.buf[6];
              ulTemp_ewl <<= 8;
              ulTemp_ewl |= hmi.buf[5];
              ulTemp_ewl <<= 8;
              ulTemp_ewl |= hmi.buf[4];
              ulTemp_ewl <<= 8;
              ulTemp_ewl |= hmi.buf[3];

              if ((InputWavLenCheck(ulTemp_ewl) == true) && (ulTemp_ewl >= hmi.swl))
              {
                hmi.ewl = ulTemp_ewl;
              }
              else
              {
                ScanParamInvalid(2);
              }
            }
            break;
            case 0x0B:
            { // 间隔波长
              int32_t ldwl;
              uint32_t ulTemp_iwl = 0;

              ulTemp_iwl |= hmi.buf[6];
              ulTemp_iwl <<= 8;
              ulTemp_iwl |= hmi.buf[5];
              ulTemp_iwl <<= 8;
              ulTemp_iwl |= hmi.buf[4];
              ulTemp_iwl <<= 8;
              ulTemp_iwl |= hmi.buf[3];

              ldwl = hmi.ewl;
              ldwl -= hmi.swl;
              if (ldwl < 0)
              {
                ldwl = -ldwl;
              }

              if (ulTemp_iwl <= ldwl)
              {
                hmi.iwl = ulTemp_iwl;
              }
              else
              {
                ScanParamInvalid(2);
              }
            }
            break;
            case 0x10:
            { // 间隔时间
              hmi.itim = 0;
              hmi.itim |= hmi.buf[4];
              hmi.itim <<= 8;
              hmi.itim |= hmi.buf[3];
              if (!hmi.itim)
              {
                hmi.itim = 1;
              }
            }
            break;
            case 0x0F:
            { // 扫描方式
              hmi.scan = hmi.buf[3];
            }
            break;
            }
          }
          break;
          case 0x09:
          { // 偏移矫正
            switch (hmi.buf[2])
            {
            case 0x05:
            {
              hmi.lCenterWavLenOffset = 0;
              hmi.lCenterWavLenOffset |= hmi.buf[6];
              hmi.lCenterWavLenOffset <<= 8;
              hmi.lCenterWavLenOffset |= hmi.buf[5];
              hmi.lCenterWavLenOffset <<= 8;
              hmi.lCenterWavLenOffset |= hmi.buf[4];
              hmi.lCenterWavLenOffset <<= 8;
              hmi.lCenterWavLenOffset |= hmi.buf[3];

              CenterWavLenOffset_Write(hmi.lCenterWavLenOffset);
            }
            break;
            }
          }
          break;
          }
        }
        break;
          //---------------------------------------------------------------
        }
        memset(hmi.buf, 0, sizeof(hmi.buf));
        hmi.len = 0;
        hmi.count = 0;
      }
    }
    else if (hmi.len < 128)
    {
      if (hmi.count > 0)
      { //
        hmi.count = 0;
        hmi.len = 0;
        memset(hmi.buf, 0, sizeof(hmi.buf));
      }
      hmi.buf[hmi.len++] = pMultPort1->rxFIFO[pMultPort1->reTx];
      pMultPort1->rxFIFO[pMultPort1->reTx] = 0;
    }
    else
    {
      hmi.count = 0;
      hmi.len = 0;
      memset(hmi.buf, 0, sizeof(hmi.buf));
    }

    pMultPort1->reTx += 1;
  }
  //--------------------------------------------------------------------------
  if ((pMultPort1->len > 0) || (pMultPort1->reTx > 0))
  {
    if (pMultPort1->len == pMultPort1->reTx)
    {
      pMultPort1->len = 0;
      pMultPort1->reTx = 0;
    }
  }
}

// --- 每 50ms 定时器调用的核心函数 ---
void Send_TOF_Spectrum_Point(void)
{
  static uint16_t tick_counter = 0;
  int y_value = 0;
  uint16_t scan_period = 600;

  // 1. 计算当前位于周期中的第几个点 (0 ~ 499 循环)
  uint16_t pos_in_cycle = tick_counter % scan_period;

  // 2. 设定波峰的“跨度”和“中心位置”
  double sigma = 12.0;

  // 将中心点固定在周期的中间位置（比如 250）
  double center_x = (double)scan_period / 2.0;

  // 3. 使用 exp 计算纯正的高斯对称响应曲线
  // 公式: y = Amplitude * exp( - (x - center)^2 / (2 * sigma^2) )
  double x_offset = (double)pos_in_cycle - center_x;

  // 指数计算 (不需要做 if-else 判断，指数自己会平滑落到基线)
  double y_float = 225.0 * exp(-(x_offset * x_offset) / (2.0 * sigma * sigma));
  y_float += 10;

  // 4. 浮点转整数
  y_value = (int)y_float;

  // 5. 极值保护 (防止溢出 255)
  if (y_value > 255)
    y_value = 255;
  if (y_value < 0)
    y_value = 0;

  // 6. 发送串口指令
  PortSelect(Port_MultiPort1);
  sprintfx("add 光谱图.s0.id,0,%d\xFF\xFF\xFF", y_value);
  PortSelect(Port_Release);

  // 7. 计数器自增 (0~65535 循环)
  tick_counter++;
}

/***************************************************************************
;** 函数名称:  void UpdateUARTHMI(void)
;** 功能描述:  周期更新串口屏的页面(后台操作触发同步控件的刷新,参数变化更新等)
;** 输入参数:
;** 返 回 值:
;** 全局变量:
;** 调用模块:
;** 作　  者:  huangjian
;** 日　  期:  2026-6-24
;** 修改原因：
;** 说    明:
;***************************************************************************/
void UpdateUARTHMI(void)
{
  static uint8_t ucUpdateDelay = 0;
  static HMI_Page_E LocalPage = HMI_Page_OPEN;

  if (LocalPage != hmi.CurrentPage)
  {
    LocalPage = hmi.CurrentPage;
    ucUpdateDelay = 10;
  }

  switch (hmi.CurrentPage)
  {
  default:
    break;
  case HMI_Page_Execute_CN:
  { // 刷新进度条?
    uint8_t ucProgress = 0;

    if (ScanerProgressCheck(&ucProgress) == true)
    {
      uint32_t ulwl_Gap = ucProgress * (hmi.ewl - hmi.swl) / 100;

      PortSelect(Port_MultiPort1);
      sprintfx("执行.x0.val=%u\xFF\xFF\xFF", hmi.swl + ulwl_Gap);
      sprintfx("执行.j0.val=%u\xFF\xFF\xFF", ucProgress);
      sprintfx("执行.x3.val=%u\xFF\xFF\xFF", ucProgress);
      PortSelect(Port_Release);

      if (ucProgress == 100)
      {
        ScanStateDisplay(2);
      }
    }
  }
  break;
  case HMI_Page_Search_CN:
  {
    if (SwitchToExecuteCheck(&bScanCmdUppercase) == true)
    {
      if (ScanExecuteCheck() == true)
      {
        ScanParamDisplay();
      }
    }
  }
  break;
  case HMI_Page_Curve:
  {
    // { // 刷新曲线
    // 	static uint16_t i = 0;

    // 	double angle = (double)i / 256 * 2 * 3.1415926;
    // 	int value = (int)((sin(angle) + 1) * 127.5);

    // 	PortSelect(Port_MultiPort1);
    // 	sprintfx("add 光谱图.s0.id,0,%u\xFF\xFF\xFF", value);
    // 	PortSelect(Port_Release);

    // 	if (++i >= 256)
    // 		i = 0;
    // }

    Send_TOF_Spectrum_Point();
  }
  break;
  case HMI_Page_Maint:
  { // 刷新维护信息(脉冲个数,温度发生变化)
    if (++ucUpdateDelay >= 20)
    {
      ucUpdateDelay = 0;

      PortSelect_ClrRecvFifo(Port_DUT2);
      printfx("srw r temp\r\n");
      PortSelect(Port_Release);

      if (PortWait(Port_DUT2, 500, 20) == true)
      {
        if (strstr((char *)pDUT2->rxFIFO, "fail"))
        {
          memcpy(hmi.temp, "25.0", strlen("25.0"));
        }
        else
        {
          memset(hmi.temp, 0, sizeof(hmi.temp));

          if (strstr((char *)pDUT2->rxFIFO, "temp") != 0)
          {
            char format[16] = {0};
            snprintf(format, sizeof(format), "%%*s %%%ds", sizeof(hmi.temp) - 1);

            sscanf((char *)pDUT2->rxFIFO, format, hmi.temp);
          }
          else
          {
            memcpy(hmi.temp, "25.0", strlen("25.0"));
          }
        }
      }

      PortSelect(Port_MultiPort1);
      sprintfx("维护信息.n1.val=%u\xFF\xFF\xFF", 1);            // 波脉冲计数器
      sprintfx("维护信息.n0.val=%u\xFF\xFF\xFF", 2);            // 频带脉冲
      sprintfx("维护信息.t6.txt=\"%s\"\xFF\xFF\xFF", hmi.temp); // 系统温度
      sprintfx("维护信息.t5.txt=\"%s\"\xFF\xFF\xFF", hmi.temp); // 主板温度
      PortSelect(Port_Release);
    }
  }
  break;
  }
}
