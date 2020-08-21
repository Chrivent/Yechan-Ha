#include "Sword.h"

Sword::Sword()
{
}

void Sword::SkillEvent(int x, int y, Character* player, Character* enemy, int result)
{
	if (result == RESULT_WIN)
	{
		int damage = player->GetDamage();
		enemy->DecreaseHp(damage);
	}
	else if (result == RESULT_LOSE)
	{
		if (RandBool(6, 1))
		{
			m_draw.TextMiddle(x, y, "���� �ߵ�! (�������� �ݰ�) ������ : " + to_string(enemy->GetDamage()));
			enemy->DecreaseHp(enemy->GetDamage());
		}
		else
			player->DecreaseHp(enemy->GetDamage());
	}
}

Sword::~Sword()
{
}
