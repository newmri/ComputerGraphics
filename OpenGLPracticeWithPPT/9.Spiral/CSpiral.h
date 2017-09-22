#ifndef CSPIRAL_H
#define CSPIRAL_H

#include "CShape.h"

const int MAX_RAD = 20;
const int MIN_RAD = 10;

const int MAX_SPRED_RAD = MAX_RAD * 2;

class CSpiral : public CShape
{
public:
	virtual void Init(SHAPE shape, int x, int y);

public:
	virtual void ChangeColor();
	virtual void ChangeSpeed(const int speed);


public:
	virtual void Draw();

public:
	virtual SHAPE GetType() { return m_shape; }
	bool GetDelete() { return m_deleteMe; }

private:
	double m_firstRad, m_rad;
	bool m_deleteMe;
	bool m_rightRotation;
};

#endif