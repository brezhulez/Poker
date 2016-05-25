#include "Table.h"



Table::Table()
{
	this->mainDeck = new Deck(52);
	this->tableDeck = new Deck(5);
	this->cashRound = 0;
}


Table::~Table()
{
}

void Table::generateQueue()
{
	for (int i = 0; i < 5; i++)
	{
		Player *player = new Player(1000);
		this->queue.push(player);
	}
	queue.front()->setDealler(true);
}