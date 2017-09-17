#include "Define.h"
#include "Shape.h"

GLvoid Init(GLvoid);
GLvoid DrawScene(GLvoid);
GLvoid Reshape(int w, int h);
GLvoid Mouse(int button, int state, int x, int y);
GLvoid Motion(int x, int y);
GLvoid Animate(int n);
GLvoid SpecialKeyBoard(int key, int x, int y);
const int MAX_RECT_NUM = 10;
const unsigned int ANIMATION_TIME = 1000 / 30;
int g_leftButton = 0;

vector<unique_ptr<CShape>> vec;
CCircle g_target;
void main(int argc, char* argv[])
{
	g_target.SetPos(Pos(1000, 1000));
	Init();
	glutCreateWindow("8.PursuitTarget");
	glutDisplayFunc(DrawScene);
	glutReshapeFunc(Reshape);

	glutMouseFunc(Mouse);
	glutMotionFunc(Motion);
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
	if (g_target.GetPos().x != 1000) g_target.Draw();

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
		g_leftButton = GLUT_LEFT_BUTTON;
		g_target.SetPos(Pos(x, y));
		glClear(GL_COLOR_BUFFER_BIT);
	}
	if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN) {
		g_leftButton = GLUT_RIGHT_BUTTON;
		vec.push_back(FACTORYMANAGER->CreateObj(SHAPE::RECTANGLE, x, y));
	}
	DrawScene();
	
}

GLvoid Motion(int x, int y)
{
	if (g_leftButton == GLUT_LEFT_BUTTON) {
		g_target.SetPos(Pos(x, y));
		glClear(GL_COLOR_BUFFER_BIT);
	}
}

GLvoid Animate(int n)
{
	g_target.ChangeColor();
	vector<unique_ptr<CShape>>::iterator itor = vec.begin();
	while (itor != vec.end()) {
		if (g_target.GetPos().x != 1000) {
			CRect* p = dynamic_cast<CRect*>(itor->get());
			p->SetTarget(g_target.GetPos(), g_target.GetRad());
		}
		(*itor)->ChangeColor();
		(*itor)->Move();
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
