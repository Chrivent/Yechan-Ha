#pragma once

#include "Collider.h"

class Ring : public Object
{
private:
	int type;

public:
	Ring();

	void Flaming();
	Collider GetCollider();
	void Draw(HDC hdc);
	void Draw2(HDC hdc);

	~Ring();
};