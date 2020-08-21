#pragma once

#include"Observer.h"

class Subject
{
public:
	Subject() {}

	virtual void NotifyObserver() = 0;

	~Subject() {}
};