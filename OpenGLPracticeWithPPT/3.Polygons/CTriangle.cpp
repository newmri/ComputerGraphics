#include "CTriangle.h"

void CTriangle::Init(SHAPE shape, int x, int y)
{
	// Top
	m_p1[0] = x + (m_width / 2);
	m_p1[1] = y - (m_height / 2);

	// Left
	m_p2[0] = x;
	m_p2[1] = y + (m_height / 2);

	// Right
	m_p3[0] = x + m_width;
	m_p3[1] = y + (m_height / 2);

	m_shape = shape;
}

void CTriangle::Render()
{
	glBegin(GL_TRIANGLES);
		glVertex2iv(m_p1);
		glVertex2iv(m_p2);
		glVertex2iv(m_p3);
	glEnd();
}