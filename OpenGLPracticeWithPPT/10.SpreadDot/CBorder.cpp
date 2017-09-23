#include "CBorder.h"

void CBorder::Init(OBJTYPE objType, MOVETYPE moveType, Pos pos)
{
	m_objType = objType;
	m_moveType = moveType;
	m_pos = pos;
	this->SetColor(Color(255.0f, 255.0f, 255.0f));

}


void CBorder::Update()
{
}

void CBorder::Render()
{
	glColor4f(m_color.R / RGB, m_color.G / RGB, m_color.B / RGB, 1.0f);
	glRecti(m_pos.x, m_pos.y, m_endPos.x, m_endPos.y);
}