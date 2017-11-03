#ifndef CFACOTRY_H
#define CFACOTRY_H

#include <memory>
#include "Enum.h"

typedef float DATA_TYPE;

class CObject;
struct Vector3;
struct Color;

class CFactory
{
public:
	static CFactory* GetInstance()
	{
		if (m_instance == nullptr)
			m_instance = new CFactory;

		return m_instance;
	}

	std::shared_ptr<CObject> CreateObj(OBJTYPE objType, Vector3 pos, Vector3 scale, DATA_TYPE size, Color color);
	std::shared_ptr<CObject> CreateObj(OBJTYPE objType, Vector3 pos, Vector3 scale, DATA_TYPE size, Color bodycolor, Color leafcolor);
private:
	CFactory(void) {};
	~CFactory(void) { delete m_instance; };

	static CFactory* m_instance;

};

#endif
