#include "Player.h"



Player::Player(int cash)
{
	this->dealler = false;
	this->active = true;
	this->cash = cash;
	this->turn = "";
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

bool Player::getActive()
{
	return this->active;
}

void Player::setActive(bool active)
{
	this->active = active;
}

void Player::minusCash(int cash)
{
	this->cash -= cash;
}
void Player::plusCash(int cash)
{
	this->cash += cash;
}

int Player::getCash()
{
	return this->cash;
}

void Player::setTurn(std::string turn)
{
	this->turn = turn;
}

std::string Player::getTurn()
{
	return this->turn;
}

Deck* Player::getDeck()
{
	return this->deck;
}