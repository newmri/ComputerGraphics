#include "Define.h"
#include "Objects.h"

GLvoid Init(GLvoid);
GLvoid Idle(GLvoid);
GLvoid RenderScene(GLvoid);
GLvoid Reshape(int w, int h);
GLvoid Keyboard(unsigned char key, int x, int y);
GLvoid Mouse(int button, int state, int x, int y);
GLvoid MouseMove(int x, int y);
GLvoid Rotate();
GLvoid Update();
GLvoid Render();


vector<shared_ptr<CObject>> g_v;


int winId;
int base;
HDC hDC;
double lastTime = glutGet(GLUT_ELAPSED_TIME);
int frame = 0;

void main(int argc, char* argv[])
{

	Init();

	winId = glutCreateWindow("");
	TEXTUREMANAGER->Init();
	RENDERMANAGER->Init();
	glutDisplayFunc(RenderScene);
	glutReshapeFunc(Reshape);
	glutKeyboardFunc(Keyboard);
	glutMouseFunc(Mouse);
	glutMotionFunc(MouseMove);
	glutIdleFunc(Idle);
	glutMainLoop();
}


GLvoid Init(GLvoid)
{
	srand((unsigned int)time(NULL));
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);


	g_v.emplace_back(FACTORYMANAGER->CreateObj(CUBE, Vector3(0.0f,0.0f,0.0f), CUBE_SIZE, Color(1.0f, 1.0f, 1.0f)));
	g_v.emplace_back(FACTORYMANAGER->CreateObj(PARTICLE, Vector3(0.0f, 0.0f, 0.0f), 0.3f, Color(1.0f, 1.0f, 1.0f)));
	Vector3 lt(Vector3(-CUBE_SIZE / 2.0f + EARTH_RAD, CUBE_SIZE / 2.0f - EARTH_RAD, CUBE_SIZE / 2.0f - EARTH_RAD));
	Vector3 rb(Vector3(CUBE_SIZE / 2.0f - EARTH_RAD, -CUBE_SIZE / 2.0f + EARTH_RAD, -CUBE_SIZE / 2.0f + EARTH_RAD));
	g_v.emplace_back(FACTORYMANAGER->CreateObj(EARTH, lt, EARTH_RAD, Color(1.0f, 1.0f, 1.0f)));
	g_v.emplace_back(FACTORYMANAGER->CreateObj(EARTH, rb, EARTH_RAD, Color(1.0f, 1.0f, 1.0f)));

	int num = rand() % 20 + 15;
	Vector3* pos = new Vector3[num];
	int* rad = new int[num];
	for (int i = 0; i < num; ++i) {
		if (i == 0) {
			pos[i] = lt;
			rad[i] = EARTH_RAD;
		}
		if (i == 1) {
			pos[i] = rb;
			rad[i] = EARTH_RAD;
		}
		bool chk = false;
		if (i != 0 && i != 1) {
			rad[i] = rand() % 5 + 2;
			int max = CUBE_SIZE - rad[i] * 2;
			float min = (CUBE_SIZE / 2.0f) - rad[i];

			pos[i].x = (float)(rand() % max) - min;
			pos[i].y = (float)(rand() % max) - min;
			pos[i].z = (float)(rand() % max) - min;
		}
		for (int j = 0; j < i; ++j) {
			chk = (pow(pos[j].x - pos[i].x, 2) + pow(pos[j].y - pos[i].y, 2) +
				   pow(pos[j].z - pos[i].z, 2) < pow(rad[i] + rad[j], 2));

			if (chk) {
				chk = false;
				i -= 1;
			}
		}
		
	}


	for (int i = 0; i < num; ++i) {
		g_v.emplace_back(FACTORYMANAGER->CreateObj(PLANET, pos[i], rad[i], Color(1.0f, 1.0f, 1.0f)));
	}
	delete[] pos;
	delete[] rad;

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
	RENDERMANAGER->Resize(w, h);
	/*
	glViewport(0, 0, w, h); // Change viewport with window size
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(REAL_WINDOW_WIDTH, WINDOW_WIDTH / WINDOW_HEIGHT, 1.0f, WINDOW_DEPTH); // Use perspective
	glTranslatef(0.0f, 0.0f, -80.0f);
	*/
}




GLvoid Keyboard(unsigned char key, int x, int y)
{
	switch (key) {

	case 'w':
	case 'a':
	case 'd':
	case 's':
	case 'z':
	case 'x': CAMERAMANAGER->SetMove(key); break;
	case 'i': CAMERAMANAGER->Reset(); break;
	case 'q':
	case 'Q': glutDestroyWindow(winId); exit(0); break;

	default: break;
	}
	RenderScene();
}


GLvoid Mouse(int button, int state, int x, int y)
{
	if (state == GLUT_DOWN) CAMERAMANAGER->SetButton(button, x, y);
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
		strcat(buff, buff2);
		glutSetWindowTitle(buff);
	}
	RENDERMANAGER->Render();
}


GLvoid Idle(GLvoid)
{
	RenderScene();
}

GLvoid MouseMove(int x, int y)
{
	if (CAMERAMANAGER->IsOnRightMouse()) {
		CAMERAMANAGER->OnMouseMove(CAMERAMANAGER->GetLastPos().x - x, CAMERAMANAGER->GetLastPos().y - y);
		CAMERAMANAGER->SetLastPos(x, y);
	}
}
