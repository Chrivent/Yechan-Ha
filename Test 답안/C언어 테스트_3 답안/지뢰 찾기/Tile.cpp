#include "Tile.h"

Tile::Tile()
{
	unpack = false;
	plag = false;
	questionMark = false;
}

void Tile::DrawTile(Mine* mine, int mineCount)
{
	Draw draw;

	if (unpack == false)
	{
		if (plag == true)
			draw.Point(position.x, position.y, "¢Ë", RED);
		else if (questionMark == true)
			draw.Point(position.x, position.y, "¢Ì", GRAY);
		else
			draw.Point(position.x, position.y, "¡à", HIGH_GREEN);
	}
	else
	{
		switch (MineCountAround(mine, mineCount))
		{
		case 0:
			draw.Point(position.x, position.y, "  ");
			break;
		case 1:
			draw.Point(position.x, position.y, "£±", SKY_BLUE);
			break;
		case 2:
			draw.Point(position.x, position.y, "£²", GREEN);
			break;
		case 3:
			draw.Point(position.x, position.y, "£³", RED);
			break;
		case 4:
			draw.Point(position.x, position.y, "£´", BLUE);
			break;
		case 5:
			draw.Point(position.x, position.y, "£µ", BLOOD);
			break;
		case 6:
			draw.Point(position.x, position.y, "£¶", BLUE_GREEN);
			break;
		case 7:
			draw.Point(position.x, position.y, "£·", GRAY);
			break;
		case 8:
			draw.Point(position.x, position.y, "£¸", ORIGINAL);
			break;
		default:
			break;
		}
	}
}

void Tile::Unpack()
{
	unpack = true;
}

int Tile::MineCountAround(Mine* mine, int mineCount)
{
	int mineCountAround = 0;

	for (int i = 0; i < mineCount; i++)
	{
		for (int x = position.x - 1; x <= position.x + 1; x++)
		{
			for (int y = position.y - 1; y <= position.y + 1; y++)
			{
				Position tmp = { x, y };

				if (mine[i].GetPosition() == tmp)
					mineCountAround++;
			}
		}
	}

	return mineCountAround;
}

bool Tile::CheckUnpack()
{
	return unpack;
}

bool Tile::CheckPlag()
{
	return plag;
}

bool Tile::CheckQuestionMark()
{
	return questionMark;
}

void Tile::SetPlag()
{
	plag = true;
}

void Tile::DeletePlag()
{
	plag = false;
}

void Tile::SetQuestionMark()
{
	questionMark = true;
}

void Tile::DeleteQuestionMark()
{
	questionMark = false;
}