#include "CObject.h"

void CObject::Init(int idx)
{
	m_idx = idx;
	m_angle = 0.0f;

	this->SetRotation(Vector3{ 0.0f, 0.0f, 1.0f });
	m_haveToRotate = true;
	m_createNew = false;
	m_pos.y = 8.0f;
}

void CObject::Update()
{
	if(m_haveToRotate) this->Rotate();
	this->Move();
}

void CObject::Render()
{
	glPushMatrix();
	glTranslatef(m_pos.x + m_dPos.x, m_pos.y, m_pos.z + m_dPos.z);
	glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
	glRotatef(m_angle, m_rotation.x, m_rotation.y, m_rotation.z);
	glutWireTorus(2.0, 10.0, 25, 25);
	glPopMatrix();

	
	
}