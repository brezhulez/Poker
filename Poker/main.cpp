#include "Game.h"

int main()
{
	Game *game = new Game();
	game->Init();
	std::cin.get();
	return 0;
}