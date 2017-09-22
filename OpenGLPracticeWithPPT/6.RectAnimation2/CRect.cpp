#include "CRect.h"

void CRect::SetPos(DATA_TYPE x, DATA_TYPE y)
{
	m_pos.left = x;
	m_pos.right = m_pos.left + m_width;
	m_pos.top = y;
	m_pos.bottom = m_pos.top + m_height;

	m_firstPos = m_pos;

}

void CRect::ChangeColor()
{
	m_rgb.R = rand() % static_cast<int>(RGB);
	m_rgb.G = rand() % static_cast<int>(RGB);
	m_rgb.B = rand() % static_cast<int>(RGB);

}

void CRect::ChangeShape()
{
	m_changeShape = !m_changeShape;
	if (m_changeShape) {
		m_pos.right = m_pos.left + m_height;
		m_pos.bottom = m_pos.top + m_width;
	}
	else {
		m_pos.right = m_pos.left + m_width;
		m_pos.bottom = m_pos.top + m_height;
	}
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void CRect::ChangeSpeed(const int speed)
{
	if (m_speed + speed < 0) return;
	m_speed += speed;
}

void CRect::Move()
{

	if (m_moveCnt == MAX_MOVE - 1) {
		if ((m_dx > 0 && m_pos.left < m_firstPos.left) ||
			(m_dx < 0 && m_pos.left > m_firstPos.left)) {
			m_pos.left += m_dx * m_speed;
			m_pos.right = m_pos.left + m_width;
		}

		else {
			if ((m_dy > 0 && m_pos.top < m_firstPos.top) ||
				(m_dy < 0 && m_pos.top > m_firstPos.top)) {
				m_pos.top += m_dy * m_speed;
				m_pos.bottom = m_pos.top + m_height;
			}
			else m_moveCnt++;

		}
		glClear(GL_COLOR_BUFFER_BIT);
		return;
	}

	if (m_moveHorizontal) {
		m_pos.left += m_dx * m_speed;
		m_pos.right = m_pos.left + m_width;
	}

	else {
		m_pos.top += m_dy * m_speed;
		m_pos.bottom = m_pos.top + m_height;
	}

	if (m_pos.left < 0 || m_pos.right > WINDOW_SIZE_WIDTH) {
		m_pos.left = (m_pos.right > WINDOW_SIZE_WIDTH) ? (WINDOW_SIZE_WIDTH - 1) - m_width : 0;
		m_pos.right = m_pos.left + m_width;
		m_dx = -m_dx;
		m_moveHorizontal = false;
		m_moveCnt++;
	}

	if (m_pos.top < 0 || m_pos.bottom > WINDOW_SIZE_HEIGHT) {
		m_pos.top = (m_pos.bottom > WINDOW_SIZE_HEIGHT) ? m_pos.top = (WINDOW_SIZE_HEIGHT - 1) - m_height : 0;
		m_pos.bottom = m_pos.top + m_height;
		m_dy = -m_dy;
		m_moveHorizontal = true;
		m_moveCnt++;
	}

	glClear(GL_COLOR_BUFFER_BIT);

}

void CRect::Draw()
{
	glColor4f(m_rgb.R / RGB, m_rgb.G / RGB, m_rgb.B / RGB, 1.0f);
	glRecti(m_pos.left, m_pos.top, m_pos.right, m_pos.bottom);

}