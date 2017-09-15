#ifndef CTRIANGLE_H
#define CTRIANGLE_H

#include "CPolygon.h"

class CTriangle : public CPolygon
{
public:
	virtual void Init(SHAPE shape, int x, int y);

public:
	virtual void Render();

protected:
	int m_p3[2];
};

#endif