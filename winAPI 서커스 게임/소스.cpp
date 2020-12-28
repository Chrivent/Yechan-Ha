#include "Circus.h"

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
HINSTANCE g_hInst;
LPCTSTR lpszClass = TEXT("Circus");

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdParam, int nCmdShow)
{
	HWND hWnd;
	MSG Message;
	WNDCLASS WndClass;
	g_hInst = hInstance;

	WndClass.cbClsExtra = 0;
	WndClass.cbWndExtra = 0;
	WndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	WndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	WndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	WndClass.hInstance = hInstance;
	WndClass.lpfnWndProc = WndProc;
	WndClass.lpszClassName = lpszClass;
	WndClass.lpszMenuName = NULL;
	WndClass.style = CS_HREDRAW | CS_VREDRAW;
	RegisterClass(&WndClass);

	hWnd = CreateWindow(lpszClass, lpszClass, WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, NULL, (HMENU)NULL, hInstance, NULL);
	ShowWindow(hWnd, nCmdShow);

	while (GetMessage(&Message, NULL, 0, 0))
	{
		TranslateMessage(&Message);
		DispatchMessage(&Message);
	}
	return (int)Message.wParam;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	HDC hdc;

	HDC g_MemDC;
	HBITMAP g_hBitmap;
	HBITMAP g_hOld;

	static Circus circus;
	static int jarFlaming;
	static int ringFlaming;
	static int playerRunning;
	static int playerWinning;
	static int crowdCheering;

	switch (iMessage)
	{
	case WM_CREATE:
		SetClientTransform(hWnd, { { 0, 0 }, { 1280, 720 } });
		return 0;

	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;

	case WM_PAINT:
		if (circus.CheckColliderIsIntersect())
			circus.Die();

		if (circus.Dying())
			circus.PlayerDying();
		else if (circus.CheckPlayerArriveGoal())
		{
			circus.DeleteRing();
			circus.MoveToGoalOrigin();

			if (playerWinning == 6)
			{
				circus.PlayerWinning();
				playerWinning = 0;
			}
			else
				playerWinning++;

			if (crowdCheering == 2)
			{
				circus.CrowdCheering();
				crowdCheering = 0;
			}
			else
				crowdCheering++;
		}
		else
		{
			if (GetKeyState(VK_LEFT) & 0x8000)
			{
				circus.MoveBackward();

				if (playerRunning == 3)
				{
					circus.PlayerRunning();
					playerRunning = 0;
				}
				else
					playerRunning++;
			}
			else if (GetKeyState(VK_RIGHT) & 0x8000)
			{
				if (circus.CheckPlayerCanMove())
				{
					circus.MoveForward();

					if (playerRunning == 3)
					{
						circus.PlayerRunning();
						playerRunning = 0;
					}
					else
						playerRunning++;
				}
				else
				{
					circus.ResetRingSpeed();
					circus.PlayerIdle();
				}
			}
			else
			{
				circus.ResetRingSpeed();
				circus.PlayerIdle();
			}

			if (GetKeyState(VK_SPACE) & 0x8000)
				circus.Jump();

			if (circus.Jumping())
				circus.PlayerJumping();
			circus.MoveRing();
		}

		if (jarFlaming == 1)
		{
			circus.JarFlaming();
			jarFlaming = 0;
		}
		else
			jarFlaming++;

		if (ringFlaming == 2)
		{
			circus.RingFlaming();
			ringFlaming = 0;
		}
		else
			ringFlaming++;

		hdc = GetDC(hWnd);

		g_MemDC = CreateCompatibleDC(hdc);
		g_hBitmap = CreateCompatibleBitmap(hdc, GetClientTransform(hWnd).scale.width, GetClientTransform(hWnd).scale.height);
		g_hOld = (HBITMAP)SelectObject(g_MemDC, g_hBitmap);

		circus.Draw(g_MemDC);
		BitBlt(hdc, 0, 0, GetClientTransform(hWnd).scale.width, GetClientTransform(hWnd).scale.height, g_MemDC, 0, 0, SRCCOPY);

		ReleaseDC(hWnd, hdc);
		return 0;
	}

	return(DefWindowProc(hWnd, iMessage, wParam, lParam));
}