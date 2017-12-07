#include "Objects.h"

void CSphere::Update()
{

}

void CSphere::Render()
{
	glPushMatrix();
	glTranslatef(m_pos.x, m_pos.y, m_pos.z);
	//glClearColor(1.0, 1.0, 1.0, 1.0);
	glColor4f(0.0f, 0.0f, 1.0f, 1.0f);
	glutSolidSphere(m_size, 25, 25);
	this->RenderText();
	glPopMatrix();
}