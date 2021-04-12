#include "Inventory.h"

Inventory::Inventory()
{
	width = 3;
	height = 6;
}

void Inventory::ArrangementSlot()
{
	for (int y = 0; y < height; y++)
	{
		for (int x = 0; x < width; x++)
		{
			if (slot[y][x] == NULL)
			{
				slot[y][x] = new Slot;

				int slotWidth = slot[y][x]->transform.scale.width;
				int slotHeight = slot[y][x]->transform.scale.height;
				int offset = (720 - height * slotHeight) / 2;

				Board board;
				int heightOffset = (720 - board.GetHeight() * slotHeight) / 2;
				int widthOffset = heightOffset * 2 + (board.GetWidth() * slotWidth);

				slot[y][x]->transform.position.x = x * slotWidth + widthOffset;
				slot[y][x]->transform.position.y = y * slotHeight + heightOffset;
			}
		}
	}
}

void Inventory::Draw(HDC hdc)
{
	DrawSlot(hdc);
}

Inventory::~Inventory()
{

}