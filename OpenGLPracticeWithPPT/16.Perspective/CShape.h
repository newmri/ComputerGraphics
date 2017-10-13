#ifndef CTRIANGLE_H
#define CTRIANGLE_H

#include "CMovableObject.h"

class CShape : public CMovableObject
{
public:
	virtual void Init(OBJTYPE objType, MOVETYPE moveType, Pos pos, DATA_TYPE size);
	virtual void Update();
	virtual void Render();

public:
	virtual void Move();

};

#endif
