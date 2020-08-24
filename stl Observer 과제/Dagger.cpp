#include "Dagger.h"

Dagger::Dagger()
{
}

void Dagger::SkillEvent(int x, int y, Character* player, Character* enemy, int result)
{
	if (result == RESULT_WIN)
	{
		int damage = player->GetDamage();
		if (RandBool(3, 1))
		{
			damage *= 2;
			m_draw.TextMiddle(x, y, "ȸ�� �ߵ�! (�������� �ι� ����) ������ : " + to_string(damage));
		}
		else
			m_draw.TextMiddle(x, y, "������ : " + to_string(damage));

		enemy->DecreaseHp(damage);
	}
	else if (result == RESULT_LOSE)
		player->DecreaseHp(enemy->GetDamage());
}

Dagger::~Dagger()
{
}
