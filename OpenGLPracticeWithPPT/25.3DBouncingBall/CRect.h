#pragma once

#include "CObject.h"

class CRect : public CObject
{

public:
	virtual void Init();
	virtual void Move();
	virtual void Update();
	virtual void Render();

};