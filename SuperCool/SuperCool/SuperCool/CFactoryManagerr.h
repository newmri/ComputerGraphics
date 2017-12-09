#pragma once

#include <memory>
#include "Enum.h"

struct ObjectInfo;
struct CObject;
struct Vector3;
struct Color;

class CFactoryManager
{
public:
	static CFactoryManager* GetInstance()
	{
		if (m_instance == nullptr)
			m_instance = new CFactoryManager;

		return m_instance;
	}

	std::shared_ptr<CObject> CreateObj(ObjectInfo objInfo);

private:
	CFactoryManager(void) {};
	~CFactoryManager(void) { delete m_instance; };

	static CFactoryManager* m_instance;

};