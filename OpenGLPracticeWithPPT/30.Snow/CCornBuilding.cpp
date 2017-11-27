#include "Define.h"
#include "Objects.h"

void CCornBuilding::Init()
{
	m_leafSize = m_size;
	this->SetRotation(Vector3(1.0f, 0.0f, 0.0f));
	m_angle = 90.0f;
	m_incre[0] = -0.1;
	m_incre[1] = 0.2;
	m_maxSize = m_size;
	m_scale2.x = 1.0f;
	m_scale2.y = 1.0f;
	m_scale2.z = 1.0f;

}

void CCornBuilding::ExpandAndReduct()
{
	if (m_size > m_maxSize || m_size < m_maxSize * 0.5f) m_incre[0] = -m_incre[0];
	if (m_leafSize > m_maxSize * m_scale.y || m_leafSize < (m_maxSize * m_scale.y) * 0.5f) m_incre[1] = -m_incre[1];

	m_size += m_incre[0];
	m_leafSize += m_incre[1];
}

void CCornBuilding::Update()
{
	this->ExpandAndReduct();

}


void CCornBuilding::Render()
{

	glPushMatrix();
	glTranslatef(m_pos.x, m_pos.y, m_pos.z);
	// Render Body
	glPushMatrix();
	glRotatef(m_angle * 3.0f, m_rotation.x, m_rotation.y, m_rotation.z);
	glColor3f(m_bodyColor.R, m_bodyColor.G, m_bodyColor.B);
	glScalef(m_scale.x, m_scale.y, m_scale.z);
	glutWireCone(m_size, m_size * m_scale.y, 40, 40);
	glPopMatrix();

	// Render Leaf
	glTranslatef(0.0f, m_size * m_scale.y + m_leafSize, 0.0f);
	glRotatef(m_angle, m_rotation.x, m_rotation.y, m_rotation.z);
	glColor3f(m_leafColor.R, m_leafColor.G, m_leafColor.B);
	glScalef(m_scale2.x, m_scale2.y, m_scale2.z);
	glutWireCone(m_leafSize, m_leafSize * m_scale2.y, 40, 40);
	glPopMatrix();
}