#include "Define.h"
#include "Objects.h"


void CCube::Init()
{

}

void CCube::Update(float frameTime)
{
	
}

void CCube::Render()
{
	glPushMatrix();

	glColor3f(m_objInfo.color.r, m_objInfo.color.g, m_objInfo.color.b);
	glTranslatef(m_objInfo.pos.x, m_objInfo.pos.y, m_objInfo.pos.z);
	glRotatef(m_objInfo.rotation.w, m_objInfo.rotation.x, m_objInfo.rotation.y, m_objInfo.rotation.z);
	glTranslatef(-m_objInfo.pos.x, -m_objInfo.pos.y, -m_objInfo.pos.z);
	glTranslatef(m_objInfo.pos.x, m_objInfo.pos.y, m_objInfo.pos.z);
	glScalef(m_objInfo.scale.x, m_objInfo.scale.y, m_objInfo.scale.z);
	glutSolidCube(m_objInfo.size);
	glPopMatrix();
	
}