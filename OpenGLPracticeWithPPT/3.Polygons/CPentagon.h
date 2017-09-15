#ifndef CPENTAGON_H
#define CPENTAGON_H

#include "CRect.h"

class CPentagon : public CRect
{
public:
	virtual void Init(SHAPE shape, int x, int y);

public:
	virtual void Render();

protected:
	int m_p5[2];
};

#endif