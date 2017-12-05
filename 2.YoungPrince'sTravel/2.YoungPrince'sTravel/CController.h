#pragma once

#include "Objects.h"

class CController : public CObject
{
public:
	virtual void Init();
	virtual void Update();
	virtual void Render();

public:
	Vector3 GetPoint() { return Vector3(m_x.x - ((CUBE_SIZE / 2.0f) - (EARTH_RAD / 2.0f)), m_y.y - ((CUBE_SIZE / 2.0f) - (EARTH_RAD / 2.0f)), m_z.z + CUBE_SIZE / 2.0f - EARTH_RAD); }

public:
	void Move(char dir);

private:
	Vector3 m_x, m_y, m_z;
};