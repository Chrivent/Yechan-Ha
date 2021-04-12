#include "Board.h"

Board::Board()
{
	width = 9;
	height = 9;

	for (int i = 0; i < WATER_MAX; i++)
		water[i] = NULL;
}

Part* Board::GetMainPowerSupply()
{
	for (int y = 0; y < height; y++)
	{
		for (int x = 0; x < width; x++)
		{
			if (slot[y][x] != NULL)
			{
				Part* part = slot[y][x]->GetPart();

				if (part != NULL && part->GetName() == "MainPowerSupply")
					return part;
			}
		}
	}
	return NULL;
}

void Board::ConveyElectric()
{
	for (int y = 0; y < height; y++)
	{
		for (int x = 0; x < width; x++)
		{
			if (slot[y][x] != NULL)
			{
				Part* part = slot[y][x]->GetPart();
				ConnectingWire* connectingWire = slot[y][x]->GetConnectingWire();

				if (part != NULL && connectingWire != NULL)
				{
					if (part->CheckElectric() == true && part->GetGate() == "Output")
					{
						if (connectingWire->CheckElectric() == false)
							connectingWire->IncreaseVoltage();
					}
					else if (part->CheckElectric() == false && part->GetGate() == "Input")
					{
						if (connectingWire->CheckElectric() == true)
							part->IncreaseVoltage();
					}
				}
			}
		}
	}
}

void Board::RemoveElectric()
{
	for (int y = 0; y < height; y++)
	{
		for (int x = 0; x < width; x++)
		{
			if (slot[y][x] != NULL)
			{
				Part* part = slot[y][x]->GetPart();
				ConnectingWire* connectingWire = slot[y][x]->GetConnectingWire();

				if (part != NULL)
					part->ResetVoltage();

				if (connectingWire != NULL)
					connectingWire->ResetVoltage();
			}
		}
	}
}

void Board::DetectElectric()
{
	for (int y = 0; y < height; y++)
	{
		for (int x = 0; x < width; x++)
		{
			if (slot[y][x] != NULL)
			{
				ConnectingWire* connectingWire = slot[y][x]->GetConnectingWire();

				if (connectingWire != NULL && connectingWire->CheckElectric() == true)
				{
					for (int direction = DIRECTION_U; direction < DIRECTION_COUNT; direction++)
					{
						int x2 = x, y2 = y;
						switch (direction)
						{
						case DIRECTION_U:
							y2 = y - 1;
							break;

						case DIRECTION_R:
							x2 = x + 1;
							break;

						case DIRECTION_D:
							y2 = y + 1;
							break;

						case DIRECTION_L:
							x2 = x - 1;
							break;

						default:
							break;
						}

						if (x2 >= 0 && x2 < width && y2 >= 0 && y2 < height)
						{
							ConnectingWire* connectingWire2 = slot[y2][x2]->GetConnectingWire();

							if (connectingWire2 != NULL)
							{
								int oppositeDirection = DIRECTION_U;
								if (direction <= DIRECTION_R)
									oppositeDirection = direction + DIRECTION_D;
								else
									oppositeDirection = direction - DIRECTION_D;

								if (connectingWire->CheckWireExist(direction) && connectingWire2->CheckWireExist(oppositeDirection))
									connectingWire2->IncreaseVoltage();
							}
						}
					}
				}
			}
		}
	}
}

void Board::ActivePart()
{
	for (int y = 0; y < height; y++)
	{
		for (int x = 0; x < width; x++)
		{
			if (slot[y][x] != NULL)
			{
				Part* part = slot[y][x]->GetPart();

				if (part != NULL)
				{
					string name = part->GetName();

					if (part->CheckElectric() == false && part->GetGate() == "Output")
					{
						if (name == "SolarPanel")
							ActiveSolarPanel(part);
						else if (name == "WaterTurbine")
						{

						}
					}
					else if (part->CheckElectric() == true && part->GetGate() == "Input")
					{
						if (name == "WaterDispenser")
							ActiveWaterDispenser(part);
					}
				}
			}
		}
	}
}

void Board::ActiveSolarPanel(Part* part)
{
	for (int y = 0; y < height; y++)
	{
		for (int x = 0; x < width; x++)
		{
			if (slot[y][x] != NULL)
			{
				Part* part2 = slot[y][x]->GetPart();

				if (part2 != NULL)
				{
					string name = part2->GetName();

					if (name == "LightBulb" && part2->CheckElectric() == true)
					{
						Position position1 = part->transform.position;
						Position position2 = part2->transform.position;

						if (position1.x == position2.x || position1.y == position2.y)
							part->IncreaseVoltage();
					}
				}
			}
		}
	}
}

void Board::ActiveWaterDispenser(Part* part)
{
	static int time;
	if (time == 1000)
	{
		for (int i = 0; i < WATER_MAX; i++)
		{
			if (water[i] == NULL)
			{
				water[i] = new Water;
				water[i]->transform = part->transform;
				break;
			}
		}
		time = 0;
	}
	else
		time++;

	for (int i = 0; i < WATER_MAX; i++)
	{
		if (water[i] != NULL)
		{
			int max = 0;
			if (slot[9][0] != NULL)
				max = slot[9][0]->transform.position.y;

			if (water[i]->transform.position.y > max)
			{
				delete water[i];
				water[i] = NULL;
			}
			else
				water[i]->transform.MoveDown();
		}
	}
}

void Board::ArrangementSlot()
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

				slot[y][x]->transform.position.x = x * slotWidth + offset;
				slot[y][x]->transform.position.y = y * slotHeight + offset;
			}
		}
	}
}

void Board::Draw(HDC hdc)
{
	DrawSlot(hdc);

	for (int i = 0; i < WATER_MAX; i++)
	{
		if (water[i] != NULL)
			water[i]->Draw(hdc);
	}
}

Board::~Board()
{

}