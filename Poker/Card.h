#pragma once
#include <iostream>
#include <windows.h>
#include <GL/glut.h>
#include <SOIL.h>

class Card
{
protected:
	std::string value;
	const char* suit;
	GLuint textureCard;
public:
	Card(std::string value, const char* suit, const char* fileName);
	GLuint getTextureCard();
	~Card();
};

