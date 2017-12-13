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

private:
	Bullet m_bullet;
};