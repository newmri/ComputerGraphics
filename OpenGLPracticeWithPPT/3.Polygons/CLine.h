#ifndef CLINE_H
#define CLINE_H

#include "CPolygon.h"

class CLine : public CPolygon
{
public:
	virtual void Init(SHAPE shape, int x, int y);

public:
	virtual void Render();
	
};

#endif