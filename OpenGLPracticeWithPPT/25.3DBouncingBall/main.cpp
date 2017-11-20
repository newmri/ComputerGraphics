#include "Define.h"
#include "CObject.h"

GLvoid Init(GLvoid);
GLvoid Idle(GLvoid);
GLvoid RenderScene(GLvoid);
GLvoid Reshape(int w, int h);
GLvoid Animate(int n);
GLvoid Keyboard(unsigned char key, int x, int y);
GLvoid MouseMotion(int x, int y);
GLvoid Rotate();
GLvoid Update();
GLvoid Render();
GLvoid MenuFunc(int button);

const unsigned int ANIMATION_TIME = 1000 / 30;


int winId;

vector<shared_ptr<CObject>> g_v;

void main(int argc, char* argv[])
{

	Init();

	winId = glutCreateWindow("25.3DBouncingBall");
	glutDisplayFunc(RenderScene);
	glutReshapeFunc(Reshape);
	glutKeyboardFunc(Keyboard);
	glutPassiveMotionFunc(MouseMotion);
	glutTimerFunc(ANIMATION_TIME, Animate, true);
	glutMainLoop();
}


GLvoid Init(GLvoid)
{
	srand((unsigned int)time(NULL));
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	glFrontFace(GL_CW);
	glEnable(GL_CULL_FACE); glCullFace(GL_BACK);
	glEnable(GL_DEPTH_TEST);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);

	
	g_v.emplace_back(FACTORYMANAGER->CreateObj(CUBE));

	g_v.emplace_back(FACTORYMANAGER->CreateObj(TINYCUBE, 10.0f));
	g_v.emplace_back(FACTORYMANAGER->CreateObj(TINYCUBE, 5.0f));
	g_v.emplace_back(FACTORYMANAGER->CreateObj(TINYCUBE, 3.0f));

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

	case 'b':
	case 'B': if(g_v.size() < 9) g_v.emplace_back(FACTORYMANAGER->CreateObj(BALL)); break;
	default: break;
	}
	RenderScene();
}


GLvoid MouseMotion(int x, int y)
{
	if ((x - (WINDOW_WIDTH / 2.0f)) < 0 && !CAMERAMANAGER->IsRotatingToCCW()) CAMERAMANAGER->SetRotate('z');
	else if ((x - (WINDOW_WIDTH / 2.0f)) > 0 && CAMERAMANAGER->IsRotatingToCCW()) CAMERAMANAGER->SetRotate('Z');
	
	RenderScene();
}


GLvoid Update()
{
	int ret{};
	CAMERAMANAGER->Update();
	for (auto& d : g_v) d->Update();

	
}

GLvoid Render()
{
	glPushMatrix();
	//glRotatef(10.0f, 0.0f, 0.0f, 1.0f);
	for (auto& d : g_v) d->Render();
	glPopMatrix(); 

}

