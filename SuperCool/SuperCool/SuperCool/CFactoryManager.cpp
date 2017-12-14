#include "Define.h"
#include "Objects.h"

CFactoryManager* CFactoryManager::m_instance = nullptr;


shared_ptr<CObject> CFactoryManager::CreateObj(ObjectInfo objInfo)
{
	shared_ptr<CObject> p = nullptr;

	switch (objInfo.objType) {
	case OBJECT_TYPE::CUBE: p = make_shared<CCube>(); break;
	case OBJECT_TYPE::PLAYER: p = make_shared<CPlayer>(); break;
	case OBJECT_TYPE::ENEMY: p = make_shared<CEnemy>(); break;
	case OBJECT_TYPE::GUN: p = make_shared<CGun>(); break;
	default: break;
	}
	
	if (p == nullptr) {
		cout << "Memory alloc error" << endl;
		while (true);
	}

	p->Init(objInfo);

	p->Init();

	return move(p);
}
