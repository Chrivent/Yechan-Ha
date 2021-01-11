#pragma once

#include "Ring.h"

class ScoreRing : public Ring
{
private:
	Collider* scoreCollider;

public:
	ScoreRing();

	Collider* GetScoreCollider();
	void Draw(HDC hdc);
	void Draw2(HDC hdc);

	~ScoreRing();
};