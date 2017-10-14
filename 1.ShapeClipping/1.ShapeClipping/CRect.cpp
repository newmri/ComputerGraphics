#include "Define.h"

void CRect::Init()
{
	m_size = RECT_SIZE;
	m_pos.y = 0.5f;
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