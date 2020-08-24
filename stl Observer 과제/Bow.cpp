#include "Bow.h"

Bow::Bow()
{
}

void Bow::SkillEvent(int x, int y, Character* player, Character* enemy, int result)
{
	static int win;
	if (win != 0 && win != 1 && win != 2)
		win = 0;

	if (result == RESULT_WIN)
	{
		int damage = player->GetDamage();

		if (win == 0)
		{
			m_draw.TextMiddle(x, y, "데미지 : " + to_string(damage));
			win++;
		}
		else if (win == 1)
		{
			damage *= 3;
			m_draw.TextMiddle(x, y, "연사 1단계 발동! (2콤보시 데미지가 크게 증가) 데미지 : " + to_string(damage));
			win++;
		}
		else if (win == 2)
		{
			damage *= 9;
			m_draw.TextMiddle(x, y, "연사 2단계 발동! (3콤보시 데미지가 극한으로 증가) 데미지 : " + to_string(damage));
			win = 0;
		}

		enemy->DecreaseHp(damage);
	}
	else if (result == RESULT_LOSE)
	{
		player->DecreaseHp(enemy->GetDamage());
		win = 0;
	}
	else if (result == RESULT_TIE)
		win = 0;
}

Bow::~Bow()
{
}
