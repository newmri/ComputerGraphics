#include <gl/glut.h>
GLvoid DrawScene(GLvoid);
GLvoid Reshape(int w, int h);

GLint p1[2] = { 50,100 };
GLint p2[2] = { 75,150 };
GLint p3[2] = { 100,100 };

void main(int argc, char* argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(250, 250);
	glutCreateWindow("DrawPoints");
	glutDisplayFunc(DrawScene);
	glutReshapeFunc(Reshape);
	glutMainLoop();
}

GLvoid DrawScene(GLvoid)
{
	glClearColor(0.0f, 0.0f, 1.0f, 1.0f); // Set background color in blue
	glClear(GL_COLOR_BUFFER_BIT);
	glBegin(GL_POINTS);
	glColor4f(0.0f, 1.0f, 0.0f, 1.0f); // Set drawing color in green
	glVertex2f(0.0f, 0.0f);
	glEnd();
	glFlush(); // Draw
}

GLvoid Reshape(int w, int h)
{
	glViewport(0, 0, w, h);
}

