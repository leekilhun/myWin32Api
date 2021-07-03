#include "exWin32Multiple.h"

/*


*/



void PaintGDI(HDC hdc)
{
	Gdiplus::Pen pen(Gdiplus::Color(0, 0, 255), 3);
	Gdiplus::Point pt1(20, 30);
	Gdiplus::Point pt2(100, 30);
	Gdiplus::Graphics g(hdc);
	g.DrawLine(&pen, pt1, pt2);


}


void expFont(HWND ah_wnd)
{
	RECT rect;
	HBRUSH hBrush;
	HFONT hFont;
	PAINTSTRUCT ps;
	HDC hdc = BeginPaint(ah_wnd, &ps);


	//Logical units are device dependent pixels, so this will create a handle to a logical font that is 48 pixels in height.
	//The width, when set to 0, will cause the font mapper to choose the closest matching value.
	//The font face name will be Impact.
	hFont = CreateFont(48, 0, 0, 0, FW_DONTCARE, FALSE, TRUE, FALSE, DEFAULT_CHARSET, OUT_OUTLINE_PRECIS,
		CLIP_DEFAULT_PRECIS, CLEARTYPE_QUALITY, VARIABLE_PITCH, TEXT("Impact"));
	SelectObject(hdc, hFont);

	//Sets the coordinates for the rectangle in which the text is to be formatted.
	SetRect(&rect, 100, 100, 700, 200);
	SetTextColor(hdc, RGB(255, 0, 0));
	DrawText(hdc, TEXT("Drawing Text with Impact"), -1, &rect, DT_NOCLIP);


	//Logical units are device dependent pixels, so this will create a handle to a logical font that is 36 pixels in height.
	//The width, when set to 20, will cause the font mapper to choose a font which, in this case, is stretched.
	//The font face name will be Times New Roman.  This time nEscapement is at -300 tenths of a degree (-30 degrees)
	hFont = CreateFont(36, 20, -300, 0, FW_DONTCARE, FALSE, TRUE, FALSE, DEFAULT_CHARSET, OUT_OUTLINE_PRECIS,
		CLIP_DEFAULT_PRECIS, CLEARTYPE_QUALITY, VARIABLE_PITCH, TEXT("Times New Roman"));
	SelectObject(hdc, hFont);

	//Sets the coordinates for the rectangle in which the text is to be formatted.
	SetRect(&rect, 100, 200, 900, 800);
	SetTextColor(hdc, RGB(0, 128, 0));
	DrawText(hdc, TEXT("Drawing Text with Times New Roman"), -1, &rect, DT_NOCLIP);


	//Logical units are device dependent pixels, so this will create a handle to a logical font that is 36 pixels in height.
	//The width, when set to 10, will cause the font mapper to choose a font which, in this case, is compressed. 
	//The font face name will be Arial. This time nEscapement is at 250 tenths of a degree (25 degrees)
	hFont = CreateFont(36, 10, 250, 0, FW_DONTCARE, FALSE, TRUE, FALSE, DEFAULT_CHARSET, OUT_OUTLINE_PRECIS,
		CLIP_DEFAULT_PRECIS, ANTIALIASED_QUALITY, VARIABLE_PITCH, TEXT("Arial"));
	SelectObject(hdc, hFont);

	//Sets the coordinates for the rectangle in which the text is to be formatted.
	SetRect(&rect, 500, 200, 1400, 600);
	SetTextColor(hdc, RGB(0, 0, 255));
	DrawText(hdc, TEXT("Drawing Text with Arial"), -1, &rect, DT_NOCLIP);

	DeleteObject(hFont);

	EndPaint(ah_wnd, &ps);
}
void OnPaint(HWND ah_wnd)
{
	PAINTSTRUCT ps;
	HDC h_dc = BeginPaint(ah_wnd, &ps);

	wchar_t str[64];
	int len;

	SetTextColor(h_dc, RGB(0, 100, 200));
	SetBkMode(h_dc, TRANSPARENT);

	HFONT h_font = CreateFont(32, 0, 0, 0, FW_BOLD, FALSE, FALSE, 0, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS,
		CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS, L"굴림체");

	HGDIOBJ h_old_font = SelectObject(h_dc, h_font);

	RECT r = {10, 10, 810, 70};
	FillRect(h_dc, &r, (HBRUSH)GetStockObject(DKGRAY_BRUSH));
	SetTextColor(h_dc, RGB(0, 100, 200));
	DrawText(h_dc, L"구구단", 3, &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

	//TextOut(h_dc, 10, 10, L"구구단", 3);
	SelectObject(h_dc, h_old_font);


	for (int step = 2; step <= 9; step++)
	{
		for (int i = 1; i <= 9; i++)
		{
			len = wsprintf(str, L"%d * %d = %d", step, i, step * i);
			TextOut(h_dc, 10 + (step - 2) * 100, 70 + i * 20, str, len);
		}
	}

	DeleteObject(h_font);

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
		break;
	case WM_COMMAND:
		break;
	case WM_PAINT:
	{
		//	OnPaint(hWnd);
		
		expFont(hWnd);
		/*
		RECT rect;
		HBRUSH hBrush;
		HFONT hFont;
		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(hWnd, &ps);


		//Logical units are device dependent pixels, so this will create a handle to a logical font that is 48 pixels in height.
		//The width, when set to 0, will cause the font mapper to choose the closest matching value.
		//The font face name will be Impact.
		hFont = CreateFont(48, 0, 0, 0, FW_DONTCARE, FALSE, TRUE, FALSE, DEFAULT_CHARSET, OUT_OUTLINE_PRECIS,
			CLIP_DEFAULT_PRECIS, CLEARTYPE_QUALITY, VARIABLE_PITCH, TEXT("Impact"));
		SelectObject(hdc, hFont);

		//Sets the coordinates for the rectangle in which the text is to be formatted.
		SetRect(&rect, 100, 100, 700, 200);
		SetTextColor(hdc, RGB(255, 0, 0));
		DrawText(hdc, TEXT("Drawing Text with Impact"), -1, &rect, DT_NOCLIP);


		//Logical units are device dependent pixels, so this will create a handle to a logical font that is 36 pixels in height.
		//The width, when set to 20, will cause the font mapper to choose a font which, in this case, is stretched.
		//The font face name will be Times New Roman.  This time nEscapement is at -300 tenths of a degree (-30 degrees)
		hFont = CreateFont(36, 20, -300, 0, FW_DONTCARE, FALSE, TRUE, FALSE, DEFAULT_CHARSET, OUT_OUTLINE_PRECIS,
			CLIP_DEFAULT_PRECIS, CLEARTYPE_QUALITY, VARIABLE_PITCH, TEXT("Times New Roman"));
		SelectObject(hdc, hFont);

		//Sets the coordinates for the rectangle in which the text is to be formatted.
		SetRect(&rect, 100, 200, 900, 800);
		SetTextColor(hdc, RGB(0, 128, 0));
		DrawText(hdc, TEXT("Drawing Text with Times New Roman"), -1, &rect, DT_NOCLIP);


		//Logical units are device dependent pixels, so this will create a handle to a logical font that is 36 pixels in height.
		//The width, when set to 10, will cause the font mapper to choose a font which, in this case, is compressed. 
		//The font face name will be Arial. This time nEscapement is at 250 tenths of a degree (25 degrees)
		hFont = CreateFont(36, 10, 250, 0, FW_DONTCARE, FALSE, TRUE, FALSE, DEFAULT_CHARSET, OUT_OUTLINE_PRECIS,
			CLIP_DEFAULT_PRECIS, ANTIALIASED_QUALITY, VARIABLE_PITCH, TEXT("Arial"));
		SelectObject(hdc, hFont);

		//Sets the coordinates for the rectangle in which the text is to be formatted.
		SetRect(&rect, 500, 200, 1400, 600);
		SetTextColor(hdc, RGB(0, 0, 255));
		DrawText(hdc, TEXT("Drawing Text with Arial"), -1, &rect, DT_NOCLIP);

		DeleteObject(hFont);

		EndPaint(hWnd, &ps);
		*/

	}
	break;
	case WM_LBUTTONDOWN:
	{
		
		int x = LOWORD(lParam);
		int y = HIWORD(lParam);
		//OnLButtonDown(hWnd, x, y);

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