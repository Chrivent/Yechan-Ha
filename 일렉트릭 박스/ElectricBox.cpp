#include "ElectricBox.h"

ElectricBox::ElectricBox()
{
	level = 1;
	powerClicked = false;

	stage = NULL;
}

void ElectricBox::CreateStage()
{
	if (stage == NULL)
	{
		stage = new Stage(level);
		stage->CreateBoard();
		stage->CreateInventory();
		stage->LoadPlateData();
	}
}

void ElectricBox::MouseButtonDownEvent(LPARAM lParam)
{
	if (stage != NULL)
	{
		stage->HoldPart(lParam);
		
		if (stage->GetMainPowerSupplyUnderMouse(lParam) != NULL)
			powerClicked = true;
	}
}

void ElectricBox::MouseMoveEvent(LPARAM lParam)
{
	if (stage != NULL)
	{
		stage->MovePart(lParam);
		
		if (stage->GetMainPowerSupplyUnderMouse(lParam) == NULL)
			powerClicked = false;
	}
}

void ElectricBox::MouseButtonUpEvent(LPARAM lParam)
{
	if (stage != NULL)
	{
		stage->PutPart(lParam);

		Part* mainPowerSupply = stage->GetMainPowerSupplyUnderMouse(lParam);
		if (powerClicked == true && mainPowerSupply != NULL)
		{
			if (mainPowerSupply->CheckElectric() == false)
				mainPowerSupply->IncreaseVoltage();
			else if (mainPowerSupply->CheckElectric() == true)
			{
				mainPowerSupply->ResetVoltage();

				if (stage != NULL)
					stage->PowerOff();
			}
		}
	}
}

void ElectricBox::ConveyElectric()
{
	if (stage != NULL)
		stage->ConveyElectric();
}

void ElectricBox::DeleteStage()
{
	if (stage != NULL)
	{
		delete stage;
		stage = NULL;
	}
}

void ElectricBox::Draw(HDC hdc)
{
	if (stage != NULL)
		stage->Draw(hdc);
}

ElectricBox::~ElectricBox()
{
	DeleteStage();
}