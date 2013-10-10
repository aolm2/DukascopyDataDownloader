// MyEAClientDlg.h : 头文件
//

#pragma once
#include "afxwin.h"

#define WM_EAMSG 0x0402
#define WPARAM_VERIFY  1
#define RET_MSG_OK     99
#define RET_MSG_ERR    -99

// CMyEAClientDlg 对话框
class CMyEAClientDlg : public CDialog
{
public:
	CString m_strInipath;/*option.ini的路径*/
	CString m_strPairpath;/*currencypair.txt的路径*/
	CString m_strPhppath;
	CString m_strDatapath;/*生成hst文件的路径*/
	CString m_strSymbol;
	int m_NumberOfDecimalDigits;/*小数部分的位数, USDJPY为例为3，EURUSD为例为5*/
	int m_nServerTimeShift;/*服务器偏移时间，小时计*/
	int m_nLocalTimeShift;/*本地偏移时间，小时计*/

	bool m_bBusy;/*程序正在进行下载、数据转换等工作。表明不可进行其他操作。*/
	int m_clientcount;/*通讯于EA窗口*/


	BOOL m_bM1, m_bM5, m_bM15, m_bM30, m_bH1, m_bH4, m_bD1;

	//Funcations
	void Init();
	void PrintLog(CString str);
	void PrintText(LPCTSTR format, ...);
	void NormalizePath(CString &strpath);
	bool IsCSVFileInFolder(CString strFolder);

// 构造
public:
	CMyEAClientDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_MYEACLIENT_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
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
	afx_msg void OnFileConvertbintoraw1minfile();
	afx_msg void OnUpdateFileDownloaddukascopydata(CCmdUI *pCmdUI);
	afx_msg void OnUpdateFileConvertbintocsvtickfile(CCmdUI *pCmdUI);
	afx_msg void OnUpdateFileConvertbintoraw1minfile(CCmdUI *pCmdUI);
	afx_msg void OnUpdateFileConvertraw1minfiletohst1min(CCmdUI *pCmdUI);
	virtual BOOL ContinueModal();
	afx_msg void OnFileConvertraw1minfiletohstfiles();
	afx_msg void OnUpdateFileConvertraw1minfiletohstfiles(CCmdUI *pCmdUI);
	virtual void OnCancel();
	afx_msg void OnUpdateViewClear(CCmdUI *pCmdUI);
	afx_msg void OnFileChangecurrencypair();
	afx_msg void OnUpdateFileChangecurrencypair(CCmdUI *pCmdUI);
	afx_msg void OnFileExit();
};
