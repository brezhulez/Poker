#include <windows.h>
#include "Game.h"

Game *poker;

void handle(void);
void display(void);
void resize(int width, int height);

int main(int argc, char **argv)
{
	FreeConsole();

	glutInit(&argc, argv); //�������������� ������ � ��������
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA); //����� �������� ����� � ������������
	glutInitWindowSize(1200, 600); //������ ����
	glutInitWindowPosition(	//��������� ����
		(glutGet(GLUT_SCREEN_WIDTH) - 1200) / 2,
		(glutGet(GLUT_SCREEN_HEIGHT) - 600) / 2
	);//��������� ������ ��������� ���� �� ������ ������

	glutCreateWindow("�����"); //������� ����

	poker = new Game();
	poker->Init();

	// �����������
	glutDisplayFunc(display);
	glutReshapeFunc(resize);
	glutIdleFunc(handle);

	glutMainLoop();
}

void handle(void) {
	
}

void resize(int width, int height) {
	poker->resize(width, height);
}

void display(void) {
	poker->draw();
}