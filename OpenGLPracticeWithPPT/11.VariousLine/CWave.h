#pragma once

#include "CMovableObject.h"

class CWave : public CMovableObject
{
public:
	virtual void Init(OBJTYPE objType, MOVETYPE moveType, Pos pos);
	virtual void Update();
	virtual void Render();

public:
	void Init(OBJTYPE objType, MOVETYPE moveType, WAVETYPE waveType);

public:
	virtual void Move();

private:
	WAVETYPE m_waveType;
	DATA_TYPE m_seta;
};