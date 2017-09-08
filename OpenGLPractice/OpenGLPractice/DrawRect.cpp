#include <iostream>
#include <gl\glut.h>

void drawScene();

int main()
{
	// Init functions
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA); // Set display mode
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(500, 500);
	glutCreateWindow("Rect");
	glutDisplayFunc(drawScene);

	glutMainLoop();
	return 0;
}

void drawScene()
{
	glClearColor(0.0f, 0.0f, 1.0f, 1.0f); // BLUE
	glClear(GL_COLOR_BUFFER_BIT); // Fill the background in blue color
	glColor4f(0.01, 1.0f, 0.0f, 1.0f); // Set green color
	glRectf(-0.5f, -0.5f, 0.5f, 0.5f);
	glFlush(); // Draw on screen
}

