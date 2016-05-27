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
	int lastRate;
public:
	Table(int minRate);
	~Table();
	void generateQueue();
	void nextPlayer();
	Deck* getMainDeck();
	std::queue<Player*> getQueue();
	int getMinRate();
	int getLastRate();
	void doingRate(int rate);

	void Check();
	void Call();
	void Raise(int rate);
	void Fold();
};

