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
	const char* suits[4] = {"d","s","c","h"};
	std::string fileName;
	for (int i = 0; i < 4; i++)
	{
		for (int j = 2; j < 15; j++)
		{
			fileName = "images/orl001";
			fileName += suits[i];
			if(j==11) fileName += "J";
			else if (j == 12) fileName += "Q";
			else if (j == 13) fileName += "K";
			else if (j == 14) fileName += "A";
			else fileName += std::to_string(j);
			fileName += ".jpg";
			Card *obj = new Card(j, suits[i], fileName.c_str());
			this->deck.push_back(obj);
		}
	}
}

Deck*& Deck::operator+ (Deck& right)
{
	Deck* tmp = new Deck(7);
	for (int i = 0; i < this->deck.size(); i++)
	{
		tmp->deck.push_back(this->deck[i]);
	}
	for (int i = 0; i < right.deck.size(); i++)
	{
		tmp->deck.push_back(right.deck[i]);
	}
	
	return tmp;
}

int Deck::findCombination()
{
	//сортируем колоду пузырьком
	bool sort = true;
	while (sort)
	{
		sort = false;
		for (int i = 0; i < this->deck.size()-1; i++)
		{
			if (this->deck[i]->getValue() > this->deck[i + 1]->getValue())
			{
				std::swap(this->deck[i], this->deck[i + 1]);
				sort = true;
			}
		}
	}
	
	int heards = 0; //количество червей
	int diamonds = 0; //количество бубей
	int clubs = 0; //количество крестей
	int spades = 0; //количество пикей
	int values[13]; //количество карт по рангу
	int combinations[10]; //конбинации у текущего игрока

	for (int i = 0; i < 13; i++) values[i] = 0;
	for (int i = 0; i < 10; i++) combinations[i] = 0;
	combinations[0] = 1;

	//считаем количество мастей в колоде и количество карт по рангу
	for (int i = 0; i < this->deck.size(); i++)
	{
		if(this->deck[i]->getSuit()=="h") heards++;
		else if (this->deck[i]->getSuit() == "d") diamonds++;
		else if (this->deck[i]->getSuit() == "c") clubs++;
		else if (this->deck[i]->getSuit() == "s") spades++;

		values[this->deck[i]->getValue()-2]++;
	}

	//проверка на комбинации: Royal Flush, Straight Flush
	if (heards >= 5 || diamonds >= 5 || clubs >= 5 || spades >= 5)
	{
		const char* bufSuit;
		if (heards >= 5) bufSuit = "h";
		else if (diamonds >= 5) bufSuit = "d";
		else if (clubs >= 5) bufSuit = "c";
		else if (spades >= 5) bufSuit = "s";
		
		//Royal Flush
		int royalFlushCount = 0;
		for (int i = 0; i < this->deck.size(); i++)
		{
			if (this->deck[i]->getSuit() == bufSuit)
			{
				if (this->deck[i]->getValue() == 10) royalFlushCount++;
				else if (this->deck[i]->getValue() == 11) royalFlushCount++;
				else if (this->deck[i]->getValue() == 12) royalFlushCount++;
				else if (this->deck[i]->getValue() == 13) royalFlushCount++;
				else if (this->deck[i]->getValue() == 14) royalFlushCount++;
			}
		}
		if (royalFlushCount >= 5) combinations[9] = 1;

		//Straight Flush
		int straightFlushCount = 0;
		int lastValue=0;
		for (int i = 0; i < this->deck.size(); i++)
		{
			if (this->deck[i]->getSuit() == bufSuit)
			{
				if (lastValue == 0) {
					straightFlushCount++;
					lastValue = this->deck[i]->getValue();
				}
				else if (this->deck[i]->getValue()-1 == lastValue) {
					straightFlushCount++;
					lastValue = this->deck[i]->getValue();
				}
			}
		}
		if (straightFlushCount >= 5) combinations[8] = 1;

		//Flush
		combinations[5] = 1;
	}

	//Four of Kind
	for (int i = 0; i < 13; i++)
	{
		if(values[i] >= 4) combinations[7] = 1;
	}

	//Full House
	bool fullHousetThree = false;
	bool fullHousetTwo = false;
	for (int i = 0; i < 13; i++)
	{
		if (values[i] >= 3) fullHousetThree = true;
		else if (values[i] >= 2) fullHousetTwo = true;
	}
	if(fullHousetThree==true && fullHousetTwo==true) combinations[6] = 1;

	//Straight
	int straightCount = 0;
	int lastValue = 0;
	for (int i = 0; i < this->deck.size(); i++)
	{
		if (lastValue == 0) {
			straightCount++;
			lastValue = this->deck[i]->getValue();
		}
		else if (this->deck[i]->getValue() - 1 == lastValue) {
			straightCount++;
			lastValue = this->deck[i]->getValue();
		}
	}
	
	if (straightCount >= 5) combinations[4] = 1;

	//Three of Kind
	for (int i = 0; i < 13; i++)
	{
		if (values[i] >= 3) combinations[3] = 1;
	}

	//Two Pair
	int twoPair = 0;
	for (int i = 0; i < 13; i++)
	{
		if (values[i] >= 2) twoPair++;
	}
	if (twoPair >= 2) combinations[2] = 1;

	//Pair
	for (int i = 0; i < 13; i++)
	{
		if (values[i] >= 2) combinations[1]=1;
	}

	for (int i = 9; i >= 0; i--)
	{
		if (combinations[i] == 1) return i;
	}
}

Card* Deck::getCard()
{
	Card *card = this->deck.back();
	this->deck.pop_back();
	return card;
}

Card* Deck::showCard(int position)
{
	return this->deck[position];
}

void Deck::addCard(Card* card)
{
	this->deck.push_back(card);
}

void Deck::mixDeck()
{
	srand(time(0));
	std::random_shuffle(this->deck.begin(), this->deck.end());
}

bool Deck::isEmpty()
{
	return this->deck.empty();
}

int Deck::getSize()
{
	return this->deck.size();
}
//функции для тестирования комбинаций
/*
void Deck::generateHightCard()
{
	Card *card1 = new Card(5, "c", "file");
	this->deck.push_back(card1);

	Card *card2 = new Card(8, "d", "file");
	this->deck.push_back(card2);

	Card *card3 = new Card(14, "c", "file");
	this->deck.push_back(card3);

	Card *card4 = new Card(7, "h", "file");
	this->deck.push_back(card4);

	Card *card5 = new Card(2, "c", "file");
	this->deck.push_back(card5);

	Card *card6 = new Card(9, "h", "file");
	this->deck.push_back(card6);

	Card *card7 = new Card(10, "c", "file");
	this->deck.push_back(card7);
}

void Deck::generatePair()
{
	Card *card1 = new Card(5, "c", "file");
	this->deck.push_back(card1);

	Card *card2 = new Card(8, "d", "file");
	this->deck.push_back(card2);

	Card *card3 = new Card(5, "c", "file");
	this->deck.push_back(card3);

	Card *card4 = new Card(7, "h", "file");
	this->deck.push_back(card4);

	Card *card5 = new Card(2, "c", "file");
	this->deck.push_back(card5);

	Card *card6 = new Card(9, "h", "file");
	this->deck.push_back(card6);

	Card *card7 = new Card(10, "c", "file");
	this->deck.push_back(card7);
}

void Deck::generateTwoPair()
{
	Card *card1 = new Card(5, "c", "file");
	this->deck.push_back(card1);

	Card *card2 = new Card(8, "d", "file");
	this->deck.push_back(card2);

	Card *card3 = new Card(5, "c", "file");
	this->deck.push_back(card3);

	Card *card4 = new Card(7, "h", "file");
	this->deck.push_back(card4);

	Card *card5 = new Card(2, "c", "file");
	this->deck.push_back(card5);

	Card *card6 = new Card(9, "h", "file");
	this->deck.push_back(card6);

	Card *card7 = new Card(2, "c", "file");
	this->deck.push_back(card7);
}

void Deck::generateThreeofKind()
{
	Card *card1 = new Card(5, "c", "file");
	this->deck.push_back(card1);

	Card *card2 = new Card(8, "d", "file");
	this->deck.push_back(card2);

	Card *card3 = new Card(5, "c", "file");
	this->deck.push_back(card3);

	Card *card4 = new Card(7, "h", "file");
	this->deck.push_back(card4);

	Card *card5 = new Card(2, "c", "file");
	this->deck.push_back(card5);

	Card *card6 = new Card(5, "h", "file");
	this->deck.push_back(card6);

	Card *card7 = new Card(3, "c", "file");
	this->deck.push_back(card7);
}

void Deck::generateStraight()
{
	Card *card1 = new Card(5, "c", "file");
	this->deck.push_back(card1);

	Card *card2 = new Card(8, "d", "file");
	this->deck.push_back(card2);

	Card *card3 = new Card(6, "c", "file");
	this->deck.push_back(card3);

	Card *card4 = new Card(7, "h", "file");
	this->deck.push_back(card4);

	Card *card5 = new Card(11, "c", "file");
	this->deck.push_back(card5);

	Card *card6 = new Card(9, "h", "file");
	this->deck.push_back(card6);

	Card *card7 = new Card(7, "c", "file");
	this->deck.push_back(card7);
}

void Deck::generateFlush()
{
	Card *card1 = new Card(5, "c", "file");
	this->deck.push_back(card1);

	Card *card2 = new Card(8, "d", "file");
	this->deck.push_back(card2);

	Card *card3 = new Card(6, "c", "file");
	this->deck.push_back(card3);

	Card *card4 = new Card(2, "c", "file");
	this->deck.push_back(card4);

	Card *card5 = new Card(11, "c", "file");
	this->deck.push_back(card5);

	Card *card6 = new Card(4, "h", "file");
	this->deck.push_back(card6);

	Card *card7 = new Card(7, "c", "file");
	this->deck.push_back(card7);
}

void Deck::generateFullHouse()
{
	Card *card1 = new Card(5, "c", "file");
	this->deck.push_back(card1);

	Card *card2 = new Card(5, "d", "file");
	this->deck.push_back(card2);

	Card *card3 = new Card(6, "c", "file");
	this->deck.push_back(card3);

	Card *card4 = new Card(5, "h", "file");
	this->deck.push_back(card4);

	Card *card5 = new Card(4, "s", "file");
	this->deck.push_back(card5);

	Card *card6 = new Card(4, "h", "file");
	this->deck.push_back(card6);

	Card *card7 = new Card(7, "d", "file");
	this->deck.push_back(card7);
}

void Deck::generateFourofKind()
{
	Card *card1 = new Card(5, "c", "file");
	this->deck.push_back(card1);

	Card *card2 = new Card(5, "d", "file");
	this->deck.push_back(card2);

	Card *card3 = new Card(6, "c", "file");
	this->deck.push_back(card3);

	Card *card4 = new Card(5, "h", "file");
	this->deck.push_back(card4);

	Card *card5 = new Card(4, "s", "file");
	this->deck.push_back(card5);

	Card *card6 = new Card(2, "h", "file");
	this->deck.push_back(card6);

	Card *card7 = new Card(5, "d", "file");
	this->deck.push_back(card7);
}

void Deck::generateStraightFlush()
{
	Card *card1 = new Card(5, "c", "file");
	this->deck.push_back(card1);

	Card *card2 = new Card(3, "c", "file");
	this->deck.push_back(card2);

	Card *card3 = new Card(6, "c", "file");
	this->deck.push_back(card3);

	Card *card4 = new Card(2, "c", "file");
	this->deck.push_back(card4);

	Card *card5 = new Card(4, "c", "file");
	this->deck.push_back(card5);

	Card *card6 = new Card(2, "h", "file");
	this->deck.push_back(card6);

	Card *card7 = new Card(6, "d", "file");
	this->deck.push_back(card7);
}

void Deck::generateRoyalFlush()
{
	Card *card1 = new Card(13, "d", "file");
	this->deck.push_back(card1);

	Card *card2 = new Card(10, "d", "file");
	this->deck.push_back(card2);

	Card *card3 = new Card(11, "d", "file");
	this->deck.push_back(card3);

	Card *card4 = new Card(14, "d", "file");
	this->deck.push_back(card4);

	Card *card5 = new Card(12, "d", "file");
	this->deck.push_back(card5);

	Card *card6 = new Card(11, "h", "file");
	this->deck.push_back(card6);

	Card *card7 = new Card(10, "c", "file");
	this->deck.push_back(card7);
}*/