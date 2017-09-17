#include "CCircle.h"

#include <math.h>

void CCircle::Init(SHAPE shape, int x, int y)
{
	m_shape = shape;
	m_pos.x = x, m_pos.y = y;

	m_rad = MIN_RAD;

}

void CCircle::ChangeColor()
{
	m_rgb.R = rand() % static_cast<int>(RGB);
	m_rgb.G = rand() % static_cast<int>(RGB);
	m_rgb.B = rand() % static_cast<int>(RGB);

}

void CCircle::ChangeSpeed(const int speed)
{
	if (m_speed + speed < 0) return;
	m_speed += speed;
}

void CCircle::Move()
{
	//glClear(GL_COLOR_BUFFER_BIT);
}

void CCircle::Draw()
{
	glColor4f(m_rgb.R / RGB, m_rgb.G / RGB, m_rgb.B / RGB, 1.0f);
	glBegin(GL_POLYGON);
	for (int i = 0; i < 360; ++i) {
		double angle = i * 3.141592 / 180;
		double x = m_rad * cos(angle);
		double y = m_rad * sin(angle);
		glVertex2f(x + m_pos.x, y + m_pos.y);
	}
	glEnd();
}