#include "Define.h"
#include "Objects.h"

CFactory* CFactory::m_instance = nullptr;


shared_ptr<CObject> CFactory::CreateObj(OBJTYPE objType, Vector3 pos, DATA_TYPE size, Color color)
{
	shared_ptr<CObject> p = nullptr;
	switch (objType) {
	case OBJTYPE::UNKNOWN: break;
	case OBJTYPE::CUBE: p = make_shared<CCube>(); break;
	case OBJTYPE::PARTICLE: p = make_shared<CParticle>(); break;
	case OBJTYPE::PLANET: p = make_shared<CPlanet>(); break;
	case OBJTYPE::EARTH: p = make_shared<CPlanet>(); break;
	case OBJTYPE::CONTROLLER: p = make_shared<CController>(); break;
	case OBJTYPE::AIRPLANE: p = make_shared<CAirPlane>(); break;
	default: break;
	}

	if (p == nullptr) {
		cout << "Memory alloc error" << endl;
		while (true);
	}

	p->Init(objType, pos, size, color);
	p->Init();

	return move(p);
}

shared_ptr<CObject> CFactory::CreateObj(OBJTYPE objType, Vector3 pos, Vector3 target[], DATA_TYPE size, Color color)
{
	shared_ptr<CObject> p = nullptr;
	switch (objType) {
	case OBJTYPE::UNKNOWN: break;
	case OBJTYPE::AIRPLANE: p = make_shared<CAirPlane>(); break;
	default: break;
	}

	if (p == nullptr) {
		cout << "Memory alloc error" << endl;
		while (true);
	}

	p->Init(objType, pos, size, color);
	p->Init();
	CAirPlane* ap = dynamic_cast<CAirPlane*> (p.get());
	ap->SetTarget(target);

	return move(p);
}