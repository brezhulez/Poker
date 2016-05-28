#include "Table.h"



Table::Table(int minRate)
{
	this->mainDeck = new Deck(52);
	this->tableDeck = new Deck(5);
	this->cashRound = 0;
	this->minRate = minRate;
	this->lastRate = 0;
	endCircle = false;
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
	while(queue.front()->getActive() == false)
	{
		this->queue.push(this->queue.front());
		this->queue.pop();
	}
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

int Table::getLastRate()
{
	return this->lastRate;
}

void Table::doingRate(int rate)
{
	this->queue.front()->minusCash(rate);
	this->cashRound += rate;
	this->lastRate = rate;
}

void Table::Call()
{
	this->doingRate(this->lastRate);
	this->queue.front()->setTurn("Call");
	this->nextPlayer();
}

void Table::Raise(int rate)
{
	this->doingRate(rate);
	this->nextPlayer();
}

void Table::Fold()
{
	this->queue.front()->setActive(false);
	this->nextPlayer();
}

void Table::Check()
{
	this->nextPlayer();
}

void Table::allIn()
{
	this->doingRate(queue.front()->getCash());
	this->nextPlayer();
}

bool Table::getEndCircle()
{
	return this->endCircle;
}

void Table::setEndCircle(bool endCircle)
{
	this->endCircle = endCircle;
}

void Table::checkTurn()
{
	for (int i = 0; i < queue.size(); i++)
	{
		if (queue.front()->getTurn() != "Check") return;
		this->nextPlayer();
	}
	endCircle = true;
}