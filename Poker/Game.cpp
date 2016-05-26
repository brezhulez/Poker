#include "Game.h"



Game::Game()
{
	this->table = new Table();
}


Game::~Game()
{
}

void Game::initGL()
{
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_COLOR_ARRAY);

	this->LoadGLTextures();
	// Разрешение наложение текстуры
	glEnable(GL_TEXTURE_2D);
	// Устанавливается синий фон
	glClearColor(0.2f, 0.5f, 0.75f, 1.0f);
	// Устанавливается значение для заполнения буфера глубины по умолчанию
    glClearDepth(1.0f);
	// Устанавливается значение, используемое в сравнениях при использовании буфера глубины
	glDepthFunc(GL_LEQUAL);
	// Включается тест глубины
    glEnable(GL_DEPTH_TEST);
	// Включается плавное затенение
	glShadeModel(GL_SMOOTH);
}

void Game::resize(int width, int height)
{
	//учитывает деление на ноль если окно будет сильно перетянуто 
	if (height == 0) height = 1;
	float ratio = 1.0* width / height;
	
	//матрица проекции
	glMatrixMode(GL_PROJECTION);

	//Reset матрицы
	glLoadIdentity();

	//определение окна просмотра
	glViewport(0, 0, width, height);

	//установка корректной перспективы.
	/*gluPerspective(45, ratio, 1, 1000);*/

	//возврат к модели
	glMatrixMode(GL_MODELVIEW);
}

void Game::LoadGLTextures()
{
	AUX_RGBImageRec *texture1;
	texture1 = auxDIBImageLoad(TEXT("images/pu.bmp")); //загрузили изображение в память, как данные RGB

	// Создание текстуры
	glGenTextures(1, &textureCards[0]);
	glBindTexture(GL_TEXTURE_2D, textureCards[0]);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, texture1->sizeX, texture1->sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, texture1->data);
}

void Game::draw()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	triangleVertexArray[0][0] = 0.0;
	triangleVertexArray[0][1] = 0.0;
	triangleVertexArray[0][2] = 0.0;

	triangleVertexArray[1][0] = 1.0;
	triangleVertexArray[1][1] = 1.0;
	triangleVertexArray[1][2] = 0.0;

	triangleVertexArray[2][0] = 1.0;
	triangleVertexArray[2][1] = 0.0;
	triangleVertexArray[2][2] = 0.0;

	triangleColorArray[0][0] = 0.25;
	triangleColorArray[0][1] = 0.87;
	triangleColorArray[0][2] = 0.81;

	triangleColorArray[1][0] = 0.25;
	triangleColorArray[1][1] = 0.87;
	triangleColorArray[1][2] = 0.81;

	triangleColorArray[2][0] = 0.25;
	triangleColorArray[2][1] = 0.87;
	triangleColorArray[2][2] = 0.81;

	triangleIndexArray[0][0] = 0;
	triangleIndexArray[0][1] = 1;
	triangleIndexArray[0][2] = 2;

	glVertexPointer(3, GL_FLOAT, 0, triangleVertexArray);
	glColorPointer(3, GL_FLOAT, 0, triangleColorArray);
	glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_BYTE, triangleIndexArray);

	glutSwapBuffers();
}

void Game::Init()
{
	this->initGL();

	table->getMainDeck()->generateDeck();
	table->getMainDeck()->mixDeck();
	table->generateQueue();
	table->nextPlayer();
}

void Game::Blind()
{
	table->doingRate(table->getMinRate() / 2);
	table->nextPlayer();
	table->doingRate(table->getMinRate());
	table->nextPlayer();
}