#pragma once

#include "Plate.h"
#include "Water.h"

#define WATER_MAX 10

class Board : public Plate
{
private:
	Water* water[WATER_MAX];

public:
	Board();

	Part* GetMainPowerSupply();
	void ConveyElectric();
	void RemoveElectric();
	void DetectElectric();
	void ActivePart();
	void ActiveSolarPanel(Part* part);
	void ActiveWaterDispenser(Part* part);
	void ArrangementSlot();
	void Draw(HDC hdc);

	~Board();
};