#pragma once

#include "Slot.h"

#define WIDTH_MAX 20
#define HEIGHT_MAX 20

class Plate
{
protected:
	int width;
	int height;
	Slot* slot[WIDTH_MAX][HEIGHT_MAX];

public:
	Plate();

	int GetWidth();
	int GetHeight();
	Slot* GetSlotOnMouse(LPARAM lParam);
	Slot* GetSlotHoldedPart();
	Part* GetPartOnMouse(LPARAM lParam);
	Part* GetHoldedPart();
	void CreatePart(string partName, int type, int x, int y, bool fixed);
	void DeleteWholeSlot();
	void DrawSlot(HDC hdc);
	void DrawPart(HDC hdc);

	virtual void ArrangementSlot() = 0;

	~Plate();
};