#pragma once

#include "CCharacter.h"
#include "CGun.h"

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
	virtual void Move();
	virtual void Update();
	virtual void Render();

public:
	void SetPos(const float x, const float y, const float z) { m_objInfo.pos.x = x; m_objInfo.pos.y = y - (m_playerInfo.handSize + m_playerInfo.armSize); m_objInfo.pos.z = z; }

private:
	PlayerInfo m_playerInfo;
	CGun m_gun;
};