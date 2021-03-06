// SelectDateDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "MyEAClient.h"
#include "SelectDateDlg.h"


// CSelectDateDlg 对话框

IMPLEMENT_DYNAMIC(CSelectDateDlg, CDialog)

CSelectDateDlg::CSelectDateDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CSelectDateDlg::IDD, pParent)
{

}

CSelectDateDlg::~CSelectDateDlg()
{
}

void CSelectDateDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_DATETIMEPICKER1, m_datepicker);
}


BEGIN_MESSAGE_MAP(CSelectDateDlg, CDialog)
	ON_BN_CLICKED(IDOK, &CSelectDateDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// CSelectDateDlg 消息处理程序

void CSelectDateDlg::OnBnClickedOk()
{
	OnOK();
}

void CSelectDateDlg::OnOK()
{
	CTime ctm;
	m_datepicker.GetTime(ctm);
	m_year = ctm.GetYear();
	m_month = ctm.GetMonth();
	m_day = ctm.GetDay();

	CDialog::OnOK();
}

BOOL CSelectDateDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	CTime ctm = CTime::GetCurrentTime();
	m_datepicker.SetTime(&ctm);

	return TRUE;  // return TRUE unless you set the focus to a control
	// Òì³£: OCX ÊôÐÔÒ³Ó¦·µ»Ø FALSE
}
