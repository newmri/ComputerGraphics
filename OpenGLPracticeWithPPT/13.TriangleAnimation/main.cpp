#include "Define.h"
#include "Objects.h"

GLvoid Init(GLvoid);
GLvoid DrawScene(GLvoid);
GLvoid Reshape(int w, int h);
GLvoid Animate(int n);
GLvoid Keyboard(unsigned char key, int x, int y);
GLvoid Rotate();

const unsigned int ANIMATION_TIME = 1000 / 30;

bool g_rotate = false;
float g_angle = 0.0f;

vector<unique_ptr<CObject>> v;

void main(int argc, char* argv[])
{

	Init();
	glutCreateWindow("13.TriangleAnimation");
	glutDisplayFunc(DrawScene);
	glutReshapeFunc(Reshape);
	glutKeyboardFunc(Keyboard);
	glutTimerFunc(ANIMATION_TIME, Animate, true);

	glutMainLoop();
}


GLvoid Init(GLvoid)
{
	for(int i = 0; i <2; ++i)
	v.push_back(FACTORYMANAGER->CreateObj(OBJTYPE::TRIANGLE,
		MOVETYPE::MOVABLE, Pos(0.0f, 0.0f), BIG_TRIANGLE_SIZE));
	for (int i = 0; i <2; ++i)
		v.push_back(FACTORYMANAGER->CreateObj(OBJTYPE::TRIANGLE,
			MOVETYPE::MOVABLE, Pos(0.0f, BIG_TRIANGLE_SIZE / 2.0f), SMALL_TRIANGLE_SIZE));

	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);

}

GLvoid DrawScene(GLvoid)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	
	for (auto& d : v)
	{
		if (g_rotate) d->Rotate();
		
		d->Render();
	}
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
	v[2]->Update();
	v[3]->Update();
	
	DrawScene();
	glutTimerFunc(ANIMATION_TIME, Animate, true);
}



GLvoid Keyboard(unsigned char key, int x, int y)
{
	switch (key) {
	case 'r': g_rotate = !g_rotate; break;
	}
	DrawScene();
}


GLvoid Rotate()
{
	if (g_angle < 360.0f) g_angle += 0.5f;
	else g_angle = 0.0f;
	glRotatef(g_angle, 0.0f, 1.0f, 0.0f);
}
