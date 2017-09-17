#include "CEffect.h"

#include <math.h>

void CEffect::Init(SHAPE shape, int x, int y)
{
	m_shape = shape;
	m_pos.x = x, m_pos.y = y;

	m_rad = (rand() % MAX_RAD) + MIN_RAD;

	m_deleteMe = false;
}

void CEffect::ChangeColor()
{

	m_rgb.R = rand() % static_cast<int>(RGB);
	m_rgb.G = rand() % static_cast<int>(RGB);
	m_rgb.B = rand() % static_cast<int>(RGB);

}

void CEffect::ChangeSpeed(const int speed)
{
	if (m_speed + speed < 0) return;
	m_speed += speed;
}

void CEffect::Move()
{
	m_rad += m_speed;
	if (m_rad > MAX_SPRED_RAD) m_deleteMe = true;
	
	glClear(GL_COLOR_BUFFER_BIT);
}

void CEffect::Draw()
{
	glColor4f(m_rgb.R / RGB, m_rgb.G / RGB, m_rgb.B / RGB, 1.0f);
	glBegin(GL_POINTS);
	for (int i = 0; i < 360; i += 10) {
		double angle = (i * 3.141592 / 180);
		double x = m_rad * cos(angle);
		double y = m_rad * sin(angle);
		glVertex2f(x + m_pos.x, y + m_pos.y);
	}

	glEnd();
}