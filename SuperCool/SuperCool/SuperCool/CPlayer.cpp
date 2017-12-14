#include "Define.h"
#include "Objects.h"

void CPlayer::Init()
{
	m_objInfo.size = 5.0f;
}

void CPlayer::Move(float frameTime)
{

}

void CPlayer::Shoot()
{
	if (m_gun.m_bulletIdx < 5 && m_playerInfo.haveGun) m_gun.m_bulletIdx++; 
}

void CPlayer::Update(float frameTime)
{
	if (m_playerInfo.haveGun) m_gun.Update(frameTime);
}

void CPlayer::Render()
{

	glPushMatrix();

	glTranslatef(m_objInfo.pos.x, m_objInfo.pos.y, m_objInfo.pos.z);
	glRotatef(-30.0, 0.0, 0.0, 1.0);
	//glRotatef(CAMERAMANAGER->GetDegreeX(), 0.0f, 0.0f, 1.0f);
	glPushMatrix();
	{
		glScalef(0.5, 1.5, 0.5);
		glColor3f(1.0, 1.0, 1.0);
		glutSolidCube(m_playerInfo.armSize);
	}
	glPopMatrix();

	glPushMatrix();
	{
		glTranslatef(0.0, 0.3, 0.0);
		glColor3f(0.6, 0.6, 0.0);
		glutSolidSphere(m_playerInfo.handSize, 20, 20);
		
		if (m_playerInfo.haveGun) // ÃÑÀÌ¶û Ãæµ¹µÇ¾úÀ¸¸é
		{
			m_gun.Render();

		}
		
	}
	glPopMatrix();
	glPopMatrix();


}
