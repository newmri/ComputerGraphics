#pragma once
#include <iostream>
#include <time.h>

using namespace std;

const  int INITROW = 3, INITCOL = 3;
const  int DETROW = 2, DETCOL = 2;

enum MATRIX_IDX { OP1, OP2, RESULT, NUM_OF_MATRIX };

template<typename DATATYPE>
class CMatrix
{
public:
	void DisplayMatrix() const;
	void Add();
	void Min();
	void Multi();
	DATATYPE Cal3by3Determinant() const;
	DATATYPE Cal3by3Determinant(DATATYPE(*mat)[INITROW]) const;
	DATATYPE Cal4by4Determinant() const;
	void DisplayDeterminant() const;
	void ChangeMatrix();
	DATATYPE*** Allocate();
	DATATYPE*** CopyValue(DATATYPE*** source);
	void Init(const int row, const int col);
	void Delete(DATATYPE*** mat, const int row, const int col);
	CMatrix() { this->Init(INITROW, INITCOL); }
	~CMatrix() { this->Delete(m_mat, m_row, m_col); }
private:
	int m_row, m_col;
	DATATYPE*** m_mat;

};