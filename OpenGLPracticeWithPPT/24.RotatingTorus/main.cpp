#include "Define.h"
#include "CObject.h"

GLvoid Init(GLvoid);
GLvoid Idle(GLvoid);
GLvoid RenderScene(GLvoid);
GLvoid Reshape(int w, int h);
GLvoid Animate(int n);
GLvoid Keyboard(unsigned char key, int x, int y);
GLvoid Mouse(int button, int state, int x, int y);
GLvoid Rotate();
GLvoid Update();
GLvoid Render();
GLvoid MenuFunc(int button);

const unsigned int ANIMATION_TIME = 1000 / 30;


int winId;

vector<shared_ptr<CObject>> g_v;
int g_idx = 0;

void main(int argc, char* argv[])
{

	Init();

	winId = glutCreateWindow("24.RotatingTorus");
	glutDisplayFunc(RenderScene);
	glutReshapeFunc(Reshape);
	glutKeyboardFunc(Keyboard);
	glutMouseFunc(Mouse);
	glutTimerFunc(ANIMATION_TIME, Animate, true);
	glutAttachMenu(GLUT_RIGHT_BUTTON);
	glutMainLoop();
}


GLvoid Init(GLvoid)
{
	srand((unsigned int)time(NULL));
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	glFrontFace(GL_CCW);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);

	int subMenu = glutCreateMenu(MenuFunc);
	glutAddMenuEntry("Hidden Surface Delete On", HIDDEN_SURFAE_DELETE_ON);
	glutAddMenuEntry("Hidden Surface Delete off", HIDDEN_SURFACE_DELETE_OFF);
	int mainMenu = glutCreateMenu(MenuFunc);
	glutAddSubMenu("Select", subMenu);
	g_v.emplace_back(FACTORYMANAGER->CreateObj(g_idx));

}

GLvoid RenderScene(GLvoid)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	Update();
	Render();

	glutSwapBuffers(); // Draw
}

GLvoid Reshape(int w, int h)
{
	glViewport(0, 0, w, h); // Change viewport with window size
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(REAL_WINDOW_WIDTH, WINDOW_WIDTH / WINDOW_HEIGHT, 1.0f, WINDOW_DEPTH); // Use perspective
	glTranslatef(0.0f, 0.0f, -80.0f);

}


GLvoid Animate(int n)
{
	RenderScene();
	glutTimerFunc(ANIMATION_TIME, Animate, true);
}


GLvoid Keyboard(unsigned char key, int x, int y)
{
	switch (key) {
	case 'x':
	case 'X':
	case 'y':
	case 'Y':
	case 'z':
	case 'Z': CAMERAMANAGER->SetRotate(key); break;

	case 'w':
	case 's':
	case 'a':
	case 'd':
	case 'q':
	case 'e':
	case '+':
	case '-': CAMERAMANAGER->SetMove(key); break;
	case 'i': CAMERAMANAGER->Reset(); break;

	default: break;
	}
	RenderScene();
}


GLvoid Mouse(int button, int state, int x, int y)
{
	RenderScene();
}


GLvoid Update()
{
	int ret{};
	CAMERAMANAGER->Update();
	for (auto& d : g_v) d->Update();

	if (g_v[g_idx]->GetCreateNew()) {
		g_v[g_idx]->ReSetCreateNew();
		if(g_idx != MAX_TORUS_NUM) g_v.emplace_back(FACTORYMANAGER->CreateObj(++g_idx));
		else {
			g_v.clear();
			g_idx = 0;
			g_v.emplace_back(FACTORYMANAGER->CreateObj(g_idx));
		}
	}
	
}

GLvoid Render()
{
	glPushMatrix();

	// Draw floor
	glPushMatrix();
	glTranslatef(0.0f, -50.0f, -30.0f);
	glScalef(15.0f, 4.0f, 5.0f);
	glColor3f(153.0f / RGB, 112.0f / RGB, 0.0f);
	glutSolidCube(10);
	glPopMatrix();

	// Draw stick
	glPushMatrix();
	glTranslatef(0.0f, -10.0f, 0.0f);
	glScalef(1.0f, 40.0f, 0.0f);
	glColor3f(1.0f, 0.0f, 0.0f);
	glutSolidCube(1);
	glPopMatrix();

	// Draw stick
	glPushMatrix();
	for (auto& d : g_v) d->Render();
	glPopMatrix(); 
	glPopMatrix();
}

GLvoid MenuFunc(int button)
{
	switch (button) {
	case HIDDEN_SURFAE_DELETE_ON: glEnable(GL_DEPTH_TEST); break;
	case HIDDEN_SURFACE_DELETE_OFF: glDisable(GL_DEPTH_TEST); break;
	default: break;
	}
}