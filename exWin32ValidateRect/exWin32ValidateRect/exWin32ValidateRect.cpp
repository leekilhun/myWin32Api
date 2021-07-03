#include "exWin32ValidateRect.h"

/*

ValidateRect 함수는?
 
 이 함수는 윈도우의 특정 영역 또는 전체영역을 유효화 상태로 변경하는 작업을 수행
 영역을 유효화 상태로 변경하는 뜻은 
 해당 영역을 정상적으로 출력했기 때문에 다시 출력할 필요가 없다고 설정하는 것
 즉 InvalidatedRect 함수의 반대 역할을 하는 함수

 따라서 InvalidateRect함수가 윈도우의 특정 영역을 무효화 시켜서 WM_PAINT 메세지를 발생시킨다면
 ValidateRect함수는 이렇게 무효화된 영역을 유효화 시켜서 WM_PAINT 메세지가 발생하는 
 것을 막는데 사용할 수 있다.




*/


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
		
		// 윈도우의 전체 영역을 유효화 시켜서 WM_PAINT 발생 조건을 제거 한다.
		// WM_PAINT 메세지가 계속해서 발생되지 않는다.
		ValidateRect(hWnd, NULL);
		return 0;
		
		/*
		hdc = BeginPaint(hWnd, &ps);

		PaintGDI(hdc);
		EndPaint(hWnd,&ps);
		*/
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