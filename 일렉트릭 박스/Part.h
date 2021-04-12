#pragma once

#include "mecro.h"

class Part : public Object
{
protected:
	bool fixed;
	bool holded;
	string name;
	int voltage;
	string gate;

public:
	Part();

	void SetFixed(bool fixed);
	void SetHolded(bool holded);
	string GetName();
	string GetGate();
	bool CheckFixed();
	bool CheckHolded();
	bool CheckElectric();
	void ResetVoltage();

	virtual void IncreaseVoltage() = 0;

	virtual ~Part();
};