#include "Define.h"
#include "Objects.h"

CFactory* CFactory::m_instance = nullptr;


shared_ptr<CObject> CFactory::CreateObj(OBJECT_TYPE objType)
{
	shared_ptr<CObject> p = nullptr;

	switch (objType) {
	case CUBE: p = make_shared<CCube>(); break;
	case BALL: p = make_shared<CBall>(); break;

	default: cout << "Type Error has been ocuured!" << endl; while (true);
	}
	if (p == nullptr) {
		cout << "Memory alloc error" << endl;
		while (true);
	}

	p->Init(objType);
	p->Init();

	return move(p);
}

shared_ptr<CObject> CFactory::CreateObj(OBJECT_TYPE objType, float size)
{
	shared_ptr<CObject> p = nullptr;

	switch (objType) {
	case TINYCUBE: p = make_shared<CTinyCube>(); break;
	default: cout << "Type Error has been ocuured!" << endl; while (true);
	}
	if (p == nullptr) {
		cout << "Memory alloc error" << endl;
		while (true);
	}

	p->Init(objType);
	p->Init();
	p->SetSize(size);
	if(size == 10) p->SetPos(Vector3(-(CUBE_RAD - (size / 2.0f)), -(CUBE_RAD - size / 2.0f), -CUBE_RAD / 2.0f));
	else if(size == 5) p->SetPos(Vector3(-(CUBE_RAD - (size / 2.0f)), -(CUBE_RAD - size / 2.0f), -CUBE_RAD / 2.0f + size));
	else p->SetPos(Vector3(-(CUBE_RAD - (size / 2.0f)), -(CUBE_RAD - size / 2.0f), -CUBE_RAD / 2.0f + size + 5));
	return move(p);
}
