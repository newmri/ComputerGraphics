#include "Define.h"
#include "Objects.h"


void CGun::Init()
{
	m_bulletIdx = 0;
}

void CGun::Update()
{
	for (int i = 0; i < m_bulletIdx; ++i) m_bullet[i].pos.z -= m_bullet[i].speed;
	
}

void CGun::Render()
{

	glPushMatrix();
	glTranslatef(m_objInfo.pos.x, m_objInfo.pos.y, m_objInfo.pos.z);
	glColor3f(m_objInfo.color.r, m_objInfo.color.g, m_objInfo.color.b);
	glutSolidCube(m_objInfo.size);
	glPopMatrix();

	for (int i = 0; i < m_bulletIdx; ++i) {
		glPushMatrix();
		glTranslatef(m_bullet[i].pos.x, m_bullet[i].pos.y, m_bullet[i].pos.z);
		glColor4f(0.0, 1.0, 0.0, 1.0);
		glutSolidSphere(m_bullet[i].size, 10, 10);
		glPopMatrix();
	}

}