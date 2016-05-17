#pragma once

#include "Card.h"
#include <vector>
#include <string>
#include <algorithm>

class Deck
{
protected:
	std::vector<Card*> deck;
	int N;
public:
	Deck(int N);
	~Deck();
	void generateDeck();
	Card* getCard();
	void addCard(Card* card);
	void mixDeck();
};

