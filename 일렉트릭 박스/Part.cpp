#include "Part.h"

Part::Part()
{
	fixed = true;
	holded = false;
	name = "";
	voltage = 0;
	gate = "";
}

void Part::SetFixed(bool fixed)
{
	this->fixed = fixed;
}

void Part::SetHolded(bool holded)
{
	this->holded = holded;
}

string Part::GetName()
{
	return name;
}

string Part::GetGate()
{
	return gate;
}

bool Part::CheckFixed()
{
	return fixed;
}

bool Part::CheckHolded()
{
	return holded;
}

bool Part::CheckElectric()
{
	if (voltage >= 255)
		return true;
	return false;
}

void Part::ResetVoltage()
{
	voltage = 0;
}

Part::~Part()
{

}