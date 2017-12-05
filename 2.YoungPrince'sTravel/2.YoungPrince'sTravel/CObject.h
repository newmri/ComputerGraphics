#pragma once

#include "Define.h"

class CObject
{
public:
	void Init(OBJTYPE objType, Vector3 pos, DATA_TYPE size, Color color)
	{
		m_objType = objType;
		m_pos = pos;
		m_size = size;
		m_color = color;
		m_angle = 0.0f;
		m_rotate = false;
	}



	virtual void Init() = 0;
	virtual void Update() = 0;
	virtual void Render() = 0;

public:
	const OBJTYPE& GetObjType() { return m_objType; }
	const Vector3& GetPos() { return m_pos; }
	const Color& GetColor() { return m_color; }

public:
	void SetPos(const Vector3 newPos) { m_pos = newPos; }
	void SetColor(const Color newColor) { m_color = newColor; }
	void SetRotation(const Vector3 newRotation) { m_rotation = newRotation; }

	void Rotate()
	{
		if (m_angle < 360.0f) m_angle += 0.02f;
		else m_angle = 0.0f;

	}

	void ChangeSizeBigger()
	{
		m_size += 0.001f;
		glScalef(m_size, m_size, m_size);
	}
public:
	float GetSize() { return m_size; }


public:

protected:
	OBJTYPE m_objType;
	Color m_color;
	Vector3 m_pos, m_scale, m_rotation;
	DATA_TYPE m_size;
	float m_angle;
	bool m_rotate;

};
