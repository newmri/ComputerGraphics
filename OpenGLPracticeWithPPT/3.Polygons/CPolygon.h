#ifndef CPOLYGON_H
#define CPOLYGON_H

#include "Define.h"

typedef int DATA_TYPE;


class CPolygon
{

public:
	virtual void Init(SHAPE shape, int x, int y) = 0;

public:
	SHAPE GetShape() { return m_shape; }

public:
	virtual void Render() = 0;

public:
	CPolygon()
	{
		m_width = (WINDOW_WIDTH / 3.0f) - 20.0f;
		m_height = (WINDOW_HEIGHT / 3.0f) - 10.0f;
	}
protected:
	DATA_TYPE m_width, m_height;
	Rgb m_rgb;
	SHAPE m_shape;
	int m_p1[2], m_p2[2];
};

#endif