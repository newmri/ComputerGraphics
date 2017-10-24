#pragma once

#include "CObject.h"

class CHexahedronTorusTree : public CObject
{
public:
	virtual void Init();
	virtual void Update();
	virtual void Render();

public:
	void MoveUpAndDown();

private:
	Vector3 m_leafPos;
	float m_speed;

};