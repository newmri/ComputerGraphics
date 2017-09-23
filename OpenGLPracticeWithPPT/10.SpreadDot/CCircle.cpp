#include "CCircle.h"

#include <math.h>

void CCircle::Init(OBJTYPE objType, MOVETYPE moveType, Pos pos)
{
	m_objType = objType;
	m_moveType = moveType;
	m_pos = pos;

	m_moveDir = static_cast<MOVEDIRECTION>(rand() % MOVEDIRECTION::END);
	m_speed = (rand() % MAX_CIRCLE_SPEED) + 1;
	m_rad = (rand() % MAX_RAD) + MIN_RAD;

	m_sizeDownTime = GetTickCount();

	switch (m_moveDir) {
	case MOVEDIRECTION::L: m_dPos.x = -1, m_dPos.y = 0; break;
	case MOVEDIRECTION::R: m_dPos.x = 1, m_dPos.y = 0; break;
	case MOVEDIRECTION::U: m_dPos.x = 0, m_dPos.y = -1; break;
	case MOVEDIRECTION::D: m_dPos.x = 0, m_dPos.y = 1; break;
	case MOVEDIRECTION::LU: m_dPos.x = -1, m_dPos.y = -1; break;
	case MOVEDIRECTION::RU: m_dPos.x = 1, m_dPos.y = -1; break;
	case MOVEDIRECTION::LD: m_dPos.x = -1, m_dPos.y = 1; break;
	case MOVEDIRECTION::RD: m_dPos.x = 1, m_dPos.y = 1; break;
	}
}


void CCircle::DownSize()
{
	m_rad -= 0.2f;
}
void CCircle::Update()
{
	if (m_sizeDownTime + 100 < GetTickCount() && m_rad > MIN_RAD) {
		this->DownSize();
		m_sizeDownTime = GetTickCount();
	}
	this->Move();
}

void CCircle::Move()
{
	m_pos.x += m_dPos.x * m_speed;
	m_pos.y += m_dPos.y * m_speed;

	glClear(GL_COLOR_BUFFER_BIT);
}

void CCircle::Render()
{
	glColor4f(m_color.R / RGB, m_color.G / RGB, m_color.B / RGB, 1.0f);
	glBegin(GL_POINTS);
	for (int i = 0; i < 360; i += 10) {
		double angle = i * 3.141592 / 180;
		double x = m_rad * cos(angle);
		double y = m_rad * sin(angle);
		glVertex2f(x + m_pos.x, y + m_pos.y);
	}
	glEnd();
}