#include "define.h"
#include "CConsle.h"

GLvoid Init(GLvoid);
GLvoid DrawScene(GLvoid);
GLvoid Reshape(int w, int h);
void KeyBoard(unsigned char key, int x, int y);

CConsole g_console;

void main(int argc, char* argv[])
{

	Init();
	glutCreateWindow("Console");
	glutDisplayFunc(DrawScene);
	glutReshapeFunc(Reshape);
	glutKeyboardFunc(KeyBoard);
	glutMainLoop();
}


GLvoid Init(GLvoid)
{
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(WINDOWS_WIDTH, WINDOWS_HEIGHT);

}

GLvoid DrawScene(GLvoid)
{
	glClearColor(1.0f, 1.0f, 1.0f, 0.5f);
	glClear(GL_COLOR_BUFFER_BIT); // Fill Background

	g_console.Render();
	glFlush(); // Draw
}

GLvoid Reshape(int w, int h)
{
	glViewport(0, 0, w, h); // Change viewport with window size
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0, w, h, 0, -1.0f, 1.0f);
}


void KeyBoard(unsigned char key, int x, int y)
{
}
