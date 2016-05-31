#pragma once
#include <iostream>
#include <windows.h>
#include <GL/glut.h>
#include <SOIL.h>

class Card
{
protected:
	int value;
	const char* suit;
	GLuint textureCard;
public:
	Card(int value, const char* suit, const char* fileName);
	GLuint getTextureCard();
	int getValue();
	const char* getSuit();
	~Card();
};

