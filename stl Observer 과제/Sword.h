#pragma once

#include "Weapon.h"

class Sword : public Weapon
{
public:
	Sword();

	void SkillEvent(int x, int y, Character* player, Character* enemy, int result);

	~Sword();
};

