#pragma once

#include "Submersible.h"

class Submarine : public Submersible
{
public:
	Submarine();

	bool CheckWeapon(string type);
	void DrawUnit(HDC hdc);
};