#pragma once

#include "Weapon.h"

class Wand : public Weapon
{
public:
	Wand();

	void SkillEvent(int x, int y, Character* player, Character* enemy, int result);

	~Wand();
};

