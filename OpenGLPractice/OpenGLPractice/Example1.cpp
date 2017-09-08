#include <iostream>
#include <gl\glut.h>

void drawScene();

int main()
{
	// Init functions
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA); // Set display mode
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(500, 500);
	glutCreateWindow("Example1");
	glutDisplayFunc(drawScene);

	glutMainLoop();
	return 0;
}

void drawScene()
{
	glClearColor(0.0f, 0.0f, 1.0f, 1.0f); // BLUE
	glClear(GL_COLOR_BUFFER_BIT); // Fill the background in blue color
	glFlush(); // Draw on screen
}

