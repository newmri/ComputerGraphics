#ifndef CFACOTRY_H
#define CFACOTRY_H

#include <memory>

typedef float DATA_TYPE;

class CObject;

class CFactory
{
public:
	static CFactory* GetInstance()
	{
		if (m_instance == nullptr)
			m_instance = new CFactory;

		return m_instance;
	}

	std::shared_ptr<CObject> CreateObj(float (*arr)[3]);
private:
	CFactory(void) {};
	~CFactory(void) { delete m_instance; };

	static CFactory* m_instance;

};

#endif
