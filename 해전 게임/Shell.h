#pragma once

#include "Unit.h"

class Shell : public Object
{
protected:
	COLORREF color;
	string type;
	int damage;
	Unit* target;
	bool breakaway;

public:
	Shell();

	void SetColor(COLORREF color);
	void SetTarget(Unit* target);
	COLORREF GetColor();
	string GetType();
	int GetDamage();
	Unit* GetTarget();
	void DeleteTarget();
	bool CheckBreakAway();

	virtual void Move() = 0;
};