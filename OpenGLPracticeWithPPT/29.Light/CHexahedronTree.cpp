#include "Define.h"
#include "Objects.h"

void CHexahedronTree::Init()
{
	this->SetRotation(Vector3(0.0f, 1.0f, 0.0f));
}

void CHexahedronTree::Update()
{
	this->Rotate();
}


void CHexahedronTree::Render()
{
	
	glPushMatrix();
		glTranslatef(m_pos.x, m_pos.y, m_pos.z);
		// Render Body
		glPushMatrix();
			glScalef(m_scale.x, m_scale.y, m_scale.z);
			glColor3f(m_bodyColor.R, m_bodyColor.G, m_bodyColor.B);
			glutSolidCube(m_size);
		glPopMatrix();

		// Render Leaf
		glTranslatef(0.0f, m_scale.y * 2.0f, 0.0f);
		glScalef(m_scale.y, m_scale.x, m_scale.z);
		glRotatef(m_angle, m_rotation.x, m_rotation.y, m_rotation.z);
		glColor3f(m_leafColor.R, m_leafColor.G, m_leafColor.B);
		glutSolidCube(m_size);
	glPopMatrix();
}