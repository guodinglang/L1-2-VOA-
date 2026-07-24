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
#include "spiFlash.h"

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
    unsigned char i,len;
    
    len=strlen(str);
    for(i=0;i<len;i++)
    {
	    if((str[i]>='A')&&(str[i]<='Z'))
	    {
		    str[i]=str[i]+0x20; 
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
void rxCommand(void)
{
	uint8_t n,x,c=0xff;
	char Tstr[12]={0,0,0,0,0,0,0,0,0,0,0,0};	
	
	
	if(pUART->len >= RX_MAX_FIFO)
	{	//超出长度
		memset(pUART->rxFIFO,0,RX_MAX_FIFO);
		pUART->len = 0;
		pUART->rxn = 0;
		pUART->reTx = 0;
	}
//--------返回每一个字符处理----------------------------------------------------    
	if(pUART->feelback==true)
	{
		while(pUART->len > pUART->reTx) 
		{printx(pUART->rxFIFO[pUART->reTx++]);}	
		if(pUART->rxn)
		{printfx("\r\n");}
	}
//--------指令判断--------------------------------------------------------------  
	if(pUART->rxn > 0)
	{
		if(pUART->len > 0)
		{
//			sscanf((const char *)pUART->rxFIFO,"%[^_| ]",Tstr);
			x=0;
			for(n=0;n<pUART->len;n++)
			{
				if((pUART->rxFIFO[n] >='a' && pUART->rxFIFO[n]<='z')||(pUART->rxFIFO[n] >='A' && pUART->rxFIFO[n]<='Z'))
				{break;}
				else
				{x++;}
			}
			
			if(x < pUART->len)
			{//头码
				memset(Tstr,0,sizeof(Tstr));
				for(n=0;n<10;n++)
				{
					c = pUART->rxFIFO[x+n];
					if((c == ' ')||(c == '_')||(c == '\0')||(c == '>'))	
					{break;}
					else
					{Tstr[n] = c;}
				}
				gLowerCaseString(Tstr);
				c = 0xff;
				for(n=0;n<cmdStrLen;n++)  ///匹配命令编号
				{						
					if(strcmp(Tstr,cmdMessage[n].cmdStr) == 0)	//NULL)
					{ 
						c = n;
						break;
					}
				}			 		
			}
			else
			{n = cmdStrLen;}
			
			if(n >= cmdStrLen)
			{				
			   printfx("<ER>"); //输入的命令非法 
			}
			else if(c!=0xff)
			{	//执行函数
				cmdMessage[c].func(pUART->rxFIFO);			
			}
			memset(pUART->rxFIFO,0,RX_MAX_FIFO);
			pUART->len = 0;		
		}
		else
		{printfx("\r\n<>\r\n");}
		
		pUART->reTx=0;
		pUART->rxn=0;
	}	
	else if(pUART->TimeOut <= 0)
	{
		if(pUART->len | pUART->rxn)
		{
			memset(pUART->rxFIFO,0,RX_MAX_FIFO);
			pUART->len = 0;
			pUART->reTx=0;
			pUART->rxn=0; 
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
char help(void *p,...)
{
	uint8_t i;
	for(i=0; i<cmdStrLen; i++)
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
char RebackCharacter(void *p,...)
{
	int s;
	
	sscanf(p, "%*s %d",&s);	
	if(s==0)
	{
		pUART->feelback = false;
		pUART->reTx=0;
		printfx(p);
		printfx(" pass\r\n");
	}
	else if(s==1)
	{
		pUART->feelback = true;
		pUART->reTx=pUART->len;
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
char ReadVersion(void *p,...)
{
//	printfx("\r\nPCB:B3-1,PGR:V29\r\n");	
	char i,c,n,j,str[25]={0};
	
	memset(str,0,sizeof(str));
	for(i=0,j=0,n=0;c!='\0';i++)
	{
		c =((char *)p)[i];
		if(c=='_' || c==' ')
		{n++;}
		else if(n > 0)
		{str[j++]=c;}
		if(n > 1)
		{break;}
	}
	gLowerCaseString(str);
	
	if(strcmp(str,"?")==0)
	{
		printfx("<");
		printfx((char *)params.ver);
		printfx(">"); 		
	}
	else if(strcmp(str,"w")==0)
	{
		memset(str,0,sizeof(str));
		for(i=0,j=0,n=0;c!='\0';i++)
		{
			c =((char *)p)[i];
			if((c=='_' || c==' ')&&(n < 2))
			{n++;}
			else if(n > 1)
			{str[j++]=c;}
		}
		n=strlen(str);
		if(n>0 && n<24)
		{
			memcpy(params.ver,str,sizeof(params.ver));
			//SaveParamet(FLASH_SECTION_PARAMETER,&params);
			printfx(p);printfx("_OK>");
		}
		else
		{printfx("<ER>");}
	}
	else
	{printfx("<ER>");}
	
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
** 日　  期:   2019-9-16
** 修改原因：
** 说    明:    字数--ASCII;  0--30; 9--39;
;***************************************************************************/
char SystemReset(void *p,...)
{
	printfx(p);
	printfx("_OK>");
	delay_ms(30);
	NVIC_SystemReset();
	
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
** 日　  期:   2019-9-16
** 修改原因：
** 说    明:    字数--ASCII;  0--30; 9--39;
;***************************************************************************/
char FactoryReset(void *p,...)
{
	ReadParamet(FLASH_SECTION_FACTORY,&params);
	params.ss=0;
	SaveParamet(FLASH_SECTION_PARAMETER,&params);
//	flash_read_level(params.nCH);
	
//	printfx(p);
	printfx("<RESET_OK>");
	delay_ms(30);
	NVIC_SystemReset();
	
	return 0;
}

/***************************************************************************
** 函数名称:  	SetPassWord
** 功能描述:  	 
** 输入参数: 	 无
** 返 回 值: 	 无
** 全局变量: 
** 调用模块: 
** 作　  者:   M-L-A
** 日　  期:   2020-1-29
** 修改原因：
** 说    明:    
;***************************************************************************/
char ReadWriteBoardIDN(void *p,...)
{
	int k=0;
	char str[144]={0};
	
	memset(str,0,sizeof(str));
	sscanf(p,"%*[^_]_%[^_]",str);
	gLowerCaseString(str);
	
	if(strcmp(str,"?")==0)
	{
		printfx("<");
		printfx((char *)params.IDN);
		printfx(">"); 		
	}
	else if(strcmp(str,"w")==0)
	{
		memset(str,0,sizeof(str));
		sscanf(p,"%*[^_]_%*[^_]_%[^'\']",str);
		k = strlen(str);	
		if((k > 0)&&(k < 128))
		{
			memset(params.IDN,0,128);
			memcpy(params.IDN,str,k);
			//SaveParamet(FLASH_SECTION_PARAMETER,&params);
			printfx(p);
			printfx("_OK>");
		}
		else
		{printfx("<ER>");}  
	}
	else
	{printfx("<ER>");}
	
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
** 日　  期:   2019-9-16
** 修改原因：
** 说    明:    字数--ASCII;  0--30; 9--39;
;***************************************************************************/
char BaudrateUART(void *p,...)
{//串口波特率
	char str[64]={0};
	memset(str,0,sizeof(str));
	sscanf(p,"%*[^_]_%[^'\']",str);
	if(strcmp(str,"?")==0)
	{//查询
		char str1[8]={0};
		memset(str1,0,sizeof(str1));
		strncpy(str1,p,5);
		printfx(str1);	
		sprintfx("_%d>",params.baud);			
	}
	else
	{
		int k=0;
		memset(str,0,sizeof(str));
		sscanf(p,"%*[^_]_%[0123456789]",str);
		k = atoi(str);
		if(strlen(str)>0 && k>0 && k<22)
		{
			params.baud=k;
			//SaveParamet(FLASH_SECTION_PARAMETER,&params);
			printfx(p);printfx("_OK>");				
		}
		else 
		{printfx("<ER>");}	
	}	
	return 0;
}
/***************************************************************************
** 函数名称:  	SaveSelectSwitch
** 功能描述:  	 
** 输入参数: 	 无
** 返 回 值: 	 无
** 全局变量: 
** 调用模块: 
** 作　  者:   M-L-A
** 日　  期:   2022-3-1
** 修改原因：
** 说    明:    字数--ASCII;  0--30; 9--39;
;***************************************************************************/
char SaveSelectSwitch(void *p,...)
{
	char str[24]={0};
	
	memset(str,0,sizeof(str));
	sscanf(p,"%*[^_]_%[^'\']",str);
	gLowerCaseString(str);
	
	if(strcmp(str,"all")==0)
	{
		stateVOA('w');
		SaveParamet(FLASH_SECTION_PARAMETER,&params);
		printfx(p);printfx("_OK>");		
	}
	else 
	{printfx("<ER>");}	
	
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
** 日　  期:   2019-9-16
** 修改原因：
** 说    明:    字数--ASCII;  0--30; 9--39;
;***************************************************************************/
char ReadSelectSwitch(void *p,...)
{
	char str[24]={0};
	VOAsturct tp;
	
	memset(str,0,sizeof(str));
	sscanf(p,"%*[^_]_%[^_|' ']",str);
	
	if(strlen(str)>0)
	{
		tp.cp = atoi(str);
		if(tp.cp>0 && tp.cp<=(params.cp-1))
		{
			memset(str,0,sizeof(str));
			sscanf(p,"%*[^_]_%*[^_]_%[^_]",str);
			if(strlen(str) > 0)
			{
				gLowerCaseString(str);
				if(strcmp(str,"att")==0)
				{//设置衰减
					tp.wl = sVOA[tp.cp-1].wl;	//atoi(str);
					memset(str,0,sizeof(str));
					sscanf(p,"%*[^_]_%*[^_]_%*[^_]_%[^'\']",str);
					if(strlen(str) > 0)
					{
						double db = atof(str);
						if((db <= 120.1f)&&(tp.wl >0))
						{
							if(db<5.0)
							{//小于
								tp.db=db;
								if(0==CalculatingLevel(&tp))
								{
									uint8_t m,i,n=0;
									IIC_WriteGP8211S(&tp.vo,tp.cp);//第一个器件
									memcpy(&sVOA[tp.cp-1],&tp,sizeof(tp));
									
									tp.vo=0;tp.cp++;tp.db=0.0;
									IIC_WriteGP8211S(&tp.vo,tp.cp);//第二个器件
									memcpy(&sVOA[tp.cp-1],&tp,sizeof(tp));
									
									m=strlen(p);
									for(i=0;i<m;i++)
									{
										if(((char *)p)[i]=='_')
										{n++;}
										if(n>=3)
										{break;}
									}
									((char *)p)[++i]=0;
									printfx(p);
									printfx("OK>");
								}
								else
								{printfx("<ER>");}
							}
							else
							{
								tp.db=db/2;
								if(0==CalculatingLevel(&tp))
								{//第一个器件
									IIC_WriteGP8211S(&tp.vo,tp.cp);
									tp.db=db;
									memcpy(&sVOA[tp.cp-1],&tp,sizeof(tp));
									
									tp.db=db/2;
									tp.cp++;
									if(0==CalculatingLevel(&tp))
									{
										//第二个器件
										uint8_t i,m,c,n=0;
										
										IIC_WriteGP8211S(&tp.vo,tp.cp);
										memcpy(&sVOA[tp.cp-1],&tp,sizeof(tp));
										
										m=strlen(p);
										for(i=0;i<m;i++)
										{
											c=((char *)p)[i];
											if(c =='_')
											{n++;}
											if(n>=3)
											{break;}
										}
										((char *)p)[++i]=0;
										printfx(p);
										printfx("OK>");
									}
									else
									{printfx("<ER>");}
								}
								else
								{printfx("<ER>");}
							}
						}
						else
						{printfx("<ER>");}
					}
					else
					{printfx("<ER>");}
				}
				else if(strcmp(str,"w")==0)
				{//设置波长
					memset(str,0,sizeof(str));
					sscanf(p,"%*[^_]_%*[^_]_%*[^_]_%[^'\']",str);
					tp.wl=atoi(str);
					if((strlen(str)>0)&&(tp.wl>0)&&(tp.wl<0xffff))	//((tp.wl==850)||(tp.wl==1310)||(tp.wl==1550))
					{
						uint8_t i,m,c,n=0;
						
						sVOA[tp.cp-1].wl=tp.wl;
						m=strlen(p);
						for(i=0;i<m;i++)
						{
							c=((char *)p)[i];
							if(c =='_')
							{n++;}
							printx(c);
							if(n>=3)
							{break;}
						}
						printfx("OK>");
					}
					else
					{printfx("<ER>");}
				}
				else if(strcmp(str,"a")==0)
				{
					memset(str,0,sizeof(str));
					sscanf(p,"%*[^_]_%*[^_]_%*[^_]_%[^'\']",str);
					if(strcmp(str,"?")==0)
					{sprintfx("<VOA_%d_%04d_%0.2f>",tp.cp,sVOA[tp.cp-1].wl,sVOA[tp.cp-1].db);}
					else
					{printfx("<ER>");}
				}
				else
				{printfx("<ER>");}
			}
			else
			{printfx("<ER>");}
		}
		else
		{printfx("<ER>");}
	}
	else
	{printfx("<ER>");}
	
	return 0;
}


/***************************************************************************
** 函数名称:  	ReadParameter
** 功能描述:  	 
** 输入参数: 	 无
** 返 回 值: 	 无
** 全局变量: 
** 调用模块: 
** 作　  者:   M-L-A
** 日　  期:   2022-3-1
** 修改原因：
** 说    明:    字数--ASCII;  0--30; 9--39;
;***************************************************************************/
char ReadWriteMaxCH(void *p,...)
{
	
	char str[24]={0};
	
	memset(str,0,sizeof(str));
	sscanf(p,"%*s %s",str);	
	gLowerCaseString(str);
	if((strcmp(str,"?")==0)||(strlen(str)<=0))
	{
		sprintfx("<CP:%d WL:%d MPN:%d>",params.cp-1,params.nwl,params.mpn);
	}
	else if(strcmp(str,"w")==0)
	{
		int cp,wl,mpn;
		sscanf(p,"%*s %*s %d %d %d",&cp,&wl,&mpn);
		if((cp>0 && cp<= VOA_NUM)&&(wl>0 && wl<=16)&&(mpn>0 && mpn<=400))
		{
			params.cp = cp+1;
			params.nwl = wl;
			params.mpn = mpn;
			SaveParamet(FLASH_SECTION_PARAMETER,&params);
			printfx(p);printfx(" OK>");
		}
		else 
		{printfx("<ER>");}			
	}	
	else 
	{printfx("<ER>");}
	
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
** 日　  期:   2019-9-16
** 修改原因：
** 说    明:    字数--ASCII;  0--30; 9--39;
;***************************************************************************/
char LevelValueDispose(void *p,...)
{
	int i=0,w=0,nwl,sq;
	char str[4]={0,0,0,0};
	double fv[2]={0.0,0.0};
	VOAsturct tp;
	
	sscanf(p,"%*s %s",str);
	gLowerCaseString(str);	
	if(strcmp(str,"w")==0)
	{//write
		sscanf(p,"%*s %*s %d %d %lf %lf %d %d",&i,&w,&fv[0],&fv[1],&nwl,&sq);
		if((i>0 && i <= params.cp)&&(nwl>0 && nwl <= params.nwl)&&(sq <= params.mpn)&&(fv[1] <= REFERENCE))
		{	
			tp.cp=i;
			tp.wl=w;
			tp.db=fv[0];
			tp.vo=fv[1]*32767/REFERENCE;
			tp.wp=nwl;
			tp.sq=sq;
			//StorageDevice(&tp);
			IIC_WriteGP8211S(&tp.vo,i);
			memcpy(&slvd,&tp,sizeof(tp));
			
			printfx(p);
			printfx(" OK>");	
		}
		else
		{printfx("<ER>");}			
	}
	else if(strcmp(str,"r")==0)
	{//read
		sscanf(p,"%*s %*s %d %d %d",&i,&nwl,&sq);
		if((i>0 && i <= params.cp)&&(nwl>0 && nwl <= params.nwl)&&(sq <= params.mpn))
		{
			float fv;
			memset(&tp,0,sizeof(tp));
			tp.cp=i;
			tp.wp=nwl;
			tp.sq=sq;
			if(QueryPoint(&tp) <0)
			{memset(&tp,0,sizeof(tp));}
			fv = REFERENCE*tp.vo/32767;
			sprintfx("<CP:%d; WL:%d; DB:%0.3f; V:%0.3f; WP:%d; SQ:%d>",tp.cp,tp.wl,tp.db,fv,tp.wp,tp.sq);
		}
		else
		{printfx("<ER>");}
	}	
	else
	{printfx("<ER>");}

	
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
char SetReadWrite(void *p,...)
{
	char r=0,str[48]={0};
	int i=0,k;
	
	memset(str,0,sizeof(str));
    sscanf(p,"%*s %s",str);
    
	gLowerCaseString(str);
	if(strcmp(str,"w")==0)
	{
		memset(str,0,sizeof(str));
		sscanf(p,"%*s %*s %s",str);
		gLowerCaseString(str);
		
		if(strcmp(str,"res")==0)
		{
			__NVIC_SystemReset();	//
		}
		else if(strcmp(str,"ls")==0)
		{//save level
			StorageDevice(&slvd);
			r=1;
		}
		else if(strcmp(str,"ver")==0)
		{
			ParameterSturct tpar;
			ReadParamet(FLASH_SECTION_FACTORY,&tpar);
			memset(str,0,sizeof(str));
			sscanf(p,"%*s %*s %*s %s",str);
			k=strlen(str);
			if(k>0 && k<24)
			{
				memcpy(tpar.ver,str,24);
				SaveParamet(FLASH_SECTION_FACTORY,&tpar);
				memcpy(params.ver,str,24);
				SaveParamet(FLASH_SECTION_PARAMETER,&tpar);
				r=2;
			}
			
		}
		else if(strcmp(str,"info")==0)
		{
			ParameterSturct tpar;
			ReadParamet(FLASH_SECTION_FACTORY,&tpar);
			memset(str,0,sizeof(str));
			sscanf(p,"%*s %*s %*s %[^'\']",str);
			k=strlen(str);
			if(k>0 && k<128)
			{
				memcpy(tpar.IDN,str,128);
				SaveParamet(FLASH_SECTION_FACTORY,&tpar);
				memcpy(params.IDN,str,128);
				SaveParamet(FLASH_SECTION_PARAMETER,&tpar);
				r=3;
			}
		}
		else if(strcmp(str,"id")==0)
		{
			ParameterSturct tpar;
			ReadParamet(FLASH_SECTION_FACTORY,&tpar);
			memset(str,0,sizeof(str));
			sscanf(p,"%*s %*s %*s %s",str);
			k=atoi(str);
			if(strlen(str)>0 && k>0 && k<255)
			{
				tpar.ID=k;
				SaveParamet(FLASH_SECTION_FACTORY,&tpar);
				params.ID=k;
				SaveParamet(FLASH_SECTION_PARAMETER,&tpar);
				r=4;
			}
		}
		else if(strcmp(str,"baud")==0)
		{
			ParameterSturct tpar;
			ReadParamet(FLASH_SECTION_FACTORY,&tpar);
			memset(str,0,sizeof(str));
			sscanf(p,"%*s %*s %*s %s",str);
			k=atoi(str);
			if(strlen(str)>0 && k>0 && k<22)
			{
				tpar.baud=k;
				SaveParamet(FLASH_SECTION_FACTORY,&tpar);
				params.baud=k;
				SaveParamet(FLASH_SECTION_PARAMETER,&tpar);
				r=5;
			}
		}
		else if(strcmp(str,"max")==0)
		{
			int cp,wl,mpn;
			ParameterSturct tpar;
			ReadParamet(FLASH_SECTION_FACTORY,&tpar);
			sscanf(p,"%*s %*s %*s %d %d %d",&cp,&wl,&mpn);
			if((cp>0 && cp<= VOA_NUM)&&(wl>0 && wl<=16)&&(mpn>0 && mpn<=400))
			{
				tpar.cp = cp+1;
				tpar.nwl = wl;
				tpar.mpn = mpn;
				SaveParamet(FLASH_SECTION_FACTORY,&tpar);
				params.cp = cp+1;
				params.nwl = wl;
				params.mpn = mpn;
				SaveParamet(FLASH_SECTION_PARAMETER,&params);
				r=6;
			}
		}
		else if(strcmp(str,"wl")==0)
		{//defualt wave length
			ParameterSturct tpar;
			ReadParamet(FLASH_SECTION_FACTORY,&tpar);
			sscanf(p,"%*s %*s %*s %d",&k);
			if(k >0)
			{
				tpar.wl=k;
				SaveParamet(FLASH_SECTION_FACTORY,&tpar);
				params.wl=k;
				SaveParamet(FLASH_SECTION_PARAMETER,&tpar);
				r=15;
			}
		}
		else if(strcmp(str,"fmdp")==0)
		{//工厂模式通道默认值设置
			uint8_t *tp,tar[10]={0};
			int cp,wl,vo;
			float fv[2]={0,0};
			
			sscanf(p,"%*s %*s %*s %d %d %f %f",&cp,&wl,&fv[0],&fv[1]);
			if(cp >0)
			{
				ParameterSturct tpar;
				ReadParamet(FLASH_SECTION_FACTORY,&tpar);
				tpar.ss=1;
				SaveParamet(FLASH_SECTION_FACTORY,&tpar);
				
				spi_flash_erase_sector(SPIF_SECTION_INTERIM); //
				vo=((double)fv[1])*32767/REFERENCE; //电压
				for(i=0;i<406;i++)
				{
					spi_flash_read(tar,SPIF_SECTION_FCH+i*10,10);
					spi_flash_write(tar,SPIF_SECTION_INTERIM+i*10,10);
				}
				spi_flash_erase_sector(SPIF_SECTION_FCH);
				for(i=0;i<406;i++)
				{
					memset(tar,0,sizeof(tar));
					if(i == (cp-1))
					{
						tar[0]=vo>>8;
						tar[1]=vo;
						tar[2]=wl>>8;
						tar[3]=wl;
						tp=(uint8_t *)&fv[0];	//衰减
						tar[4]=tp[0];
						tar[5]=tp[1];
						tar[6]=tp[2];
						tar[7]=tp[3];
						spi_flash_write(tar,SPIF_SECTION_FCH+i*10,10);
					}
					else
					{
						spi_flash_read(tar,SPIF_SECTION_INTERIM+i*10,10);
						spi_flash_write(tar,SPIF_SECTION_FCH+i*10,10);
					}
				}
				r=7;
			}
		}
		else if(strcmp(str,"dacp")==0)
		{//dac power
			memset(str,0,sizeof(str));
			sscanf(p,"%*s %*s %*s %[0123456789]",str);
			if(strlen(str) >0)
			{
				if(atoi(str)>0)
				{DAC_POWER(1);}
				else
				{DAC_POWER(0);}
				r=8;
			}
		}
		else if(strcmp(str,"svo")==0)
		{//set dac voltage output
			double fv;
			uint16_t v;
			
			sscanf(p,"%*s %*s %*s %d %lf",&i,&fv);
			if(i>0 && fv<=10.0f)
			{
				v = fv*32767/REFERENCE;
				IIC_WriteGP8211S(&v,i);
				r=9;
			}
		}
		else if(strcmp(str,"ss")==0)
		{//save state
			if(stateVOA('w')==0)
			{r=10;}
		}
		else if(strcmp(str,"cs")==0)
		{//clear state
			if(stateVOA('c')==0)
			{r=11;}
		}
		else if(strcmp(str,"cf")==0)
		{//clear SPI flash
			spi_flash_erase_chip();
			r=12;
		}
		
		
		if(r >0)
		{printfx(p);printfx(" OK>");}
		else
		{printfx("<ER>");}
	}
	else if(strcmp(str,"r")==0)
	{
		memset(str,0,sizeof(str));
		sscanf(p,"%*s %*s %s",str);
		gLowerCaseString(str);
		
		if(strcmp(str,"id")==0)
		{
			sprintfx("<ID: %d>",params.ID);
		}
		else if(strcmp(str,"baud")==0)
		{
			sprintfx("<baud: %d>",IndexToBaudrate(params.baud));
		}
		else if(strcmp(str,"temp")==0)
		{//temperature
			sprintfx("<temp: %0.2f>",sTempere.tValue);
		}
		else if(strcmp(str,"wl")==0)
		{//defualt wave length
			ParameterSturct tpar;
			ReadParamet(FLASH_SECTION_FACTORY,&tpar);
			sprintfx("<WL: %d>",tpar.wl);
		}
		else if(strcmp(str,"fmdp")==0)
		{//工厂模式通道默认值设置
			uint8_t *tp,tar[10]={0};
			uint16_t wl;
			float db,vo;
			sscanf(p,"%*s %*s %*s %d",&i);
			if(i >0)
			{
				memset(tar,0,sizeof(tar));
				spi_flash_read(tar,SPIF_SECTION_FCH + (i-1)*10,10);
				
				vo = (tar[0]<<8)|tar[1];
				wl = (tar[2]<<8)|tar[3];
				tp=(uint8_t *)&db;
				tp[0]=tar[4];
				tp[1]=tar[5];
				tp[2]=tar[6];
				tp[3]=tar[7];
				vo = ((double)REFERENCE)*vo/32767;
				sprintfx("<CP:%d; WL:%d; DB:%0.3f; V:%0.3f>",i,wl,db,vo);
			}
			else
			{printfx("<ER>");}
		}
		else
		{printfx("<ER>");}	
	}
	else
	{printfx("<ER>");}
	
	return 0;
}


