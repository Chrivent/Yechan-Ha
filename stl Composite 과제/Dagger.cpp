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
			m_draw.TextMiddle(x, y, "회심 발동! (데미지가 두배 증가) 데미지 : " + to_string(damage));
		}
		else
			m_draw.TextMiddle(x, y, "데미지 : " + to_string(damage));

		enemy->DecreaseHp(damage);
	}
	else if (result == RESULT_LOSE)
		player->DecreaseHp(enemy->GetDamage());
}

Dagger::~Dagger()
{
}
