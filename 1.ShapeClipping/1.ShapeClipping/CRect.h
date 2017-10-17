#pragma once

#include "CObject.h"


class CRect : public CObject
{

public:
	virtual void Init();
	virtual void Update();
	virtual void Render();

public:
	CRect() { this->Init(); }
	CRect(const POSITION position) { m_position = position; this->Init(); }
private:
	POSITION m_position;
	Flags m_flag;
};