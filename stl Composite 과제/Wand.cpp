#include "Wand.h"

Wand::Wand()
{
}

void Wand::SkillEvent(int x, int y, Character* player, Character* enemy, int result)
{
	if (result == RESULT_WIN)
	{
		int damage = player->GetDamage();
		enemy->DecreaseHp(damage);
	}
	else if (result == RESULT_LOSE)
	{
		if (RandBool(3, 1))
			m_draw.TextMiddle(x, y, "방벽 발동! (데미지를 무효화)");
		else
			player->DecreaseHp(enemy->GetDamage());
	}
}

Wand::~Wand()
{
}
