#pragma once

#include "MainPowerSupply.h"
#include "Target.h"
#include "LightBulb.h"
#include "SolarPanel.h"
#include "WaterDispenser.h"
#include "WaterTurbine.h"

#include "ConnectingWire.h"

class Slot : public Object
{
private:
	int offset;
	ConnectingWire* connectingWire;
	Part* part;

public:
	Slot();

	Part* GetPart();
	Part* GetPartOnMouse(LPARAM lParam);
	Part* GetHoldedPart();
	ConnectingWire* GetConnectingWire();
	void CreateConnectingWire(int type);
	void CreatePart(string partName, int type, bool fixed);
	void NullPart();
	void PutPart(Part* part);
	void DeleteConnectingWire();
	void DeletePart();
	void Draw(HDC hdc);
	void DrawPart(HDC hdc);

	~Slot();
};