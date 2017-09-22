#include "Define.h"
#include "Shape.h"

CFactory* CFactory::m_instance = nullptr;


unique_ptr<CShape> CFactory::CreateObj(SHAPE shape, int x, int y)
{
	unique_ptr<CShape> p = nullptr;

	switch (shape) {
	case SHAPE::SPIRAL: p = make_unique<CSpiral>(); break;
	default: break;
	}

	p->Init(shape, x, y);
	return move(p);
}
