#include "exWin32ThreeRectangle.h"

/*


*/

#define MAX_COUNT 5

int g_index[MAX_COUNT] = {0};





void PaintGDI(HDC hdc)
{
	Gdiplus::Pen pen(Gdiplus::Color(0, 0, 255), 3);
	Gdiplus::Point pt1(20, 30);
	Gdiplus::Point pt2(100, 30);
	Gdiplus::Graphics g(hdc);
	g.DrawLine(&pen, pt1, pt2);


}

void OnPaint(HWND ah_wnd)
{
	PAINTSTRUCT ps;
	HDC h_dc = BeginPaint(ah_wnd, &ps);

	for (int i = 0; i < MAX_COUNT; i++)
	{
		Rectangle(h_dc, i * 100, 0, 101 + i * 100, 101);
		Rectangle(h_dc, i * 100, 100, 101 + i * 100, 200);
	}

	HGDIOBJ h_old_bruch = SelectObject(h_dc, GetStockObject(NULL_BRUSH));
	for (int i = 0; i < MAX_COUNT; i++)
	{
		Rectangle(h_dc, i * 100 -40, 5, 101 + i * 100-50, 95);
	}

	SelectObject(h_dc, GetStockObject(BLACK_BRUSH));//GetCurrentObject(h_dc, OBJ_BRUSH);
	
	for (int i = 0; i < MAX_COUNT; i++)
	{
		if (g_index[i] == 1) Ellipse(h_dc, i * 100 - 50, 50, 101 + i * 100 - 50, 150);

	}

	SelectObject(h_dc, h_old_bruch);


#if 0

	/*
	for (int i = 0; i < MAX_COUNT; i++)
	{
		if (1 == g_index[i])
		{
			HGDIOBJ h_old_brush = SelectObject(h_dc, GetStockObject(BLACK_BRUSH));
			Rectangle(h_dc, i * 100, 0, 101 + i * 100, 100);
			SelectObject(h_dc, h_old_brush);
		}
		else
		{
			Rectangle(h_dc, i * 100, 0, 101 + i * 100, 100);
		}
	}

	*/
	HGDIOBJ h_old_bruch = GetCurrentObject(h_dc, OBJ_BRUSH);

	int table[2] = {WHITE_BRUSH, BLACK_BRUSH}, index;
	for (int i = 0; i < MAX_COUNT; i++)
	{
		index = g_index[i];
		SelectObject(h_dc, GetStockObject(table[index]));
		Rectangle(h_dc, i * 100, 0, 101 + i * 100, 101);
	}

	SelectObject(h_dc, h_old_bruch);
	//SelectObject(h_dc, GetStockObject(WHITE_BRUSH));


	for (int i = 0; i < MAX_COUNT; i++)
	{
		//index = g_index[i];
		Rectangle(h_dc, i * 100, 100, 101 + i * 100, 200);
	}

#endif // 0




	EndPaint(ah_wnd, &ps);

}

void OnLButtonDown(HWND a_hWnd, int a_x, int a_y)
{
	if (a_y >= 0 && a_y < 100)
	{

		UINT index = (a_x + 50) / 100;
		if (index < MAX_COUNT)
		{

			/*
			int remain = a_x % 100; // 140% 100->40, 270%100 -> 70
			if (remain >= 50) index++;
			*/
			g_index[index] = !g_index[index]; //(g_index[i] +1) % 2 
			InvalidateRect(a_hWnd, NULL, TRUE);
		}

		/*
		for (int i = 0; i < MAX_COUNT; i++)
		{
			// 0    ~  99  : 0 
			// 100  ~ 199  : 1
			// 200  ~ 299  : 2
			// 300  ~ 399  : 3

			if (a_x < (i + 1) * 100)
			{
				g_index[i] = !g_index[i]; //(g_index[i] +1) % 2 
				InvalidateRect(a_hWnd, NULL, TRUE);
				break;
			}
		}
		*/

	}
	//HDC h_dc = GetDC(a_hWnd);
	

	//ReleaseDC(a_hWnd, h_dc);
}


LRESULT CALLBACK WindProcedure(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam)
{
	switch (Msg)
	{
	case WM_CREATE:
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
		OnLButtonDown(hWnd, x, y);

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
		50, 50, 600, 600, 0, 0, 0, 0)) return -1;

	//while(PeekMessage(&msg, 0, 0, 0,PM_REMOVE))

	while (GetMessageW(&msg, 0, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessageW(&msg);

	}

	DeleteObject(h_bk_brush);

	return 0;



}