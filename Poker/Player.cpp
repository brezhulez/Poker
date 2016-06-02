#include "Player.h"



Player::Player(std::string name, int cash)
{
	this->dealler = false;
	this->active = true;
	this->man = false;
	this->cash = cash;
	this->turn = "";
	this->name = name;
	this->winner = false;
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

int Player::getCombination()
{
	return this->combination;
}

void Player::setCombination(int combination)
{
	this->combination = combination;
}

float Player::getX()
{
	return this->x;
}
float Player::getY()
{
	return this->y;
}
void Player::setX(float x)
{
	this->x = x;
}
void Player::setY(float y)
{
	this->y = y;
}

bool Player::getMan()
{
	return this->man;
}
void Player::setMan(bool man)
{
	this->man = man;
}

Deck* Player::getDeck()
{
	return this->deck;
}

std::string Player::getName()
{
	return this->name;
}

void Player::setWinner(bool win)
{
	this->winner = win;
}
bool Player::getWinner()
{
	return this->winner;
}