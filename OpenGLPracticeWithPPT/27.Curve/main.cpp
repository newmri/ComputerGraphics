#include "Define.h"
#include "CObject.h"

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
int g_row = 0;

int winId;

vector<shared_ptr<CObject>> g_v;
GLfloat g_ctrlpoints[4][3]{};

void main(int argc, char* argv[])
{

	Init();

	winId = glutCreateWindow("27.Curve");
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
	glOrtho(-(WINDOW_WIDTH / 2.0f), WINDOW_WIDTH / 2.0f, -(WINDOW_HEIGHT / 2.0f), (WINDOW_HEIGHT / 2.0f), -1.0, 200.0);

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

	case 'r':
	case 'R':
		g_row = 0;
		g_v.clear();
		ZeroMemory(&g_ctrlpoints, sizeof(g_ctrlpoints)); break;
	default: break;
	}
	RenderScene();
}


GLvoid Mouse(int button, int state, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
		g_ctrlpoints[g_row][0] = static_cast<GLfloat>(x - (WINDOW_WIDTH / 2.0f));
		g_ctrlpoints[g_row][1] = static_cast<GLfloat>((WINDOW_HEIGHT / 2.0f) - y);
		g_row++;
		if (g_row == 4) {
			g_v.emplace_back(FACTORYMANAGER->CreateObj(g_ctrlpoints));
			g_row = 1;
			for (int i = 0; i < 3; ++i) g_ctrlpoints[0][i] = g_ctrlpoints[3][i];
		}
	}
	RenderScene();
}


GLvoid Update()
{
	int ret{};
	CAMERAMANAGER->Update();
	
}

GLvoid Render()
{
	glPushMatrix();
	if (g_v.size() != 0) {
		for (auto d : g_v) {
			// 곡선 제어점 설정: 매개변수 u의 최소값은 0, 최대값은 1,
			// 제어점간의 데이터 개수는 3, 제어점은 4개를 사용
			glMap1f(GL_MAP1_VERTEX_3, 0.0, 1.0, 3, 4, &d->GetPoints()[0][0]);
			glEnable(GL_MAP1_VERTEX_3);
			// 제어점 사이의 곡선위의 점들을 계산한다. 제어점 사이를 10개로 나누어 그 점들을 연결한다.  곡선위의 점 계산
			glMapGrid1f(10.0, 0.0, 1.0); // 매개변수 0~1 사이를 10개로 나눔
			glEvalMesh1(GL_LINE, 0, 10); // 선분으로 나눈 부분 0~10까지 선으로 그림
			glDisable(GL_MAP1_VERTEX_3);
			// 제어점에 점을 그린다.
			glPointSize(5.0);
			glColor3f(0.0, 0.0, 1.0);
			glBegin(GL_POINTS);
			for (int i = 0; i < 4; i++) glVertex3fv(&d->GetPoints()[i][0]);
			glEnd();
		}
		// 제어점에 점을 그린다.
		glPointSize(5.0);
		glColor3f(0.0, 0.0, 1.0);
		glBegin(GL_POINTS);
		for (int i = 0; i < g_row; i++) glVertex3fv(&g_ctrlpoints[i][0]);
		glEnd();
	}
	else {
		// 제어점에 점을 그린다.
		glPointSize(5.0);
		glColor3f(0.0, 0.0, 1.0);
		glBegin(GL_POINTS);
		for (int i = 0; i < g_row; i++) glVertex3fv(&g_ctrlpoints[i][0]);
		glEnd();
	}
	glPopMatrix();
}

