#include "Define.h"
#include "Objects.h"

GLvoid Init(GLvoid);
GLvoid Idle(GLvoid);
GLvoid RenderScene(GLvoid);
GLvoid Reshape(int w, int h);
GLvoid Keyboard(unsigned char key, int x, int y);
GLvoid Mouse(int button, int state, int x, int y);
GLvoid MouseMove(int x, int y);
GLvoid Update();
GLvoid Render();



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
	case 'i': CAMERAMANAGER->Reset(); RENDERMANAGER->Reset(); break;
	case 'q':
	case 'Q': glutDestroyWindow(winId); exit(0); break;
	case '6':
	case '4':
	case '2': 
	case '8':
	case '7':
	case '1':{
		CController* p = dynamic_cast<CController*> (RENDERMANAGER->GetObj()[CONTROLLER].get());
		p->Move(key); break;
	}
	case '0': {
		CController* p = dynamic_cast<CController*> (RENDERMANAGER->GetObj()[CONTROLLER].get());
		RENDERMANAGER->IncreaseRow(p->GetPoint()); break;
	}
	case '9': {
		RENDERMANAGER->ResetController(); break;
	}

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
	RENDERMANAGER->Update();
}

GLvoid Render()
{
	

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
