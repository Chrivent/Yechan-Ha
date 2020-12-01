#include "GameFrameWork.h"

GameFrameWork::GameFrameWork()
{
	_CrtSetDbgFlag(_CRTDBG_LEAK_CHECK_DF | _CRTDBG_ALLOC_MEM_DF);
}

void GameFrameWork::Init(HWND hWnd)
{
	this->hWnd = hWnd;

	Transform clientTransform;

	clientTransform.position = { 0, 0 };
	clientTransform.scale = { 1280, 720 };

	SetClientTransform(hWnd, clientTransform);

	ringMakeType = 0;
	jumpType = 0;
}

void GameFrameWork::Release()
{

}

void GameFrameWork::Update()
{
	m_dwCurTime = GetTickCount();
	m_fDeltaTime = (m_dwCurTime - m_dwLastTime) / 1000.0f;
	m_dwLastTime = m_dwCurTime;

	if (ringMakeType == 99)
	{
		circus.CreateRing();
		ringMakeType = 0;
	}
	else
		ringMakeType++;

	circus.MoveRing();

	if (jumpType == 2) 
	{
		circus.Float();
		jumpType = 0;
	}
	else
		jumpType++;

	OperateInput();

	Render();
}

void GameFrameWork::OperateInput()
{
	if (GetKeyState(VK_LEFT) & 0x8000)
		circus.MoveBackward();
	else if (GetKeyState(VK_RIGHT) & 0x8000)
		circus.MoveForward();
	else
		circus.Stop();

	if (GetKeyState(VK_SPACE) & 0x8000)
		circus.Jump();
}

void GameFrameWork::Render()
{
	HDC hdc = GetDC(hWnd);

	HDC g_MemDC = CreateCompatibleDC(hdc);
	HBITMAP g_hBitmap = CreateCompatibleBitmap(hdc, GetClientTransform(hWnd).scale.width, GetClientTransform(hWnd).scale.height);
	HBITMAP g_hOld = (HBITMAP)SelectObject(g_MemDC, g_hBitmap);

	circus.Draw(g_MemDC);
	BitBlt(hdc, 0, 0, GetClientTransform(hWnd).scale.width, GetClientTransform(hWnd).scale.height, g_MemDC, 0, 0, SRCCOPY);

	ReleaseDC(hWnd, hdc);
}

GameFrameWork::~GameFrameWork()
{

}