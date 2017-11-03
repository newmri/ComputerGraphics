#include "Define.h"
#include "Objects.h"

void CAirplain::Init()
{
	m_angle = 0.0f;
	m_propelerRotation.x = 1.0f;
	m_propelerRotation.y = 0.0f;
	m_propelerRotation.z = 0.0f;
	m_proplerAngle = 0.0f;
	this->SetRotation(Vector3(0.0f, 0.0f, 1.0f));
}

void CAirplain::Move()
{

}

void CAirplain::Update()
{
	if (m_proplerAngle < 360.0f) m_proplerAngle += 10.0f;
	else m_proplerAngle = 0.0f;

	//this->Move();
}


void CAirplain::Render()
{
	glPushMatrix();
	glTranslatef(m_pos.x, m_pos.y, m_pos.z);
	// Render Body
	glPushMatrix();
	glScalef(m_scale.x, m_scale.y, m_scale.z);
	glColor3f(m_bodyColor.R, m_bodyColor.G, m_bodyColor.B);
	glutSolidCube(m_size);
	glPopMatrix();

	// Render Propeler
	glPushMatrix();
	glColor3f(1.0f, 1.0f, 1.0f);
	glScalef(0.5f, 0.5f, 3.0f);
	glTranslatef(-m_size * 2.0f, 0.0f, 0.0f);
	glRotatef(m_proplerAngle, m_propelerRotation.x, m_propelerRotation.y, m_propelerRotation.z);
	glutSolidCube(m_size);
	glPopMatrix();

	// Render Right Wing
	glPushMatrix();
	glTranslatef(0.0f, 0.0f, -m_size * m_scale.x);
	glColor3f(1.0f, 1.0f, 1.0f);
	glBegin(GL_TRIANGLES);
	glVertex3f(0.0f, 0.0f, 0.0f);
	glVertex3f(0.0f, 0.0f, 5.0f);
	glVertex3f(-m_size, 0.0f, 5.0f);
	glEnd();
	glPopMatrix();

	// Render Left Wing
	glPushMatrix();
	glTranslatef(0.0f, 0.0f, m_size / 2.0f);
	glColor3f(1.0f, 1.0f, 1.0f);
	glBegin(GL_TRIANGLES);
	glVertex3f(0.0f, 0.0f, 0.0f);
	glVertex3f(0.0f, 0.0f, 5.0f);
	glVertex3f(-m_size, 0.0f, 0.0f);
	glEnd();
	glPopMatrix();

	glPopMatrix();
}