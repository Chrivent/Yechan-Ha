#include "Slot.h"

Slot::Slot()
{
	transform.scale = { 70, 70 };
	offset = 5;

	connectingWire = NULL;
	part = NULL;
}

Part* Slot::GetPart()
{
	return part;
}

Part* Slot::GetPartOnMouse(LPARAM lParam)
{
	if (part != NULL && part->CheckFixed() == false && part->CheckHolded() == false)
	{
		if (CheckPositionIsInTransform(part->transform, MousePosition(lParam)))
			return part;
		return NULL;
	}
	return NULL;
}

Part* Slot::GetHoldedPart()
{
	if (part != NULL && part->CheckHolded() == true)
		return part;
	return NULL;
}

ConnectingWire* Slot::GetConnectingWire()
{
	return connectingWire;
}

void Slot::CreateConnectingWire(int type)
{
	if (connectingWire == NULL)
	{
		connectingWire = new ConnectingWire(type);

		if (connectingWire != NULL)
			connectingWire->transform = transform;
	}
}

void Slot::CreatePart(string partName, int type, bool fixed)
{
	if (part == NULL)
	{
		if (partName == "MainPowerSupply")
			part = new MainPowerSupply;
		else if (partName == "Target")
			part = new Target;
		else if (partName == "LightBulb")
			part = new LightBulb;
		else if (partName == "SolarPanel")
			part = new SolarPanel;
		else if (partName == "WaterDispenser")
			part = new WaterDispenser;
		else if (partName == "WaterTurbine")
			part = new WaterTurbine;

		if (part != NULL)
		{
			part->transform = transform;
			part->SetFixed(fixed);
		}
	}
}

void Slot::NullPart()
{
	part = NULL;
}

void Slot::PutPart(Part* part)
{
	this->part = part;
}

void Slot::DeleteConnectingWire()
{
	if (connectingWire != NULL)
	{
		delete connectingWire;
		connectingWire = NULL;
	}
}

void Slot::DeletePart()
{
	if (part != NULL)
	{
		delete part;
		part = NULL;
	}
}

void Slot::Draw(HDC hdc)
{
	DrawRectangleCustom(hdc, transform, offset, SKYBLUE, BLUE);

	if (connectingWire != NULL)
		connectingWire->Draw(hdc);
}

void Slot::DrawPart(HDC hdc)
{
	if (part != NULL)
		part->Draw(hdc);
}

Slot::~Slot()
{
	DeleteConnectingWire();
	DeletePart();
}