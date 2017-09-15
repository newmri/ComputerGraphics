#include "CRect.h"

void CRect::Init(SHAPE shape, int x, int y)
{
	// Top Left
	m_p1[0] = x;
	m_p1[1] = y - (m_height / 2);

	// Top Right
	m_p2[0] = x + m_width;
	m_p2[1] = m_p1[1];

	// Bottom Left
	m_p3[0] = x;
	m_p3[1] = y + (m_height / 2);

	// Bottom Right
	m_p4[0] = m_p2[0];
	m_p4[1] = m_p3[1];

	m_shape = shape;
}

void CRect::Render()
{
	glBegin(GL_POLYGON);
	glVertex2iv(m_p1);
	glVertex2iv(m_p3);
	glVertex2iv(m_p4);
	glVertex2iv(m_p2);
	glEnd();
}