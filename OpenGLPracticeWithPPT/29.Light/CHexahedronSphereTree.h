#pragma once

#include "CObject.h"


class CHexahedronSphereTree : public CObject
{
public:
	virtual void Init();
	virtual void Update();
	virtual void Render();

public:
	void ExpandAndReduct();

private:
	float m_leafSize;
	float m_incre;
};