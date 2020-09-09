#include "BitMapManager.h"

BitMapManager* BitMapManager::m_hThis = NULL;

BitMapManager::BitMapManager()
{
	m_pieces = new BitMap[max];
	m_Board = new BitMap[2];
}

void BitMapManager::InitPieces(HWND hWnd, PLAYER player)
{
	TCHAR buf[256];
	HDC hdc = GetDC(hWnd);
	if (player == PLAYER_BLACK)
	{
		for (int i = 0; i < max; i++)
		{
			wsprintf(buf, L"block_b_0%d.bmp", i);
			m_pieces[i].Init(hdc, buf);
		}
	}
	else
	{
		for (int i = 0; i < max; i++)
		{
			wsprintf(buf, L"block_w_0%d.bmp", i);
			m_pieces[i].Init(hdc, buf);
		}
	}

	ReleaseDC(hWnd, hdc);
}

void BitMapManager::InitBoard(HWND hWnd)
{
	HDC hdc = GetDC(hWnd);
	
	m_Board[0].Init(hdc, L"block01.bmp");
	m_Board[1].Init(hdc, L"block02.bmp");
	
	ReleaseDC(hWnd, hdc);
}

BitMapManager::~BitMapManager()
{
	delete[] m_pieces;
	delete[] m_Board;
}
