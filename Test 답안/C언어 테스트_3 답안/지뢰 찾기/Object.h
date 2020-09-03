#pragma once

#include "mecro.h"

class Object
{
protected:
	Position position;

public:
	void SetPosition(Position position);
	Position GetPosition();
};