// MyEAClientDlg.h : ͷ�ļ�
//

#pragma once
#include "afxwin.h"

#define WM_EAMSG 0x0402
#define WPARAM_VERIFY  1
#define RET_MSG_OK     99
#define RET_MSG_ERR    -99

// CMyEAClientDlg �Ի���
class CMyEAClientDlg : public CDialog
{
public:
	CString m_strInipath;/*option.ini��·��*/
	CString m_strPairpath;/*currencypair.txt��·��*/
	CString m_strPhppath;
	CString m_strDatapath;/*����hst�ļ���·��*/
	CString m_strSymbol;
	int m_nDotMultiper;/*10��С��λ������-��EURUSDΪ��Ϊ100000,��USDJPYΪ��Ϊ1000�����۵�С������м�λ���м���0.*/
	int m_nServerTimeShift;/*������ƫ��ʱ�䣬Сʱ��*/
	int m_nLocalTimeShift;/*����ƫ��ʱ�䣬Сʱ��*/

	bool m_bBusy;/*�������ڽ������ء�����ת���ȹ������������ɽ�������������*/
	int m_clientcount;/*ͨѶ��EA����*/

	//Funcations
	void Init();
	void PrintLog(CString str);
	void PrintText(LPCTSTR format, ...);
	void NormalizePath(CString &strpath);
	bool IsCSVFileInFolder(CString strFolder);

// ����
public:
	CMyEAClientDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_MYEACLIENT_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg LRESULT OnEAMessage(WPARAM wParam, LPARAM lParam);
	DECLARE_MESSAGE_MAP()


public:
	CEdit m_edit;
	bool m_bcreated;
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnEnSetfocusEdit1();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnFileDownloaddukascopydata();
	afx_msg void OnViewClear();
	afx_msg void OnHelpAbout();
	afx_msg void OnFileConvertbintocsvtickfile();
	afx_msg void OnFileConvertraw1minfiletohst1min();
	afx_msg void OnFileConvertbintoraw1minfile();
	afx_msg void OnUpdateFileDownloaddukascopydata(CCmdUI *pCmdUI);
	afx_msg void OnUpdateFileConvertbintocsvtickfile(CCmdUI *pCmdUI);
	afx_msg void OnUpdateFileConvertbintoraw1minfile(CCmdUI *pCmdUI);
	afx_msg void OnUpdateFileConvertraw1minfiletohst1min(CCmdUI *pCmdUI);
	virtual BOOL ContinueModal();
};
