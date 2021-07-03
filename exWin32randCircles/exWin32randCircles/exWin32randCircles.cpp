#include "exWin32randCircles.h"
#include "time.h"
/*


*/

#define MAX_COUNT 100

struct Circle
{
	int x;
	int y;
	int r;
	COLORREF color;
};

Circle g_pos[MAX_COUNT];

RECT g_rect;

void MakeCircleData(Circle* ap_data, RECT* ap_rect)
{
	ap_data->x = rand() % ap_rect->right;
	ap_data->y = rand() % ap_rect->bottom;
	ap_data->r = rand() % 50 + 10;
	ap_data->color = RGB(rand() % 256, rand() % 256, rand() % 256);
}

void DrawEllipse(HDC ah_dc)
{
	Circle* p = g_pos;
	HBRUSH h_brush;
	HGDIOBJ h_old_brush = GetCurrentObject(ah_dc, OBJ_BRUSH);
	HGDIOBJ h_old_pen = SelectObject(ah_dc, GetStockObject(NULL_PEN));

	for (int i = 0; i < MAX_COUNT; i++)
	{
		h_brush = CreateSolidBrush(p->color);
		SelectObject(ah_dc, h_brush);
		Ellipse(ah_dc, p->x - p->r, p->y - p->r,
			p->x + p->r, p->y + p->r);

		p++;
		DeleteObject(h_brush);
	}
	SelectObject(ah_dc, h_old_pen);
	SelectObject(ah_dc, h_old_brush);
}

void OnPaint(HWND ah_wnd)
{
	PAINTSTRUCT ps;
	HDC h_dc = BeginPaint(ah_wnd, &ps);
	
	DrawEllipse(h_dc);

#if 0  // DrawEllipse로 대체 됨

	Circle* p = g_pos;
	HBRUSH h_brush;
	HGDIOBJ h_old_brush = GetCurrentObject(h_dc, OBJ_BRUSH);

	for (int i = 0; i < MAX_COUNT; i++)
	{
		h_brush = CreateSolidBrush(p->color);
		SelectObject(h_dc, h_brush);
		Ellipse(h_dc, p->x - p->r, p->y - p->r,
			p->x + p->r, p->y + p->r);
		p++;
		/*
		Ellipse(h_dc,g_pos[i].x - g_pos[i].r,g_pos[i].y - g_pos[i].r,
				g_pos[i].x + g_pos[i].r,g_pos[i].y + g_pos[i].r

		*/
		DeleteObject(h_brush);
	}
	SelectObject(h_dc, h_old_brush);
#endif // 0  // DrawEllipse로 대체 됨

	
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
		srand((UINT)time(NULL));

		GetClientRect(hWnd, &g_rect);
		for (int i = 0; i < MAX_COUNT; i++)
		{
			MakeCircleData(g_pos + i, &g_rect);
		}
#if 0 //  개선
		RECT r;
		GetClientRect(hWnd, &r);
		for (int i = 0; i < MAX_COUNT; i++)
		{
			MakeCircleData(g_pos + i, &r);  //MakeCircleData(&g_pos[i], &r)
			/*
			g_pos[i].x = rand() % r.right;
			g_pos[i].y = rand() % r.bottom;
			g_pos[i].r = rand() % 50 + 10;
			g_pos[i].color = RGB(rand() % 256, rand() % 256, rand() % 256);
			*/
		}
#endif // 0 //  개선


		SetTimer(hWnd, 1, 50, NULL);

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
	case WM_SIZE:
	{
		GetClientRect(hWnd, &g_rect);
	}
	break;
	case WM_TIMER:
	{
		
		if (wParam == 1)
		{

			for (int i = 0; i < MAX_COUNT; i++)
			{
				g_pos[i].r--;
				if (g_pos[i].r <= 1)
				{
					MakeCircleData(g_pos + i, &g_rect);
				}

			}
#if 0
			RECT r;
			GetClientRect(hWnd, &r);
			for (int i = 0; i < MAX_COUNT; i++)
			{
				g_pos[i].r--;
				if (g_pos[i].r <= 1)
				{
					MakeCircleData(g_pos + i, &r);
					/*
					g_pos[i].x = rand() % r.right;
					g_pos[i].y = rand() % r.bottom;
					g_pos[i].r = rand() % 50 + 10;
					g_pos[i].color = RGB(rand() % 256, rand() % 256, rand() % 256);
					*/
				}

			}
#endif // 0

		}
		InvalidateRect(hWnd, NULL, TRUE);
		

	}
	break;
	case WM_CLOSE:
		break;
	case WM_DESTROY:

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