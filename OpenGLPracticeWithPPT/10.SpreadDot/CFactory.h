#ifndef CFACOTRY_H
#define CFACOTRY_H

#include <memory>
#include "Enum.h"

class CObject;
struct Pos;

class CFactory
{
public:
	static CFactory* GetInstance()
	{
		if (m_instance == nullptr)
			m_instance = new CFactory;

		return m_instance;
	}

	std::unique_ptr<CObject> CreateObj(OBJTYPE objType, MOVETYPE moveType, Pos pos);

private:
	CFactory(void) {};
	~CFactory(void) { delete m_instance; };

	static CFactory* m_instance;

};

#endif
