#include "Define.h"
#include "Objects.h"

void CHexahedronSphereTree::Init()
{
	m_leafSize = m_size;
	m_incre = 0.1f;
}

void CHexahedronSphereTree::ExpandAndReduct()
{
	if (m_leafSize > m_size * 2.0f || m_leafSize < m_size * 0.5f) m_incre = -m_incre;

	m_leafSize += m_incre;
}

void CHexahedronSphereTree::Update()
{
	this->ExpandAndReduct();
}


void CHexahedronSphereTree::Render()
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
	glTranslatef(0.0f, m_scale.y * 3.5f, 0.0f);
	glRotatef(m_angle, m_rotation.x, m_rotation.y, m_rotation.z);
	glColor3f(m_leafColor.R, m_leafColor.G, m_leafColor.B);
	glutWireSphere(m_leafSize, 25, 25);
	glPopMatrix();
}