#pragma once
#include "afxdtctl.h"


// CSelectDateDlg 对话框

class CSelectDateDlg : public CDialog
{
	DECLARE_DYNAMIC(CSelectDateDlg)
public:
	int m_year,m_month,m_day;

public:
	CSelectDateDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CSelectDateDlg();

// 对话框数据
	enum { IDD = IDD_DIALOGSELECTDATE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CDateTimeCtrl m_datepicker;
	afx_msg void OnBnClickedOk();
protected:
	virtual void OnOK();
public:
	virtual BOOL OnInitDialog();
};
