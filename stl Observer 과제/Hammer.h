#pragma once

#include "Weapon.h"

class Hammer : public Weapon
{
public:
	Hammer();

	void SkillEvent(int x, int y, Character* player, Character* enemy, int result);

	~Hammer();
};

