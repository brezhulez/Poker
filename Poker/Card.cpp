#include "Card.h"

GLuint Card::shirtCard;

Card::Card(int value, const char* suit, const char* fileName)
{
	this->value = value;
	this->suit = suit;

	glGenTextures(1, &this->textureCard);  // выделение памяти для текстуры
	this->textureCard =SOIL_load_OGL_texture // загрузка изображения в память
	(
		fileName,
		SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_MIPMAPS
	);
	glBindTexture(GL_TEXTURE_2D, this->textureCard);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
}

GLuint Card::getTextureCard()
{
	return this->textureCard;
}

int Card::getValue()
{
	return this->value;
}

const char* Card::getSuit()
{
	return this->suit;
}

Card::~Card()
{
}