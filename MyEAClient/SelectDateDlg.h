#pragma once
#include "afxdtctl.h"


// CSelectDateDlg �Ի���

class CSelectDateDlg : public CDialog
{
	DECLARE_DYNAMIC(CSelectDateDlg)
public:
	int m_year,m_month,m_day;

public:
	CSelectDateDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CSelectDateDlg();

// �Ի�������
	enum { IDD = IDD_DIALOGSELECTDATE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CDateTimeCtrl m_datepicker;
	afx_msg void OnBnClickedOk();
protected:
	virtual void OnOK();
public:
	virtual BOOL OnInitDialog();
};
