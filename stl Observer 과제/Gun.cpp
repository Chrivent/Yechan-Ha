#include "Gun.h"

Gun::Gun()
{
}

void Gun::SkillEvent(int x, int y, Character* player, Character* enemy, int result)
{
	if (result == RESULT_WIN)
	{
		int damage = player->GetDamage();
		if (RandBool(3, 1))
		{
			damage += (damage / 2);
			m_draw.TextMiddle(x, y, "���� �� �ߵ�! (�������� ���� ����) ������ : " + to_string(damage));
		}
		else if (RandBool(6, 1))
		{
			damage *= 2;
			m_draw.TextMiddle(x, y, "���� �� �ߵ�! (�������� ũ�� ����) ������ : " + to_string(damage));
		}
		else
			m_draw.TextMiddle(x, y, "������ : " + to_string(damage));

		enemy->DecreaseHp(damage);
	}
	else if (result == RESULT_LOSE)
		player->DecreaseHp(enemy->GetDamage());
}

Gun::~Gun()
{
}
