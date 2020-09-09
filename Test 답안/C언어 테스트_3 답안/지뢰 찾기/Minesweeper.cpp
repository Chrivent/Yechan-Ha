#include "Minesweeper.h"

Minesweeper::Minesweeper()
{
	level = "초급";

	Load();

	useQuestionMark = true;

	mine = NULL;
	tile = NULL;
}

void Minesweeper::Load()
{
	if (level == "초급")
	{
		height = 9;
		width = 9;
		mineCount = 9;
	}
	else if (level == "중급")
	{
		height = 16;
		width = 16;
		mineCount = 40;
	}
	else if (level == "고급")
	{
		height = 16;
		width = 30;
		mineCount = 99;
	}
	else if (level == "사용자 지정")
	{
		system("cls");

		while (true)
		{
			cout << "높이(9 ~ 24) : ";
			height = InputNum();

			if (height >= 9 && height <= 24)
				break;
			else
				cout << "범위를 벗어났습니다." << endl;
		}

		while (true)
		{
			cout << "너비(9 ~ 30) : ";
			width = InputNum();

			if (width >= 9 && width <= 30)
				break;
			else
				cout << "범위를 벗어났습니다." << endl;
		}

		int mineMax = TileCount() - 1;
		if (mineMax > 668)
			mineMax = 668;

		while (true)
		{
			cout << "지뢰(10 ~ " << to_string(mineMax) << ") : ";
			mineCount = InputNum();

			if (mineCount >= 10 && mineCount <= mineMax)
				break;
			else
				cout << "범위를 벗어났습니다." << endl;
		}
	}
}

void Minesweeper::Init()
{
	SetScreenSize(width, height + 1);

	mine = new Mine[mineCount];
	for (int i = 0; i < mineCount; i++)
	{
		while (true)
		{
			mine[i].SetPosition({ RandNum(0, width - 1), RandNum(0, height - 1) });

			bool overlap = false;
			for (int j = 0; j < i; j++)
			{
				if (mine[j].GetPosition() == mine[i].GetPosition())
					overlap = true;
			}

			if (!overlap)
				break;
		}
	}

	tile = new Tile[TileCount()];
	for (int i = 0; i < TileCount(); i++)
		tile[i].SetPosition({ i % width, i / width });

	cursor.SetPosition({ width / 2, height / 2 });
}

void Minesweeper::DrawMap()
{
	for (int i = 0; i < TileCount(); i++)
		tile[i].DrawTile(mine, mineCount);

	cursor.DrawCursor();

	DrawMineCount();
}

void Minesweeper::DrawMineCount()
{
	Draw draw;
	draw.WidthLine(0, height, width, "  ");
	draw.TextMiddle(width / 2, height, "지뢰 : " + to_string(mineCount - PlagTileCount()));
}

void Minesweeper::MoveLeft()
{
	if (cursor.GetPosition().x > 0)
	{
		for (int i = 0; i < TileCount(); i++)
		{
			if (tile[i].GetPosition() == cursor.GetPosition())
				tile[i].DrawTile(mine, mineCount);
		}
		cursor.MoveLeft();
		cursor.DrawCursor();
	}
}

void Minesweeper::MoveRight()
{
	if (cursor.GetPosition().x < width - 1)
	{
		for (int i = 0; i < TileCount(); i++)
		{
			if (tile[i].GetPosition() == cursor.GetPosition())
				tile[i].DrawTile(mine, mineCount);
		}
		cursor.MoveRight();
		cursor.DrawCursor();
	}
}

void Minesweeper::MoveUp()
{
	if (cursor.GetPosition().y > 0)
	{
		for (int i = 0; i < TileCount(); i++)
		{
			if (tile[i].GetPosition() == cursor.GetPosition())
				tile[i].DrawTile(mine, mineCount);
		}
		cursor.MoveUp();
		cursor.DrawCursor();
	}
}

void Minesweeper::MoveDown()
{
	if (cursor.GetPosition().y < height - 1)
	{
		for (int i = 0; i < TileCount(); i++)
		{
			if (tile[i].GetPosition() == cursor.GetPosition())
				tile[i].DrawTile(mine, mineCount);
		}
		cursor.MoveDown();
		cursor.DrawCursor();
	}
}

void Minesweeper::EnterEvent()
{
	if (CheckPositionIsMine(cursor.GetPosition()))
	{
		for (int i = 0; i < mineCount; i++)
			mine[i].DrawMine();

		getch();
		Release();
		Init();
		DrawMap();
		return;
	}

	UnpackTile(cursor.GetPosition());

	if (CheckFindAllMine())
	{
		Draw draw;
		draw.TextMiddle(width / 2, height, "축하합니다!!!");

		getch();
		Release();
		Init();
		DrawMap();
	}
}

void Minesweeper::UnpackTile(Position position)
{
	if (!CheckPositionIsInMap(position))
		return;
	else if (CheckPositionIsUnpackTile(position))
		return;

	for (int i = 0; i < TileCount(); i++)
	{
		if (tile[i].GetPosition() == position)
		{
			tile[i].Unpack();
			tile[i].DrawTile(mine, mineCount);
		}
	}

	if (CheckPositionIsNumberTile(position))
		return;

	for (int x = position.x - 1; x <= position.x + 1; x++)
	{
		for (int y = position.y - 1; y <= position.y + 1; y++)
			UnpackTile({ x, y });
	}
}

bool Minesweeper::CheckPositionIsMine(Position position)
{
	for (int i = 0; i < mineCount; i++)
	{
		if (mine[i].GetPosition() == position)
			return true;
	}
	return false;
}

bool Minesweeper::CheckPositionIsUnpackTile(Position position)
{
	for (int i = 0; i < TileCount(); i++)
	{
		if (tile[i].GetPosition() == position && tile[i].CheckUnpack())
			return true;
	}
	return false;
}

bool Minesweeper::CheckPositionIsNumberTile(Position position)
{
	for (int i = 0; i < TileCount(); i++)
	{
		if (tile[i].GetPosition() == position && tile[i].MineCountAround(mine, mineCount) != 0)
			return true;
	}
	return false;
}

bool Minesweeper::CheckPositionIsInMap(Position position)
{
	if (position.x >= 0 && position.x < width)
	{
		if (position.y >= 0 && position.y < height)
			return true;
	}
	return false;
}

void Minesweeper::SpaceEvent()
{
	for (int i = 0; i < TileCount(); i++)
	{
		if (tile[i].GetPosition() == cursor.GetPosition() && !tile[i].CheckUnpack())
		{
			if (tile[i].CheckPlag() == false)
			{
				if (tile[i].CheckQuestionMark() == true)
					tile[i].DeleteQuestionMark();
				else
					tile[i].SetPlag();
			}
			else
			{
				tile[i].DeletePlag();

				if (useQuestionMark == true)
					tile[i].SetQuestionMark();
			}
			tile[i].DrawTile(mine, mineCount);

			DrawMineCount();
		}
	}
}

void Minesweeper::Option(bool& playing)
{
	while (true)
	{
		system("cls");

		cout << "1. 난이도 설정" << endl << "(현재 : " << level << ")" << endl;
		cout << "2. 물음표 On/Off" << endl << "(현재 : " << (useQuestionMark ? "On" : "Off") << ")" << endl;
		cout << "3. 돌아가기" << endl;
		cout << "4. 종료" << endl;
		cout << "입력 : " << endl;

		switch (InputNum())
		{
		case 1:
			SetLevel();
			break;
		case 2:
			if (useQuestionMark == true)
			{
				useQuestionMark = false;

				for (int i = 0; i < TileCount(); i++)
				{
					if (tile[i].CheckQuestionMark() == true)
						tile[i].DeleteQuestionMark();
				}
			}
			else
				useQuestionMark = true;

			break;
		case 3:
			return;
		case 4:
			playing = false;
			return;
		default:
			break;
		}
	}
}

void Minesweeper::SetLevel()
{
	while (true)
	{
		system("cls");

		cout << "1. 초급" << endl;
		cout << "2. 중급" << endl;
		cout << "3. 고급" << endl;
		cout << "4. 사용자 지정" << endl;
		cout << "5. 돌아가기" << endl;
		cout << "입력 : " << endl;

		switch (InputNum())
		{
		case 1:
			level = "초급";
			Release();
			Load();
			Init();
			break;
		case 2:
			level = "중급";
			Release();
			Load();
			Init();
			break;
		case 3:
			level = "고급";
			Release();
			Load();
			Init();
			break;
		case 4:
			level = "사용자 지정";
			Release();
			Load();
			Init();
			break;
		case 5:
			return;
		default:
			break;
		}
	}
}

bool Minesweeper::CheckFindAllMine()
{
	if (PackTileCount() == mineCount)
		return true;
	return false;
}

int Minesweeper::PackTileCount()
{
	int packTileCount = 0;

	for (int i = 0; i < TileCount(); i++)
	{
		if (tile[i].CheckUnpack() == false)
			packTileCount++;
	}

	return packTileCount;
}

int Minesweeper::PlagTileCount()
{
	int plagTileCount = 0;

	for (int i = 0; i < TileCount(); i++)
	{
		if (tile[i].CheckPlag() == true)
			plagTileCount++;
	}

	return plagTileCount;
}

int Minesweeper::TileCount()
{
	return width * height;
}

void Minesweeper::Release()
{
	delete[] tile;
	delete[] mine;
	tile = NULL;
	mine = NULL;
}

Minesweeper::~Minesweeper()
{
	Release();
}