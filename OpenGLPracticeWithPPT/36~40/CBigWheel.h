#pragma once

#include "CObject.h"

class CBigWheel : public CObject
{
public:
	virtual void Init();
	virtual void Update();
	virtual void Render();

private:
	float m_seatSize;
};