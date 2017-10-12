#include "Define.h"
#include "Polygons.h"

GLvoid Init(GLvoid);
GLvoid DrawScene(GLvoid);
GLvoid Reshape(int w, int h);

GLvoid DrawCrossStrips(GLvoid);

vector<unique_ptr<CPolygon>> vec;


void main(int argc, char* argv[])
{
	Init();
	glutCreateWindow("3.Polygons");
	glutDisplayFunc(DrawScene);
	glutReshapeFunc(Reshape);
	glutMainLoop();
}


GLvoid Init(GLvoid)
{
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);

	srand((unsigned int)time(NULL));
	int shape = rand() % SHAPE::END;
	for (int y = 0; y < CROSS_Y_NUM; ++y) {
		for (int x = 0; x < CROSS_X_NUM; ++x) {
			vec.push_back(FACTPRYMANAGER->CreateObj(static_cast<SHAPE>(shape), (CROSS_DRAW_X * x) + 10,
				(CROSS_DRAW_Y * y) + (CROSS_DRAW_Y / 2)));
			if (shape < SHAPE::PENTAGON) ++shape;
			else shape = SHAPE::LINE;
		}

	}
	


}

GLvoid DrawScene(GLvoid)
{
	glBegin(GL_LINES);
		DrawCrossStrips();
	glEnd();

	for (auto& d : vec) d->Render();

	glFlush(); // Draw
}

GLvoid Reshape(int w, int h)
{
	glViewport(0, 0, w, h);
	glOrtho(0, WINDOW_WIDTH, WINDOW_HEIGHT, 0, -1.0f, 1.0f);
}

GLvoid DrawCrossStrips(GLvoid)
{
	for (int i = 1; i < CROSS_X_NUM; ++i) {
		// Horizontal Lines
		glVertex2f(0.0f, CROSS_DRAW_Y * i);
		glVertex2f(WINDOW_WIDTH, CROSS_DRAW_Y * i);

	}

	for (int i = 1; i < CROSS_Y_NUM; ++i) {
		// Vertical Lines
		glVertex2f(CROSS_DRAW_X * i, 0.0f);
		glVertex2f(CROSS_DRAW_X * i, WINDOW_HEIGHT);
	}
}

