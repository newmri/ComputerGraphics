#include "Define.h"

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
GLvoid MenuFunc(int button);

const unsigned int ANIMATION_TIME = 1000 / 30;


int winId;

float g_yAngle = 45.0f;
float g_frontOpen = false;
float g_frontZ = 0.0f;
float g_topOpen = false;
float g_topZ = 0.0f;
void main(int argc, char* argv[])
{

	Init();

	winId = glutCreateWindow("23.RGBCube");
	glutDisplayFunc(RenderScene);
	glutReshapeFunc(Reshape);
	glutKeyboardFunc(Keyboard);
	glutMouseFunc(Mouse);
	glutTimerFunc(ANIMATION_TIME, Animate, true);
	glutAttachMenu(GLUT_RIGHT_BUTTON);
	glutMainLoop();
}


GLvoid Init(GLvoid)
{
	srand((unsigned int)time(NULL));
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	glFrontFace(GL_CCW);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);

	int subMenu = glutCreateMenu(MenuFunc);
	glutAddMenuEntry("Hidden Surface Delete On", HIDDEN_SURFAE_DELETE_ON);
	glutAddMenuEntry("Hidden Surface Delete off", HIDDEN_SURFACE_DELETE_OFF);
	glutAddMenuEntry("Culling On", CULLING_ON);
	glutAddMenuEntry("Culling off", CULLING_OFF);
	glutAddMenuEntry("Flat On", SHADING_FLAT);
	glutAddMenuEntry("Smooth On", SHADING_SMOOTH);
	glutAddMenuEntry("Front Side Open", FRONT_OPEN);
	glutAddMenuEntry("Front Side Close", FRONT_CLOSE);
	glutAddMenuEntry("Top Side Open", TOP_OPEN);
	glutAddMenuEntry("Top Side Close", TOP_CLOSE);
	int mainMenu = glutCreateMenu(MenuFunc);
	glutAddSubMenu("Select", subMenu);


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
	int ret{};
	CAMERAMANAGER->Update();
	if (g_yAngle >= MAX_DEGREE) g_yAngle = 0.0f;
	else g_yAngle += 1.0f;

	if (g_frontOpen) { if (g_frontZ < CUBE_RAD * 2.0f)  g_frontZ += 0.1f; }
	else { if (g_frontZ > 0) g_frontZ -= 0.1f; }

	if (g_topOpen) { if (g_topZ < CUBE_RAD * 2.0f)  g_topZ += 0.1f; }
	else { if (g_topZ > 0) g_topZ -= 0.1f; }
}

GLvoid Render()
{
	glPushMatrix();
	glRotatef(30.0f, 1.0f, 0.0f, 0.0f);
	glRotatef(g_yAngle, 0.0f, 1.0f, 0.0f);
	glBegin(GL_QUADS);

	// Front
	glColor3f(1.0f, 1.0f, 1.0f);
	glVertex3f(CUBE_RAD, CUBE_RAD, 0.0f); // Top Right
	glColor3f(1.0f, 0.0f, 1.0f);
	glVertex3f(-CUBE_RAD + g_frontZ, CUBE_RAD, g_frontZ); // Top Left
	glColor3f(1.0f, 0.0f, 0.0f);
	glVertex3f(-CUBE_RAD + g_frontZ, -CUBE_RAD, g_frontZ); // Bottom Left
	glColor3f(1.0f, 1.0f, 0.0f);
	glVertex3f(CUBE_RAD, -CUBE_RAD, 0.0f); // Bottom Right
	
	// Back
	glColor3f(0.0f, 1.0f, 1.0f);
	glVertex3f(CUBE_RAD, CUBE_RAD, -CUBE_RAD * 2.0f); // Top Right
	glColor3f(0.0f, 0.0f, 1.0f);
	glVertex3f(-CUBE_RAD, CUBE_RAD, -CUBE_RAD * 2.0f); // Top Left
	glColor3f(0.0f, 0.0f, 0.0f);
	glVertex3f(-CUBE_RAD, -CUBE_RAD, -CUBE_RAD * 2.0f); // Bottom Left
	glColor3f(0.0f, 1.0f, 0.0f);
	glVertex3f(CUBE_RAD, -CUBE_RAD, -CUBE_RAD * 2.0f); // Bottom Right
	
	// Top
	glColor3f(0.0f, 1.0f, 1.0f);
	glVertex3f(CUBE_RAD, CUBE_RAD, -CUBE_RAD * 2.0f); // Top Right
	glColor3f(0.0f, 0.0f, 1.0f);
	glVertex3f(-CUBE_RAD, CUBE_RAD, -CUBE_RAD * 2.0f); // Top Left
	glColor3f(1.0f, 0.0f, 1.0f);
	glVertex3f(-CUBE_RAD, CUBE_RAD + g_topZ, -g_topZ); // Bottom Left
	glColor3f(1.0f, 1.0f, 1.0f);
	glVertex3f(CUBE_RAD, CUBE_RAD + g_topZ, -g_topZ); // Bottom Right

	// Bottom
	glColor3f(0.0f, 1.0f, 0.0f);
	glVertex3f(CUBE_RAD, -CUBE_RAD, -CUBE_RAD * 2.0f); // Top Right
	glColor3f(0.0f, 0.0f, 0.0f);
	glVertex3f(-CUBE_RAD, -CUBE_RAD, -CUBE_RAD * 2.0f); // Top Left
	glColor3f(1.0f, 0.0f, 0.0f);
	glVertex3f(-CUBE_RAD, -CUBE_RAD, 0.0f); // Bottom Left
	glColor3f(1.0f, 1.0f, 0.0f);
	glVertex3f(CUBE_RAD, -CUBE_RAD, 0.0f); // Bottom Right

    // Left
	glColor3f(1.0f, 0.0f, 1.0f);
	glVertex3f(-CUBE_RAD, CUBE_RAD, 0.0f); // Top Right
	glColor3f(0.0f, 0.0f, 1.0f);
	glVertex3f(-CUBE_RAD, CUBE_RAD, -CUBE_RAD * 2.0f); // Top Left
	glColor3f(0.0f, 0.0f, 0.0f);
	glVertex3f(-CUBE_RAD, -CUBE_RAD, -CUBE_RAD * 2.0f); // Bottom Left
	glColor3f(1.0f, 0.0f, 0.0f);
	glVertex3f(-CUBE_RAD, -CUBE_RAD, 0.0f); // Bottom Right

	// Right
	glColor3f(0.0f, 1.0f, 1.0f);
	glVertex3f(CUBE_RAD, CUBE_RAD, -CUBE_RAD * 2.0f);
	glColor3f(1.0f, 1.0f, 1.0f);
	glVertex3f(CUBE_RAD, CUBE_RAD, 0.0f);
	glColor3f(1.0f, 1.0f, 0.0f);
	glVertex3f(CUBE_RAD, -CUBE_RAD, 0.0f);
	glColor3f(0.0f, 1.0f, 0.0f);
	glVertex3f(CUBE_RAD, -CUBE_RAD, -CUBE_RAD * 2.0f);
	

	glEnd();
	
	glPopMatrix();
}

GLvoid MenuFunc(int button)
{
	switch (button) {
	case HIDDEN_SURFAE_DELETE_ON: glEnable(GL_DEPTH_TEST); break;
	case HIDDEN_SURFACE_DELETE_OFF: glDisable(GL_DEPTH_TEST); break;
	case CULLING_ON: glEnable(GL_CULL_FACE); glCullFace(GL_BACK); break;
	case CULLING_OFF: glDisable(GL_CULL_FACE); break;
	case SHADING_FLAT: 	glShadeModel(GL_FLAT); break;
	case SHADING_SMOOTH: 	glShadeModel(GL_SMOOTH); break;
	case FRONT_OPEN: 	g_frontOpen = true; break;
	case FRONT_CLOSE: 	g_frontOpen = false; break;
	case TOP_OPEN: 	g_topOpen = true; break;
	case TOP_CLOSE: 	g_topOpen = false; break;
	default: break;
	}
}