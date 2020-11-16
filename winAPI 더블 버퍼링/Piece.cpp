#include "Piece.h"

Piece::Piece()
{
	transform.scale = { SCALE, SCALE };

	type = 0;
	selected = false;
	moved = false;
	promotioned = false;
}

void Piece::SetType(int type)
{
	this->type = type;
}

int Piece::GetType()
{
	return type;
}

bool Piece::CheckSelected()
{
	return selected;
}

void Piece::Select()
{
	selected = true;
}

void Piece::Unselect()
{
	selected = false;
}

void Piece::Moved()
{
	moved = true;
}

void Piece::Promotioned()
{
	promotioned = true;
}

bool Piece::CheckPromotioned()
{
	return promotioned;
}

void Piece::GetBaseTileIndex(Tile tile[8][8], int& y, int& x)
{
	for (y = 0; y < 8; y++)
	{
		for (x = 0; x < 8; x++)
		{
			if (tile[y][x].transform.position == transform.position)
				return;
		}
	}
}