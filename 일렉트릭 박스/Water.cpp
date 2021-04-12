#include "Water.h"

Water::Water()
{

}

void Water::Draw(HDC hdc)
{
	DrawRectangle(hdc, transform, BLUE);
}

Water::~Water()
{

}