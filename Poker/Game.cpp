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
	// –азрешение наложение текстуры
	glEnable(GL_TEXTURE_2D);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	glEnableClientState(GL_VERTEX_ARRAY);
	// ”станавливаетс€ синий фон
	glClearColor(0.2f, 0.5f, 0.75f, 1.0f);
	// ”станавливаетс€ значение дл€ заполнени€ буфера глубины по умолчанию
    glClearDepth(1.0f);
	// ”станавливаетс€ значение, используемое в сравнени€х при использовании буфера глубины
	glDepthFunc(GL_LEQUAL);
	// ¬ключаетс€ тест глубины
    glEnable(GL_DEPTH_TEST);
	// ¬ключаетс€ плавное затенение
	glShadeModel(GL_SMOOTH);

	//загрузка рубашки карты
	glGenTextures(1, &Card::shirtCard);
	Card::shirtCard = SOIL_load_OGL_texture
	(
		"images/shirt.jpg",
		SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_MIPMAPS
	);
	glBindTexture(GL_TEXTURE_2D, Card::shirtCard);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
}

void Game::resize(int width, int height)
{
	//учитывает деление на ноль если окно будет сильно перет€нуто 
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

void Game::displayText(float x, float y, float r, float g, float b, const char *string) {
	int j = strlen(string);

	glEnable(GL_LIGHTING);
	glColor3f(r, g, b);
	glRasterPos2f(x, y);
	for (int i = 0; i < j; i++) {
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, string[i]);
	}
	glDisable(GL_LIGHTING);
}

void Game::draw()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW);

	glLoadIdentity();

	//отрисовываем колоду
	glBindTexture(GL_TEXTURE_2D, Card::shirtCard);
	
	this->displayText(0.61, 0.25, 0.5, 0.5, 0.5, "Deck");
	std::string bank = "Bank: " + std::to_string(table->getCashRound());
	this->displayText(0.31, -0.07, 0.5, 0.5, 0.5, bank.c_str());

	cardVertexArray[0][0] = 0.55;
	cardVertexArray[0][1] = -0.3;

	cardVertexArray[1][0] = 0.55;
	cardVertexArray[1][1] = 0.22;

	cardVertexArray[2][0] = 0.76;
	cardVertexArray[2][1] = 0.22;

	cardVertexArray[3][0] = 0.76;
	cardVertexArray[3][1] = -0.3;

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

	//отрисовываем игроков
	float cardX = 0.22;
	int player = 1;
	for (int i = 0; i < table->getQueue().size(); i++)
	{
		float x = table->getQueue().front()->getX();
		float y = table->getQueue().front()->getY();
		if (table->getQueue().front()->getMan() == true) {
			this->displayText(x, y + 0.55, 0.5, 0.5, 0.5, "Player");
		}
		else {
			std::string name = "Enemy" + std::to_string(player);
			this->displayText(x, y + 0.55, 0.5, 0.5, 0.5, name.c_str());
			player++;
		}
		std::string cash = "Cash: " + std::to_string(table->getQueue().front()->getCash());
		this->displayText(x + 0.23, y + 0.55, 0.5, 0.5, 0.5, cash.c_str());
		if (!table->getQueue().front()->getDeck()->isEmpty()) {
			for (int j = 0; j < 2; j++) {
				if (table->getQueue().front()->getMan() == true) {
					Card *card = table->getQueue().front()->getDeck()->showCard(j);
					glBindTexture(GL_TEXTURE_2D, card->getTextureCard());
				}
				else glBindTexture(GL_TEXTURE_2D, Card::shirtCard);

				cardVertexArray[0][0] = x;
				cardVertexArray[0][1] = y;

				cardVertexArray[1][0] = x;
				cardVertexArray[1][1] = y + 0.52;

				cardVertexArray[2][0] = x + 0.21;
				cardVertexArray[2][1] = y + 0.52;

				cardVertexArray[3][0] = x + 0.21;
				cardVertexArray[3][1] = y;

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
				x += cardX;
			}
		}
		table->nextPlayer();
	}

	//отрисовываем карты на столе
	if (!table->getTableDeck()->isEmpty()) {
		float x = -0.98;
		float y = -0.3;
		for (int i = 0; i < 5; i++)
		{
			Card *card = table->getTableDeck()->showCard(i);
			glBindTexture(GL_TEXTURE_2D, card->getTextureCard());

			cardVertexArray[0][0] = x;
			cardVertexArray[0][1] = y;

			cardVertexArray[1][0] = x;
			cardVertexArray[1][1] = y + 0.52;

			cardVertexArray[2][0] = x + 0.21;
			cardVertexArray[2][1] = y + 0.52;

			cardVertexArray[3][0] = x + 0.21;
			cardVertexArray[3][1] = y;

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
			x += cardX;
		}
	}
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

void Game::giveCardPlayer()
{
	for (int i = 0; i < table->getQueue().size() * 2; i++)
	{
		Card *card = table->getMainDeck()->getCard();
		table->getQueue().front()->addCard(card);
		table->nextPlayer();
	}
}

void Game::giveThreeCard()
{
	for (int i = 0; i < 3; i++)
	{
		Card *card = table->getMainDeck()->getCard();
		table->getTableDeck()->addCard(card);
	}
}

void Game::giveOneCard()
{
	Card *card = table->getMainDeck()->getCard();
	table->getTableDeck()->addCard(card);
}

void Game::playerStep()
{
	table->Call();
}

void Game::firstCircle()
{
	while (table->getEndCircle() == false)
	{
		playerStep();
		table->checkTurn();
	}
	table->clearTurn();
}

void Game::secondCircle()
{
	this->giveThreeCard();
	while (table->getEndCircle() == false)
	{
		playerStep();
		table->checkTurn();
	}
	table->clearTurn();
}

void Game::thirdCircle()
{
	this->giveOneCard();
	while (table->getEndCircle() == false)
	{
		playerStep();
		table->checkTurn();
	}
	table->clearTurn();
}

void Game::fourthCircle()
{
	this->giveOneCard();
	while (table->getEndCircle() == false)
	{
		playerStep();
		table->checkTurn();
	}
	table->clearTurn();
}

void Game::winner()
{
	table->combination();
}