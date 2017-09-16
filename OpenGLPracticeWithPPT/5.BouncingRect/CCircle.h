#ifndef CCIRCLE_H
#define CCIRCLE_H

#include "CShape.h"

const int MAX_RAD = 100;
const int MIN_RAD = 10;

class CCircle : public CShape
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
	double m_rad;
};

#endif