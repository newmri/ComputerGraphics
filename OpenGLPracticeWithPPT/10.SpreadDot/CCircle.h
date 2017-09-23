#ifndef CCIRCLE_H
#define CCIRCLE_H

#include "CShape.h"

const int MAX_RAD = 20;
const int MIN_RAD = 10;

class CCircle : public CShape
{
public:
	virtual void Init(OBJTYPE objType, MOVETYPE moveType, Pos pos);
	virtual void Update();
	virtual void Render();

public:
	const double& GetRad() { return m_rad; }

public:
	virtual void Move();

public:
	void DownSize();

private:
	double m_rad;
	DWORD m_sizeDownTime;
};

#endif