#include "CRect.h"

void CRect::SetPos(DATA_TYPE x, DATA_TYPE y)
{
	m_pos.left = x;
	m_pos.right = m_pos.left + m_width;
	m_pos.top = y;
	m_pos.bottom = m_pos.top + m_height;

}

void CRect::ChangeColor()
{
	if (m_rgb.G < RGB) m_rgb.G += 50.0f;
	else m_rgb.G = 0.0f;

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

void CRect::Draw()
{
	glColor4f(m_rgb.R / RGB, m_rgb.G / RGB, m_rgb.B / RGB, 1.0f);
	glRecti(m_pos.left, m_pos.top, m_pos.right, m_pos.bottom);

}