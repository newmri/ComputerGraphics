#include "CRect.h"

GLvoid Init(GLvoid);
GLvoid DrawScene(GLvoid);
GLvoid Reshape(int w, int h);
GLvoid Mouse(int button, int state, int x, int y);
GLvoid Animate(int n);

const int MAX_RECT_NUM = 10;
const unsigned int ANIMATION_TIME = 1000;
int idx = 0;

vector<CRect> vec;

void main(int argc, char* argv[])
{
	Init();
	glutCreateWindow("4.RectAnimation");
	glutDisplayFunc(DrawScene);
	glutReshapeFunc(Reshape);
	glutMouseFunc(Mouse);
	glutTimerFunc(ANIMATION_TIME, Animate, true);
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

	for (auto d : vec) d.Draw();
	glFlush(); // Draw
}

GLvoid Reshape(int w, int h)
{
	glViewport(0, 0, w, h);
	glOrtho(0, WINDOW_SIZE_WIDTH, WINDOW_SIZE_HEIGHT, 0, -1.0f,1.0f);
}

void Mouse(int button, int state, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
		if (vec.size() == 10) {
			vector<CRect>::iterator itor = vec.begin();
			itor = vec.erase(itor);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		}
		CRect rect;
		rect.SetPos(x, y);
		vec.push_back(rect);
		DrawScene();
	}
}

GLvoid Animate(int n)
{
	vector<CRect>::iterator itor = vec.begin();
	while (itor != vec.end()) {
		itor->ChangeColor();
		itor->ChangeShape();
		++itor;
	}
	glutPostRedisplay(); // Re draw
	glutTimerFunc(ANIMATION_TIME, Animate, true);
}