#ifndef COBJECT_H
#define COBJECT_H

#include "Define.h"

class CObject
{
public:
	void Init(OBJTYPE objType, Vector3 pos, Vector3 scale, DATA_TYPE size, Color color)
	{
		m_objType = objType;
		m_pos = pos;
		m_size = size;
		m_bodyColor = color;
		m_scale = scale;
	}
	void Init(OBJTYPE objType, Vector3 pos, Vector3 scale, DATA_TYPE size, Color bodycolor, Color leafcolor)
	{
		m_objType = objType;
		m_pos = pos;
		m_size = size;
		m_bodyColor = bodycolor;
		m_leafColor = leafcolor;
		m_scale = scale;
	}
	virtual void Init() = 0;
	virtual void Update() = 0;
	virtual void Render() = 0;

public:
	const OBJTYPE& GetObjType() { return m_objType; }
	const Vector3& GetPos() { return m_pos; }
	const Color& GetBodyColor() { return m_bodyColor; }

public:
	void SetPos(const Vector3 newPos) { m_pos = newPos; }
	void SetBodyColor(const Color newColor) { m_bodyColor = newColor; }
	void SetRotation(const Vector3 newRotation) { m_rotation = newRotation; }

	void Rotate()
	{
		if (m_angle < 360.0f) m_angle += BALL_ROTATION_SPEED;
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
	bool CheckCollision(CObject* other)
	{
		Vector3 v1(m_pos.x - other->GetPos().x, m_pos.z - other->GetPos().z, 0.0f);

		Vector3 v[4];
		v[0].x = m_pos.x - m_size;
		v[0].y = m_pos.z;
		v[1].x = m_pos.x + m_size;
		v[1].y = m_pos.z;
		v[2].x = m_pos.x;
		v[2].y = m_pos.z + m_size;
		v[3].x = m_pos.x;
		v[3].y = m_pos.z - m_size;

		float dist = sqrtf((v1.x * v1.x) + (v1.y * v1.y));
		if (dist < m_size + other->GetSize()) return true;
		for (int i = 0; i < 4; ++i) {
			if (other->GetPos().x - other->GetSize() < v[i].x &&  other->GetPos().x + other->GetSize() > v[i].x &&
				other->GetPos().z - other->GetSize() < v[i].y && other->GetPos().z + other->GetSize() < v[i].y) {
				return true;
			}
		}
		return false;
	}

protected:
	OBJTYPE m_objType;
	Color m_bodyColor, m_leafColor;
	Vector3 m_pos, m_scale, m_rotation;
	DATA_TYPE m_size;
	float m_angle;
};

#endif