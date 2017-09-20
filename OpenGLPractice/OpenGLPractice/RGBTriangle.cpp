#include <iostream>
#include <gl/glut.h>

void SetUpRC();
void RenderScene();
void ReshapeScene(int w, int h);
void OnTimer(int id);

float g_fAngle = 0;

int main()
{
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA); // Set display mode
	glutInitWindowPosition(100, 100); // Set window position
	glutInitWindowSize(500, 500); // Set window size
	glutCreateWindow("RGBTriangle"); // Create window
	glutDisplayFunc(RenderScene); // Set render func
	glutReshapeFunc(ReshapeScene); // Change window size func

	SetUpRC();
	glutMainLoop();

	return 0;
}

void SetUpRC()
{
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // Set background in black
	glShadeModel(GL_SMOOTH);
	glFrontFace(GL_CW);

}

void ReshapeScene(int w, int h)
{
	float fRange = 100.0f;

	glViewport(0, 0, w, h); // Change viewport with window size
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	if (w <= h) glOrtho(-fRange, fRange, -fRange * h / w, fRange * h / w, -fRange, fRange);
	else glOrtho(-fRange * w / h, fRange * w / h, -fRange, fRange, -fRange, fRange);

}

void RenderScene()
{
	glClear(GL_COLOR_BUFFER_BIT);			// Fill background

	glMatrixMode(GL_MODELVIEW);				// Init matrix
	glLoadIdentity();

	glBegin(GL_TRIANGLES);					// Draw triangle
	glColor3ub(255, 0, 0);				// Red
	glVertex3f(0.0f, 70.0f, 0.0f);
	glColor3ub(0, 255, 0);				// Green
	glVertex3f(70.0f, -30.0f, 0.0f);
	glColor3ub(0, 0, 255);				// Blue
	glVertex3f(-70.0f, -30.0f, 0.0f);
	glEnd();


	glFlush();								// Draw
}

void OnTimer(int id)
{
	g_fAngle += 1.0f;
	glutPostRedisplay();
}