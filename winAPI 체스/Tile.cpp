#include "Tile.h"
#include "Piece.h"

Tile::Tile()
{
	transform.scale = { SCALE, SCALE };

	type = 0;
	mode = MODE_DEFAULT;
	piece = NULL;
}

void Tile::SetType(int type)
{
	this->type = type;
}

void Tile::SetMode(MODE mode)
{
	this->mode = mode;
}

MODE Tile::GetMode()
{
	return mode;
}

void Tile::AppendPiece(Piece* piece)
{
	this->piece = piece;

	piece->transform.position = transform.position;
}

Piece* Tile::GetPiece()
{
	return piece;
}

void Tile::RemovePiece()
{
	piece = NULL;
}

void Tile::Draw(HDC hdc)
{
	switch (mode)
	{
	case MODE_DEFAULT:
		DrawBitmap(hdc, transform, (type == 0) ? TEXT("block01.bmp") : TEXT("block02.bmp"));
		break;

	case MODE_BASE:
		DrawBitmap(hdc, transform, TEXT("block04.bmp"));
		break;

	case MODE_ROUTE:
		DrawBitmap(hdc, transform, TEXT("block05.bmp"));
		DrawBitmapTransparent(hdc, transform, TEXT("block03.bmp"));
		break;

	case MODE_CHECK:
		DrawBitmap(hdc, transform, TEXT("block06.bmp"));
		break;

	default:
		break;
	}
}