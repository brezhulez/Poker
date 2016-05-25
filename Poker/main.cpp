#include "Table.h"

int main()
{
/*	Deck *deck = new Deck(52);
	deck->generateDeck();
	Card* card = deck->getCard();
	deck->addCard(card);
	deck->mixDeck();*/
	Table *table = new Table();
	table->generateQueue();
	std::cin.get();
	return 0;
}