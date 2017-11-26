#pragma once

#include "CObject.h"

class CLight : public CObject
{
public:
	virtual void Init();
	virtual void Update();
	virtual void Render();

};
