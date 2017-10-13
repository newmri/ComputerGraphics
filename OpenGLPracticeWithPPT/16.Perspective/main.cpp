#include "Define.h"

GLvoid Init(GLvoid);
GLvoid DrawScene(GLvoid);
GLvoid Reshape(int w, int h);
GLvoid Animate(int n);
GLvoid Keyboard(unsigned char key, int x, int y);
GLvoid Mouse(int button, int state, int x, int y);
GLvoid ConvertDeviceToOpenGL(int x, int y, Pos* pos);
GLvoid Rotate();
GLvoid RotateLeftObject();
GLvoid RotateRightObject();
GLvoid RenderCoordinates();

const unsigned int ANIMATION_TIME = 1000 / 30;


int winId;

float g_angle = 0.0f;
float g_lAngle = 0.0f;
float g_rAngle = 0.0f;

float g_rotateX = 0.0f, g_rotateY = 0.0f, g_rotateZ = 0.0f;

float g_lRotate[3]{ 0.0f, 0.0f, 0.0f };
float g_rRotate[3]{ 0.0f, 0.0f, 0.0f };

float g_angleD = 1.0f;

bool g_isOnRotate = false;
bool g_isOnLRotate = false;
bool g_isOnRRotate = false;

OBJTYPE g_objType = OBJTYPE::CUBE;

void main(int argc, char* argv[])
{

	Init();
	winId = glutCreateWindow("16.Perspective");
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

}

GLvoid DrawScene(GLvoid)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	if(g_isOnRotate) Rotate();

	RenderCoordinates();

	// Draw floor
	glPushMatrix();
	glTranslatef(0.0f, -50.0f, 0.0f);
	glScalef(15.0f, 4.0f, 5.0f);
	glColor3f(153.0f / RGB, 112.0f / RGB, 0.0f);
	glutSolidCube(10);
	glPopMatrix();

	// Draw left solid object
	glPushMatrix();
	glTranslatef(-30.0f, -10.0f, 30.0f);
	glScalef(1.0f, 3.0f, 1.0f);
	if (g_isOnLRotate) RotateLeftObject();
	glColor3f(1.0f, 0.0f, 0.0f);
	switch (g_objType) {
	case OBJTYPE::CUBE: glutSolidCube(10.0f); break;
	case OBJTYPE::SPHERE: glutSolidSphere(5.0f, 30, 30); break;
	case OBJTYPE::CIRCLECONE: glRotatef(270, 1.0f, 0.0f, 0.0f);
		glutSolidCone(5.0f, 10.0f, 10, 3); break;
	case OBJTYPE::TEAPOT: glutSolidTeapot(10.0f); break;
	}
	glPopMatrix();

	// Draw right wire object
	glPushMatrix();
	glTranslatef(30.0f, -10.0f, 30.0f);
	glScalef(3.0f, 1.0f, 1.0f);
	if (g_isOnRRotate) RotateRightObject();
	switch (g_objType) {
	case OBJTYPE::CUBE: glutWireCube(10.0f); break;
	case OBJTYPE::SPHERE: glutWireSphere(5.0f, 30, 30); break;
	case OBJTYPE::CIRCLECONE: glRotatef(270, 1.0f, 0.0f, 0.0f); glutWireCone(5.0f, 10.0f, 10, 3); break;
	case OBJTYPE::TEAPOT: glutWireTeapot(10.0f); break;
	}
	glPopMatrix();

	
	glutSwapBuffers(); // Draw
}

GLvoid Reshape(int w, int h)
{
	glViewport(0, 0, w, h); // Change viewport with window size
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60.0f, WINDOW_WIDTH / WINDOW_HEIGHT, 1.0f, 120.0f); // Use perspective
	glTranslatef(0.0f, 0.0f, -100.0f);


}


GLvoid Animate(int n)
{

	DrawScene();
	glutTimerFunc(ANIMATION_TIME, Animate, true);
}



GLvoid Keyboard(unsigned char key, int x, int y)
{
	switch (key) {
	case 'x':
	case 'X':
		g_angle = 0.0f;
		g_rotateX = 1.0f;
		g_rotateY = 0.0f;
		g_rotateZ = 0.0f;
		g_isOnRotate = true;
		break;
	case 'y':
	case 'Y':
		g_angle = 0.0f;
		g_rotateX = 0.0f;
		g_rotateY = 1.0f;
		g_rotateZ = 0.0f;
		g_isOnRotate = true;
		break;
	case 'z':
	case 'Z':
		g_angle = 0.0f;
		g_rotateX = 0.0f;
		g_rotateY = 0.0f;
		g_rotateZ = 1.0f;
		g_isOnRotate = true;
		break;
	case 'q':
		glutDestroyWindow(winId);
		exit(0);
		break;
	case '1':
		g_objType = OBJTYPE::CUBE; break;
	case '2':
		g_objType = OBJTYPE::SPHERE; break;
	case '3':
		g_objType = OBJTYPE::CIRCLECONE; break;
	case '4':
		g_objType = OBJTYPE::TEAPOT; break;
	case 'l':
	case 'L':
		g_lAngle = 0;
		for (int i = 0; i < 3; ++i) g_lRotate[i] = 0.0f;
		g_lRotate[rand() % 3] = 1.0f;
		g_isOnLRotate = true;
		break;
	case 'r':
	case 'R':
		g_rAngle = 0;
		for (int i = 0; i < 3; ++i) g_rRotate[i] = 0.0f;
		g_rRotate[rand() % 3] = 1.0f;
		g_isOnRRotate = true;
		break;
	case 'e':
	case 'E':
		g_angle = 0.0f;
		g_rAngle = 0.0f;
		g_lAngle = 0.0f;
		g_rotateX = 0.0f;
		g_rotateY = 0.0f;
		g_rotateZ = 0.0f;
		for (int i = 0; i < 3; ++i) g_lRotate[i] = 0.0f;
		for (int i = 0; i < 3; ++i) g_rRotate[i] = 0.0f;
		g_isOnRotate = false;
		g_isOnLRotate = false;
		g_isOnRRotate = false;

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

GLvoid RenderCoordinates()
{
	glPushMatrix();

	// X
	glPushMatrix();
	glScalef(5.0f, 1.0f, 1.0f);
	glColor3f(1.0f, 0.0f, 0.0f);
	glutSolidCube(COORDINATES_SIZE);
	glPopMatrix();

	// Y
	glPushMatrix();
	glTranslatef(-(COORDINATES_SIZE * 2), COORDINATES_SIZE * 2, 0.0f);
	glScalef(1.0f, 5.0f, 1.0f);
	glColor3f(0.0f, 1.0f, 0.0f);
	glutSolidCube(COORDINATES_SIZE);
	glPopMatrix();


	// Z
	glPushMatrix();
	glTranslatef(-(COORDINATES_SIZE * 2), 0.0f, -(COORDINATES_SIZE * 3));
	glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
	glScalef(1.0f, 5.0f, 1.0f);
	glColor3f(0.0f, 84.0f / RGB, 1.0f);
	glutSolidCube(COORDINATES_SIZE);
	glPopMatrix();
	
	glPopMatrix();

}

GLvoid Rotate()
{

	if (g_angle < 360) g_angle += g_angleD;
	else g_angle = 0.0f;

	glRotatef(g_angle, g_rotateX, g_rotateY, g_rotateZ);

}

GLvoid RotateLeftObject()
{
	if (g_isOnLRotate) {
		if (g_lAngle < 360) g_lAngle += g_angleD;
		else g_lAngle = 0.0f;

		glRotatef(g_lAngle, g_lRotate[0], g_lRotate[1], g_lRotate[2]);
	}
}

GLvoid RotateRightObject()
{
	if (g_isOnRRotate) {
		if (g_rAngle < 360) g_rAngle += g_angleD;
		else g_rAngle = 0.0f;

		glRotatef(g_rAngle, g_rRotate[0], g_rRotate[1], g_rRotate[2]);
	}
}