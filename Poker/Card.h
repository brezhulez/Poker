#pragma once
#include <iostream>

class Card
{
protected:
	std::string value;
	char suit;
public:
	Card(std::string value, char suit);
	~Card();
};

