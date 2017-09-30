#include "Define.h"
#include "Objects.h"

GLvoid Init(GLvoid);
GLvoid DrawScene(GLvoid);
GLvoid Reshape(int w, int h);
GLvoid Animate(int n);
GLvoid Rotate();
GLvoid RenderSpring();
GLvoid Keyboard(unsigned char key, int x, int y);
GLvoid SpecialKeyBoard(int key, int x, int y);
GLvoid AnimationReset();

const unsigned int ANIMATION_TIME = 1000 / 60;
const unsigned int SPRING_NUM =  360 * 7;
const unsigned int RECT_NUM = 10;

float g_angle = 0.0f;

vector<unique_ptr<CObject>> v;

CWave g_cos, g_sin;
Pos g_scale(1.0f,1.0f,1.0f), g_wPos, g_wRotation;

float springEnd = SPRING_NUM;
float rectIdx = RECT_NUM;
bool g_doAnimation = false;

void main(int argc, char* argv[])
{

	Init();
	glutCreateWindow("11.VariousLine");
	glutDisplayFunc(DrawScene);
	glutReshapeFunc(Reshape);
	glutKeyboardFunc(Keyboard);
	glutSpecialFunc(SpecialKeyBoard);
	glutTimerFunc(ANIMATION_TIME, Animate, true);
	glutMainLoop();
}


GLvoid Init(GLvoid)
{
	for (int i = 0; i < RECT_NUM; ++i)
		v.push_back(FACTORYMANAGER->CreateObj(OBJTYPE::RECTANGLE, MOVETYPE::MOVABLE, Pos(0.1f + 0.05, 0.0f), 0.1f));

	g_cos.Init(OBJTYPE::WAVE, MOVETYPE::MOVABLE, WAVETYPE::COS);
	g_sin.Init(OBJTYPE::WAVE, MOVETYPE::MOVABLE, WAVETYPE::SIN);

	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);

}

GLvoid DrawScene(GLvoid)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glColor3f(1.0, 0.5, 0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	// Render cross line
	glBegin(GL_LINES);
		glVertex3f(LEFT, 0.0f, 0.0f);
		glVertex3f(RIGHT, 0.0f, 0.0f);
		glVertex3f(0.0f, TOP, 0.0f);
		glVertex3f(0.0f, BOTTOM, 0.0f);
	glEnd();

	glRotatef(g_angle, g_wRotation.x, g_wRotation.y, g_wRotation.z);
	glScalef(g_scale.x, g_scale.y, g_scale.z);
	glTranslatef(g_wPos.x, g_wPos.y, g_wPos.z);

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
		for (int i = 0; i < rectIdx; ++i) v[i]->Render();
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
	if (g_doAnimation) {
		glutPostRedisplay(); // Re draw
		g_cos.Update();
		g_sin.Update();
		if (springEnd < SPRING_NUM) springEnd += 10.0f;
		else springEnd = 0.0f;
		if (rectIdx < 9) rectIdx += 0.055;
		else rectIdx = 0.0f;
	}
	glutTimerFunc(ANIMATION_TIME, Animate, true);
}


GLvoid Rotate()
{
	if (g_angle < 360.0f) g_angle += 10.0f;
	else g_angle = 0.0f;
}

GLvoid RenderSpring()
{
	float x{}, y{};
	glBegin(GL_LINE_STRIP);
	float interval{};
	float angle{};
	for (int i = 0; i < springEnd; i += 10) {
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

GLvoid Keyboard(unsigned char key, int x, int y)
{
	switch (key) {
	case 'S':
		g_scale.x += 0.1f;
		g_scale.y += 0.1f;
		g_scale.z += 0.1f;
		break;
	case 's':
		g_scale.x += -0.1f;
		g_scale.y += -0.1f;
		g_scale.z += -0.1f;
		break;
	case 'A':
		g_doAnimation = true;
		break;
	case 'a':
		g_doAnimation = false;
		break;
	case 'x':
		g_wRotation.x = 1.0f;
		g_wRotation.y = 0.0f;
		g_wRotation.z = 0.0f;
		Rotate();
		break;
	case 'y':
		g_wRotation.x = 0.0f;
		g_wRotation.y = 1.0f;
		g_wRotation.z = 0.0f;
		Rotate();
		break;
	case 'z':
		g_wRotation.x = 0.0f;
		g_wRotation.y = 0.0f;
		g_wRotation.z = 1.0f;
		Rotate();
		break;
	case 'r': AnimationReset(); break;
	case 'i': g_wPos.x = 0.0f;
		g_wRotation.x = 0.0f;
		g_wRotation.y = 0.0f;
		g_wRotation.z = 0.0f; break;

	}

	DrawScene();
}

GLvoid SpecialKeyBoard(int key, int x, int y)
{
	if (key == GLUT_KEY_LEFT) g_wPos.x += -0.1f;
	else if (key == GLUT_KEY_RIGHT) g_wPos.x += 0.1f;
	DrawScene();
	
}

GLvoid AnimationReset()
{
	springEnd = SPRING_NUM;
	rectIdx = RECT_NUM;
	g_cos.ResetWaveEnd();
	g_sin.ResetWaveEnd();
}