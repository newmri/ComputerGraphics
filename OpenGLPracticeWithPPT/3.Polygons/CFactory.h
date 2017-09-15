#ifndef CFACOTRY_H
#define CFACOTRY_H

#include <memory>

class CPolygon;

class CFactory
{
public:
	static CFactory* GetInstance()
	{
		if (m_instance == nullptr)
			m_instance = new CFactory;

		return m_instance;
	}

	std::unique_ptr<CPolygon> CreateObj(SHAPE shape, int x, int y);

private:
	CFactory(void) {};
	~CFactory(void) { delete m_instance; };

	static CFactory* m_instance;

};

#endif
