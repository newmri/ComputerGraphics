#include "Define.h"
#include "Objects.h"

CFactory* CFactory::m_instance = nullptr;

unique_ptr<CObject> CFactory::CreateObj(OBJTYPE objType, MOVETYPE moveType, Pos pos)
{
	unique_ptr<CShape> p = nullptr;

	switch (objType) {
	case CIRCLE: p = make_unique<CCircle>(); break;
	default: break;
	}
	
	if (p == nullptr) {
		cout << "Memory alloc error" << endl;
		while (true);
	}

	p->Init(objType, moveType, pos);
	return move(p);
}
