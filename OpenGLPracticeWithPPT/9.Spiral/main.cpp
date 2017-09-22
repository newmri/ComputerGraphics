#include "Define.h"
#include "Shape.h"

GLvoid Init(GLvoid);
GLvoid DrawScene(GLvoid);
GLvoid Reshape(int w, int h);
GLvoid Mouse(int button, int state, int x, int y);
GLvoid Animate(int n);
GLvoid SpecialKeyBoard(int key, int x, int y);
GLvoid MenuFunc(int button);

const int MAX_SPIRAL_NUM = 5;
const unsigned int ANIMATION_TIME = 1000 / 30;

vector<unique_ptr<CShape>> vec;

SHAPE g_shape = SHAPE::SPIRAL;

void main(int argc, char* argv[])
{
	int mainMenu{}, subMenu{};

	Init();
	glutCreateWindow("9.Spiral");
	glutDisplayFunc(DrawScene);
	glutReshapeFunc(Reshape);
	glutMouseFunc(Mouse);
	glutTimerFunc(ANIMATION_TIME, Animate, true);
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
	for (auto& d : vec) d->Draw();

	glFlush(); // Draw
}

GLvoid Reshape(int w, int h)
{
	glViewport(0, 0, w, h);
	glOrtho(0, WINDOW_SIZE_WIDTH, WINDOW_SIZE_HEIGHT, 0, -1.0f, 1.0f);
}

void Mouse(int button, int state, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
		if (vec.size() == 5) {
			vector<unique_ptr<CShape>>::iterator itor = vec.begin();
			itor = vec.erase(itor);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		}
		vec.push_back(FACTORYMANAGER->CreateObj(g_shape, x, y));
		glutPostRedisplay(); // Re draw
	}
}

GLvoid Animate(int n)
{

	vector<unique_ptr<CShape>>::iterator itor = vec.begin();
	while (itor != vec.end()) {
		(*itor)->ChangeColor();
		++itor;
	}
	glutPostRedisplay(); // Re draw
	glutTimerFunc(ANIMATION_TIME, Animate, true);
}

GLvoid SpecialKeyBoard(int key, int x, int y)
{
	vector<unique_ptr<CShape>>::iterator itor = vec.begin();

	if (key == GLUT_KEY_UP) {
		while (itor != vec.end()) {
			(*itor)->ChangeSpeed(SPEED_UP);
			++itor;
		}
	}
	
	else if (key == GLUT_KEY_DOWN) {
		while (itor != vec.end()) {
			(*itor)->ChangeSpeed(SPEED_DOWN);
			++itor;
		}
		
	}

}

GLvoid MenuFunc(int button)
{
	switch (button) {
	case SHAPE::SPIRAL: g_shape = SHAPE::SPIRAL; break;
	default: break;
	}

}