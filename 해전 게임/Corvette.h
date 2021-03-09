#pragma once

#include "Ship.h"

class Corvette : public Ship
{
public:
	Corvette();

	bool CheckWeapon(string type);
	void DrawUnit(HDC hdc);
};