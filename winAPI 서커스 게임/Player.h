#pragma once

#include "background.h"

class Player : public Object
{
private:
	int type;

public:
	Player();

	void Running();
	void Jumping();
	void Idle();
	void Draw(HDC hdc);

	~Player();
};