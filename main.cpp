#include "game.h"


int main()
{
	CGame game;
	while (game.Start() != CGame::GAME_END)
		;
	game.PrintGoodbye();
	return 0;
}