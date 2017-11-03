#include "Define.h"
#include "Objects.h"

void CFloor::Init()
{

}

void CFloor::Update()
{

}


void CFloor::Render()
{
	glTranslatef(m_pos.x, m_pos.y, m_pos.z);

	glPushMatrix();
		glScalef(m_scale.x, m_scale.y, m_scale.z);
		glColor3f(m_bodyColor.R, m_bodyColor.G, m_bodyColor.B);
		glutSolidCube(m_size);
	glPopMatrix();
}