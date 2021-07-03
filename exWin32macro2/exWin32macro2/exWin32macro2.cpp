#include "exWin32macro2.h"
#include "time.h"
#include "stdio.h"
/*
실행되어 있는 여러개의 메모장에 텍스트 출력, 읽기

*/

#define MAX_COUNT 5

struct TalkWnd
{
	HWND h_talk_wnd, h_edit_wnd;

	wchar_t title[256];
};

TalkWnd g_talk_list[MAX_COUNT];
int g_talk_count = 0;

HWND gh_chat_edit, gh_send_btn, gh_list_box;

void FindTalkWindow() 
{

	HWND h_find_wnd = NULL;
	HWND h_edit_wnd = NULL;
	TalkWnd* p = g_talk_list;
	wchar_t str[256];
	while (h_find_wnd = FindWindowEx(NULL, h_find_wnd, L"Notepad", NULL))
	{
		if (NULL != h_find_wnd)
		{
			p->h_edit_wnd = FindWindowEx(h_find_wnd, NULL, L"Edit", NULL);
			if (NULL != p->h_edit_wnd)
			{
				p->h_talk_wnd = h_find_wnd;
				GetWindowText(p->h_talk_wnd, p->title, 256);
				swprintf_s(str, 256, L"찾음 : %s", p->title);
				SendMessage(gh_list_box, LB_INSERTSTRING, g_talk_count, (LPARAM)str);

				p++;
				g_talk_count++;

			}
			/*
			h_edit_wnd = FindWindowEx(h_find_wnd, NULL, L"Edit", NULL);
			if (NULL != h_edit_wnd)
			{
				p->h_talk_wnd = h_find_wnd;
				p->h_edit_wnd = h_edit_wnd;
				GetWindowText(p->h_talk_wnd, p->title, 256);
				swprintf_s(str, 256, L"찾음 : %s", p->title);
				SendMessage(gh_list_box, LB_INSERTSTRING, g_talk_count, (LPARAM)str);

				p++;
				g_talk_count++;

			}
			*/
		}		
	}

	/*
	// 자신의 컴퓨터에 실행되어 있는 대화 상자를 검색
	while (g_talk_list[g_talk_count].h_talk_wnd = FindWindowEx(NULL, g_talk_list[g_talk_count].h_talk_wnd, L"Notepad", NULL))
	{
		g_talk_list[g_talk_count].h_edit_wnd = FindWindowEx(g_talk_list[g_talk_count].h_talk_wnd, NULL, L"Edit", NULL);
		if (NULL != g_talk_list[g_talk_count].h_edit_wnd)
		{

		}

	}
	*/
}


void SendChatData()
{
	if (g_talk_count == 0) return;

	wchar_t str[128];
	GetWindowText(gh_chat_edit, str, 128);

	TalkWnd* p = g_talk_list;

	for (int i = 0; i < g_talk_count; i++)
	{
		SendMessage(p->h_edit_wnd, WM_SETTEXT, 0, (LPARAM)str);
		// SendMessage(h_edit_wnd, WM_SETTEXT, 0, (LPARAM)L"안녕하세요");
		p++;
	}

	/*
	Sleep(200);
	
	p = g_talk_list;

	for (int i = 0; i < g_talk_count; i++)
	{
		//Enter키를 누른 것과 같은 메세지
		PostMessage(p->h_edit_wnd, WM_KEYDOWN, 0x0000000D, 0x001C001);
		PostMessage(p->h_edit_wnd, WM_KEYUP, 0x0000000D, 0xC01C001);
		p++;
	}
	*/
	
}

void OnPaint(HWND ah_wnd)
{
	PAINTSTRUCT ps;
	HDC h_dc = BeginPaint(ah_wnd, &ps);
	


	EndPaint(ah_wnd, &ps);

}

void OnLButtonDown(HWND a_hWnd, int a_x, int a_y)
{

	//HDC h_dc = GetDC(a_hWnd);


	//ReleaseDC(a_hWnd, h_dc);
}


LRESULT CALLBACK WindProcedure(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam)
{
	switch (Msg)
	{
	case WM_CREATE:
	{
		gh_chat_edit = CreateWindowEx(WS_EX_CLIENTEDGE, L"EDIT", NULL,
			WS_CHILD | WS_VISIBLE | WS_BORDER | ES_AUTOHSCROLL,
			5, 303, 380, 28, hWnd, (HMENU)25002, NULL, NULL);

		gh_send_btn = CreateWindow(L"Button", L"전송",
			WS_CHILD | WS_VISIBLE | BS_DEFPUSHBUTTON,
			390, 301, 80, 31, hWnd, (HMENU)25003, NULL, NULL);

		gh_list_box = CreateWindowEx(WS_EX_CLIENTEDGE, L"ListBox", NULL,
			WS_CHILD | WS_VISIBLE | LBS_STANDARD,
			5, 5, 465, 300, hWnd, (HMENU)25001, NULL, NULL);

		FindTalkWindow();
	}
	break;
	case WM_COMMAND:
	{
		if (LOWORD(wParam) == 25003) SendChatData();
		
	}
		break;
	case WM_PAINT:
	{
		OnPaint(hWnd);

	}
	break;
	case WM_LBUTTONDOWN:
	{
		
	
	}

	break;
	case WM_SIZE:
	{
		
	}
	break;
	case WM_TIMER:
	{
		

	}
	break;
	case WM_CLOSE:
		break;
	case WM_DESTROY:
		DestroyWindow(gh_chat_edit);
		DestroyWindow(gh_send_btn);
		DestroyWindow(gh_list_box);
		PostQuitMessage(0);
		break;
	}

	return DefWindowProc(hWnd, Msg, wParam, lParam);
}

void PaintGDI(HDC hdc)
{
	Gdiplus::Pen pen(Gdiplus::Color(0, 0, 255), 3);
	Gdiplus::Point pt1(20, 30);
	Gdiplus::Point pt2(100, 30);
	Gdiplus::Graphics g(hdc);
	g.DrawLine(&pen, pt1, pt2);


}

int WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrev, LPSTR Args, int cmdlines)
{
	ULONG_PTR token;
	Gdiplus::GdiplusStartupInput input;
	WNDCLASSW wnd = {0};
	MSG msg = {0};
	const wchar_t* class_name = L"tutorial";
	HBRUSH h_bk_brush = CreateSolidBrush(RGB(244, 176, 77));
	wnd.cbClsExtra = 0;
	wnd.cbWndExtra = 0;
	wnd.hbrBackground = h_bk_brush;//(HBRUSH)GetStockObject(WHITE_BRUSH);
	wnd.hCursor = LoadCursor(NULL, IDC_ARROW);
	wnd.hIcon = LoadIcon(NULL, IDI_APPLICATION);

	wnd.lpfnWndProc = WindProcedure;
	wnd.lpszClassName = class_name;

	wnd.hInstance = hInst;
	wnd.style = CS_HREDRAW | CS_VREDRAW;

	Gdiplus::GdiplusStartup(&token, &input, NULL);


	if (!RegisterClassW(&wnd)) return -1;
	if (!CreateWindowW(class_name, L"GDI+ tutorial", WS_OVERLAPPEDWINDOW | WS_VISIBLE,
		50, 50, 500, 400, 0, 0, 0, 0)) return -1;

	//while(PeekMessage(&msg, 0, 0, 0,PM_REMOVE))

	while (GetMessageW(&msg, 0, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessageW(&msg);

	}

	DeleteObject(h_bk_brush);

	return 0;



}