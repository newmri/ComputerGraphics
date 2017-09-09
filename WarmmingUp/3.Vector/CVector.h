#pragma once

#include <iostream>
using namespace std;

typedef int DATA_TYPE;
const int VECTORSIZE = 3;

template<typename DATATYPE>
class CVector
{
public:
	CVector operator+(const CVector& other) const
	{
		CVector<DATATYPE> vector;
		vector.SetX(m_vector[0] + other.GetX());
		vector.SetY(m_vector[1] + other.GetY());
		vector.SetZ(m_vector[2] + other.GetZ());

		return vector;
	}

	CVector operator-(const CVector& other) const
	{
		CVector<DATATYPE> vector;
		vector.SetX(m_vector[0] - other.GetX());
		vector.SetY(m_vector[1] - other.GetY());
		vector.SetZ(m_vector[2] - other.GetZ());

		return vector;
	}

	CVector operator*(const CVector& other) const
	{
		CVector<DATATYPE> vector;
		vector.SetX(m_vector[1] * other.GetZ() - m_vector[2] * other.GetY());
		vector.SetY(m_vector[2] * other.GetX() - m_vector[0] * other.GetZ());
		vector.SetZ(m_vector[0] * other.GetY() - m_vector[1] * other.GetX());

		return vector;
	}

	friend ostream& operator<<(ostream &os, const CVector& vector)
	{
		os << "(" << vector.GetX() << ", " << vector.GetY() << ", " << vector.GetZ() << ")";
		return os;
	}

	friend CVector operator>>(istream &is, CVector& vector)
	{
		DATATYPE v[3];
		is >> v[0] >> v[1] >> v[2];

		vector.SetX(v[0]);
		vector.SetY(v[1]);
		vector.SetZ(v[2]);

		return vector;
	}

public:
	DATATYPE CalScalarProduct(const CVector& other) const
	{
		DATATYPE data{};
		data = (m_vector[0] * other.GetX()) + (m_vector[1] * other.GetY()) + (m_vector[2] * other.GetZ());

		return data;
	}

	const int GetLength() const
	{
		int ret{};
		for (int i = 0; i < VECTORSIZE; ++i) ret += m_vector[i] * m_vector[i];

		return ret;
	}

public:
	DATATYPE GetX() const { return m_vector[0]; };
	DATATYPE GetY() const { return m_vector[1]; };
	DATATYPE GetZ() const { return m_vector[2]; };

public:
	void SetX(const DATATYPE x) { m_vector[0] = x; };
	void SetY(const DATATYPE y) { m_vector[1] = y; };
	void SetZ(const DATATYPE z) { m_vector[2] = z; };

public:
	CVector() { memset(&m_vector, 0, sizeof(m_vector)); };
	CVector(const DATATYPE x, const DATATYPE y, const DATATYPE z)
	{
		m_vector[0] = x;
		m_vector[1] = y;
		m_vector[2] = z;
	}

private:
	DATATYPE m_vector[VECTORSIZE];

};


