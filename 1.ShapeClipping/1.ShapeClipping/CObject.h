#pragma once

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

class CObject
{

public:
	virtual void Init() = 0;
	virtual void Update() = 0;
	virtual void Render() = 0;

public:
	void SetPos(const Vector3 pos) { m_pos = pos; }

public:
	const Vector3& GetPos() { return m_pos; }

protected:
	Vector3 m_pos;
	float m_size;
};