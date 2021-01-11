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
	void Resurrection();
	void Idle();
	Collider GetCollider();
	Collider GetScoreCollider();
	int GetType();
	void Draw(HDC hdc);

	~Player();
};