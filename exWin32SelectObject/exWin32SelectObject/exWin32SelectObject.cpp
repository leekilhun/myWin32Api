#include "exWin32SelectObject.h"

/*

Rectangle 

CopyRect		한 사각형의 좌표를 다른 사각형에 복사 합니다.
EqualRect		왼쪽 위 모퉁이와 오른쪽 아래 모퉁이의 좌표를 비교 하 여 지정 된 두 사각형이 같은지 여부를 확인 합니다.
InflateRect		지정 된 사각형의 너비와 높이를 늘리거나 줄입니다.
IntersectRect	두 소스 사각형의 교집합을 계산 하 고 교차 사각형의 좌표를 대상 사각형에 배치 합니다.
IsRectEmpty		지정 된 사각형이 비어 있는지 여부를 확인 합니다.
OffsetRect		지정 된 사각형을 지정 된 오프셋으로 이동 합니다.
PtInRect		지정 된 점이 지정 된 사각형 내에 있는지 여부를 확인 합니다.
SetRect			지정 된 사각형의 좌표를 설정 합니다.
SetRectEmpty	모든 좌표가 0으로 설정 된 빈 사각형을 만듭니다.
SubtractRect	다른 사각형에서 사각형 하나를 빼서 형성 된 사각형의 좌표를 확인 합니다.
UnionRect		두 사각형의 합집합을 만듭니다.


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
	switch (Msg)
	{
	case WM_CREATE:
		break;
	case WM_COMMAND:
		break;
	case WM_PAINT:
		break;
	case WM_LBUTTONDOWN:
	{
		HDC h_dc = GetDC(hWnd);

		HBRUSH h_brush;
		const char* p_style_string[6] = {"HS_BDIAGONAL","HS_CROSS","HS_DIAGCROSS","HS_FDIAGONAL","HS_HORIZONTAL", "HS_VERTICAL"};
		int brush_style[6] = {HS_BDIAGONAL,HS_CROSS,HS_DIAGCROSS,HS_FDIAGONAL,HS_HORIZONTAL, HS_VERTICAL};
		
		SetBkMode(h_dc, TRANSPARENT);

		HGDIOBJ h_old_brush = GetCurrentObject(h_dc, OBJ_BRUSH);

		RECT r;

		for (int i = 0; i < 6; i++)
		{
			// 유니코드 타입 시
			//TextOut(h_dc, 10, 10 + i * 20, p_style_string[i], wcslen(p_style_string[i]));

			TextOutA(h_dc, 10, 10 + i * 30, p_style_string[i], strlen(p_style_string[i]));

			h_brush= CreateHatchBrush(brush_style[i], RGB(0, 0, 255));

			//SelectObject(h_dc, h_brush);

			SetRect(&r, 200, 5 + i * 30, 400, 30 + i * 30);
			FillRect(h_dc, &r, h_brush);

			//Rectangle(h_dc, 200, 5 + i * 30, 400, 30 + 1 * 30);
			 

			DeleteObject(h_brush);

		}

		SelectObject(h_dc, h_old_brush);

		// 그림을 그리기 위해 얻었던 DC 반환한다.
		ReleaseDC(hWnd, h_dc);


#if 0

		HPEN h_pen;
		// pen의 속성을 비교하기 위해 명칭을 지정
		const char* p_style_string[6] = {"PS_SOLID","PS_DASH","PS_DOT","PS_DASHDOT","PS_DASHDOTDOT", "PS_NULL"};
		// 유니코드 타입 시
		// const wchar_t* p_style_string[6] = {L"PS_SOLID",L"PS_DASH",L"PS_DOT",L"PS_DASHDOT",L"PS_DASHDOTDOT", L"PS_NULL"};

		int pen_style[6] = {PS_SOLID,PS_DASH,PS_DOT,PS_DASHDOT,PS_DASHDOTDOT, PS_NULL};

		//점선의 경우 배경이 표시되지 않게 하는 옵션
		SetBkMode(h_dc, TRANSPARENT);
		//SetBkMode(h_dc, RGB(0, 255, 0));
		// 현재 dc에 설정된 팬 핸들 값을 얻는다.
		HGDIOBJ h_old_pen = GetCurrentObject(h_dc, OBJ_PEN);


		for (int i = 0; i < 6; i++)
		{
			// 유니코드 타입 시
			//TextOut(h_dc, 10, 10 + i * 20, p_style_string[i], wcslen(p_style_string[i]));

			TextOutA(h_dc, 10, 10 + i * 20, p_style_string[i], strlen(p_style_string[i]));

			h_pen = CreatePen(pen_style[i], 1, RGB(0, 0, 255));

			SelectObject(h_dc, h_pen);

			MoveToEx(h_dc, 200, 15 + i * 20, NULL);
			LineTo(h_dc, 400, 15 + i * 20);

			DeleteObject(h_pen);

		}

		SelectObject(h_dc, h_old_pen);

		// 그림을 그리기 위해 얻었던 DC 반환한다.
		ReleaseDC(hWnd, h_dc);


		/*
		HPEN h_red_pen = CreatePen(PS_SOLID, 3, RGB(255, 0, 0));
		HGDIOBJ h_old_pen = SelectObject(h_dc, h_red_pen);
		// (200,15), (400,15) 점을 연결하는 직선을 그린다
		MoveToEx(h_dc, 200, 15, NULL);
		LineTo(h_dc, 400, 15);

		// 기존에 사용하던 펜 객체 복구
		SelectObject(h_dc, h_old_pen);
		// 자신이 만든 펜 객체 제거
		DeleteObject(h_red_pen);
		// 그림을 그리기 위해 얻었던 DC 반환한다.
		ReleaseDC(hWnd, h_dc);
		*/
		/*
		HBRUSH h_brush = CreateSolidBrush(RGB(0, 0, 255));

		HGDIOBJ h_old_brush = SelectObject(h_dc, h_brush);

		Rectangle(h_dc, 50, 50, 100, 100);

		SelectObject(h_dc, h_old_brush);
		Rectangle(h_dc, 250, 50, 300, 100);

		ReleaseDC(hWnd, h_dc);
		DeleteObject(h_brush);
		*/
#endif // 0

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

	wnd.lpfnWndProc = WindProcedure;
	wnd.hInstance = hInst;
	wnd.hCursor = LoadCursor(hInst, IDC_ARROW);
	wnd.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wnd.lpszClassName = L"sample";
	wnd.hIcon = LoadIcon(hInst, IDI_APPLICATION);
	wnd.style = CS_HREDRAW | CS_VREDRAW;

	Gdiplus::GdiplusStartup(&token, &input, NULL);


	if (!RegisterClassW(&wnd)) return -1;
	if (!CreateWindowW(L"sample", L"GDI+", WS_OVERLAPPEDWINDOW | WS_VISIBLE,
		0, 0, 860, 780, 0, 0, 0, 0)) return -1;

	//while(PeekMessage(&msg, 0, 0, 0,PM_REMOVE))

	while (GetMessageW(&msg, 0, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessageW(&msg);

	}

	return 0;



}