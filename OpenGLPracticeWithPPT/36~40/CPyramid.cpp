#include "Define.h"
#include "Objects.h"


void CPyramid::Init()
{
	m_iterations = 0;
	float temp[4][3] = 
	{{ -m_objInfo.size, -m_objInfo.size, -m_objInfo.size },
	{ m_objInfo.size, -m_objInfo.size, -m_objInfo.size },
	{ 0.0, -m_objInfo.size,  m_objInfo.size / 2.0f },
	{ 0.0,  m_objInfo.size, -m_objInfo.size / 2.0f }};

	memcpy(m_pyramid, temp, sizeof(temp));
	this->GenerateColors();

	m_time = GetTickCount();
}

void CPyramid::GenerateColors()
{
	for (int i = 0; i < 1000; i++) m_colors[i] = rand() / (double)RAND_MAX;
	
}

double CPyramid::GetRandomColor(bool reset)
{
	static int curr = 0;
	if (reset) {
		curr = 0;
		return 0.0;
	}
	else {
		if (curr >= 1000) curr = 0;
		return m_colors[curr++];
	}
}

void CPyramid::Divide(float* a, float* b, float* c, float* d, int iterations)
{
	GLfloat v[6][3];
	int j;
	if (iterations> 0) {
		//encontrar los puntos medios de cada arista del triángulo
		for (j = 0; j < 3; j++) v[0][j] = (a[j] + b[j]) / 2;
		for (j = 0; j < 3; j++) v[1][j] = (a[j] + c[j]) / 2;
		for (j = 0; j < 3; j++) v[2][j] = (b[j] + c[j]) / 2;
		for (j = 0; j < 3; j++) v[3][j] = (a[j] + d[j]) / 2;
		for (j = 0; j < 3; j++) v[4][j] = (b[j] + d[j]) / 2;
		for (j = 0; j < 3; j++) v[5][j] = (c[j] + d[j]) / 2;
	
		Divide(a, v[0], v[1], v[3], iterations - 1);
		Divide(v[0], b, v[2], v[4], iterations - 1);
		Divide(v[1], v[2], c, v[5], iterations - 1);
		Divide(v[3], v[4], v[5], d, iterations - 1);

	}
	else Draw(a, b, c, d);
}

void CPyramid::Update()
{
	if (m_time + 1000 < GetTickCount()) {
		m_iterations = (m_iterations + 1) % 5;
		m_time = GetTickCount();
	}
}

void CPyramid::Draw(float* a, float* b, float* c, float* d)
{
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glShadeModel(GL_SMOOTH);

	glBegin(GL_TRIANGLES);
	// Bottom
	
	glColor3f(GetRandomColor(), GetRandomColor(), GetRandomColor());
	glVertex3fv(a);
	glColor3f(GetRandomColor(), GetRandomColor(), GetRandomColor());
	glVertex3fv(b);
	glColor3f(GetRandomColor(), GetRandomColor(), GetRandomColor());
	glVertex3fv(c);
	glEnd();

	// Back
	glBegin(GL_TRIANGLES);
	glColor3f(GetRandomColor(), GetRandomColor(), GetRandomColor());
	glVertex3fv(a);
	glColor3f(GetRandomColor(), GetRandomColor(), GetRandomColor());
	glVertex3fv(b);
	glColor3f(GetRandomColor(), GetRandomColor(), GetRandomColor());
	glVertex3fv(d);
	glEnd();
	
	// Left
	glBegin(GL_TRIANGLES);
	glColor3f(GetRandomColor(), GetRandomColor(), GetRandomColor());
	glVertex3fv(a);
	glColor3f(GetRandomColor(), GetRandomColor(), GetRandomColor());
	glVertex3fv(c);
	glColor3f(GetRandomColor(), GetRandomColor(), GetRandomColor());
	glVertex3fv(d);
	glEnd();
	
	// Right
	glBegin(GL_TRIANGLES);
	glColor3f(GetRandomColor(), GetRandomColor(), GetRandomColor());
	glVertex3fv(b);
	glColor3f(GetRandomColor(), GetRandomColor(), GetRandomColor());
	glVertex3fv(c);
	glColor3f(GetRandomColor(), GetRandomColor(), GetRandomColor());
	glVertex3fv(d);
	glEnd();
	
}

void CPyramid::Render()
{
	glPushMatrix();
	glTranslatef(m_objInfo.pos.x, m_objInfo.pos.y, m_objInfo.pos.z);
	GetRandomColor(true);
	Divide(m_pyramid[0], m_pyramid[1], m_pyramid[2], m_pyramid[3], m_iterations);
	glPopMatrix();
	
}