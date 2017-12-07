#include "Objects.h"

void CTeapot::Update()
{

}

void CTeapot::Render()
{
	glPushMatrix();
	glTranslatef(m_pos.x, m_pos.y, m_pos.z);
	//glClearColor(1.0, 1.0, 1.0, 1.0);
	//glBlendFunc(GL_ONE, GL_ONE);
	glColor4f(1.0f, 0.0f, 0.0f, 0.5f);
	glutSolidTeapot(m_size);
	glPopMatrix();
}