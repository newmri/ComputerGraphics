#ifndef CSHAPE_H
#define CSHAPE_H

#include "CMovableObject.h"

class CShape : public CMovableObject
{
public:
	virtual void Init(OBJTYPE objType, MOVETYPE moveType, Pos pos) {};
	virtual void Update() {};
	virtual void Render() {};

public:
	virtual void Move() {};
};

#endif