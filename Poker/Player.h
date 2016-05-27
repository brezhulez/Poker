#pragma once
#include "Deck.h"

class Player
{
protected:
	bool dealler;
	bool active;
	int cash;
	Deck* deck;
public:
	Player(int cash);
	~Player();
	bool getDealler();
	bool getActive();
	void setDealler(bool dealler);
	void setActive(bool active);
	void minusCash(int cash);
	void plusCash(int cash);
	void addCard(Card* card);
};

