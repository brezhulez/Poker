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
	table->nextPlayer();
}

void Game::Blind()
{
	table->doingRate(table->getMinRate() / 2);
	table->nextPlayer();
	table->doingRate(table->getMinRate());
	table->nextPlayer();
}