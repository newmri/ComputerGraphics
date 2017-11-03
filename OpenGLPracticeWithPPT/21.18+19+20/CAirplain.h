#pragma once

#include "CObject.h"

class CAirplain : public CObject
{
public:
	virtual void Init();
	virtual void Update();
	virtual void Render();


public:
	void Move();

private:
	float m_incre;
	Vector3 m_propelerRotation;
	float m_proplerAngle;
};
