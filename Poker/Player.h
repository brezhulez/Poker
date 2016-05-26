#pragma once
#include "Deck.h"

class Player
{
protected:
	bool dealler;
	int cash;
	Deck* deck;
public:
	Player(int cash);
	~Player();
	void Check();
	void Call();
	void Raise();
	void Fold();
	bool getDealler();
	void setDealler(bool dealler);
	void minusCash(int cash);
	void plusCash(int cash);
	void addCard(Card* card);
};

