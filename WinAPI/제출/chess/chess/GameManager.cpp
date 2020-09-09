#include "GameManager.h"

GameManager::GameManager()
{
	m_Board.left = board_start_width;
	m_Board.right = board_width;
	m_Board.top = board_start_height;
	m_Board.bottom = board_height;
}

void GameManager::InIt(HWND hWnd)
{
	BitMapManager::GetInstance()->InitBoard(hWnd);
	m_BoardBit[0] = BitMapManager::GetInstance()->GetBoard(0);
	m_BoardBit[1] = BitMapManager::GetInstance()->GetBoard(1);
}

void GameManager::Draw(HDC hdc)
{
	for (int i = 0; i < max; i++)
	{
		m_BoardBit[0]->Draw(hdc, board_start_width + (i * 125), board_start_height + (i * 125), 
			m_BoardBit[0]->GetSize().cx, m_BoardBit[0]->GetSize().cy);
		m_BoardBit[1]->Draw(hdc, board_start_width + (i * 125), board_start_height + (i * 125), 
			m_BoardBit[1]->GetSize().cx, m_BoardBit[1]->GetSize().cy);
	}
}

GameManager::~GameManager()
{
}
