#pragma once

#include "Piece.h"

class Pawn : public Piece
{
public:
	void Draw(HDC hdc);
	void SetPattern(Tile tile[8][8]);
};