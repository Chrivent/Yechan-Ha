#include "Stage.h"

Stage::Stage(int level)
{
	this->level = level;

	board = NULL;
	inventory = NULL;
}

int Stage::GetLevel()
{
	return level;
}

Part* Stage::GetMainPowerSupplyUnderMouse(LPARAM lParam)
{
	Part* mainPowerSupply;
	mainPowerSupply = board->GetMainPowerSupply();

	if (mainPowerSupply != NULL)
	{
		if (CheckPositionIsInTransform(mainPowerSupply->transform, MousePosition(lParam)))
			return mainPowerSupply;
	}
	return NULL;
}

void Stage::CreateBoard()
{
	if (board == NULL)
	{
		board = new Board;
		board->ArrangementSlot();
	}
}

void Stage::CreateInventory()
{
	if (inventory == NULL)
	{
		inventory = new Inventory;
		inventory->ArrangementSlot();
	}
}

void Stage::LoadPlateData()
{
	ifstream load;
	TCHAR fileName[512];
	wsprintf(fileName, TEXT("level_%d.txt"), level);
	load.open(fileName);
	if (load.is_open())
	{
		int plate = 1;
		while (!load.eof())
		{
			string str;
			load >> str;
			if (str == "Board")
			{
				plate = 1;
				continue;
			}
			else if (str == "Inventory")
			{
				plate = 2;
				continue;
			}

			string partName;
			int type;
			int x;
			int y;

			partName = str;
			load >> str;
			type = stoi(str);
			load >> str;
			x = stoi(str) - 1;
			load >> str;
			y = stoi(str) - 1;
			
			if (board != NULL && plate == 1)
				board->CreatePart(partName, type, x, y, true);
			else if (inventory != NULL && plate == 2)
				inventory->CreatePart(partName, type, x, y, false);
		}
	}
	load.close();
}

void Stage::HoldPart(LPARAM lParam)
{
	Part* boardPart = board->GetPartOnMouse(lParam);
	Part* inventoryPart = inventory->GetPartOnMouse(lParam);

	Part* part = NULL;
	if (boardPart != NULL)
		part = boardPart;
	else if (inventoryPart != NULL)
		part = inventoryPart;

	if (part != NULL)
	{
		if (board->GetMainPowerSupply()->CheckElectric() == false)
			part->SetHolded(true);
		else
		{
			//È­»ìÇ¥
		}
	}
}

void Stage::MovePart(LPARAM lParam)
{
	Part* boardPart = board->GetHoldedPart();
	Part* inventoryPart = inventory->GetHoldedPart();

	Part* part = NULL;
	if (boardPart != NULL)
		part = boardPart;
	else if (inventoryPart != NULL)
		part = inventoryPart;

	if (part != NULL)
	{
		Position partPosition;
		partPosition.x = MousePosition(lParam).x - part->transform.scale.width / 2;
		partPosition.y = MousePosition(lParam).y - part->transform.scale.height / 2;

		part->transform.position = partPosition;
	}
}

void Stage::PutPart(LPARAM lParam)
{
	Slot* boardSlotHoldedPart = board->GetSlotHoldedPart();
	Slot* inventorySlotHoldedPart = inventory->GetSlotHoldedPart();

	Slot* slotHoldedPart = NULL;
	if (boardSlotHoldedPart != NULL)
		slotHoldedPart = boardSlotHoldedPart;
	else if (inventorySlotHoldedPart != NULL)
		slotHoldedPart = inventorySlotHoldedPart;

	if (slotHoldedPart != NULL)
	{
		Slot* boardSlotOnMouse = board->GetSlotOnMouse(lParam);
		Slot* inventorySlotOnMouse = inventory->GetSlotOnMouse(lParam);

		Slot* slotOnMouse = NULL;
		if (boardSlotOnMouse != NULL)
			slotOnMouse = boardSlotOnMouse;
		else if (inventorySlotOnMouse != NULL)
			slotOnMouse = inventorySlotOnMouse;

		Part* tmp = NULL;
		tmp = slotHoldedPart->GetPart();
		slotHoldedPart->NullPart();

		if (slotOnMouse == NULL || slotOnMouse->GetPart() != NULL)
			slotOnMouse = slotHoldedPart;

		slotOnMouse->PutPart(tmp);

		tmp->SetHolded(false);
		tmp->transform = slotOnMouse->transform;
	}
}

void Stage::ConveyElectric()
{
	board->ConveyElectric();
	board->DetectElectric();
	board->ActivePart();
}

void Stage::PowerOff()
{
	board->RemoveElectric();
}

void Stage::DeleteBoard()
{
	if (board != NULL)
	{
		delete board;
		board = NULL;
	}
}

void Stage::DeleteInventory()
{
	if (inventory != NULL)
	{
		delete inventory;
		inventory = NULL;
	}
}

void Stage::Draw(HDC hdc)
{
	DrawRectangle(hdc, { { 0, 0 }, { 1280, 720 } }, BLUE);

	if (board != NULL)
		board->Draw(hdc);

	if (inventory != NULL)
		inventory->Draw(hdc);

	if (board != NULL)
		board->DrawPart(hdc);

	if (inventory != NULL)
		inventory->DrawPart(hdc);
}

Stage::~Stage()
{
	DeleteBoard();
	DeleteInventory();
}
