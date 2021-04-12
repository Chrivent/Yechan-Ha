#pragma once

#include "Board.h"

class Inventory : public Plate
{
public:
	Inventory();

	void ArrangementSlot();
	void Draw(HDC hdc);

	~Inventory();
};