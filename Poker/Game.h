#pragma once

#include "Table.h"

class Game
{
protected:
	Table *table;
	GLfloat cardVertexArray[4][2];
	GLfloat cardTextureArray[4][2];
	GLubyte cardIndexArray[1][4];
	void initGL();
public:
	Game(int minRate);
	~Game();
	void Init();
	void Blind();
	void giveCardPlayer();
	void giveThreeCard();
	void giveOneCard();
	void draw();
	void resize(int width, int height);
	void playerStep();
	void firstCircle();
	void secondCircle();
	void thirdCircle();
	void fourthCircle();
	void winner();
	void displayText(float x, float y, float r, float g, float b, const char *string);
};

