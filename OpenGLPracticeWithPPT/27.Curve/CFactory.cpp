#include "Define.h"
#include "CObject.h"

CFactory* CFactory::m_instance = nullptr;


shared_ptr<CObject> CFactory::CreateObj(float(*arr)[3])
{
	shared_ptr<CObject> p = make_shared<CObject>();

	if (p == nullptr) {
		cout << "Memory alloc error" << endl;
		while (true);
	}

	p->Init(arr);

	return move(p);
}

