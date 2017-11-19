#include "Define.h"
#include "Objects.h"

void CBall::Init()
{
	m_size = BALL_RAD;
	float speed{ BALL_SPEED };

	switch (rand() % 18) {
	case 0: m_vPos.x = speed; break;
	case 1: m_vPos.x = -speed; break;
	case 2: m_vPos.y = speed; break;
	case 3: m_vPos.y = -speed; break;
	case 4: m_vPos.x = speed; m_vPos.y = speed; break;
	case 5: m_vPos.x = speed; m_vPos.y = -speed; break;
	case 6: m_vPos.x = -speed; m_vPos.y = speed; break;
	case 7: m_vPos.x = -speed; m_vPos.y = -speed; break;
	case 8: m_vPos.z = speed; break;
	case 9: m_vPos.z = -speed; break;
	case 10: m_vPos.z = speed;  m_vPos.x = speed; break;
	case 11: m_vPos.z = -speed; m_vPos.x = -speed; break;
	case 12: m_vPos.z = speed;  m_vPos.y = speed; break;
	case 13: m_vPos.z = -speed; m_vPos.y = -speed; break;
	case 14: m_vPos.z = speed;  m_vPos.y = speed; m_vPos.x = speed; break;
	case 15: m_vPos.z = -speed; m_vPos.y = speed; m_vPos.x = -speed; break;
	case 16: m_vPos.z = speed;  m_vPos.y = -speed; m_vPos.x = speed; break;
	case 17: m_vPos.z = -speed; m_vPos.y = -speed; m_vPos.x = -speed; break;
	}
}

void CBall::Move()
{
	this->CheckCollision();
	m_pos += m_vPos;
	
}

void CBall::Update()
{
	this->Move();
}

void CBall::Render()
{
	glPushMatrix();
	glTranslatef(0.0f, 0.0f, CUBE_RAD / -2.0f);
	glTranslatef(m_pos.x, m_pos.y, m_pos.z); // Let's move!
	glColor3f(0.0f, 0.0f, 0.0f);
	glutSolidSphere(m_size, 25, 25);
	glPopMatrix();

}