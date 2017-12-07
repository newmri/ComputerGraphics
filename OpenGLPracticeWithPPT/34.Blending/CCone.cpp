#include "Objects.h"

void CCone::Update()
{

}

void CCone::Render()
{
	glPushMatrix();


	glTranslatef(-m_pos.x, -m_pos.y, -m_pos.z);
	glRotatef(300, 1.0f, 0.0f, 0.0f);
	glTranslatef(m_pos.x, m_pos.y, m_pos.z);

	
	glTranslatef(m_pos.x, 0, m_pos.y);

	//glClearColor(1.0, 1.0, 1.0, 1.0);

	glColor4f(0.0f, 1.0f, 0.0f, 0.25f);
	glutSolidCone(m_size / 4, m_size / 2, 40, 40);
	this->RenderText();
	glPopMatrix();
}