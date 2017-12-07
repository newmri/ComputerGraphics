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

const unsigned int ANIMATION_TIME = 1000 / 30;


int winId;


GLfloat g_fog_color[4] = { 0.7, 0.7, 0.7, 1.0 };
GLfloat g_density = 0.7;
GLfloat g_start = 0.0;
GLfloat g_end = 10.0;
bool g_exp = true;
void main(int argc, char* argv[])
{

	Init();

	winId = glutCreateWindow("35.Fog");
	glutDisplayFunc(RenderScene);
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
	glFrontFace(GL_CCW);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);



}

GLvoid RenderScene(GLvoid)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);
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
	case 'a':
	case 'q':
	case '+':
	case '-': CAMERAMANAGER->SetMove(key); break;
	case 'i': CAMERAMANAGER->Reset(); break;

	case 'd': if (g_density < 1.0f) g_density += 0.1f; break;
	case 'D': if (g_density > 0.1f) g_density -= 0.1f; else g_density = 0.0f; break;
	case 's': g_start += 1.0f; break;
	case 'S': g_start -= 1.0f; break;
	case 'e': g_end += 1.0f; break;
	case 'E': g_end -= 1.0f; break;
	case 'M':
	case 'm': g_exp = !g_exp; break;
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
	CAMERAMANAGER->Update();

}

GLvoid Render()
{
	glEnable(GL_FOG);
	if(g_exp) glFogf(GL_FOG_MODE, GL_EXP2);
	else glFogf(GL_FOG_MODE, GL_LINEAR);
	glFogfv(GL_FOG_COLOR, g_fog_color);
	glFogf(GL_FOG_DENSITY, g_density); // fog mode가 GL_EXP, GL_EXP2일 경우 밀도의 설정이 가능
	glHint(GL_FOG_HINT, GL_NICEST);
	glFogf(GL_FOG_START, g_start);
	glFogf(GL_FOG_END, g_end); // end는 world coordinate상에서 안개 끝 위치를 의미한다.
	glPushMatrix();

	glRotatef(45.0f, 0.0f, 1.0f, 0.0f);
	glRotatef(15.0f, 1.0f, 0.0f, 0.0f);

	glPushMatrix();
	glColor3f(0.0f, 1.0f, 0.f);
	glutSolidCube(5);
	glPopMatrix();
	glTranslatef(0.0f, 0.0f, 2.5f + 5.0f);
	glColor3f(1.0f, 0.0f, 0.f);
	glutSolidCube(10);
	glTranslatef(0.0f, 0.0f, 2.5f + 5.0f);
	glColor3f(1.0f, 1.0f, 0.f);
	glutSolidCube(8);


	glPopMatrix();

	glDisable(GL_FOG);
	
}

