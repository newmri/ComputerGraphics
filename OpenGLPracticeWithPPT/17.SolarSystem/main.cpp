#include "Define.h"

GLvoid Init(GLvoid);
GLvoid DrawScene(GLvoid);
GLvoid Reshape(int w, int h);
GLvoid Animate(int n);
GLvoid Keyboard(unsigned char key, int x, int y);
GLvoid Mouse(int button, int state, int x, int y);
GLvoid Rotate();
GLvoid RenderSolar();
GLvoid RenderBluePlanet();
GLvoid RenderYellowPlanet();
GLvoid RenderWhitePlanet();
GLvoid RenderMoonTrack();
GLvoid MenuFunc(int button);
GLvoid InitMenu();

const unsigned int ANIMATION_TIME = 1000 / 30;


int winId;

float g_whiteAngle = 0.0f, g_yellowAngle = 0.0f, g_blueAngle = 0.0f;
float g_whiteMoonAngle = 0.0f, g_yellowMoonAngle = 0.0f, g_blueMoonAngle = 0.0f;

RENDERTYPE g_renderModel = RENDERTYPE::SOLID;

void main(int argc, char* argv[])
{

	Init();

	winId = glutCreateWindow("17.SolarSystem");
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

	RenderSolar();
	RenderWhitePlanet();
	RenderYellowPlanet();
	RenderBluePlanet();

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
	if(g_whiteAngle < 360.0f) g_whiteAngle += WHITE_SPEED;
	else g_whiteAngle = 0.0f;

	if (g_whiteMoonAngle < 360.0f) g_whiteMoonAngle += MOON_SPEED;
	else g_whiteMoonAngle = 0.0f;

	if (g_yellowAngle < 360.0f) g_yellowAngle += YELLOW_SPEED;
	else g_yellowAngle = 0.0f;

	if (g_yellowMoonAngle < 360.0f) g_yellowMoonAngle += MOON_SPEED;
	else g_yellowMoonAngle = 0.0f;

	if (g_blueAngle < 360.0f) g_blueAngle += BLUE_SPEED;
	else g_blueAngle = 0.0f;

	if (g_blueMoonAngle < 360.0f) g_blueMoonAngle += MOON_SPEED;
	else g_blueMoonAngle = 0.0f;


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
	default: break;
	}
	DrawScene();
}



GLvoid Mouse(int button, int state, int x, int y)
{
	DrawScene();
}




GLvoid RenderSolar()
{
	glColor3f(1.0f, 0.0f, 0.0f);
	if(g_renderModel == RENDERTYPE::SOLID) glutSolidSphere(SUN_RAD, 30, 30);
	else if (g_renderModel == RENDERTYPE::WIRE) glutWireSphere(SUN_RAD, 30, 30);
}

GLvoid RenderWhitePlanet()
{
	// Render track
	glPushMatrix();

	glScalef(3.0f, 1.0f, 1.0f);
	glColor3f(1.0f, 1.0f, 1.0f);
	glBegin(GL_POINTS);
	for (int i = 0; i < 360; i += 10) {
		double angle = (i * PIE / 180);
		double x = TRACK_RAD * cos(angle);
		double y = TRACK_RAD * sin(angle);
		glVertex2f(x, y);
	}
	glEnd();

	glPopMatrix();

	glPushMatrix();

	// Render white planet
	glTranslatef((TRACK_RAD * cos(g_whiteAngle * PIE / 180)) * 3,
		TRACK_RAD * sin(g_whiteAngle * PIE / 180),
		-(TRACK_RAD * sin(g_whiteAngle * PIE / 180)));

	if (g_renderModel == RENDERTYPE::SOLID) glutSolidSphere(PLANET_RAD, 30, 30);
	else if (g_renderModel == RENDERTYPE::WIRE) glutWireSphere(PLANET_RAD, 30, 30);

	glPushMatrix();

	// Render moon track
	RenderMoonTrack();

	// Render moon
	glColor3f(1.0f, 1.0f, 0.0f);
	glTranslatef((MOON_TRACK_RAD * cos(g_whiteMoonAngle * PIE / 180)) * 3,
		MOON_TRACK_RAD * sin(g_whiteMoonAngle * PIE / 180),
		-(MOON_TRACK_RAD * sin(g_whiteMoonAngle * PIE / 180)));

	if (g_renderModel == RENDERTYPE::SOLID) glutSolidSphere(MOON_RAD, 30, 30);
	else if (g_renderModel == RENDERTYPE::WIRE) glutWireSphere(MOON_RAD, 30, 30);

	glPopMatrix();
	glPopMatrix();
}

GLvoid RenderYellowPlanet()
{
	glPushMatrix();

	glRotatef(45.0f, 0.0f, 0.0f, 1.0f);

	// Render track
	glPushMatrix();

	glScalef(3.0f, 1.0f, 1.0f);
	glColor3f(1.0f, 1.0f, 0.0f);
	glBegin(GL_POINTS);
	for (int i = 0; i < 360; i += 10) {
		double angle = (i * PIE / 180);
		double x = TRACK_RAD * cos(angle);
		double y = TRACK_RAD * sin(angle);
		glVertex2f(x, y);
	}
	glEnd();

	glPopMatrix();

	// Render yellow planet
	glPushMatrix();

	glTranslatef((TRACK_RAD * cos(g_yellowAngle * PIE / 180)) * 3,
		TRACK_RAD * sin(g_yellowAngle * PIE / 180),
		-(TRACK_RAD * sin(g_yellowAngle * PIE / 180)));

	if (g_renderModel == RENDERTYPE::SOLID) glutSolidSphere(PLANET_RAD, 30, 30);
	else if (g_renderModel == RENDERTYPE::WIRE) glutWireSphere(PLANET_RAD, 30, 30);
	
	// Render moon track
	glPushMatrix();

	glRotatef(-45.0f, 0.0f, 0.0f, 1.0f);
	RenderMoonTrack();

	// Render moon
	glColor3f(1.0f, 1.0f, 0.0f);
	glTranslatef((MOON_TRACK_RAD * cos(g_yellowMoonAngle * PIE / 180)) * 3,
		MOON_TRACK_RAD * sin(g_yellowMoonAngle * PIE / 180),
		-(MOON_TRACK_RAD * sin(g_yellowMoonAngle * PIE / 180)));

	if (g_renderModel == RENDERTYPE::SOLID) glutSolidSphere(MOON_RAD, 30, 30);
	else if (g_renderModel == RENDERTYPE::WIRE) glutWireSphere(MOON_RAD, 30, 30);

	glPopMatrix();

	glPopMatrix();

	glPopMatrix();
}

GLvoid RenderBluePlanet()
{
	glPushMatrix();

	glRotatef(135.0f, 0.0f, 0.0f, 1.0f);

	// Render track
	glPushMatrix();

	glScalef(3.0f, 1.0f, 1.0f);
	glColor3f(1.0f / RGB, 0.0f, 1.0f);
	glBegin(GL_POINTS);
	for (int i = 0; i < 360; i += 10) {
		double angle = (i * PIE / 180);
		double x = TRACK_RAD * cos(angle);
		double y = TRACK_RAD * sin(angle);
		glVertex2f(x, y);
	}
	glEnd();

	glPopMatrix();

	// Render blue planet
	glPushMatrix();

	glTranslatef((TRACK_RAD * cos(g_blueAngle * PIE / 180)) * 3,
		TRACK_RAD * sin(g_blueAngle * PIE / 180), TRACK_RAD * sin(g_blueAngle * PIE / 180));

	if (g_renderModel == RENDERTYPE::SOLID) glutSolidSphere(PLANET_RAD, 30, 30);
	else if (g_renderModel == RENDERTYPE::WIRE) glutWireSphere(PLANET_RAD, 30, 30);

	// Render moon track
	glPushMatrix();

	glRotatef(-135.0f, 0.0f, 0.0f, 1.0f);
	RenderMoonTrack();

	// Render moon
	glColor3f(1.0f, 1.0f, 0.0f);
	glTranslatef((MOON_TRACK_RAD * cos(g_blueMoonAngle * PIE / 180)) * 3,
		MOON_TRACK_RAD * sin(g_blueMoonAngle * PIE / 180),
		-(MOON_TRACK_RAD * sin(g_blueMoonAngle * PIE / 180)));

	if (g_renderModel == RENDERTYPE::SOLID) glutSolidSphere(MOON_RAD, 30, 30);
	else if (g_renderModel == RENDERTYPE::WIRE) glutWireSphere(MOON_RAD, 30, 30);

	glPopMatrix();

	glPopMatrix();

	glPopMatrix();
}

GLvoid RenderMoonTrack()
{
	glPushMatrix();

	glScalef(3.0f, 1.0f, 1.0f);
	glColor3f(29.0f / RGB, 219.0f / RGB, 22.0f / RGB);
	glBegin(GL_POINTS);
	for (int i = 0; i < 360; i += 10) {
		double angle = (i * PIE / 180);
		double x = MOON_TRACK_RAD * cos(angle);
		double y = MOON_TRACK_RAD * sin(angle);
		glVertex2f(x, y);
	}
	glEnd();

	glPopMatrix();
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