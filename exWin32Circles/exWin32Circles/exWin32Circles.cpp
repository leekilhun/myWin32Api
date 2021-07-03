#include "exWin32Circles.h"

/*


*/

int g_pos1 = 0, g_pos2 = 0;

void CALLBACK MyMoveTimer(HWND hWnd, UINT nMsg, UINT_PTR nIDEVENT, DWORD dwTime)
{
	g_pos1 += 10;
	if (g_pos1 >= 400) g_pos1 = 0;

	InvalidateRect(hWnd, NULL, TRUE);

	/*
	HDC h_dc = GetDC(hWnd);
	Ellipse(h_dc, g_pos, 10, g_pos + 100, 110);
	ReleaseDC(hWnd, h_dc);
	*/
}




void OnPaint(HWND ah_wnd)
{
	PAINTSTRUCT ps;
	HDC h_dc = BeginPaint(ah_wnd, &ps);

	Ellipse(h_dc, g_pos1, 10, g_pos1 + 30, 40);
	Ellipse(h_dc, g_pos2, 50, g_pos2 + 30, 80);

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
		SetTimer(hWnd, 1, 300, MyMoveTimer);
		SetTimer(hWnd, 2, 200, NULL);
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

		
		if (wParam == 2)
		{
			g_pos2 = (g_pos2 + 10) % 400;
			
			//g_pos2 += 10;
			//if (g_pos2 >= 400) g_pos2 = 0;
		
			InvalidateRect(hWnd, NULL, TRUE);
		}
		

	}
	break;
	case WM_CLOSE:
		break;
	case WM_DESTROY:
		KillTimer(hWnd, 1);
		KillTimer(hWnd, 2);
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
		50, 50, 900, 600, 0, 0, 0, 0)) return -1;

	//while(PeekMessage(&msg, 0, 0, 0,PM_REMOVE))

	while (GetMessageW(&msg, 0, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessageW(&msg);

	}

	DeleteObject(h_bk_brush);

	return 0;



}