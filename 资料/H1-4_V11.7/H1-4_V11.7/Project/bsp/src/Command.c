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

#include "Command.h"
#include "CommandList.h"
#include "includes.h"

/***************************************************************************
** 函数名称:
** 功能描述:   大写转小写
** 输入参数: 	 无
** 返 回 值: 	 无
** 全局变量:
** 调用模块:
** 作　  者:   M-L-A
** 日　  期:   2014-4-29
** 修改原因：
** 说    明:
;***************************************************************************/
int gLowerCaseString(char *str)
{
  unsigned char i, len;

  len = strlen(str);
  for (i = 0; i < len; i++)
  {
    if ((str[i] >= 'A') && (str[i] <= 'Z'))
    {
      str[i] = str[i] + 0x20;
    }
  }
  return 0;
}

/***************************************************************************
** 函数名称:
** 功能描述:
** 输入参数: 	 无
** 返 回 值: 	 无
** 全局变量:
** 调用模块:
** 作　  者:   M-L-A
** 日　  期:   2014-4-29
** 修改原因：
** 说    明:    字数--ASCII;  0--30; 9--39;
;***************************************************************************/
void rxCommandDispose(void *pt)
{
  uint8_t n, c = 0xff, x;
  char Tstr[16] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
  rxStructure *p = pt;

  if (p->len >= RX_MAX_FIFO)
  { // 超出长度
    memset(p->rxFIFO, 0, RX_MAX_FIFO);
    p->len = 0;
    p->rxn = 0;
    p->reTx = 0;
  }
  //--------返回每一个字符处理----------------------------------------------------
  if (p->feelback == true)
  {
    p->send = 1;
    while (p->len > p->reTx)
    {
      printx(p->rxFIFO[p->reTx++]);
    }
    if (p->rxn)
    {
      printfx("\r\n");
    }
    p->send = 0;
  }
  //--------指令判断--------------------------------------------------------------
  if (p->rxn > 0)
  {
    if (p->len > 0)
    {
      IndexTimeDec = setups.bTime; // select board time
      c = 0;
      tPort = pt;
      if (strstr((char *)p->rxFIFO, "##:") == 0)
      { // 跳过##这条指令
        for (n = 0; n < p->len; n++)
        {
          if (((p->rxFIFO[n] >= 'a') && (p->rxFIFO[n] <= 'z')) || ((p->rxFIFO[n] >= 'A') && (p->rxFIFO[n] <= 'Z')))
          {
            break;
          }
          else
          {
            c++;
          }
        }
      }
      if (c >= p->len)
      {
        p->send = 1;
        printfx("command is illegal\r\n"); // 输入的命令非法
        p->send = 0;
      }
      else
      {
        for (n = 0; n < 9; n++)
        {
          x = p->rxFIFO[c + n];
          if ((x == '_') || (x == ' ') || (x == '\0'))
          {
            break;
          }
          else
          {
            Tstr[n] = x;
          }
        }
        gLowerCaseString(Tstr);
        if (strstr(Tstr, ":") != 0)
        {
          for (c = 0xff, n = 0; n < cmdStrLen; n++) /// 匹配命令编号
          {
            if (strcmp(Tstr, cmdMessage[n].cmdStr) == 0)
            {
              c = n;
              break;
            }
          }
          if (n >= cmdStrLen)
          { // 传送DUT
            p->send = 1;
            printfx("command is illegal\r\n"); // 输入的命令非法
            p->send = 0;
          }
          else if (c != 0xff)
          { // 执行函数
            p->send = 1;
            cmdMessage[c].func(p->rxFIFO);
            p->send = 0;
          }
        }
        else
        { // 子板
          if (p->len > 0)
          {
            pUART->send = 0;
            pUSB->send = 0;
            pEther->send = 0;
            pDUT->send = 0;
            pDUT2->send = 0;
            pMultPort1->send = 0;
            pMultPort2->send = 0;
            pMultPort3->send = 0;
            pMultPort4->send = 0;
            c = 0;
            switch (BoardIndex)
            { // ## 传送给选中的板
            case 0:
            {
              c = 2;
            }
            break;
            case 1:
            {
              pDUT->send = 1;
              printfx((char *)p->rxFIFO);
              printfx("\r\n");
              pDUT->send = 0;
            }
            break;
            case 2:
            {
              c = 2;
            }
            break;
            case 3:
            {
              pMultPort1->send = 1;
              printfx((char *)p->rxFIFO);
              printfx("\xFF\xFF\xFF");
              pMultPort1->send = 0;
            }
            break;
            case 4:
            {
              pMultPort2->send = 1;
              printfx((char *)p->rxFIFO);
              pMultPort2->send = 0;
            }
            break;
            case 5:
            {
              pMultPort3->send = 1;
              printfx((char *)p->rxFIFO);
              pMultPort3->send = 0;
            }
            break;
            case 6:
            {
              pMultPort4->send = 1;
              printfx((char *)p->rxFIFO);
              pMultPort4->send = 0;
            }
            break;
            default:
            {
              c = 2;
            }
            break;
            }
            if (c == 2)
            {
              if (strcmp(Tstr, "reset") == 0)
              {
                if ((strstr((char *)p->rxFIFO, "scan") != 0) || (strstr((char *)p->rxFIFO, "SCAN") != 0))
                { // 复位扫描命令
                  // if (ScanerOngoingCheck() == true)
                  {
                    PortSelect_ClrRecvFifo(Port_DUT2);
                    printfx((char *)p->rxFIFO);
                    printfx("\r\n");
                    PortSelect(Port_Release);

                    if (PortWait(Port_DUT2, 500, 20) == true)
                    {
                      if (strstr((char *)pDUT2->rxFIFO, "pass") != 0)
                      {
                        ScanerStop();

                        PortSelect(Port_MultiPort1);
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
                        PortSelect(Port_Release);
                      }
                    }
                  }
                }
                else if ((strstr((char *)p->rxFIFO, "wln") != 0) || (strstr((char *)p->rxFIFO, "WLN") != 0))
                { // 复位波长设置命令
                  PortSelect_ClrRecvFifo(Port_DUT2);
                  printfx((char *)p->rxFIFO);
                  printfx("\r\n");
                  PortSelect(Port_Release);

                  if (PortWait(Port_DUT2, 500, 20) == true)
                  {
                    if (strstr((char *)pDUT2->rxFIFO, "pass") != 0)
                    {
                      hmi.ewl = 0;

                      PortSelect(Port_MultiPort1);
                      if (hmi.language)
                      {
                        sprintfx("main.x0.val=%d\xFF\xFF\xFF", hmi.ewl);
                        sprintfx("main.x3.val=%d\xFF\xFF\xFF", 0);
                        printfx("page 0\xFF\xFF\xFF");
                      }
                      else
                      {
                        sprintfx("主页.x0.val=%d\xFF\xFF\xFF", hmi.ewl);
                        sprintfx("主页.x3.val=%d\xFF\xFF\xFF", 0);
                        printfx("page 5\xFF\xFF\xFF");
                      }
                      PortSelect(Port_Release);
                    }
                  }
                }
              }
              else if (strcmp(Tstr, "scan") == 0)
              { // 扫描上传屏幕
                int num, tival, mode;
                double s, e, step;
                uint32_t ulTemp_swl, ulTemp_ewl;

                memset(Tstr, 0, sizeof(Tstr));
                sscanf((char *)p->rxFIFO, "%*s %lf %lf %lf %d %d %d", &s, &e, &step, &num, &tival, &mode);

                ulTemp_swl = (uint32_t)(s * 1000);
                ulTemp_ewl = (uint32_t)(e * 1000);

                {
                  { // 缓存参数,然后跳转页面,由页面回调函数处理命令
                    hmi.swl = ulTemp_swl;
                    hmi.ewl = ulTemp_ewl;
                    hmi.iwl = (uint32_t)(step * 1000);
                    hmi.itim = tival;
                    hmi.scan = mode;
                  }

                  PortSelect(Port_MultiPort1);

                  if (hmi.language)
                  {
                    sprintfx("峰值搜索.t0.txt=\"λstart:\"\xFF\xFF\xFF");
                    sprintfx("峰值搜索.t1.txt=\"λstart:\"\xFF\xFF\xFF");
                    sprintfx("峰值搜索.t2.txt=\"λinterval:\"\xFF\xFF\xFF");
                    sprintfx("峰值搜索.t7.txt=\"Tinterval:\"\xFF\xFF\xFF");
                    sprintfx("峰值搜索.t8.txt=\"ScanMode:\"\xFF\xFF\xFF");
                    sprintfx("峰值搜索.b1.txt=\"Excute\"\xFF\xFF\xFF");
                    sprintfx("峰值搜索.b0.txt=\"Back\"\xFF\xFF\xFF");
                  }
                  else
                  {
                    sprintfx("峰值搜索.t0.txt=\"起始波长:\"\xFF\xFF\xFF");
                    sprintfx("峰值搜索.t1.txt=\"结束波长:\"\xFF\xFF\xFF");
                    sprintfx("峰值搜索.t2.txt=\"间隔波长:\"\xFF\xFF\xFF");
                    sprintfx("峰值搜索.t7.txt=\"间隔时间:\"\xFF\xFF\xFF");
                    sprintfx("峰值搜索.t8.txt=\"扫描方式:\"\xFF\xFF\xFF");
                    sprintfx("峰值搜索.b1.txt=\"执行\"\xFF\xFF\xFF");
                    sprintfx("峰值搜索.b0.txt=\"返回\"\xFF\xFF\xFF");
                  }

                  printfx("page 6\xFF\xFF\xFF"); // 峰值搜索页面

                  PortSelect(Port_Release);

                  if (strstr((char *)p->rxFIFO, "SCAN") != 0)
                  {
                    SwitchToExecuteAfter(600 / 25, true); // 峰值搜索页面停留600ms后再执行
                  }
                  else
                  {
                    SwitchToExecuteAfter(600 / 25, false); // 峰值搜索页面停留600ms后再执行
                  }
                }
              }
              else
              {
                if (strcmp(Tstr, "set") == 0)
                {
                  memset(Tstr, 0, sizeof(Tstr));
                  sscanf((char *)p->rxFIFO, "%*s %s", Tstr);
                  if ((Tstr[0] != 'C') || (Tstr[0] != 'c'))
                  {
                    double f;
                    uint32_t ulTemp_ewl;

                    sscanf(Tstr, "%lf", &f);
                    ulTemp_ewl = f * 1000;

                    if (InputWavLenCheck(ulTemp_ewl) == true)
                    {
                      hmi.ewl = ulTemp_ewl;
                      f = hmi.ewl; // f=2.99792*pow(8)/wl
                      f = f / 1000;
                      f = 2.99792 / f;
                      f = f * 100000;

                      pMultPort1->send = 1;

                      if (hmi.language)
                      {
                        sprintfx("main.x0.val=%d\xFF\xFF\xFF", hmi.ewl);
                        sprintfx("main.x3.val=%d\xFF\xFF\xFF", (uint32_t)(f * 10000));
                        printfx("page 0\xFF\xFF\xFF");
                      }
                      else
                      {
                        sprintfx("主页.x0.val=%d\xFF\xFF\xFF", hmi.ewl);
                        sprintfx("主页.x3.val=%d\xFF\xFF\xFF", (uint32_t)(f * 10000));
                        printfx("page 5\xFF\xFF\xFF");
                      }

                      pMultPort1->send = 0;
                    }
                  }
                }

                pDUT2->send = 1;
                printfx((char *)p->rxFIFO);
                printfx("\r\n");
                pDUT2->send = 0;
              }
            }
          }
        }
      }
      memset(p->rxFIFO, 0, RX_MAX_FIFO);
      p->len = 0;
    }
    else
    {
      p->send = 1;
      printfx("\r\n@_@\r\n");
      p->send = 0;
    }
    p->reTx = 0;
    p->rxn = 0;
  }
  else if (p->len > 0) //(p->TimeOut <= 0)
  {
    if (!p->TimeOut) //(p->len | p->rxn)
    {
      p->cto++;
      if (p->cto > 60000)
      {
        uint16_t i;

        for (i = 0; i < RX_MAX_FIFO; i++)
        {
          if (p->TimeOut)
          {
            p->cto = 0;
            break;
          }
          p->rxFIFO[i] = 0;
        }
        p->len = 0;
        p->reTx = 0;
        p->rxn = 0;
      }
    }
    else
    {
      p->cto = 0;
    }
  }
}

/***************************************************************************
** 函数名称:  	help
** 功能描述:
** 输入参数: 	 无
** 返 回 值: 	 无
** 全局变量:
** 调用模块:
** 作　  者:   M-L-A
** 日　  期:   2019-9-16
** 修改原因：
** 说    明:    字数--ASCII;  0--30; 9--39;
;***************************************************************************/
char help(void *p, ...)
{
  uint8_t i;
  for (i = 0; i < cmdStrLen; i++)
  {
    printfx((char *)cmdMessage[i].rChar);
  }

  return 0;
}

/***************************************************************************
** 函数名称:  	help
** 功能描述:
** 输入参数: 	 无
** 返 回 值: 	 无
** 全局变量:
** 调用模块:
** 作　  者:   M-L-A
** 日　  期:   2019-6-8
** 修改原因：
** 说    明:    字数--ASCII;  0--30; 9--39;
;***************************************************************************/
char RebackCharacter(void *p, ...)
{
  int s;

  sscanf(p, "%*s %d", &s);
  if (s == 0)
  {
    pUART->feelback = false;
    pUART->reTx = 0;
    printfx(p);
    printfx(" pass\r\n");
  }
  else if (s == 1)
  {
    pUART->feelback = true;
    pUART->reTx = pUART->len;
    printfx(p);
    printfx(" pass\r\n");
  }
  else
  {
    printfx(p);
    printfx(" fail\r\n");
  }

  return 0;
}
/***************************************************************************
** 函数名称:  	ReadVersion
** 功能描述:
** 输入参数: 	 无
** 返 回 值: 	 无
** 全局变量:
** 调用模块:
** 作　  者:   M-L-A
** 日　  期:   2019-9-16
** 修改原因：
** 说    明:    字数--ASCII;  0--30; 9--39;
;***************************************************************************/
char ReadVersion(void *p, ...)
{
  //	memset(Tstr1,0,strlen(Tstr1));
  //	sscanf(p, "%[^)]",Tstr1);

  printfx(VERSION);
  printfx("\r\n");

  return 0;
}

/***************************************************************************
** 函数名称:
** 功能描述:
** 输入参数: 	 无
** 返 回 值: 	 无
** 全局变量:
** 调用模块:
** 作　  者:   M-L-A
** 日　  期:   2022-5-26
** 修改原因：
** 说    明:    字数--ASCII;  0--30; 9--39;
;***************************************************************************/
char SetReadWrite(void *p, ...)
{
  char r = 0, str[48] = {0}, str1[48] = {0};
  int i = 0;

  memset(str, 0, sizeof(str));
  memset(str1, 0, sizeof(str1));
  sscanf(p, "%*s %s %s %d", str, str1, &i);

  gLowerCaseString(str);
  gLowerCaseString(str1);

  if (strcmp(str, "w") == 0)
  {
    if (strcmp(str1, "lock") == 0)
    {
      setups.lock = i;
      IIC_Write_Data(PRG_ADD_LOCK, setups.lock);
      r = 1;
    }
    else if (strcmp(str1, "scan") == 0)
    {
      setups.scan = i;
      IIC_Write_Data(PRG_ADD_SCAN, setups.scan);
      r = 2;
    }
    else if (strcmp(str1, "tgap") == 0)
    {
      if (i > 30 && i < 1000000000)
      {
        setups.Tgap = i;
        IIC_Write_4Byte(PRG_ADD_GAP, setups.Tgap);
        r = 3;
      }
    }
    else if (strcmp(str1, "sch") == 0)
    {
      if (i <= setups.ech)
      {
        setups.sch = i;
        IIC_Write_2Byte(PRG_ADD_SCH, setups.sch);
        r = 4;
      }
    }
    else if (strcmp(str1, "dport") == 0)
    { // default port
      if ((i > 0) && (i < 5))
      {
        setups.dport = i;
        IIC_Write_Data(BOARD_ADD_D, setups.dport);
        r = 5;
      }
    }
    else if (strcmp(str1, "language") == 0)
    {
      setups.language = i;
      IIC_Write_Data(PRG_ADD_LANGUAGE, setups.language);
      r = 6;
    }
    else if (strcmp(str1, "bruart") == 0)
    {
      setups.brUART = i;
      IIC_Write_4Byte(PRG_ADD_BR_UART, setups.brUART);
      usart1_config(setups.brUART);
      r = 7;
    }
    else if (strcmp(str1, "brusb") == 0)
    {
      setups.brUSB = i;
      IIC_Write_4Byte(PRG_ADD_BR_USB, setups.brUSB);
      usart3_config(setups.brUSB);
      r = 8;
    }
    else if (strcmp(str1, "brdut") == 0)
    {
      setups.brDUT = i;
      IIC_Write_4Byte(PRG_ADD_BR_DUT, setups.brDUT);
      usart2_config(setups.brDUT);
      r = 9;
    }
    else if (strcmp(str1, "spk") == 0)
    {
      setups.speak = i;
      IIC_Write_Data(PRG_ADD_SPEAK, setups.speak);
      r = 10;
    }
    //		else if(strcmp(str1,"swmax")==0)
    //		{swMes.max=i;IIC_Write_2Byte(MEMS_ADD_MAX,swMes.max);r=10;}
    else if (strcmp(str1, "logo") == 0)
    {
      pLCD->logo = i;
      IIC_Write_Data(LCD_ADD_LOGO, pLCD->logo);
      r = 12;
    }
    else if (strcmp(str1, "nport") == 0)
    { // set port number
      if ((i > 0) && (i <= 16))
      {
        setups.nport = i;
        IIC_Write_Data(BOARD_ADD_N, setups.nport);
        r++;
      }
    }
    else if (strcmp(str1, "btime") == 0)
    { // select port time
      setups.bTime = i;
      IIC_Write_4Byte(BOARD_ADD_T, setups.bTime);
      r++;
    }
    else if (strcmp(str1, "idcan") == 0)
    { // CAN ID
      setups.idCAN = i;
      IIC_Write_Data(PRG_ADD_CAN_ID, setups.idCAN);
      memset(str, 0, sizeof(str));
      sformat(str, "srw w hid %d\r\n", i);
      target_id = 0xff;                    // 广播地址0x00; 禁止广播
      txCAN1((uint8_t *)str, strlen(str)); //
      r++;
    }

    printfx(p);
    if (r > 0)
    {
      printfx(" pass\r\n");
      if (!setups.step)
      {
        MainGUI(GRAYBLUE, GRAY0);
      }
      else
      {
        SetupGUI(setups.page, BROWN, GRAY0);
        SelectMarkGUI(setups.reel, BROWN, GRAY0);
        if (setups.step == 3)
        {
          SelectOptionGUI(setups.reel, BROWN, KHAKI);
        }
      }
    }
    else
    {
      printfx(" fail\r\n");
    }
  }
  else if (strcmp(str, "r") == 0)
  {
    if (strcmp(str1, "err") == 0)
    {
      if (erCode.bit.b0 == true)
      {
        printfx("DUT alarm\r\n");
      }
      else
      {
        sprintfx("err:%d\r\n", erCode.regis);
      }
    }
    else if (strcmp(str1, "lock") == 0)
    {
      sprintfx("lock:%d\r\n", setups.lock);
    }
    else if (strcmp(str1, "scan") == 0)
    {
      sprintfx("scan:%d\r\n", setups.scan);
    }
    else if (strcmp(str1, "tgap") == 0)
    {
      sprintfx("Tgap:%d\r\n", setups.Tgap);
    }
    else if (strcmp(str1, "sch") == 0)
    {
      sprintfx("sch:%d\r\n", setups.sch);
    }
    else if (strcmp(str1, "ech") == 0)
    {
      sprintfx("ech:%d\r\n", setups.ech);
    }
    else if (strcmp(str1, "language") == 0)
    {
      sprintfx("language:%d\r\n", setups.language);
    }
    else if (strcmp(str1, "bruart") == 0)
    {
      sprintfx("UART:%d\r\n", setups.brUART);
    }
    else if (strcmp(str1, "brusb") == 0)
    {
      sprintfx("USB:%d\r\n", setups.brUSB);
    }
    else if (strcmp(str1, "brdut") == 0)
    {
      sprintfx("DUT:%d\r\n", setups.brDUT);
    }
    else if (strcmp(str1, "spk") == 0)
    {
      sprintfx("speak:%d\r\n", setups.speak);
    }
    //		else if(strcmp(str1,"swmax")==0)
    //		{sprintfx("max:%d\r\n",swMes.max);}
    else if (strcmp(str1, "logo") == 0)
    {
      sprintfx("logo:%d\r\n", pLCD->logo);
    }
    else if (strcmp(str1, "dport") == 0)
    {
      sprintfx("dport:%d\r\n", setups.dport);
    }
    else if (strcmp(str1, "nport") == 0)
    {
      sprintfx("nport:%d\r\n", setups.nport);
    }
    else if (strcmp(str1, "btime") == 0)
    {
      sprintfx("bTime:%d\r\n", setups.bTime);
    }
    else if (strcmp(str1, "idcan") == 0)
    {
      sprintfx("idCAN:%d\r\n", setups.idCAN);
    }
    else
    {
      printfx(p);
      printfx(" fail\r\n");
    }
  }
  else
  {
    printfx(p);
    printfx(" fail\r\n");
  }

  return 0;
}

/***************************************************************************
** 函数名称:
** 功能描述:
** 输入参数: 	 无
** 返 回 值: 	 无
** 全局变量:
** 调用模块:
** 作　  者:   M-L-A
** 日　  期:   2022-5-26
** 修改原因：
** 说    明:    字数--ASCII;  0--30; 9--39;
;***************************************************************************/
char EthernerParameter(void *p, ...)
{
  char str[48] = {0}, tstr[48] = {0};
  uint8_t i = 0, td[6] = {0};
  int k;

  memset(str, 0, sizeof(str));
  sscanf(p, "%*s %s", str);
  gLowerCaseString(str);
  if (strcmp(str, "w") == 0)
  {
    memset(str, 0, sizeof(str));
    sscanf(p, "%*s %*s %s", str);
    gLowerCaseString(str);
    i = 0;
    if (strcmp(str, "mac") == 0)
    {
      memset(str, 0, sizeof(str));
      sscanf(p, "%*s %*s %*s %s", str);

      for (i = 0; i < 6; i++)
      {
        memset(tstr, 0, sizeof(tstr));
        sscanf(str, "%[^-]", tstr);
        if (strlen(tstr) > 0)
        {
          sscanf(tstr, "%x", &k);
          td[i] = k;
          memset(tstr, 0, sizeof(tstr));
          sscanf(str, "%*[^-]-%[^'\']", tstr);
          memcpy(str, tstr, sizeof(str));
        }
        else
        {
          break;
        }
      }
      if (i == 6)
      {
        for (i = 0; i < 6; i++)
        {
          ethernet.mac[i] = td[i];
        }
        IIC_Write_Nbyte(ethernet.mac, ETHER_ADD_MAC, 6);
        i = 1;
      }
      else
      {
        i = 0;
      }
    }
    else if (strcmp(str, "ip") == 0)
    {
      memset(str, 0, sizeof(str));
      sscanf(p, "%*s %*s %*s %s", str);
      for (i = 0; i < 4; i++)
      {
        memset(tstr, 0, sizeof(tstr));
        sscanf(str, "%[^.]", tstr);
        if (strlen(tstr) > 0)
        {
          td[i] = atoi(tstr);
          memset(tstr, 0, sizeof(tstr));
          sscanf(str, "%*[^.].%[^'\']", tstr);
          memcpy(str, tstr, sizeof(str));
        }
        else
        {
          break;
        }
      }
      if (i == 4)
      {
        for (i = 0; i < 4; i++)
        {
          ethernet.ip[i] = td[i];
        }
        IIC_Write_Nbyte(ethernet.ip, ETHER_ADD_IP, 4);
        i = 1;
      }
      else
      {
        i = 0;
      }
    }
    else if (strcmp(str, "sm") == 0)
    {
      memset(str, 0, sizeof(str));
      sscanf(p, "%*s %*s %*s %s", str);
      for (i = 0; i < 4; i++)
      {
        memset(tstr, 0, sizeof(tstr));
        sscanf(str, "%[^.]", tstr);
        if (strlen(tstr) > 0)
        {
          td[i] = atoi(tstr);
          memset(tstr, 0, sizeof(tstr));
          sscanf(str, "%*[^.].%[^'\']", tstr);
          memcpy(str, tstr, sizeof(str));
        }
        else
        {
          break;
        }
      }
      if (i == 4)
      {
        for (i = 0; i < 4; i++)
        {
          ethernet.sm[i] = td[i];
        }
        IIC_Write_Nbyte(ethernet.sm, ETHER_ADD_SUB, 4);
        i = 1;
      }
      else
      {
        i = 0;
      }
    }
    else if (strcmp(str, "gw") == 0)
    {
      memset(str, 0, sizeof(str));
      sscanf(p, "%*s %*s %*s %s", str);
      for (i = 0; i < 4; i++)
      {
        memset(tstr, 0, sizeof(tstr));
        sscanf(str, "%[^.]", tstr);
        if (strlen(tstr) > 0)
        {
          td[i] = atoi(tstr);
          memset(tstr, 0, sizeof(tstr));
          sscanf(str, "%*[^.].%[^'\']", tstr);
          memcpy(str, tstr, sizeof(str));
        }
        else
        {
          break;
        }
      }
      if (i == 4)
      {
        for (i = 0; i < 4; i++)
        {
          ethernet.gw[i] = td[i];
        }
        IIC_Write_Nbyte(ethernet.gw, ETHER_ADD_GW, 4);
        i = 1;
      }
      else
      {
        i = 0;
      }
    }
    else if (strcmp(str, "dns") == 0)
    {
      memset(str, 0, sizeof(str));
      sscanf(p, "%*s %*s %*s %s", str);
      for (i = 0; i < 4; i++)
      {
        memset(tstr, 0, sizeof(tstr));
        sscanf(str, "%[^.]", tstr);
        if (strlen(tstr) > 0)
        {
          td[i] = atoi(tstr);
          memset(tstr, 0, sizeof(tstr));
          sscanf(str, "%*[^.].%[^'\']", tstr);
          memcpy(str, tstr, sizeof(str));
        }
        else
        {
          break;
        }
      }
      if (i == 4)
      {
        for (i = 0; i < 4; i++)
        {
          ethernet.dns[i] = td[i];
        }
        IIC_Write_Nbyte(ethernet.dns, ETHER_ADD_DNS, 4);
        i = 1;
      }
      else
      {
        i = 0;
      }
    }
    else if (strcmp(str, "rip") == 0)
    {
      memset(str, 0, sizeof(str));
      sscanf(p, "%*s %*s %*s %s", str);
      for (i = 0; i < 4; i++)
      {
        memset(tstr, 0, sizeof(tstr));
        sscanf(str, "%[^.]", tstr);
        if (strlen(tstr) > 0)
        {
          td[i] = atoi(tstr);
          memset(tstr, 0, sizeof(tstr));
          sscanf(str, "%*[^.].%[^'\']", tstr);
          memcpy(str, tstr, sizeof(str));
        }
        else
        {
          break;
        }
      }
      if (i == 4)
      {
        for (i = 0; i < 4; i++)
        {
          ethernet.rip[i] = td[i];
        }
        IIC_Write_Nbyte(ethernet.rip, ETHER_ADD_RIP, 4);
        i = 1;
      }
      else
      {
        i = 0;
      }
    }
    else if (strcmp(str, "port") == 0)
    {
      memset(str, 0, sizeof(str));
      sscanf(p, "%*s %*s %*s %[0123456789]", str);
      if (strlen(str) > 0)
      {
        ethernet.port = atoi(str);
        IICx = IIC0;
        IIC_Write_2Byte(ETHER_ADD_PORT, ethernet.port);
        i = 1;
      }
      else
      {
        i = 0;
      }
    }

    if (i == 1)
    { // 重新初始化
      printfx(p);
      printfx(" pass\r\n");
      set_w5500_netinfo();
    }
    else
    {
      printfx(p);
      printfx(" fail\r\n");
    }
  }
  else if (strcmp(str, "r") == 0)
  {
    memset(str, 0, sizeof(str));
    sscanf(p, "%*s %*s %s", str);
    gLowerCaseString(str);

    if (strcmp(str, "mac") == 0)
    {
      sprintfx("mac:%02X-%02X-%02X-%02X-%02X-%02X\r\n", ethernet.mac[0], ethernet.mac[1], ethernet.mac[2], ethernet.mac[3], ethernet.mac[4], ethernet.mac[5]);
    }
    else if (strcmp(str, "ip") == 0)
    {
      sprintfx("IP:%d.%d.%d.%d\r\n", ethernet.ip[0], ethernet.ip[1], ethernet.ip[2], ethernet.ip[3]);
    }
    else if (strcmp(str, "sm") == 0)
    {
      sprintfx("sm:%d.%d.%d.%d\r\n", ethernet.sm[0], ethernet.sm[1], ethernet.sm[2], ethernet.sm[3]);
    }
    else if (strcmp(str, "gw") == 0)
    {
      sprintfx("gw:%d.%d.%d.%d\r\n", ethernet.gw[0], ethernet.gw[1], ethernet.gw[2], ethernet.gw[3]);
    }
    else if (strcmp(str, "dns") == 0)
    {
      sprintfx("dns:%d.%d.%d.%d\r\n", ethernet.dns[0], ethernet.dns[1], ethernet.dns[2], ethernet.dns[3]);
    }
    else if (strcmp(str, "rip") == 0)
    {
      sprintfx("rip:%d.%d.%d.%d\r\n", ethernet.rip[0], ethernet.rip[1], ethernet.rip[2], ethernet.rip[3]);
    }
    else if (strcmp(str, "port") == 0)
    {
      sprintfx("port:%d\r\n", ethernet.port);
    }
    else if (strcmp(str, "all") == 0)
    {
      sprintfx("mac:%02X-%02X-%02X-%02X-%02X-%02X\r\n", ethernet.mac[0], ethernet.mac[1], ethernet.mac[2], ethernet.mac[3], ethernet.mac[4], ethernet.mac[5]);
      sprintfx("IP:%d.%d.%d.%d\r\n", ethernet.ip[0], ethernet.ip[1], ethernet.ip[2], ethernet.ip[3]);
      sprintfx("sm:%d.%d.%d.%d\r\n", ethernet.sm[0], ethernet.sm[1], ethernet.sm[2], ethernet.sm[3]);
      sprintfx("gw:%d.%d.%d.%d\r\n", ethernet.gw[0], ethernet.gw[1], ethernet.gw[2], ethernet.gw[3]);
      sprintfx("dns:%d.%d.%d.%d\r\n", ethernet.dns[0], ethernet.dns[1], ethernet.dns[2], ethernet.dns[3]);
      sprintfx("rip:%d.%d.%d.%d\r\n", ethernet.rip[0], ethernet.rip[1], ethernet.rip[2], ethernet.rip[3]);
      sprintfx("port:%d\r\n", ethernet.port);
      sprintfx("ver:%d%d\r\n", ethernet.sw_ver[0], ethernet.sw_ver[1]);
    }
    else
    {
      printfx(p);
      printfx(" fail\r\n");
    }
  }
  else
  {
    printfx(p);
    printfx(" fail\r\n");
  }

  return 0;
}

/***************************************************************************
** 函数名称:
** 功能描述:
** 输入参数: 	 无
** 返 回 值: 	 无
** 全局变量:
** 调用模块:
** 作　  者:   M-L-A
** 日　  期:   2022-5-26
** 修改原因：
** 说    明:    字数--ASCII;  0--30; 9--39;
;***************************************************************************/
char SetupDUT(void *p, ...)
{
  char str[48] = {0};
  int i;
  BitStructure16 st;

  memset(str, 0, sizeof(str));
  sscanf(p, "%*s %s", str);
  gLowerCaseString(str);

  if (strcmp(str, "w") == 0)
  {
    memset(str, 0, sizeof(str));
    sscanf(p, "%*s %*s %s %d", str, &i);
    gLowerCaseString(str);

    if (strcmp(str, "spp") == 0)
    { // 并行切换DUT通道
      st.regis = i;
      DUT_D0(st.bit.b0);
      DUT_D1(st.bit.b1);
      DUT_D2(st.bit.b2);
      DUT_D3(st.bit.b3);
      DUT_D4(st.bit.b4);
      DUT_D5(st.bit.b5);
      DUT_D6(st.bit.b6);
      DUT_D7(st.bit.b7);
      delay_ms(1);
      DUT_STROBE(0); // 触发
      delay_ms(3);
      DUT_STROBE(1);
    }
    else if (strcmp(str, "pow") == 0)
    {
      DUT_POWER(i);
      printfx(p);
      printfx(" pass\r\n");
    }
    else
    {
      printfx(p);
      printfx(" fail\r\n");
    }
  }
  else
  {
    printfx(p);
    printfx(" fail\r\n");
  }

  return 0;
}

/***************************************************************************
** 函数名称:
** 功能描述:
** 输入参数: 	 无
** 返 回 值: 	 无
** 全局变量:
** 调用模块:
** 作　  者:   M-L-A
** 日　  期:   2022-5-26
** 修改原因：
** 说    明:    字数--ASCII;  0--30; 9--39;
;***************************************************************************/
char SetupLCD(void *p, ...)
{
  char str[48] = {0};
  int i;

  memset(str, 0, sizeof(str));
  sscanf(p, "%*s %s", str);
  gLowerCaseString(str);

  if (strcmp(str, "w") == 0)
  {
    memset(str, 0, sizeof(str));
    sscanf(p, "%*s %*s %s %d", str, &i);
    gLowerCaseString(str);

    if (strcmp(str, "blk") == 0)
    {
      if (i > 100)
      {
        i = 100;
      }
      pLCD->blk = i; //*BLK_SRV/100+BLK_MIN;	//100%->4095
      IICx = IIC0;
      IIC_Write_2Byte(LCD_ADD_BLK, pLCD->blk);
      SetOutputVoltageDAC1(pLCD->blk * BLK_SRV / 100 + BLK_MIN);
      if (setups.step)
      {
        if (setups.page == 0)
        {
          BringhtnessGUI(GREEN, BLACK);
        }
      }
      printfx(p);
      printfx(" pass\r\n");
    }
    else if (strcmp(str, "title") == 0)
    {
      memset(pLCD->title, 0, 17);
      sscanf(p, "%*s %*s %*s %s", pLCD->title);
      //			memcpy(pLCD->title,str1,16);
      IICx = 0;
      IIC_Write_Nbyte(pLCD->title, LCD_ADD_TITLE, 16);
      if (!setups.step)
      {
        i = strlen((char *)pLCD->title);
        i = i / 2 + 1;
        i = i * 16;
        LCD_Fill(0, 0, 320, 42, GRAY0);
        LCD_ShowASCII(160 - i, 10, pLCD->title, GRAYBLUE, GRAY0, ASC_16X32, 0);
      }
      printfx(p);
      printfx(" pass\r\n");
    }
    else
    {
      printfx(p);
      printfx(" fail\r\n");
    }
  }
  else if (strcmp(str, "r") == 0)
  {
    memset(str, 0, sizeof(str));
    sscanf(p, "%*s %*s %s", str);
    gLowerCaseString(str);

    if (strcmp(str, "blk") == 0)
    {
      //			i=((double)(pLCD->blk-BLK_MIN))*1000/BLK_SRV;
      //			if((i%10)>5)
      //			{i=i/10+1;}
      //			else
      //			{i=i/10;}
      sprintfx("blk:%d%%\r\n", pLCD->blk);
    }
    else if (strcmp(str, "title") == 0)
    {
      printfx((char *)pLCD->title);
      printfx("\r\n");
    }
  }
  else
  {
    printfx(p);
    printfx(" fail\r\n");
  }

  return 0;
}

/***************************************************************************
** 函数名称:
** 功能描述:
** 输入参数: 	 无
** 返 回 值: 	 无
** 全局变量:
** 调用模块:
** 作　  者:   M-L-A
** 日　  期:   2022-5-26
** 修改原因：
** 说    明:    字数--ASCII;  0--30; 9--39;
;***************************************************************************/
char SendButtonValue(void *p, ...)
{
  int i;

  sscanf(p, "%*s %d", &i);

  if (i == 4604498)
  {
    IICx = 0;
    IIC_Write_Data(0, 0);
    __NVIC_SystemReset();
  }
  else
  {
    pkey->value = i;

    printfx(p);
    printfx(" pass\r\n");
  }
  return 0;
}

/***************************************************************************
** 函数名称:
** 功能描述:
** 输入参数: 	 无
** 返 回 值: 	 无
** 全局变量:
** 调用模块:
** 作　  者:   M-L-A
** 日　  期:   2025-7-21
** 修改原因：
** 说    明:    字数--ASCII;  0--30; 9--39;
;***************************************************************************/
char SetBoardIndex(void *p, ...)
{
  char str[8] = {0};
  int index = 0;

  memset(str, 0, sizeof(str));
  sscanf(p, "%*s %s", str);
  gLowerCaseString(str);
  if (strcmp(str, "?") == 0)
  {
    sprintfx("##: %d\r\n", BoardIndex);
  }
  else if (strcmp(str, "w") == 0)
  {
    sscanf(p, "%*s %*s %d", &index);
    if ((index < setups.dport) || (index >= (setups.dport + setups.nport)))
    {
      printfx(p);
      printfx(" fail\r\n");
    }
    else
    {
      BoardIndex = index;
      if (BoardIndex > 0)
      {
        IndexTimeDec = setups.bTime;
      }
      printfx(p);
      printfx(" pass\r\n");
    }
  }
  else
  {
    printfx(p);
    printfx(" fail\r\n");
  }
  return 0;
}
