#include "Game.h"



Game::Game(int minRate)
{
	this->table = new Table(minRate);
}

Game::~Game()
{
}

void Game::initGL()
{
	this->generateTextures();
	// Разрешение наложение текстуры
	glEnable(GL_TEXTURE_2D);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	glEnableClientState(GL_VERTEX_ARRAY);
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

	//возврат к модели
	glMatrixMode(GL_MODELVIEW);
}

void Game::generateTextures()
{
	/*glGenTextures(52, textureCards);

	textureCards[0] = SOIL_load_OGL_texture
	(
		"images/orl001c10.jpg",
		SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_MIPMAPS
	);
	
	glBindTexture(GL_TEXTURE_2D, textureCards[0]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);*/
}

void Game::draw()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW);

	glLoadIdentity();

	//glBindTexture(GL_TEXTURE_2D, textureCards[0]);
	glBindTexture(GL_TEXTURE_2D, table->getMainDeck()->showCard()->getTextureCard());

	cardVertexArray[0][0] = 0.0;
	cardVertexArray[0][1] = 0.0;

	cardVertexArray[1][0] = 0.0;
	cardVertexArray[1][1] = 0.52;

	cardVertexArray[2][0] = 0.21;
	cardVertexArray[2][1] = 0.52;

	cardVertexArray[3][0] = 0.21;
	cardVertexArray[3][1] = 0.0;

	cardTextureArray[0][0] = 0.0;
	cardTextureArray[0][1] = 1.0;

	cardTextureArray[1][0] = 0.0;
	cardTextureArray[1][1] = 0.0;

	cardTextureArray[2][0] = 1.0;
	cardTextureArray[2][1] = 0.0;

	cardTextureArray[3][0] = 1.0;
	cardTextureArray[3][1] = 1.0;

	cardIndexArray[0][0] = 0;
	cardIndexArray[0][1] = 1;
	cardIndexArray[0][2] = 2;
	cardIndexArray[0][3] = 3;

	glVertexPointer(2, GL_FLOAT, 0, cardVertexArray);
	glTexCoordPointer(2, GL_FLOAT, 0, cardTextureArray);
	glDrawElements(GL_QUADS, 4, GL_UNSIGNED_BYTE, cardIndexArray);
	
	glutSwapBuffers();
	glutPostRedisplay();
}

void Game::Init()
{
	//this->initGL();

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

void Game::giveCard()
{
	for (int i = 0; i < table->getQueue().size() * 2; i++)
	{
		Card *card = table->getMainDeck()->getCard();
		table->getQueue().front()->addCard(card);
		table->nextPlayer();
	}
}

void Game::playerStep()
{
	table->Call();
}

void Game::firsCircle()
{
	while (table->getEndCircle() == false)
	{
		playerStep();
		table->checkTurn();
	}
}