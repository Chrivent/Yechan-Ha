#include<stdio.h>
#include<stdbool.h>
#include<stdlib.h>
#include<string.h>
#include<conio.h>
#include<Windows.h>
#include<time.h>
#include<math.h>
#include<crtdbg.h>
#include<iostream>
#include<iomanip>
#include<fstream>
#include<string>
#include<vector>

using namespace std;

#define col GetStdHandle(STD_OUTPUT_HANDLE) 
#define BLACK SetConsoleTextAttribute( col,0x0000 );
#define DARK_BLUE SetConsoleTextAttribute( col,0x0001 );
#define GREEN SetConsoleTextAttribute( col,0x0002 );
#define BLUE_GREEN SetConsoleTextAttribute( col,0x0003 );
#define BLOOD SetConsoleTextAttribute( col,0x0004 );
#define PUPPLE SetConsoleTextAttribute( col,0x0005 );
#define GOLD SetConsoleTextAttribute( col,0x0006 );
#define ORIGINAL SetConsoleTextAttribute( col,0x0007 );
#define GRAY SetConsoleTextAttribute( col,0x0008 );
#define BLUE SetConsoleTextAttribute( col,0x0009 );
#define HIGH_GREEN SetConsoleTextAttribute( col,0x000a );
#define SKY_BLUE SetConsoleTextAttribute( col,0x000b );
#define RED SetConsoleTextAttribute( col,0x000c );
#define PLUM SetConsoleTextAttribute( col,0x000d );
#define YELLOW SetConsoleTextAttribute( col,0x000e );

#define Y 0
#define X 1

#define MAX 100

#define NULL 0
#define WALL 1
#define STONE 2
#define EXIT 3
#define SAND 4
#define EXPLODE 5
#define PLAYER 6
#define BUG_Init 100
#define MUMMY_Init 200
#define DOOR_Init 300
#define KEY_Init 400
#define MARBLE_Init 500
#define ROCK_Init 600
#define TNT_Init 700

#define LEFT 75
#define RIGHT 77
#define UP 72
#define DOWN 80
#define ESC 27

#define HEIGHT 12
#define WIDTH 18

#define LIFE 3
#define SPEED 4

void Loading();
void Init();
void MapDraw();
void PlayerMove();
void EnemyMove();
void ObjectMove();
void ExitEvent();
void PlayerEvent();
void BugEvent(int Bugindex);
void MummyEvent(int Mummyindex);
void KeyEvent(int Keyindex);
void MarbleEvent(int Marbleindex);
void TntEvent(int Tntindex);
void RockEvent(int Rockindex);
void DoExplode(int ExplodeY, int ExplodeX);

bool PlayerCanMove(int index1, int index2);
bool EnemyCanMove(int index);
bool KeyCanMove(int index);
bool MarbleCanMove(int index, bool Fall);
bool RockCanMove(int index, bool Fall);
bool TntCanMove(int index, bool Fall);

vector<int> Player(2);
vector<int> Exit(2);

vector<vector<int>> Bug(MAX, vector<int>(2));
vector<vector<int>> Mummy(MAX, vector<int>(2));
vector<vector<int>> Door(MAX, vector<int>(2));
vector<vector<int>> Key(MAX, vector<int>(2));
vector<vector<int>> Marble(MAX, vector<int>(2));
vector<vector<int>> Tnt(MAX, vector<int>(2));
vector<vector<int>> Rock(MAX, vector<int>(2));

vector<int> Bugindex(MAX);
vector<int> Mummyindex(MAX);
vector<int> Keyindex(MAX);
vector<int> Marbleindex(MAX);
vector<int> Tntindex(MAX);
vector<int> Rockindex(MAX);

int PlayerDirect;
vector<int> BugDirect(MAX);
vector<int> MummyDirect(MAX);

vector<bool> MarbleFall(MAX);
vector<bool> TntFall(MAX);
vector<bool> RockFall(MAX);

int Map[HEIGHT][WIDTH];
int Lv;
int Life;
int MarbleCount;
int Time;

bool ClearMap;
bool PlayerExploded;

vector<vector<int>> Lv1(HEIGHT, vector<int>(WIDTH));
vector<vector<int>> Lv2(HEIGHT, vector<int>(WIDTH));
vector<vector<int>> Lv3(HEIGHT, vector<int>(WIDTH));
vector<vector<int>> Lv4(HEIGHT, vector<int>(WIDTH));

void main()
{
	Lv = 1;
	Life = LIFE;
	Time = 1;
	ClearMap = true;
	PlayerExploded = false;

	Loading();

	Init();

	while (Life)
	{
		MapDraw();

		ExitEvent();

		if (!(Time % (SPEED / 2)))
			ObjectMove();

		if (!(Time % SPEED))
			EnemyMove();

		PlayerMove();

		Time++;
		if (Time == SPEED + 1)
			Time = 1;

		Sleep(33);
	}
}

void Loading()
{
	ifstream load;

	load.open("Lv1.txt");
	for (int y = 0; y < HEIGHT; y++)
	{
		for (int x = 0; x < WIDTH; x++)
			load >> Lv1[y][x];
	}
	load.close();

	load.open("Lv2.txt");
	for (int y = 0; y < HEIGHT; y++)
	{
		for (int x = 0; x < WIDTH; x++)
			load >> Lv2[y][x];
	}
	load.close();

	load.open("Lv3.txt");
	for (int y = 0; y < HEIGHT; y++)
	{
		for (int x = 0; x < WIDTH; x++)
			load >> Lv3[y][x];
	}
	load.close();

	load.open("Lv4.txt");
	for (int y = 0; y < HEIGHT; y++)
	{
		for (int x = 0; x < WIDTH; x++)
			load >> Lv4[y][x];
	}
	load.close();
}

void Init()
{
	char buf[256];

	sprintf(buf, "mode con: lines=%d cols=%d", HEIGHT + 2, (WIDTH * 2) + 1);
	system(buf);

	for (int y = 0; y < HEIGHT; y++)
	{
		for (int x = 0; x < WIDTH; x++)
		{
			switch (Lv)
			{
			case 1:
				Map[y][x] = Lv1[y][x];
				MarbleCount = 1;
				break;
			case 2:
				Map[y][x] = Lv2[y][x];
				MarbleCount = 4;
				break;
			case 3:
				Map[y][x] = Lv3[y][x];
				MarbleCount = 9;
				break;
			case 4:
				Map[y][x] = Lv4[y][x];
				MarbleCount = 2;
				break;
			}

			if (Map[y][x] == PLAYER)
			{
				Player[Y] = y;
				Player[X] = x;
			}

			else if (Map[y][x] == EXIT)
			{
				Exit[Y] = y;
				Exit[X] = x;
			}

			else if (Map[y][x] >= BUG_Init && Map[y][x] < BUG_Init + MAX)
			{
				Bug[Map[y][x] % MAX][Y] = y;
				Bug[Map[y][x] % MAX][X] = x;
			}

			else if (Map[y][x] >= MUMMY_Init && Map[y][x] < MUMMY_Init + MAX)
			{
				Mummy[Map[y][x] % MAX][Y] = y;
				Mummy[Map[y][x] % MAX][X] = x;
			}

			else if (Map[y][x] >= DOOR_Init && Map[y][x] < DOOR_Init + MAX)
			{
				Door[Map[y][x] % MAX][Y] = y;
				Door[Map[y][x] % MAX][X] = x;
			}

			else if (Map[y][x] >= KEY_Init && Map[y][x] < KEY_Init + MAX)
			{
				Key[Map[y][x] % MAX][Y] = y;
				Key[Map[y][x] % MAX][X] = x;
			}

			else if (Map[y][x] >= MARBLE_Init && Map[y][x] < MARBLE_Init + MAX)
			{
				Marble[Map[y][x] % MAX][Y] = y;
				Marble[Map[y][x] % MAX][X] = x;
			}

			else if (Map[y][x] >= ROCK_Init && Map[y][x] < ROCK_Init + MAX)
			{
				Rock[Map[y][x] % MAX][Y] = y;
				Rock[Map[y][x] % MAX][X] = x;
			}

			else if (Map[y][x] >= TNT_Init && Map[y][x] < TNT_Init + MAX)
			{
				Tnt[Map[y][x] % MAX][Y] = y;
				Tnt[Map[y][x] % MAX][X] = x;
			}
		}
	}

	for (int Num = 0; Num < 100; Num++)
	{
		MarbleFall[Num] = false;
		RockFall[Num] = false;
		TntFall[Num] = false;
	}
}

void MapDraw()
{
	system("cls");

	for (int y = 0; y < HEIGHT; y++)
	{
		for (int x = 0; x < WIDTH; x++)
		{
			if (ClearMap)
			{
				Init();
				ClearMap = false;
			}

			if (Map[y][x] == NULL)
				printf("  ");

			else if (Map[y][x] == WALL)
			{
				PUPPLE
					printf("¡á");
				ORIGINAL
			}

			else if (Map[y][x] == STONE)
			{
				GRAY
					printf("¢Ì");
				ORIGINAL
			}

			else if (Map[y][x] == EXIT)
			{
				if (MarbleCount)
				{
					BLUE_GREEN
						printf("¢Ã");
					ORIGINAL
				}

				else
				{
					HIGH_GREEN
						printf("¢Ã");
					ORIGINAL
				}
			}

			else if (Map[y][x] == SAND)
			{
				YELLOW
					printf("¢Æ");
				ORIGINAL
			}

			else if (Map[y][x] == PLAYER)
			{
				ORIGINAL
					printf("¢¿");
				ORIGINAL
			}

			else if (Map[y][x] == EXPLODE)
			{
				BLOOD
					printf("£À");
				ORIGINAL
			}

			else if (Map[y][x] >= BUG_Init && Map[y][x] < BUG_Init + MAX)
			{
				GREEN
					printf("¢Î");
				ORIGINAL
			}

			else if (Map[y][x] >= MUMMY_Init && Map[y][x] < MUMMY_Init + MAX)
			{
				BLUE
					printf("¢Í");
				ORIGINAL
			}

			else if (Map[y][x] >= DOOR_Init && Map[y][x] < DOOR_Init + MAX)
			{
				PLUM
					printf("¡Ø");
				ORIGINAL
			}

			else if (Map[y][x] >= KEY_Init && Map[y][x] < KEY_Init + MAX)
			{
				YELLOW
					printf("¢Ò");
				ORIGINAL
			}

			else if (Map[y][x] >= MARBLE_Init && Map[y][x] < MARBLE_Init + MAX)
			{
				SKY_BLUE
					printf("¡Ý");
				ORIGINAL
			}

			else if (Map[y][x] >= ROCK_Init && Map[y][x] < ROCK_Init + MAX)
			{
				GRAY
					printf("¡Ü");
				ORIGINAL
			}

			else if (Map[y][x] >= TNT_Init && Map[y][x] < TNT_Init + MAX)
			{
				RED
					printf("¢Ç");
				ORIGINAL
			}
		}
		printf("\n");
	}
	printf("Life : %d\tMarbleCount : %d", Life, MarbleCount);

	for (int y = 0; y < HEIGHT; y++)
	{
		for (int x = 0; x < WIDTH; x++)
		{
			if (Map[y][x] == EXPLODE)
				Map[y][x] = NULL;
		}
	}

	if (PlayerExploded)
	{
		Life--;
		ClearMap = true;
		PlayerExploded = false;
	}

	for (int Num = 0; Num < MAX; Num++)
	{
		Bugindex[Num] = NULL;
		Mummyindex[Num] = NULL;
		Keyindex[Num] = NULL;
		Marbleindex[Num] = NULL;
		Tntindex[Num] = NULL;
		Rockindex[Num] = NULL;
	}
}

void PlayerMove()
{
	int index1, index2;

	if (GetAsyncKeyState(VK_LEFT) & 0x8000)
	{
		PlayerDirect = LEFT;

		index1 = Map[Player[Y]][Player[X] - 1];
		index2 = Map[Player[Y]][Player[X] - 2];

		if (PlayerCanMove(index1, index2))
		{
			Map[Player[Y]][Player[X]] = NULL;
			Player[X]--;
		}
	}

	else if (GetAsyncKeyState(VK_RIGHT) & 0x8000)
	{
		PlayerDirect = RIGHT;

		index1 = Map[Player[Y]][Player[X] + 1];
		index2 = Map[Player[Y]][Player[X] + 2];

		if (PlayerCanMove(index1, index2))
		{
			Map[Player[Y]][Player[X]] = NULL;
			Player[X]++;
		}
	}

	else if (GetAsyncKeyState(VK_UP) & 0x8000)
	{
		PlayerDirect = UP;

		index1 = Map[Player[Y] - 1][Player[X]];

		if (PlayerCanMove(index1, index1))
		{
			Map[Player[Y]][Player[X]] = NULL;
			Player[Y]--;
		}
	}

	else if (GetAsyncKeyState(VK_DOWN) & 0x8000)
	{
		PlayerDirect = DOWN;

		index1 = Map[Player[Y] + 1][Player[X]];

		if (PlayerCanMove(index1, index1))
		{
			Map[Player[Y]][Player[X]] = NULL;
			Player[Y]++;
		}
	}

	else if (GetAsyncKeyState(VK_ESCAPE) & 1)
	{
		Life--;
		ClearMap = true;
	}

	PlayerEvent();
}

void EnemyMove()
{
	for (int y = 0; y < HEIGHT; y++)
	{
		for (int x = 0; x < WIDTH; x++)
		{
			int index1, index2;
			int Num = Map[y][x] % MAX;

			if (Map[y][x] >= BUG_Init && Map[y][x] < BUG_Init + MAX)
			{
				Bugindex[Num] = Map[y][x];

				switch (BugDirect[Num])
				{
				case LEFT:
					index1 = Map[y][x - 1];
					index2 = Map[y + 1][x - 1];

					if (EnemyCanMove(index1))
					{
						Map[y][x] = NULL;
						Bug[Num][X]--;

						if (EnemyCanMove(index2))
							BugDirect[Num] = DOWN;
					}

					else
						BugDirect[Num] = UP;

					break;

				case RIGHT:
					index1 = Map[y][x + 1];
					index2 = Map[y - 1][x + 1];

					if (EnemyCanMove(index1))
					{
						Map[y][x] = NULL;
						Bug[Num][X]++;

						if (EnemyCanMove(index2))
							BugDirect[Num] = UP;
					}

					else
						BugDirect[Num] = DOWN;

					break;

				case UP:
					index1 = Map[y - 1][x];
					index2 = Map[y - 1][x - 1];

					if (EnemyCanMove(index1))
					{
						Map[y][x] = NULL;
						Bug[Num][Y]--;

						if (EnemyCanMove(index2))
							BugDirect[Num] = LEFT;
					}

					else
						BugDirect[Num] = RIGHT;

					break;

				case DOWN:
					index1 = Map[y + 1][x];
					index2 = Map[y + 1][x + 1];

					if (EnemyCanMove(index1))
					{
						Map[y][x] = NULL;
						Bug[Num][Y]++;

						if (EnemyCanMove(index2))
							BugDirect[Num] = RIGHT;
					}

					else
						BugDirect[Num] = LEFT;

					break;

				default:
					BugDirect[Num] = LEFT;

					break;
				}
			}

			else if (Map[y][x] >= MUMMY_Init && Map[y][x] < MUMMY_Init + MAX)
			{
				Mummyindex[Num] = Map[y][x];

				switch (MummyDirect[Num])
				{
				case HEIGHT:
					index1 = Map[y - 1][x];
					index2 = Map[y + 1][x];

					if (Player[Y] < y && EnemyCanMove(index1))
					{
						Map[y][x] = NULL;
						Mummy[Num][Y]--;
					}

					else if (Player[Y] > y && EnemyCanMove(index2))
					{
						Map[y][x] = NULL;
						Mummy[Num][Y]++;
					}

					MummyDirect[Num] = WIDTH;

					break;

				case WIDTH:
					index1 = Map[y][x - 1];
					index2 = Map[y][x + 1];

					if (Player[X] < x && EnemyCanMove(index1))
					{
						Map[y][x] = NULL;
						Mummy[Num][X]--;
					}

					else if (Player[X] > x && EnemyCanMove(index2))
					{
						Map[y][x] = NULL;
						Mummy[Num][X]++;
					}

					MummyDirect[Num] = HEIGHT;

					break;

				default:
					MummyDirect[Num] = HEIGHT;

					break;
				}
			}
		}
	}

	for (int Num = 0; Num < MAX; Num++)
	{
		if (Bugindex[Num] >= BUG_Init && Bugindex[Num] < BUG_Init + MAX)
			BugEvent(Bugindex[Num]);

		if (Mummyindex[Num] >= MUMMY_Init && Mummyindex[Num] < MUMMY_Init + MAX)
			MummyEvent(Mummyindex[Num]);
	}
}

void ObjectMove()
{
	for (int y = 0; y < HEIGHT; y++)
	{
		for (int x = 0; x < WIDTH; x++)
		{
			int Num = Map[y][x] % MAX;
			int indexDown = Map[y + 1][x];

			if (Map[y][x] >= KEY_Init && Map[y][x] < KEY_Init + MAX)
			{
				Keyindex[Num] = Map[y][x];

				if (KeyCanMove(indexDown))
				{
					Map[y][x] = NULL;
					Key[Num][Y]++;
				}
			}

			else if (Map[y][x] >= MARBLE_Init && Map[y][x] < MARBLE_Init + MAX)
			{
				Marbleindex[Num] = Map[y][x];

				if (MarbleCanMove(indexDown, MarbleFall[Num]))
				{
					Map[y][x] = NULL;
					Marble[Num][Y]++;
					MarbleFall[Num] = true;
				}

				else
					MarbleFall[Num] = false;
			}

			else if (Map[y][x] >= ROCK_Init && Map[y][x] < ROCK_Init + MAX)
			{
				Rockindex[Num] = Map[y][x];

				if (RockCanMove(indexDown, RockFall[Num]))
				{
					Map[y][x] = NULL;
					Rock[Num][Y]++;
					RockFall[Num] = true;
				}

				else
					RockFall[Num] = false;
			}

			else if (Map[y][x] >= TNT_Init && Map[y][x] < TNT_Init + MAX)
			{
				Tntindex[Num] = Map[y][x];

				if (TntCanMove(indexDown, TntFall[Num]))
				{
					Map[y][x] = NULL;
					Tnt[Num][Y]++;
					TntFall[Num] = true;
				}

				else
					TntFall[Num] = false;
			}
		}
	}

	for (int Num = 0; Num < MAX; Num++)
	{
		if (Keyindex[Num] >= KEY_Init && Keyindex[Num] < KEY_Init + MAX)
			KeyEvent(Keyindex[Num]);

		if (Marbleindex[Num] >= MARBLE_Init && Marbleindex[Num] < MARBLE_Init + MAX)
			MarbleEvent(Marbleindex[Num]);

		if (Tntindex[Num] >= TNT_Init && Tntindex[Num] < TNT_Init + MAX)
			TntEvent(Tntindex[Num]);

		if (Rockindex[Num] >= ROCK_Init && Rockindex[Num] < ROCK_Init + MAX)
			RockEvent(Rockindex[Num]);
	}
}

void ExitEvent()
{
	int indexUp = Map[Exit[Y] - 1][Exit[X]];

	Map[Exit[Y]][Exit[X]] = EXIT;

	if (indexUp == PLAYER && !MarbleCount)
	{
		Lv++;
		ClearMap = true;
	}
}


void PlayerEvent()
{
	int index = Map[Player[Y]][Player[X]];
	int Num = index % MAX;

	Map[Player[Y]][Player[X]] = PLAYER;

	if (index == EXPLODE)
	{
		DoExplode(Player[Y], Player[X]);
		PlayerExploded = true;
	}

	else if (index >= BUG_Init && index < MUMMY_Init + MAX)
	{
		DoExplode(Player[Y], Player[X]);
		PlayerExploded = true;
	}

	else if (index >= KEY_Init && index < KEY_Init + MAX)
		Map[Door[Num][Y]][Door[Num][X]] = NULL;

	else if (index >= MARBLE_Init && index < MARBLE_Init + MAX)
	{
		if (MarbleFall[Num])
		{
			DoExplode(Player[Y], Player[X]);
			DoExplode(Player[Y] - 1, Player[X]);
			PlayerExploded = true;
		}

		else
		{
			switch (PlayerDirect)
			{
			case LEFT:
				Marble[Num][X]--;
				break;
			case RIGHT:
				Marble[Num][X]++;
				break;
			}
			Map[Marble[Num][Y]][Marble[Num][X]] = index;
		}
	}

	else if (index >= TNT_Init && index < TNT_Init + MAX)
	{
		if (TntFall[Num])
		{
			DoExplode(Player[Y], Player[X]);
			DoExplode(Player[Y] - 1, Player[X]);
			PlayerExploded = true;
		}

		else
		{
			switch (PlayerDirect)
			{
			case LEFT:
				Tnt[Num][X]--;
				break;
			case RIGHT:
				Tnt[Num][X]++;
				break;
			}
			Map[Tnt[Num][Y]][Tnt[Num][X]] = index;
		}
	}

	else if (index >= ROCK_Init && index < ROCK_Init + MAX)
	{
		if (RockFall[Num])
		{
			DoExplode(Player[Y], Player[X]);
			DoExplode(Player[Y] - 1, Player[X]);
			PlayerExploded = true;
		}

		else
		{
			switch (PlayerDirect)
			{
			case LEFT:
				Rock[Num][X]--;
				break;
			case RIGHT:
				Rock[Num][X]++;
				break;
			}
			Map[Rock[Num][Y]][Rock[Num][X]] = index;
		}
	}
}

void BugEvent(int Bugindex)
{
	int index = Map[Bug[Bugindex % MAX][Y]][Bug[Bugindex % MAX][X]];

	Map[Bug[Bugindex % MAX][Y]][Bug[Bugindex % MAX][X]] = Bugindex;

	if (index == EXPLODE)
		DoExplode(Bug[Bugindex % MAX][Y], Bug[Bugindex % MAX][X]);

	else if (index == PLAYER)
	{
		DoExplode(Player[Y], Player[X]);
		PlayerExploded = true;
	}

	else if (index >= MARBLE_Init && index < MARBLE_Init + MAX && MarbleFall[index % MAX])
	{
		DoExplode(Bug[Bugindex % MAX][Y], Bug[Bugindex % MAX][X]);
		DoExplode(Bug[Bugindex % MAX][Y] - 1, Bug[Bugindex % MAX][X]);
	}

	else if (index >= ROCK_Init && index < ROCK_Init + MAX && RockFall[index % MAX])
	{
		DoExplode(Bug[Bugindex % MAX][Y], Bug[Bugindex % MAX][X]);
		DoExplode(Bug[Bugindex % MAX][Y] - 1, Bug[Bugindex % MAX][X]);
	}

	else if (index >= TNT_Init && index < TNT_Init + MAX && TntFall[index % MAX])
	{
		DoExplode(Bug[Bugindex % MAX][Y], Bug[Bugindex % MAX][X]);
		DoExplode(Bug[Bugindex % MAX][Y] - 1, Bug[Bugindex % MAX][X]);
	}
}

void MummyEvent(int Mummyindex)
{
	int index = Map[Mummy[Mummyindex % MAX][Y]][Mummy[Mummyindex % MAX][X]];

	Map[Mummy[Mummyindex % MAX][Y]][Mummy[Mummyindex % MAX][X]] = Mummyindex;

	if (index == EXPLODE)
		DoExplode(Mummy[Mummyindex % MAX][Y], Mummy[Mummyindex % MAX][X]);

	else if (index == PLAYER)
	{
		DoExplode(Player[Y], Player[X]);
		PlayerExploded = true;
	}

	else if (index >= MARBLE_Init && index < MARBLE_Init + MAX && MarbleFall[index % MAX])
	{
		DoExplode(Mummy[Mummyindex % MAX][Y], Mummy[Mummyindex % MAX][X]);
		DoExplode(Mummy[Mummyindex % MAX][Y] - 1, Mummy[Mummyindex % MAX][X]);
	}

	else if (index >= ROCK_Init && index < ROCK_Init + MAX && RockFall[index % MAX])
	{
		DoExplode(Mummy[Mummyindex % MAX][Y], Mummy[Mummyindex % MAX][X]);
		DoExplode(Mummy[Mummyindex % MAX][Y] - 1, Mummy[Mummyindex % MAX][X]);
	}

	else if (index >= TNT_Init && index < TNT_Init + MAX && TntFall[index % MAX])
	{
		DoExplode(Mummy[Mummyindex % MAX][Y], Mummy[Mummyindex % MAX][X]);
		DoExplode(Mummy[Mummyindex % MAX][Y] - 1, Mummy[Mummyindex % MAX][X]);
	}
}

void KeyEvent(int Keyindex)
{
	int index = Map[Key[Keyindex % MAX][Y]][Key[Keyindex % MAX][X]];

	Map[Key[Keyindex % MAX][Y]][Key[Keyindex % MAX][X]] = Keyindex;

	if (index == PLAYER)
	{
		Map[Door[Keyindex % MAX][Y]][Door[Keyindex % MAX][X]] = NULL;
		Map[Key[Keyindex % MAX][Y]][Key[Keyindex % MAX][X]] = PLAYER;
	}
}

void MarbleEvent(int Marbleindex)
{
	int index = Map[Marble[Marbleindex % MAX][Y]][Marble[Marbleindex % MAX][X]];

	Map[Marble[Marbleindex % MAX][Y]][Marble[Marbleindex % MAX][X]] = Marbleindex;

	if (index == EXPLODE)
		DoExplode(Marble[Marbleindex % MAX][Y], Marble[Marbleindex % MAX][X]);

	else if (index == EXIT)
		MarbleCount--;

	else if (index >= BUG_Init && index < MUMMY_Init + MAX && MarbleFall[Marbleindex % MAX])
	{
		DoExplode(Marble[Marbleindex % MAX][Y], Marble[Marbleindex % MAX][X]);
		DoExplode(Marble[Marbleindex % MAX][Y] - 1, Marble[Marbleindex % MAX][X]);
	}
}

void RockEvent(int Rockindex)
{
	int index = Map[Rock[Rockindex % MAX][Y]][Rock[Rockindex % MAX][X]];

	Map[Rock[Rockindex % MAX][Y]][Rock[Rockindex % MAX][X]] = Rockindex;

	if (index == EXPLODE)
		DoExplode(Rock[Rockindex % MAX][Y], Rock[Rockindex % MAX][X]);

	else if (index >= BUG_Init && index < MUMMY_Init + MAX && RockFall[Rockindex % MAX])
	{
		DoExplode(Rock[Rockindex % MAX][Y], Rock[Rockindex % MAX][X]);
		DoExplode(Rock[Rockindex % MAX][Y] - 1, Rock[Rockindex % MAX][X]);
	}
}

void TntEvent(int Tntindex)
{
	int index = Map[Tnt[Tntindex % MAX][Y]][Tnt[Tntindex % MAX][X]];
	int Num = index % MAX;

	Map[Tnt[Tntindex % MAX][Y]][Tnt[Tntindex % MAX][X]] = Tntindex;

	if (index == EXPLODE)
		DoExplode(Tnt[Tntindex % MAX][Y], Tnt[Tntindex % MAX][X]);

	else if (MarbleFall[Num] && index >= MARBLE_Init && index < MARBLE_Init + MAX)
	{
		DoExplode(Tnt[Tntindex % MAX][Y], Tnt[Tntindex % MAX][X]);
		DoExplode(Tnt[Tntindex % MAX][Y] - 1, Tnt[Tntindex % MAX][X]);
	}

	else if (TntFall[Num] && index >= TNT_Init && index < TNT_Init + MAX)
	{
		DoExplode(Tnt[Tntindex % MAX][Y], Tnt[Tntindex % MAX][X]);
		DoExplode(Tnt[Tntindex % MAX][Y] - 1, Tnt[Tntindex % MAX][X]);
	}

	else if (RockFall[Num] && index >= ROCK_Init && index < ROCK_Init + MAX)
	{
		DoExplode(Tnt[Tntindex % MAX][Y], Tnt[Tntindex % MAX][X]);
		DoExplode(Tnt[Tntindex % MAX][Y] - 1, Tnt[Tntindex % MAX][X]);
	}

	else if (TntFall[Tntindex % MAX] && index)
	{
		if (index == PLAYER || (index >= BUG_Init && index < MUMMY_Init + MAX) || (index >= MARBLE_Init && index < TNT_Init + MAX))
			DoExplode(Tnt[Tntindex % MAX][Y], Tnt[Tntindex % MAX][X]);

		DoExplode(Tnt[Tntindex % MAX][Y] - 1, Tnt[Tntindex % MAX][X]);
	}
}

void DoExplode(int ExplodeY, int ExplodeX)
{
	for (int j = -1; j <= 1; j++)
	{
		for (int i = -1; i <= 1; i++)
		{
			int index = Map[ExplodeY + j][ExplodeX + i];

			if (index != WALL && index != EXIT && !(index >= DOOR_Init && index < DOOR_Init + MAX))
				Map[ExplodeY + j][ExplodeX + i] = EXPLODE;
		}
	}
}

bool PlayerCanMove(int index1, int index2)
{
	if (!index1 || index1 == SAND || index1 == EXPLODE)
		return true;

	else if ((index1 >= KEY_Init && index1 < KEY_Init + MAX) || (index1 >= BUG_Init && index1 < MUMMY_Init + MAX))
		return true;

	else if (index1 >= MARBLE_Init && index1 < MARBLE_Init + MAX && (!index2 || index2 == EXPLODE) && !MarbleFall[index1 % MAX])
		return true;

	else if (index1 >= ROCK_Init && index1 < ROCK_Init + MAX && (!index2 || index2 == EXPLODE) && !RockFall[index1 % MAX])
		return true;

	else if (index1 >= TNT_Init && index1 < TNT_Init + MAX && (!index2 || index2 == EXPLODE) && !TntFall[index1 % MAX])
		return true;

	else
		return false;
}

bool EnemyCanMove(int index)
{
	if (!index || index == PLAYER || index == EXPLODE)
		return true;

	else
		return false;
}

bool KeyCanMove(int index)
{
	if (!index || index == PLAYER || index == EXPLODE)
		return true;

	else
		return false;
}

bool MarbleCanMove(int index, bool Fall)
{
	if (!index || index == EXPLODE || index == EXIT)
		return true;

	else if (((index >= TNT_Init && index < TNT_Init + MAX) || (index == PLAYER) || (index >= BUG_Init && index < MUMMY_Init + MAX)) && Fall)
		return true;

	else
		return false;
}

bool RockCanMove(int index, bool Fall)
{
	if (!index || index == EXPLODE)
		return true;

	else if (((index >= TNT_Init && index < TNT_Init + MAX) || (index == PLAYER) || (index >= BUG_Init && index < MUMMY_Init + MAX)) && Fall)
		return true;

	else
		return false;
}

bool TntCanMove(int index, bool Fall)
{
	if (!index || index == EXPLODE || Fall)
		return true;

	else
		return false;
}