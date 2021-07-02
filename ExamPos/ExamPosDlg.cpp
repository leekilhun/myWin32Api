
// ExamPosDlg.cpp : ���� ����
//

#include "stdafx.h"
#include "ExamPos.h"
#include "ExamPosDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CExamPosDlg ��ȭ ����



CExamPosDlg::CExamPosDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_EXAMPOS_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CExamPosDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CExamPosDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_MOVE()
END_MESSAGE_MAP()


// CExamPosDlg �޽��� ó����

BOOL CExamPosDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// �� ��ȭ ������ �������� �����մϴ�.  ���� ���α׷��� �� â�� ��ȭ ���ڰ� �ƴ� ��쿡��
	//  �����ӿ�ũ�� �� �۾��� �ڵ����� �����մϴ�.
	SetIcon(m_hIcon, TRUE);			// ū �������� �����մϴ�.
	SetIcon(m_hIcon, FALSE);		// ���� �������� �����մϴ�.

	return TRUE;  // ��Ŀ���� ��Ʈ�ѿ� �������� ������ TRUE�� ��ȯ�մϴ�.
}

// ��ȭ ���ڿ� �ּ�ȭ ���߸� �߰��� ��� �������� �׸�����
//  �Ʒ� �ڵ尡 �ʿ��մϴ�.  ����/�� ���� ����ϴ� MFC ���� ���α׷��� ��쿡��
//  �����ӿ�ũ���� �� �۾��� �ڵ����� �����մϴ�.

void CExamPosDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // �׸��⸦ ���� ����̽� ���ؽ�Ʈ�Դϴ�.

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Ŭ���̾�Ʈ �簢������ �������� ����� ����ϴ�.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// �������� �׸��ϴ�.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// ����ڰ� �ּ�ȭ�� â�� ���� ���ȿ� Ŀ���� ǥ�õǵ��� �ý��ۿ���
//  �� �Լ��� ȣ���մϴ�.
HCURSOR CExamPosDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CExamPosDlg::OnMove(int x, int y)
{
	CDialogEx::OnMove(x, y);

	CRect r;
	GetWindowRect(r);

	CString str;
	str.Format(L"(%04d, %04d), (%04d, %04d)", r.left, r.top, r.right, r.bottom);
	SetDlgItemText(IDC_DLG_POS_EDIT, str);

	GetClientRect(r);

	str.Format(L"(%04d, %04d), (%04d, %04d)", r.left, r.top, r.right, r.bottom);
	SetDlgItemText(IDC_CLIENT_POS_EDIT, str);

	CWnd *p_ok_btn = GetDlgItem(IDOK);
	if (NULL != p_ok_btn) {
		p_ok_btn->GetWindowRect(r);

		str.Format(L"(%04d, %04d), (%04d, %04d)", r.left, r.top, r.right, r.bottom);
		SetDlgItemText(IDC_OK_POS_EDIT, str);

		ScreenToClient(r);
		str.Format(L"(%04d, %04d), (%04d, %04d)", r.left, r.top, r.right, r.bottom);
		SetDlgItemText(IDC_OK_FIX_POS_EDIT, str);
	}
}
