#include "Table.h"



Table::Table()
{
	this->mainDeck = new Deck(52);
	this->tableDeck = new Deck(5);
	this->cashRound = 0;
}


Table::~Table()
{
}
