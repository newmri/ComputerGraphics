#include "Define.h"
#include "Objects.h"

GLvoid Init(GLvoid);
GLvoid DrawScene(GLvoid);
GLvoid Reshape(int w, int h);
GLvoid Animate(int n);
GLvoid RenderTornado();
GLvoid RenderZigZag();
GLvoid Keyboard(unsigned char key, int x, int y);
GLvoid MenuFunc(int button);

const unsigned int ANIMATION_TIME = 1000 / 30;

const unsigned int RECT_NUM = 10;

float g_angle = 0.0f;

const unsigned int Tornado_NUM = 360 * 7;

float TornadoEnd = Tornado_NUM;

vector<unique_ptr<CObject>> v;
CWave g_cos, g_sin;

OBJTYPE g_shape = OBJTYPE::RECTANGLE;
OBJTYPE g_pathShape = OBJTYPE::CIRCLE;



void main(int argc, char* argv[])
{

	Init();
	glutCreateWindow("12.MoveWithPath");
	glutDisplayFunc(DrawScene);
	glutReshapeFunc(Reshape);
	glutKeyboardFunc(Keyboard);
	glutTimerFunc(ANIMATION_TIME, Animate, true);

	int mainMenu{}, subMenu{};
	subMenu = glutCreateMenu(MenuFunc);
	glutAddMenuEntry("Rectangle", OBJTYPE::RECTANGLE);
	glutAddMenuEntry("Triangle", OBJTYPE::TRIANGLE);
	mainMenu = glutCreateMenu(MenuFunc);
	glutAddSubMenu("Shape", subMenu);

	glutAttachMenu(GLUT_RIGHT_BUTTON);

	glutMainLoop();
}


GLvoid Init(GLvoid)
{

	v.push_back(FACTORYMANAGER->CreateObj(OBJTYPE::CIRCLE, MOVETYPE::MOVABLE, Pos(0.0f,0.0f), 2.5f));
	v.push_back(FACTORYMANAGER->CreateObj(OBJTYPE::RECTANGLE, MOVETYPE::MOVABLE, Pos(0.0f, 0.0f), MIN_SIZE));
	v.push_back(FACTORYMANAGER->CreateObj(OBJTYPE::TRIANGLE,
		MOVETYPE::MOVABLE, Pos(0.0f, 0.0f), MIN_SIZE));

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

	switch (g_pathShape) {
	case OBJTYPE::CIRCLE: v[OBJTYPE::CIRCLE]->Render(); break;
	case OBJTYPE::SINWAVE: g_sin.Render(); break;
	case OBJTYPE::TORNADO: RenderTornado(); break;
	case OBJTYPE::ZIGZAG: RenderZigZag(); break;
	}

	glPushMatrix();
	if (g_pathShape == OBJTYPE::TORNADO) {
		glTranslatef(0.0f, -0.75f, 0.0f);
		glRotatef(90.0f, 0.0f, 0.0f, 1.0f);
	}
	v[g_shape]->Render();
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
	v[g_shape]->Update();
	DrawScene();
	glutTimerFunc(ANIMATION_TIME, Animate, true);
}


GLvoid Rotate()
{
	if (g_angle < 360.0f) g_angle += 10.0f;
	else g_angle = 0.0f;
}

GLvoid RenderTornado()
{
	glPushMatrix();
	glTranslatef(0.0f, -0.75f, 0.0f);
	glRotatef(90.0f, 0.0f, 0.0f, 1.0f);
	float x{}, y{};
	glBegin(GL_LINE_STRIP);
	float interval{};
	float angle{};
	float size{ 7.0f };
	for (int i = 0; i < TornadoEnd; i += 10) {
		angle = i * PIE / 180;
		x = cos(angle) / size;
		y = sin(angle) / size;
		
		if (i % 360 == 0 && i != 0) size -= 0.5f;
		glVertex2f(x + interval, y);

		interval += 0.006f;
		
	}
	glEnd();

	glPopMatrix();
}

GLvoid Keyboard(unsigned char key, int x, int y)
{
	switch (key) {
	case '1':
		g_pathShape = OBJTYPE::SINWAVE;
		for (int i = 1; i < 3; ++i) v[i]->SetPath(OBJTYPE::SINWAVE);
		break;
	case '2':
		g_pathShape = OBJTYPE::TORNADO;
		for (int i = 1; i < 3; ++i) v[i]->SetPath(OBJTYPE::TORNADO);
		break;
	case '3':
		g_pathShape = OBJTYPE::ZIGZAG;
		for (int i = 1; i < 3; ++i) v[i]->SetPath(OBJTYPE::ZIGZAG);
		break;
	default:break;
	}

	DrawScene();
}

GLvoid MenuFunc(int button)
{
	switch (button) {
	case OBJTYPE::RECTANGLE: g_shape = OBJTYPE::RECTANGLE; break;
	case OBJTYPE::TRIANGLE:  g_shape = OBJTYPE::TRIANGLE; break;
	default: break;
	}

}


GLvoid RenderZigZag()
{
	glBegin(GL_LINE_STRIP);
	for (float x = -0.75f, y = 0.75; x < 1.0f; x += 0.15) {
		glVertex2f(x, y);
		y = -y;
	}
	glEnd();
}