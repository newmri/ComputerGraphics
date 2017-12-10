#pragma once

#include "CObject.h"

class CCube : public CObject
{
public:
	virtual void Init();
	virtual void Update();
	virtual void Render();

private:
	DWORD m_time;
};