#include "Define.h"
#include "Objects.h"

void CPlayer::Init()
{
	m_objInfo.size = 5.0f;
}

void CPlayer::Move(float frameTime)
{
	for (auto& d : m_bullet) {
		if (d->GetIsOnShoot()) d->Move(frameTime * d->GetSpeed());
	}
}

void CPlayer::CreateBullet(ObjectInfo info)
{
	m_bullet.emplace_back(FACTORYMANAGER->CreateBullet(info));
}

void CPlayer::DeleteBullet()
{
	vector<unique_ptr<CBullet>>::iterator itor = m_bullet.begin();
	while (itor != m_bullet.end()) {
		if ((*itor)->GetDelete()) itor = m_bullet.erase(itor);
		else ++itor;
	}
}

void CPlayer::Shoot()
{
	if (m_bullet.size() >= 1) {
		m_bullet[m_bullet.size() - 1]->SetPos(Vector3(m_objInfo.pos.x, m_objInfo.pos.y, m_objInfo.pos.z - 10.0f));
		m_bullet[m_bullet.size() - 1]->Shoot();
		
	}
	
}

void CPlayer::Update(float frameTime)
{
	this->Move(frameTime);
	this->DeleteBullet();
}

void CPlayer::Render()
{

	glPushMatrix();
	glTranslatef(m_objInfo.pos.x, m_objInfo.pos.y, m_objInfo.pos.z);

	glPushMatrix();
	{
		glScalef(0.5, 1.5, 0.5);
		glColor3f(1.0, 1.0, 1.0);
		glutSolidCube(m_playerInfo.armSize);
	}
	glPopMatrix();

	
	for (auto& d : m_bullet) if(!d->GetIsOnShoot()) d->Render();
	
	glPopMatrix();

	for (auto& d : m_bullet) if (d->GetIsOnShoot()) d->Render();
}
