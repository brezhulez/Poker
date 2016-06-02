#include "Game.h"

Game *poker;

GLvoid handle(GLvoid);
GLvoid display(GLvoid);
GLvoid resize(int width, int height);

void processSpecialKeys(int key, int x, int y) {
	switch (key) {
	case GLUT_KEY_F1:
		if (poker->getCurrentCircle() == 1) poker->setFirstCircle(false);
		else if (poker->getCurrentCircle() == 2) poker->setSecondCircle(false);
		else if (poker->getCurrentCircle() == 3) poker->setThirdCircle(false);
		else if (poker->getCurrentCircle() == 4) poker->setFourthCircle(false);
		poker->playerStep("Call");
		poker->draw();
		Sleep(1500);
		break;
	case GLUT_KEY_F2:
		if (poker->getCurrentCircle() == 1) poker->setFirstCircle(false);
		else if (poker->getCurrentCircle() == 2) poker->setSecondCircle(false);
		else if (poker->getCurrentCircle() == 3) poker->setThirdCircle(false);
		else if (poker->getCurrentCircle() == 4) poker->setFourthCircle(false);
		poker->playerStep("Raise x 2");
		poker->draw();
		Sleep(1500);
		break;
	case GLUT_KEY_F3:
		if (poker->getCurrentCircle() == 1) poker->setFirstCircle(false);
		else if (poker->getCurrentCircle() == 2) poker->setSecondCircle(false);
		else if (poker->getCurrentCircle() == 3) poker->setThirdCircle(false);
		else if (poker->getCurrentCircle() == 4) poker->setFourthCircle(false);
		poker->playerStep("Raise x 3");
		poker->draw();
		Sleep(1500);
		break;
	case GLUT_KEY_F4:
		if (poker->getCurrentCircle() == 1) poker->setFirstCircle(false);
		else if (poker->getCurrentCircle() == 2) poker->setSecondCircle(false);
		else if (poker->getCurrentCircle() == 3) poker->setThirdCircle(false);
		else if (poker->getCurrentCircle() == 4) poker->setFourthCircle(false);
		poker->playerStep("Check");
		poker->draw();
		Sleep(1500);
		break;
	case GLUT_KEY_F5:
		if (poker->getCurrentCircle() == 1) poker->setFirstCircle(false);
		else if (poker->getCurrentCircle() == 2) poker->setSecondCircle(false);
		else if (poker->getCurrentCircle() == 3) poker->setThirdCircle(false);
		else if (poker->getCurrentCircle() == 4) poker->setFourthCircle(false);
		poker->playerStep("Fold");
		poker->draw();
		Sleep(1500);
		break;
	case GLUT_KEY_F6:
		if (poker->getCurrentCircle() == 1) poker->setFirstCircle(false);
		else if (poker->getCurrentCircle() == 2) poker->setSecondCircle(false);
		else if (poker->getCurrentCircle() == 3) poker->setThirdCircle(false);
		else if (poker->getCurrentCircle() == 4) poker->setFourthCircle(false);
		poker->playerStep("AllIn");
		poker->draw();
		Sleep(1500);
		break;
	}
}
void timf(int value) // Timer function
{
	glutPostRedisplay();  // Redraw windows
	glutTimerFunc(40, timf, 0); // Setup next timer
}

int main(int argc, char **argv)
{
	//FreeConsole();

	glutInit(&argc, argv); //инициализирует работу с графикой
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA); //выбор цветовой схемы и буферизацией
	glutCreateWindow("Покер"); //создает окно
	glutFullScreen();

	poker = new Game(50);
	poker->Init();

	// регистрация
	glutDisplayFunc(display);
	glutReshapeFunc(resize);
	glutIdleFunc(handle);
	glutTimerFunc(40, timf, 0);

	glutSpecialFunc(processSpecialKeys);

	glutMainLoop();
}

GLvoid handle(GLvoid) {
	if (!poker->getCardHands()) {
		poker->Blind();
		poker->giveCardPlayer();
	}
	if (!poker->getFirstCircle()) poker->firstCircle();
	else if (!poker->getSecondCircle()) poker->secondCircle();
	else if (!poker->getThirdCircle()) poker->thirdCircle();
	else if (!poker->getFourthCircle()) poker->fourthCircle();
	if(poker->getGameEnd()) poker->winner();
}

GLvoid resize(int width, int height) {
	poker->resize(width, height);
}

GLvoid display(GLvoid) {
	poker->draw();
}