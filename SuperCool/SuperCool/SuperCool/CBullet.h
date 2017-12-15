#pragma once

#include "CObject.h"


class CBullet : public CObject
{
public:
	void Init(ObjectInfo info) { m_objInfo = info; }
public:
	virtual void Init();
	virtual void Update(float frameTime);
	virtual void Render();

public:
	void Move(float speed);
	void Shoot() { m_onShoot = true; }

public:
	int GetSpeed() { return m_speed; }
	bool GetIsOnShoot() { return m_onShoot; }
private:
	int m_speed;
	bool m_onShoot;
};