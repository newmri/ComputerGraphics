#pragma once
#ifndef CEFFECT_H
#define CEFFECT_H

#include "CCircle.h"

const int MAX_SPRED_RAD = MAX_RAD * 2;

class CEffect : public CCircle
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

public:
	virtual SHAPE GetType() { return m_shape; }
	bool GetDelete() { return m_deleteMe; }

private:
	double m_firstRad, m_rad;
	bool m_deleteCircle, m_deleteMe;
};

#endif