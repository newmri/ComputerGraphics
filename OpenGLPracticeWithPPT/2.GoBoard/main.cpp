#include <gl/glut.h>
#include <time.h>
#include <stdlib.h>

GLvoid Init(GLvoid);
GLvoid DrawScene(GLvoid);
GLvoid Reshape(int w, int h);

const float WINDOW_SIZE_WIDTH = 800.0f;
const float WINDOW_SIZE_HEIGHT = 600.0f;
const float RGB = 255.0f;

const float TOP = WINDOW_SIZE_HEIGHT / 2;
const float BOTTOM = (WINDOW_SIZE_HEIGHT / 2) * -1;
const float LEFT = (WINDOW_SIZE_WIDTH / 2) * -1;
const float RIGHT = WINDOW_SIZE_WIDTH / 2;

const int MAX_RECT_NUM = 20;

void main(int argc, char* argv[])
{
	Init();
	glutCreateWindow("2.GoBoard");
	glutDisplayFunc(DrawScene);
	glutReshapeFunc(Reshape);
	glutMainLoop();
}


GLvoid Init(GLvoid)
{
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(WINDOW_SIZE_WIDTH, WINDOW_SIZE_HEIGHT);

	srand((unsigned int)time(NULL));
}

GLvoid DrawScene(GLvoid)
{
	int xNum = (rand () % MAX_RECT_NUM) + 1;
	int yNum = (rand() % MAX_RECT_NUM) + 1;

	float top = TOP;
	float bottom = top - (WINDOW_SIZE_HEIGHT / yNum);
	float left = LEFT;
	float right = left + (WINDOW_SIZE_WIDTH / xNum);

	for (int y = 0; bottom >= BOTTOM; ++y) {
		for (int x = 0; right <= RIGHT; ++x) {
			bool k = x % 2 == 0 == y % 2;
			if (x % 2 == 0 == y % 2)
				glColor4f(92.0f / RGB, 209.0f / RGB, 229.0f / RGB, 1.0f);
			else
				glColor4f(47.0f / RGB, 157.0f / RGB, 39.0f / RGB, 1.0f);

			glRectf(left, top, right, bottom);
			left = right;
			right = left + (WINDOW_SIZE_WIDTH / xNum);
		}
		left = LEFT;
		right = left + (WINDOW_SIZE_WIDTH / xNum);
		top = bottom;
		bottom = top - (WINDOW_SIZE_HEIGHT / yNum);
	}

	

	glFlush(); // Draw
}

GLvoid Reshape(int w, int h)
{
	glViewport(0, 0, w, h);
	glOrtho((WINDOW_SIZE_WIDTH / 2) * -1, WINDOW_SIZE_WIDTH / 2,
		(WINDOW_SIZE_HEIGHT / 2) * -1, WINDOW_SIZE_HEIGHT / 2, -1.0f, 1.0f);
}

