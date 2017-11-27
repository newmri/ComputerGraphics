#pragma once

#include "CObject.h"

class CPyramid : public CObject
{
public:
	virtual void Init();
	virtual void Update();
	virtual void Render();

private:
	Vector3 m_doorScale;
	float m_yDist;
	float m_doorIncre, m_doorPosIncre;
	float m_planetAngle, m_moonAngle;
};