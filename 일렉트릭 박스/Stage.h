#pragma once

#include "Board.h"
#include "Inventory.h"

class Stage
{
private:
	int level;
	Board* board;
	Inventory* inventory;

public:
	Stage(int level);

	int GetLevel();
	Part* GetMainPowerSupplyUnderMouse(LPARAM lParam);
	void CreateBoard();
	void CreateInventory();
	void LoadPlateData();
	void HoldPart(LPARAM lParam);
	void MovePart(LPARAM lParam);
	void PutPart(LPARAM lParam);
	void ConveyElectric();
	void PowerOff();
	void DeleteBoard();
	void DeleteInventory();
	void Draw(HDC hdc);

	~Stage();
};