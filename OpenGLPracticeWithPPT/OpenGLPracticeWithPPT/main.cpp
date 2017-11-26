#include <gl/glut.h>
GLvoid DrawScene(GLvoid);
GLvoid Reshape(int w, int h);

void main(int argc, char* argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(250, 250);
	glutCreateWindow("DrawShape");
	glutDisplayFunc(DrawScene);
	glutReshapeFunc(Reshape);
	glutMainLoop();
}

GLvoid DrawScene(GLvoid)
{
	glClearColor(0.0f, 0.0f, 1.0f, 1.0f); // Set background color in blue
	glClear(GL_COLOR_BUFFER_BIT); // Fill Background
	glColor4f(0.0f, 1.0f, 0.0f, 1.0f); // Set drawing color in green
	glRectf(-0.5f, -0.5f, 0.5f, 0.5f); // Draw rectangle
	glFlush(); // Draw
}

GLvoid Reshape(int w, int h)
{
	glViewport(0, 0, w, h);
}

