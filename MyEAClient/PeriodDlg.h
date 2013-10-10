#pragma once


// CPeriodDlg dialog

class CPeriodDlg : public CDialog
{
	DECLARE_DYNAMIC(CPeriodDlg)



public:
	CPeriodDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CPeriodDlg();

// Dialog Data
	enum { IDD = IDD_DIALOGPERIOD };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
//	bool m_bM1;
//	bool m_bM5;
//	bool m_bM15;
//	bool m_bM30;
//	bool m_bH1;
//	bool m_bH4;
//	bool m_bD1;
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	BOOL m_bM1;
	BOOL m_bD1;
//	CButton m_bH1;
	BOOL m_bH1;
	BOOL m_bH4;
	BOOL m_bM15;
	BOOL m_bM30;
//	CButton m_bM5;
	BOOL m_bM5;
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
};
