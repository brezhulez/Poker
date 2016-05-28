#include "Deck.h"



Deck::Deck(int N)
{
	this->N = N;
}


Deck::~Deck()
{
}

void Deck::generateDeck()
{
	const char* suits[4] = {"d","s","c","h"};
	std::string cards = "JQKA";
	std::string fileName;
	for (int i = 0; i < 4; i++)
	{
		for (int j = 2; j < 11; j++)
		{
			fileName = "images/orl001";
			fileName += suits[i];
			fileName += std::to_string(j);
			fileName += ".jpg";
			Card *obj = new Card(std::to_string(j), suits[i], fileName.c_str());
			this->deck.push_back(obj);
		}
		for (int j = 0; j < 4; j++)
		{
			std::string s(1, cards[j]);
			fileName = "images/orl001";
			fileName += suits[i];
			fileName += s;
			fileName += ".jpg";
			Card *obj = new Card(s, suits[i], fileName.c_str());
			this->deck.push_back(obj);
		}
	}
}

Card* Deck::getCard()
{
	Card *card = this->deck.back();
	this->deck.pop_back();
	return card;
}

Card* Deck::showCard()
{
	return this->deck.back();
}

void Deck::addCard(Card* card)
{
	this->deck.push_back(card);
}

void Deck::mixDeck()
{
	srand(time(0));
	std::random_shuffle(this->deck.begin(), this->deck.end());
}