#include "Define.h"

void CRect::Init()
{
	m_size = RECT_SIZE;
	m_pos.y = 0.5f;

	switch (m_position) {
	case LT:
		m_flag.left = true;
		m_flag.right = false;
		m_flag.top = true;
		m_flag.bottom = false;
		break;
	case T:
		m_flag.left = false;
		m_flag.right = false;
		m_flag.top = true;
		m_flag.bottom = false;
		break;
	case RT:
		m_flag.left = false;
		m_flag.right = true;
		m_flag.top = true;
		m_flag.bottom = false;
		break;
	case L:
		m_flag.left = true;
		m_flag.right = false;
		m_flag.top = false;
		m_flag.bottom = false;
		break;
	case M:
		m_flag.left = false;
		m_flag.right = false;
		m_flag.top = false;
		m_flag.bottom = false;
		break;
	case R:
		m_flag.left = false;
		m_flag.right = true;
		m_flag.top = false;
		m_flag.bottom = false;
		break;
	case LB:
		m_flag.left = true;
		m_flag.right = false;
		m_flag.top = false;
		m_flag.bottom = true;
		break;
	case B:
		m_flag.left = false;
		m_flag.right = false;
		m_flag.top = false;
		m_flag.bottom = true;
		break;
	case RB:
		m_flag.left = false;
		m_flag.right = true;
		m_flag.top = false;
		m_flag.bottom = true;
		break;
	}
}

void CRect::Update()
{

}

void CRect::Render()
{
	glPushMatrix();
		glColor3f(1.0f, 0.0f, 0.0f);
		glTranslatef(m_pos.x, m_pos.y, m_pos.z);
		glutSolidCube(m_size);
	glPopMatrix();
}