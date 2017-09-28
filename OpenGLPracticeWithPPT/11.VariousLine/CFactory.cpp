#include "Define.h"
#include "Objects.h"

CFactory* CFactory::m_instance = nullptr;

unique_ptr<CObject> CFactory::CreateObj(OBJTYPE objType, MOVETYPE moveType, Pos pos)
{
	unique_ptr<CObject> p = nullptr;

	switch (objType) {
	case OBJTYPE::RECTANGLE: p = make_unique<CRect>(); break;
	case OBJTYPE::WAVE: p = make_unique<CWave>(); break;
	default: break;
	}
	
	if (p == nullptr) {
		cout << "Memory alloc error" << endl;
		while (true);
	}

	p->Init(objType, moveType, pos);
	return move(p);
}

unique_ptr<CObject> CFactory::CreateObj(OBJTYPE objType, MOVETYPE moveType, Pos pos, float size)
{
	unique_ptr<CObject> p = nullptr;
	unique_ptr<CRect> sp = nullptr;

	switch (objType) {
	case OBJTYPE::RECTANGLE: sp = make_unique<CRect>(); break;
	default: break;
	}


	sp->Init(objType, moveType, pos, size);
	p = move(sp);

	if (p == nullptr) {
		cout << "Memory alloc error" << endl;
		while (true);
	}

	return move(p);
}