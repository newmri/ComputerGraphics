#include <iostream>
#include <gl/glut.h>

void SetUpRC();
void RenderScene();
void ReshapeScene(int w, int h);
void RenderBitmapString(float x, float y, float z, void* font, char* str);

int main()
{
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA); // Set display mode
	glutInitWindowPosition(100, 100); // Set window position
	glutInitWindowSize(500, 500); // Set window size
	glutCreateWindow("PrintText"); // Create window
	glutDisplayFunc(RenderScene); // Set render func
	glutReshapeFunc(ReshapeScene); // Change window size func

	SetUpRC();
	glutMainLoop();

	return 0;
}

void SetUpRC()
{
	glClearColor(0.0f, 0.0f, 1.0f, 1.0f); // Set background in blue
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

	glMatrixMode(GL_MODELVIEW); // Change to model view
	glLoadIdentity();

	glColor3ub(255, 255, 0); // Yellow
	RenderBitmapString(-10.0f, 0.0f, 0.0f, GLUT_BITMAP_HELVETICA_18, "Hello World");

	glFlush(); // display
}

void RenderBitmapString(float x, float y, float z, void* font, char* str)
{
	char* c;
	glRasterPos3f(x, y, z);
	for (c = str; *c != '\0'; ++c) glutBitmapCharacter(font, *c);
}