#pragma once

#include "CCharacter.h"

class CEnemy : public CCharacter
{
public:
	virtual void Init();
	virtual void Move(float frameTime);
	virtual void Update(float frameTime);
	virtual void Render();

public:
	void LookPlayer();
private:
	float m_speed;
	float m_rotate;
};