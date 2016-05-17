#include "Deck.h"

int main()
{
	Deck *deck = new Deck(52);
	deck->generateDeck();
	Card* card = deck->getCard();
	deck->addCard(card);
	deck->mixDeck();
	std::cin.get();
	return 0;
}