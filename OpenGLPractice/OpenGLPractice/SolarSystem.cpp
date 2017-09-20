#include <iostream>
#include <gl/glut.h>

void SetUpRC();
void RenderScene();
void ReshapeScene(int w, int h);
void OnTimer(int id);

float g_fAngle = 0;

int main()
{
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA); // Set display mode
	glutInitWindowPosition(100, 100); // Set window position
	glutInitWindowSize(500, 500); // Set window size
	glutCreateWindow("SolarSystem"); // Create window
	glutDisplayFunc(RenderScene); // Set render func
	glutReshapeFunc(ReshapeScene); // Change window size func

	SetUpRC();
	glutMainLoop();

	return 0;
}

void SetUpRC()
{
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // Set background in black
	glShadeModel(GL_FLAT); // Flat rendering mode
	glFrontFace(GL_CCW); // CCW is front

	glEnable(GL_CULL_FACE);
	glEnable(GL_DEPTH_TEST);

}

void ReshapeScene(int w, int h)
{
	float fRange = 10.0f;

	glViewport(0, 0, w, h); // Change viewport with window size
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	if (w <= h) glOrtho(-fRange, fRange, -fRange * h / w, fRange * h / w, -fRange, fRange);
	else glOrtho(-fRange * w / h, fRange * w / h, -fRange, fRange, -fRange, fRange);

}

void RenderScene()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Fill background
	
	glutTimerFunc(50, OnTimer, 1);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glTranslatef(0.0f, 0.0f, -1.0f);

	glPushMatrix();
	glColor3ub(255, 0, 0);
	glutSolidSphere(2.0f, 24, 24); // Draw the sun
	glPopMatrix();
	
	glPushMatrix();
	glColor3ub(0, 0, 200);
	glRotatef(g_fAngle, 0.0f, 1.0f, 0.0f);
	glTranslatef(6.0f, 0.0f, 0.0f);
	glutSolidSphere(0.5f, 24, 24); // Draw the earth

	glPushMatrix();
	glColor3ub(150, 150, 0);
	glRotatef(g_fAngle * 12.0f, 0.0f, 1.0f, 0.0f);
	glTranslatef(2.0f, 0.0f, 0.0f);
	glutSolidSphere(0.2f, 24, 24);		// Draw the moon
	glPopMatrix();

	glPopMatrix();

	glFlush(); // display
}

void OnTimer(int id)
{
	g_fAngle += 1.0f;
	glutPostRedisplay();
}