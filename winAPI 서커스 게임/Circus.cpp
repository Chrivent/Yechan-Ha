#include "Circus.h"

Circus::Circus()
{
	for (int i = 0; i < RING_MAX; i++)
		ring[i] = NULL;

	int tmp = 0;
	for (int i = 0; i < RING_MAX; i++)
	{
		tmp += RandNum(640, 1920);
		if (tmp <= 13090)
		{
			ring[i] = RandBool(3, 1) ? new ScoreRing : new Ring;
			ring[i]->transform.position.x = tmp;
		}
		else
			break;
	}

	for (int i = 0; i < 10; i++)
		jar[i].transform.position.x = 640 + i * 1280;

	moveSpeed = 10;
	ResetRingSpeed();
	arriveGoal = false;

	score = 0;
}

void Circus::ResetRingSpeed()
{
	ringSpeed = 10;
}

void Circus::MoveForward()
{
	if (background.transform.position.x >= -11800)
	{
		background.transform.MoveLeft(moveSpeed);
		for (int i = 0; i < 10; i++)
			jar[i].transform.MoveLeft(moveSpeed);
		goal.transform.MoveLeft(moveSpeed);

		ResetRingSpeed();
		ringSpeed += moveSpeed;
	}
	else
	{
		player.transform.MoveRight(moveSpeed);
		ResetRingSpeed();
	}
}

void Circus::MoveForwardLittle()
{
	int tmpSpeed = moveSpeed / 2;

	if (background.transform.position.x >= -11800)
	{
		background.transform.MoveLeft(tmpSpeed);
		for (int i = 0; i < 10; i++)
			jar[i].transform.MoveLeft(tmpSpeed);
		goal.transform.MoveLeft(tmpSpeed);

		ResetRingSpeed();
		ringSpeed += tmpSpeed;
	}
	else
	{
		player.transform.MoveRight(tmpSpeed);
		ResetRingSpeed();
	}
}

void Circus::MoveBackward()
{
	if (player.transform.position.x > 100)
	{
		player.transform.MoveLeft(moveSpeed);
		ResetRingSpeed();
	}
	else if (background.transform.position.x < 0)
	{
		background.transform.MoveRight(moveSpeed);
		for (int i = 0; i < 10; i++)
			jar[i].transform.MoveRight(moveSpeed);
		goal.transform.MoveRight(moveSpeed);

		ResetRingSpeed();
		ringSpeed -= moveSpeed;
	}
}

void Circus::Jump()
{
	player.transform.MoveDown();
}

bool Circus::Jumping()
{
	static int jumpDistance;

	if (player.transform.position.y != 460)
	{
		player.transform.position.y += jumpDistance;
		jumpDistance++;

		if (player.transform.position.y > 460)
			player.transform.position.y = 460;

		return true;
	}
	else
	{
		jumpDistance = -22;

		return false;
	}
}

void Circus::MoveRing()
{
	for (int i = 0; i < RING_MAX; i++)
	{
		if (ring[i] != NULL)
		{
			if (ring[i]->transform.position.x >= background.transform.position.x)
				ring[i]->transform.MoveLeft(ringSpeed);
			else
				ring[i]->transform.position.x = background.transform.position.x + 13090;
		}
	}
}

void Circus::JarFlaming()
{
	for (int i = 0; i < 10; i++)
		jar[i].Flaming();
}

void Circus::RingFlaming()
{
	for (int i = 0; i < RING_MAX; i++)
	{
		if (ring[i] != NULL)
			ring[i]->Flaming();
	}
}

void Circus::PlayerRunning()
{
	player.Running();
}

void Circus::PlayerJumping()
{
	player.Jumping();
}

void Circus::PlayerDying()
{
	player.Dying();
}

void Circus::PlayerWinning()
{
	player.Winning();
}

void Circus::PlayerIdle()
{
	player.Idle();
}

void Circus::CrowdCheering()
{
	background.Cheering();
}

bool Circus::CheckColliderIsIntersect()
{
	for (int i = 0; i < 10; i++)
	{
		if (CheckTransformIsIntersect(player.GetCollider().transform, jar[i].GetCollider().transform))
			return true;
	}

	for (int i = 0; i < RING_MAX; i++)
	{
		if (ring[i] != NULL)
		{
			if (CheckTransformIsIntersect(player.GetCollider().transform, ring[i]->GetCollider().transform))
				return true;
		}
	}

	return false;
}

void Circus::Die()
{
	player.Dying();
}

bool Circus::Dying()
{
	if (player.GetType() == 3)
	{
		if (player.transform.position.y <= 720)
		{
			player.transform.position.y += jumpDistance;
			jumpDistance++;
		}

		return true;
	}
	else
	{
		jumpDistance = -11;

		return false;
	}
}

bool Circus::CheckPlayerCanMove()
{
	if (player.transform.position.x + player.transform.scale.width < goal.transform.position.x)
		return true;
	else if (player.transform.position.y < 350)
		return true;
	else
		return false;
}

bool Circus::CheckPlayerArriveGoal()
{
	if (CheckTransformIsIntersect(player.GetCollider().transform, goal.GetCollider().transform))
		arriveGoal = true;

	return arriveGoal;
}

void Circus::PlayerGetScore()
{
	for (int i = 0; i < RING_MAX; i++)
	{
		if (ring[i] != NULL)
		{
			Collider* scoreCollider = ring[i]->GetScoreCollider();

			if (scoreCollider != NULL && CheckTransformIsIntersect(player.GetScoreCollider().transform, scoreCollider->transform))
			{
				Transform tmp = ring[i]->transform;
				delete ring[i];
				ring[i] = NULL;
				ring[i] = new Ring;
				ring[i]->transform = tmp;
				score++;
			}
		}
	}
}

void Circus::MoveToGoalOrigin()
{
	Position playerPosition = player.transform.position;
	Position goalOriginPosition = goal.transform.position;

	if (playerPosition.x != goalOriginPosition.x + 20)
		(playerPosition.x < goalOriginPosition.x + 20) ? player.transform.MoveRight(10) : player.transform.MoveLeft(10);

	if (playerPosition.y != goalOriginPosition.y - 150)
		player.transform.position.y = goalOriginPosition.y - 150;
}

void Circus::Resurrection()
{
	player.Resurrection();
	timerResurrection = 90;

	jumpDistance = -11;
}

bool Circus::Resurrecting()
{
	if (timerResurrection > 0)
		return true;
	return false;
}

void Circus::IncreaseTimerResurrection()
{
	timerResurrection--;
}

void Circus::TimerCount()
{
	timer++;
}

void Circus::Draw(HDC hdc)
{
	background.Draw(hdc);

	for (int i = 0; i < 10; i++)
		jar[i].Draw(hdc);

	goal.Draw(hdc);

	for (int i = 0; i < RING_MAX; i++)
	{
		if (ring[i] != NULL)
			ring[i]->Draw(hdc);
	}

	player.Draw(hdc);

	for (int i = 0; i < RING_MAX; i++)
	{
		if (ring[i] != NULL)
			ring[i]->Draw2(hdc);
	}

	TCHAR time[512];
	int tmp = timer / 30;
	wsprintf(time, TEXT("%d : %d"), tmp / 60, tmp % 60);
	DrawTextOut(hdc, { { 0, 720 }, { 240, 80 } }, time, WHITE);

	TCHAR timeResurrection[512];
	int tmp2 = (timerResurrection + 29) / 30;
	wsprintf(timeResurrection, TEXT("¹«Àû: %dÃÊ"), tmp2);
	if (tmp2 != 0)
		DrawTextOut(hdc, { { 420, 720 }, { 240, 80 } }, timeResurrection, WHITE);

	TCHAR scoreText[512];
	wsprintf(scoreText, TEXT("Score : %d"), score);
	DrawTextOut(hdc, { { 960, 720 }, { 240, 80 } }, scoreText, WHITE);
}

void Circus::DeleteRing()
{
	for (int i = 0; i < RING_MAX; i++)
	{
		if (ring[i] != NULL)
		{
			delete ring[i];
			ring[i] = NULL;
		}
	}
}

Circus::~Circus()
{
	DeleteRing();
}