#ifndef COBJECT_H
#define COBJECT_H

#include "Define.h"

class CObject
{
public:

	void Init(OBJECT_TYPE objType)
	{
		m_objType = objType;
		m_angle = 0.0f;
	}

	void CheckCollision()
	{
		// Left And Right
		if (m_pos.x + m_size >= CUBE_RAD || m_pos.x + m_size <= -CUBE_RAD) 
			m_vPos.x = -m_vPos.x;

		// Top And Bottom
		if (m_pos.y + m_size >= CUBE_RAD || m_pos.y + m_size <= -CUBE_RAD)
			m_vPos.y = -m_vPos.y;

		// In And Out
		if (m_pos.z + m_size >= CUBE_RAD || m_pos.z + m_size <= -CUBE_RAD)
			m_vPos.z = -m_vPos.z;
		
	}

public:
	virtual void Init() = 0;
	virtual void Move() = 0;
	virtual void Update() = 0;
	virtual void Render() = 0;

public:
	const Vector3& GetPos() { return m_pos; }


public:
	void SetPos(const Vector3 newPos) { m_pos = newPos; }
	void SetRotation(const Vector3 newRotation) { m_rotation = newRotation; }
	void SetSize(float size) { m_size = size; }
	void Rotate()
	{
		if (m_angle < 360.0f) m_angle += 10.0f;
		else m_angle = 0.0f;

	}


protected:
	OBJECT_TYPE m_objType;
	Vector3 m_pos, m_rotation;
	Vector3 m_vPos;
	float m_angle;
	float m_size;
};

#endif