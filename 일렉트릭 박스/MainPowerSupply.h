#pragma once

#include "Part.h"

class MainPowerSupply : public Part
{
public:
	MainPowerSupply();

	void IncreaseVoltage();
	void Draw(HDC hdc);

	~MainPowerSupply();
};