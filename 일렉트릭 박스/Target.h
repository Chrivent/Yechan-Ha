#pragma once

#include "Part.h"

class Target : public Part
{
public:
	Target();

	void IncreaseVoltage();
	void Draw(HDC hdc);

	~Target();
};