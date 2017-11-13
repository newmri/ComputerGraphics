#include "Define.h"
#include "CObject.h"

CFactory* CFactory::m_instance = nullptr;


shared_ptr<CObject> CFactory::CreateObj(int idx)
{
	shared_ptr<CObject> p = make_shared<CObject>();

	if (p == nullptr) {
		cout << "Memory alloc error" << endl;
		while (true);
	}

	p->Init(idx);

	return move(p);
}

