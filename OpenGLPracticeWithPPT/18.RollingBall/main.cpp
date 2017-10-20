#include "Define.h"

GLvoid Init(GLvoid);
GLvoid DrawScene(GLvoid);
GLvoid Reshape(int w, int h);
GLvoid Animate(int n);
GLvoid Keyboard(unsigned char key, int x, int y);
GLvoid Mouse(int button, int state, int x, int y);
GLvoid Rotate();
GLvoid MenuFunc(int button);
GLvoid InitMenu();

const unsigned int ANIMATION_TIME = 1000 / 30;


int winId;

float g_ballAngle = 0.0f;
bool g_ballMove[3]{ false, false, false };
Vector3 g_ballPos, g_ballRotate{ 0.0f, 1.0f, 0.0f };

RENDERTYPE g_renderModel = RENDERTYPE::SOLID;

void main(int argc, char* argv[])
{

	Init();

	winId = glutCreateWindow("19.Crane");
	glutDisplayFunc(DrawScene);
	glutReshapeFunc(Reshape);
	
	InitMenu();

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

}

GLvoid DrawScene(GLvoid)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	CAMERAMANAGER->Update();

	// Draw floor
	glPushMatrix();

		glTranslatef(0.0f, -30.0f, 0.0f);

		glPushMatrix();
			glScalef(10.0f, 2.0f, 3.0f);
			glColor3f(153.0f / RGB, 112.0f / RGB, 0.0f);
			glutSolidCube(FLOOR_SIZE);
		glPopMatrix();

		glPushMatrix();
			glColor3f(1.0f, 0.0f, 0.0f);
			glTranslatef(g_ballPos.x, g_ballPos.y, g_ballPos.z);
			glRotatef(g_ballAngle, g_ballRotate.x, g_ballRotate.y, g_ballRotate.z);
			glutWireSphere(BALL_RAD, 25, 25);
		glPopMatrix();
	glPopMatrix();

	glutSwapBuffers(); // Draw
}

GLvoid Reshape(int w, int h)
{
	glViewport(0, 0, w, h); // Change viewport with window size
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60.0f, WINDOW_WIDTH / WINDOW_HEIGHT, 1.0f, 100.0f); // Use perspective
	glTranslatef(0.0f, 0.0f, -80.0f);

}


GLvoid Animate(int n)
{
	if(g_ballAngle < 360.0f) g_ballAngle += BALL_ROTATION_SPEED;
	else g_ballAngle = 0.0f;
	if(g_ballMove[X]) g_ballPos.x -= (BALL_ROTATION_SPEED / 360.0f)  * BALL_RAD * PIE * 2;
	if(g_ballMove[Z]) g_ballPos.z += (BALL_ROTATION_SPEED / 360.0f)  * BALL_RAD * PIE * 2;
	
	if (g_ballPos.x < -((FLOOR_SIZE * 5.0f) + PIE)) g_ballMove[X] = false;
	if (g_ballPos.z > (FLOOR_SIZE * 2.0f) + PIE) g_ballMove[Z] = false;
	DrawScene();
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
	case '+':
	case '-': CAMERAMANAGER->SetMove(key); break;
	case 'i':
		g_ballAngle = 0.0f;
		ZeroMemory(&g_ballMove, sizeof(g_ballMove));
		g_ballRotate.x = 0.0f;
		g_ballRotate.y = 1.0f;
		g_ballRotate.z = 0.0f;
		ZeroMemory(&g_ballPos, sizeof(g_ballPos));
		CAMERAMANAGER->Reset(); break;

	case 'l':
	case 'L':
		g_ballRotate.x = 1.0f;
		g_ballRotate.y = 0.0f;
		g_ballRotate.z = 0.0f;
		g_ballMove[Z] = true;
		g_ballMove[X] = false;
		g_ballMove[Y] = false;
		break;
	case 'm':
	case 'M':
		g_ballRotate.x = 0.0f;
		g_ballRotate.y = 1.0f;
		g_ballRotate.z = 0.0f;
		break;
	case 'n':
	case 'N':
		g_ballRotate.x = 0.0f;
		//g_ballRotate.y = 0.0f;
		g_ballRotate.z = 1.0f;
		g_ballMove[X] = true;
		g_ballMove[Y] = false;
		g_ballMove[Z] = false;
		break;
	default: break;
	}
	DrawScene();
}



GLvoid Mouse(int button, int state, int x, int y)
{
	DrawScene();
}




GLvoid MenuFunc(int button)
{
	switch (button) {
	case RENDERTYPE::SOLID: g_renderModel = RENDERTYPE::SOLID; break;
	case RENDERTYPE::WIRE:  g_renderModel = RENDERTYPE::WIRE; break;
	default: break;
	}

}

GLvoid InitMenu()
{
	int mainMenu{}, subMenu{};

	subMenu = glutCreateMenu(MenuFunc);
	glutAddMenuEntry("Solid", RENDERTYPE::SOLID);
	glutAddMenuEntry("Wire", RENDERTYPE::WIRE);
	mainMenu = glutCreateMenu(MenuFunc);
	glutAddSubMenu("Render Model", subMenu);

	glutAttachMenu(GLUT_RIGHT_BUTTON);
}