
// ExamPos.cpp : 응용 프로그램에 대한 클래스 동작을 정의합니다.
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

// CExamPosApp 생성

CExamPosApp::CExamPosApp()
{
	// TODO: 여기에 생성 코드를 추가합니다.
	// InitInstance에 모든 중요한 초기화 작업을 배치합니다.
}

// 유일한 CExamPosApp 개체입니다.
CExamPosApp theApp;

// CExamPosApp 초기화
BOOL CExamPosApp::InitInstance()
{
	CWinApp::InitInstance();

	CExamPosDlg dlg;
	m_pMainWnd = &dlg;
	dlg.DoModal();

	return FALSE;
}

