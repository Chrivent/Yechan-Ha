#pragma once

#include "Weapon.h"

class Dagger : public Weapon
{
public:
	Dagger();

	void SkillEvent(int x, int y, Character* player, Character* enemy, int result);

	~Dagger();
};

