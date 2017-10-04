#ifndef CTRIANGLE_H
#define CTRIANGLE_H

#include "CCircle.h"

class CTriangle : public CCircle
{
public:
	virtual void Init(OBJTYPE objType, MOVETYPE moveType, Pos pos);
	virtual void Update();
	virtual void Render();

public:
	virtual void Move();

};

#endif
