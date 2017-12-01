#include "Define.h"
#include "Objects.h"

CFactory* CFactory::m_instance = nullptr;


shared_ptr<CObject> CFactory::CreateObj(OBJTYPE objType, Vector3 pos, Vector3 scale, DATA_TYPE size, Color bodycolor, Color leafcolor)
{
	shared_ptr<CObject> p = nullptr;
	switch (objType) {
	case OBJTYPE::UNKNOWN: break;
	case OBJTYPE::FLOOR: p = make_shared<CFloor>(); break;
	case OBJTYPE::PYRAMID: p = make_shared<CPyramid>(); break;
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
	case OBJTYPE::PARTICLE: p = make_shared<CParticle>(); break;
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

shared_ptr<CObject> CFactory::CreateObj(OBJTYPE objType, Vector3 pos, DATA_TYPE size, float lightNum)
{
	shared_ptr<CObject> p = nullptr;
	switch (objType) {
	case OBJTYPE::LIGHT1:
	case OBJTYPE::LIGHT2:
	case OBJTYPE::LIGHT3:
	case OBJTYPE::LIGHT4:
		p = make_shared<CLight>(); break;
	default: break;
	}

	if (p == nullptr) {
		cout << "Memory alloc error" << endl;
		while (true);
	}

	p->Init(objType, pos, size, lightNum);
	p->Init();

	return move(p);
}