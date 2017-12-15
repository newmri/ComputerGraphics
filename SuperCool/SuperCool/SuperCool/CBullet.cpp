#include "Define.h"
#include "Objects.h"


void CBullet::Init()
{
	m_speed = BULLET_SPEED;
	m_onShoot = false;
	m_objInfo.haveToDelete = false;
}

void CBullet::Move(float speed)
{
	m_objInfo.pos.z -= speed; 

	for (auto& d : RENDERMANAGER->GetObjects()) {
		if (d->GetObjInfo().objType == ENEMY) {
			if (!this->CheckCollision(d->GetObjInfo())) {
				d->SetDelete();
				this->SetDelete();
			}
		}
	}

	if (this->m_objInfo.pos.z > 50.0f || this->m_objInfo.pos.z < -50.0f) this->SetDelete();
	
	
}

void CBullet::Update(float frameTime)
{
	
}

void CBullet::Render()
{

	glPushMatrix();
	glTranslatef(m_objInfo.pos.x, m_objInfo.pos.y, m_objInfo.pos.z);
	glColor3f(m_objInfo.color.r, m_objInfo.color.g, m_objInfo.color.b);
	glutSolidSphere(m_objInfo.size, 25, 25);
	if (RENDERMANAGER->ShowCollisionArea()) {
		glColor3f(1.0f, 0.0f, 0.0f);
		glutWireCube(m_objInfo.size);
	}
	glPopMatrix();

}