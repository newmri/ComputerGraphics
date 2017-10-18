#pragma once

#include <vector>

struct Flags
{
	unsigned int top : 1;
	unsigned int bottom : 1;
	unsigned int right : 1;
	unsigned int left : 1;

	bool operator& (const Flags& other)
	{
	
		if ((top == 0 && bottom == 0 && left == 0 && right == 0) ||
			(other.top == 0 && other.bottom == 0 && other.left == 0 && other.right == 0)) return true; // Line is in mid

		else return false;
		Flags flag;
		flag.top = top & other.top;
		flag.bottom = bottom & other.bottom;
		flag.left = left & other.left;
		flag.right = right & other.right;

		//if (flag.top == 0 && flag.bottom == 0 && flag.left == 0 && flag.right == 0)
		
	}

};

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
	static void MouseClick(const int button, const int state, const int x, const int y);
	static void MouseClickMove(const int x, const int y);
	static void MouseMove(const int x, const int y);

public:
	static void ConvertDeviceToOpenGL(const int x, const int y, Vector2& pos);

public:
	const bool HaveSomethingToClip();

public:
	void SetPos(const Vector2 pos) { m_pos = pos; }

public:
	Vector2& GetPos() { return m_pos; }
	std::vector<Vector2>& GetPosList() { return m_posV; }

private:
	static CMouseManager* m_instance;
	static std::vector<Vector2> m_posV;
	static bool m_isLeftOn;

private:
	Vector2 m_pos;
	Flags m_flag[2];
};