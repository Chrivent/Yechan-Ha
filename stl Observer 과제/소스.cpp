#include "RPG_Game.h"

void main()
{
	_CrtSetDbgFlag(_CRTDBG_LEAK_CHECK_DF | _CRTDBG_ALLOC_MEM_DF);

	RPG_Game game;
	
	game.AutoRun();
}