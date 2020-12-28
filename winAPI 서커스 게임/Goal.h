#pragma once

#include "Collider.h"

class Goal : public Object
{
public:
	Goal();

	Collider GetCollider();
	void Draw(HDC hdc);

	~Goal();
};