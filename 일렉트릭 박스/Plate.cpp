#include "Plate.h"

Plate::Plate()
{
	width = 0;
	height = 0;

	for (int y = 0; y < HEIGHT_MAX; y++)
	{
		for (int x = 0; x < WIDTH_MAX; x++)
			slot[y][x] = NULL;
	}
}

int Plate::GetWidth()
{
	return width;
}

int Plate::GetHeight()
{
	return height;
}

Slot* Plate::GetSlotOnMouse(LPARAM lParam)
{
	for (int y = 0; y < height; y++)
	{
		for (int x = 0; x < width; x++)
		{
			if (slot[y][x] != NULL && CheckPositionIsInTransform(slot[y][x]->transform, MousePosition(lParam)))
				return slot[y][x];
		}
	}
	return NULL;
}

Slot* Plate::GetSlotHoldedPart()
{
	for (int y = 0; y < height; y++)
	{
		for (int x = 0; x < width; x++)
		{
			if (slot[y][x] != NULL && slot[y][x]->GetHoldedPart() != NULL)
				return slot[y][x];
		}
	}
	return NULL;
}

Part* Plate::GetPartOnMouse(LPARAM lParam)
{
	for (int y = 0; y < height; y++)
	{
		for (int x = 0; x < width; x++)
		{
			if (slot[y][x] != NULL)
			{
				Part* part = slot[y][x]->GetPartOnMouse(lParam);

				if (part != NULL)
					return part;
			}
		}
	}
	return NULL;
}

Part* Plate::GetHoldedPart()
{
	for (int y = 0; y < height; y++)
	{
		for (int x = 0; x < width; x++)
		{
			if (slot[y][x] != NULL)
			{
				Part* part = slot[y][x]->GetHoldedPart();

				if (part != NULL)
					return part;
			}
		}
	}
	return NULL;
}

void Plate::CreatePart(string partName, int type, int x, int y, bool fixed)
{
	if (slot[y][x] != NULL)
	{
		if (partName == "ConnectingWire")
			slot[y][x]->CreateConnectingWire(type);
		else
			slot[y][x]->CreatePart(partName, type, fixed);
	}
}

void Plate::DeleteWholeSlot()
{
	for (int y = 0; y < HEIGHT_MAX; y++)
	{
		for (int x = 0; x < WIDTH_MAX; x++)
		{
			if (slot[y][x] != NULL)
			{
				delete slot[y][x];
				slot[y][x] = NULL;
			}
		}
	}
}

void Plate::DrawSlot(HDC hdc)
{
	for (int y = 0; y < height; y++)
	{
		for (int x = 0; x < width; x++)
		{
			if (slot[y][x] != NULL)
				slot[y][x]->Draw(hdc);
		}
	}
}

void Plate::DrawPart(HDC hdc)
{
	for (int y = 0; y < height; y++)
	{
		for (int x = 0; x < width; x++)
		{
			if (slot[y][x] != NULL)
				slot[y][x]->DrawPart(hdc);
		}
	}
}

Plate::~Plate()
{
	DeleteWholeSlot();
}