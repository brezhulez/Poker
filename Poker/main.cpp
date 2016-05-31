#include "Game.h"

Game *poker;

GLvoid handle(GLvoid);
GLvoid display(GLvoid);
GLvoid resize(int width, int height);

/*void processSpecialKeys(int key, int x, int y) {
	switch (key) {
	case GLUT_KEY_F1:
		poker->giveCardPlayer();
		break;
	}
}
void timf(int value) // Timer function
{
	glutPostRedisplay();  // Redraw windows
	glutTimerFunc(40, timf, 0); // Setup next timer
}*/

int main(int argc, char **argv)
{
	FreeConsole();

	glutInit(&argc, argv); //инициализирует работу с графикой
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA); //выбор цветовой схемы и буферизацией
	glutCreateWindow("Покер"); //создает окно
	glutFullScreen();

	poker = new Game(50);
	poker->Init();
	poker->Blind();
	poker->giveCardPlayer();
	poker->firstCircle();
	poker->secondCircle();
	poker->thirdCircle();
	poker->fourthCircle();
	poker->winner();

	// регистрация
	glutDisplayFunc(display);
	glutReshapeFunc(resize);
	glutIdleFunc(handle);
	/*glutTimerFunc(40, timf, 0);

	glutSpecialFunc(processSpecialKeys);*/

	poker->Blind();

	glutMainLoop();
}

GLvoid handle(GLvoid) {
	//poker->draw();
	/*poker->firstCircle();
	poker->secondCircle();
	poker->thirdCircle();
	poker->fourthCircle();
	poker->winner();*/
}

GLvoid resize(int width, int height) {
	poker->resize(width, height);
}

GLvoid display(GLvoid) {
	poker->draw();
}