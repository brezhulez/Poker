#include "Game.h"

Game *poker;

GLvoid handle(GLvoid);
GLvoid display(GLvoid);
GLvoid resize(int width, int height);

int main(int argc, char **argv)
{
	FreeConsole();

	glutInit(&argc, argv); //инициализирует работу с графикой
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA); //выбор цветовой схемы и буферизацией
	/*glutInitWindowSize(1200, 600); //размер окна
	glutInitWindowPosition(	//положение окна
		(glutGet(GLUT_SCREEN_WIDTH) - 1200) / 2,
		(glutGet(GLUT_SCREEN_HEIGHT) - 600) / 2
	);//аргументы задают положение окна по центру экрана*/
	glutCreateWindow("Покер"); //создает окно
	glutFullScreen();

	poker = new Game();
	poker->Init();

	// регистрация
	glutDisplayFunc(display);
	glutReshapeFunc(resize);
	glutIdleFunc(handle);

	glutMainLoop();
}

GLvoid handle(GLvoid) {
	
}

GLvoid resize(int width, int height) {
	poker->resize(width, height);
}

GLvoid display(GLvoid) {
	poker->draw();
}