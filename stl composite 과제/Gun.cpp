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
			m_draw.TextMiddle(x, y, "관통 소 발동! (데미지가 조금 증가) 데미지 : " + to_string(damage));
		}
		else if (RandBool(6, 1))
		{
			damage *= 2;
			m_draw.TextMiddle(x, y, "관통 대 발동! (데미지가 크게 증가) 데미지 : " + to_string(damage));
		}
		else
			m_draw.TextMiddle(x, y, "데미지 : " + to_string(damage));

		enemy->DecreaseHp(damage);
	}
	else if (result == RESULT_LOSE)
		player->DecreaseHp(enemy->GetDamage());
}

Gun::~Gun()
{
}
