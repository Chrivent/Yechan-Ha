#pragma once

#include "Background.h"
#include "Player.h"
#include "Ring.h"
#include "ScoreRing.h"
#include "Jar.h"
#include "Goal.h"

#define RING_MAX 20

class Circus
{
private:
	Background background;
	Player player;
	Ring* ring[RING_MAX];
	Jar jar[10];
	Goal goal;

	int moveSpeed;
	int ringSpeed;
	bool arriveGoal;
	int jumpDistance;
	int timer;
	int timerResurrection;
	int score;

public:
	Circus();

	void ResetRingSpeed();
	void MoveForward();
	void MoveForwardLittle();
	void MoveBackward();
	void Jump();
	bool Jumping();
	void MoveRing();
	void JarFlaming();
	void RingFlaming();
	void PlayerRunning();
	void PlayerJumping();
	void PlayerDying();
	void PlayerWinning();
	void PlayerIdle();
	void CrowdCheering();
	bool CheckColliderIsIntersect();
	void Die();
	bool Dying();
	bool CheckPlayerCanMove();
	bool CheckPlayerArriveGoal();
	void PlayerGetScore();
	void MoveToGoalOrigin();
	void Resurrection();
	bool Resurrecting();
	void IncreaseTimerResurrection();
	void TimerCount();
	void Draw(HDC hdc);
	void DeleteRing();

	~Circus();
};