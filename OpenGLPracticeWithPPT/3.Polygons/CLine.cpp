#include "CLine.h"

void CLine::Init(SHAPE shape, int x, int y)
{
	m_p1[0] = x;
	m_p1[1] = y;

	m_p2[0] = x + m_width;
	m_p2[1] = y;

	m_shape = shape;
}

void CLine::Render()
{
	glBegin(GL_LINES);
		glVertex2iv(m_p1);
		glVertex2iv(m_p2);
	glEnd();
}