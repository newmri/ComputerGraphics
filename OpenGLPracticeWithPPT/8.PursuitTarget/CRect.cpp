#include "CRect.h"
#include "CEffect.h"
#include "Define.h"

void CRect::Init(SHAPE shape, int x, int y)
{
	
	m_shape = shape;
	m_width = (rand() % MAX_RECT_SIZE) + 10;
	m_height = (rand() % MAX_RECT_SIZE) + 10;


	m_pos.left = x;
	m_pos.right = m_pos.left + m_width;
	m_pos.top = y;
	m_pos.bottom = m_pos.top + m_height;
	
}

void CRect::ChangeColor()
{
	m_rgb.R = rand() % static_cast<int>(RGB);
	m_rgb.G = rand() % static_cast<int>(RGB);
	m_rgb.B = rand() % static_cast<int>(RGB);

}

void CRect::ChangeSpeed(const int speed)
{
	if (m_speed + speed < 0) return;
	m_speed += speed;
}

void CRect::SetTarget(Pos pos)
{
	m_targetPos = pos;
}

void CRect::SetTarget(Pos pos, double rad)
{
	m_targetPos = pos;
	m_targetRad = rad;
}

void CRect::Move()
{

	// Target is right direction
	if (m_pos.right <  m_targetPos.x - m_targetRad) {
		if(m_dx < 0) m_dx = -m_dx;
		m_pos.left += m_dx * m_speed;
		m_pos.right = m_pos.left + m_width;
	}
	
	// Target is left direction
	else if (m_pos.left > m_targetPos.x + m_targetRad) {
		if(m_dx > 0) m_dx = -m_dx;
		m_pos.left += m_dx * m_speed;
		m_pos.right = m_pos.left + m_width;
	}


	// Target is up direction 
	if (m_pos.top > m_targetPos.y + m_targetRad) {
		if (m_dy > 0) m_dy = -m_dy;
		m_pos.top += m_dy * m_speed;
		m_pos.bottom = m_pos.top + m_height;
	}
	// Target is down direction 
	else if (m_pos.bottom < m_targetPos.y - m_targetRad) {
		if (m_dy < 0) m_dy = -m_dy;
		m_pos.top += m_dy * m_speed;
		m_pos.bottom = m_pos.top + m_height;
	}

	glClear(GL_COLOR_BUFFER_BIT);
}

void CRect::Draw()
{
	glColor4f(m_rgb.R / RGB, m_rgb.G / RGB, m_rgb.B / RGB, 1.0f);
	glRecti(m_pos.left, m_pos.top, m_pos.right, m_pos.bottom);

}