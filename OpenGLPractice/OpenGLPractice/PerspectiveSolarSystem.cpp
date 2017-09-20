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
	glutCreateWindow("PerspectiveSolarSystem"); // Create window
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
	float fAspect = (float)w / (float)h;

	glViewport(0, 0, w, h);	// 뷰포트를 윈도우 크기에 맞춘다.

	glMatrixMode(GL_PROJECTION);		// 프로젝션 매트릭스를 초기화 한다.
	glLoadIdentity();

	gluPerspective(45.0f, fAspect, 1.0f, 425.0f);

}

void RenderScene()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Fill background

	glutTimerFunc(50, OnTimer, 1);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glTranslatef(0.0f, 0.0f, -20.0f);

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