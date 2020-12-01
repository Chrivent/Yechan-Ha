#pragma once

#include "Background.h"
#include "Player.h"
#include "Ring.h"

class Circus
{
private:
	Background background;
	Player player;

	Ring* ring[2];

	int runType;
	bool movingForward;
	bool movingBackward;
	bool jumping;
	int acceleration;
	int flameType;

public:
	Circus();

	void Draw(HDC hdc);
	void MoveForward();
	void MoveBackward();
	void Stop();
	void Jump();
	void Float();
	void Clear();
	void CreateRing();
	void MoveRing();
	void DeleteRing();

	~Circus();
};