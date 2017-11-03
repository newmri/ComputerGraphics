#pragma once

#include "CObject.h"

class CCornBuilding : public CObject
{
public:
	virtual void Init();
	virtual void Update();
	virtual void Render();

public:
	void ExpandAndReduct();
private:
	float m_leafSize;
	float m_incre[2];
	float m_maxSize;
	Vector3 m_scale2;
};