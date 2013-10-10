// PickPairDlg.cpp : implementation file
//

#include "stdafx.h"
#include "MyEAClient.h"
#include "PickPairDlg.h"
#include "afxdialogex.h"


// CPickPairDlg dialog

IMPLEMENT_DYNAMIC(CPickPairDlg, CDialog)

CPickPairDlg::CPickPairDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CPickPairDlg::IDD, pParent)
{

}

CPickPairDlg::~CPickPairDlg()
{
}

void CPickPairDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO1, m_combo);
}


BEGIN_MESSAGE_MAP(CPickPairDlg, CDialog)
END_MESSAGE_MAP()


// CPickPairDlg message handlers


BOOL CPickPairDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	CStdioFile cFile;
	CString strLine;

	if(!cFile.Open(m_strpairpath, CFile::modeRead))
		return TRUE;

	while(cFile.ReadString(strLine))
	{
		strLine.Trim();

		CString strpairread = strLine.Mid(1,6);
		strpairread.MakeUpper();
		CString str0 = strpairread.Mid(0,3);
		CString str1 = strpairread.Mid(3,3);

		if ((( str0 == "EUR")||
			(str0 == "USD")||
			(str0 == "GBP")||
			(str0 == "JPY")||
			(str0 == "AUD")||
			(str0 == "CHF")||
			(str0 == "NZD")||
			(str0 == "CAD"))
			&&
			(( str1 == "EUR")||
			(str1 == "USD")||
			(str1 == "GBP")||
			(str1 == "JPY")||
			(str1 == "AUD")||
			(str1 == "CHF")||
			(str1 == "NZD")||
			(str1 == "CAD")))

		{

			m_combo.AddString(strpairread);
		}
		
	}

	int i;
	for (i=0;i<m_combo.GetCount();i++)
	{
		CString str;
		m_combo.GetLBText(i,str);
		if (str == m_symbol)
		{
			m_combo.SetCurSel(i);
			break;
		}
	}


	cFile.Close();



	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}


void CPickPairDlg::OnOK()
{
	m_combo.GetLBText(m_combo.GetCurSel(),m_symbol);

	CDialog::OnOK();
}
