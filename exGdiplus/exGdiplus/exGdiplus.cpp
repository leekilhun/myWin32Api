#include "exGdiplus.h"

void PaintGDI(HDC hdc) 
{
	Gdiplus::Pen pen(Gdiplus::Color(0, 0, 255), 3);
	Gdiplus::Point pt1(20, 30);
	Gdiplus::Point pt2(100, 30);
	Gdiplus::Graphics g(hdc);
	g.DrawLine(&pen, pt1, pt2);


}



LRESULT CALLBACK WindProcedure(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam)
{
	HDC hdc;
	PAINTSTRUCT ps;

	switch (Msg)
	{
	case WM_CREATE:
		break;
	case WM_COMMAND:
		break;
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);

		PaintGDI(hdc);
		EndPaint(hWnd,&ps);
		break;
	case WM_CLOSE:
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;	
	}

	return DefWindowProc(hWnd, Msg, wParam, lParam);
}


int WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrev, LPSTR Args, int cmdlines)
{
	ULONG_PTR token;
	Gdiplus::GdiplusStartupInput input;
	WNDCLASSW wnd = {0};
	MSG msg = {0};

	wnd.lpfnWndProc = WindProcedure;
	wnd.hInstance = hInst;
	wnd.hCursor = LoadCursor(hInst, IDC_ARROW);
	wnd.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wnd.lpszClassName = L"sample";
	wnd.hIcon = LoadIcon(hInst, IDI_APPLICATION);
	wnd.style = CS_HREDRAW | CS_VREDRAW;
	
	Gdiplus::GdiplusStartup(&token, &input, NULL);


	if (!RegisterClassW(&wnd)) return -1;
	if(!CreateWindowW(L"sample", L"GDI+", WS_OVERLAPPEDWINDOW|WS_VISIBLE,
		0, 0, 860, 780, 0, 0, 0, 0)) return -1;

	while (GetMessageW(&msg, 0, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessageW(&msg);

	}

	return 0;



}