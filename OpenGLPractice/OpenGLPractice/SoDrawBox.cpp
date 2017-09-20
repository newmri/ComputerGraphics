#include <iostream>
#include <gl/glut.h>

void SetUpRC();
void RenderScene();
void ReshapeScene(int w, int h);

int main()
{
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA); // Set display mode
	glutInitWindowPosition(100, 100); // Set window position
	glutInitWindowSize(500, 500); // Set window size
	glutCreateWindow("DrawBox"); // Create window
	glutDisplayFunc(RenderScene); // Set render func
	glutReshapeFunc(ReshapeScene); // Change window size func

	SetUpRC();
	glutMainLoop();

	return 0;
}

void SetUpRC()
{
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // Set background in black
	glShadeModel(GL_FLAT); // Flat rendering mode
	glFrontFace(GL_CCW); // CCW is front
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
	glClear(GL_COLOR_BUFFER_BIT); // Fill background
	glPolygonMode(GL_BACK, GL_LINE); // Back side is line

	glMatrixMode(GL_MODELVIEW); // Change to model view
	glLoadIdentity();

	glBegin(GL_TRIANGLE_STRIP);
	glColor3ub(0, 114, 188);
	glVertex3f(-25.0f, -25.0f, 0.0f);
	glVertex3f(25.0f, -25.0f, 0.0f);
	glVertex3f(-25.0f, 25.0f, 0.0f);
	glColor3ub(0, 52, 113);
	glVertex3f(25.0f, 25.0f, 0.0f);
	glEnd();

	glFlush(); // display
}