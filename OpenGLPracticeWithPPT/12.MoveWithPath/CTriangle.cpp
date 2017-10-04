#include "CTriangle.h"

void CTriangle::Init(OBJTYPE objType, MOVETYPE moveType, Pos pos) {}

void CTriangle::Move()
{
	switch (m_pathType) {
	case OBJTYPE::CIRCLE: this->MoveWithCircle(); break;
	case OBJTYPE::SINWAVE: this->MoveWithSinWave(); break;
	case OBJTYPE::ZIGZAG: this->MoveWithZigZag(); break;
	case OBJTYPE::TORNADO: this->MoveWithTornado(); break;
	}
}

void CTriangle::Update()
{
	this->Move();
	if (m_bounceTime + BOUNCE_TIME < GetTickCount()) {
		this->Bounce();
		m_bounceTime = GetTickCount();
	}
}

void CTriangle::Render()
{

	glColor3f(1.0, 0.0, 0.0);
	glTranslatef(m_pos.x, m_pos.y, 0.0f);
	glRotatef(m_angle * (180 / PIE), 0.0, 0.0, 1.0);
	glutSolidCone(m_size, m_size, 3, 3);
}

