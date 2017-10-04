#ifndef CCIRCLE_H
#define CCIRCLE_H

#include "CRect.h"

class CCircle : public CRect
{
public:
	virtual void Init(OBJTYPE objType, MOVETYPE moveType, Pos pos);
	virtual void Update();
	virtual void Render();

public:
	virtual void Move();

};

#endif
