#pragma once


class CMouseManager
{
public:
	static CMouseManager* GetInstance()
	{
		if (m_instance == nullptr)
			m_instance = new CMouseManager;

		return m_instance;
	}

public:
	void Init();
	void Update();

public:
	void SetPos(const Vector2 pos) { m_pos = pos; }

public:
	Vector2& GetPos() { return m_pos; }

private:
	static CMouseManager* m_instance;
	Vector2 m_pos;
};