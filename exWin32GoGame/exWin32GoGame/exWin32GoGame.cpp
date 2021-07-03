#include "exWin32GoGame.h"

/*


*/

//가로 세로 줄이 19개인 바둑판을 만들어서 사용
#define X_COUNT 19
#define Y_COUNT 19

//화면의 왼쪽에서 바둑판의 왼쪽면까지의 거리 (여백)
#define START_X 50
//화면의 위쪽에서 바둑판의 위쪽면까지의 거리 (여백)
#define START_Y 50

//줄 사이의 간격이 26이다. 바둑 돌의 지름 크기도 동일하다.
#define INTERVAL 26
//바독 돌의 반지름은 줄 간격의 절반과 동일핟. 
#define HALF_INTERVAL   INTERVAL/2

// 바둑판에 돌이 놓일 수  있는 위치를 좀더 편하게 계산할 수 있도록
// 매크로 함수로 만듬. x와 y에 0 ~18 값을 사용하면
// 실제 화면상의 좌표로 알 수 있다.
#define XPOS(x) (START_X + (x) * INTERVAL)
#define YPOS(y) (START_Y + (y) * INTERVAL)


// 바둑판에 돌이 놓여져 있는지 기억하기 위한 변수 배열의 각 항목의 값이 0이면 돌이
// 놓여져 있지 않다는 뜻이고 1이면 검은색 돌, 2이면 흰색 돌이 놓어져 있다는 뜻
unsigned char g_dol[Y_COUNT][X_COUNT];// = {1,2,2,1};
// 현재 어떤 돌을 놓을 것인지를 결정하는 변수 (0이면 검은색, 1이면 흰색 돌을 놓을 순서)
unsigned char g_step;




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

	for (int x = 0; x < X_COUNT; x++) //수직으로19개의 선을 그린다 
		// (x,0) 점과 (x, Y_COUNT-1) 점을 연결하는 선을 그린다.
	{
		MoveToEx(h_dc, XPOS(x), YPOS(0), NULL);
		LineTo(h_dc, XPOS(x), YPOS(Y_COUNT - 1));
	}

	for (int y = 0; y < Y_COUNT; y++)//수평으로19개의 선을 그린다 
		// (0,y) 점과 (X_COUNT-1, y) 점을 연결하는 선을 그린다.
	{
		MoveToEx(h_dc, XPOS(0), YPOS(y), NULL);
		LineTo(h_dc, XPOS(X_COUNT - 1), YPOS(y));
	}

	// 바둑판 전체에 놓여져 있는 돌을  각 위치별로 체크하면서 돌이 놓여져 있으면
	// 돌의 종류에 따라 그린다.
	for (int y = 0; y < Y_COUNT; y++)
	{
		for (int x = 0; x < X_COUNT; x++)
		{
			if (g_dol[y][x] > 0) // 바둑돌이 놓여져 있는 경우 (1 검은, 2 흰)
			{
				// 검은돌이면 검은색, 흰돌이면 흰색 설정
				if (g_dol[y][x] == 1) SelectObject(h_dc, GetStockObject(BLACK_BRUSH));
				else SelectObject(h_dc, GetStockObject(WHITE_BRUSH));

				// 바둑돌이 놓여질 위치를 계산한다. (x,y)를 중심점으로 하고
				// 반지름이 HALF_INTERVAL인 원이 그려질 좌표를 구성
				Ellipse(h_dc, XPOS(x) - HALF_INTERVAL, YPOS(y) - HALF_INTERVAL,
					XPOS(x) + HALF_INTERVAL, YPOS(y) + HALF_INTERVAL);

			}
		}
	}

	EndPaint(ah_wnd, &ps);

}

void OnLButtonDown(HWND a_hWnd, int a_x, int a_y)
{
	HDC h_dc = GetDC(a_hWnd);
	// 왼쪽 클릭 시 크로스 포인트에 돌을 놓기 위한 계산
	if (a_x > (XPOS(0) - HALF_INTERVAL) && a_y > (YPOS(0) - HALF_INTERVAL)
		&& a_x < (XPOS(X_COUNT - 1) + HALF_INTERVAL)
		&& a_y < (YPOS(Y_COUNT - 1) + HALF_INTERVAL))
	{

		int x = (a_x - START_X+ HALF_INTERVAL) / INTERVAL;
		int y = (a_y - START_Y+ HALF_INTERVAL) / INTERVAL;
		
		if (g_dol[y][x] == 0)
			// 돌이 없는 곳에만 돌을 놓을 수 있다.
			// g_step이 0이면 검은돌이 놓여질 순서이고 1이면 흰돌이 놓여질 순서이기
			// 때문에 g_step에 1을 더해서 바둑판에 놓여진 돌 정보를 구성하면
			// 돌이 없으면 0, 검은돌이면 1, 흰돌이면 2가 저장됨
		{
			g_dol[y][x] = g_step + 1;
			//검은돌을 놓았으면 흰돌로 상태를 변경하고
			//흰돌을 놓았으면 검은돌로 상태를 변경
			g_step = !(g_step);
			InvalidateRect(a_hWnd, NULL, TRUE);
		}
		/*
		x = x * INTERVAL + START_X;
		y = y * INTERVAL + START_Y;

		Ellipse(h_dc, x - HALF_INTERVAL, y - HALF_INTERVAL, x + HALF_INTERVAL, y + HALF_INTERVAL);
		*/
	}

	ReleaseDC(a_hWnd, h_dc);
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