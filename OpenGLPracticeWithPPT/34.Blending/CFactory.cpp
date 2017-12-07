#include "Define.h"
#include "Objects.h"

CFactory* CFactory::m_instance = nullptr;


unique_ptr<CShape> CFactory::CreateObj(OBJTYPE objType, Pos pos, DATA_TYPE size)
{
	unique_ptr<CShape> p = nullptr;

	switch (objType) {
	case OBJTYPE::UNKNOWN: break;
	case OBJTYPE::TEAPOT: p = make_unique<CTeapot>(); break;
	case OBJTYPE::SPHERE:  p = make_unique<CSphere>(); break;
	case OBJTYPE::CONE: p = make_unique<CCone>();  break;
	default: break;
	}

	if (p == nullptr) {
		cout << "Memory alloc error" << endl;
		while (true);
	}

	p->Init(objType, pos, size);

	return move(p);
}