#include "Define.h"
#include "Objects.h"

GLvoid Init(GLvoid);
GLvoid Idle(GLvoid);
GLvoid RenderScene(GLvoid);
GLvoid Reshape(int w, int h);
GLvoid Keyboard(unsigned char key, int x, int y);
GLvoid Mouse(int button, int state, int x, int y);
GLvoid Rotate();
GLvoid Update();
GLvoid Render();
void SetUpRC();

vector<shared_ptr<CObject>> g_v;


int winId;
int base;
HDC hDC;
double lastTime = glutGet(GLUT_ELAPSED_TIME);
int frame = 0;

void main(int argc, char* argv[])
{

	Init();

	winId = glutCreateWindow("33.Snow+Texture");
	SetUpRC();
	glutDisplayFunc(RenderScene);
	glutReshapeFunc(Reshape);
	glutKeyboardFunc(Keyboard);
	glutMouseFunc(Mouse);
	glutIdleFunc(Idle);
	glutMainLoop();
}


GLvoid Init(GLvoid)
{
	srand((unsigned int)time(NULL));
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);

	g_v.emplace_back(FACTORYMANAGER->CreateObj(LIGHT1, Vector3(-(REAL_WINDOW_WIDTH - GAP_OF_END), 50.0f, -GAP_OF_END), 5.0f, 0.0f));
	g_v.emplace_back(FACTORYMANAGER->CreateObj(LIGHT2, Vector3((REAL_WINDOW_WIDTH - GAP_OF_END), 50.0f, -GAP_OF_END), 5.0f, 1));
	g_v.emplace_back(FACTORYMANAGER->CreateObj(LIGHT3, Vector3(-(REAL_WINDOW_WIDTH - GAP_OF_END), 50.0f, GAP_OF_END), 5.0f, 0.0f));
	g_v.emplace_back(FACTORYMANAGER->CreateObj(LIGHT4, Vector3((REAL_WINDOW_WIDTH - GAP_OF_END), 50.0f, GAP_OF_END), 5.0f, 1));

	g_v.emplace_back(FACTORYMANAGER->CreateObj(FLOOR, Vector3(0.0f, -30.0f, 30.0f), FLOOR_SCALE,
		FLOOR_SIZE, Color(1.0f, 1.0f, 1.0f)));

	g_v.emplace_back(FACTORYMANAGER->CreateObj(PARTICLE, Vector3(0.0f, 50.0f, 0.0f), FLOOR_SCALE,
		0.3f, Color(1.0f, 1.0f, 1.0f)));
	
	g_v.emplace_back(FACTORYMANAGER->CreateObj(PYRAMID, Vector3(-10.0f, 20.0f, -((REAL_WINDOW_DEPTH - GAP_OF_END) / 3.0f)), Vector3(1.0f, 5.0f, 1.0f),
		10.0f, Color(1.0f, 1.0f, 0.0f), Color(1.0f, 1.0f, 0.0f)));
		
	g_v.emplace_back(FACTORYMANAGER->CreateObj(PYRAMID, Vector3(20.0f, 20.0f, -((REAL_WINDOW_DEPTH - GAP_OF_END) / 3.0f)), Vector3(1.0f, 5.0f, 1.0f),
		10.0f, Color(1.0f, 1.0f, 0.0f), Color(1.0f, 1.0f, 0.0f)));

}

void SetUpRC()
{
	TEXTUREMANAGER->Init();

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
	case '1': g_v[LIGHT1]->SwitchLight(); break;
	case '2': g_v[LIGHT2]->SwitchLight(); break;
	case '3': g_v[LIGHT3]->SwitchLight(); break;
	case '4': g_v[LIGHT4]->SwitchLight(); break;
	case 'A': for(int i = 0; i < 4; ++i) g_v[i]->TurnOnLight(); break;
	case 'a': for (int i = 0; i < 4; ++i) g_v[i]->TurnOffLight(); break;
	case 'n': CAMERAMANAGER->SetNormalize(true); break;
	case 'N': CAMERAMANAGER->SetNormalize(false); break;

	default: break;
	}
	RenderScene();
}


GLvoid Mouse(int button, int state, int x, int y)
{
	cout << x << endl;
	RenderScene();
}


GLvoid Update()
{
	CAMERAMANAGER->Update();
	for (auto& d: g_v) d->Update();
}

GLvoid Render()
{

	for (auto& d : g_v) d->Render();

	double time = glutGet(GLUT_ELAPSED_TIME);
	frame++;
	if ((time - lastTime) > 1000.0)
	{
		int fps = frame * 1000.0 / (time - lastTime);
		lastTime = time;
		frame = 0;
		char buff[10]{ "fps: " };
		char buff2[10];
		_itoa_s(fps, buff2, 10);
		strcat_s(buff, buff2);
		glutSetWindowTitle(buff);
	}
}


GLvoid Idle(GLvoid)
{
	RenderScene();
}

