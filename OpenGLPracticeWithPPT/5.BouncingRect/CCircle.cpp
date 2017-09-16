#include "CCircle.h"

#include <math.h>

void CCircle::Init(SHAPE shape, int x, int y)
{
	m_shape = shape;
	m_x = x, m_y = y;

	m_rad = (rand() % MAX_RAD) + MIN_RAD;

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
	m_x += m_dx * m_speed;
	m_y += m_dy * m_speed;


	if (m_x - m_rad < 0 || m_x + m_rad> WINDOW_SIZE_WIDTH - 1) {
		m_x = (m_x + m_rad> WINDOW_SIZE_WIDTH - 1) ? m_x = (WINDOW_SIZE_WIDTH - 1) - m_rad : m_rad;
		m_dx = -m_dx;
	}

	
	if (m_y - m_rad < 0 || m_y + m_rad > WINDOW_SIZE_HEIGHT - 1) {
		m_y = (m_y + m_rad> WINDOW_SIZE_HEIGHT - 1) ? m_y = (WINDOW_SIZE_HEIGHT - 1) - m_rad : m_rad;
		m_dy = -m_dy;
	}
	glClear(GL_COLOR_BUFFER_BIT);
}

void CCircle::Draw()
{
	glColor4f(m_rgb.R / RGB, m_rgb.G / RGB, m_rgb.B / RGB, 1.0f);
	glBegin(GL_POLYGON);
	for (int i = 0; i < 360; ++i) {
		double angle = i * 3.141592 / 180;
		double x = m_rad * cos(angle);
		double y = m_rad * sin(angle);
		glVertex2f(x + m_x, y + m_y);
	}
	glEnd();
}