#include "exWin32SelectObject.h"

/*

Rectangle 

CopyRect		�� �簢���� ��ǥ�� �ٸ� �簢���� ���� �մϴ�.
EqualRect		���� �� �����̿� ������ �Ʒ� �������� ��ǥ�� �� �� �� ���� �� �� �簢���� ������ ���θ� Ȯ�� �մϴ�.
InflateRect		���� �� �簢���� �ʺ�� ���̸� �ø��ų� ���Դϴ�.
IntersectRect	�� �ҽ� �簢���� �������� ��� �� �� ���� �簢���� ��ǥ�� ��� �簢���� ��ġ �մϴ�.
IsRectEmpty		���� �� �簢���� ��� �ִ��� ���θ� Ȯ�� �մϴ�.
OffsetRect		���� �� �簢���� ���� �� ���������� �̵� �մϴ�.
PtInRect		���� �� ���� ���� �� �簢�� ���� �ִ��� ���θ� Ȯ�� �մϴ�.
SetRect			���� �� �簢���� ��ǥ�� ���� �մϴ�.
SetRectEmpty	��� ��ǥ�� 0���� ���� �� �� �簢���� ����ϴ�.
SubtractRect	�ٸ� �簢������ �簢�� �ϳ��� ���� ���� �� �簢���� ��ǥ�� Ȯ�� �մϴ�.
UnionRect		�� �簢���� �������� ����ϴ�.


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
			// �����ڵ� Ÿ�� ��
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

		// �׸��� �׸��� ���� ����� DC ��ȯ�Ѵ�.
		ReleaseDC(hWnd, h_dc);


#if 0

		HPEN h_pen;
		// pen�� �Ӽ��� ���ϱ� ���� ��Ī�� ����
		const char* p_style_string[6] = {"PS_SOLID","PS_DASH","PS_DOT","PS_DASHDOT","PS_DASHDOTDOT", "PS_NULL"};
		// �����ڵ� Ÿ�� ��
		// const wchar_t* p_style_string[6] = {L"PS_SOLID",L"PS_DASH",L"PS_DOT",L"PS_DASHDOT",L"PS_DASHDOTDOT", L"PS_NULL"};

		int pen_style[6] = {PS_SOLID,PS_DASH,PS_DOT,PS_DASHDOT,PS_DASHDOTDOT, PS_NULL};

		//������ ��� ����� ǥ�õ��� �ʰ� �ϴ� �ɼ�
		SetBkMode(h_dc, TRANSPARENT);
		//SetBkMode(h_dc, RGB(0, 255, 0));
		// ���� dc�� ������ �� �ڵ� ���� ��´�.
		HGDIOBJ h_old_pen = GetCurrentObject(h_dc, OBJ_PEN);


		for (int i = 0; i < 6; i++)
		{
			// �����ڵ� Ÿ�� ��
			//TextOut(h_dc, 10, 10 + i * 20, p_style_string[i], wcslen(p_style_string[i]));

			TextOutA(h_dc, 10, 10 + i * 20, p_style_string[i], strlen(p_style_string[i]));

			h_pen = CreatePen(pen_style[i], 1, RGB(0, 0, 255));

			SelectObject(h_dc, h_pen);

			MoveToEx(h_dc, 200, 15 + i * 20, NULL);
			LineTo(h_dc, 400, 15 + i * 20);

			DeleteObject(h_pen);

		}

		SelectObject(h_dc, h_old_pen);

		// �׸��� �׸��� ���� ����� DC ��ȯ�Ѵ�.
		ReleaseDC(hWnd, h_dc);


		/*
		HPEN h_red_pen = CreatePen(PS_SOLID, 3, RGB(255, 0, 0));
		HGDIOBJ h_old_pen = SelectObject(h_dc, h_red_pen);
		// (200,15), (400,15) ���� �����ϴ� ������ �׸���
		MoveToEx(h_dc, 200, 15, NULL);
		LineTo(h_dc, 400, 15);

		// ������ ����ϴ� �� ��ü ����
		SelectObject(h_dc, h_old_pen);
		// �ڽ��� ���� �� ��ü ����
		DeleteObject(h_red_pen);
		// �׸��� �׸��� ���� ����� DC ��ȯ�Ѵ�.
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