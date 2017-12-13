#include "Define.h"
#include "Objects.h"

void CPlayer::Init()
{
	m_objInfo.size = 5.0f;
}

void CPlayer::Move()
{

}

void CPlayer::Update()
{
	
}

void CPlayer::Render()
{

	glPushMatrix();

	glTranslatef(m_objInfo.pos.x, m_objInfo.pos.y, m_objInfo.pos.z);
	//glTranslatef(m_objInfo.pos.x, CAMERAMANAGER->GetPos().y - (m_playerInfo.handSize + m_playerInfo.armSize), CAMERAMANAGER->GetPos().z - 1.0f);
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
		/*
		if (m_playerInfo.haveGun) // ÃÑÀÌ¶û Ãæµ¹µÇ¾úÀ¸¸é
		{
			gun.pos.x = 0;
			gun.pos.y = 0.1;
			gun.pos.z = 0;
			gun.size = 0.1;
			gun.draw_gun();


			glTranslatef(gun.bullets.pos.x, gun.bullets.pos.y, gun.bullets.pos.z);
			printf("%f %f %f\n", gun.bullets.pos.x, gun.bullets.pos.y, gun.bullets.pos.z);
			glColor4f(0.0, 1.0, 0.0, 1.0);
			glutSolidSphere(gun.bullets.size, 10, 10);

		}
		*/
	}
	glPopMatrix();
	glPopMatrix();


}
