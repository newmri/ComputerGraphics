#ifndef __MATRIX_H_
#define __MATRIX_H_

#ifdef __cplusplus
extern "C"
{
#endif

#ifdef _COMPLING_DLL_MATRIX
#define LIBSPEC __declspec(dllexport)
#else
#define LIBSPEC __declspec(dllimport)
#endif
#include <math.h>
#include "Vector.h"
#define PIE       3.14159265358979323846
	struct Matrix4
	{
		float matrix[16];
		float identity[16] =
		{
			1.0, 0.0, 0.0, 0.0,
			0.0, 1.0, 0.0, 0.0,
			0.0, 0.0, 1.0, 0.0,
			0.0, 0.0, 0.0, 1.0
		};

		LIBSPEC Matrix4();
		LIBSPEC Matrix4(const Matrix4& m);
		LIBSPEC Matrix4(float* m);
		LIBSPEC Matrix4(double* m);
		~Matrix4() {}

		Vector3 operator*(const Vector3& v)
		{
			float  prod[4] = { 0,0,0,0 };
			for (int r = 0; r < 4; r++) {
				for (int c = 0; c < 3; ++c) prod[r] += v[c] * get(c, r);
				prod[r] += get(3, r);
			}

			float div = 1.0 / prod[3];

			return Vector3(prod[0] * div, prod[1] * div, prod[2] * div);
		}

		
		Vector4 operator*(const Vector4& v)
		{
			return Vector4(
				(v.x * get(0, 0)) + (v.y * get(1, 0)) + (v.z * get(2, 0)) + (v.w * get(3, 0)),
				(v.x * get(0, 1)) + (v.y * get(1, 1)) + (v.z * get(2, 1)) + (v.w * get(3, 1)),
				(v.x * get(0, 2)) + (v.y * get(1, 2)) + (v.z * get(2, 2)) + (v.w * get(3, 2)),
				(v.x * get(0, 3)) + (v.y * get(1, 3)) + (v.z * get(2, 3)) + (v.w * get(3, 3)));
		}
		
		float& operator[](const int index)
		{
			float ret = -1;
			if (index > 15) return ret;
			return matrix[index];
		}

		float* operator& ()
		{
			return (float*)this;
		}

		LIBSPEC void Reset();
		LIBSPEC void Identity();

		LIBSPEC Matrix4 Inverse();
		LIBSPEC void InvertMatrixGeneral(const float* m, float* out);
		LIBSPEC void InvertMatrix(const float* m, float* out);

		LIBSPEC void set(const int col, const int row, const double val) { matrix[col * 4 + row] = val; }
		LIBSPEC float get(const int col, const int row) const { return matrix[col * 4 + row]; }
		LIBSPEC float& element(const int col, const int row) { return matrix[col * 4 + row]; }
		LIBSPEC Vector4 GetRow(int row);
		LIBSPEC void GetAngle(Vector3& rotate);

	};
	LIBSPEC Matrix4 operator*(Matrix4& mat1, Matrix4& mat2);
	LIBSPEC Matrix4 GetBiasMatrix();
	LIBSPEC Matrix4 GetBiasMatrixInverse();
	LIBSPEC Matrix4 GetViewMatrix(const Vector3& x, const Vector3& y, const Vector3& z, const Vector3& pos);
	LIBSPEC Matrix4 GetViewMatrixInverse(Matrix4 &V);
	LIBSPEC Matrix4 GetPerspectiveProjectionMatrix(float fovy, float x, float y, float n, float f);
	LIBSPEC Matrix4 GetPerspectiveProjectionMatrixInverse(Matrix4 &pp);
	LIBSPEC Matrix4 RotationMatrix(float angle, const Vector3 &u);
	LIBSPEC Vector3 RotateVector(const Vector3& u, float angle, const Vector3& v);
#ifdef __cplusplus
}
#endif
#endif

