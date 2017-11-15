#pragma once

#include "CObject.h"

class CFloor : public CObject
{
public:
	virtual void Init();
	virtual void Update();
	virtual void Render();

public:
	void ChangeControlPoint(int key);
private:
	float m_leftCtrlPoints[3][3][3], m_rightCtrlPoints[3][3][3];
	float m_incre[2];
};