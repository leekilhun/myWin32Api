
// ExamPos.h : PROJECT_NAME ���� ���α׷��� ���� �� ��� �����Դϴ�.
//

#pragma once

#ifndef __AFXWIN_H__
	#error "PCH�� ���� �� ������ �����ϱ� ���� 'stdafx.h'�� �����մϴ�."
#endif

#include "resource.h"		// �� ��ȣ�Դϴ�.


// CExamPosApp:
// �� Ŭ������ ������ ���ؼ��� ExamPos.cpp�� �����Ͻʽÿ�.
//

class CExamPosApp : public CWinApp
{
public:
	CExamPosApp();

// �������Դϴ�.
public:
	virtual BOOL InitInstance();

// �����Դϴ�.

	DECLARE_MESSAGE_MAP()
};

extern CExamPosApp theApp;
