#include "Define.h"
#include "Objects.h"

GLvoid Init(GLvoid);
GLvoid DrawScene(GLvoid);
GLvoid Reshape(int w, int h);
GLvoid Animate(int n);
GLvoid RenderSpring();

const unsigned int ANIMATION_TIME = 1000 / 30;


vector<unique_ptr<CObject>> v;

CWave g_cos, g_sin;

void main(int argc, char* argv[])
{

	Init();
	glutCreateWindow("11.VariousLine");
	glutDisplayFunc(DrawScene);
	glutReshapeFunc(Reshape);

	glutTimerFunc(ANIMATION_TIME, Animate, true);
	glutMainLoop();
}


GLvoid Init(GLvoid)
{
	for (int i = 0; i < 10; ++i) 
		v.push_back(FACTORYMANAGER->CreateObj(OBJTYPE::RECTANGLE, MOVETYPE::MOVABLE, Pos(0.1f + 0.05, 0.0f), 0.1f));

	g_cos.Init(OBJTYPE::WAVE, MOVETYPE::MOVABLE, WAVETYPE::COS);
	g_sin.Init(OBJTYPE::WAVE, MOVETYPE::MOVABLE, WAVETYPE::SIN);

	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);

}

GLvoid DrawScene(GLvoid)
{

	glColor3f(1.0, 0.5, 0);

	// Render cross line
	glBegin(GL_LINES);
		glVertex3f(LEFT, 0.0f, 0.0f);
		glVertex3f(RIGHT, 0.0f, 0.0f);
		glVertex3f(0.0f, TOP, 0.0f);
		glVertex3f(0.0f, BOTTOM, 0.0f);
	glEnd();

	// Render cos wave
	glPushMatrix();
		glTranslatef(-0.75f, 0.5f, 0.0f);
		g_cos.Render();
	glPopMatrix();

	// Render sin wave
	glPushMatrix();
		glTranslatef(-0.75f, 0.25f, 0.0f);
		g_sin.Render();
	glPopMatrix();

	// Render spring
	glPushMatrix();
		glTranslatef(-0.75f, -0.15f, 0.0f);
		RenderSpring();
	glPopMatrix();

	// Render rect
	glPushMatrix();
		glTranslatef(-0.75f, -0.5f, 0.0f);
		for (auto& d : v) d->Render();
	glPopMatrix();


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
	glutPostRedisplay(); // Re draw
	glutTimerFunc(ANIMATION_TIME, Animate, true);
}

GLvoid RenderSpring()
{
	float x{}, y{};
	glBegin(GL_LINE_STRIP);
	float interval{};
	float angle{};
	for (int i = 0; i < 360 * 7; i += 10) {
		angle = i * PIE / 180;
		x = cos(angle) / 7.0f;
		y = sin(angle) / 7.0f;

		glColor3f(interval, 0.0f, 0.0f);
		glVertex2f(x + interval, y);
		glColor3f(0.0f, 0.0f, interval);
		glVertex2f(x + interval, y);

		interval += 0.006f;
	}
	glEnd();
}