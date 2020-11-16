#pragma once

#include "Tile.h"

class Cursor : public Object
{
public:
	Cursor();

	void Draw(HDC hdc);
};