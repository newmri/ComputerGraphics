#pragma once

#include "CObject.h"

struct Bullet
{
	Vector3 pos;
	float speed;
	float size;
	Bullet()
	{
		speed = 10.0f;
		size = 0.01f;
	}
};

class CGun : public CObject
{
public:
	virtual void Init();
	virtual void Update(float frameTime);
	virtual void Render();

public:
	Bullet m_bullet[5];
	int m_bulletIdx;
};