#pragma once

#include "Unit.h"

class Aircraft : public Unit
{
public:
	Aircraft();

	void SetPositionOrigin();
	bool CheckAntiWeapon(string type);
};

