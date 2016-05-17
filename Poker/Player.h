#pragma once
#include "Deck.h"

class Player
{
protected:
	bool dealler;
	int cash;
	Deck* deck;
public:
	Player(bool dealler, int cash);
	~Player();
	void Check();
	void Call();
	void Raise();
	void Fold();
	void addCard(Card* card)
};

