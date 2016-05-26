#include "Table.h"



Table::Table()
{
	this->mainDeck = new Deck(52);
	this->tableDeck = new Deck(5);
	this->cashRound = 0;
	this->minRate = 50;
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

void Table::nextPlayer()
{
	this->queue.push(this->queue.front());
	this->queue.pop();
}

Deck* Table::getMainDeck()
{
	return this->mainDeck;
}

std::queue<Player*> Table::getQueue()
{
	return this->queue;
}

int Table::getMinRate()
{
	return this->minRate;
}

void Table::doingRate(int rate)
{
	this->queue.front()->minusCash(rate);
	this->cashRound += rate;
}