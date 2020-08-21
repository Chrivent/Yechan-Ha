#include "Enemy.h"

Enemy::Enemy()
{
	m_live = false;
}

void Enemy::Update()
{
	RankUp();
	m_live = true;
}

void Enemy::SetLive(bool live)
{
	m_live = live;
}

bool Enemy::CheckLive()
{
	return m_live;
}

Enemy::~Enemy()
{

}