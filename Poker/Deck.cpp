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
	int suits[4] = {259,260,261,262};
	std::string cards = "JQKA";
	for (int i = 0; i < 4; i++)
	{
		for (int j = 2; j < 11; j++)
		{
			Card *obj = new Card(std::to_string(j), suits[i]);
			this->deck.push_back(obj);
		}
		for (int j = 0; j < 4; j++)
		{
			std::string s(1, cards[j]);
			Card *obj = new Card(s, suits[i]);
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

void Deck::addCard(Card* card)
{
	this->deck.push_back(card);
}

void Deck::mixDeck()
{
	std::random_shuffle(this->deck.begin(), this->deck.end());
}