#pragma once

#include "mecro.h"

#define SCALE 100

enum MODE
{
	MODE_DEFAULT,
	MODE_BASE,
	MODE_ROUTE,
	MODE_CHECK
};

class Piece;

class Tile : public Object
{
private:
	int type;
	MODE mode;
	Piece* piece;

public:
	Tile();

	void SetType(int type);
	void SetMode(MODE mode);
	MODE GetMode();
	void AppendPiece(Piece* piece);
	Piece* GetPiece();
	void RemovePiece();
	void Draw(HDC hdc);
};