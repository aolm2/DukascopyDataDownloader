// MyEAClientDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "MyEAClient.h"
#include "MyEAClientDlg.h"

#include "Shlwapi.h"
#include "SelectDateDlg.h"

#include <math.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
END_MESSAGE_MAP()


// CMyEAClientDlg 对话框




CMyEAClientDlg::CMyEAClientDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CMyEAClientDlg::IDD, pParent)
{
	m_bcreated = false;
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);

	m_clientcount = 0;
	m_bBusy = false;

}

void CMyEAClientDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT1, m_edit);
}

BEGIN_MESSAGE_MAP(CMyEAClientDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()

	ON_MESSAGE(WM_EAMSG, OnEAMessage)
	//}}AFX_MSG_MAP
//	ON_WM_MOVE()
//	ON_WM_MOVING()
	ON_WM_SIZE()
	ON_EN_SETFOCUS(IDC_EDIT1, &CMyEAClientDlg::OnEnSetfocusEdit1)
	ON_WM_CTLCOLOR()
	ON_COMMAND(ID_FILE_DOWNLOADDUKASCOPYDATA, &CMyEAClientDlg::OnFileDownloaddukascopydata)
	ON_COMMAND(ID_VIEW_CLEAR, &CMyEAClientDlg::OnViewClear)
	ON_COMMAND(ID_HELP_ABOUT, &CMyEAClientDlg::OnHelpAbout)
	ON_COMMAND(ID_FILE_CONVERTBINTOCSVTICKFILE, &CMyEAClientDlg::OnFileConvertbintocsvtickfile)
	ON_COMMAND(ID_FILE_CONVERTRAW1MINFILETOHST1MIN, &CMyEAClientDlg::OnFileConvertraw1minfiletohst1min)
	ON_COMMAND(ID_FILE_CONVERTBINTORAW1MINFILE, &CMyEAClientDlg::OnFileConvertbintoraw1minfile)
	ON_UPDATE_COMMAND_UI(ID_FILE_DOWNLOADDUKASCOPYDATA, &CMyEAClientDlg::OnUpdateFileDownloaddukascopydata)
	ON_UPDATE_COMMAND_UI(ID_FILE_CONVERTBINTOCSVTICKFILE, &CMyEAClientDlg::OnUpdateFileConvertbintocsvtickfile)
	ON_UPDATE_COMMAND_UI(ID_FILE_CONVERTBINTORAW1MINFILE, &CMyEAClientDlg::OnUpdateFileConvertbintoraw1minfile)
	ON_UPDATE_COMMAND_UI(ID_FILE_CONVERTRAW1MINFILETOHST1MIN, &CMyEAClientDlg::OnUpdateFileConvertraw1minfiletohst1min)
END_MESSAGE_MAP()


// CMyEAClientDlg 消息处理程序

BOOL CMyEAClientDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。
	m_bcreated = true;
	CMenu* menu =new CMenu;
	menu->LoadMenu(MAKEINTRESOURCE(IDR_MENU1));      //红色部分为对应自己添加的菜单资源的名称
	this->SetMenu(menu);

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
	
	Init();


	
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CMyEAClientDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CMyEAClientDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CMyEAClientDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

LRESULT CMyEAClientDlg::OnEAMessage( WPARAM wParam, LPARAM lParam )
{
	if (wParam == WPARAM_VERIFY)
	{
		int cid = ++m_clientcount + 100;
		PrintText("Client ID: %d - New MT4 Window logged in. ",cid);
		return cid;
	}
	else if (wParam > 100)
	{
		int cid = wParam;
		CTime ctm(lParam - m_nLocalTimeShift * 3600);
		PrintText("Client ID: %d - New bar. %04d.%02d.%02d %02d:%02d:%02d ",cid,
			ctm.GetYear(),ctm.GetMonth(),ctm.GetDay(),ctm.GetHour(),ctm.GetMinute(),ctm.GetSecond());
		return RET_MSG_OK;
	}

	return RET_MSG_ERR;

}

/*************************************************
函数名称: ReadStringFromFile
修改日期: 2013-7-12
函数功能: 从某文本格式文件中读取全部文本到字符串
输入参数: 
 - strfilepath 某文本格式文件的路径
输出参数: 
	无。
返回值: 
	字符串，包含了文件的内容。
*************************************************/

CString ReadStringFromFile(CString strfilepath)
{
	FILE *infile =fopen(strfilepath,"rb");
	ASSERT(infile);
	fseek(infile,0,SEEK_END);
	int len = ftell(infile);

	char *pc = new char[len+1];
	memset(pc,'\0',len+1);

	fseek(infile,0,SEEK_SET);
	fread(pc, sizeof(char), len, infile);  
	fclose(infile);

	CString strout = pc;
	delete [] pc;

	return strout;
}

/*************************************************
函数名称: ReadPairGmtStartFrom
修改日期: 2013-7-13
函数功能: 读取currencypair.txt中start from的GMT时间
输入参数: 
 - strpath currencypair.txt的路径
 - strpair 货币对
输出参数: 
	无。
返回值: 
	该货币对start from的GMT时间，若读取失败返回0。
*************************************************/

UINT ReadPairGmtStartFrom(CString strpath, CString strpair)
{
	CStdioFile cFile;
	CString strLine;

	if(!cFile.Open(strpath, CFile::modeRead))
		return 0;

	UINT gmttm = 0;
	while(cFile.ReadString(strLine))
	{
		strLine.Trim();
		
		CString strpairread = strLine.Mid(1,6);
		if (strpair != strpairread)
			continue;

		int pos0,pos1;
		pos0 = strLine.Find("=> ");
		pos1 = strLine.Find(",");
		CString strstartfrom = strLine.Mid(pos0+3,pos1-pos0-3);
		strstartfrom.Trim();
		gmttm = atoi(strstartfrom);
		break;
	}

	cFile.Close();
	return gmttm;

}


/*************************************************
函数名称: ThreadDownloadBINFunc
修改日期: 2013-7-12
函数功能: 从Dukascopy下载数据的线程
输入参数: 
 - dwparam 存储了指向CDukascopyToHstDlg实例的指针
输出参数: 
	无。
返回值: 
	无。
全局调用:
	(in) m_strSymbol - 类成员变量，货币对
	(in) m_strPhppath
	(in) m_strPairpath
其他说明:
	下载的数据为原始的BIN格式。并且会自动补全到最近的时间。
*************************************************/

void ThreadDownloadBINFunc(DWORD dwparam)
{
	CMyEAClientDlg *pdlg = (CMyEAClientDlg*)dwparam;
	pdlg->PrintText("启动下载:");

	pdlg->m_bBusy = true;
	CString strpair = pdlg->m_strSymbol;

	/*写入my_download_data.php要调用的头文件currencies.php*/
	UINT gmttm = ReadPairGmtStartFrom(pdlg->m_strPairpath,pdlg->m_strSymbol);
	ASSERT(gmttm > 0);

	CString strrequirefilepath;
	strrequirefilepath = pdlg->m_strPhppath + "currencies.php";

	FILE *fp;
	fp = fopen(strrequirefilepath,"w");
	ASSERT(fp);
	fprintf(fp,"<?php $currencies = array(");
	fprintf(fp,"\"%s\" => %d,",strpair,gmttm);
	fprintf(fp,"); ?>");
	fclose(fp);
	
	/*计算需要执行的命令行字符串*/
	CString strcmd;
	strcmd.Format("%sphp my_download_data.php",pdlg->m_strPhppath);
	pdlg->PrintText(strcmd);

	/*计算命令行输出Log文件路径*/
	CString strstdfile;
	strstdfile.Format("%serror.log",pdlg->m_strPhppath);
	DeleteFile(strstdfile);

	/*执行命令行，等待直到结束*/
	PROCESS_INFORMATION ProcessInfo;
	STARTUPINFO StartupInfo; //This is an [in] parameter
	ZeroMemory(&StartupInfo, sizeof(StartupInfo));
	StartupInfo.cb = sizeof StartupInfo ; //Only compulsory field
	if(CreateProcessA(NULL,strcmd.GetBuffer(0),
		NULL,NULL,FALSE,0,NULL,
		pdlg->m_strPhppath,&StartupInfo,&ProcessInfo))
	{

		WaitForSingleObject(ProcessInfo.hProcess,INFINITE);
		CloseHandle(ProcessInfo.hThread);
		CloseHandle(ProcessInfo.hProcess);
	}

	/*读取命令行输出的Log文件并打印*/
	CString strout = ReadStringFromFile(strstdfile);
	pdlg->PrintLog(strout);
	pdlg->PrintText("执行完毕。");
	pdlg->m_bBusy = false;

}

/*************************************************
函数名称:	ConvertWeekBINtoCSV
修改日期:    2013-7-15
函数功能:    转换一周的BIN数据到CSV tick文件。
输入参数: 
	- pdlg 指向CMyEAClientDlg的实例。
	- tmsundaystart 以Local时间表示的星期天00:00:01，是要转换的一周开始的星期天。
	- bSkipifRawExists 自动转换时bSkipifRawExists由于CSV仅仅是中间文件，故为真
						手动转换时bSkipifRawExists为假。
输出参数: 
	无。
返回值: 
	生成失败返回-1, 如果CSV文件已经存在返回0, 如果CSV文件声称成功返回1,
	如果bSkipifRawExists为真且RAW文件存在返回2;
全局调用:
	(in) m_strSymbol - 类成员变量，货币对
	(in) m_strPhppath
	(in) m_strInipath
	(in) m_strDatapath - HST文件存储位置
其他说明:
	无。
*************************************************/

int ConvertWeekBINtoCSV(CMyEAClientDlg *pdlg, CTime tmsundaystart,bool bSkipifRawExists)
{
	/*计算一周时间差*/
	CTime t1( 1999, 3, 20, 8, 0, 0 ); 
	CTime t2( 1999, 3, 21, 8, 0, 0 ); 
	CTime t3( 1999, 3, 27, 8, 0, 0 ); 
	CTimeSpan tmspanday = t2 - t1;
	CTimeSpan tmspanweek = t3 - t1;

	/*验证tmsundaystart时间的有效性*/
	int hour = tmsundaystart.GetHour();
	int min = tmsundaystart.GetMinute();
	int sec = tmsundaystart.GetSecond();
	ASSERT((hour==0)&&(min==0)&&(sec==1));
	ASSERT(tmsundaystart.GetDayOfWeek()==1);

	/*手动选择的时间段则必须保证本周BIN数据存在*/
	if (!bSkipifRawExists)
	{
		CTime nextsundayctm = tmsundaystart + tmspanweek;
		CTime nextfridayctm = nextsundayctm - tmspanday - tmspanday;

		/*检查BIN数据是否下载*/
		CString strbinpath;
		strbinpath.Format("%s%s\\%04d\\%02d\\%02d\\23h_ticks.bi5",
			pdlg->m_strPhppath,pdlg->m_strSymbol,nextfridayctm.GetYear(),nextfridayctm.GetMonth()-1,nextfridayctm.GetDay());
		if (!PathFileExists(strbinpath))
		{
			pdlg->PrintText("Bin数据不存在! 请下载.");
			return -1;
		}
	}

	/*开始转换*/
	CTime tmweekstart = tmsundaystart;
	CTime tmweekend = tmsundaystart + tmspanweek;
	
	CString strstartdate,strenddate;
	strstartdate.Format("%04d%02d%02d",tmweekstart.GetYear(),tmweekstart.GetMonth(),tmweekstart.GetDay());
	strenddate.Format("%04d%02d%02d",tmweekend.GetYear(),tmweekend.GetMonth(),tmweekend.GetDay());

	CString stroutfile,strrawfile;
	strrawfile.Format("%s%s_raw\\%s-%s.raw",pdlg->m_strPhppath,pdlg->m_strSymbol,strstartdate,strenddate);
	stroutfile.Format("%s%s_csv\\%s-%s.csv",pdlg->m_strPhppath,pdlg->m_strSymbol,strstartdate,strenddate);

	if (PathFileExists(strrawfile) && bSkipifRawExists)
	{
		pdlg->PrintText("跳过生成%s", strrawfile);
		return 2;
	}

	if (!PathFileExists(stroutfile))
	{
		/*计算命令行输出Log文件路径*/
		CString strerrorfile;
		strerrorfile.Format("%serrorbin2csv.log",pdlg->m_strPhppath);
		DeleteFile(strerrorfile);

		/*执行命令行*/
		CString strcmd;
		strcmd.Format("%sphp my_process_data.php %s %s %s",
			pdlg->m_strPhppath, pdlg->m_strSymbol,strstartdate,strenddate);
		pdlg->PrintText("BIN to CSV: %s %s ...", strstartdate,strenddate);

		PROCESS_INFORMATION ProcessInfo; 
		STARTUPINFO StartupInfo; //This is an [in] parameter
		ZeroMemory(&StartupInfo, sizeof(StartupInfo));
		StartupInfo.cb = sizeof StartupInfo ; //Only compulsory field
		if(CreateProcessA(NULL,strcmd.GetBuffer(strcmd.GetLength()),
			NULL,NULL,FALSE,0,NULL,
			pdlg->m_strPhppath,&StartupInfo,&ProcessInfo))
		{
			WaitForSingleObject(ProcessInfo.hProcess,INFINITE);
			CloseHandle(ProcessInfo.hThread);
			CloseHandle(ProcessInfo.hProcess);
		}  
		else
		{
			pdlg->PrintText("无法启动命令行...");
			return -1;
		}

		/*调用命令行完毕，检查是否正确生成CSV，以防中途cmd退出*/
		CString strerror = ReadStringFromFile(strerrorfile);
		CString strcheck;
		strcheck.Format("BIN to CSV: %s %s Done!", strstartdate,strenddate);
		if (strerror == strcheck)
		{
			pdlg->PrintText("Done.");
			return 1;
		}
		else
		{
			pdlg->PrintText("命令行程序意外终止。");
			DeleteFile(stroutfile);
			return -1;
		}

	}
	else
	{
		return 0;
	}


}


/*************************************************
函数名称:	ConvertWeekCSVtoRAW1Min
修改日期:    2013-7-15
函数功能:    转换一周的Tick CSV数据到1 Min的RAW文件。
输入参数: 
	- pdlg 指向CMyEAClientDlg的实例。
	- tmsundaystart 以Local时间表示的星期天00:00:01，是要转换的一周开始的星期天。
	- bDeleteCSV 生成BIN文件后是否删除CSV源以节约硬盘空间。
输出参数: 
	无。
返回值: 
	生成失败返回false, 如果文件已经存在or生成成功返回true。
全局调用:
	(in) m_strSymbol - 类成员变量，货币对
	(in) m_strPhppath
	(in) m_strInipath
	(in) m_strDatapath - HST文件存储位置
其他说明:
	RAW文件格式其实和HST文件相同，只是没有HST文件头，且时间戳为GMT+0时间。
	由于算法原因，每周最后一分钟的数据会被丢失，正好也屏蔽掉可能多余的极少数tick数据。
*************************************************/

bool ConvertWeekCSVtoRAW1Min(CMyEAClientDlg *pdlg, CTime tmsundaystart, bool bDeleteCSV)
{
	/*计算一周时间差*/
	CTime t1( 1999, 3, 20, 8, 0, 0 );
	CTime t3( 1999, 3, 27, 8, 0, 0 ); 
	CTimeSpan tmspanweek = t3 - t1;

	/*验证tmsundaystart时间的有效性*/
	int hour = tmsundaystart.GetHour();
	int min = tmsundaystart.GetMinute();
	int sec = tmsundaystart.GetSecond();
	ASSERT((hour==0)&&(min==0)&&(sec==1));
	ASSERT(tmsundaystart.GetDayOfWeek()==1);

	/*计算RAW文件目录的路径，不存在则创建*/
	CString strRawFolder;
	strRawFolder.Format("%s%s_raw\\",pdlg->m_strPhppath,pdlg->m_strSymbol);
	if (!PathFileExists(strRawFolder))
	{
		CreateDirectoryA(strRawFolder,NULL);
	}

	/*计算CSV文件和RAW文件的路径*/
	CTime tmnextsundaystart = tmsundaystart + tmspanweek;
	CString strCsvfilepath, strRawfilepath;
	CString strstartdate, strenddate;

	strstartdate.Format("%04d%02d%02d",tmsundaystart.GetYear(),tmsundaystart.GetMonth(),tmsundaystart.GetDay());
	strenddate.Format("%04d%02d%02d",tmnextsundaystart.GetYear(),tmnextsundaystart.GetMonth(),tmnextsundaystart.GetDay());

	strCsvfilepath.Format("%s%s_csv\\%s-%s.csv",pdlg->m_strPhppath,pdlg->m_strSymbol,strstartdate,strenddate);
	strRawfilepath.Format("%s%s_raw\\%s-%s.raw",pdlg->m_strPhppath,pdlg->m_strSymbol,strstartdate,strenddate);

	if (PathFileExists(strRawfilepath))
	{
		pdlg->PrintText("RAW文件已经存在。");
		return true;
	}

	if (!PathFileExists(strCsvfilepath))
	{
		pdlg->PrintText("CSV源数据缺失。");
		return false;
	}

	/*开始写入一周的RAW数据*/
	pdlg->PrintText("CSV to RAW: %s %s ...", strstartdate, strenddate);

	FILE *fp = NULL;
	fp = fopen(strRawfilepath, "wb");
	ASSERT(fp);

	FILE *fcsv = NULL;
	fcsv = fopen(strCsvfilepath, "r");
	ASSERT(fcsv);

	double d_open, d_low, d_high, d_close,d_bid,d_ask,d_spread,d_vol;
	int dotmultiper = pdlg->m_nDotMultiper;
	time_t ttm,tlasttm = 0;

	char buf[60];
	int len;
	CString strdatetime,strask,strbid;
	int year,month,day,hh,mm,ss;
	int pos1,pos2,pos3;

	while(fgets(buf,60,fcsv) != NULL)
	{
		len = strlen(buf);
		buf[len-1] = '\0';  /*去掉换行符*/
		CString strline = buf;
		strline.Trim();
		if (strline == "")
			break;

		strdatetime = strline.Left(19);
		sscanf(strdatetime.GetBuffer(strdatetime.GetLength()),"%d.%d.%d %d:%d:%d",
			&year,&month,&day,&hh,&mm,&ss);
		CTime ctm(year,month,day,hh,mm,0);
		ttm = ctm.GetTime() + pdlg->m_nLocalTimeShift * 3600; /*注意这里是加上Local时区偏移得到GMT+0时间*/
		
		pos1 = strline.Find(",",0);
		pos2 = strline.Find(",",pos1+1);
		pos3 = strline.Find(",",pos2+1);

		strbid = strline.Mid(pos1+1,pos2-pos1-1);
		strask = strline.Mid(pos2+1,pos3-pos2-1);

		d_bid = atof(strbid);
		d_ask = atof(strask);
		/*
		d_bid = 1.32735;
		d_ask = 1.32750;
		*/
		d_spread = (d_ask - d_bid)*dotmultiper;

		if (ttm > tlasttm)//new bar
		{

			if (tlasttm > 0)//write the last bar
			{
				DWORD ttmtmp = tlasttm;
				fwrite(&ttmtmp,sizeof(DWORD),1,fp);

				int lendb = sizeof(double);
				fwrite(&d_open,lendb,1,fp);
				fwrite(&d_low,lendb,1,fp);
				fwrite(&d_high,lendb,1,fp);
				fwrite(&d_close,lendb,1,fp);
				fwrite(&d_vol,lendb,1,fp);
				fflush(fp);
			}

			d_open = d_bid;
			d_low = d_bid;
			d_high = d_bid;
			d_close = d_bid;
			d_vol = d_spread;

			tlasttm = ttm;

		}
		else
		{
			//inside a bar
			if (d_low > d_bid) d_low = d_bid;
			if (d_high < d_bid) d_high = d_bid;
			if (d_vol < d_spread) d_vol = d_spread;
			d_close = d_bid;

		}
	}

	fclose(fcsv);
	fclose(fp);

	pdlg->PrintText("Done.", strstartdate, strenddate);

	if (bDeleteCSV)
		DeleteFile(strCsvfilepath);

	return true;

}

/*************************************************
函数名称:	ThreadBINtoRAWFunc
修改日期:    2013-6-12
函数功能:    转换BIN格式到RAW格式表示的1 Min数据。更新到最近的周末。
输入参数: 
 - dwparam 存储了指向CDukascopyToHstDlg实例的指针
输出参数: 
	无。
返回值: 
	无。
全局调用:
	(in) m_strSymbol - 类成员变量，货币对
	(in) m_strPhppath
	(in) m_strInipath
其他说明:
	调用前系统时间应该确保正确。
	无论是否中间CSV是否存在，都会补齐所有RAW文件。
*************************************************/

void ThreadBINtoRAWFunc(DWORD dwparam)
{
	CMyEAClientDlg *pdlg = (CMyEAClientDlg*)dwparam;
	pdlg->m_bBusy = true;
	CString strpair = pdlg->m_strSymbol;

	/*计算一天、一周的时间差*/
	CTime t1( 1999, 3, 20, 8, 0, 0 ); 
	CTime t2( 1999, 3, 21, 8, 0, 0 ); 
	CTime t3( 1999, 3, 27, 8, 0, 0 ); 
	CTimeSpan tmspanday = t2 - t1;
	CTimeSpan tmspanweek = t3 - t1;

	/*计算最近的行情周末*/
	CTime curctm = CTime::GetCurrentTime();
	struct tm gmttm;
	curctm.GetGmtTm(&gmttm);

	CTime calctm = curctm;
	if (gmttm.tm_wday == 6 || gmttm.tm_wday == 0)
	{
		calctm = curctm + tmspanday+ tmspanday+ tmspanday;
	}

	while (calctm.GetDayOfWeek() != 1)
	{
		calctm -= tmspanday;
	}

	CTime lastsundayctm = calctm;
	CTime lastfridayctm = lastsundayctm - tmspanday - tmspanday;

	pdlg->PrintText("最近的周末: %04d-%02d-%02d",
		lastsundayctm.GetYear(),lastsundayctm.GetMonth(),lastsundayctm.GetDay());

	/*检查BIN数据是否下载到最近的周末*/
	CString strbinpath;
	strbinpath.Format("%s%s\\%04d\\%02d\\%02d\\23h_ticks.bi5",
		pdlg->m_strPhppath,pdlg->m_strSymbol,lastfridayctm.GetYear(),lastfridayctm.GetMonth()-1,lastfridayctm.GetDay());
	if (!PathFileExists(strbinpath))
	{
		pdlg->PrintText("Bin数据未更新到最近的周末! 请先下载补全。");
		pdlg->PrintText("命令执行完毕。");
		pdlg->m_bBusy = false;
		return;
	}

	/*计算有数据以来的第一个周末*/
	UINT gmtstarttm = ReadPairGmtStartFrom(pdlg->m_strPairpath,pdlg->m_strSymbol);
	ASSERT(gmtstarttm > 0);
	CTime ctm((time_t)gmtstarttm);
	while (ctm.GetDayOfWeek()!=1)
	{
		ctm += tmspanday;
	}

	CTime tmweekstart(ctm.GetYear(),ctm.GetMonth(),ctm.GetDay(),0,0,1);
	CTime tmweekend = tmweekstart + tmspanweek;

	/*转换BIN to RAW*/
	int skippedcount = 0,count = 0;
	CTime tmlastmonday = lastsundayctm + tmspanday;
	while (tmweekend < tmlastmonday)
	{
		/*转换BIN to CSV*/
		int ret = ConvertWeekBINtoCSV(pdlg,tmweekstart,true);
		if (ret == -1) break;
		if (ret == 0) 
		{
			/*转换CSV to RAW*/
			ConvertWeekCSVtoRAW1Min(pdlg,tmweekstart,false);
			count++;
		}
		else if (ret == 1) 
		{
			/*转换CSV to RAW*/
			ConvertWeekCSVtoRAW1Min(pdlg,tmweekstart,true);
			count++;
		}
		else if (ret == 2)
		{
			skippedcount++;		
		}

		tmweekstart += tmspanweek;
		tmweekend = tmweekstart + tmspanweek;
	}

	pdlg->PrintText("转换完毕. %d written, %d skipped.", count, skippedcount);
	pdlg->m_bBusy = false;

}


/*************************************************
函数名称:	AppendWeekRAWtoHST1Min
修改日期:    2013-7-15
函数功能:    转换一周的1 Min RAW数据到1 Min的HST文件，如果HST文件已存在则添加在文件末。
输入参数: 
	- pdlg 指向CMyEAClientDlg的实例。
	- tmsundaystart 以Local时间表示的星期天00:00:01，是要转换的一周开始的星期天。
输出参数: 
	数据添加成功or数据已经存在返回true，否则返回false。
返回值: 
	无。
全局调用:
	(in) m_strSymbol - 类成员变量，货币对
	(in) m_strPhppath
	(in) m_strInipath
	(in) m_strDatapath - HST文件存储位置
其他说明:
	如HST文件不存在，则创建新的HST文件。
	已存在的HST文件中则上周数据必须存在，否则会报错。
	由于RAW数据和HST文件格式除去HST文件头是一致的，只是前者为GMT+0时间戳，所以只需将RAW数据修改时间戳后添加到HST文件尾。
*************************************************/


bool AppendWeekRAWtoHST1Min(CMyEAClientDlg *pdlg, CTime tmsundaystart)
{
	/*计算一周时间差*/
	CTime t1( 1999, 3, 20, 8, 0, 0 ); 
	CTime t3( 1999, 3, 27, 8, 0, 0 ); 
	CTimeSpan tmspanweek = t3 - t1;

	/*验证tmsundaystart时间的有效性*/
	int hour = tmsundaystart.GetHour();
	int min = tmsundaystart.GetMinute();
	int sec = tmsundaystart.GetSecond();
	ASSERT((hour==0)&&(min==0)&&(sec==1));
	ASSERT(tmsundaystart.GetDayOfWeek()==1);


	/*计算Hst文件路径*/
	CString strHstfilepath = pdlg->m_strDatapath + pdlg->m_strSymbol + "1.hst";

	/*Hst文件不存在，创建并写入文件头*/
	if (!PathFileExists(strHstfilepath))
	{
		FILE *fp = NULL;
		fp = fopen(strHstfilepath, "wb");
		ASSERT(fp);

		char c_copyright[64]="(C)opyright 2003, MetaQuotes Software Corp.";
		int    version=400;
		char c_symbol[12]="EURUSD";   
		int    i_digits=5;
		int    i_unused[13];
		int    i_period = 1;
		int    i_zero = 0;

		memset(i_unused,0,13*sizeof(int));

		fwrite(&version,sizeof(int),1,fp);
		fwrite(c_copyright,1,64,fp);
		fwrite(c_symbol,1,12,fp);
		fwrite(&i_period,sizeof(int),1,fp);
		fwrite(&i_digits,sizeof(int),1,fp);
		fwrite(&i_zero,sizeof(int),1,fp);
		fwrite(&i_zero,sizeof(int),1,fp);
		fwrite(i_unused,sizeof(int),13,fp);

		fflush(fp);
		fclose(fp);

	}
	/*Hst文件已存在，读取最后的时间戳，验证时间戳是否在上周，否则输入的tmsundaystart不合理*/
	else
	{
		FILE *fp = NULL;
		fp = fopen(strHstfilepath, "rb");
		ASSERT(fp);

		fseek(fp,0,SEEK_END);
		int len = ftell(fp);
		if (len <= (64 + sizeof(int)*18 + 12))
		{
			fclose(fp);
			pdlg->PrintText("已存在的HST文件中没有数据，请删除后再试。");
			return false;
		}

		/*读取最后的时间戳*/
		DWORD tmlast = 0;
		int offset = -sizeof(DWORD) - 5 * sizeof(double);
		fseek(fp, offset,SEEK_END);
		fread(&tmlast,sizeof(DWORD),1,fp);
		ASSERT(tmlast > 0);

		CTime tmlastsundaystart = tmsundaystart - tmspanweek;
		/*验证最后的时间戳是否在上周，尽管一个是GMT+0时间，另外两个是LocalTime对应的GMT+0时间，但由于是星期天00:00:01所以可以*/
		if (tmlast > tmsundaystart.GetTime())
		{
			pdlg->PrintText("当周数据已存在，执行跳过。");
			fclose(fp);
			return true;
		}
		else if (tmlast < tmlastsundaystart.GetTime())
		{
			pdlg->PrintText("无法追加HST数据，因先前数据可能存在缺失。");
			fclose(fp);
			return false;
		}

		fclose(fp);
	}

	/*计算RAW数据的路径*/
	CTime tmnextsundaystart = tmsundaystart + tmspanweek;
	CString strRawfile;
	CString strstartdate, strenddate;

	strstartdate.Format("%04d%02d%02d",tmsundaystart.GetYear(),tmsundaystart.GetMonth(),tmsundaystart.GetDay());
	strenddate.Format("%04d%02d%02d",tmnextsundaystart.GetYear(),tmnextsundaystart.GetMonth(),tmnextsundaystart.GetDay());

	strRawfile.Format("%s%s_raw\\%s-%s.raw",pdlg->m_strPhppath,pdlg->m_strSymbol,strstartdate,strenddate);
	if (!PathFileExists(strRawfile))
	{
		pdlg->PrintText("RAW源数据缺失。");
		return false;
	}

	/*开始追加一周的HST数据*/
	FILE *fp = NULL;
	fp = fopen(strHstfilepath, "rb+");
	ASSERT(fp);
	fseek(fp,0,SEEK_END);

	FILE *fraw = NULL;
	fraw = fopen(strRawfile, "rb");
	ASSERT(fraw);
	fseek(fraw,0,SEEK_END);

	int datalen = ftell(fraw);
	fseek(fraw,0,SEEK_SET);

	#define PACKSIZE 44
	ASSERT(datalen % PACKSIZE == 0);
	int count = datalen / PACKSIZE;
	int index;

	DWORD dwgtm;
	double d_open,d_low,d_high,d_close,d_vol;
	int lendb = sizeof(double);
	for (index = 0;index < count;index ++)
	{
		fread(&dwgtm,sizeof(DWORD), 1,fraw);
		fread(&d_open,lendb,1,fraw);
		fread(&d_low,lendb,1,fraw);
		fread(&d_high,lendb,1,fraw);
		fread(&d_close,lendb,1,fraw);
		fread(&d_vol,lendb,1,fraw);

		/*GMT+0时间转换到Server时间*/
		dwgtm += pdlg->m_nServerTimeShift * 3600;

		fwrite(&dwgtm,sizeof(DWORD), 1,fp);
		fwrite(&d_open,lendb,1,fp);
		fwrite(&d_low,lendb,1,fp);
		fwrite(&d_high,lendb,1,fp);
		fwrite(&d_close,lendb,1,fp);
		fwrite(&d_vol,lendb,1,fp);
		fflush(fp);
	}

	fclose(fraw);
	fclose(fp);

	return true;
}



/*************************************************
函数名称:	ThreadRAWtoHSTFunc
修改日期:    2013-7-15
函数功能:    转换RAW格式表示的1 Min数据到MetaTrader可读的HST文件。更新到最近的周末。
输入参数: 
 - dwparam 存储了指向CDukascopyToHstDlg实例的指针
输出参数: 
	无。
返回值: 
	无。
全局调用:
	(in) m_strSymbol - 类成员变量，货币对
	(in) m_strPhppath
	(in) m_strInipath
其他说明:
	调用前系统时间应该确保正确。
*************************************************/

void ThreadRAWtoHSTFunc(DWORD dwparam)
{
	CMyEAClientDlg *pdlg = (CMyEAClientDlg*)dwparam;
	pdlg->m_bBusy = true;
	CString strpair = pdlg->m_strSymbol;

	/*计算一天、一周的时间差*/
	CTime t1( 1999, 3, 20, 8, 0, 0 ); 
	CTime t2( 1999, 3, 21, 8, 0, 0 ); 
	CTime t3( 1999, 3, 27, 8, 0, 0 ); 
	CTimeSpan tmspanday = t2 - t1;
	CTimeSpan tmspanweek = t3 - t1;

	/*计算最近的行情周末*/
	CTime curctm = CTime::GetCurrentTime();
	struct tm gmttm;
	curctm.GetGmtTm(&gmttm);

	CTime calctm = curctm;
	if (gmttm.tm_wday == 6 || gmttm.tm_wday == 0)
	{
		calctm = curctm + tmspanday+ tmspanday+ tmspanday;
	}

	while (calctm.GetDayOfWeek() != 1)
	{
		calctm -= tmspanday;
	}

	CTime lastsundayctm = calctm;
	CTime lastfridayctm = lastsundayctm - tmspanday - tmspanday;

	pdlg->PrintText("最近的周末: %04d-%02d-%02d",
		lastsundayctm.GetYear(),lastsundayctm.GetMonth(),lastsundayctm.GetDay());

	/*检查RAW数据是否更新到最近的周末*/
	CTime llastdundayctm = lastsundayctm - tmspanweek;
	CString strlstrawpath;
	strlstrawpath.Format("%s%s_raw\\%04d%02d%02d-%04d%02d%02d.raw",pdlg->m_strPhppath,pdlg->m_strSymbol,
		llastdundayctm.GetYear(),llastdundayctm.GetMonth(),llastdundayctm.GetDay(),
		lastsundayctm.GetYear(),lastsundayctm.GetMonth(),lastsundayctm.GetDay());
	if (!PathFileExists(strlstrawpath))
	{
		pdlg->PrintText("RAW数据未更新到最近的周末! 请先更新.");
		pdlg->PrintText("命令执行完毕。");
		pdlg->m_bBusy = false;
		return;
	}

	/*计算有数据以来的第一个周末*/
	UINT gmtstarttm = ReadPairGmtStartFrom(pdlg->m_strPairpath,pdlg->m_strSymbol);
	ASSERT(gmtstarttm > 0);
	CTime ctm((time_t)gmtstarttm);

	while (ctm.GetDayOfWeek()!=1)
	{
		ctm += tmspanday;
	}

	CTime tmweekstart(ctm.GetYear(),ctm.GetMonth(),ctm.GetDay(),0,0,1);
	CTime tmweekend = tmweekstart + tmspanweek;

	/*转换RAW to HST*/
	CString strcmd, stroutfile;
	CString strstartdate, strenddate;
	int skippedcount = 0,count = 0;

	CTime tmlastmonday = lastsundayctm + tmspanday;
	while (tmweekend < tmlastmonday)
	{
		pdlg->PrintText("转换RAW to HST: %04d-%02d-%02d - %04d-%02d-%02d",tmweekstart.GetYear(),tmweekstart.GetMonth(),
			tmweekstart.GetDay(),tmweekend.GetYear(),tmweekend.GetMonth(),tmweekend.GetDay());

		if (!AppendWeekRAWtoHST1Min(pdlg,tmweekstart))
		{
			break;
		}

		tmweekstart += tmspanweek;
		tmweekend = tmweekstart + tmspanweek;

	}

	pdlg->PrintText("命令执行完毕。");
	pdlg->m_bBusy = false;

}


void CMyEAClientDlg::OnSize(UINT nType, int cx, int cy)
{
	CDialog::OnSize(nType, cx, cy);

	if (!m_bcreated) 
		return;

	CRect rc0;
	GetClientRect(&rc0);
	m_edit.MoveWindow(rc0);

}

void CMyEAClientDlg::PrintLog(CString str)
{
	int len = m_edit.GetWindowTextLength();
	m_edit.SetSel(len,len);

	if (str.Right(2)=="\r\n")
		m_edit.ReplaceSel("============== Log Start ================\r\n" + str + "============== Log End ================\r\n");
	else
		m_edit.ReplaceSel("============== Log Start ================\r\n" + str + "\r\n============== Log End ================\r\n");
}

void CMyEAClientDlg::PrintText(LPCTSTR format, ...)
{
	CString str,strtm;
	CTime tm = CTime::GetCurrentTime();
	strtm = tm.Format( "%Y.%m.%d %H:%M:%S > " );

	va_list args;
	va_start( args, format );
	str.FormatV(format,args);
	va_end( args );

	int len = m_edit.GetWindowTextLength();
	m_edit.SetSel(len,len);

	if (str.Right(2)=="\r\n")
		m_edit.ReplaceSel(strtm + str);
	else
		m_edit.ReplaceSel(strtm + str + "\r\n");

}



void CMyEAClientDlg::Init()
{
	CFont *pFont=new CFont;
	pFont->CreatePointFont(100,_T("Arial"),NULL);
	m_edit.SetFont(pFont,TRUE);
	m_edit.SetLimitText(MAXINT);

	/*获取程序所在路径*/
	char cpath[MAX_PATH];
	GetModuleFileName(NULL,cpath,MAX_PATH);
	CString strprogrampath = cpath;
	int pos = strprogrampath.ReverseFind('\\');
	strprogrampath = strprogrampath.Left(pos);
	NormalizePath(strprogrampath);

	/*获取option.ini, currencypair.txt路径*/
	m_strPairpath = strprogrampath + "currencypair.txt";
	m_strInipath = strprogrampath + "option.ini";
	PrintText("载入ini文件: %s", m_strInipath);

	/*读取ini文件中的数据*/
	char cline[MAX_PATH];
	GetPrivateProfileString("General","Symbol","Unknown",cline,MAX_PATH,m_strInipath);
	m_strSymbol = cline;
	m_strSymbol.Trim();
	m_strSymbol.MakeUpper();
	PrintText("当前Symbol: %s",m_strSymbol);

	int NumberOfDecimalDigits = GetPrivateProfileInt("NumberOfDecimalDigits",m_strSymbol,0,m_strInipath);
	if (NumberOfDecimalDigits==0)
	{
		if (m_strSymbol.Find("JPY")>=0)
		{
			NumberOfDecimalDigits = 3;
		}
		else
		{
			NumberOfDecimalDigits = 5;
		}
	}

	PrintText("小数位数: %d",NumberOfDecimalDigits);
	m_nDotMultiper = pow(10.0,NumberOfDecimalDigits);


	GetPrivateProfileString("General","PhpPath","Unknown",cline,MAX_PATH,m_strInipath);
	m_strPhppath = cline;
	NormalizePath(m_strPhppath);
	PrintText("Php路径: %s",m_strPhppath);

	GetPrivateProfileString("General","HstDataPath","Unknown",cline,MAX_PATH,m_strInipath);
	m_strDatapath = cline;
	NormalizePath(m_strDatapath);
	PrintText("Hst文件存储位置: %s",m_strDatapath);

	m_nServerTimeShift = GetPrivateProfileInt("General","ServerTimeShift",0,m_strInipath);
	m_nLocalTimeShift = GetPrivateProfileInt("General","LocalTimeShift",0,m_strInipath);
	PrintText("Ini文件已载入.");

	/*其他*/
	SetWindowTextA("MT4 Data Downloader (" + m_strSymbol + ")");

}

void CMyEAClientDlg::OnEnSetfocusEdit1()
{
	m_edit.SetSel(-1, 0, false);
}

/*************************************************
函数名称: OnCtlColor
修改日期: 2013-10-5
函数功能: 改变Edit前景，背景色。
**************************************************/

HBRUSH CMyEAClientDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);

	if(pWnd->GetDlgCtrlID()   ==   IDC_EDIT1)
	{   
		int nctl = 200;
		HBRUSH   hbru   =   ::CreateSolidBrush   (RGB(nctl,nctl,nctl));  
		pDC->SetTextColor(RGB(0,0,0));     //设置字体颜色   
		pDC->SetBkColor(RGB(nctl,nctl,nctl));     //设置背景色   
		return   hbru;             //这句很重要!   
	}   
	return hbr;
}


/*************************************************
函数名称: NormalizePath
修改日期:    2013-6-11
函数功能: 标准化目录路径
输入参数: 
 - strpath 需要标准化的路径
输出参数: 
 - strpath 被标准化后的路径
返回值: 
	无。
其他说明:
    输入的字符串必须是目录的路径。
*************************************************/
void CMyEAClientDlg::NormalizePath( CString &strpath )
{
	strpath.Trim();
	if (strpath.Right(1) != "\\")
		strpath += "\\";
}


void CMyEAClientDlg::OnViewClear()
{
	m_edit.SetWindowText("");
}


/*************************************************
函数名称: OnHelpAbout
函数功能: 本段代码主要用于快速测试用。
*************************************************/
void CMyEAClientDlg::OnHelpAbout()
{
	CString strtm;

	/*
	CTime ctm = CTime::GetCurrentTime();


	struct tm osTime;
	ctm.GetGmtTm(&osTime);
	strtm.Format("GMT: %04d.%02d.%02d %02d:%02d:%02d",osTime.tm_year,osTime.tm_mon+1,osTime.tm_mday,
		osTime.tm_hour,osTime.tm_min,osTime.tm_sec);
	PrintText(strtm);


	struct tm lcTime;
	ctm.GetLocalTm(&lcTime);
	strtm.Format("Local: %04d.%02d.%02d %02d:%02d:%02d",lcTime.tm_year,lcTime.tm_mon+1,lcTime.tm_mday,
		lcTime.tm_hour,lcTime.tm_min,lcTime.tm_sec);
	PrintText(strtm);
	*/

	CTime tmlocal(1970,1,1,10,0,0);
	PrintText("1970.01.01 10:00:00 GMT: %d ", tmlocal.GetTime());


	CTime tml(1373648395);
	struct tm lcTime;
	tml.GetLocalTm(&lcTime);
	strtm.Format("Local: %04d.%02d.%02d %02d:%02d:%02d",lcTime.tm_year,lcTime.tm_mon+1,lcTime.tm_mday,
		lcTime.tm_hour,lcTime.tm_min,lcTime.tm_sec);
	PrintText(strtm);
	//PrintText("%04d.%02d.%02d %02d:%02d:%02d",tml.GetYear(),tml.GetMonth(),tml.GetDay(),
	//	tml.GetHour(),tml.GetMinute(),tml.GetSecond());

	CTime tmgmt(1373648395);
	struct tm osTime;
	tmgmt.GetGmtTm(&osTime);
	strtm.Format("GMT: %04d.%02d.%02d %02d:%02d:%02d",osTime.tm_year,osTime.tm_mon+1,osTime.tm_mday,
		osTime.tm_hour,osTime.tm_min,osTime.tm_sec);
	PrintText(strtm);
	
}

/*************************************************
函数名称: OnFileDownloaddukascopydata
函数功能: 下载Dukascopy数据。 
*************************************************/

void CMyEAClientDlg::OnFileDownloaddukascopydata()
{
	if (IDYES != MessageBox("警告: 一旦启动下载，不可随意关闭命令行窗口，否则可能造成个别文件数据的损坏。\r\n\r\n仅仅当专业人员清楚了解目前下载到哪一份文件时候才可以手动关闭命令行窗口，且在关闭后务必删除可能损坏的文件。\r\n\r\n确定继续请按是，退出请按否。","Warning",MB_YESNO|MB_ICONQUESTION))
	{
		return;
	}

	DWORD ThreadID;
	HANDLE hThread=CreateThread(NULL,
		0,
		(LPTHREAD_START_ROUTINE)ThreadDownloadBINFunc,
		(VOID*)this,
		0,
		&ThreadID);
}


void CMyEAClientDlg::OnFileConvertbintocsvtickfile()
{
	CSelectDateDlg cdlg;
	if (cdlg.DoModal() == IDOK)
	{
		CTime tm(cdlg.m_year,cdlg.m_month,cdlg.m_day,0,0,1);
		if (tm.GetDayOfWeek() != 1)
		{
			MessageBox("选择日期必须是星期天！","Warning",MB_OK);
			return;
		}

		m_bBusy = true;
		ConvertWeekBINtoCSV(this,tm,false);
		PrintText("执行完毕。");
		m_bBusy = false;
	}

}

/*************************************************
函数名称: IsCSVFileInFolder
修改日期:    2013-7-16
函数功能: 判断指定目录下是否存在csv文件
输入参数: 
 - strFolder 指定目录
输出参数: 
	无。
返回值: 
	有csv文件返回true，否则返回false。
其他说明:
    输入的字符串必须是目录的路径。
*************************************************/

bool CMyEAClientDlg::IsCSVFileInFolder(CString strFolder)
{
	NormalizePath(strFolder);

	char FullPath[MAX_PATH];
	strcpy(FullPath,strFolder);
	strcat(FullPath,"*.csv");

	HANDLE hFind;
	WIN32_FIND_DATA wfData;
	
	hFind = FindFirstFile(FullPath,&wfData);
	if(hFind == INVALID_HANDLE_VALUE)
	{
		return false;
	}
	else
	{
		FindClose(hFind);
		return true;
	}

	
}



void CMyEAClientDlg::OnFileConvertbintoraw1minfile()
{
	/*判断中间csv目录中是否存在csv文件*/
	CString strcsvfolder;
	strcsvfolder.Format("%s%s_csv\\",m_strPhppath,m_strSymbol);
	if (IsCSVFileInFolder(strcsvfolder))
	{
		int ret = MessageBox("中间目录中存在CSV文件，如果CSV文件不完整则可能导致输出数据错误！\r\n确定要继续吗？","Warning",MB_YESNOCANCEL|MB_ICONASTERISK);
		if (ret != IDYES)
			return;
	}

	/*开启转换线程*/
	DWORD ThreadID;
	HANDLE hThread=CreateThread(NULL,
		0,
		(LPTHREAD_START_ROUTINE)ThreadBINtoRAWFunc,
		(VOID*)this,
		0,
		&ThreadID);
}


void CMyEAClientDlg::OnFileConvertraw1minfiletohst1min()
{
	DWORD ThreadID;
	HANDLE hThread=CreateThread(NULL,
		0,
		(LPTHREAD_START_ROUTINE)ThreadRAWtoHSTFunc,
		(VOID*)this,
		0,
		&ThreadID);	
}




void CMyEAClientDlg::OnUpdateFileDownloaddukascopydata(CCmdUI *pCmdUI)
{
	pCmdUI->Enable(!m_bBusy);
}

void CMyEAClientDlg::OnUpdateFileConvertbintocsvtickfile(CCmdUI *pCmdUI)
{
	pCmdUI->Enable(!m_bBusy);
}

void CMyEAClientDlg::OnUpdateFileConvertbintoraw1minfile(CCmdUI *pCmdUI)
{
	pCmdUI->Enable(!m_bBusy);
}

void CMyEAClientDlg::OnUpdateFileConvertraw1minfiletohst1min(CCmdUI *pCmdUI)
{
	pCmdUI->Enable(!m_bBusy);
}

BOOL CMyEAClientDlg::ContinueModal()
{
	CMenu* pMainMenu = GetMenu();
	CCmdUI cmdUI;
	for (UINT n = 0; n < pMainMenu->GetMenuItemCount(); ++n)
	{
		CMenu* pSubMenu = pMainMenu->GetSubMenu(n);
		cmdUI.m_nIndexMax = pSubMenu->GetMenuItemCount();
		for (UINT i = 0; i < cmdUI.m_nIndexMax;++i)
		{
			cmdUI.m_nIndex = i;
			cmdUI.m_nID = pSubMenu->GetMenuItemID(i);
			cmdUI.m_pMenu = pSubMenu;
			cmdUI.DoUpdate(this, FALSE);
		}
	}

	return CDialog::ContinueModal();
}
