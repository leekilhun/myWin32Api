#include "exWin32macro1.h"
#include "time.h"
/*
실행되어 있는 메모장에 텍스트 출력, 읽기

*/




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
		
	}
	break;
	case WM_COMMAND:
		break;
	case WM_PAINT:
	{
		OnPaint(hWnd);

	}
	break;
	case WM_LBUTTONDOWN:
	{
		HWND h_find_wnd = FindWindow(L"Notepad", NULL);
		if (NULL != h_find_wnd)
		{
			HWND h_edit_wnd = FindWindowEx(h_find_wnd, NULL, L"Edit", NULL); //소속된 윈도우를 찾는다
			if (NULL != h_edit_wnd)
			{
				//SendMessage(h_edit_wnd, WM_SETTEXT, 0, (LPARAM)L"안녕하세요");

				const wchar_t str[256] = {};
				SendMessage(h_edit_wnd, WM_GETTEXT, 256, (LPARAM)str);
				MessageBox(hWnd, str, L"에디트에 적힌 내용 확인", MB_OK);
			}
		}
	
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