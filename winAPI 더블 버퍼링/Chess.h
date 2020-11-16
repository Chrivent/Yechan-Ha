#pragma once

#include "Pawn.h"
#include "Knight.h"
#include "Bishop.h"
#include "Rook.h"
#include "Queen.h"
#include "King.h"

#include "Cursor.h"

class Chess
{
private:
	Tile tile[8][8];

	Piece* pawn[2][8];
	Piece* knight[2][2];
	Piece* bishop[2][2];
	Piece* rook[2][2];
	Piece* queen[2];
	Piece* king[2];

	int turn;

public:
	Cursor cursor;

	Chess();

	void CreatePiece();
	void ArrangementTile();
	void ArrangementPiece();
	Tile* GetTileByPosition(Position position);
	Piece* GetFriendlyPieceUnderMouse(LPARAM lParam);
	void ShowPattern(Piece* piece);
	void HidePattern();
	Piece* GetPieceSelected();
	void DeleteOnePiece(Piece* piece);
	void ChangeTurn();
	void Check();
	void Promotion(HWND hWnd);
	Tile* GetTileUnderMouse(LPARAM lParam);
	void SetCursorPosition(Position position);
	void Draw(HDC hdc);
	void DeletePiece();

	~Chess();
};
