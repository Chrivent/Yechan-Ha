#pragma once

#include "Ship.h"

class Frigate : public Ship
{
public:
	Frigate();

	bool CheckWeapon(string type);
	void DrawUnit(HDC hdc);
};