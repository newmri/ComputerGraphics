#include "Define.h"
#include "Objects.h"

CFactoryManager* CFactoryManager::m_instance = nullptr;


shared_ptr<CObject> CFactoryManager::CreateObj(ObjectInfo objInfo)
{
	shared_ptr<CObject> p = nullptr;

	switch (objInfo.objType) {
	case OBJECT_TYPE::PYRAMID: p = make_shared<CPyramid>(); break;
	case OBJECT_TYPE::CUBE: p = make_shared<CCube>(); break;
	case OBJECT_TYPE::BIGWHEEL: p = make_shared<CBigWheel>(); break;
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
