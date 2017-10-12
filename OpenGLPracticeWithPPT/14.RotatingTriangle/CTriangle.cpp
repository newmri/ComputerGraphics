#include "CTriangle.h"

void CTriangle::Init(OBJTYPE objType, MOVETYPE moveType, Pos pos, DATA_TYPE size)
{
	m_objType = objType;
	m_moveType = moveType;
	m_pos = pos;
	m_size = size;
	m_angle = 0.0f;
	m_i = 0;
	m_idx = 0;
	m_trianglePos[0] = { 0.0f, BIG_TRIANGLE_SIZE / 2};
	m_trianglePos[1] = { -BIG_TRIANGLE_SIZE / 2, -BIG_TRIANGLE_SIZE /2 };
	m_trianglePos[2] = { BIG_TRIANGLE_SIZE / 2, -BIG_TRIANGLE_SIZE / 2};
	m_trianglePos[3] = { 0.0f, BIG_TRIANGLE_SIZE / 2 };
}

void CTriangle::Move()
{
	float a{}, b{}, step{};
	if (m_i < 20) ++m_i;
	else {
		m_i = 0;
		if (m_idx < 2) m_idx++;
		else m_idx = 0;
	}
	a = (m_trianglePos[m_idx + 1].y - m_trianglePos[m_idx].y)
		/ (m_trianglePos[m_idx + 1].x - m_trianglePos[m_idx].x);
	b = m_trianglePos[m_idx].y - a * m_trianglePos[m_idx].x;

	step = (m_trianglePos[m_idx + 1].x - m_trianglePos[m_idx].x) / 20;
	m_pos.x = m_trianglePos[m_idx].x + step * m_i;
	m_pos.y = (a * (m_trianglePos[m_idx].x + step * m_i)) + b;
}

void CTriangle::Update()
{
	if (m_objType == SMALL_TRIANGLE) this->Rotate();

	this->Move();
}

void CTriangle::Render()

{
	glPushMatrix();
	glColor3f(1.0, 0.0, 0.0);
	glTranslatef(m_pos.x, m_pos.y, 0.0f);
	glBegin(GL_LINE_LOOP);
	glVertex2f(m_pos.x, m_pos.y + m_size);
	glVertex2f(m_pos.x + m_size, m_pos.y - m_size);
	glVertex2f(m_pos.x - m_size, m_pos.y - m_size);
	glEnd();
	glPopMatrix();
}

