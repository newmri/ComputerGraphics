#pragma once

#include <vector>
#include <memory>
#include "CCharacter.h"
#include "CBullet.h"

struct PlayerInfo
{
	float armSize, handSize;
	bool haveGun;
	PlayerInfo()
	{
		armSize = 0.3f;
		handSize = 0.1f;
		haveGun = false;
	}
};

class CPlayer : public CCharacter
{
public:
	virtual void Init();
	virtual void Move(float frameTime);
	virtual void Update(float frameTime);
	virtual void Render();

public:
	int GetBulletNum() { return m_bullet.size(); }
public:
	void SetPos(const float x, const float y, const float z) { m_objInfo.pos.x = x; m_objInfo.pos.y = y - (m_playerInfo.handSize + m_playerInfo.armSize); m_objInfo.pos.z = z; }
	void CreateBullet(ObjectInfo info);
	void DeleteBullet();

public:
	void Shoot();
private:
	PlayerInfo m_playerInfo;
	std::vector<std::unique_ptr<CBullet>> m_bullet;
};