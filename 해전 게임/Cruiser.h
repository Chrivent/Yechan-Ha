#pragma once

#include "Ship.h"

class Cruiser : public Ship
{
public:
	Cruiser();

	bool CheckWeapon(string type);
	void DrawUnit(HDC hdc);
};