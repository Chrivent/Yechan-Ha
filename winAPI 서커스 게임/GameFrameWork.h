#pragma once

#include "Circus.h"

class GameFrameWork
{
private:
	HWND hWnd;

	DWORD m_dwLastTime;
	DWORD m_dwCurTime;
	float m_fDeltaTime;

	Circus circus;

	int ringMakeType;
	int jumpType;

public:
	GameFrameWork();

	void Init(HWND hWnd);
	void Release();
	void Update();
	void OperateInput();
	void Render();

	~GameFrameWork();
};