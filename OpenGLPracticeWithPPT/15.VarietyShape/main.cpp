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

vector<unique_ptr<CObject>> v;

int winId;

void main(int argc, char* argv[])
{

	Init();
	winId = glutCreateWindow("15.VarietyShape");
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
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);

}

GLvoid DrawScene(GLvoid)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	
	for (auto& d : v) d->Render();
	
	glutSwapBuffers(); // Draw
}

GLvoid Reshape(int w, int h)
{
	glViewport(0, 0, w, h); // Change viewport with window size
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
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

	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN){
		Pos pos;
		ConvertDeviceToOpenGL(x, y, &pos);
		OBJTYPE shape = static_cast<OBJTYPE>((rand() % (OBJTYPE::END - 1)) + 1);
		v.emplace_back(FACTORYMANAGER->CreateObj(shape,
			MOVETYPE::MOVABLE, pos, BIG_TRIANGLE_SIZE));
	}

	DrawScene();
}

GLvoid ConvertDeviceToOpenGL(int x, int y, Pos* pos)
{
	float w = WINDOW_WIDTH;
	float h = WINDOW_HEIGHT;

	pos->x = (x - w / 2.0f) * (1.0f / (w / 2.0f));
	pos->y = -(y - h / 2.0f) * (1.0f / (h / 2.0f));

}