#include "CRect.h"

void CRect::Init(SHAPE shape, int x, int y)
{
	m_shape = shape;
	m_x = x, m_y = y;

	m_pos.left = m_x;
	m_pos.right = m_pos.left + m_width;
	m_pos.top = m_y;
	m_pos.bottom = m_pos.top + m_height;

	m_width = (rand() % MAX_RECT_SIZE) + 10;
	m_height = (rand() % MAX_RECT_SIZE) + 10;
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

void CRect::Move()
{
	m_pos.left += m_dx * m_speed;
	m_pos.top += m_dy * m_speed;
	m_pos.right = m_pos.left + m_width;
	m_pos.bottom = m_pos.top + m_height;

	if (m_pos.left < 0 || m_pos.right > WINDOW_SIZE_WIDTH - 1) {
		m_pos.left = (m_pos.right > WINDOW_SIZE_WIDTH - 1) ? m_pos.right - m_width : 0;
		m_pos.right = m_pos.left + m_width;
		m_dx = -m_dx;
	}

	if (m_pos.top < 0 || m_pos.bottom > WINDOW_SIZE_HEIGHT - 1) {
		m_pos.top = (m_pos.bottom > WINDOW_SIZE_HEIGHT - 1) ? m_pos.top = m_pos.bottom - m_height : 0;
		m_pos.bottom = m_pos.top + m_height;
		m_dy = -m_dy;
	}


	glClear(GL_COLOR_BUFFER_BIT);
}

void CRect::Draw()
{
	glColor4f(m_rgb.R / RGB, m_rgb.G / RGB, m_rgb.B / RGB, 1.0f);
	glRecti(m_pos.left, m_pos.top, m_pos.right, m_pos.bottom);
}