#include "Game.h"



Game::Game()
{
	this->table = new Table();
}


Game::~Game()
{
}

void Game::Init()
{
	table->getMainDeck()->generateDeck();
	table->getMainDeck()->mixDeck();
	table->generateQueue();
}