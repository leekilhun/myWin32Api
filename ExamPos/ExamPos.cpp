
// ExamPos.cpp : ���� ���α׷��� ���� Ŭ���� ������ �����մϴ�.
//

#include "stdafx.h"
#include "ExamPos.h"
#include "ExamPosDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CExamPosApp

BEGIN_MESSAGE_MAP(CExamPosApp, CWinApp)
	ON_COMMAND(ID_HELP, &CWinApp::OnHelp)
END_MESSAGE_MAP()

// CExamPosApp ����

CExamPosApp::CExamPosApp()
{
	// TODO: ���⿡ ���� �ڵ带 �߰��մϴ�.
	// InitInstance�� ��� �߿��� �ʱ�ȭ �۾��� ��ġ�մϴ�.
}

// ������ CExamPosApp ��ü�Դϴ�.
CExamPosApp theApp;

// CExamPosApp �ʱ�ȭ
BOOL CExamPosApp::InitInstance()
{
	CWinApp::InitInstance();

	CExamPosDlg dlg;
	m_pMainWnd = &dlg;
	dlg.DoModal();

	return FALSE;
}

