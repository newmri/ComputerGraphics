#pragma once

struct Vector2
{
	float x, y;

	Vector2()
	{
		x = 0.0f, y = 0.0f;
	}

};

class CObject
{

public:
	virtual void Init() = 0;
	virtual void Update() = 0;

public:
	void SetPos(const Vector2 pos) { m_pos = pos; }

public:
	const Vector2& GetPos() { return m_pos; }

protected:
	Vector2 m_pos;
};