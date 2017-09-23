#include "Define.h"
#include "Objects.h"

GLvoid Init(GLvoid);
GLvoid DrawScene(GLvoid);
GLvoid Reshape(int w, int h);
GLvoid Mouse(int button, int state, int x, int y);
GLvoid Motion(int x, int y);
GLvoid Animate(int n);
GLvoid SpecialKeyBoard(int key, int x, int y);
GLvoid MenuFunc(int button);

const int MAX_RECT_NUM = 10;
const unsigned int ANIMATION_TIME = 1000 / 30;
const unsigned int SIZE_CHANGE_TIME = 1000;

int g_button = -1;

vector<unique_ptr<CObject>> v;
CBorder g_border;
OBJTYPE g_objType = OBJTYPE::BORDER;

void main(int argc, char* argv[])
{
	int mainMenu{}, subMenu{};

	Init();
	glutCreateWindow("10.PsreadDot");
	glutDisplayFunc(DrawScene);
	glutReshapeFunc(Reshape);
	subMenu = glutCreateMenu(MenuFunc);
	glutAddMenuEntry("Border", OBJTYPE::BORDER);
	glutAddMenuEntry("Circle", OBJTYPE::CIRCLE);
	mainMenu = glutCreateMenu(MenuFunc);
	glutAddSubMenu("Shape", subMenu);

	glutAttachMenu(GLUT_RIGHT_BUTTON);

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

	g_border.Init(OBJTYPE::BORDER, MOVETYPE::UNMOVABLE, Pos(0, 0));
	srand((unsigned int)time(NULL));
}

GLvoid DrawScene(GLvoid)
{
	g_border.Render();

	for (auto& d : v) d->Render();
	glFlush(); // Draw
}

GLvoid Reshape(int w, int h)
{

	glViewport(0, 0, w, h); // Change viewport with window size
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0, w, h, 0, -1.0f, 1.0f);

}

void Mouse(int button, int state, int x, int y)
{
	g_button = button;

	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
		if(g_objType == OBJTYPE::BORDER) g_border.SetPos(Pos(x, y));
		else {
			if (v.size() == 20) {
				vector<unique_ptr<CObject>>::iterator itor = v.begin();
				itor = v.erase(itor);
			}
			v.push_back(FACTORYMANAGER->CreateObj(OBJTYPE::CIRCLE, MOVETYPE::MOVABLE, Pos(x, y)));
		}
	}
}

GLvoid Animate(int n)
{
	if (v.size() != 0) {
		vector<unique_ptr<CObject>>::iterator itor = v.begin();
		while (itor != v.end()) {
			(*itor)->Update();
			if ((*itor)->GetObjType() == OBJTYPE::CIRCLE) {
				CCircle* p = dynamic_cast<CCircle*>(itor->get());
				if (!((p->GetPos().x - p->GetRad() >= g_border.GetPos().x) &&
					(p->GetPos().x + p->GetRad() <= g_border.GetEndPos().x)) ||
					((p->GetPos().y - p->GetRad() <= g_border.GetPos().y) ||
					(p->GetPos().y + p->GetRad() >= g_border.GetEndPos().y)) 
					)
					itor = v.erase(itor);
				else ++itor;
				
				
			}
		}
	}
	glutPostRedisplay(); // Re draw
	glutTimerFunc(ANIMATION_TIME, Animate, true);
}

GLvoid SpecialKeyBoard(int key, int x, int y)
{
	vector<unique_ptr<CObject>>::iterator itor = v.begin();

	if (key == GLUT_KEY_UP) {
		while (itor != v.end()) {
			if ((*itor)->GetMoveType() == MOVETYPE::MOVABLE) {
				CMovableObject* p = dynamic_cast<CMovableObject*>(itor->get());
				p->ChangeSpeed(SPEED_UP);
			}
			++itor;
		}
	}
	
	else if (key == GLUT_KEY_DOWN) {
		while (itor != v.end()) {
			if ((*itor)->GetMoveType() == MOVETYPE::MOVABLE) {
				CMovableObject* p = dynamic_cast<CMovableObject*>(itor->get());
				p->ChangeSpeed(SPEED_DOWN);
			}
			++itor;
		}
		
	}

}

GLvoid Motion(int x, int y)
{
	if (g_button == GLUT_LEFT_BUTTON && g_objType == OBJTYPE::BORDER) {
		g_border.SetEndPos(Pos(x, y));
		glClear(GL_COLOR_BUFFER_BIT);
	}
}

GLvoid MenuFunc(int button)
{
	switch (button) {
	case OBJTYPE::BORDER: g_objType = OBJTYPE::BORDER; break;
	case OBJTYPE::CIRCLE: g_objType = OBJTYPE::CIRCLE; break;
	default: break;
	}

}
