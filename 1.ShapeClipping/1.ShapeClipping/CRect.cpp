#include "Define.h"

void CRect::Init()
{
	m_size = RECT_SIZE;
	m_pos.y = 0.5f;

	switch (m_position) {
	case LT:
		m_pos.x = -m_size;
		m_pos.y += m_size;
		break;
	case T:
		m_pos.y += m_size;
		break;
	case RT:
		m_pos.x = m_size;
		m_pos.y += m_size;
		break;
	case L:
		m_pos.x = -m_size;
		break;
	case M:
		m_color.g = 1.0f;
		break;
	case R:
		m_pos.x = m_size;
		break;
	case LB:
		m_pos.x = -m_size;
		m_pos.y -= m_size;
		break;
	case B:
		m_pos.y -= m_size;
		break;
	case RB:
		m_pos.x = m_size;
		m_pos.y -= m_size;
		break;
	}
}

void CRect::Update()
{

}

void CRect::Render()
{
	glPushMatrix();
		glColor4f(m_color.r, m_color.g, m_color.b, m_color.a);
		glTranslatef(m_pos.x, m_pos.y, m_pos.z);
		glutSolidCube(m_size);
	glPopMatrix();
}