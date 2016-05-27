#include "Game.h"

Game *poker;

GLvoid handle(GLvoid);
GLvoid display(GLvoid);
GLvoid resize(int width, int height);

int main(int argc, char **argv)
{
	FreeConsole();

	glutInit(&argc, argv); //�������������� ������ � ��������
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA); //����� �������� ����� � ������������
	/*glutInitWindowSize(1200, 600); //������ ����
	glutInitWindowPosition(	//��������� ����
		(glutGet(GLUT_SCREEN_WIDTH) - 1200) / 2,
		(glutGet(GLUT_SCREEN_HEIGHT) - 600) / 2
	);//��������� ������ ��������� ���� �� ������ ������*/
	glutCreateWindow("�����"); //������� ����
	glutFullScreen();

	poker = new Game();
	poker->Init();

	// �����������
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