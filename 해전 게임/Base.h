#pragma once

#include "Unit.h"

class Base : public Unit
{
public:
	void SetPositionOrigin();
	bool CheckWeapon(string type);
	bool CheckAntiWeapon(string type);
	void MoveUnit();
	void DrawUnit(HDC hdc);
};