#pragma once

#include "Aircraft.h"

class Helicopter : public Aircraft
{
public:
	Helicopter();

	bool CheckWeapon(string type);
	void DrawUnit(HDC hdc);
	void MoveUnit();
};