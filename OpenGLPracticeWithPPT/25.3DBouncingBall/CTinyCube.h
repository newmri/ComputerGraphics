#pragma once
#include "CObject.h"

class CTinyCube : public CObject
{

public:
	virtual void Init();
	virtual void Move();
	virtual void Update();
	virtual void Render();

private:
	bool m_firstMove;

};