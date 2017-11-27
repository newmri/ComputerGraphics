#include "Define.h"
#include "Objects.h"

void CHexahedronTorusTree::Init()
{
	this->SetRotation(Vector3(1.0f, 0.0f, 0.0f));
	m_angle = 90.0f;

	m_leafPos = m_scale;
	m_leafPos.y = m_leafPos.y * 2.5f;
	m_speed = -SPEED;
}


void CHexahedronTorusTree::MoveUpAndDown()
{
	if (m_leafPos.y < m_pos.y || m_leafPos.y > m_scale.y * 2.5f) m_speed = -m_speed;
	m_leafPos.y += m_speed;
}
void CHexahedronTorusTree::Update()
{
	this->MoveUpAndDown();
}


void CHexahedronTorusTree::Render()
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
	glTranslatef(0.0f, m_leafPos.y, 0.0f);
	glRotatef(m_angle, m_rotation.x, m_rotation.y, m_rotation.z);
	glColor3f(m_leafColor.R, m_leafColor.G, m_leafColor.B);
	glutWireTorus(m_size / 2.0f, m_size * 1.5f, 40, 20);
	glPopMatrix();
}