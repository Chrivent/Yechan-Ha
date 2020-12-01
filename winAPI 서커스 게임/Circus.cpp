#include "Circus.h"

Circus::Circus()
{
	for (int i = 0; i < 2; i++)
		ring[i] = NULL;

	runType = 0;
	jumping = false;
	movingForward = false;
	movingBackward = false;
	acceleration = 24;
	flameType = 0;
}

void Circus::Draw(HDC hdc)
{
	background.Draw(hdc);

	for (int i = 0; i < 2; i++)
	{
		if (ring[i] != NULL)
			ring[i]->Draw(hdc);
	}

	player.Draw(hdc);

	for (int i = 0; i < 2; i++)
	{
		if (ring[i] != NULL)
			ring[i]->Draw2(hdc);
	}
}

void Circus::MoveForward()
{
	background.PassingBackward();

	if (runType == 15)
	{
		if (jumping)
			player.Jumping();
		else
			player.Running();

		runType = 0;
	}
	else
		runType++;

	movingForward = true;
	movingBackward = false;
}

void Circus::MoveBackward()
{
	background.PassingForward();

	if (runType == 15)
	{
		if (jumping)
			player.Jumping();
		else
			player.Running();

		runType = 0;
	}
	else
		runType++;

	movingForward = false;
	movingBackward = true;
}

void Circus::Stop()
{
	if (jumping)
		player.Jumping();
	else
		player.Idle();

	movingForward = false;
	movingBackward = false;
}

void Circus::Jump()
{
	if (jumping == false)
	{
		player.Jumping();
		player.transform.position.y--;

		jumping = true;
	}
}

void Circus::Float()
 {
	if (player.transform.position.y != 550)
	{
		player.transform.position.y -= acceleration;
		acceleration--;

		if (player.transform.position.y >= 550)
		{
			player.transform.position.y = 550;
			acceleration = 24;

			jumping = false;
		}
	}
}

void Circus::Clear()
{
	background.Cheering();
}

void Circus::CreateRing()
{
	for (int i = 0; i < 2; i++)
	{
		if (ring[i] == NULL)
		{
			ring[i] = new Ring;
			break;
		}
	}
}

void Circus::MoveRing()
{
	for (int i = 0; i < 2; i++)
	{
		if (ring[i] != NULL)
		{
			if (ring[i]->transform.position.x < 0)
			{
				delete ring[i];
				ring[i] = NULL;
			}
			else
			{
				if (movingForward)
					ring[i]->FastMove();
				else
				{
					if (movingBackward)
						ring[i]->SlowestMove();
					else
						ring[i]->SlowMove();
				}

				if (flameType == 10)
				{
					ring[i]->Flaming();
					flameType = 0;
				}
				else
					flameType++;
			}
		}
	}
}

void Circus::DeleteRing()
{
	for (int i = 0; i < 2; i++)
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