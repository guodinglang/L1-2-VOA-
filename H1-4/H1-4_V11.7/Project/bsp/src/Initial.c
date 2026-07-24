
/****************************************************************************************
 *
 *	模块名称 : BSP(Board Support Package)
 *	文件名称 :
 *	版    本 : V0.1
 *	说    明 : BSP 板级支持包(Board Support Package)
 *	修改记录 :
 *   版 本 号 :
 *   日    期 :
 *   作    者 :
 *	说    明 :
 *
 *****************************************************************************************/

#include "Initial.h"
#include "includes.h"

//--------------------------------------------------------------------------
uint8_t BoardIndex = 0;
uint32_t IndexTimeDec = 0;
SturctTOF TOF;

// LevelSturct  sLevel[LEVEL_NUM];	//

/***************************************************************************
;** 函数名称: 	SysTickConfigure
;** 功能描述:   SysTick Time Configure
;** 输入参数:
;** 返 回 值:
;** 全局变量:
;** 调用模块:
;** 作　  者:   M-L-A
;** 日　  期:  2022-5-26
;** 修改原因:
;** 说    明:
;***************************************************************************/
void SysTickConfigure(void)
{
  /* configure systick */
  systick_clock_source_config(SYSTICK_CLOCK_SOURCE_AHBCLK_NODIV);
  //  SysTick->LOAD = (uint32_t)(system_core_clock / (1000U));
  //  SysTick->VAL = 0x00;
  //  SysTick->CTRL |= SysTick_CTRL_ENABLE_Msk ;
  SysTick_Config(system_core_clock / 1000U); // 1ms
}

/***************************************************************************
;** 函数名称: 	configWDT
;** 功能描述:   config WDT
;** 输入参数:
;** 返 回 值:
;** 全局变量:
;** 调用模块:
;** 作　  者:   M-L-A
;** 日　  期:  2022-5-26
;** 修改原因:
;** 说    明:
;***************************************************************************/
void configWDT(uint16_t d)
{
  /* reset from wdt */
  crm_flag_clear(CRM_WDT_RESET_FLAG);
  /* disable register write protection */
  wdt_register_write_enable(TRUE);

  /* set the wdt divider value */
  wdt_divider_set(WDT_CLK_DIV_32); // 0.8ms*d

  /* set reload value

  timeout = reload_value * (divider / lick_freq )    (s)

  lick_freq    = 40000 Hz
  divider      = 64		//1.6ms*d
  reload_value = d		//12bit=4095

  timeout = d * (64 / 40000 ) = max:6.552s = 6552ms
  */
  wdt_reload_value_set(d - 1);

  /* reload wdt counter */
  wdt_counter_reload();

  /* enable wdt */
  wdt_enable();
}

/***************************************************************************
;** 函数名称:
;** 功能描述:  取出EEPRAM 数据
;** 输入参数:
;** 返 回 值:
;** 全局变量:
;** 调用模块:
;** 作　  者:   M-L-A
;** 日　  期:  2013-4-17
;** 修改原因：
;** 说    明:  	AT24C256	  (65535 byte )
;***************************************************************************/
void epramInitialize(void)
{
#ifdef SimulateIIC1

  //	uint8_t i;

  IICx = IIC0;
  if (0x11 != IIC_Read_Data(0))
  {
    IIC_Write_Data(0, 0x11);

    ethernet.mac[0] = 0;
    ethernet.mac[1] = 8;
    ethernet.mac[2] = 220;
    ethernet.mac[3] = 17;
    ethernet.mac[4] = 17;
    ethernet.mac[5] = 17;
    IIC_Write_Nbyte(ethernet.mac, ETHER_ADD_MAC, 6);
    ethernet.ip[0] = 192;
    ethernet.ip[1] = 168;
    ethernet.ip[2] = 1;
    ethernet.ip[3] = 188;
    IIC_Write_Nbyte(ethernet.ip, ETHER_ADD_IP, 4);
    ethernet.sm[0] = 255;
    ethernet.sm[1] = 255;
    ethernet.sm[2] = 255;
    ethernet.sm[3] = 0;
    IIC_Write_Nbyte(ethernet.sm, ETHER_ADD_SUB, 4);
    ethernet.gw[0] = 192;
    ethernet.gw[1] = 168;
    ethernet.gw[2] = 1;
    ethernet.gw[3] = 1;
    IIC_Write_Nbyte(ethernet.gw, ETHER_ADD_GW, 4);
    ethernet.dns[0] = 114;
    ethernet.dns[1] = 114;
    ethernet.dns[2] = 114;
    ethernet.dns[3] = 114;
    IIC_Write_Nbyte(ethernet.dns, ETHER_ADD_DNS, 4);
    ethernet.rip[0] = 192;
    ethernet.rip[1] = 168;
    ethernet.rip[2] = 1;
    ethernet.rip[3] = 100;
    IIC_Write_Nbyte(ethernet.rip, ETHER_ADD_RIP, 4);
    ethernet.port = 1000;
    IIC_Write_2Byte(ETHER_ADD_PORT, ethernet.port);
    ethernet.sw_ver[0] = 0;
    ethernet.sw_ver[1] = 1;
    IIC_Write_Nbyte(ethernet.sw_ver, ETHER_ADD_VER, 2);

    pLCD->blk = 50;
    IIC_Write_2Byte(LCD_ADD_BLK, pLCD->blk);

    setups.lock = 0;
    IIC_Write_Data(PRG_ADD_LOCK, setups.lock);
    setups.scan = 0;
    IIC_Write_Data(PRG_ADD_SCAN, setups.scan);
    setups.Tgap = 500;
    IIC_Write_4Byte(PRG_ADD_GAP, setups.Tgap);
    setups.sch = 0;
    IIC_Write_2Byte(PRG_ADD_SCH, setups.sch);
    setups.ech = 8;
    IIC_Write_2Byte(PRG_ADD_ECH, setups.ech);
    setups.language = 0;
    IIC_Write_Data(PRG_ADD_LANGUAGE, setups.language);
    setups.brUART = 115200;
    IIC_Write_4Byte(PRG_ADD_BR_UART, setups.brUART);
    setups.brUSB = 115200;
    IIC_Write_4Byte(PRG_ADD_BR_USB, setups.brUSB);
    setups.brDUT = 115200;
    IIC_Write_4Byte(PRG_ADD_BR_DUT, setups.brDUT);
    setups.speak = 1;
    IIC_Write_Data(PRG_ADD_SPEAK, setups.speak);

    setups.idCAN = 254; //
    IIC_Write_Data(PRG_ADD_CAN_ID, setups.idCAN);

    //		swMes.max=32;
    //		IIC_Write_2Byte(MEMS_ADD_MAX,swMes.max);

    pLCD->logo = 1;
    IIC_Write_Data(LCD_ADD_LOGO, pLCD->logo);

    memset(pLCD->title, 0, 17);
    memcpy(pLCD->title, "OXC_16X16", 9);
    IIC_Write_Nbyte(pLCD->title, LCD_ADD_TITLE, 16);

    setups.dport = 0; // ## default port
    IIC_Write_Data(BOARD_ADD_D, setups.dport);
    setups.nport = 6; // port number
    IIC_Write_Data(BOARD_ADD_N, setups.nport);
    setups.bTime = 10000;
    IIC_Write_2Byte(BOARD_ADD_T, setups.bTime);
  }

  IIC_Read_Nbyte(ethernet.mac, ETHER_ADD_MAC, 6);
  IIC_Read_Nbyte(ethernet.ip, ETHER_ADD_IP, 4);
  IIC_Read_Nbyte(ethernet.sm, ETHER_ADD_SUB, 4);
  IIC_Read_Nbyte(ethernet.gw, ETHER_ADD_GW, 4);
  IIC_Read_Nbyte(ethernet.dns, ETHER_ADD_DNS, 4);
  IIC_Read_Nbyte(ethernet.rip, ETHER_ADD_RIP, 4);
  ethernet.port = IIC_Read_2Byte(ETHER_ADD_PORT);
  IIC_Read_Nbyte(ethernet.sw_ver, ETHER_ADD_VER, 2);

  pLCD->blk = IIC_Read_2Byte(LCD_ADD_BLK);
  //	SetOutputVoltageDAC1(pLCD->blk * BLK_SRV/100+BLK_MIN);//打开背光

  setups.lock = IIC_Read_Data(PRG_ADD_LOCK);
  setups.scan = IIC_Read_Data(PRG_ADD_SCAN);
  setups.Tgap = IIC_Read_4Byte(PRG_ADD_GAP);
  setups.sch = IIC_Read_2Byte(PRG_ADD_SCH);
  setups.ech = IIC_Read_2Byte(PRG_ADD_ECH);
  setups.language = IIC_Read_Data(PRG_ADD_LANGUAGE);
  setups.brUART = IIC_Read_4Byte(PRG_ADD_BR_UART);
  if ((setups.brUART <= 0) || (setups.brUART > 2000000))
  {
    setups.brUART = 115200;
  }
  setups.brUSB = IIC_Read_4Byte(PRG_ADD_BR_USB);
  if ((setups.brUSB <= 0) || (setups.brUSB > 2000000))
  {
    setups.brUSB = 115200;
  }
  setups.brDUT = IIC_Read_4Byte(PRG_ADD_BR_DUT);
  if ((setups.brDUT <= 0) || (setups.brDUT > 2000000))
  {
    setups.brDUT = 115200;
  }
  setups.speak = IIC_Read_Data(PRG_ADD_SPEAK);

  setups.dport = IIC_Read_Data(BOARD_ADD_D);
  if (setups.dport > 6)
  {
    setups.dport = 1;
  }
  setups.nport = IIC_Read_Data(BOARD_ADD_N);
  if (setups.nport > 6)
  {
    setups.nport = 6;
  }
  setups.bTime = IIC_Read_2Byte(BOARD_ADD_T);
  if (setups.bTime > 65530)
  {
    setups.bTime = 10000;
  }

  setups.idCAN = IIC_Read_Data(PRG_ADD_CAN_ID);
  //	if(setups.idCAN >15)
  //	{setups.idCAN=15;}

  pLCD->logo = IIC_Read_Data(LCD_ADD_LOGO);

  memset(pLCD->title, 0, 17);
  IIC_Read_Nbyte(pLCD->title, LCD_ADD_TITLE, 16);

  //	swMes.iep = IIC_Read_Data(MEMS_ADD_IEP);
  //	swMes.oep = IIC_Read_Data(MEMS_ADD_OEP);

#else

  //	uint8_t i;
  //
  //	flash_read_byte(FLASH_SECTION_PARAMETER + 0,&params.fInitial,1);
  //	if(0xed != params.fInitial)
  //	{
  //		params.fInitial=0xed;	//标记初始化
  //		for(i=0;i <= CH_NUM;i++)
  //		{
  //			params.ht[i]=500;
  //			params.lt[i]=500;
  //			params.cyc[i]=300;
  //		}
  //		ParameterSave();
  //	}
  //
  //	flash_read_byte(FLASH_SECTION_PARAMETER + 0,&params.fInitial,1);
  //	flash_read_halfword(FLASH_SECTION_PARAMETER + HT_ADDR,params.ht,CH_NUM);
  //	flash_read_halfword(FLASH_SECTION_PARAMETER + LT_ADDR,params.lt,CH_NUM);
  //	flash_read_halfword(FLASH_SECTION_PARAMETER + CYC_ADDR,params.cyc,CH_NUM);
  //

#endif
}

/***************************************************************************
;** 函数名称:
;** 功能描述:  硬件的初始化
;** 输入参数:
;** 返 回 值:
;** 全局变量:
;** 调用模块:
;** 作　  者:   M-L-A
;** 日　  期:  2013-3-17
;** 修改原因:
;** 说    明:
;***************************************************************************/
void bsp_Init(void)
{
  uint8_t r = 0, i;
  //	char str[25]={0};
  int n, j;

  pBuz->state = false;
  pBuz->enable = false;

  setups.step = 0;  //
  setups.reel = 0;  // 选项
  setups.page = 0;  // 菜单页
  setups.digit = 0; //
  setups.index = 0; //

  //	swMes.iep[0] = 0;
  //	swMes.iep[1] = 0;
  //	swMes.oep[0] = 0;
  //	swMes.oep[1] = 0;

  memset(pMultPort1->rxFIFO, 0, sizeof(pMultPort1->rxFIFO));
  //	memset(swMes.ocr,0,sizeof(swMes.ocr));
  memset(&hmi, 0, sizeof(hmi));
  //	memset(pCAN1,0,sizeof(rxStructure));

  pMultPort1->len = 0;
  pMultPort1->reTx = 0;
  pMultPort2->len = 0;
  pMultPort2->reTx = 0;
  pMultPort3->len = 0;
  pMultPort3->reTx = 0;
  pMultPort4->len = 0;
  pMultPort4->reTx = 0;

  //	pUART->send=0;
  //	pDUT->send=1;
  //	pDUT2->send=1;
  //	pMultPort1->send=1;
  //	pMultPort2->send=1;
  //	pMultPort3->send=1;
  //	pMultPort4->send=1;
  //	printfx("\r\n");
  pDUT->send = 0;
  pDUT2->send = 0;
  pMultPort1->send = 0;
  pMultPort2->send = 0;
  pMultPort3->send = 0;
  pMultPort4->send = 0;

  BoardIndex = setups.dport;

  pLCD->time = 500;
  if (!pLCD->logo)
  {
    // LCD_ShowASCII(12,48,(u8 *)VERSION,WHITE,BLACK,24,0);
    for (i = 0; i < 10; i++)
    {
      delay_ms(200);
      LCD_ShowASCII(i * 32, 42, (u8 *)"- ", WHITE, BLACK, 32, 0);
    }
  }
  while (pLCD->time)
  {
    ;
  }

  hmi.CurrentPage = HMI_Page_OPEN;
  hmi.language = setups.language;

  PortSelect_ClrRecvFifo(Port_MultiPort1);

  if (hmi.language)
  {
    printfx("语言.cb0.txt=\"English\"\xff\xff\xff");
  }
  else
  {
    printfx("语言.cb0.txt=\"中文\"\xff\xff\xff");
  }

  printfx("page 14\xff\xff\xff");         // 开机界面
  printfx("open.t0.aph=127\xff\xff\xff"); // 显示inital
  printfx("open.j0.aph=127\xff\xff\xff"); // 显示进度条
  printfx("open.j0.val=10\xff\xff\xff");  // 进度值
  PortSelect(Port_Release);
  //-------------------------------------------------------------------------------

  if (CalibrationStatistics(&CalibrationInfo) == false)
  {
    if (CalibrationInfo.valid_count)
    { // 没有定标?
      // PortSelect(Port_MultiPort1);
      // printfx("open.t1.txt=\"Calibration data lost.\"\xff\xff\xff");
      // PortSelect(Port_Release);
      // PortTickDelay(500); // 停留500ms 展示信息
    }
    else
    { // 没有检测到模块?弹窗提示
      // PortSelect(Port_MultiPort1);
      // printfx("open.t1.txt=\"TOF module not detected.\"\xff\xff\xff");
      // PortSelect(Port_Release);
      // PortTickDelay(500); // 停留500ms 展示信息
    }
  }

  // if (CenterWavLenOffset_Read(&hmi.lCenterWavLenOffset) == false)
  // { // 没有获取到中心波长偏移值
  // 	PortSelect(Port_MultiPort1);
  // 	printfx("open.t1.txt=\"CenterWavLenOffset data lost.\"\xff\xff\xff");
  // 	PortSelect(Port_Release);
  // 	PortTickDelay(500); // 停留500ms 展示信息
  // }

  // ListVoltage(&ChannelParam[0], CHANNEL_NUM);
  // SimulateVoltage(30, 40, 30, 40, &ChannelParam[0], CHANNEL_NUM);

  PortSelect(Port_MultiPort1);
  printfx("j0.val=20\xff\xff\xff"); // 进度条
  PortSelect(Port_Release);
  //-------------------------------------------------------------------------------
  PortSelect_ClrRecvFifo(Port_DUT2);
  printfx("read min\r\n");
  PortSelect(Port_Release);

  if (PortWait(Port_DUT2, 500, 20) == true)
  {
    if (strstr((char *)pDUT2->rxFIFO, "fail"))
    {
      // PortSelect(Port_MultiPort1);
      // printfx("open.t1.txt=\"read min fail.\"\xff\xff\xff");
      // PortSelect(Port_Release);
      // PortTickDelay(500); // 停留500ms 展示信息

      r++;
    }
    else if ((strstr((char *)pDUT2->rxFIFO, "min")) || (strstr((char *)pDUT2->rxFIFO, "MIN")))
    {
      sscanf((char *)pDUT2->rxFIFO, "%*s %f", &TOF.min);
    }
  }
  else
  {
    r++;
  }

  PortSelect(Port_MultiPort1);
  printfx("j0.val=30\xff\xff\xff"); // 进度条
  PortSelect(Port_Release);
  //-------------------------------------------------------------------------------
  PortSelect_ClrRecvFifo(Port_DUT2);
  printfx("read max\r\n");
  PortSelect(Port_Release);

  if (PortWait(Port_DUT2, 500, 20) == true)
  {
    if (strstr((char *)pDUT2->rxFIFO, "fail"))
    {
      // PortSelect(Port_MultiPort1);
      // printfx("open.t1.txt=\"read max fail.\"\xff\xff\xff");
      // PortSelect(Port_Release);
      // PortTickDelay(500); // 停留500ms 展示信息

      r++;
    }
    else if ((strstr((char *)pDUT2->rxFIFO, "max")) || (strstr((char *)pDUT2->rxFIFO, "MAX")))
    {
      sscanf((char *)pDUT2->rxFIFO, "%*s %f", &TOF.max);
    }
  }
  else
  {
    r++;
  }

  PortSelect(Port_MultiPort1);
  printfx("j0.val=40\xff\xff\xff"); // 进度条
  PortSelect(Port_Release);
  //-------------------------------------------------------------------------------
  PortSelect_ClrRecvFifo(Port_DUT2);
  printfx("read wl\r\n");
  PortSelect(Port_Release);

  if (PortWait(Port_DUT2, 500, 20) == true)
  {
    if (strstr((char *)pDUT2->rxFIFO, "fail"))
    {
      // PortSelect(Port_MultiPort1);
      // printfx("open.t1.txt=\"read wl fail.\"\xff\xff\xff");
      // PortSelect(Port_Release);
      // PortTickDelay(500); // 停留500ms 展示信息

      r++;
    }
    else if ((strstr((char *)pDUT2->rxFIFO, "wl")) || (strstr((char *)pDUT2->rxFIFO, "WL")))
    {
      sscanf((char *)pDUT2->rxFIFO, "%*s %d", &n);
      TOF.wl = n;
    }
  }
  else
  {
    r++;
  }

  PortSelect(Port_MultiPort1);
  printfx("j0.val=50\xff\xff\xff"); // 进度条
  PortSelect(Port_Release);
  //-------------------------------------------------------------------------------
  PortSelect_ClrRecvFifo(Port_DUT2);
  printfx("read ch\r\n");
  PortSelect(Port_Release);

  if (PortWait(Port_DUT2, 500, 20) == true)
  {
    if (strstr((char *)pDUT2->rxFIFO, "fail"))
    {
      // PortSelect(Port_MultiPort1);
      // printfx("open.t1.txt=\"read ch fail.\"\xff\xff\xff");
      // PortSelect(Port_Release);
      // PortTickDelay(500); // 停留500ms 展示信息

      r++;
    }
    else if ((strstr((char *)pDUT2->rxFIFO, "ch")) || (strstr((char *)pDUT2->rxFIFO, "CH")))
    {
      sscanf((char *)pDUT2->rxFIFO, "%*s %d", &n);
      TOF.ch = n;
    }
  }
  else
  {
    r++;
  }

  PortSelect(Port_MultiPort1);
  printfx("j0.val=60\xff\xff\xff"); // 进度条
  PortSelect(Port_Release);
  //-------------------------------------------------------------------------------
  PortSelect_ClrRecvFifo(Port_DUT2);
  printfx("sn ?\r\n");
  PortSelect(Port_Release);

  if (PortWait(Port_DUT2, 500, 20) == true)
  {
    if (strstr((char *)pDUT2->rxFIFO, "fail"))
    {
      r++;
    }
    else if ((strstr((char *)pDUT2->rxFIFO, "sn:")) || (strstr((char *)pDUT2->rxFIFO, "SN:")))
    {
      char *p_SN = (char *)((uint32_t)pDUT2->rxFIFO + strlen("\r\n") + 3);

      memset(hmi.sn, 0, sizeof(hmi.sn));

      i = 0;
      while (1)
      {
        if ((*p_SN != '\r') && (*p_SN != '\n'))
        {
          hmi.sn[i] = *p_SN;

          if (++i >= (sizeof(hmi.sn) - 1))
            break;
        }

        p_SN += 1;
      }
    }
  }
  else
  {
    r++;
  }

  PortSelect(Port_MultiPort1);
  printfx("j0.val=70\xff\xff\xff"); // 进度条
  PortSelect(Port_Release);
  //-------------------------------------------------------------------------------
  PortSelect_ClrRecvFifo(Port_DUT2);
  printfx("ver ?\r\n");
  PortSelect(Port_Release);

  if (PortWait(Port_DUT2, 500, 20) == true)
  {
    if (strstr((char *)pDUT2->rxFIFO, "fail"))
    {
      r++;
    }
    else
    {
      n = strlen((char *)pDUT2->rxFIFO);
      memset(hmi.ver, 0, sizeof(hmi.ver));

      if (n >= sizeof(hmi.ver))
        n = sizeof(hmi.ver) - 1;

      for (i = 0, j = 0; i < n; i++)
      {
        if ((pDUT2->rxFIFO[i] != '\r') && (pDUT2->rxFIFO[i] != '\n'))
        {
          hmi.ver[j++] = pDUT2->rxFIFO[i];
        }
      }
    }
  }
  else
  {
    r++;
  }

  PortSelect(Port_MultiPort1);
  printfx("j0.val=80\xff\xff\xff"); // 进度条
  PortSelect(Port_Release);
  //-------------------------------------------------------------------------------
  PortSelect_ClrRecvFifo(Port_DUT2);
  printfx("srw r rwl\r\n");
  PortSelect(Port_Release);

  if (PortWait(Port_DUT2, 500, 20) == true)
  {
    if (strstr((char *)pDUT2->rxFIFO, "fail"))
    {
      // PortSelect(Port_MultiPort1);
      // printfx("open.t1.txt=\"srw r rwl fail.\"\xff\xff\xff");
      // PortSelect(Port_Release);
      // PortTickDelay(500); // 停留500ms 展示信息

      r++;
    }
    else
    {
      n = strlen((char *)pDUT2->rxFIFO);
      memset(hmi.rwl, 0, sizeof(hmi.rwl));

      if (n >= sizeof(hmi.rwl))
        n = sizeof(hmi.rwl) - 1;

      for (i = 0, j = 0; i < n; i++)
      {
        if ((pDUT2->rxFIFO[i] != '\r') && (pDUT2->rxFIFO[i] != '\n'))
        {
          hmi.rwl[j++] = pDUT2->rxFIFO[i];
        }
      }
    }
  }
  else
  {
    r++;
  }

  PortSelect(Port_MultiPort1);
  printfx("j0.val=90\xff\xff\xff"); // 进度条
  PortSelect(Port_Release);
  //-------------------------------------------------------------------------------
  PortSelect_ClrRecvFifo(Port_DUT2);
  printfx("srw r bb\r\n");
  PortSelect(Port_Release);

  if (PortWait(Port_DUT2, 500, 20) == true)
  {
    if (strstr((char *)pDUT2->rxFIFO, "fail"))
    {
      // PortSelect(Port_MultiPort1);
      // printfx("open.t1.txt=\"srw r bb fail.\"\xff\xff\xff");
      // PortSelect(Port_Release);
      // PortTickDelay(500); // 停留500ms 展示信息

      r++;
    }
    else
    {
      n = strlen((char *)pDUT2->rxFIFO);
      memset(hmi.bb, 0, sizeof(hmi.bb));

      if (n >= sizeof(hmi.bb))
        n = sizeof(hmi.bb) - 1;

      for (i = 0, j = 0; i < n; i++)
      {
        if ((pDUT2->rxFIFO[i] != '\r') && (pDUT2->rxFIFO[i] != '\n'))
        {
          hmi.bb[j++] = pDUT2->rxFIFO[i];
        }
      }
    }
  }
  else
  {
    r++;
  }

  PortSelect(Port_MultiPort1);
  printfx("j0.val=95\xff\xff\xff"); // 进度条
  PortSelect(Port_Release);
  //-------------------------------------------------------------------------------
  PortSelect_ClrRecvFifo(Port_DUT2);
  printfx("srw r temp\r\n");
  PortSelect(Port_Release);

  if (PortWait(Port_DUT2, 500, 20) == true)
  {
    if (strstr((char *)pDUT2->rxFIFO, "fail"))
    {
      // PortSelect(Port_MultiPort1);
      // printfx("open.t1.txt=\"srw r temp fail.\"\xff\xff\xff");
      // PortSelect(Port_Release);
      // PortTickDelay(500); // 停留500ms 展示信息

      r++;
    }
    else
    {
      n = strlen((char *)pDUT2->rxFIFO);
      memset(hmi.temp, 0, sizeof(hmi.temp));

      if (n >= sizeof(hmi.temp))
        n = sizeof(hmi.temp) - 1;

      for (i = 0, j = 0; i < n; i++)
      {
        if ((pDUT2->rxFIFO[i] != '\r') && (pDUT2->rxFIFO[i] != '\n'))
        {
          hmi.temp[j++] = pDUT2->rxFIFO[i];
        }
      }
    }
  }
  else
  {
    r++;
  }

  PortSelect(Port_MultiPort1);
  printfx("j0.val=100\xff\xff\xff"); // 进度条
  PortSelect(Port_Release);
  //-------------------------------------------------------------------------------

  if (setups.speak)
  {
    BuzStart(100, 0, 1);
  }

  PortSelect(Port_MultiPort1);
  if (hmi.language)
  {
    printfx("page 0\xff\xff\xff");

    hmi.CurrentPage = HMI_Page_Main_EN;
  }
  else
  {
    printfx("page 5\xff\xff\xff");

    hmi.CurrentPage = HMI_Page_Main_CN;
  } // 主页
  PortSelect(Port_Release);

  PortSelect(Port_UART);
  if (r)
  {
    printfx("Initial ER\r\n");
  }
  else
  {
    printfx("Initial OK\r\n");
  } // 主页
  PortSelect(Port_Release);
}

/***************************************************************************
;** 函数名称:
;** 功能描述:  浮点型格式化小数点 带四舍五入
;** 输入参数:
;** 返 回 值:
;** 全局变量:
;** 调用模块:
;** 作　  者:   M-L-A
;** 日　  期:  2013-3-17
;** 修改原因：
;** 说    明:  	 leng 保几位小数点
;***************************************************************************/
double ffp(double fm, int leng)
{
  double ft = 0.0;
  unsigned long ul = 0;

  if (fabs(fm) > 0.0)
  {
    if (leng >= 0)
    {
      if (leng >= 5) // 只允许保留5位小数点
      {
        leng = 5;
      }
      leng++;
      ul = (unsigned long)(fabs(fm) * pow(10, leng)); // 10的leng次方
      if ((ul % 10) >= 5)
      {
        ul = ul / 10 + 1;
      } // 四舍五入
      else
      {
        ul = ul / 10;
      }
      ft = (double)(ul / pow(10, leng - 1)); // 保留的小数点
      if (fm < 0.0)
      {
        ft = -ft;
      }
    }
    else
    {
      ft = fm * pow(10, leng);
    } // 负次方
  }
  return ft;
}

/***************************************************************************
** 函数名称:
** 功能描述:  	转换浮点数n 为字符串str。
** 输入参数:
** 返 回 值: 	 无
** 全局变量:
** 调用模块:
** 作　  者:   M-L-A
** 日　  期:   2013-4-25
** 修改原因：
** 说    明:    字符串表示为科学计数法形式，由decimals指定四舍五入保留小数位（最多五位）。
;***************************************************************************/
char ftoa(double fv, unsigned char decimals, char *str)
{
  double fd;
  unsigned char i, n, c, k;
  unsigned int v, pw;

  c = 0;
  if (fv < 0.0)
  {
    str[c++] = '-';
  }
  fv = fabs(fv);
  v = fv;
  fd = fv - v;
  v = fd * pow(10, decimals + 1); // 四舍五入
  if ((v % 10) >= 5)
  {
    fv = fv + 1 / pow(10, decimals);
  }
  v = fv;
  k = 0;
  for (i = 0; i < 10; i++) // 0xffffffff=4 294 967 295
  {
    pw = pow(10, 9 - i);
    n = v / pw;
    v = v % pw;
    if ((n > 0) || (k > 0))
    {
      str[c + k] = n + '0';
      k++;
    }
  }
  c = c + k;
  if (k <= 0)
  {
    str[c++] = '0';
  }
  if (decimals > 0)
  {
    str[c++] = '.';
    v = fv;
    fd = fv - v;
    for (i = 0; i < decimals; i++)
    {
      fd = fd * 10;
      v = fd;
      n = v % 10;
      str[c++] = n + '0';
    }
  }
  return c;
}
/***************************************************************************
** 函数名称:  	char itoa(int tv,char *str)
** 功能描述:  	整数 为字符串string。
** 输入参数:    tv--需要转换的整型；
** 返 回 值: 	c--返回个数； *str--返回字符串
** 全局变量:
** 调用模块:
** 作　  者:   M-L-A
** 日　  期:   2019-9-13
** 修改原因：
** 说    明:
      0xffffffff = 4 294 967 295;
;***************************************************************************/
char itoa(int tv, char *str)
{
  unsigned char i, n, c;
  unsigned int v;

  v = abs(tv);
  for (i = 0; i < 10; i++) // 0xffffffff=4 294 967 295
  {
    str[i] = (v % 10) + '0';
    v = v / 10;
    if (v <= 0)
    {
      break;
    }
  }
  c = i + 1;
  if (tv < 0)
  {
    str[c] = '-';
    c++;
  }
  for (i = 0; i < (c / 2); i++)
  { // 高低位互换
    n = str[i];
    str[i] = str[c - i - 1];
    str[c - i - 1] = n;
  }

  return c;
}
/***************************************************************************
** 函数名称:  	char itoa_32(int tv,char *str)
** 功能描述:  	整数 为字符串string。
** 输入参数:    tv--需要转换的整型；
** 返 回 值: 	c--返回个数； *str--返回字符串
** 全局变量:
** 调用模块:
** 作　  者:   M-L-A
** 日　  期:   2019-9-13
** 修改原因：
** 说    明:
      0xffffffff = 4 294 967 295;
;***************************************************************************/
char itoa_32(int tv, char *str)
{
  unsigned char i, n, c;
  unsigned int v, pw;

  c = 0;
  v = abs(tv);
  for (i = 0; i < 10; i++) // 0xffffffff=4 294 967 295
  {
    pw = pow(10, 9 - i);
    n = v / pw;
    v = v % pw;
    if ((n > 0) || (c > 0))
    {
      str[c++] = n + 0x30;
    }
  }
  if (c > 0)
  {
    for (i = 0; i < c; i++)
    {
      n = str[i];
      str[i] = str[c - i - 1];
      str[c - i - 1] = n;
    }
    if (tv < 0)
    {
      str[c] = '-';
    }
  }
  else
  {
    str[0] = '0';
  }
  return c;
}
/***************************************************************************
;** 函数名称:
;** 功能描述:  USARTx printf
;** 输入参数:
;** 返 回 值:
;** 全局变量:
;** 调用模块:
;** 作　  者:   M-L-A
;** 日　  期:  2012-6-29
;** 修改原因：
;** 说    明:
;***************************************************************************/
void sformat(char *o, char *s, ...)
{
  char buf[128] = {0}; // 分配512字节的字符串缓存

  va_list ap;
  va_start(ap, s);
  vsprintf(buf, (const char *)s, ap); // 将格式字符串与后面的参数绑定为一个字符串，拷贝到输出缓存
  va_end(ap);

  strncat(o, buf, strlen(buf));
}

/***************************************************************************
** 函数名称:
** 功能描述:  	转换浮点数n 为字符串str。
** 输入参数:
** 返 回 值: 	 无
** 全局变量:
** 调用模块:
** 作　  者:   M-L-A
** 日　  期:   2013-4-25
** 修改原因：
** 说    明:    decimal>0，不做四舍五入保留小数位（最多五位）。
;***************************************************************************/
char ftoa_nr(double fv, unsigned char decimals, char *str)
{
  double fd;
  char i, c, tstr[10] = {0};
  unsigned int v;

  c = 0;
  if (fv < 0.0)
  {
    tstr[c++] = '-';
  }
  fd = fabs(fv);
  v = fd * pow(10, decimals + 1); //
  if ((v % 10) > 8)               // 0.9999999999 -> 1
  {
    v = v + 1;
  }
  v = v / 10;
  for (i = 0; i < 10; i++) // 0xffffffff=4 294 967 295
  {
    tstr[c++] = (v % 10) + '0';
    if ((i + 1) == decimals)
    {
      tstr[c++] = '.';
    }
    v = v / 10;
    if (!v)
    {
      if (c <= (decimals + 1))
      {
        tstr[c++] = '0';
      } // .1 -> 0.1
      break;
    }
  }
  for (i = 0; i < c; i++)
  {
    str[i] = tstr[c - 1 - i];
  }

  return c;
}
