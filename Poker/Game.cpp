#include "Game.h"



Game::Game(int minRate)
{
	this->table = new Table(minRate);
	this->cardHands = false;
	this->firstCircleFlag = false;
	this->secondCircleFlag = true;
	this->thirdCircleFlag = true;
	this->fourthCircleFlag = true;
	gameEnd = false;
	currentCircle = 0;
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

	this->displayText(0.65, -0.5, 0.5, 0.5, 0.5, "F1 - Call");
	this->displayText(0.65, -0.55, 0.5, 0.5, 0.5, "F2 - Raise x 2");
	this->displayText(0.65, -0.60, 0.5, 0.5, 0.5, "F3 - Raise x 3");
	this->displayText(0.65, -0.65, 0.5, 0.5, 0.5, "F4 - Check");
	this->displayText(0.65, -0.70, 0.5, 0.5, 0.5, "F5 - Fold");
	this->displayText(0.65, -0.75, 0.5, 0.5, 0.5, "F6 - AllIn");

	if (this->gameEnd == true) {
		Player *player;
		int combination = 0;
		for (int i = 0; i < table->getQueue().size(); i++)
		{
			if (table->getQueue().front()->getActive() == true)
			{
				if (combination < table->getQueue().front()->getCombination())
				{
					player = table->getQueue().front();
					combination = table->getQueue().front()->getCombination();
				}
			}
			table->nextPlayerDraw();
		}

		std::string winner = "Winner: " + player->getName();
		this->displayText(-0.8, -0.6, 0.5, 0.5, 0.5, winner.c_str());

		std::string comb = "Combination: " + table->getCombinationName(combination);
		this->displayText(-0.8, -0.75, 0.5, 0.5, 0.5, comb.c_str());
	}
	
	this->displayText(0.61, 0.25, 0.5, 0.5, 0.5, "Deck");
	std::string bank = "Bank: " + std::to_string(table->getCashRound());
	this->displayText(0.31, -0.07, 0.5, 0.5, 0.5, bank.c_str());

	std::string lastRate = "Last rate: " + std::to_string(table->getLastRate());
	this->displayText(0.31, -0.25, 0.5, 0.5, 0.5, lastRate.c_str());

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
	for (int i = 0; i < table->getQueue().size(); i++)
	{
		float x = table->getQueue().front()->getX();
		float y = table->getQueue().front()->getY();
		this->displayText(x, y + 0.55, 0.5, 0.5, 0.5, table->getQueue().front()->getName().c_str());
		std::string cash = "Cash: " + std::to_string(table->getQueue().front()->getCash());
		
		this->displayText(x + 0.225, y + 0.55, 0.5, 0.5, 0.5, cash.c_str());
		
		std::string turn = table->getQueue().front()->getTurn();

		this->displayText(x + 0.225, y - 0.05, 0.5, 0.5, 0.5, turn.c_str());

		if (table->getQueue().front()->getDealler() == true) 
			this->displayText(x, y - 0.05, 0.5, 0.5, 0.5, "Dealler");
		if (!table->getQueue().front()->getDeck()->isEmpty()) {
			for (int j = 0; j < table->getQueue().front()->getDeck()->getSize(); j++) {
				if (this->gameEnd == false) {
					if (table->getQueue().front()->getMan() == true) {
						Card *card = table->getQueue().front()->getDeck()->showCard(j);
						glBindTexture(GL_TEXTURE_2D, card->getTextureCard());
					}
					else glBindTexture(GL_TEXTURE_2D, Card::shirtCard);
				}
				else{				
					Card *card = table->getQueue().front()->getDeck()->showCard(j);
					glBindTexture(GL_TEXTURE_2D, card->getTextureCard());
				}
				

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
		table->nextPlayerDraw();
	}

	//отрисовываем карты на столе
	if (!table->getTableDeck()->isEmpty()) {
		float x = -0.98;
		float y = -0.3;
		for (int i = 0; i < table->getTableDeck()->getSize(); i++)
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

void Game::giveCardPlayer()
{
	for (int i = 0; i < table->getQueue().size() * 2; i++)
	{
		Card *card = table->getMainDeck()->getCard();
		table->getQueue().front()->addCard(card);
		table->nextPlayer();
		Sleep(400);
		this->draw();
	}
	this->cardHands = true;
	table->nextPlayer();
	table->nextPlayer();
	table->nextPlayer();
}

void Game::giveThreeCard()
{
	for (int i = 0; i < 3; i++)
	{
		Card *card = table->getMainDeck()->getCard();
		table->getTableDeck()->addCard(card);
		this->draw();
		Sleep(800);
	}
}

void Game::giveOneCard()
{
	Card *card = table->getMainDeck()->getCard();
	table->getTableDeck()->addCard(card);
	this->draw();
	Sleep(800);
}

void Game::playerStep(std::string step)
{
	if(step=="Call") table->Call();
	else if (step == "Check") table->Check();
	else if (step == "Raise x 2") table->Raise(table->getLastRate() * 2);
	else if (step == "Raise x 3") table->Raise(table->getLastRate() * 3);
	else if (step == "Fold") table->Fold();
	else if (step == "AllIn") table->allIn();
}

void Game::Blind()
{
	table->doingRate(table->getMinRate() / 2);
	table->getQueue().front()->setTurn("Blind/2");
	table->nextPlayer();
	Sleep(1500);
	this->draw();

	table->doingRate(table->getMinRate());
	table->getQueue().front()->setTurn("Blind");
	table->nextPlayer();

	Sleep(1500);
	this->draw();

	this->toDealler();
}
std::string Game::logicComp()
{
	Card *card1, *card2;
	card1 = table->getQueue().front()->getDeck()->showCard(0);
	card2 = table->getQueue().front()->getDeck()->showCard(1);

	if (table->getQueue().front()->getTurn() != "" && table->getQueue().front()->getTurn() != "Call") return "Call";

	if (table->getTableDeck()->isEmpty()) {
		if (card1->getValue() == 14 && card2->getValue() == 13 ||
			card1->getValue() == 13 && card2->getValue() == 14) {
			return "Raise x 2";
		}
		else if (card1->getValue() == 13 && card2->getValue() == 12 ||
			card1->getValue() == 12 && card2->getValue() == 13) {
			return "Raise x 2";
		}
		else if (card1->getValue() == 12 && card2->getValue() == 11 ||
			card1->getValue() == 11 && card2->getValue() == 12) {
			return "Raise x 2";
		}
		else if (card1->getValue() == 11 && card2->getValue() == 10 ||
			card1->getValue() == 10 && card2->getValue() == 11) {
			return "Raise x 2";
		}
		else if (card1->getSuit() == card2->getSuit()) {
			return "Raise x 2";
		}
		else if (card1->getValue() == card2->getValue()) {
			return "Call";
		}
		else if (card1->getValue() < 7 && card2->getValue() < 7) {
			return "Fold";
		}
		else return "Call";
	}
	else {
		Card *card3 = table->getTableDeck()->showCard(0);
		if (card1->getSuit() == card2->getSuit() && card2->getSuit() == card3->getSuit()) {
			return "Raise x 2";
		}
		else if (card1->getValue() < 7 && card2->getValue() < 7 && card3->getValue() < 7) {
			return "Fold";
		}
		else return "Call";
	}
}
void Game::firstCircle()
{
	currentCircle = 1;
	while (table->getEndCircle() == false)
	{
		if (table->getQueue().front()->getMan()) {
			this->secondCircleFlag = true;
			return;
		}

		playerStep(logicComp());
		table->checkTurn();
		this->draw();
		Sleep(1500);
	}
	table->clearTurn();
	this->firstCircleFlag = true;
	this->secondCircleFlag = false;
	this->toDealler();
	table->nextPlayer();
	this->giveThreeCard();
}

void Game::secondCircle()
{
	currentCircle = 2;
	while (table->getEndCircle() == false)
	{
		if (table->getQueue().front()->getMan()) {
			this->secondCircleFlag = true;
			return;
		}
		playerStep(logicComp());
		table->checkTurn();
		this->draw();
		Sleep(1500);
	}
	table->clearTurn();
	this->secondCircleFlag = true;
	this->thirdCircleFlag = false;
	this->toDealler();
	table->nextPlayer();
	this->giveOneCard();
}

void Game::thirdCircle()
{
	currentCircle = 3;
	while (table->getEndCircle() == false)
	{
		if (table->getQueue().front()->getMan()) {
			this->thirdCircleFlag = true;
			return;
		}
		playerStep(logicComp());
		table->checkTurn();
		this->draw();
		Sleep(1500);
	}
	table->clearTurn();
	this->thirdCircleFlag = true;
	this->fourthCircleFlag = false;
	this->toDealler();
	table->nextPlayer();
	this->giveOneCard();
}

void Game::fourthCircle()
{
	currentCircle = 4;
	while (table->getEndCircle() == false)
	{
		if (table->getQueue().front()->getMan()) {
			this->fourthCircleFlag = true;
			return;
		}
		playerStep(logicComp());
		table->checkTurn();
		this->draw();
		Sleep(1500);
	}
	table->clearTurn();
	this->fourthCircleFlag = true;
	this->gameEnd = true;
	this->toDealler();
	table->nextPlayer();
}

void Game::winner()
{
	table->combination();
	this->gameEnd = true;
}

bool Game::getCardHands()
{
	return this->cardHands;
}

void Game::toDealler()
{
	while (!table->getQueue().front()->getDealler())
	{
		table->nextPlayerDraw();
	}
}

bool Game::getFirstCircle()
{
	return this->firstCircleFlag;
}
bool Game::getSecondCircle()
{
	return this->secondCircleFlag;
}
bool Game::getThirdCircle()
{
	return this->thirdCircleFlag;
}
bool Game::getFourthCircle()
{
	return this->fourthCircleFlag;
}
void Game::setFirstCircle(bool flag)
{
	this->firstCircleFlag = flag;
}
void Game::setSecondCircle(bool flag)
{
	this->secondCircleFlag = flag;
}
void Game::setThirdCircle(bool flag)
{
	this->thirdCircleFlag = flag;
}
void Game::setFourthCircle(bool flag)
{
	this->fourthCircleFlag = flag;
}
int Game::getCurrentCircle()
{
	return this->currentCircle;
}
bool Game::getGameEnd()
{
	return this->gameEnd;
}