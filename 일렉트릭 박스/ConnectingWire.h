#pragma once

#include "Part.h"

enum DIRECTION
{
	DIRECTION_U,
	DIRECTION_R,
	DIRECTION_D,
	DIRECTION_L,
	DIRECTION_COUNT
};

class ConnectingWire : public Part
{
private:
	bool wire[DIRECTION_COUNT];

public:
	ConnectingWire(int type);
	
	bool CheckWireExist(int direction);
	void IncreaseVoltage();
	void Draw(HDC hdc);

	~ConnectingWire();
};