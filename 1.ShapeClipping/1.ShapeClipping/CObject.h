#pragma once

#include "Enum.h"

struct Vector3
{
	float x, y, z;

	Vector3()
	{
		x = 0.0f, y = 0.0f, z = 0.0f;
	}

};

struct Vector2
{
	float x, y;

	Vector2()
	{
		x = 0.0f, y = 0.0f;
	}

};



struct Color
{
	float r, g, b, a;
	Color()
	{
		r = 1.0f, g = 1.0f, b = 1.0f, a = 1.0f;
	}
};

class CObject
{

public:
	virtual void Init() = 0;
	virtual void Update() = 0;
	virtual void Render() = 0;

public:
	void SetPos(const Vector2 pos) { m_pos = pos; }
	void ChangeDirection() { m_vX = -m_vX; }
public:
	const Vector2& GetPos() { return m_pos; }
	const float GetLeftPos() { return m_pos.x - (m_size / 2.0f); }
	const float GetRightPos() { return m_pos.x + (m_size / 2.0f); }
	const float GetTopPos() { return m_pos.y + (m_size / 2.0f); }
	const float GetBottomPos() { return m_pos.y - (m_size / 2.0f); }
	const float& GetDirection() { return m_vX; }
	const float& GetSize() { return m_size; }
protected:
	Vector2 m_pos;
	Color m_color;
	float m_size;
	float m_vX;
};