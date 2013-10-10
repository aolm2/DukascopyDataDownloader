// PeriodDlg.cpp : implementation file
//

#include "stdafx.h"
#include "MyEAClient.h"
#include "PeriodDlg.h"
#include "afxdialogex.h"


// CPeriodDlg dialog

IMPLEMENT_DYNAMIC(CPeriodDlg, CDialog)

CPeriodDlg::CPeriodDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CPeriodDlg::IDD, pParent)
	, m_bM1(false)
	, m_bM5(false)
	, m_bM15(false)
	, m_bM30(false)
	, m_bH1(false)
	, m_bH4(false)
	, m_bD1(false)
{

}

CPeriodDlg::~CPeriodDlg()
{
}

void CPeriodDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Check(pDX, IDC_CHECKM1, m_bM1);
	DDX_Check(pDX, IDC_CHECKD1, m_bD1);
	//  DDX_Control(pDX, IDC_CHECKH1, m_bH1);
	DDX_Check(pDX, IDC_CHECKH1, m_bH1);
	DDX_Check(pDX, IDC_CHECKH4, m_bH4);
	DDX_Check(pDX, IDC_CHECKM15, m_bM15);
	DDX_Check(pDX, IDC_CHECKM30, m_bM30);
	//  DDX_Control(pDX, IDC_CHECKM5, m_bM5);
	DDX_Check(pDX, IDC_CHECKM5, m_bM5);
}


BEGIN_MESSAGE_MAP(CPeriodDlg, CDialog)
	ON_BN_CLICKED(IDC_BUTTON1, &CPeriodDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CPeriodDlg::OnBnClickedButton2)
END_MESSAGE_MAP()


// CPeriodDlg message handlers


BOOL CPeriodDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}


void CPeriodDlg::OnOK()
{
	UpdateData(TRUE);

	CDialog::OnOK();
}


void CPeriodDlg::OnBnClickedButton1()
{
	m_bM1 = FALSE; 
	m_bM5 = FALSE; 
	m_bM15 = FALSE; 
	m_bM30 = FALSE; 
	m_bH1 = FALSE; 
	m_bH4 = FALSE; 
	m_bD1 = FALSE;

	UpdateData(FALSE);
}


void CPeriodDlg::OnBnClickedButton2()
{
	m_bM1 = TRUE; 
	m_bM5 = TRUE; 
	m_bM15 = TRUE; 
	m_bM30 = TRUE; 
	m_bH1 = TRUE; 
	m_bH4 = TRUE; 
	m_bD1 = TRUE;

	UpdateData(FALSE);
}
