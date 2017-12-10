#include "Define.h"
#include "Objects.h"


void CCube::Init()
{
	m_time = GetTickCount();
}



void CCube::Update()
{
	if (m_time + 1000 / 60 < GetTickCount()) {
		if (m_objInfo.rotation.w < 360) m_objInfo.rotation.w++;
		else m_objInfo.rotation.w = 0.0f;
		m_time = GetTickCount();
	}
	
}



void CCube::Render()
{
	glEnable(GL_BLEND);
	glPushMatrix();
	glTranslatef(m_objInfo.pos.x, m_objInfo.pos.y, m_objInfo.pos.z);
	glRotatef(m_objInfo.rotation.w, 0.0f, 1.0f, 0.0f);
	glPushMatrix();
	glRotatef(90.0f, 1.0f, 1.0f, 0.0f);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glColor4f(m_objInfo.color.r, m_objInfo.color.r, m_objInfo.color.b, 0.5f);
	glutSolidCube(m_objInfo.size);
	glPopMatrix();
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	glutSolidCube(m_objInfo.size / 2.0f);
	glPopMatrix();
	glDisable(GL_BLEND);
}