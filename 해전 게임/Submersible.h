#pragma once

#include "Unit.h"

class Submersible : public Unit
{
public:
	Submersible();

	void SetPositionOrigin();
	bool CheckAntiWeapon(string type);
	void MoveUnit();
};