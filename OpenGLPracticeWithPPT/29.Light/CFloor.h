#pragma once

#include "CObject.h"

class CFloor : public CObject
{
public:
	virtual void Init();
	virtual void Update();
	virtual void Render();
};