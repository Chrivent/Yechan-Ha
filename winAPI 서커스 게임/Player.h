#pragma once

#include "Collider.h"

class Player : public Object
{
private:
	int type;

public:
	Player();

	void Running();
	void Jumping();
	void Dying();
	void Winning();
	void Idle();
	Collider GetCollider();
	int GetType();
	void Draw(HDC hdc);

	~Player();
};