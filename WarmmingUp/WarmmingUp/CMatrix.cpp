#include <Windows.h>
#include "CMatrix.h"



template<typename DATATYPE>
void CMatrix<DATATYPE>::DisplayMatrix() const
{
	for (int i = 0; i < MATRIX_IDX::NUM_OF_MATRIX; ++i) {
		for (int j = 0; j < m_row; ++j) {
			if(i == MATRIX_IDX::OP1 + 1) cout << "\t";
			else if(i == MATRIX_IDX::OP2 + 1) cout << "\t\t";
			cout << "|";
			for (int k = 0; k < m_col; ++k) {
				cout << " " << m_mat[i][j][k];
			}
			cout << " |"<<endl;

		}
	}
				
}

template<typename DATATYPE>
void CMatrix<DATATYPE>::Add()
{
	for (int j = 0; j < m_row; ++j) {
		for (int k = 0; k < m_col; ++k) {
			m_mat[MATRIX_IDX::RESULT][j][k] = m_mat[MATRIX_IDX::OP1][j][k] + m_mat[MATRIX_IDX::OP2][j][k];
		}
	}

	this->DisplayMatrix();
}

template<typename DATATYPE>
void CMatrix<DATATYPE>::Min()
{
	for (int j = 0; j < m_row; ++j) {
		for (int k = 0; k < m_col; ++k) {
			m_mat[MATRIX_IDX::RESULT][j][k] = m_mat[MATRIX_IDX::OP1][j][k] - m_mat[MATRIX_IDX::OP2][j][k];
		}
	}

	this->DisplayMatrix();

}

template<typename DATATYPE>
void CMatrix<DATATYPE>::Multi()
{
	for (int i = 0; i < m_row; ++i) {
		for (int j = 0; j < m_col; ++j) {
			for (int k = 0; k < m_col; ++k) {
				m_mat[MATRIX_IDX::RESULT][i][j] += m_mat[MATRIX_IDX::OP1][i][k] * m_mat[MATRIX_IDX::OP2][k][j];

			}
		}
	}

	this->DisplayMatrix();
}

template<typename DATATYPE>
DATATYPE CMatrix<DATATYPE>::Cal3by3Determinant() const
{
	DATATYPE tempMat[DETROW][DETCOL]{};
	DATATYPE result{};
	for (int i = 0; i < INITCOL; ++i) {
		if (m_mat[MATRIX_IDX::OP1][0][i] != 0) {
			switch (i) {
			case 0:
				tempMat[0][0] = m_mat[MATRIX_IDX::OP1][1][1];
				tempMat[0][1] = m_mat[MATRIX_IDX::OP1][1][2];
				tempMat[1][0] = m_mat[MATRIX_IDX::OP1][2][1];
				tempMat[1][1] = m_mat[MATRIX_IDX::OP1][2][2];
				break;
			case 1:
				tempMat[0][0] = m_mat[MATRIX_IDX::OP1][1][0];
				tempMat[0][1] = m_mat[MATRIX_IDX::OP1][1][2];
				tempMat[1][0] = m_mat[MATRIX_IDX::OP1][2][0];
				tempMat[1][1] = m_mat[MATRIX_IDX::OP1][2][2];
				break;
			case 2:
				tempMat[0][0] = m_mat[MATRIX_IDX::OP1][1][0];
				tempMat[0][1] = m_mat[MATRIX_IDX::OP1][1][1];
				tempMat[1][0] = m_mat[MATRIX_IDX::OP1][2][0];
				tempMat[1][1] = m_mat[MATRIX_IDX::OP1][2][1];
				break;
			}

			if (i % 2 == 0) result += ((tempMat[0][0] * tempMat[1][1] - tempMat[0][1] * tempMat[1][0]) * m_mat[MATRIX_IDX::OP1][0][i]);
			else result += ((tempMat[0][0] * tempMat[1][1] - tempMat[0][1] * tempMat[1][0]) * m_mat[MATRIX_IDX::OP1][0][i]) * -1;

		}

	}

	return result;
}

template<typename DATATYPE>
DATATYPE CMatrix<DATATYPE>::Cal3by3Determinant(DATATYPE(*mat)[INITROW]) const
{
	DATATYPE tempMat[DETROW][DETCOL]{};
	DATATYPE result{};
	for (int i = 0; i < INITCOL; ++i) {
		if (m_mat[0][i] != 0) {
			switch (i) {
			case 0:
				tempMat[0][0] = mat[1][1];
				tempMat[0][1] = mat[1][2];
				tempMat[1][0] = mat[2][1];
				tempMat[1][1] = mat[2][2];
				break;
			case 1:
				tempMat[0][0] = mat[1][0];
				tempMat[0][1] = mat[1][2];
				tempMat[1][0] = mat[2][0];
				tempMat[1][1] = mat[2][2];
				break;
			case 2:
				tempMat[0][0] = mat[1][0];
				tempMat[0][1] = mat[1][1];
				tempMat[1][0] = mat[2][0];
				tempMat[1][1] = mat[2][1];
				break;
			}

			if (i % 2 == 0) result += ((tempMat[0][0] * tempMat[1][1] - tempMat[0][1] * tempMat[1][0]) * mat[0][i]);
			else result += ((tempMat[0][0] * tempMat[1][1] - tempMat[0][1] * tempMat[1][0]) * mat[0][i]) * -1;

		}

	}

	return result;
}

template<typename DATATYPE>
DATATYPE CMatrix<DATATYPE>::Cal4by4Determinant() const
{
	DATATYPE mat[INITROW][INITCOL]{};
	DATATYPE result{};
	for (int i = 0; i < m_col; ++i) {
		switch (i) {
		case 0:
			for (int j = 0; j < INITROW; ++j) {
				for (int k = 0; k < INITCOL; ++k)
					mat[j][k] = m_mat[MATRIX_IDX::OP1][j + 1][k + 1];
			}
			break;
		case 1:
			for (int j = 0; j < INITROW; ++j) {
				for (int k = 0; k < INITCOL; ++k) {
					if (k == 0) mat[j][k] = m_mat[MATRIX_IDX::OP1][j + 1][k];
					else mat[j][k] = m_mat[MATRIX_IDX::OP1][j + 1][k + 1];
				}
			}
			break;
		case 2:
			for (int j = 0; j < INITROW; ++j) {
				for (int k = 0; k < INITCOL; ++k) {
					if (k == INITCOL - 1) mat[j][k] = m_mat[MATRIX_IDX::OP1][j + 1][k];
					else mat[j][k] = m_mat[MATRIX_IDX::OP1][j + 1][k + 1];
				}
			}
			break;
		case 3:
			for (int j = 1; j < INITROW; ++j) {
				for (int k = 0; k < INITCOL; ++k)
					mat[j][k] = m_mat[MATRIX_IDX::OP1][j][k];
			}
			break;
		}
		if (i % 2 == 0) result += Cal3by3Determinant(mat);
		else result += Cal3by3Determinant(mat) * -1;
	}
	return result;
}

template<typename DATATYPE>
void CMatrix<DATATYPE>::DisplayDeterminant() const
{
	for (int i = 0; i < m_row; ++i) {
		cout << "|";
		for (int j = 0; j < m_col; ++j) {
			cout << " " << m_mat[MATRIX_IDX::OP1][i][j];
		}
		cout << " |" << endl;
	}

	DATATYPE result{};

	if (m_row == INITCOL) result = Cal3by3Determinant();
	else if(m_row == INITCOL + 1) result = Cal4by4Determinant();
	else cout << "Error" << endl;

	cout <<"DET = "<< result << endl;
}

template<typename DATATYPE>
void CMatrix<DATATYPE>::ChangeMatrix()
{
	DATATYPE*** backMat = this->CopyValue(m_mat);

	this->Delete(m_mat, m_row, m_col);

	this->Init(4, 4);
	
	for (int i = 0; i < MATRIX_IDX::RESULT; ++i) {
		for (int j = 0; j < m_row - 1; ++j) {
			for (int k = 0; k < m_col - 1; ++k) m_mat[i][j][k] = backMat[i][j][k];
		}

		for (int j = 0; j < m_col - 1; ++j) {
			m_mat[i][m_row - 1][j] = 0;
			m_mat[i][j][m_col - 1] = 0;
		}

		m_mat[i][m_row - 1][m_col - 1] = 1;

	}
	
	this->Delete(backMat, INITROW, INITCOL);
	this->DisplayMatrix();

}

template<typename DATATYPE>
// Allocate memory
DATATYPE*** CMatrix<DATATYPE>::Allocate()
{
	DATATYPE*** mat;
	mat = new DATATYPE**[MATRIX_IDX::NUM_OF_MATRIX];

	for (int i = 0; i < MATRIX_IDX::NUM_OF_MATRIX; ++i) {
		mat[i] = new DATATYPE*[m_row];
		for (int j = 0; j < m_row; ++j) mat[i][j] = new DATATYPE[m_col];
	}

	return mat;
}

template<typename DATATYPE>
DATATYPE*** CMatrix<DATATYPE>::CopyValue(DATATYPE*** source)
{
	DATATYPE*** target = this->Allocate();

	for (int i = 0; i < MATRIX_IDX::RESULT; ++i) {
		for (int j = 0; j < m_row; ++j) {
			for (int k = 0; k < m_col; ++k) {
				target[i][j][k] = source[i][j][k];
			}

		}
	}

	return target;
}

template<typename DATATYPE>
// Set row, col
void CMatrix<DATATYPE>::Init(const int row, const int col)
{
	m_row = row;
	m_col = col;
	m_mat = this->Allocate();

	srand((unsigned)time(NULL));

	for (int i = 0; i < MATRIX_IDX::RESULT; ++i) {
		for (int j = 0; j < m_row; ++j) {
			for (int k = 0; k < m_col; ++k) {
				m_mat[i][j][k] = (rand() % 5);
			}

		}
	}

	for (int i = 0; i < m_row; ++i) {
		for (int j = 0; j < m_col; ++j) {
			m_mat[MATRIX_IDX::RESULT][i][j] = 0;
		}
	}

}

template<typename DATATYPE>
// Delete allocated memory
void CMatrix<DATATYPE>::Delete(DATATYPE*** mat, const int row, const int col)
{
	for (int i = 0; i < row; ++i) {
		for (int j = 0; j < col; ++j) {
			delete[] mat[i][j];
		}
	}

	for (int i = 0; i < MATRIX_IDX::NUM_OF_MATRIX; ++i) delete[] mat[i];
	delete[] mat;

}

