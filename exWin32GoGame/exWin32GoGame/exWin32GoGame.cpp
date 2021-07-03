#include "exWin32GoGame.h"

/*


*/

//���� ���� ���� 19���� �ٵ����� ���� ���
#define X_COUNT 19
#define Y_COUNT 19

//ȭ���� ���ʿ��� �ٵ����� ���ʸ������ �Ÿ� (����)
#define START_X 50
//ȭ���� ���ʿ��� �ٵ����� ���ʸ������ �Ÿ� (����)
#define START_Y 50

//�� ������ ������ 26�̴�. �ٵ� ���� ���� ũ�⵵ �����ϴ�.
#define INTERVAL 26
//�ٵ� ���� �������� �� ������ ���ݰ� ������. 
#define HALF_INTERVAL   INTERVAL/2

// �ٵ��ǿ� ���� ���� ��  �ִ� ��ġ�� ���� ���ϰ� ����� �� �ֵ���
// ��ũ�� �Լ��� ����. x�� y�� 0 ~18 ���� ����ϸ�
// ���� ȭ����� ��ǥ�� �� �� �ִ�.
#define XPOS(x) (START_X + (x) * INTERVAL)
#define YPOS(y) (START_Y + (y) * INTERVAL)


// �ٵ��ǿ� ���� ������ �ִ��� ����ϱ� ���� ���� �迭�� �� �׸��� ���� 0�̸� ����
// ������ ���� �ʴٴ� ���̰� 1�̸� ������ ��, 2�̸� ��� ���� ������ �ִٴ� ��
unsigned char g_dol[Y_COUNT][X_COUNT];// = {1,2,2,1};
// ���� � ���� ���� �������� �����ϴ� ���� (0�̸� ������, 1�̸� ��� ���� ���� ����)
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

	for (int x = 0; x < X_COUNT; x++) //��������19���� ���� �׸��� 
		// (x,0) ���� (x, Y_COUNT-1) ���� �����ϴ� ���� �׸���.
	{
		MoveToEx(h_dc, XPOS(x), YPOS(0), NULL);
		LineTo(h_dc, XPOS(x), YPOS(Y_COUNT - 1));
	}

	for (int y = 0; y < Y_COUNT; y++)//��������19���� ���� �׸��� 
		// (0,y) ���� (X_COUNT-1, y) ���� �����ϴ� ���� �׸���.
	{
		MoveToEx(h_dc, XPOS(0), YPOS(y), NULL);
		LineTo(h_dc, XPOS(X_COUNT - 1), YPOS(y));
	}

	// �ٵ��� ��ü�� ������ �ִ� ����  �� ��ġ���� üũ�ϸ鼭 ���� ������ ������
	// ���� ������ ���� �׸���.
	for (int y = 0; y < Y_COUNT; y++)
	{
		for (int x = 0; x < X_COUNT; x++)
		{
			if (g_dol[y][x] > 0) // �ٵϵ��� ������ �ִ� ��� (1 ����, 2 ��)
			{
				// �������̸� ������, ���̸� ��� ����
				if (g_dol[y][x] == 1) SelectObject(h_dc, GetStockObject(BLACK_BRUSH));
				else SelectObject(h_dc, GetStockObject(WHITE_BRUSH));

				// �ٵϵ��� ������ ��ġ�� ����Ѵ�. (x,y)�� �߽������� �ϰ�
				// �������� HALF_INTERVAL�� ���� �׷��� ��ǥ�� ����
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
	// ���� Ŭ�� �� ũ�ν� ����Ʈ�� ���� ���� ���� ���
	if (a_x > (XPOS(0) - HALF_INTERVAL) && a_y > (YPOS(0) - HALF_INTERVAL)
		&& a_x < (XPOS(X_COUNT - 1) + HALF_INTERVAL)
		&& a_y < (YPOS(Y_COUNT - 1) + HALF_INTERVAL))
	{

		int x = (a_x - START_X+ HALF_INTERVAL) / INTERVAL;
		int y = (a_y - START_Y+ HALF_INTERVAL) / INTERVAL;
		
		if (g_dol[y][x] == 0)
			// ���� ���� ������ ���� ���� �� �ִ�.
			// g_step�� 0�̸� �������� ������ �����̰� 1�̸� ���� ������ �����̱�
			// ������ g_step�� 1�� ���ؼ� �ٵ��ǿ� ������ �� ������ �����ϸ�
			// ���� ������ 0, �������̸� 1, ���̸� 2�� �����
		{
			g_dol[y][x] = g_step + 1;
			//�������� �������� �򵹷� ���¸� �����ϰ�
			//���� �������� �������� ���¸� ����
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