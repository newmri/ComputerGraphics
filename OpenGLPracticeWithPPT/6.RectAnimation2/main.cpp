#include "CRect.h"

GLvoid Init(GLvoid);
GLvoid DrawScene(GLvoid);
GLvoid Reshape(int w, int h);
GLvoid Mouse(int button, int state, int x, int y);
GLvoid Animate(int n);
GLvoid CreateRect(int n);
GLvoid SpecialKeyBoard(int key, int x, int y);

const int MAX_RECT_NUM = 10;
const unsigned int ANIMATION_TIME = 1000/ 30;
const unsigned int RECT_CREATION_TIME = 2000;

const unsigned int SPEED_UP = 1;
const unsigned int SPEED_DOWN = -1;

vector<CRect> vec;
int idx = 1;
bool g_moveAll = false;

void main(int argc, char* argv[])
{
	Init();
	glutCreateWindow("6.RectAnimation2");
	glutDisplayFunc(DrawScene);
	glutReshapeFunc(Reshape);
	glutMouseFunc(Mouse);
	glutTimerFunc(ANIMATION_TIME, Animate, true);
	glutTimerFunc(RECT_CREATION_TIME, CreateRect, true);
	glutMouseFunc(Mouse);
	glutSpecialFunc(SpecialKeyBoard);
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


GLvoid Animate(int n)
{
	if (g_moveAll) {
		if (vec.size() != 0) {
			if (vec[idx - 1].GetStoped() && vec.size() >= idx + 1) ++idx;
			vec[idx - 1].ChangeColor();
			vec[idx - 1].Move();
		}
	}
	glutPostRedisplay(); // Re draw
	glutTimerFunc(ANIMATION_TIME, Animate, true);
}

GLvoid CreateRect(int n)
{
	vec.emplace_back(CRect());
	if (vec.size() < MAX_RECT_NUM) glutTimerFunc(RECT_CREATION_TIME, CreateRect, true);
	
}

GLvoid Mouse(int button, int state, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) g_moveAll = !g_moveAll;	
}

GLvoid SpecialKeyBoard(int key, int x, int y)
{

	if (key == GLUT_KEY_UP) vec[idx - 1].ChangeSpeed(SPEED_UP);

	else if (key == GLUT_KEY_DOWN) vec[idx - 1].ChangeSpeed(SPEED_DOWN);


}