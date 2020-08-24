#pragma once

#include "mecro.h"

class Observer
{
public:
	Observer() {}

	virtual void Update() = 0;

	~Observer() {}
};