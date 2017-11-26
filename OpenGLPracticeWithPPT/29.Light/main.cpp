#include "Define.h"
#include "Objects.h"

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

const unsigned int ANIMATION_TIME = 1000 / 30;

vector<shared_ptr<CObject>> g_v;

int winId;

void main(int argc, char* argv[])
{

	Init();

	winId = glutCreateWindow("20.VarietyObjectsAnimation");
	glutDisplayFunc(RenderScene);
	glutReshapeFunc(Reshape);
	glutKeyboardFunc(Keyboard);
	glutMouseFunc(Mouse);
	glutTimerFunc(ANIMATION_TIME, Animate, true);

	glutMainLoop();
}


GLvoid Init(GLvoid)
{
	srand((unsigned int)time(NULL));
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);

	g_v.emplace_back(FACTORYMANAGER->CreateObj(FLOOR, Vector3(0.0f, -30.0f, 0.0f), FLOOR_SCALE,
		FLOOR_SIZE, Color(1.0f, 1.0f, 1.0f)));
	g_v.emplace_back(FACTORYMANAGER->CreateObj(HEXAHEDRON_TREE, Vector3(-(REAL_WINDOW_WIDTH - GAP_OF_END), 0.0f, -(REAL_WINDOW_DEPTH - GAP_OF_END)), Vector3(1.0f, 5.0f, 1.0f),
		HEXAHEDRON_TREE_SIZE, Color(1.0f, 108.0f / RGB, 108.0f / RGB), Color(67.0f / RGB, 116.0f / RGB, 217.0f / RGB)));
	g_v.emplace_back(FACTORYMANAGER->CreateObj(HEXAHEDRON_SPHRE_TREE, Vector3((REAL_WINDOW_WIDTH - GAP_OF_END), 0.0f, -(REAL_WINDOW_DEPTH - GAP_OF_END)), Vector3(1.0f, 5.0f, 1.0f),
		HEXAHEDRON_TREE_SIZE, Color(1.0f, 108.0f / RGB, 108.0f / RGB), Color(67.0f / RGB, 116.0f / RGB, 217.0f / RGB)));
	g_v.emplace_back(FACTORYMANAGER->CreateObj(HEXAHEDRON_TORUS_BUILDING, Vector3(-(REAL_WINDOW_WIDTH - GAP_OF_END), 0.0f, 0.0f), Vector3(1.0f, 5.0f, 1.0f),
		HEXAHEDRON_TREE_SIZE, Color(1.0f, 108.0f / RGB, 108.0f / RGB), Color(67.0f / RGB, 116.0f / RGB, 217.0f / RGB)));
	g_v.emplace_back(FACTORYMANAGER->CreateObj(CORN_BUILDING, Vector3((REAL_WINDOW_WIDTH - GAP_OF_END * 2), 0.0f, GAP_OF_END), Vector3(2.0f, 2.0f, 1.0f),
		HEXAHEDRON_TREE_SIZE, Color(1.0f, 108.0f / RGB, 108.0f / RGB), Color(67.0f / RGB, 116.0f / RGB, 217.0f / RGB)));

	g_v.emplace_back(FACTORYMANAGER->CreateObj(PYRAMID, Vector3(0.0f, 0.0f, -((REAL_WINDOW_DEPTH - GAP_OF_END) / 3.0f)), Vector3(1.0f, 5.0f, 1.0f),
		20.0f, Color(1.0f, 1.0f, 0.0f), Color(1.0f, 1.0f, 0.0f)));

	g_v.emplace_back(FACTORYMANAGER->CreateObj(LIGHT, Vector3(-(REAL_WINDOW_WIDTH - GAP_OF_END), 70.0f, 0.0f), 5.0f, 0.0f));

	g_v.emplace_back(FACTORYMANAGER->CreateObj(LIGHT, Vector3((REAL_WINDOW_WIDTH - GAP_OF_END), 70.0f, 0.0f), 5.0f, 1));

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
	case '+':
	case '-': CAMERAMANAGER->SetMove(key); break;
	case 'i': CAMERAMANAGER->Reset(); break;
	case '1': g_v[LIGHT - 1]->SwitchLight(); break;
	case '2': g_v[LIGHT]->SwitchLight(); break;
	case 'A': g_v[LIGHT - 1]->IncreAmbient(); g_v[LIGHT]->IncreAmbient(); break;
	case 'a': g_v[LIGHT - 1]->DecreAmbient(); g_v[LIGHT]->DecreAmbient(); break;

	case 'D': g_v[LIGHT - 1]->IncreDiffuse(); g_v[LIGHT]->IncreDiffuse(); break;
	case 'd': g_v[LIGHT - 1]->DecreDiffuse(); g_v[LIGHT]->DecreDiffuse(); break;

	case 'S': g_v[LIGHT - 1]->IncreSpecular(); g_v[LIGHT]->IncreSpecular(); break;
	case 's': g_v[LIGHT - 1]->DecreSpecular(); g_v[LIGHT]->DecreSpecular(); break;
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
	CAMERAMANAGER->Update();
	for (auto d : g_v) d->Update();
}

GLvoid Render()
{
	for (auto d : g_v) d->Render();
}

