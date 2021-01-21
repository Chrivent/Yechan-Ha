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
	_CrtSetDbgFlag(_CRTDBG_LEAK_CHECK_DF | _CRTDBG_ALLOC_MEM_DF);

	HDC hdc;
	PAINTSTRUCT ps;
	SYSTEMTIME st;

	HDC g_MemDC;
	HBITMAP g_hBitmap;
	HBITMAP g_hOld;

	static Circus circus;
	static bool playerRunning;
	static bool playerWinning;
	static bool crowdCheering;
	static int playerDirection;
	static bool playerJumping;

	switch (iMessage)
	{
	case WM_CREATE:
		SetClientTransform(hWnd, { { 0, 0 }, { 1280, 800 } });
		SetTimer(hWnd, 1, 15, NULL);
		SetTimer(hWnd, 2, 60, NULL);
		SetTimer(hWnd, 3, 90, NULL);
		SetTimer(hWnd, 4, 210, NULL);
		SetTimer(hWnd, 5, 120, NULL);
		return 0;

	case WM_DESTROY:
		KillTimer(hWnd, 1);
		KillTimer(hWnd, 2);
		KillTimer(hWnd, 3);
		KillTimer(hWnd, 4);
		KillTimer(hWnd, 5);
		PostQuitMessage(0);
		return 0;

	case WM_TIMER:
		switch (wParam)
		{
		case 1:
			circus.PlayerGetScore();

			if (GetKeyState(VK_ESCAPE) & 0x8000)
				circus.Resurrection();

			if (circus.Resurrecting())
				circus.IncreaseTimerResurrection();
			else if (circus.CheckColliderIsIntersect())
				circus.Die();

			if (circus.Dying())
				circus.PlayerDying();
			else if (circus.CheckPlayerArriveGoal())
			{
				circus.DeleteRing();
				circus.MoveToGoalOrigin();

				playerWinning = true;
				crowdCheering = true;
			}
			else
			{
				circus.TimerCount();

				if ((GetKeyState(VK_LEFT) & 0x8000) && !playerJumping)
				{
					circus.MoveBackward();
					playerDirection = LEFT;
					playerRunning = true;
				}
				else if ((GetKeyState(VK_RIGHT) & 0x8000) && !playerJumping)
				{
					if (circus.CheckPlayerCanMove())
					{
						circus.MoveForward();
						playerDirection = RIGHT;
						playerRunning = true;
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

					if (!playerJumping)
						playerDirection = NULL;
				}

				if (GetKeyState(VK_SPACE) & 0x8000)
					circus.Jump();

				if (circus.Jumping())
				{
					circus.PlayerJumping();
					playerJumping = true;

					switch (playerDirection)
					{
					case LEFT:
						circus.MoveBackward();
						playerDirection = LEFT;
						break;
					case RIGHT:
						circus.MoveForward();
						playerDirection = RIGHT;
						break;
					default:
						circus.MoveForwardLittle();
						break;
					}
				}
				else
					playerJumping = false;

				circus.MoveRing();
			}

			InvalidateRect(hWnd, NULL, FALSE);
			break;

		case 2:
			circus.JarFlaming();
			break;

		case 3:
			circus.RingFlaming();

			if (crowdCheering)
			{
				circus.CrowdCheering();
				crowdCheering = false;
			}
			break;

		case 4:
			if (playerWinning)
			{
				circus.PlayerWinning();
				playerWinning = false;
			}
			break;

		case 5:
			if (playerRunning == true)
			{
				circus.PlayerRunning();
				playerRunning = false;
			}
			break;
		}
		return 0;
		
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);

		g_MemDC = CreateCompatibleDC(hdc);
		g_hBitmap = CreateCompatibleBitmap(hdc, GetClientTransform(hWnd).scale.width, GetClientTransform(hWnd).scale.height);
		g_hOld = (HBITMAP)SelectObject(g_MemDC, g_hBitmap);

		circus.Draw(g_MemDC);
		BitBlt(hdc, 0, 0, GetClientTransform(hWnd).scale.width, GetClientTransform(hWnd).scale.height, g_MemDC, 0, 0, SRCCOPY);

		EndPaint(hWnd, &ps);
		return 0;
	}

	return(DefWindowProc(hWnd, iMessage, wParam, lParam));
}