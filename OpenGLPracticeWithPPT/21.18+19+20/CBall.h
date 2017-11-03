#pragma once

#include "CObject.h"

class CBall : public CObject
{
public:
	virtual void Init();
	virtual void Update();
	virtual void Render();


public:
	void Move();

private:
	float m_incre;
};