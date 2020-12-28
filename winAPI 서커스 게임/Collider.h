#pragma once

#include "mecro.h"

class Collider : public Object
{
public:
	Collider();

	void Draw(HDC hdc);

	~Collider();
};