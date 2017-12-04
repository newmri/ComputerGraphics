#pragma once

#include "CObject.h"

class CPlanet : public CObject
{
public:
	virtual void Init();
	virtual void Update();
	virtual void Render();

private:
	int m_precision;
	int m_textureNum;
};