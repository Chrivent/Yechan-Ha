#pragma once
#include "Player.h"

class GameManager
{
private:
	RECT m_Board;
	BitMap* m_BoardBit[2];
public:
	void InIt(HWND);
	void Draw(HDC hdc);
	GameManager();
	~GameManager();
};

