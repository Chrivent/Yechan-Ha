#pragma once

#include "Weapon.h"

class Bow : public Weapon
{
public:
	Bow();

	void SkillEvent(int x, int y, Character* player, Character* enemy, int result);

	~Bow();
};

