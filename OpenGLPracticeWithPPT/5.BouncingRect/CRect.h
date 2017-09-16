#ifndef CRECT_H
#define CRECT_H

#include "CShape.h"

class CRect : public CShape
{

public:
	virtual void Init(SHAPE shape, int x, int y);

public:
	virtual void ChangeColor();
	virtual void ChangeSpeed(const int speed);

public:
	virtual void Move();

public:
	virtual void Draw();

private:
	Pos m_pos;
	DATA_TYPE m_width, m_height;
};

#endif