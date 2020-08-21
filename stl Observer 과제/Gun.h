#pragma once

#include "Weapon.h"

class Gun : public Weapon
{
public:
	Gun();

	void SkillEvent(int x, int y, Character* player, Character* enemy, int result);

	~Gun();
};

