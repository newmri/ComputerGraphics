#include "Define.h"
#include "Objects.h"

void CRect::Init()
{
	

}

void CRect::Move()
{
	

}

void CRect::Update()
{
	//this->Move();
}

void CRect::Render()
{
	glPushMatrix();
	glTranslatef(0.0f, 0.0f, CUBE_RAD / -2.0f);
	glTranslatef(m_pos.x, m_pos.y, m_pos.z); // Let's move!
	glColor3f(0.0f, 0.0f, 0.0f);
	glutSolidSphere(m_size, 25, 25);
	glPopMatrix();

}