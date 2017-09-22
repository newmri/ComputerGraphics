#ifndef CSHAPE_H
#define CSHAPE_H

#include "Define.h"

class CShape
{

public:
	virtual void Init(SHAPE shape, int x, int y) = 0;

public:
	virtual void ChangeColor() = 0;
	virtual void ChangeSpeed(const int speed) = 0;

public:
	virtual SHAPE GetType() = 0;

public:
	virtual void Draw() = 0;

public:
	CShape()
	{

		m_speed = (rand() % SPEED) + 1;
		if (rand() % 2) {
			m_dx = -1 * m_speed;
			m_dy = -1 * m_speed;
		}
		else {
			m_dx = m_speed;
			m_dy = m_speed;
		}
	}
protected:
	SHAPE m_shape;
	Rgb m_rgb;
	int m_x, m_y;
	int m_dx, m_dy;
	int m_speed;
};

#endif