#pragma once

#include "Aircraft.h"

class TorpedoBomber : public Aircraft
{
private:
	string direction;

public:
	TorpedoBomber();

	bool CheckWeapon(string type);
	void DrawUnit(HDC hdc);
	void MoveUnit();
};