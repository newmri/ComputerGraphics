#include "Define.h"
#include "Objects.h"


void CGun::Init()
{

}

void CGun::Update()
{

}

void CGun::Render()
{

	glPushMatrix();
	glColor3f(m_objInfo.color.r, m_objInfo.color.g, m_objInfo.color.b);
	glTranslatef(m_objInfo.pos.x, m_objInfo.pos.y, m_objInfo.pos.z);
	glutSolidCube(m_objInfo.size);
	glPopMatrix();

}