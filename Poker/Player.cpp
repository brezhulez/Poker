#include "Player.h"



Player::Player(int cash)
{
	this->dealler = false;
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

bool Player::getDealler()
{
	return this->dealler;
}

void Player::setDealler(bool dealler)
{
	this->dealler = dealler;
}