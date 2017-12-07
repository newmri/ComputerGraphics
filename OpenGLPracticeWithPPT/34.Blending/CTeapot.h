#pragma once

#include "CShape.h"

class CTeapot : public CShape
{
public:
	virtual void Update();
	virtual void Render();
};