#ifndef COBJECT_H
#define COBJECT_H

#include "Define.h"

class CObject
{
public:
	void Init(int idx);
	void Update();
	void Render();

public:
	const Vector3& GetPos() { return m_pos; }
	const bool& GetCreateNew() { return m_createNew; }
	void ReSetCreateNew() { m_createNew = false; }

public:
	void SetPos(const Vector3 newPos) { m_pos = newPos; }
	void SetRotation(const Vector3 newRotation) { m_rotation = newRotation; }

	void Rotate()
	{
		if (m_angle < 360.0f) m_angle += 10.0f;
		else m_angle = 0.0f;

		m_dPos.x = 8 * cos(m_angle * PIE / 180);
		m_dPos.z = 8 * sin(m_angle * PIE / 180);

	}

	void Move()
	{
		if (!m_createNew) {
			if (m_pos.y > -21.6666f + ((4.0f + 4.0 / 36.0) * m_idx)) m_pos.y -= 4.0 / 36.0;
			else {
				m_createNew = true;
				m_haveToRotate = false;
			}

		}
		
	}



private:
	Vector3 m_pos, m_rotation;
	Vector3 m_dPos;
	float m_angle;
	bool m_haveToRotate;
	bool m_createNew;
	int m_idx;
};

#endif