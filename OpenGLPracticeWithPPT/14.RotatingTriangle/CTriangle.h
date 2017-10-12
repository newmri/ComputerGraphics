#ifndef CTRIANGLE_H
#define CTRIANGLE_H

#include "CMovableObject.h"

class CTriangle : public CMovableObject
{
public:
	virtual void Init(OBJTYPE objType, MOVETYPE moveType, Pos pos, DATA_TYPE size);
	virtual void Update();
	virtual void Render();

public:
	virtual void Move();

private:
	Pos m_trianglePos[4];
	int m_i;
	int m_idx;
};

#endif
