#pragma once

#include "Card.h"
#include <vector>
#include <string>
#include <algorithm>
#include <time.h>

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
	Card* showCard();
	void addCard(Card* card);
	void mixDeck();
};

