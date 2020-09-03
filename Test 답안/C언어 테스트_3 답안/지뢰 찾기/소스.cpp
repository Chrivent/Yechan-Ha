#include "Minesweeper.h"

void main()
{
	_CrtSetDbgFlag(_CRTDBG_LEAK_CHECK_DF | _CRTDBG_ALLOC_MEM_DF);

	Minesweeper minesweeper;

	minesweeper.Init();
	minesweeper.DrawMap();

	while (true)
	{
		switch (Hit())
		{
		case 'a':
			minesweeper.MoveLeft();
			break;
		case 'd':
			minesweeper.MoveRight();
			break;
		case 'w':
			minesweeper.MoveUp();
			break;
		case 's':
			minesweeper.MoveDown();
			break;
		case ENTER:
			minesweeper.EnterEvent();
			break;
		case SPACE:
			minesweeper.SpaceEvent();
			break;
		case ESC:
			minesweeper.Option();
			minesweeper.DrawMap();
			break;
		default:
			break;
		}
	}

	minesweeper.Release();
}