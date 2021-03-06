
#include <iostream>
#include <gl/glut.h>


GLUnurbsObj * m_objNurbs;

GLfloat m_specref[4];
GLfloat m_specLight[4];
GLfloat m_lightPos[4];
GLfloat m_diffuseLight[4];
GLfloat m_ambientLight[4];
GLfloat m_fAngle;

void SetupRC();
void RenderScene();
void ReshapeScene(int width, int height);
void OnTimer(int id);

int main()
{
	// 초기화 함수들
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);	// 디스플레이 모드 설정
	glutInitWindowPosition(100, 100);				// 윈도우의 위치 지정
	glutInitWindowSize(500, 500);					// 윈도우의 크기 지정
	glutCreateWindow("D.13.3");					// 윈도우 생성 (윈도우 이름)
	glutDisplayFunc(RenderScene);					// 출력 함수의 지정
	glutReshapeFunc(ReshapeScene);					// 윈도우크기변경함수의 지정


	m_fAngle = 0.0f;

	m_ambientLight[0] = 0.3f;
	m_ambientLight[1] = 0.3f;
	m_ambientLight[2] = 0.3f;
	m_ambientLight[3] = 1.0f;

	m_diffuseLight[0] = 0.7f;
	m_diffuseLight[1] = 0.7f;
	m_diffuseLight[2] = 0.7f;
	m_diffuseLight[3] = 1.0f;

	m_lightPos[0] = 100.0f;
	m_lightPos[1] = 100.0f;
	m_lightPos[2] = 100.0f;
	m_lightPos[3] = 1.0f;

	m_specLight[0] = 0.7f;
	m_specLight[1] = 0.7f;
	m_specLight[2] = 0.7f;
	m_specLight[3] = 1.0f;

	m_specref[0] = 0.5f;
	m_specref[1] = 0.5f;
	m_specref[2] = 0.5f;
	m_specref[3] = 1.0f;

	m_objNurbs = gluNewNurbsRenderer();

	SetupRC();

	glutMainLoop();

	gluDeleteNurbsRenderer(m_objNurbs);

	return 0;
}

void OnTimer(int id)
{
	glutPostRedisplay();
}

void ReshapeScene(int width, int height)
{
	float fRange = 10.0f;
	if (height == 0) height = 1;

	float fAspect = (float)width / (float)height;

	glViewport(0, 0, width, height);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	if (width <= height)
		glOrtho(-fRange, fRange, -fRange / fAspect, fRange / fAspect, -fRange, fRange);
	else
		glOrtho(-fRange * fAspect, fRange * fAspect, -fRange, fRange, -fRange, fRange);


}

void SetupRC()
{
	glShadeModel(GL_FLAT);
	glFrontFace(GL_CCW);
	glEnable(GL_CULL_FACE);
	glEnable(GL_DEPTH_TEST);

	glEnable(GL_LIGHTING);
	glLightfv(GL_LIGHT0, GL_AMBIENT, m_ambientLight);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, m_diffuseLight);
	glLightfv(GL_LIGHT0, GL_SPECULAR, m_specLight);
	glLightfv(GL_LIGHT0, GL_POSITION, m_lightPos);
	glEnable(GL_LIGHT0);

	glEnable(GL_COLOR_MATERIAL);
	glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);

	glMaterialfv(GL_FRONT, GL_SPECULAR, m_specref);
	glMateriali(GL_FRONT, GL_SHININESS, 128);

	// NURBS propety setting
	gluNurbsProperty(m_objNurbs, GLU_SAMPLING_TOLERANCE, 25.0f);
	gluNurbsProperty(m_objNurbs, GLU_DISPLAY_MODE, (GLfloat)GL_FILL);

	glEnable(GL_AUTO_NORMAL);

	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
}

void RenderScene()
{
	GLfloat ctrlPoints[4][4][3] = {
		{ { -6.0f, -6.0f, 0.0f },{ -6.0f, -2.0f, 0.0f },{ -6.0f,  2.0f, 0.0f },{ -6.0f,  6.0f, 0.0f } },
		{ { -2.0f, -6.0f, 0.0f },{ -2.0f, -2.0f, 8.0f },{ -2.0f,  2.0f, 8.0f },{ -2.0f,  6.0f, 0.0f } },
		{ { 2.0f, -6.0f, 0.0f },{ 2.0f, -2.0f, 8.0f },{ 2.0f,  2.0f, 8.0f },{ 2.0f,  6.0f, 0.0f } },
		{ { 6.0f, -6.0f, 0.0f },{ 6.0f, -2.0f, 0.0f },{ 6.0f,  2.0f, 0.0f },{ 6.0f,  6.0f, 0.0f } } };

	GLfloat Knots[8] = { 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f };

	glColor3ub(0, 0, 220);

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();

	glRotatef(310.0f, 1.0f, 0.0f, 0.0f);

	gluBeginSurface(m_objNurbs);

	gluNurbsSurface(m_objNurbs, 8, Knots, 8, Knots, 4 * 3, 3, &ctrlPoints[0][0][0], 4, 4, GL_MAP2_VERTEX_3);

	gluEndSurface(m_objNurbs);

	glPointSize(5.0f);
	glColor3ub(255, 0, 0);

	glBegin(GL_POINTS);
	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 4; j++)
			glVertex3fv(ctrlPoints[i][j]);
	glEnd();

	glPopMatrix();

	glFlush();								// 화면에 출력하기
}
