#ifndef CMOVABLEOBJECT_H
#define CMOVABLEOBJECT_H

#include "CObject.h"

class CMovableObject : public CObject
{
public:
	virtual void Init(OBJTYPE objType, MOVETYPE moveType, Pos pos){};
	virtual void Update() {};
	virtual void Render() {};

public:
	void Move() {};

public:
	void SetSpeed(DATA_TYPE newSpeed) { m_speed = newSpeed; }
	void ChangeSpeed(DATA_TYPE speed) { m_speed += speed; }
	
protected:
	DATA_TYPE m_speed;
	Pos m_dPos;
};

#endif