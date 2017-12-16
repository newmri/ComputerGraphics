#pragma once

#include "CCharacter.h"
#include "CParticle.h"

class CEnemy : public CCharacter
{
public:
	virtual void Init();
	virtual void Move(float frameTime);
	virtual void Update(float frameTime);
	virtual void Render();

public:
	void SetSpeed(float speed) { m_speed = speed; }

public:
	float GetSpeed() { return m_speed; }
public:
	void LookPlayer();

private:
	float m_speed;
};

