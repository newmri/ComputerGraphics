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
	SHAPE GetType() { return m_shape; }
	Pos GetPos() { return m_pos; }

public:
	virtual void Move() = 0;

public:
	virtual void Draw() = 0;

public:
	CShape()
	{

		m_speed = (rand() % SPEED) + 1;
		m_dx = m_speed;
		m_dy = m_speed;
	}
protected:
	SHAPE m_shape;
	Rgb m_rgb;
	Pos m_pos;
	DATA_TYPE m_dx, m_dy;
	DATA_TYPE m_speed;
};

#endif