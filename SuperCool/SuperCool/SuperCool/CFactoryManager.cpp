#include "Define.h"
#include "Objects.h"

CFactoryManager* CFactoryManager::m_instance = nullptr;


shared_ptr<CObject> CFactoryManager::CreateObj(ObjectInfo objInfo)
{
	shared_ptr<CObject> p = nullptr;

	switch (objInfo.objType) {
	case OBJECT_TYPE::CUBE: p = make_shared<CCube>(); break;
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
