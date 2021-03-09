#pragma once

#include "Unit.h"

class Ship : public Unit
{
public:
	Ship();

	void SetPositionOrigin();
	bool CheckAntiWeapon(string type);
	void MoveUnit();
};