#include "CRect.h"

void CRect::Init(OBJTYPE objType, MOVETYPE moveType, Pos pos) {}

void CRect::Init(OBJTYPE objType, MOVETYPE moveType, Pos pos, float size)
{
	m_objType = objType;
	m_moveType = moveType;
	m_pos = pos;
	m_size = size;
}

void CRect::Move()
{
}

void CRect::Update()
{

}

void CRect::Render()
{
	glTranslatef(m_pos.x, m_pos.y, 0.0f);
	glutSolidCube(m_size);
}

