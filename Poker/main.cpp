#include "Game.h"

int main()
{
	Game *game = new Game();
	game->Init();
	game->Blind();
	std::cin.get();
	return 0;
}