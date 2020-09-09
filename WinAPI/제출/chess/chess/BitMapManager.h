#pragma once
#include "BitMap.h"

class BitMapManager
{
private:
	BitMap* m_pieces;
	BitMap* m_Board;
	static BitMapManager* m_hThis;
public:
	static BitMapManager* GetInstance()
	{
		if (m_hThis == NULL)
			m_hThis = new BitMapManager;
		return m_hThis;
	}
	BitMap* GetpieceImage(PIECE index)
	{
		return &m_pieces[index];
	}
	BitMap* GetBoard(int i)
	{
		return &m_Board[i];
	}
	void InitPieces(HWND hWnd, PLAYER player);
	void InitBoard(HWND hWnd);
	BitMapManager();
	~BitMapManager();
};

