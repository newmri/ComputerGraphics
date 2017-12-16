#pragma once

#include "CObject.h"

class CItem : public CObject
{
public:
	virtual void Init();
	virtual void Move(float frameTime);
	virtual void Update(float frameTime);
	virtual void Render();

public:
	int GetItemType() { return m_imgIdx; }

private:
	float m_speed;
	int m_imgIdx;
	DWORD m_time;
};