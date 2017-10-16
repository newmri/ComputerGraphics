#include "Define.h"

GLvoid Init(GLvoid);
GLvoid DrawScene(GLvoid);
GLvoid Reshape(int w, int h);
GLvoid Animate(int n);
GLvoid Keyboard(unsigned char key, int x, int y);
GLvoid Mouse(int button, int state, int x, int y);
GLvoid Rotate();


const unsigned int ANIMATION_TIME = 1000 / 30;


int winId;

float g_angle[3]{ 0.0f, 0.0f, 0.0f };
Vector3 g_cranePos, g_rotation[3];

float g_craneSpeed = CRANE_SPEED;
float g_bodyAndArmRotation = -CRANE_SPEED;

// Bottom, Body, Arm
bool g_isOnRotation[3] = { false, false, false };
void main(int argc, char* argv[])
{

	Init();

	winId = glutCreateWindow("19.Crane");
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
			glTranslatef(g_cranePos.x, g_cranePos.y, g_cranePos.z);

			if(g_isOnRotation[BOTTOM])
			glRotatef(g_angle[BOTTOM], g_rotation[BOTTOM].x, g_rotation[BOTTOM].y, g_rotation[BOTTOM].z);
			// Draw bottom
			glutSolidCube(BOTTOM_SIZE);
			glPushMatrix();
			
			glColor3f(1.0f, 1.0f, 0.0f);
			glTranslatef(0.0f, BOTTOM_SIZE - (BODY_SIZE / 2.0f), 0.0f);
			if (g_isOnRotation[BODY]) 
				glRotatef(g_angle[BODY], g_rotation[BODY].x, g_rotation[BODY].y, g_rotation[BODY].z);
			// Draw body
			glutSolidCube(BODY_SIZE);

			glPushMatrix();
			glColor3f(0.0f, 5.0f, 0.0f);
			glScalef(1.0f, 2.0f, 1.0f);
			glTranslatef(0.0f, BODY_SIZE - (ARM_SIZE), 0.0f);
			if (g_isOnRotation[ARM])
				glRotatef(g_angle[ARM], g_rotation[ARM].x, g_rotation[ARM].y, g_rotation[ARM].z);
			// Draw arm
			glutSolidCube(ARM_SIZE);
			glPopMatrix();

			glPopMatrix();

			
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
	if ((g_cranePos.x < -((FLOOR_SIZE * 5.0f) + (BOTTOM_SIZE / 2.0f))) ||
		((g_cranePos.x > ((FLOOR_SIZE * 5.0f) + (BOTTOM_SIZE / 2.0f))))) g_craneSpeed = -g_craneSpeed;

	for(int i = 1; i<3; ++i){
		if (g_isOnRotation[i]) {
			g_angle[i] += g_bodyAndArmRotation;
			if (g_angle[i] < -90.0f || g_angle[i] > 90.0f) g_bodyAndArmRotation = -g_bodyAndArmRotation;
			cout << g_angle[i] << endl;
		}
	}
	g_cranePos.x += g_craneSpeed;
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
	case 'i': CAMERAMANAGER->Reset(); break;

	case '1':
		ZeroMemory(&g_rotation, sizeof(g_rotation));
		ZeroMemory(&g_isOnRotation, sizeof(g_isOnRotation));
		g_isOnRotation[BOTTOM] = true;
		g_rotation[BOTTOM].y = 1.0f;
		break;
	case '2':
		ZeroMemory(&g_rotation, sizeof(g_rotation));
		ZeroMemory(&g_isOnRotation, sizeof(g_isOnRotation));
		g_isOnRotation[BODY] = true;
		g_rotation[BODY].x = 1.0f;
		break;
	case '3':
		ZeroMemory(&g_rotation, sizeof(g_rotation));
		ZeroMemory(&g_isOnRotation, sizeof(g_isOnRotation));
		g_isOnRotation[BODY] = true;
		g_rotation[BODY].y = 1.0f;
		break;
	case '4':
		ZeroMemory(&g_rotation, sizeof(g_rotation));
		ZeroMemory(&g_isOnRotation, sizeof(g_isOnRotation));
		g_isOnRotation[ARM] = true;
		g_rotation[ARM].x = 1.0f;
		g_bodyAndArmRotation = -CRANE_SPEED;
		break;
	case '5':
		ZeroMemory(&g_rotation, sizeof(g_rotation));
		ZeroMemory(&g_isOnRotation, sizeof(g_isOnRotation));
		g_isOnRotation[ARM] = true;
		g_rotation[ARM].y = 1.0f;
		g_bodyAndArmRotation = -CRANE_SPEED;
		break;
	default: break;
	}
	DrawScene();
}



GLvoid Mouse(int button, int state, int x, int y)
{
	DrawScene();
}




