#ifndef COBJECT_H
#define COBJECT_H

#include "Define.h"

class CObject
{
public:
	virtual void Init(OBJTYPE objType, MOVETYPE moveType, Pos pos) = 0;
	virtual void Update() = 0;
	virtual void Render() = 0;

public:
	const OBJTYPE& GetObjType() { return m_objType; }
	const MOVETYPE& GetMoveType() { return m_moveType; }
	const Pos& GetPos() { return m_pos; }
	const Color& GetColor() { return m_color; }

public:
	void SetPos(const Pos newPos) { m_pos = newPos; }
	void SetColor(const Color newColor) { m_color = newColor; }

public:
	float GetSize() { return m_size; }

public:
	void SetPath(OBJTYPE objType) {
		m_pathType = objType;
		if (objType == OBJTYPE::TORNADO) this->InitTornado(); 
		else if (objType == OBJTYPE::SINWAVE) m_pos.x = -0.75f;
	}

public:
	void Bounce()
	{
		m_size = (m_size < MAX_SIZE) ? MAX_SIZE : MIN_SIZE;
	}

public:
	void MoveWithCircle()
	{
		if (m_i < 360) m_i += m_speed;
		else m_i = 0.0f;

		m_angle = (m_i * PIE / 180);
		m_x = 2 * cos(m_angle);
		m_y = 2 * sin(m_angle);
		m_pos.x = (m_x + m_pos.x) / 5;
		m_pos.y = (m_y + m_pos.y) / 5;
	}
	void MoveWithSinWave()
	{
		if (m_pos.x < m_waveEnd) {
			m_pos.x += 0.01;
			m_theta += 0.4;
		}

		else {
			m_pos.x = -0.75f;
			m_theta = 0.0f;
		}

		m_pos.y = sin(m_theta) / 2.0f;
	}

	void MoveWithZigZag()
	{
		if (m_i < ZIAZAG_SLICE) ++m_i;
		else {
			m_i = 0;
			if (m_zigzagIdx < m_zigzagPos.size() - 2) m_zigzagIdx++;
			else m_zigzagIdx = 0;
		}
		float a = (m_zigzagPos[m_zigzagIdx + 1].y - m_zigzagPos[m_zigzagIdx].y)
			/ (m_zigzagPos[m_zigzagIdx + 1].x - m_zigzagPos[m_zigzagIdx].x);
		float b = m_zigzagPos[m_zigzagIdx].y - a * m_zigzagPos[m_zigzagIdx].x;

		float step = (m_zigzagPos[m_zigzagIdx + 1 ].x - m_zigzagPos[m_zigzagIdx].x) / ZIAZAG_SLICE;
		m_pos.x = m_zigzagPos[m_zigzagIdx].x + step * m_i;
		m_pos.y = (a * (m_zigzagPos[m_zigzagIdx].x + step * m_i)) + b;
		
	}

	void MoveWithTornado()
	{
		
		if (m_i < 360 * 7) {
			m_i += 10;
			m_angle = m_i * PIE / 180;
			m_pos.x = (cos(m_angle) / m_tornadoSize) + m_interval;
			m_pos.y = sin(m_angle) / m_tornadoSize;

			if ((int)m_i % 360 == 0 && m_i != 0) m_tornadoSize -= 0.5f;

			m_interval += 0.006f;

		}
		else this->InitTornado();
		

	}

	void InitTornado()
	{

		m_i = 0;
		m_tornadoSize = 7.0f;
		m_interval = 0;
		m_pos.x = 0;
		m_pos.y = 0;
	}
protected:
	OBJTYPE m_objType;
	MOVETYPE m_moveType;
	Color m_color;
	Pos m_pos, m_startPos, m_endPos;
	vector<Pos> m_zigzagPos;
	int m_zigzagIdx;
	float m_tornadoSize;
	float m_interval;
	float m_size, m_rad, m_x, m_y, m_angle;
	float m_i;
	DWORD m_bounceTime;
	float m_theta, m_waveEnd;
	OBJTYPE m_pathType;

	DATA_TYPE m_speed;
};

#endif