#pragma once

#include "Ship.h"

class Destroyer : public Ship
{
public:
	Destroyer();

	bool CheckWeapon(string type);
	void DrawUnit(HDC hdc);
};