#include "Define.h"
#include "Shape.h"

CFactory* CFactory::m_instance = nullptr;


unique_ptr<CShape> CFactory::CreateObj(SHAPE shape, int x, int y)
{
	unique_ptr<CShape> p = nullptr;

	switch (shape) {
	case SHAPE::RECTANGLE: p = make_unique<CRect>(); break;
	case SHAPE::CIRCLE: p = make_unique<CCircle>(); break;
	default: break;
	}

	p->Init(shape, x, y);
	return move(p);
}
