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
	int minRate;
public:
	Table();
	~Table();
	void generateQueue();
	void nextPlayer();
	Deck* getMainDeck();
	std::queue<Player*> getQueue();
	int getMinRate();
	void doingRate(int rate);
};

