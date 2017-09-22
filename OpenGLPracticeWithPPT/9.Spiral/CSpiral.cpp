#include "CSpiral.h"

#include <math.h>

void CSpiral::Init(SHAPE shape, int x, int y)
{
	m_shape = shape;
	m_x = x, m_y = y;

	m_rad = MAX_RAD;
	m_firstRad = m_rad;

	m_rightRotation = rand() % 2;
	m_deleteMe = false;
}

void CSpiral::ChangeColor()
{
	
	m_rgb.R = rand() % static_cast<int>(RGB);
	m_rgb.G = rand() % static_cast<int>(RGB);
	m_rgb.B = rand() % static_cast<int>(RGB);
	
}

void CSpiral::ChangeSpeed(const int speed)
{
	if (m_speed + speed < 0) return;
	m_speed += speed;
}



void CSpiral::Draw()
{
	double angle{}, x{}, y{};
	glColor4f(m_rgb.R / RGB, m_rgb.G / RGB, m_rgb.B / RGB, 1.0f);
	glBegin(GL_POINTS);
	
	double tx{}, ty{};
	
	if (!m_rightRotation) {
		for (int i = 20; i < 360 * 3 + 80; i += 10) {
			angle = (i * 3.141592 / 180);
			m_rad = MAX_RAD * exp(0.1 * angle);
			x = m_rad * cos(angle);
			y = m_rad * sin(angle);
			glVertex2f(y + m_x, x + m_y);
		}


		tx = x * 1.75 + 150, ty = y * 1.75 - 190;
		for (int i = 20; i < 360 * 3 - 180; i += 10) {
			angle = (i * 3.141592 / 180);
			m_rad = MAX_RAD * exp(0.1 * angle);
			x = m_rad * cos(angle);
			y = m_rad * sin(angle);
			glVertex2f(x + m_x + tx, y + m_y + ty);
		}
	}
	
	if (m_rightRotation) {
		for (int i = 20; i < 360 * 3; i += 10) {
			angle = (i * 3.141592 / 180);
			m_rad = MAX_RAD * exp(0.1 * angle);
			x = m_rad * cos(angle);
			y = m_rad * sin(angle);
			glVertex2f(x + m_x, y + m_y);
		}

		tx = x * 1.75, ty = y * 1.75;
		for (int i = 20; i < 360 * 2 + 170; i += 10) {
			angle = (i * 3.141592 / 180);
			m_rad = MAX_RAD * exp(0.1 * angle);
			x = m_rad * cos(angle);
			y = m_rad * sin(angle);
			glVertex2f(x + m_x + tx, y + m_y + ty);
		}
	}

	glEnd();
}