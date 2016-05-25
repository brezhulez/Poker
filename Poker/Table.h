#pragma once
#include "Player.h"
#include <queue>
class Table
{
protected:
	Deck* mainDeck;
	Deck* tableDeck;
	std::queue<Player*> queue;
	int cashRound;
public:
	Table();
	~Table();
	void generateQueue();
	Deck* getMainDeck();
};

