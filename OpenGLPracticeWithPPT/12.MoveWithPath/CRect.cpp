#include "CRect.h"

void CRect::Init(OBJTYPE objType, MOVETYPE moveType, Pos pos) {}

void CRect::Init(OBJTYPE objType, MOVETYPE moveType, Pos pos, float size)
{
	m_objType = objType;
	m_moveType = moveType;
	m_pos = pos;
	m_size = size;
	m_i = 0.0f;
	m_speed = SPEED;
	m_bounceTime = GetTickCount();
	m_waveEnd = PIE / 4;
	m_theta = 0.0f;
	m_pathType = OBJTYPE::CIRCLE;
	m_tornadoSize = 7.0;
	m_zigzagIdx = 0;

	for (float x = -0.75f, y = 0.75; x < 1.0f; x += 0.15) {
		m_zigzagPos.push_back(Pos(x, y));
		y = -y;
	}

	m_interval = 0;
	

}


void CRect::Move()
{
	switch (m_pathType) {
	case OBJTYPE::CIRCLE: this->MoveWithCircle(); break;
	case OBJTYPE::SINWAVE: this->MoveWithSinWave(); break;
	case OBJTYPE::ZIGZAG: this->MoveWithZigZag(); break;
	case OBJTYPE::TORNADO: this->MoveWithTornado(); break;
	case OBJTYPE::LINE: this->MoveWithLine(); break;
	}


}

void CRect::Update()
{
	this->Move();
	if (m_bounceTime + BOUNCE_TIME < GetTickCount()) {
		this->Bounce();
		m_bounceTime = GetTickCount();
	}
	
}

void CRect::Render()
{
	glTranslatef(m_pos.x, m_pos.y, 0.0f);
	glutSolidCube(m_size);
}

