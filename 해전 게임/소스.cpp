#include "BlackNavyWar.h"

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
HINSTANCE g_hInst;
LPCTSTR lpszClass = TEXT("Game");

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

	HDC g_MemDC;
	HBITMAP g_hBitmap;
	HBITMAP g_hOld;

	static BlackNavyWar blackNavyWar;

	switch (iMessage)
	{
	case WM_CREATE:
		SetClientTransform(hWnd, { { 0, 0 }, { 1280, 720 } });

		SetTimer(hWnd, 0, 16, NULL);
		SetTimer(hWnd, 1, 33, NULL);
		SetTimer(hWnd, 2, 50, NULL);
		SetTimer(hWnd, 3, 100, NULL);
		SetTimer(hWnd, 4, 25, NULL);
		SetTimer(hWnd, 5, 25, NULL);
		SetTimer(hWnd, 6, 100, NULL);
		SetTimer(hWnd, 7, 100, NULL);

		SetTimer(hWnd, 100, 200, NULL);
		SetTimer(hWnd, 101, 30, NULL);
		SetTimer(hWnd, 200, 500, NULL);
		SetTimer(hWnd, 201, 30, NULL);
		SetTimer(hWnd, 300, 700, NULL);
		SetTimer(hWnd, 301, 30, NULL);
		SetTimer(hWnd, 400, 500, NULL);
		SetTimer(hWnd, 401, 30, NULL);
		SetTimer(hWnd, 500, 1500, NULL);
		SetTimer(hWnd, 501, 30, NULL);

		SetTimer(hWnd, 1000, 6000, NULL);
		SetTimer(hWnd, 2000, 1000, NULL);
		return 0;

	case WM_DESTROY:
		KillTimer(hWnd, 0);
		KillTimer(hWnd, 1);
		KillTimer(hWnd, 2);
		KillTimer(hWnd, 3);
		KillTimer(hWnd, 4);
		KillTimer(hWnd, 5);
		KillTimer(hWnd, 6);
		KillTimer(hWnd, 7);

		KillTimer(hWnd, 100);
		KillTimer(hWnd, 101);
		KillTimer(hWnd, 200);
		KillTimer(hWnd, 201);
		KillTimer(hWnd, 300);
		KillTimer(hWnd, 301);
		KillTimer(hWnd, 400);
		KillTimer(hWnd, 401);
		KillTimer(hWnd, 500);
		KillTimer(hWnd, 501);

		KillTimer(hWnd, 1000);
		KillTimer(hWnd, 2000);

		PostQuitMessage(0);
		return 0;

	case WM_TIMER:
		switch (wParam)
		{
		case 0:
			blackNavyWar.DetectUnitEvent();
			blackNavyWar.HitUnitEvent();
			blackNavyWar.ExhaustLifeEvent();
			blackNavyWar.BreakawayShellEvent();
			blackNavyWar.DestroyShellTargetEvent();
			blackNavyWar.EnoughResourceEvent();
			InvalidateRect(hWnd, NULL, FALSE);
			break;
		case 1:
			blackNavyWar.MoveUnit('1');
			break;
		case 2:
			blackNavyWar.MoveUnit('2');
			break;
		case 3:
			blackNavyWar.MoveUnit('3');
			break;
		case 4:
			blackNavyWar.MoveUnit('4');
			break;
		case 5:
			blackNavyWar.MoveUnit('5');
			break;
		case 6:
			blackNavyWar.MoveUnit('6');
			break;
		case 7:
			blackNavyWar.MoveUnit('7');
			break;

		case 100:
			blackNavyWar.Fire("MachineGun_a");
			blackNavyWar.Fire("MachineGun_s");
			break;
		case 101:
			blackNavyWar.MoveShell("MachineGun_a");
			blackNavyWar.MoveShell("MachineGun_s");
			break;

		case 200:
			blackNavyWar.Fire("Torpedo");
			break;
		case 201:
			blackNavyWar.MoveShell("Torpedo");
			break;

		case 300:
			blackNavyWar.Fire("DepthCharge");
			break;
		case 301:
			blackNavyWar.MoveShell("DepthCharge");
			break;

		case 400:
			blackNavyWar.Fire("Shrapnel");
			break;
		case 401:
			blackNavyWar.MoveShell("Shrapnel");
			break;

		case 500:
			blackNavyWar.Fire("Missile");
			break;
		case 501:
			blackNavyWar.MoveShell("Missile");
			break;

		case 1000:
			blackNavyWar.CreateEnemyUnit();
			break;

		case 2000:
			blackNavyWar.IncreaseResource();
			break;
		}
		return 0;

	case WM_LBUTTONDOWN:
		blackNavyWar.MouseClickEvent(lParam);
		return 0;

	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);

		g_MemDC = CreateCompatibleDC(hdc);
		g_hBitmap = CreateCompatibleBitmap(hdc, GetClientTransform(hWnd).scale.width, GetClientTransform(hWnd).scale.height);
		g_hOld = (HBITMAP)SelectObject(g_MemDC, g_hBitmap);

		blackNavyWar.Draw(g_MemDC);
		BitBlt(hdc, 0, 0, GetClientTransform(hWnd).scale.width, GetClientTransform(hWnd).scale.height, g_MemDC, 0, 0, SRCCOPY);

		SelectObject(g_MemDC, g_hOld);
		DeleteObject(g_hBitmap);
		DeleteDC(g_MemDC);

		EndPaint(hWnd, &ps);
		return 0;
	}

	return(DefWindowProc(hWnd, iMessage, wParam, lParam));
}