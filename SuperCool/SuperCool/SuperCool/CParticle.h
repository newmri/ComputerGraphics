#pragma once

#include "CObject.h"

class CParticle : public CObject
{
public:
	virtual void Init();
	virtual void Update(float frameTime);
	virtual void Render();

private:
	float m_speed;
	DWORD m_time;

};