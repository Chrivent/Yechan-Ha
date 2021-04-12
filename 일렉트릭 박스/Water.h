#pragma once

#include "mecro.h"

class Water : public Object
{
public:
	Water();

	void Draw(HDC hdc);

	~Water();
};