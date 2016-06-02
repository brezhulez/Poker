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
	int getSize();
	Card* showCard(int position);
	void addCard(Card* card);
	void mixDeck();
	Deck*& operator+ (Deck& left);
	int findCombination();
	bool isEmpty();

	//функции для тестирования комбинаций
	/*void generateRoyalFlush();
	void generateStraightFlush();
	void generateFourofKind();
	void generateFullHouse();
	void generateFlush();
	void generateStraight();
	void generateThreeofKind();
	void generateTwoPair();
	void generatePair();
	void generateHightCard();*/
};

