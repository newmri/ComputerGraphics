#ifndef COBJECT_H
#define COBJECT_H

#include "Define.h"

class CObject
{
public:
	virtual void Init(OBJTYPE objType, MOVETYPE moveType, Pos pos) = 0;
	virtual void Update() = 0;
	virtual void Render() = 0;

public:
	const OBJTYPE& GetObjType() { return m_objType; }
	const MOVETYPE& GetMoveType() { return m_moveType; }
	const Pos& GetPos() { return m_pos; }
	const Color& GetColor() { return m_color; }

public:
	void SetPos(const Pos newPos) { m_pos = newPos; }
	void SetColor(const Color newColor) { m_color = newColor; }

protected:
	OBJTYPE m_objType;
	MOVETYPE m_moveType;
	Color m_color;
	Pos m_pos, m_borderPos;
};

#endif