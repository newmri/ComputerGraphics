
#include <iostream>
#include <gl/glut.h>
#include "OpenGL.h"

COpenGL *openGL = NULL;

void Display();
void Reshape(int width, int height);
void MouseButton(int button, int state, int x, int y);
void MouseMove(int x, int y);
void Menu(int num);

int main()
{
	// �ʱ�ȭ �Լ���
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);	// ���÷��� ��� ����
	glutInitWindowPosition(100, 100);				// �������� ��ġ ����
	glutInitWindowSize(500, 500);					// �������� ũ�� ����
	glutCreateWindow("OpenGL Project");					// ������ ���� (������ �̸�)
	glutDisplayFunc(Display);					// ��� �Լ��� ����
	glutReshapeFunc(Reshape);					// ������ũ�⺯���Լ��� ����
	glutMouseFunc(MouseButton);					// ���콺 ��ư �Լ� ����
	glutMotionFunc(MouseMove);					// ���콺 �̵� �Լ� ����
 
	int submenu_id = glutCreateMenu(Menu);
	
	glutAddMenuEntry("Open/Close the first drawer", 1);
	glutAddMenuEntry("Open/Close the second drawer", 2);
	glutAddMenuEntry("Turn On/Off the red light", 3);
	glutAddMenuEntry("Turn On/Off the green light", 4);
	glutAddMenuEntry("Turn On/Off the blue light", 5);
	glutAttachMenu(GLUT_RIGHT_BUTTON);

	openGL = new COpenGL();

	openGL->Init();

	glutMainLoop();

	openGL->Release();

	delete openGL;

	return 0;
}

void OnTimer(int id)
{
	glutPostRedisplay();

	openGL->MoveStatusDrawerPart1();
	openGL->MoveStatusDrawerPart2();
}

void Reshape(int width, int height)
{
	openGL->Resize(width, height);
}


void Display()
{
	openGL->Draw();
	
	glutTimerFunc(50, OnTimer, 1);
}

void MouseButton(int button, int state, int x, int y)
{
	// ���� ��ư�� ������ ��
	if (button == GLUT_LEFT_BUTTON) {
		if (state == GLUT_DOWN) {
			openGL->SetLButtonStatus(TRUE);
			openGL->StartMouseMove(x, y);
		} else {
			openGL->SetLButtonStatus(FALSE);
		}
	// ��� ��ư�� ������ ��
	} else if (button == GLUT_MIDDLE_BUTTON) {
		if (state == GLUT_DOWN) {
			openGL->SetMButtonStatus(TRUE);
			openGL->StartMouseMove(x, y);
		} else {
			openGL->SetMButtonStatus(FALSE);
		}
	}
}

void MouseMove(int x, int y)
{
	openGL->DoMouseMove(x, y);
}

void Menu(int num)
{
	switch (num) {
	case 1: 
		openGL->SetStatusDrawerPart1();
		break;
	case 2:
		openGL->SetStatusDrawerPart2();
		break;
	case 3:
		openGL->TurnRed();
		break;
	case 4:
		openGL->TurnGreen();
		break;
	case 5:
		openGL->TurnBlue();
		break;
	}
}
