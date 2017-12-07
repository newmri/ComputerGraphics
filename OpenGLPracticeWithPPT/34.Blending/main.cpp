#include "Define.h"
#include "Objects.h"

GLvoid Init(GLvoid);
GLvoid DrawScene(GLvoid);
GLvoid Reshape(int w, int h);
GLvoid Animate(int n);
GLvoid Keyboard(unsigned char key, int x, int y);
GLvoid Mouse(int button, int state, int x, int y);
GLvoid ConvertDeviceToOpenGL(int x, int y, Pos* pos);
GLvoid Rotate();

const unsigned int ANIMATION_TIME = 1000 / 30;

bool g_rotate = false;
float g_angle = 0.0f;

vector<unique_ptr<CShape>> v;

int winId;

void main(int argc, char* argv[])
{

	Init();
	winId = glutCreateWindow("34.Blending");
	glutDisplayFunc(DrawScene);
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
	
	// T
	v.emplace_back(FACTORYMANAGER->CreateObj(TEAPOT, Pos(-WINDOW_WIDTH / 2 + 100, WINDOW_HEIGHT / 2 - 100, 0), 50));
	v.emplace_back(FACTORYMANAGER->CreateObj(SPHERE, Pos(-WINDOW_WIDTH / 2 + 100 + 25, WINDOW_HEIGHT / 2 - 100, 0), 50));
	v[1]->SetStr("(GL_ONE, GL_ZERO)");
	v.emplace_back(FACTORYMANAGER->CreateObj(CONE, Pos(-WINDOW_WIDTH / 2 + 100 + 25 + 50, WINDOW_HEIGHT / 2 + 250, 0), 200));

	v.emplace_back(FACTORYMANAGER->CreateObj(TEAPOT, Pos(-WINDOW_WIDTH / 2 + 350, WINDOW_HEIGHT / 2 - 100, 0), 50));
	v.emplace_back(FACTORYMANAGER->CreateObj(SPHERE, Pos(-WINDOW_WIDTH / 2 + 350 + 25, WINDOW_HEIGHT / 2 - 100, 0), 50));
	v[4]->SetStr("(GL_ZERO, GL_ZERO)");
	v.emplace_back(FACTORYMANAGER->CreateObj(CONE, Pos(-WINDOW_WIDTH / 2 + 350 + 25 + 50, WINDOW_HEIGHT / 2 + 250, 0), 200));

	v.emplace_back(FACTORYMANAGER->CreateObj(TEAPOT, Pos(-WINDOW_WIDTH / 2 + 600, WINDOW_HEIGHT / 2 - 100, 0), 50));
	v.emplace_back(FACTORYMANAGER->CreateObj(SPHERE, Pos(-WINDOW_WIDTH / 2 + 600 + 25, WINDOW_HEIGHT / 2 - 100, 0), 50));
	v[7]->SetStr("(GL_ONE, GL_ONE)");
	v.emplace_back(FACTORYMANAGER->CreateObj(CONE, Pos(-WINDOW_WIDTH / 2 + 600 + 25 + 50, WINDOW_HEIGHT / 2 + 250, 0), 200));

	// M
	v.emplace_back(FACTORYMANAGER->CreateObj(TEAPOT, Pos(-WINDOW_WIDTH / 2 + 100, 0, 0), 50));
	v.emplace_back(FACTORYMANAGER->CreateObj(SPHERE, Pos(-WINDOW_WIDTH / 2 + 100 + 25, 0, 0), 50));
	v[10]->SetStr("(GL_SRC_ALPHA, GL_1_MIN_SRC_ALPHA)");
	v.emplace_back(FACTORYMANAGER->CreateObj(CONE, Pos(-WINDOW_WIDTH / 2 + 100 + 25 + 50, 0, 0), 200));

	v.emplace_back(FACTORYMANAGER->CreateObj(TEAPOT, Pos(-WINDOW_WIDTH / 2 + 350, 0, 0), 50));
	v.emplace_back(FACTORYMANAGER->CreateObj(SPHERE, Pos(-WINDOW_WIDTH / 2 + 350 + 25, 0, 0), 50));
	v[13]->SetStr("(GL_SRC_ALPHA, GL_ONE)");
	v.emplace_back(FACTORYMANAGER->CreateObj(CONE, Pos(-WINDOW_WIDTH / 2 + 350 + 25 + 50, 0, 0), 200));

	v.emplace_back(FACTORYMANAGER->CreateObj(TEAPOT, Pos(-WINDOW_WIDTH / 2 + 600, 0, 0), 50));
	v.emplace_back(FACTORYMANAGER->CreateObj(SPHERE, Pos(-WINDOW_WIDTH / 2 + 600 + 25, 0, 0), 50));
	v[16]->SetStr("(GL_ZERO, GL_SRC_COLOR)");
	v.emplace_back(FACTORYMANAGER->CreateObj(CONE, Pos(-WINDOW_WIDTH / 2 + 600 + 25 + 50, 0, 0), 200));


	// B
	v.emplace_back(FACTORYMANAGER->CreateObj(TEAPOT, Pos(-WINDOW_WIDTH / 2 + 100, -200, 0), 50));
	v.emplace_back(FACTORYMANAGER->CreateObj(SPHERE, Pos(-WINDOW_WIDTH / 2 + 100 + 25, -200, 0), 50));
	v[19]->SetStr("(GL_1_MIN_DST_COLOR, GL_ZERO)");
	v.emplace_back(FACTORYMANAGER->CreateObj(CONE, Pos(-WINDOW_WIDTH / 2 + 100 + 25 + 50, -550, 0), 200));

	
	v.emplace_back(FACTORYMANAGER->CreateObj(TEAPOT, Pos(-WINDOW_WIDTH / 2 + 350, -200, 0), 50));
	v.emplace_back(FACTORYMANAGER->CreateObj(SPHERE, Pos(-WINDOW_WIDTH / 2 + 350 + 25, -200, 0), 50));
	v[22]->SetStr("(GL_SRC_ALPHA, GL_1_MIN_SRC_COLOR)");
	v.emplace_back(FACTORYMANAGER->CreateObj(CONE, Pos(-WINDOW_WIDTH / 2 + 350 + 25 + 50, -550, 0), 200));

	v.emplace_back(FACTORYMANAGER->CreateObj(TEAPOT, Pos(-WINDOW_WIDTH / 2 + 600, -200, 0), 50));
	v.emplace_back(FACTORYMANAGER->CreateObj(SPHERE, Pos(-WINDOW_WIDTH / 2 + 600 + 25, -200, 0), 50));
	v[25]->SetStr("(GL_ONE, GL_ONE)");
	v.emplace_back(FACTORYMANAGER->CreateObj(CONE, Pos(-WINDOW_WIDTH / 2 + 600 + 25 + 50, -550, 0), 200));
	
	//v.emplace_back(FACTORYMANAGER->CreateObj(TEAPOT, Pos(-50, 30,0), 10));
	//  Pos(-WINDOW_WIDTH / 2 + 100, WINDOW_HEIGHT / 2 - 100,0)

}

GLvoid DrawScene(GLvoid)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glEnable(GL_BLEND);
	//glClearColor(0.0, 0.0, 0.0, 0.5);
	// T
	glBlendFunc(GL_ONE, GL_ZERO);
	v[0]->Render();
	v[1]->Render();
	v[2]->Render();

	glBlendFunc(GL_ZERO, GL_ZERO);
	v[3]->Render();
	v[4]->Render();
	v[5]->Render();

	glBlendFunc(GL_ONE, GL_ONE);
	v[6]->Render();
	v[7]->Render();
	v[8]->Render();

	// M
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	v[9]->Render();
	v[10]->Render();
	v[11]->Render();

	glBlendFunc(GL_SRC_ALPHA, GL_ONE);
	v[12]->Render();
	v[13]->Render();
	v[14]->Render();

	glBlendFunc(GL_ZERO, GL_SRC_COLOR);
	v[15]->Render();
	v[16]->Render();
	v[17]->Render();

	// B
	glBlendFunc(GL_ONE_MINUS_DST_COLOR, GL_ZERO);
	v[18]->Render();
	v[19]->Render();
	v[20]->Render();

	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_COLOR);
	v[21]->Render();
	v[22]->Render();
	v[23]->Render();

	glBlendFunc(GL_ONE, GL_ONE);
	v[24]->Render();
	v[25]->Render();
	v[26]->Render();

	//glEnable(GL_BLEND);
	glutSwapBuffers(); // Draw
}

GLvoid Reshape(int w, int h)
{

	glViewport(0, 0, w, h); // Change viewport with window size
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	//gluPerspective(REAL_WINDOW_WIDTH, WINDOW_WIDTH / WINDOW_HEIGHT, 1.0f, WINDOW_DEPTH); // Use perspective
	//glTranslatef(0.0f, 0.0f, -80.0f);
	glOrtho(-(WINDOW_WIDTH / 2.0f), WINDOW_WIDTH / 2.0f, -(WINDOW_HEIGHT / 2.0f), (WINDOW_HEIGHT / 2.0f), -1000.0, 1000.0);
}


GLvoid Animate(int n)
{
	for (auto& d : v) d->Update();

	DrawScene();
	glutTimerFunc(ANIMATION_TIME, Animate, true);
}



GLvoid Keyboard(unsigned char key, int x, int y)
{
	switch (key) {
	case 'q':
		glutDestroyWindow(winId);
		exit(0);
		break;
	}
	DrawScene();
}



GLvoid Mouse(int button, int state, int x, int y)
{

	

	DrawScene();
}

GLvoid ConvertDeviceToOpenGL(int x, int y, Pos* pos)
{
	float w = WINDOW_WIDTH;
	float h = WINDOW_HEIGHT;

	pos->x = (x - w / 2.0f) * (1.0f / (w / 2.0f));
	pos->y = -(y - h / 2.0f) * (1.0f / (h / 2.0f));

}