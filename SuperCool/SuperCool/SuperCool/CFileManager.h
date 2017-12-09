#pragma once

class CFileManager
{
public:
	static CFileManager* GetInstance()
	{
		if (m_instance == nullptr)
			m_instance = new CFileManager;

		return m_instance;
	}

	CFileManager() {  }
	~CFileManager() { delete m_instance; }

public:
	void LoadFileWithPath(char* path);

private:
	static CFileManager* m_instance;
};