#pragma once

#include "CObject.h"

class CCube : public CObject
{
public:
	virtual void Init();
	virtual void Update(float frameTime);
	virtual void Render();
};