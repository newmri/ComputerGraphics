#include "Define.h"
#include "Objects.h"

void CParticle::Init()
{
	m_time = GetTickCount();
	m_speed = rand() / (float)RAND_MAX * PARTICLE_SPEED;

}

void CParticle::Update(float frameTime)
{
	float dist = frameTime * m_speed;
	m_objInfo.pos.x += dist;
	m_objInfo.pos.y += dist;
	m_objInfo.pos.z += dist;

	if (m_time + PARTICLE_TIME < GetTickCount()) m_objInfo.haveToDelete = true;
}

void CParticle::Render()
{

	glPushMatrix();
	{
			glRotatef(m_objInfo.rotation.x, 1.0, 0.0, 0.0);
			glRotatef(m_objInfo.rotation.y, 0.0, 1.0, 0.0);
			glRotatef(m_objInfo.rotation.z, 0.0, 0.0, 1.0);
			glTranslatef(m_objInfo.pos.x, m_objInfo.pos.y, m_objInfo.pos.z);

			glColor3f(rand() / (float)RAND_MAX * 1.0f, rand() / (float)RAND_MAX * 1.0f, rand() / (float)RAND_MAX * 1.0f);
			glutSolidCube(0.2f);

	}
	glPopMatrix();
	
}