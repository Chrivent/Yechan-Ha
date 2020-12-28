#pragma once

#include "Collider.h"

class Jar : public Object
{
private:
	int type;

public:
	Jar();

	void Flaming();
	Collider GetCollider();
	void Draw(HDC hdc);

	~Jar();
};