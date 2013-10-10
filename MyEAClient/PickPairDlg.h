#pragma once


// CPickPairDlg dialog

class CPickPairDlg : public CDialog
{
	DECLARE_DYNAMIC(CPickPairDlg)
public:
	CString m_strpairpath;
	CString m_symbol;

public:
	CPickPairDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CPickPairDlg();

// Dialog Data
	enum { IDD = IDD_DIALOG2 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	CComboBox m_combo;
	virtual void OnOK();
};
