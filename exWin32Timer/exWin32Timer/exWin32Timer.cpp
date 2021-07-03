#include "exWin32Timer.h"

/*


*/

wchar_t g_time_str[64];
int g_time_len;
HFONT gh_font;


void OnPaint(HWND ah_wnd)
{
	PAINTSTRUCT ps;
	HDC h_dc = BeginPaint(ah_wnd, &ps);


	RECT r;
	GetClientRect(ah_wnd, &r);


	SetBkMode(h_dc, TRANSPARENT);
	SetTextColor(h_dc, RGB(255, 255, 0));

	HGDIOBJ h_old_font = SelectObject(h_dc, gh_font);

	//TextOut(h_dc, 10, 10, g_time_str, g_time_len);
	DrawText(h_dc, g_time_str, g_time_len, &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);


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
		SetTimer(hWnd, 1, 1000, NULL);

		gh_font = CreateFont(32, 0, 0, 0, 
			FW_BOLD, 
			FALSE, FALSE, FALSE, 
			DEFAULT_CHARSET, 
			OUT_DEFAULT_PRECIS,
			CLIP_DEFAULT_PRECIS, 
			DEFAULT_QUALITY, 
			DEFAULT_PITCH | FF_SWISS, 
			TEXT("굴림체"));

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

		int x = LOWORD(lParam);
		int y = HIWORD(lParam);
		//OnLButtonDown(hWnd, x, y);

	}

	break;
	case WM_TIMER:
	{
		if (wParam == 1)
		{
			SYSTEMTIME cur_time;
			//GetSystemTime(&cur_time);// UTC 기반 시스템 시간  우리나라는 UTC+9
			GetLocalTime(&cur_time);

			g_time_len = wsprintf(g_time_str, L"%02d시 %02d분 %02d초", cur_time.wHour, cur_time.wMinute, cur_time.wSecond);
		}
		InvalidateRect(hWnd, NULL, TRUE);


	}
	break;
	case WM_CLOSE:
		break;
	case WM_DESTROY:

		DeleteObject(gh_font);
		KillTimer(hWnd, 1);
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