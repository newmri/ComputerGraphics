#pragma once

#include <iostream>
using namespace std;

typedef int DATA_TYPE;

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
	bool CheckCollision(const CRect& other)
	{


	}

public:
	Pos<DATATYPE> GetPos() const { return m_pos; }
	DATATYPE GetY() const { return m_rect[1]; }

public:
	void SetPos(const Pos<DATATYPE> pos) { /*m_pos = pos;*/ }

private:
	Pos<DATATYPE> m_pos;
};