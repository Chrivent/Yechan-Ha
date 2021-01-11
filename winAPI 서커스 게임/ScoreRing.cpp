#include "ScoreRing.h"

ScoreRing::ScoreRing()
{
	scoreCollider = new Collider;
}

Collider* ScoreRing::GetScoreCollider()
{
	scoreCollider->transform = transform;

	scoreCollider->transform.position.x += 20;
	scoreCollider->transform.scale.width -= 60;
	scoreCollider->transform.position.y += 80;
	scoreCollider->transform.scale.height -= 240;

	return scoreCollider;
}

void ScoreRing::Draw(HDC hdc)
{
	Transform transform1 = transform;
	transform1.scale.width /= 2;

	DrawBitmapTransparent(hdc, transform1, TEXT("enemy_l_b.bmp"));
}

void ScoreRing::Draw2(HDC hdc)
{
	Transform transform2 = transform;
	transform2.position.x += transform.scale.width / 2;
	transform2.scale.width /= 2;

	DrawBitmapTransparent(hdc, transform2, TEXT("enemy_l_f.bmp"));

	//GetCollider().Draw(hdc);
	GetScoreCollider()->Draw(hdc);
}

ScoreRing::~ScoreRing()
{
	if (scoreCollider != NULL)
	{
		delete scoreCollider;
		scoreCollider = NULL;
	}
}