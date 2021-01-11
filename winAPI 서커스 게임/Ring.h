#pragma once

#include "Collider.h"

class Ring : public Object
{
protected:
	int type;

public:
	Ring();

	void Flaming();
	Collider GetCollider();
	virtual Collider* GetScoreCollider();
	void Draw(HDC hdc);
	virtual void Draw2(HDC hdc);

	virtual ~Ring();
};