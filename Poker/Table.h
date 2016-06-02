#pragma once
#include "Player.h"
#include <queue>
class Table
{
protected:
	Deck* mainDeck;
	Deck* tableDeck;
	std::queue<Player*> queue;
	int cashRound;
	int minRate;
	int lastRate;
	bool endCircle; //контролирует активность текущего круга торгов
	std::string combinations[10];
public:
	Table(int minRate);
	~Table();
	void generateQueue();
	void nextPlayer();
	void nextPlayerDraw();
	Deck* getMainDeck();
	Deck* getTableDeck();
	std::queue<Player*> getQueue();
	int getMinRate();
	int getCashRound();
	int getLastRate();
	void doingRate(int rate);
	bool getEndCircle();
	void setEndCircle(bool endCircle);
	void clearTurn();
	void checkTurn();

	//функции для определения действий текущего игрока
	void Check();
	void Call();
	void Raise(int rate);
	void Fold();
	void allIn();

	int combination();
	std::string getCombinationName(int rang);
};

