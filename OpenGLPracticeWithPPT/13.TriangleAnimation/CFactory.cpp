#include "Define.h"
#include "Objects.h"

CFactory* CFactory::m_instance = nullptr;


unique_ptr<CObject> CFactory::CreateObj(OBJTYPE objType, MOVETYPE moveType, Pos pos, DATA_TYPE size)
{
	unique_ptr<CObject> p = nullptr;

	switch (objType) {
	case OBJTYPE::TRIANGLE: p = make_unique<CTriangle>(); break;
	default: break;
	}


	p->Init(objType, moveType, pos, size);

	if (p == nullptr) {
		cout << "Memory alloc error" << endl;
		while (true);
	}

	return move(p);
}