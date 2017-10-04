#include "CCircle.h"

void CCircle::Init(OBJTYPE objType, MOVETYPE moveType, Pos pos) {}

void CCircle::Move()
{
}

void CCircle::Update()
{

}

void CCircle::Render()
{

	glColor3f(1.0, 0.0, 0.0);
	glBegin(GL_LINE_STRIP);
	for (int i = -10; i < 360; i += 10) {
		m_angle = (i * PIE / 180);
		m_x = m_size * cos(m_angle);
		m_y = m_size * sin(m_angle);
		glVertex2f((m_x + m_pos.x) / 5, (m_y + m_pos.y) / 5);
	}

	glEnd();
}

