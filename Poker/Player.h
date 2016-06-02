#pragma once
#include "Deck.h"

class Player
{
protected:
	bool dealler;
	bool active;
	bool man;
	bool winner;
	int cash;
	std::string turn;
	std::string name;
	Deck* deck;
	int combination;
	float x;
	float y;
public:
	Player(std::string name, int cash);
	~Player();
	int getCash();
	bool getDealler();
	bool getActive();
	bool getMan();
	void setMan(bool man);
	float getX();
	float getY();
	void setX(float x);
	void setY(float y);
	int getCombination();
	Deck* getDeck();
	void setDealler(bool dealler);
	void setActive(bool active);
	void minusCash(int cash);
	void plusCash(int cash);
	void addCard(Card* card);
	void setTurn(std::string turn);
	void setCombination(int combination);
	std::string getTurn();
	std::string getName();
	void setWinner(bool win);
	bool getWinner();
};

