// MyEAClientDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "MyEAClient.h"
#include "MyEAClientDlg.h"

#include "PeriodDlg.h"
#include "PickPairDlg.h"

#include "Shlwapi.h"
#include "SelectDateDlg.h"

#include <math.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
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


// CMyEAClientDlg �Ի���




CMyEAClientDlg::CMyEAClientDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CMyEAClientDlg::IDD, pParent)
{
	m_bcreated = false;
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);

	m_clientcount = 0;
	m_bBusy = false;

	m_bM1 = TRUE; 
	m_bM5 = TRUE; 
	m_bM15 = TRUE; 
	m_bM30 = TRUE; 
	m_bH1 = TRUE; 
	m_bH4 = TRUE; 
	m_bD1 = TRUE;

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
	ON_COMMAND(ID_FILE_CONVERTBINTORAW1MINFILE, &CMyEAClientDlg::OnFileConvertbintoraw1minfile)
	ON_UPDATE_COMMAND_UI(ID_FILE_DOWNLOADDUKASCOPYDATA, &CMyEAClientDlg::OnUpdateFileDownloaddukascopydata)
	ON_UPDATE_COMMAND_UI(ID_FILE_CONVERTBINTOCSVTICKFILE, &CMyEAClientDlg::OnUpdateFileConvertbintocsvtickfile)
	ON_UPDATE_COMMAND_UI(ID_FILE_CONVERTBINTORAW1MINFILE, &CMyEAClientDlg::OnUpdateFileConvertbintoraw1minfile)
	ON_COMMAND(ID_FILE_CONVERTRAW1MINFILETOHSTFILES, &CMyEAClientDlg::OnFileConvertraw1minfiletohstfiles)
	ON_UPDATE_COMMAND_UI(ID_FILE_CONVERTRAW1MINFILETOHSTFILES, &CMyEAClientDlg::OnUpdateFileConvertraw1minfiletohstfiles)
	ON_UPDATE_COMMAND_UI(ID_VIEW_CLEAR, &CMyEAClientDlg::OnUpdateViewClear)
	ON_COMMAND(ID_FILE_CHANGECURRENCYPAIR, &CMyEAClientDlg::OnFileChangecurrencypair)
	ON_UPDATE_COMMAND_UI(ID_FILE_CHANGECURRENCYPAIR, &CMyEAClientDlg::OnUpdateFileChangecurrencypair)
	ON_COMMAND(ID_FILE_EXIT, &CMyEAClientDlg::OnFileExit)
END_MESSAGE_MAP()


// CMyEAClientDlg ��Ϣ�������

BOOL CMyEAClientDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�
	m_bcreated = true;
	CMenu* menu =new CMenu;
	menu->LoadMenu(MAKEINTRESOURCE(IDR_MENU1));      //��ɫ����Ϊ��Ӧ�Լ���ӵĲ˵���Դ������
	this->SetMenu(menu);

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
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

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������
	
	Init();


	
	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
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

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CMyEAClientDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
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
��������: ReadStringFromFile
�޸�����: 2013-7-12
��������: ��ĳ�ı���ʽ�ļ��ж�ȡȫ���ı����ַ���
�������: 
 - strfilepath ĳ�ı���ʽ�ļ���·��
�������: 
	�ޡ�
����ֵ: 
	�ַ������������ļ������ݡ�
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
��������: ReadPairGmtStartFrom
�޸�����: 2013-7-13
��������: ��ȡcurrencypair.txt��start from��GMTʱ��
�������: 
 - strpath currencypair.txt��·��
 - strpair ���Ҷ�
�������: 
	�ޡ�
����ֵ: 
	�û��Ҷ�start from��GMTʱ�䣬����ȡʧ�ܷ���0��
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
��������: ThreadDownloadBINFunc
�޸�����: 2013-7-12
��������: ��Dukascopy�������ݵ��߳�
�������: 
 - dwparam �洢��ָ��CDukascopyToHstDlgʵ����ָ��
�������: 
	�ޡ�
����ֵ: 
	�ޡ�
ȫ�ֵ���:
	(in) m_strSymbol - ���Ա���������Ҷ�
	(in) m_strPhppath
	(in) m_strPairpath
����˵��:
	���ص�����Ϊԭʼ��BIN��ʽ�����һ��Զ���ȫ�������ʱ�䡣
*************************************************/

void ThreadDownloadBINFunc(DWORD dwparam)
{
	CMyEAClientDlg *pdlg = (CMyEAClientDlg*)dwparam;
	pdlg->PrintText("��������:");

	pdlg->m_bBusy = true;
	CString strpair = pdlg->m_strSymbol;

	/*д��my_download_data.phpҪ���õ�ͷ�ļ�currencies.php*/
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
	
	/*������Ҫִ�е��������ַ���*/
	CString strcmd;
	strcmd.Format("%sphp my_download_data.php",pdlg->m_strPhppath);
	pdlg->PrintText(strcmd);

	/*�������������Log�ļ�·��*/
	CString strstdfile;
	strstdfile.Format("%serror.log",pdlg->m_strPhppath);
	DeleteFile(strstdfile);

	/*ִ�������У��ȴ�ֱ������*/
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

	/*��ȡ�����������Log�ļ�����ӡ*/
	CString strout = ReadStringFromFile(strstdfile);
	pdlg->PrintLog(strout);
	pdlg->PrintText("ִ����ϡ�");
	pdlg->m_bBusy = false;

}

/*************************************************
��������:	ConvertWeekBINtoCSV
�޸�����:    2013-10-07
��������:    ת��һ�ܵ�BIN���ݵ�CSV tick�ļ���
�������: 
	- pdlg ָ��CMyEAClientDlg��ʵ����
	- tmsundaystart ��Localʱ���ʾ��������00:00:01����Ҫת����һ�ܿ�ʼ�������졣
�������: 
	�ޡ�
����ֵ: 
	����ʧ�ܷ���-1, ���CSV�ļ��Ѿ����ڷ���0, ���CSV�ļ����ɳɹ�����1,
ȫ�ֵ���:
	(in) m_strSymbol - ���Ա���������Ҷ�
	(in) m_strPhppath
����˵��:
	��ر�֤ʱ�䷶Χ�ڵ�BIN�ļ��Ѿ��ɹ����أ�����ᵼ�����CSV�ļ�������ȱʧ��
*************************************************/

int ConvertWeekBINtoCSV(CMyEAClientDlg *pdlg, CTime tmsundaystart)
{
	/*����һ��ʱ���*/
	CTime t1( 1999, 3, 20, 8, 0, 0 ); 
	CTime t2( 1999, 3, 21, 8, 0, 0 ); 
	CTime t3( 1999, 3, 27, 8, 0, 0 ); 
	CTimeSpan tmspanday = t2 - t1;
	CTimeSpan tmspanweek = t3 - t1;

	/*��֤tmsundaystartʱ�����Ч��*/
	int hour = tmsundaystart.GetHour();
	int min = tmsundaystart.GetMinute();
	int sec = tmsundaystart.GetSecond();
	ASSERT((hour==0)&&(min==0)&&(sec==1));
	ASSERT(tmsundaystart.GetDayOfWeek()==1);

	/*��ʼת��*/
	CTime tmweekstart = tmsundaystart;
	CTime tmweekend = tmsundaystart + tmspanweek;
	
	CString strstartdate,strenddate;
	strstartdate.Format("%04d%02d%02d",tmweekstart.GetYear(),tmweekstart.GetMonth(),tmweekstart.GetDay());
	strenddate.Format("%04d%02d%02d",tmweekend.GetYear(),tmweekend.GetMonth(),tmweekend.GetDay());

	CString stroutfile;
	stroutfile.Format("%s%s_csv\\%s-%s.csv",pdlg->m_strPhppath,pdlg->m_strSymbol,strstartdate,strenddate);

	if (!PathFileExists(stroutfile))
	{
		/*�������������Log�ļ�·��*/
		CString strerrorfile;
		strerrorfile.Format("%serrorbin2csv.log",pdlg->m_strPhppath);
		DeleteFile(strerrorfile);

		/*ִ��������*/
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
			pdlg->PrintText("�޷�����������...");
		}

		/*������������ϣ�����Ƿ���ȷ����CSV���Է���;cmd�˳�*/
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
			pdlg->PrintText("�����г���������ֹ��");
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
��������:	ConvertWeekCSVtoRAW1Min
�޸�����:    2013-7-15
��������:    ת��һ�ܵ�Tick CSV���ݵ�1 Min��RAW�ļ���
�������: 
	- pdlg ָ��CMyEAClientDlg��ʵ����
	- tmsundaystart ��Localʱ���ʾ��������00:00:01����Ҫת����һ�ܿ�ʼ�������졣
	- bDeleteCSV ����BIN�ļ����Ƿ�ɾ��CSVԴ�Խ�ԼӲ�̿ռ䡣
�������: 
	�ޡ�
����ֵ: 
	����ʧ�ܷ���false, ����ļ��Ѿ�����or���ɳɹ�����true��
ȫ�ֵ���:
	(in) m_strSymbol - ���Ա���������Ҷ�
	(in) m_strPhppath
	(in) m_strInipath
	(in) m_strDatapath - HST�ļ��洢λ��
����˵��:
	RAW�ļ���ʽ��ʵ��HST�ļ���ͬ��ֻ��û��HST�ļ�ͷ����ʱ���ΪGMT+0ʱ�䡣
	�����㷨ԭ��ÿ�����һ���ӵ����ݻᱻ��ʧ������Ҳ���ε����ܶ���ļ�����tick���ݡ�
*************************************************/

bool ConvertWeekCSVtoRAW1Min(CMyEAClientDlg *pdlg, CTime tmsundaystart, bool bDeleteCSV)
{
	/*����һ��ʱ���*/
	CTime t1( 1999, 3, 20, 8, 0, 0 );
	CTime t3( 1999, 3, 27, 8, 0, 0 ); 
	CTimeSpan tmspanweek = t3 - t1;

	/*��֤tmsundaystartʱ�����Ч��*/
	int hour = tmsundaystart.GetHour();
	int min = tmsundaystart.GetMinute();
	int sec = tmsundaystart.GetSecond();
	ASSERT((hour==0)&&(min==0)&&(sec==1));
	ASSERT(tmsundaystart.GetDayOfWeek()==1);

	/*����RAW�ļ�Ŀ¼��·�����������򴴽�*/
	CString strRawFolder;
	strRawFolder.Format("%s%s_raw\\",pdlg->m_strPhppath,pdlg->m_strSymbol);
	if (!PathFileExists(strRawFolder))
	{
		CreateDirectoryA(strRawFolder,NULL);
	}

	/*����CSV�ļ���RAW�ļ���·��*/
	CTime tmnextsundaystart = tmsundaystart + tmspanweek;
	CString strCsvfilepath, strRawfilepath;
	CString strstartdate, strenddate;

	strstartdate.Format("%04d%02d%02d",tmsundaystart.GetYear(),tmsundaystart.GetMonth(),tmsundaystart.GetDay());
	strenddate.Format("%04d%02d%02d",tmnextsundaystart.GetYear(),tmnextsundaystart.GetMonth(),tmnextsundaystart.GetDay());

	strCsvfilepath.Format("%s%s_csv\\%s-%s.csv",pdlg->m_strPhppath,pdlg->m_strSymbol,strstartdate,strenddate);
	strRawfilepath.Format("%s%s_raw\\%s-%s.raw",pdlg->m_strPhppath,pdlg->m_strSymbol,strstartdate,strenddate);

	if (PathFileExists(strRawfilepath))
	{
		pdlg->PrintText("RAW�ļ��Ѿ����ڣ����ڳ����߼�����");
		return true;
	}

	if (!PathFileExists(strCsvfilepath))
	{
		pdlg->PrintText("CSVԴ����ȱʧ�����ڳ����߼�����");
		return false;
	}

	/*��ʼд��һ�ܵ�RAW����*/
	pdlg->PrintText("CSV to RAW: %s %s ...", strstartdate, strenddate);

	FILE *fp = NULL;
	fp = fopen(strRawfilepath, "wb");
	ASSERT(fp);

	FILE *fcsv = NULL;
	fcsv = fopen(strCsvfilepath, "r");
	ASSERT(fcsv);

	double d_open, d_low, d_high, d_close,d_bid,d_ask,d_spread,d_vol;
	int dotmultiper = pow(10.0,pdlg->m_NumberOfDecimalDigits);
	time_t ttm,tlasttm = 0;

	char buf[70];
	int len;
	CString strdatetime,strask,strbid;
	int year,month,day,hh,mm,ss;
	int pos1,pos2,pos3;

	while(fgets(buf,70,fcsv) != NULL)
	{
		len = strlen(buf);
		buf[len-1] = '\0';  /*ȥ�����з�*/
		CString strline = buf;
		strline.Trim();
		if (strline == "")
			break;

		strdatetime = strline.Left(19);
		sscanf(strdatetime.GetBuffer(strdatetime.GetLength()),"%d.%d.%d %d:%d:%d",
			&year,&month,&day,&hh,&mm,&ss);
		CTime ctm(year,month,day,hh,mm,0);
		ttm = ctm.GetTime() + pdlg->m_nLocalTimeShift * 3600; /*ע�������Ǽ���Localʱ��ƫ�Ƶõ�GMT+0ʱ��*/
		
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
��������:	ThreadBINtoRAW1MinFunc
�޸�����:    2013-10-07
��������:    ת��BIN��ʽ��RAW��ʽ��ʾ��1 Min���ݡ����µ��������ĩ��
�������: 
 - dwparam �洢��ָ��CDukascopyToHstDlgʵ����ָ��
�������: 
	�ޡ�
����ֵ: 
	�ޡ�
ȫ�ֵ���:
	(in) m_strSymbol - ���Ա���������Ҷ�
	(in) m_strPhppath
	(in) m_strInipath
����˵��:
	����ǰϵͳʱ��Ӧ��ȷ����ȷ��ͬʱ��֤û��CSV�ļ��������м�Ŀ¼�����Ѿ����������µ�BIN���ݡ�
*************************************************/

void ThreadBINtoRAW1MinFunc(DWORD dwparam)
{
	CMyEAClientDlg *pdlg = (CMyEAClientDlg*)dwparam;
	pdlg->m_bBusy = true;
	CString strpair = pdlg->m_strSymbol;

	/*����һ�졢һ�ܵ�ʱ���*/
	CTime t1( 1999, 3, 20, 8, 0, 0 ); 
	CTime t2( 1999, 3, 21, 8, 0, 0 ); 
	CTime t3( 1999, 3, 27, 8, 0, 0 ); 
	CTimeSpan tmspanday = t2 - t1;
	CTimeSpan tmspanweek = t3 - t1;

	/*���������������ĩ*/
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

	pdlg->PrintText("�������ĩ: %04d-%02d-%02d",
		lastsundayctm.GetYear(),lastsundayctm.GetMonth(),lastsundayctm.GetDay());

	/*���BIN�����Ƿ����ص��������ĩ*/
	CString strbinpath;
	strbinpath.Format("%s%s\\%04d\\%02d\\%02d\\23h_ticks.bi5",
		pdlg->m_strPhppath,pdlg->m_strSymbol,lastfridayctm.GetYear(),lastfridayctm.GetMonth()-1,lastfridayctm.GetDay());
	if (!PathFileExists(strbinpath))
	{
		pdlg->PrintText("Bin����δ���µ��������ĩ! �������ز�ȫ��ע�⣺��ʹû�д���ʾ��Ҳ����ʾBin���ݵ������ԣ���˲�ȷ��������б�Ҫ��������ȷ�ϡ�");
		pdlg->PrintText("����ִ����ϡ�");
		pdlg->m_bBusy = false;
		return;
	}

	/*���������������ĵ�һ����ĩ*/
	UINT gmtstarttm = ReadPairGmtStartFrom(pdlg->m_strPairpath,pdlg->m_strSymbol);
	ASSERT(gmtstarttm > 0);
	CTime ctm((time_t)gmtstarttm);
	while (ctm.GetDayOfWeek()!=1)
	{
		ctm += tmspanday;
	}

	CTime tmweekstart(ctm.GetYear(),ctm.GetMonth(),ctm.GetDay(),0,0,1);
	CTime tmweekend = tmweekstart + tmspanweek;

	/*ת��BIN to RAW*/
	int skippedcount = 0,count = 0;
	CTime tmlastmonday = lastsundayctm + tmspanday;
	while (tmweekend < tmlastmonday)
	{
		/*�ж�raw�ļ��Ƿ��Ѿ����ڣ�����Ѿ�����������*/
		CString strstartdate,strenddate;
		strstartdate.Format("%04d%02d%02d",tmweekstart.GetYear(),tmweekstart.GetMonth(),tmweekstart.GetDay());
		strenddate.Format("%04d%02d%02d",tmweekend.GetYear(),tmweekend.GetMonth(),tmweekend.GetDay());

		CString strrawfile;
		strrawfile.Format("%s%s_raw\\%s-%s.raw",pdlg->m_strPhppath,pdlg->m_strSymbol,strstartdate,strenddate);
		if (PathFileExists(strrawfile))
		{
			pdlg->PrintText("��������%s", strrawfile);
			skippedcount++;
		}
		else
		{
			/*ת��BIN to CSV*/
			int ret = ConvertWeekBINtoCSV(pdlg,tmweekstart);
			if (ret == -1) break;
			else if (ret == 0)
			{
				/*�м�CSV�ļ��Ѿ����ڣ������߳��߼���Ӧ�ó��ִ��������*/
				pdlg->PrintText("�����ص���CSV�м��ļ������ڳ����߼�����");
				break;
			}
			else if (ret == 1) 
			{
				/*ת��CSV to RAW*/
				ConvertWeekCSVtoRAW1Min(pdlg,tmweekstart,true);
				count++;
			}
			else
			{
				//��Ӧ���˲����������ڳ����߼�����		
			}
		}

		tmweekstart += tmspanweek;
		tmweekend = tmweekstart + tmspanweek;
	}

	pdlg->PrintText("ת�����. %d written, %d skipped.", count, skippedcount);
	pdlg->m_bBusy = false;

}


/*************************************************
��������:	AppendWeekRAWtoHST
�޸�����:    2013-10-10
��������:    ת��һ�ܵ�1 Min RAW���ݵ�ָ�����ڵ�HST�ļ������HST�ļ��Ѵ�����������ļ�ĩ��
�������: 
	- pdlg ָ��CMyEAClientDlg��ʵ����
	- tmsundaystart ��Localʱ���ʾ��������00:00:01����Ҫת����һ�ܿ�ʼ�������졣
	- period ת��ΪHST�ļ�������, �Է���Ϊ��λ����ѡΪ 1 Day, 4H, 1H, 30 Min, 15 Min, 5 Min, 1 Min
�������: 
	������ӳɹ�or�����Ѿ����ڷ���true�����򷵻�false��
����ֵ: 
	�ޡ�
ȫ�ֵ���:
	(in) m_strSymbol - ���Ա���������Ҷ�
	(in) m_strPhppath
	(in) m_strInipath
	(in) m_strDatapath - HST�ļ��洢λ��
����˵��:
	��HST�ļ������ڣ��򴴽��µ�HST�ļ���
	�Ѵ��ڵ�HST�ļ������������ݱ�����ڣ�����ᱨ��
	RAW���ݺ�HST�ļ���ʽ��ȥHST�ļ�ͷ��һ�µģ�ֻ��ǰ��ΪGMT+0ʱ�����������Ϊ1���ӡ�
*************************************************/


bool AppendWeekRAWtoHST(CMyEAClientDlg *pdlg, CTime tmsundaystart, int period)
{
	pdlg->PrintText("����ת��RAW to HST ���� %d ����", period);

	/*�������Ϊ1 Day*/
	ASSERT((period == 60 * 24) || (period == 60 * 4) || (period == 60) || (period == 30)||(period == 15)||(period == 5)||(period == 1));

	/*����һ��ʱ���*/
	CTime t1( 1999, 3, 20, 8, 0, 0 );
	CTime t3( 1999, 3, 27, 8, 0, 0 );
	CTimeSpan tmspanweek = t3 - t1;

	/*��֤tmsundaystartʱ�����Ч��*/
	int hour = tmsundaystart.GetHour();
	int min = tmsundaystart.GetMinute();
	int sec = tmsundaystart.GetSecond();
	ASSERT((hour==0)&&(min==0)&&(sec==1));
	ASSERT(tmsundaystart.GetDayOfWeek()==1);

	/*����Hst�ļ�·��*/
	CString strHstname;
	strHstname.Format("%d.hst",period);
	CString strHstfilepath = pdlg->m_strDatapath + pdlg->m_strSymbol + strHstname;

	/*Hst�ļ������ڣ�������д���ļ�ͷ*/
	if (!PathFileExists(strHstfilepath))
	{
		FILE *fp = NULL;
		fp = fopen(strHstfilepath, "wb");
		ASSERT(fp);

		char c_copyright[64]="(C)opyright 2003, MetaQuotes Software Corp.";
		int    version=400;
		char c_symbol[12];
		int    i_digits= pdlg->m_NumberOfDecimalDigits;
		int    i_unused[13];
		int    i_period = period;
		int    i_zero = 0;

		memset(c_symbol, 0, 12);
		memset(i_unused,0,13*sizeof(int));

		ASSERT(pdlg->m_strSymbol.GetLength()<=10);
		strcpy(c_symbol,pdlg->m_strSymbol);

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
	/*Hst�ļ��Ѵ��ڣ���ȡ����ʱ�������֤ʱ����Ƿ������ܣ����������tmsundaystart������*/
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
			pdlg->PrintText("�Ѵ��ڵ�HST�ļ���û�����ݣ���ɾ�������ԡ�");
			return false;
		}

		/*��ȡ����ʱ���*/
		DWORD tmlast = 0;
		int offset = -sizeof(DWORD) - 5 * sizeof(double);
		fseek(fp, offset,SEEK_END);
		fread(&tmlast,sizeof(DWORD),1,fp);
		ASSERT(tmlast > 0);

		CTime tmlastsundaystart = tmsundaystart - tmspanweek;
		/*��֤����ʱ����Ƿ������ܣ�����һ����GMT+0ʱ�䣬����������LocalTime��Ӧ��GMT+0ʱ�䣬��������������00:00:01���Կ���*/
		if (tmlast > tmsundaystart.GetTime())
		{
			pdlg->PrintText("���������Ѵ��ڣ�ִ��������");
			fclose(fp);
			return true;
		}
		else if (tmlast < tmlastsundaystart.GetTime())
		{
			pdlg->PrintText("�޷�׷��HST���ݣ�����ǰ���ݿ��ܴ���ȱʧ��");
			fclose(fp);
			return false;
		}

		fclose(fp);
	}

	/*����RAW���ݵ�·��*/
	CTime tmnextsundaystart = tmsundaystart + tmspanweek;
	CString strRawfile;
	CString strstartdate, strenddate;

	strstartdate.Format("%04d%02d%02d",tmsundaystart.GetYear(),tmsundaystart.GetMonth(),tmsundaystart.GetDay());
	strenddate.Format("%04d%02d%02d",tmnextsundaystart.GetYear(),tmnextsundaystart.GetMonth(),tmnextsundaystart.GetDay());

	strRawfile.Format("%s%s_raw\\%s-%s.raw",pdlg->m_strPhppath,pdlg->m_strSymbol,strstartdate,strenddate);
	if (!PathFileExists(strRawfile))
	{
		pdlg->PrintText("RAWԴ����ȱʧ��");
		return false;
	}

	/*��ʼ׷��һ�ܵ�HST����*/
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

	/*һ��pack����һ��DWORD��5��double, ����Ϊ sizeof(DWORD) + 5 * sizeof(double)*/
#define PACKSIZE 44 
	ASSERT(datalen % PACKSIZE == 0);
	int count = datalen / PACKSIZE;
	int lendb = sizeof(double);
	
	/*���´����Ƕ�mq4�ļ��ķ��룬������������*/
	int i;
	int periodseconds= period*60;

	DWORD time0, i_time;
	double s_open,s_low,s_high,s_close,s_vol;
	double d_open,d_low,d_high,d_close,d_vol;

	fread(&time0,sizeof(DWORD), 1,fraw);
	fread(&s_open,lendb,1,fraw);
	fread(&s_low,lendb,1,fraw);
	fread(&s_high,lendb,1,fraw);
	fread(&s_close,lendb,1,fraw);
	fread(&s_vol,lendb,1,fraw);

	d_open = s_open;
	d_low = s_low;
	d_high = s_high;
	d_close = s_close;
	d_vol = s_vol;

	time0 += pdlg->m_nServerTimeShift * 3600;
	i_time = time0 / periodseconds;
	i_time *= periodseconds;

	
	for (i = 2;i <= count;i ++)
	{
		fread(&time0,sizeof(DWORD), 1,fraw);
		fread(&s_open,lendb,1,fraw);
		fread(&s_low,lendb,1,fraw);
		fread(&s_high,lendb,1,fraw);
		fread(&s_close,lendb,1,fraw);
		fread(&s_vol,lendb,1,fraw);
		time0 += pdlg->m_nServerTimeShift * 3600;

		if ((time0 >= i_time + periodseconds) && (i  < count))
		{
			fwrite(&i_time,sizeof(DWORD), 1,fp);
			fwrite(&d_open,lendb,1,fp);
			fwrite(&d_low,lendb,1,fp);
			fwrite(&d_high,lendb,1,fp);
			fwrite(&d_close,lendb,1,fp);
			fwrite(&d_vol,lendb,1,fp);
			fflush(fp);

			i_time = time0 / periodseconds;
			i_time *= periodseconds;
			d_open = s_open;
			d_low = s_low;
			d_high = s_high;
			d_close = s_close;
			d_vol = s_vol;

		}
		else if ((time0 >= i_time + periodseconds) && (i  == count))
		{
			fwrite(&i_time,sizeof(DWORD), 1,fp);
			fwrite(&d_open,lendb,1,fp);
			fwrite(&d_low,lendb,1,fp);
			fwrite(&d_high,lendb,1,fp);
			fwrite(&d_close,lendb,1,fp);
			fwrite(&d_vol,lendb,1,fp);
			fflush(fp);

			i_time = time0 / periodseconds;
			i_time *= periodseconds;
			d_open = s_open;
			d_low = s_low;
			d_high = s_high;
			d_close = s_close;
			d_vol = s_vol;

			fwrite(&i_time,sizeof(DWORD), 1,fp);
			fwrite(&d_open,lendb,1,fp);
			fwrite(&d_low,lendb,1,fp);
			fwrite(&d_high,lendb,1,fp);
			fwrite(&d_close,lendb,1,fp);
			fwrite(&d_vol,lendb,1,fp);
			fflush(fp);

		}
		else if ((time0 < i_time + periodseconds) && (i  == count))
		{
			if (d_vol < s_vol) d_vol = s_vol;
			if (d_low > s_low) d_low = s_low;
			if (d_high < s_high) d_high = s_high;
			d_close = s_close;

			fwrite(&i_time,sizeof(DWORD), 1,fp);
			fwrite(&d_open,lendb,1,fp);
			fwrite(&d_low,lendb,1,fp);
			fwrite(&d_high,lendb,1,fp);
			fwrite(&d_close,lendb,1,fp);
			fwrite(&d_vol,lendb,1,fp);
			fflush(fp);

		}
		else /*if ((time0 < i_time + periodseconds) && (i  < count))*/
		{
			if (d_vol < s_vol) d_vol = s_vol;
			if (d_low > s_low) d_low = s_low;
			if (d_high < s_high) d_high = s_high;
			d_close = s_close;
		}

	}

	fclose(fraw);
	fclose(fp);

	return true;
}


/*************************************************
��������:	ThreadRAWtoHSTFunc
�޸�����:    2013-10-10
��������:    ת��RAW��ʽ��ʾ��1 Min���ݵ�MetaTrader�ɶ���HST�ļ������µ��������ĩ��
�������: 
 - dwparam �洢��ָ��CDukascopyToHstDlgʵ����ָ��
�������: 
	�ޡ�
����ֵ: 
	�ޡ�
ȫ�ֵ���:
	(in) m_strSymbol - ���Ա���������Ҷ�
	(in) m_strPhppath
	(in) m_strInipath
����˵��:
	����ǰϵͳʱ��Ӧ��ȷ����ȷ��
*************************************************/

void ThreadRAWtoHSTFunc(DWORD dwparam)
{
	CMyEAClientDlg *pdlg = (CMyEAClientDlg*)dwparam;
	pdlg->m_bBusy = true;
	CString strpair = pdlg->m_strSymbol;

	/*����һ�졢һ�ܵ�ʱ���*/
	CTime t1( 1999, 3, 20, 8, 0, 0 ); 
	CTime t2( 1999, 3, 21, 8, 0, 0 ); 
	CTime t3( 1999, 3, 27, 8, 0, 0 ); 
	CTimeSpan tmspanday = t2 - t1;
	CTimeSpan tmspanweek = t3 - t1;

	/*���������������ĩ*/
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

	pdlg->PrintText("�������ĩ: %04d-%02d-%02d",
		lastsundayctm.GetYear(),lastsundayctm.GetMonth(),lastsundayctm.GetDay());

	/*���RAW�����Ƿ���µ��������ĩ*/
	CTime llastdundayctm = lastsundayctm - tmspanweek;
	CString strlstrawpath;
	strlstrawpath.Format("%s%s_raw\\%04d%02d%02d-%04d%02d%02d.raw",pdlg->m_strPhppath,pdlg->m_strSymbol,
		llastdundayctm.GetYear(),llastdundayctm.GetMonth(),llastdundayctm.GetDay(),
		lastsundayctm.GetYear(),lastsundayctm.GetMonth(),lastsundayctm.GetDay());
	if (!PathFileExists(strlstrawpath))
	{
		pdlg->PrintText("RAW����δ���µ��������ĩ! ���ȸ���.");
		pdlg->PrintText("����ִ����ϡ�");
		pdlg->m_bBusy = false;
		return;
	}

	/*���������������ĵ�һ����ĩ*/
	UINT gmtstarttm = ReadPairGmtStartFrom(pdlg->m_strPairpath,pdlg->m_strSymbol);
	ASSERT(gmtstarttm > 0);
	CTime ctm((time_t)gmtstarttm);

	while (ctm.GetDayOfWeek()!=1)
	{
		ctm += tmspanday;
	}

	CTime tmweekstart(ctm.GetYear(),ctm.GetMonth(),ctm.GetDay(),0,0,1);
	CTime tmweekend = tmweekstart + tmspanweek;

	/*ת��RAW to HST*/
	CString strcmd, stroutfile;
	CString strstartdate, strenddate;
	int skippedcount = 0,count = 0;

	CTime tmlastmonday = lastsundayctm + tmspanday;
	while (tmweekend < tmlastmonday)
	{
		pdlg->PrintText("ת��RAW to HST: %04d-%02d-%02d - %04d-%02d-%02d",tmweekstart.GetYear(),tmweekstart.GetMonth(),
			tmweekstart.GetDay(),tmweekend.GetYear(),tmweekend.GetMonth(),tmweekend.GetDay());

		if (pdlg->m_bM1 && !AppendWeekRAWtoHST(pdlg,tmweekstart, 1))
		{
			break;
		}

		if (pdlg->m_bM5 && !AppendWeekRAWtoHST(pdlg,tmweekstart, 5))
		{
			break;
		}

		if (pdlg->m_bM15 && !AppendWeekRAWtoHST(pdlg,tmweekstart, 15))
		{
			break;
		}

		if (pdlg->m_bM30 && !AppendWeekRAWtoHST(pdlg,tmweekstart, 30))
		{
			break;
		}

		if (pdlg->m_bH1 && !AppendWeekRAWtoHST(pdlg,tmweekstart, 60))
		{
			break;
		}

		if (pdlg->m_bH4 && !AppendWeekRAWtoHST(pdlg,tmweekstart, 60 * 4))
		{
			break;
		}

		if (pdlg->m_bD1 && !AppendWeekRAWtoHST(pdlg,tmweekstart, 60 * 24))
		{
			break;
		}

		tmweekstart += tmspanweek;
		tmweekend = tmweekstart + tmspanweek;

	}

	pdlg->PrintText("����ִ����ϡ�");
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

	/*��ȡ��������·��*/
	char cpath[MAX_PATH];
	GetModuleFileName(NULL,cpath,MAX_PATH);
	CString strprogrampath = cpath;
	int pos = strprogrampath.ReverseFind('\\');
	strprogrampath = strprogrampath.Left(pos);
	NormalizePath(strprogrampath);

	/*��ȡoption.ini, currencypair.txt·��*/
	m_strPairpath = strprogrampath + "currencypair.txt";
	m_strInipath = strprogrampath + "option.ini";
	PrintText("����ini�ļ�: %s", m_strInipath);

	/*��ȡini�ļ��е�����*/
	char cline[MAX_PATH];
	GetPrivateProfileString("General","Symbol","Unknown",cline,MAX_PATH,m_strInipath);
	m_strSymbol = cline;
	m_strSymbol.Trim();
	m_strSymbol.MakeUpper();
	PrintText("��ǰSymbol: %s",m_strSymbol);

	m_NumberOfDecimalDigits = GetPrivateProfileInt("NumberOfDecimalDigits",m_strSymbol,0,m_strInipath);
	if (m_NumberOfDecimalDigits==0)
	{
		if (m_strSymbol.Find("JPY")>=0)
		{
			m_NumberOfDecimalDigits = 3;
		}
		else
		{
			m_NumberOfDecimalDigits = 5;
		}
	}

	PrintText("С��λ��: %d",m_NumberOfDecimalDigits);

	GetPrivateProfileString("General","PhpPath","Unknown",cline,MAX_PATH,m_strInipath);
	m_strPhppath = cline;
	NormalizePath(m_strPhppath);
	PrintText("Php·��: %s",m_strPhppath);

	GetPrivateProfileString("General","HstDataPath","Unknown",cline,MAX_PATH,m_strInipath);
	m_strDatapath = cline;
	NormalizePath(m_strDatapath);
	PrintText("Hst�ļ��洢λ��: %s",m_strDatapath);

	m_nServerTimeShift = GetPrivateProfileInt("General","ServerTimeShift",0,m_strInipath);
	m_nLocalTimeShift = GetPrivateProfileInt("General","LocalTimeShift",0,m_strInipath);
	PrintText("Ini�ļ�������.");

	/*����*/
	SetWindowTextA("MT4 Data Downloader (" + m_strSymbol + ")");

}

void CMyEAClientDlg::OnEnSetfocusEdit1()
{
	m_edit.SetSel(-1, 0, false);
}

/*************************************************
��������: OnCtlColor
�޸�����: 2013-10-5
��������: �ı�Editǰ��������ɫ��
**************************************************/

HBRUSH CMyEAClientDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);

	if(pWnd->GetDlgCtrlID()   ==   IDC_EDIT1)
	{   
		int nctl = 200;
		HBRUSH   hbru   =   ::CreateSolidBrush   (RGB(nctl,nctl,nctl));  
		pDC->SetTextColor(RGB(0,0,0));     //����������ɫ   
		pDC->SetBkColor(RGB(nctl,nctl,nctl));     //���ñ���ɫ   
		return   hbru;             //������Ҫ!   
	}   
	return hbr;
}


/*************************************************
��������: NormalizePath
�޸�����:    2013-6-11
��������: ��׼��Ŀ¼·��
�������: 
 - strpath ��Ҫ��׼����·��
�������: 
 - strpath ����׼�����·��
����ֵ: 
	�ޡ�
����˵��:
    ������ַ���������Ŀ¼��·����
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
��������: OnHelpAbout
��������: ���δ�����Ҫ���ڿ��ٲ����á�
*************************************************/
void CMyEAClientDlg::OnHelpAbout()
{
	CString strtm;
	CAboutDlg dlg;
	dlg.DoModal();

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

	/*
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
	*/
	
}

/*************************************************
��������: OnFileDownloaddukascopydata
��������: ����Dukascopy���ݡ� 
*************************************************/

void CMyEAClientDlg::OnFileDownloaddukascopydata()
{
	if (IDYES != MessageBox("����: һ���������أ���������ر������д��ڣ����������ɸ����ļ����ݵ��𻵡�\r\n\r\n������רҵ��Ա����˽�Ŀǰ���ص���һ���ļ�ʱ��ſ����ֶ��ر������д��ڣ����ڹرպ����ɾ�������𻵵��ļ���\r\n\r\nȷ�������밴�ǣ��˳��밴��","Warning",MB_YESNO|MB_ICONQUESTION))
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
			MessageBox("ѡ�����ڱ����������죡","Warning",MB_OK);
			return;
		}

		m_bBusy = true;
		ConvertWeekBINtoCSV(this,tm);
		PrintText("ִ����ϡ�");
		m_bBusy = false;
	}

}

/*************************************************
��������: IsCSVFileInFolder
�޸�����:    2013-10-07
��������: �ж�ָ��Ŀ¼���Ƿ����csv�ļ�
�������: 
 - strFolder ָ��Ŀ¼
�������: 
	�ޡ�
����ֵ: 
	��csv�ļ�����true�����򷵻�false�����Ŀ¼������Ҳ����false��
����˵��:
    ������ַ���������Ŀ¼��·����
*************************************************/

bool CMyEAClientDlg::IsCSVFileInFolder(CString strFolder)
{
	NormalizePath(strFolder);
	if (!PathFileExists(strFolder))
		return false;

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
	/*�ж��Ƿ����CSVĿ¼����������ж��м�CSVĿ¼���Ƿ����csv�ļ�*/
	CString strcsvfolder;
	strcsvfolder.Format("%s%s_csv\\",m_strPhppath,m_strSymbol);
	if (IsCSVFileInFolder(strcsvfolder))
	{
		MessageBox("�м�Ŀ¼"+strcsvfolder+"�д���CSV�ļ��������������ݳ�ͻ��\r\n�����޷�������","Warning",MB_OK|MB_ICONASTERISK);
		return;
	}

	/*������ʾ����*/
	if (IDYES != MessageBox("����(ת��BIN���ݵ�RAW 1Min����):\r\n\r\n1. ת��ǰ��Ҫ��֤BIN�����Ѿ�������ϣ����򽫲���ȫ���飬�������ȱ©��BIN��������ܵ����������ݵĲ�������\r\n\r\n2. ���ùر�ת���ڼ䵯���������д��ڣ�������ܵ������ݴ���\r\n\r\nȷ�������밴�ǣ��˳��밴��","Warning",MB_YESNO|MB_ICONQUESTION))
	{
		return;
	}

	/*����ת���߳�*/
	DWORD ThreadID;
	HANDLE hThread=CreateThread(NULL,
		0,
		(LPTHREAD_START_ROUTINE)ThreadBINtoRAW1MinFunc,
		(VOID*)this,
		0,
		&ThreadID);
}


void CMyEAClientDlg::OnFileConvertraw1minfiletohstfiles()
{
	/*������ʾ����*/
	if (IDYES != MessageBox("����(ת��RAW���ݵ�HST����): ת��ǰ��Ҫ��֤RAW�����Ѿ�������ϣ����򽫲���ȫ���飬�������ȱ©��RAW��������ܵ����������ݵĲ�������\r\n\r\nȷ�������밴�ǣ��˳��밴��","Warning",MB_YESNO|MB_ICONQUESTION))
	{
		return;
	}

	CPeriodDlg perioddlg;
	perioddlg.m_bM1 = m_bM1;
	perioddlg.m_bM5 = m_bM5;
	perioddlg.m_bM15 = m_bM15;
	perioddlg.m_bM30 = m_bM30;
	perioddlg.m_bH1 = m_bH1;
	perioddlg.m_bH4 = m_bH4;
	perioddlg.m_bD1 = m_bD1;
	if (perioddlg.DoModal()==IDOK)
	{
		m_bM1 = perioddlg.m_bM1;
		m_bM5 = perioddlg.m_bM5;
		m_bM15 = perioddlg.m_bM15;
		m_bM30 = perioddlg.m_bM30;
		m_bH1 = perioddlg.m_bH1;
		m_bH4 = perioddlg.m_bH4;
		m_bD1 = perioddlg.m_bD1;
	}
	else
	{
		return;
	}

	DWORD ThreadID;
	HANDLE hThread=CreateThread(NULL,
		0,
		(LPTHREAD_START_ROUTINE)ThreadRAWtoHSTFunc,
		(VOID*)this,
		0,
		&ThreadID);


}


void CMyEAClientDlg::OnUpdateViewClear(CCmdUI *pCmdUI)
{
	pCmdUI->Enable(!m_bBusy);
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

void CMyEAClientDlg::OnUpdateFileConvertraw1minfiletohstfiles(CCmdUI *pCmdUI)
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


void CMyEAClientDlg::OnCancel()
{
	if (m_bBusy)
	{
		MessageBeep(1);
		return;
	}

	CDialog::OnCancel();
}





void CMyEAClientDlg::OnFileChangecurrencypair()
{
	CPickPairDlg dlg;
	dlg.m_strpairpath = m_strPairpath;
	dlg.m_symbol = m_strSymbol;
	if (dlg.DoModal()==IDOK)
	{
		m_strSymbol = dlg.m_symbol;
		m_strSymbol.Trim();
		m_strSymbol.MakeUpper();

		PrintText("��ǰSymbol: %s",m_strSymbol);

		m_NumberOfDecimalDigits = GetPrivateProfileInt("NumberOfDecimalDigits",m_strSymbol,0,m_strInipath);
		if (m_NumberOfDecimalDigits==0)
		{
			if (m_strSymbol.Find("JPY")>=0)
			{
				m_NumberOfDecimalDigits = 3;
			}
			else
			{
				m_NumberOfDecimalDigits = 5;
			}
		}

		PrintText("С��λ��: %d",m_NumberOfDecimalDigits);
		SetWindowTextA("MT4 Data Downloader (" + m_strSymbol + ")");
	}
}


void CMyEAClientDlg::OnUpdateFileChangecurrencypair(CCmdUI *pCmdUI)
{
	pCmdUI->Enable(!m_bBusy);

}


void CMyEAClientDlg::OnFileExit()
{
	OnCancel();
}
