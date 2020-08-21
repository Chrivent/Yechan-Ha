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
			m_draw.TextMiddle(x, y, "�溮 �ߵ�! (�������� ��ȿȭ)");
		else
			player->DecreaseHp(enemy->GetDamage());
	}
}

Wand::~Wand()
{
}
