#ifndef CBORDER_H
#define CBORDER_H

#include "CObject.h"

class CBorder : public CObject
{
public:
	virtual void Init(OBJTYPE objType, MOVETYPE moveType, Pos pos);
	virtual void Update();
	virtual void Render();

public:
	const Pos& GetEndPos() { return m_endPos; }

public:
	void SetEndPos(Pos pos) { m_endPos = pos; }

private:
	Pos m_endPos;
};

#endif