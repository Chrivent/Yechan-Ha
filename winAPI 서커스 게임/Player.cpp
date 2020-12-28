#include "Player.h"

Player::Player()
{
	transform.position = { 100, 460 };
	transform.scale = { 170, 170 };

	type = 0;
}

void Player::Running()
{
	type += 1;

	if (type >= 3)
		type = 0;
}

void Player::Jumping()
{
	type = 2;
}

void Player::Dying()
{
	type = 3;
}

void Player::Winning()
{
	type += 1;

	if (type == 6 || type < 4)
		type = 4;
}

void Player::Idle()
{
	type = 0;
}

Collider Player::GetCollider()
{
	Collider collider;
	collider.transform = transform;

	collider.transform.position.x += 20;
	collider.transform.scale.width -= 40;
	collider.transform.position.y += 150;
	collider.transform.scale.height -= 150;

	return collider;
}

int Player::GetType()
{
	return type;
}

void Player::Draw(HDC hdc)
{
	LPCWSTR sprite;

	switch (type)
	{
	case 0:
		sprite = TEXT("player0.bmp");
		break;

	case 1:
		sprite = TEXT("player1.bmp");
		break;

	case 2:
		sprite = TEXT("player2.bmp");
		break;

	case 3:
		sprite = TEXT("die.bmp");
		break;

	case 4:
		sprite = TEXT("win.bmp");
		break;

	case 5:
		sprite = TEXT("win2.bmp");
		break;
	}

	DrawBitmapTransparent(hdc, transform, sprite);

	//GetCollider().Draw(hdc);
}

Player::~Player()
{
}