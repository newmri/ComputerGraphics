#include <iostream>
#include <gl/glut.h>

void SetUpRC();
void RenderScene();
void ReshapeScene(int w, int h);
void OnTimer(int id);

float g_fAngle = 0;
float g_fEarth = 0.0f;
float g_fMoon = 0.0f;

float g_lightPos[4] = { 0.0f, 0.0f, 3.0f, 1.0f };
float g_diffuseLight[4] = { 1.0f, 0.5f, 0.5f, 1.0f };
float g_ambientLight[4] = { 0.0f, 0.0f, 0.0f, 1.0f };
float g_specularLight[4] = { 1.0f, 1.0f, 1.0f, 1.0f };
float g_specref[4] = { 0.7f, 0.7f, 0.7f, 1.0f };

int main()
{
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA); // Set display mode
	glutInitWindowPosition(100, 100); // Set window position
	glutInitWindowSize(500, 500); // Set window size
	glutCreateWindow("ShinySphere"); // Create window
	glutDisplayFunc(RenderScene); // Set render func
	glutReshapeFunc(ReshapeScene); // Change window size func

	SetUpRC();
	glutMainLoop();

	return 0;
}

void SetUpRC()
{
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // Set background in black
	glShadeModel(GL_SMOOTH); // Smooth rendering mode
	glFrontFace(GL_CCW); // CCW is front

	glEnable(GL_CULL_FACE);
	glEnable(GL_DEPTH_TEST);

	glEnable(GL_LIGHTING);
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, g_ambientLight);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, g_diffuseLight);
	glLightfv(GL_LIGHT0, GL_SPECULAR, g_specularLight);
	glLightfv(GL_LIGHT0, GL_SPECULAR, g_lightPos);
	glEnable(GL_LIGHT0);
	glEnable(GL_COLOR_MATERIAL);

	glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
	glMaterialfv(GL_FRONT, GL_SPECULAR, g_specref);
	glMateriali(GL_FRONT, GL_SHININESS, 128);

}

void ReshapeScene(int w, int h)
{
	float fAspect = (float)w / (float)h;

	glViewport(0, 0, w, h);	

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	gluPerspective(45.0f, fAspect, 1.0f, 425.0f);

}

void RenderScene()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Fill background

	glutTimerFunc(50, OnTimer, 1);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glTranslatef(0.0f, 0.0f, -10.0f);
	glLightfv(GL_LIGHT0, GL_POSITION, g_lightPos); // Set light position

	glEnable(GL_LIGHTING);
	
	glPushMatrix();
	glColor3ub(50, 50, 255);
	glRotatef(g_fAngle, 0.0f, 1.0f, 0.0f);
	glutSolidSphere(1.0f, 24, 24);
	glPopMatrix();

	glFlush(); // display
}

void OnTimer(int id)
{
	g_fAngle += 1.0f;
	glutPostRedisplay();
}