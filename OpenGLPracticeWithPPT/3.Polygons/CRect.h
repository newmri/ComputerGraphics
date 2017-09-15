#ifndef CRECT_H
#define CRECT_H

#include "CTriangle.h"

class CRect : public CTriangle
{
public:
	virtual void Init(SHAPE shape, int x, int y);

public:
	virtual void Render();

protected:
	int m_p4[2];
};

#endif