#include "Define.h"
#include "Polygons.h"

CFactory* CFactory::m_instance = nullptr;


unique_ptr<CPolygon> CFactory::CreateObj(SHAPE shape, int x, int y)
{
	unique_ptr<CPolygon> p = nullptr;

	switch (shape) {
	case SHAPE::LINE: p = make_unique<CLine>(); break;
	case SHAPE::TRIANGLE: p = make_unique<CTriangle>(); break;
	case SHAPE::RECTANGLE: p = make_unique<CRect>(); break;
	case SHAPE::PENTAGON: p = make_unique<CPentagon>(); break;
	default: break;
	}

	p->Init(shape, x, y);
	return move(p);
}
