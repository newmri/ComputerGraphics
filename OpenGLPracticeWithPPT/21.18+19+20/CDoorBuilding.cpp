#include "Define.h"
#include "Objects.h"

void CDoorBuilding::Init()
{

	m_doorScale.x = m_scale.y;
	m_doorScale.y = m_scale.x;
	m_doorScale.z = m_scale.z;
	m_yDist = m_doorScale.x;

	m_doorIncre = 0.1f;
	m_doorPosIncre = -0.25f;

}


void CDoorBuilding::Update()
{
	if (m_yDist < -m_scale.y || m_yDist > m_doorScale.x) {
		m_doorPosIncre = -m_doorPosIncre;
		m_doorIncre = -m_doorIncre;
	}
	m_yDist += m_doorPosIncre;
	m_doorScale.y += m_doorIncre;
}

void CDoorBuilding::Render()
{

	glPushMatrix();
	glTranslatef(m_pos.x, m_pos.y, m_pos.z);

	// Render Left
	glPushMatrix();
	glTranslatef(-GAP_OF_END, 0.0f, 0.0f);
	glColor3f(m_bodyColor.R, m_bodyColor.G, m_bodyColor.B);
	glScalef(m_scale.x, m_scale.y, m_scale.z);
	glutSolidCube(m_size);
	glPopMatrix();
	// Render Door
	glPushMatrix();
	glTranslatef(0.0f, m_yDist + m_size, 0.0f);
	glColor3f(m_bodyColor.R, m_bodyColor.G, m_bodyColor.B);
	glScalef(m_doorScale.x, m_doorScale.y, m_doorScale.z);
	glutSolidCube(m_size);
	glPopMatrix();
	
	// Render Right
	glPushMatrix();
	glTranslatef(GAP_OF_END, 0.0f, 0.0f);
	glColor3f(m_bodyColor.R, m_bodyColor.G, m_bodyColor.B);
	glScalef(m_scale.x, m_scale.y, m_scale.z);
	glutSolidCube(m_size);
	glPopMatrix();
	glPopMatrix();

}