#ifndef CRECT_H
#define CRECT_H

#include "CMovableObject.h"

class CRect : public CMovableObject
{
public:
	virtual void Init(OBJTYPE objType, MOVETYPE moveType, Pos pos);
	virtual void Update();
	virtual void Render();
	
public:
	void Init(OBJTYPE objType, MOVETYPE moveType, Pos pos, float size);

public:
	virtual void Move();

private:
	float m_size;
};

#endif