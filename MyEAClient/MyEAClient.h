// MyEAClient.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CMyEAClientApp:
// �йش����ʵ�֣������ MyEAClient.cpp
//

class CMyEAClientApp : public CWinApp
{
public:
	CMyEAClientApp();

// ��д
	public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CMyEAClientApp theApp;