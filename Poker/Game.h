#pragma once

#include "Table.h"

class Game
{
protected:
	Table *table;
	//GLuint textureCards[52];
	GLfloat cardVertexArray[4][2];
	GLfloat cardTextureArray[4][2];
	GLubyte cardIndexArray[1][4];
	void initGL();
	void generateTextures();
public:
	Game(int minRate);
	~Game();
	void Init();
	void Blind();
	void giveCard();
	void draw();
	void resize(int width, int height);
	void playerStep();
};

