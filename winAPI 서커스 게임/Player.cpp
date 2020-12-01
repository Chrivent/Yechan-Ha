#include "Player.h"

Player::Player()
{
	transform.position = { 160, 550 };
	transform.scale = { 160, 160 };

	type = 0;
}

void Player::Running()
{
	type++;

	if (type == 3)
		type = 0;
}

void Player::Jumping()
{
	type = 1;
}

void Player::Idle()
{
	type = 0;
}

void Player::Draw(HDC hdc)
{
	if (type == 0)
		DrawBitmapTransparent(hdc, transform, TEXT("player0.bmp"));
	else if (type == 1)
		DrawBitmapTransparent(hdc, transform, TEXT("player2.bmp"));
	else if (type == 2)
		DrawBitmapTransparent(hdc, transform, TEXT("player1.bmp"));
}

Player::~Player()
{
}