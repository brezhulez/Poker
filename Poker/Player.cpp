#include "Player.h"



Player::Player(bool dealler, int cash)
{
	this->dealler = dealler;
	this->cash = cash;
	deck = new Deck(2);
}


Player::~Player()
{
}

void Player::addCard(Card* card)
{
	this->deck->addCard(card);
}