#pragma once

#include <GL/glut.h>
#include <gl\GLAux.h>
#include "Table.h"

class Game
{
protected:
	Table *table;
	GLuint textureCards[52];
	GLfloat triangleVertexArray[3][3];
	GLfloat triangleColorArray[3][3];
	GLubyte triangleIndexArray[1][3];
	void initGL();
public:
	Game();
	~Game();
	void Init();
	void Blind();
	void draw();
	void resize(int width, int height);
	void LoadGLTextures();
};

