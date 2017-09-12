#include <gl/glut.h>
GLvoid DrawScene(GLvoid);
GLvoid Reshape(int w, int h);

const int WINDOW_SIZE_WIDTH = 800;
const int WINDOW_SIZE_HEIGHT = 600;
const float RGB = 255.0f;

void main(int argc, char* argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(WINDOW_SIZE_WIDTH, WINDOW_SIZE_HEIGHT);
	glutCreateWindow("1.DrawRect");
	glutDisplayFunc(DrawScene);
	glutReshapeFunc(Reshape);
	glutMainLoop();
}

GLvoid DrawScene(GLvoid)
{
	glClearColor(0.0f, 0.0f, 1.0f, 1.0f); // Set background color in blue
	glClear(GL_COLOR_BUFFER_BIT); // Fill Background
	// Mid
	glColor4f(92.0f / RGB, 209.0f / RGB, 229.0f / RGB, 1.0f);
	glRectf(-0.2f, -0.2f, 0.3f, 0.2f);
	// Left Top
	glColor4f(0.0f, 130.0f / RGB, 153.0f / RGB, 1.0f);
	glRectf(-1.0f, 1.0f, -0.5f, 0.6f);
	// Left Bottom
	glColor4f(204.0f / RGB, 61.0f / RGB, 61.0f / RGB, 1.0f);
	glRectf(-1.0f, -0.5f, -0.5f, -1.0f);
	// Right Top
	glColor4f(29.0f / RGB, 219.0f / RGB, 22.0f / RGB, 1.0f);
	glRectf(0.5f, 1.0f, 1.0f, 0.6f);
	// Right Bottom
	glColor4f(47.0f / RGB, 157.0f / RGB, 39.0f / RGB, 1.0f);
	glRectf(0.5f, -0.5f, 1.0f, -1.0f);
	glFlush(); // Draw
}

GLvoid Reshape(int w, int h)
{
	glViewport(0, 0, w, h);
}

