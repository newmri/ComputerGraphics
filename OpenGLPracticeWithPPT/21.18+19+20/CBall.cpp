#include "Define.h"
#include "Objects.h"

void CBall::Init()
{
	m_angle = 0.0f;
	this->SetRotation(Vector3(0.0f, 0.0f, 1.0f));
	m_incre = -BALL_ROTATION_SPEED;
}

void CBall::Move()
{
	m_pos.x += (m_incre / 360.0f)  * m_size * PIE * 2;
}

void CBall::Update()
{
	//this->Move();
}


void CBall::Render()
{
	glPushMatrix();
	glTranslatef(m_pos.x, m_pos.y, m_pos.z);
	glPushMatrix();
	glRotatef(m_angle, m_rotation.x, m_rotation.y, m_rotation.z);
	glColor3f(m_bodyColor.R, m_bodyColor.G, m_bodyColor.B);
	glutWireSphere(m_size, 25, 25);
	glPopMatrix();
	glPopMatrix();
}