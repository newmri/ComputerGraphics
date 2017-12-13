#pragma once

#include "CObject.h"

struct Bullet
{
	Vector3 pos;
	float speed;
	float size;
	Bullet()
	{
		speed = 1.0f;
		size = 0.01f;
	}
};

class CGun : public CObject
{
public:
	virtual void Init();
	virtual void Update();
	virtual void Render();

public:
	Bullet m_bullet[5];
	int m_bulletIdx;
};