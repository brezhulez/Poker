#pragma once

#include "Table.h"
#include <conio.h>

class Game
{
protected:
	Table *table;
	bool cardHands;
	bool firstCircleFlag;
	bool secondCircleFlag;
	bool thirdCircleFlag;
	bool fourthCircleFlag;
	int currentCircle;
	bool gameEnd;
	GLfloat cardVertexArray[4][2];
	GLfloat cardTextureArray[4][2];
	GLubyte cardIndexArray[1][4];
	void initGL();
	std::string logicComp();
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
	void playerStep(std::string step);
	void firstCircle();
	void secondCircle();
	void thirdCircle();
	void fourthCircle();
	void winner();
	void displayText(float x, float y, float r, float g, float b, const char *string);
	bool getCardHands();
	bool getFirstCircle();
	bool getSecondCircle();
	bool getThirdCircle();
	bool getFourthCircle();
	bool getGameEnd();
	int getCurrentCircle();
	void setFirstCircle(bool flag);
	void setSecondCircle(bool flag);
	void setThirdCircle(bool flag);
	void setFourthCircle(bool flag);
	void toDealler();
};

