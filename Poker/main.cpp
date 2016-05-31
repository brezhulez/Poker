#include "Game.h"

Game *poker;

GLvoid handle(GLvoid);
GLvoid display(GLvoid);
GLvoid resize(int width, int height);

int main(int argc, char **argv)
{
	FreeConsole();

	/*glutInit(&argc, argv); //инициализирует работу с графикой
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA); //выбор цветовой схемы и буферизацией
	glutCreateWindow("Покер"); //создает окно
	glutFullScreen();*/

	poker = new Game(50);
	poker->Init();
	poker->Blind();
	poker->firstCircle();
	poker->secondCircle();
	poker->thirdCircle();
	poker->fourthCircle();
	poker->winner();

	std::cin.get();

	// регистрация
	/*glutDisplayFunc(display);
	glutReshapeFunc(resize);
	glutIdleFunc(handle);

	glutMainLoop();*/
}

GLvoid handle(GLvoid) {
	
}

GLvoid resize(int width, int height) {
	poker->resize(width, height);
}

GLvoid display(GLvoid) {
	poker->draw();
}