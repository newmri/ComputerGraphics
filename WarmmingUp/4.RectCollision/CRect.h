#pragma once

#include <iostream>
using namespace std;

typedef int DATA_TYPE;

const DATA_TYPE SPEED = 60;

enum MOVE { LEFT = -1, RIGHT = 1, UP = 2, DOWN = -2 };

template<typename DATATYPE>
struct Pos
{
	DATATYPE left, top, bottom, right;
	Pos()
	{
		left = 0;
		top = 0;
		bottom = 0;
		right = 0;
	}
};

template<typename DATATYPE>
class CRect
{
public:
	friend ostream& operator<<(ostream &os, const CRect& rect)
	{
		os << "(" << rect.GetPos().left << ", " << rect.GetPos().top << ") "
			<< "(" << rect.GetPos().right << ", " << rect.GetPos().bottom << ")" <<endl;
		return os;
	}

	friend CRect operator>>(istream &is, CRect& rect)
	{
		Pos<DATA_TYPE> pos;
		is >> pos.left >> pos.top >> pos.right >> pos.bottom;

		rect.SetPos(pos);

		return rect;
	}

public:
	void Move(MOVE dir)
	{
		switch (dir) {
		case MOVE::LEFT:
		case MOVE::RIGHT:
			m_pos.left += dir * m_speed;
			m_pos.right += dir * m_speed;
			break;
		case MOVE::UP:
		case MOVE::DOWN:
			m_pos.top += dir * (m_speed / 2);
			m_pos.bottom += dir * (m_speed / 2);
			break;

		}
	}
	bool CheckCollision(const CRect& other)
	{
		if ((m_pos.top < other.GetPos().bottom && m_pos.bottom > other.GetPos().top)
			&& (m_pos.left < other.GetPos().right && m_pos.right > other.GetPos().left)) return true;
		else return false;
	}

public:
	Pos<DATATYPE> GetPos() const { return m_pos; }
	DATATYPE GetY() const { return m_rect[1]; }

public:
	void SetPos(const Pos<DATATYPE> pos) { m_pos = pos; }

public:
	CRect() { m_speed = SPEED; }

private:
	Pos<DATATYPE> m_pos;
	DATATYPE m_speed;
};