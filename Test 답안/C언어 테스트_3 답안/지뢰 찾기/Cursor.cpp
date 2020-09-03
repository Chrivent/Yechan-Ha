#include "Cursor.h"

void Cursor::MoveLeft()
{
	position.x--;
}

void Cursor::MoveRight()
{
	position.x++;
}

void Cursor::MoveUp()
{
	position.y--;
}

void Cursor::MoveDown()
{
	position.y++;
}

void Cursor::DrawCursor()
{
	Draw draw;
	draw.Point(position.x, position.y, "¢Ã", HIGH_GREEN);
}