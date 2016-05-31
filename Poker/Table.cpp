#include "Table.h"



Table::Table(int minRate)
{
	this->mainDeck = new Deck(52);
	this->tableDeck = new Deck(5);
	this->cashRound = 0;
	this->minRate = minRate;
	this->lastRate = 0;
	endCircle = false;

	combinations[0] = "Hight Card"; //оценивается по старшей карте
	combinations[1] = "Pair"; //2 карты одного ранга
	combinations[2] = "Two Pair"; //2 карты одного ранга и 2 другого
	combinations[3] = "Three of Kind"; //3 карты одного ранга
	combinations[4] = "Straight"; //5 последовательных карт
	combinations[5] = "Flush"; //5 карт одной масти
	combinations[6] = "Full House"; //3 карты одного ранга и 2 другого
	combinations[7] = "Four of Kind"; //4 карты одного ранга
	combinations[8] = "Straight Flush"; //5 последовательных карт одной масти
	combinations[9] = "Royal Flush"; //5 старших карт одной масти
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

Deck* Table::getTableDeck()
{
	return this->tableDeck;
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
	this->queue.front()->setTurn("Raise");
	this->nextPlayer();
}

void Table::Fold()
{
	this->queue.front()->setActive(false);
	this->queue.front()->setTurn("Fold");
	this->nextPlayer();
}

void Table::Check()
{
	this->queue.front()->setTurn("Check");
	this->nextPlayer();
}

void Table::allIn()
{
	this->doingRate(queue.front()->getCash());
	this->queue.front()->setTurn("allIn");
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
		if (queue.front()->getTurn() != "Call") return;
		this->nextPlayer();
	}
	this->endCircle = true;
}

void Table::clearTurn()
{
	for (int i = 0; i < queue.size(); i++)
	{
		queue.front()->setTurn("");
		this->nextPlayer();
	}
	this->endCircle = false;
}

int Table::combination()
{
	for (int i = 0; i < queue.size(); i++)
	{
		//тестирование колоды для разных комбинаций
		/*Deck* cardsCombination = new Deck(7);
		cardsCombination->generateHightCard();*/

		Deck* cardsCombination = *this->tableDeck + *queue.front()->getDeck();
		int combination = cardsCombination->findCombination();
		delete cardsCombination;
		this->nextPlayer();
	}
	
	return 1;
}