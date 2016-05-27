#pragma once

#include <windows.h>
#include <GL/glut.h>
#include <SOIL.h>
#include "Table.h"

class Game
{
protected:
	Table *table;
	GLuint textureCards[52];
	GLfloat cardVertexArray[4][2];
	GLfloat cardTextureArray[4][2];
	GLubyte cardIndexArray[1][4];
	void initGL();
	void generateTextures();
public:
	Game();
	~Game();
	void Init();
	void Blind();
	void draw();
	void resize(int width, int height);
};

