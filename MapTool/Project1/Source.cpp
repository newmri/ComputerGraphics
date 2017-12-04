#include <Windows.h>
#include <gl\GL.h>
#include <gl\GLU.h>

#include <gl\glut.h>
#include <cmath>
using namespace std;

struct Point
{
	float p[3];
};
struct Vector
{
	float p[3];
};
struct Matrix
{
	float m[9];
};
struct Object
{
	float colors[3];
	Point position;
	float radius;
};
Object obj1, obj2, obj3, obj4;
bool isLeftMouseDown;
float fovy;
int win_width;
int win_height;
float zNear;
float zFar;
void SetPoint(Point* p, float a, float b, float c)
{
	p->p[0] = a;
	p->p[1] = b;
	p->p[2] = c;
}
void SetVector(Vector *v, float a, float b, float c)
{
	v->p[0] = a;
	v->p[1] = b;
	v->p[2] = c;
}
void SetMatrix(Matrix *m, float _00, float _01, float _02, float _10, float _11, float _12, float _20, float _21, float _22)
{
	m->m[0] = _00; m->m[1] = _01; m->m[2] = _02;
	m->m[3] = _10; m->m[4] = _11; m->m[5] = _12;
	m->m[6] = _20; m->m[7] = _21; m->m[8] = _22;
}
float DotProduct(Vector * v1, Vector *v2)
{
	float s = 0.0f;
	for (int i = 0; i < 3; i++)
		s += v1->p[i] * v2->p[i];
	return s;
}
Vector CrossProduct(Vector *v1, Vector * v2)
{
	Vector v3;
	v3.p[0] = (v1->p[1] * v2->p[2]) - (v1->p[2] * v2->p[1]);
	v3.p[1] = (v1->p[2] * v2->p[0]) - (v1->p[0] * v2->p[2]);
	v3.p[2] = (v1->p[0] * v2->p[1]) - (v1->p[1] * v2->p[0]);
	return v3;
}
float VecLength(Vector *v)
{
	return sqrt((v->p[0] * v->p[0]) + (v->p[1] * v->p[1]) + (v->p[2] * v->p[2]));
}
Vector Normalize(Vector *v)
{
	Vector v1;
	float length = VecLength(v);
	v1.p[0] = v->p[0] / length;
	v1.p[1] = v->p[1] / length;
	v1.p[2] = v->p[2] / length;
	return v1;
}
Vector InverseVector(Vector *v)
{
	Vector v1;
	for (int i = 0; i < 3; i++)
		v1.p[i] = -(v->p[i]);
	return v1;
}
Matrix MatrixTranspose(Matrix *m)
{
	Matrix c;
	c.m[0] = m->m[0];
	c.m[1] = m->m[3];
	c.m[2] = m->m[6];
	c.m[3] = m->m[1];
	c.m[4] = m->m[4];
	c.m[5] = m->m[7];
	c.m[6] = m->m[2];
	c.m[7] = m->m[5];
	c.m[8] = m->m[8];
	return c;
}
Point AddPointVec(Point *p, Vector * v)
{
	Point p1;
	for (int i = 0; i < 3; i++)
		p1.p[i] = p->p[i] + v->p[i];
	return p1;
}
Vector SubPoint(Point *p1, Point *p2)
{
	Vector v;
	v.p[0] = p1->p[0] - p2->p[0];
	v.p[1] = p1->p[1] - p2->p[1];
	v.p[2] = p1->p[2] - p2->p[2];
	return v;
}
Vector MultMatVec(Matrix *m, Vector * v)
{
	Vector v1;
	v1.p[0] = m->m[0] * v->p[0] + m->m[3] * v->p[1] + m->m[6] * v->p[2];
	v1.p[1] = m->m[1] * v->p[0] + m->m[4] * v->p[1] + m->m[7] * v->p[2];
	v1.p[2] = m->m[2] * v->p[0] + m->m[5] * v->p[1] + m->m[8] * v->p[2];
	return v1;
}
Point MultMatPoint(Matrix *m, Point *p)
{
	Point p1;
	p1.p[0] = m->m[0] * p->p[0] + m->m[3] * p->p[1] + m->m[6] * p->p[2];
	p1.p[1] = m->m[1] * p->p[0] + m->m[4] * p->p[1] + m->m[7] * p->p[2];
	p1.p[2] = m->m[2] * p->p[0] + m->m[5] * p->p[1] + m->m[8] * p->p[2];
	return p1;
}
void init(void)
{
	obj1.colors[0] = 1.0f;  obj1.colors[1] = 0.0f; obj1.colors[2] = 0.0f;
	obj2.colors[0] = 0.0f;  obj2.colors[1] = 1.0f; obj2.colors[2] = 0.5f;
	obj3.colors[0] = 1.0f;  obj3.colors[1] = 0.0f; obj3.colors[2] = 0.7f;
	obj4.colors[0] = 1.0f;  obj4.colors[1] = 1.0f; obj4.colors[2] = 0.0f;
	SetPoint(&obj1.position, 2.0f, 2.0f, 0.0f);
	SetPoint(&obj2.position, -2.0f, 2.0f, 0.0f);
	SetPoint(&obj3.position, -2.0f, -2.0f, 0.0f);
	SetPoint(&obj4.position, 2.0f, -2.0f, 0.0f);
	obj1.radius = 1.0;
	obj2.radius = 1.0;
	obj3.radius = 1.0;
	obj4.radius = 1.0;
	isLeftMouseDown = false;
	fovy = 45;
	zNear = 1.0f;
	zFar = 1000.0;
}
void setupRC(void)
{
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
}
void changeSize(int w, int h)
{
	if (h == 0)
		h = 1;
	float aspectRatio = w / h;
	win_width = w;
	win_height = h;
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(fovy, aspectRatio, zNear, zFar);
}
void setupLight0()
{
	GLfloat position[4] = { -1.0, 1.0, 1.0, 0.0 };
	GLfloat ambient[4] = { 0.3, 0.3, 0.3, 1.0 };
	GLfloat diffuse[4] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat specular[4] = { 1.0, 1.0, 1.0, 1.0 };
	glLightfv(GL_LIGHT0, GL_POSITION, position);
	glLightfv(GL_LIGHT0, GL_AMBIENT, ambient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, specular);
}
void setMaterial(float r, float g, float b)
{
	float ambient_m[4] = { 0.3, 0.3, 0.3, 1.0 };
	float diffuse_m[4] = { r, g, b, 1.0 };
	float specular_m[4] = { 1.0, 1.0, 1.0, 1.0 };
	float shininess_m = 100.0;
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ambient_m);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, diffuse_m);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specular_m);
	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, shininess_m);
}
void drawObject(Object obj)
{
	setMaterial(obj.colors[0], obj.colors[1], obj.colors[2]);
	glPushMatrix();
	{
		glTranslatef(obj.position.p[0], obj.position.p[1], obj.position.p[2]);
		glutSolidTeapot(obj.radius);
	}
	glPopMatrix();
}
void calcRay(int  _x, int _y, Point * _rayOri, Vector * _rayDir)
{
	float aspectRatio = win_width / win_height;
	float fovyRadius = fovy * 3.14159f / 180.f;
	float rayDx = tanf(fovyRadius*0.5f)*aspectRatio;
	float rayDy = tanf(fovyRadius*0.5f);
	float windowHalfWidth = (float)win_width *0.5f;
	float windowHalfHeight = (float)win_height * 0.5f;
	float dx = rayDx * ((float)_x / windowHalfWidth - 1.0f);
	float dy = rayDy * (1.0f - (float)_y / windowHalfHeight);

	Point ori;
	SetPoint(&ori, dx * zNear, dy *zNear, -zNear);
	Point end;
	SetPoint(&end, dx*zFar, dy * zFar, -zFar);
	Vector dir = SubPoint(&end, &ori);
	dir = Normalize(&dir);
	double mv[16];
	glGetDoublev(GL_MODELVIEW_MATRIX, mv);
	Matrix mat;
	SetMatrix(&mat, mv[0], mv[4], mv[8], mv[1], mv[5], mv[9], mv[2], mv[6], mv[10]);
	Vector translVec;
	SetVector(&translVec, mv[12], mv[13], mv[14]);
	Matrix invMat = MatrixTranspose(&mat);
	Vector invTranslVec = InverseVector(&translVec);

	ori = AddPointVec(&ori, &invTranslVec);
	ori = MultMatPoint(&invMat, &ori);
	end = AddPointVec(&end, &invTranslVec);
	end = MultMatPoint(&invMat, &end);
	dir = MultMatVec(&invMat, &dir);
	*(_rayOri) = ori;
	*(_rayDir) = dir;
}
bool interSection(Point & _ryaOri, Vector & _rayDir, Point & _objPos, float _radius, float *t)
{
	Vector vo = SubPoint(&_ryaOri, &_objPos);
	float a = (float)DotProduct(&_rayDir, &_rayDir);
	float b = (float)(2.0f * DotProduct(&_rayDir, &vo));
	float c = (float)DotProduct(&vo, &vo) - (float)(_radius * _radius);
	float disc = b*b - 4.0f * a * a * c;
	if (disc < 0)
		return false;
	float distSqrt = sqrtf(disc);
	float q;
	if (b < 0)
		q = (-b - distSqrt) / 2.0f;
	else
		q = (-b + distSqrt) / 2.0f;
	float t0 = q / a;
	float t1 = c / q;
	if (t0 > t1)
	{
		float temp = t0;
		t0 = t1;
		t1 = temp;
	}
	if (t1 < 0)
		return false;
	if (t0 < 0)
	{
		*t = (float)t1;
		return true;
	}
	else
	{
		*t = (float)t0;
		return true;
	}
}
void pickingObject(int _x, int _y)
{
	Point rayOri;
	Vector rayDir;
	calcRay(_x, _y, &rayOri, &rayDir);
	float t;
	bool isCollison1 = interSection(rayOri, rayDir, obj1.position, obj1.radius, &t);
	bool isCollison2 = interSection(rayOri, rayDir, obj2.position, obj2.radius, &t);
	bool isCollison3 = interSection(rayOri, rayDir, obj3.position, obj3.radius, &t);
	bool isCollison4 = interSection(rayOri, rayDir, obj4.position, obj4.radius, &t);
	if (isCollison1)
	{
		obj1.colors[0] = 0.5f;
		obj1.colors[1] = 0.5f;
		obj1.colors[2] = 0.5f;
	}
	if (isCollison2)
	{
		obj2.colors[0] = 0.5f;
		obj2.colors[1] = 0.5f;
		obj2.colors[2] = 0.5f;
	}
	if (isCollison3)
	{
		obj3.colors[0] = 0.5f;
		obj3.colors[1] = 0.5f;
		obj3.colors[2] = 0.5f;
	}
	if (isCollison4)
	{
		obj4.colors[0] = 0.5f;
		obj4.colors[1] = 0.5f;
		obj4.colors[2] = 0.5f;
	}
}
void mouse(int button, int state, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON  && state == GLUT_DOWN)
	{
		pickingObject(x, y);
	}
	if (button == GLUT_LEFT_BUTTON  && state == GLUT_UP)
	{
		//obj1.colors[0] = 0.0f; obj1.colors[1] = 0.0f; obj1.colors[2] = 0.0f;
	}
	glutPostRedisplay();
}
void renderScene(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	setupLight0();
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslatef(0, 0, -10.0f);
	drawObject(obj1);
	drawObject(obj2);
	drawObject(obj3);
	drawObject(obj4);
	glutSwapBuffers();
}
void main(int argc, char* argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(600, 600);
	glutCreateWindow("Simple");
	glutDisplayFunc(renderScene);
	glutReshapeFunc(changeSize);
	glutMouseFunc(mouse);
	init();
	setupRC();
	glutMainLoop();

}