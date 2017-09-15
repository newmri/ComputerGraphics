#include "CPentagon.h"

void CPentagon::Init(SHAPE shape, int x, int y)
{
	// Top
	m_p1[0] = x + (m_width / 2);
	m_p1[1] = y - (m_height / 2);

	// Left
	m_p2[0] = x;
	m_p2[1] = y - 10;

	// Left Bottom
	m_p3[0] = m_p2[0] + 30;
	m_p3[1] = y + (m_height / 2);

	// Right Bottom
	m_p4[0] = x + m_width - 30;
	m_p4[1] = m_p3[1];

	// Right
	m_p5[0] = x + m_width;
	m_p5[1] = m_p2[1];


	m_shape = shape;
}

void CPentagon::Render()
{
	glBegin(GL_POLYGON);
	glVertex2iv(m_p1);
	glVertex2iv(m_p2);
	glVertex2iv(m_p3);
	glVertex2iv(m_p4);
	glVertex2iv(m_p5);
	glEnd();
}