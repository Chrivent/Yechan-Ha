#include "Cursor.h"

Cursor::Cursor()
{
	transform.scale = { SCALE, SCALE };
}

void Cursor::Draw(HDC hdc)
{
	DrawBitmapTransparent(hdc, transform, TEXT("block03.bmp"));
}
