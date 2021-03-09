#pragma once

#include "Corvette.h"
#include "Frigate.h"
#include "Submarine.h"
#include "TorpedoBomber.h"
#include "Helicopter.h"
#include "Destroyer.h"
#include "Cruiser.h"

class Button : public Object
{
private:
	Unit* unit;
	bool on;

public:
	Button(char unitID);

	int GetResource();
	void On();
	void Off();
	char GetUnitID();
	void Draw(HDC hdc);

	~Button();
};