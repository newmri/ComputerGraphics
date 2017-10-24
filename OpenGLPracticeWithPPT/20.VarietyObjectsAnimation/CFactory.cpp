#include "Define.h"
#include "Objects.h"

CFactory* CFactory::m_instance = nullptr;


shared_ptr<CObject> CFactory::CreateObj(OBJTYPE objType, Vector3 pos, Vector3 scale, DATA_TYPE size, Color bodycolor, Color leafcolor)
{
	shared_ptr<CObject> p = nullptr;
	switch (objType) {
	case OBJTYPE::UNKNOWN: break;
	case OBJTYPE::FLOOR: p = make_shared<CFloor>(); break;
	case OBJTYPE::HEXAHEDRON_TREE: p = make_shared<CHexahedronTree>(); break;
	case OBJTYPE::HEXAHEDRON_SPHRE_TREE: p = make_shared<CHexahedronSphereTree>(); break;
	case OBJTYPE::HEXAHEDRON_TORUS_BUILDING: p = make_shared<CHexahedronTorusTree>(); break;
	case OBJTYPE::CORN_BUILDING: p = make_shared<CCornBuilding>(); break;
	case OBJTYPE::DOOR_BUILDING: p = make_shared<CDoorBuilding>(); break;
	default: break;
	}

	if (p == nullptr) {
		cout << "Memory alloc error" << endl;
		while (true);
	}

	p->Init(objType, pos, scale, size, bodycolor, leafcolor);
	p->Init();

	return move(p);
}

shared_ptr<CObject> CFactory::CreateObj(OBJTYPE objType, Vector3 pos, Vector3 scale, DATA_TYPE size, Color color)
{
	shared_ptr<CObject> p = nullptr;
	switch (objType) {
	case OBJTYPE::UNKNOWN: break;
	case OBJTYPE::FLOOR: p = make_shared<CFloor>(); break;
	default: break;
	}

	if (p == nullptr) {
		cout << "Memory alloc error" << endl;
		while (true);
	}

	p->Init(objType, pos, scale, size, color);
	p->Init();

	return move(p);
}