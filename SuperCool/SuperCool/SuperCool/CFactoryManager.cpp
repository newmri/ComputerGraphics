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
	case OBJECT_TYPE::BULLET: p = make_shared<CBullet>(); break;
	case OBJECT_TYPE::ITEM: p = make_shared<CItem>(); break;
	case OBJECT_TYPE::PARTICLE: p = make_shared<CParticle>(); break;
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

unique_ptr<CBullet>  CFactoryManager::CreateBullet(ObjectInfo objInfo)
{
	unique_ptr<CBullet> p = nullptr;
	if (objInfo.objType == BULLET) p = make_unique<CBullet>();

	if (p == nullptr) {
		cout << "Memory alloc error" << endl;
		while (true);
	}

	p->Init(objInfo);
	p->Init();

	return move(p);

}