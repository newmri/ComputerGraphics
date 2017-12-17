#ifndef __VECTOR_H_
#define __VECTOR_H_

#ifdef __cplusplus
extern "C"
{
#endif

#ifdef _COMPLING_DLL_VECTOR
#define LIBSPEC __declspec(dllexport)
#else
#define LIBSPEC __declspec(dllimport)
#endif
	struct Vector3
	{
		float x, y, z;

		Vector3(){ x = 0.0, y = 0.0, z = 0.0; }
		Vector3(float x, float y, float z) : x(x), y(y), z(z) {};
		~Vector3() {};

		Vector3 operator+(const Vector3& other)
		{
			return Vector3(x + other.x, y + other.y, z + other.z);
		}
		void operator+=(const Vector3& other)
		{
			x += other.x;
			y += other.y;
			z += other.z;
		}
		
		Vector3 operator-(const Vector3& other)
		{
			return Vector3(x - other.x, y - other.y, z - other.z);
		}

		void operator-=(const Vector3& other)
		{
			x -= other.x;
			y -= other.y;
			z -= other.z;
		}

		Vector3 operator* (float num)
		{
			return Vector3(x * num, y * num, z * num); 
		}

		void operator*= (float num)
		{
			x *= num;
			y *= num;
			z *= num;
		}

		float operator[](const int i) const
		{
			if (i == 0) return x;
			else if (i == 1) return y;
			else if (i == 2) return z;
			else return -1;

		}
		float Len() const
		{
			float fret{ 1 };
			float ret = ((x * x) + (y * y) + (z * z));
			for (int i = 0; i < 10; ++i) fret = 0.5 * ( (fret) + (ret / fret) );

			return fret;
		}
	};
	LIBSPEC void Normalize3f(Vector3& dest, const Vector3& source);
	LIBSPEC float Dot3f(const Vector3& v1, const Vector3& v2);
	LIBSPEC void Cross3f(Vector3& dest, const Vector3& v1, const Vector3& v2);

	struct Vector4
	{
		float x, y, z, w;

		Vector4() { x = 0.0, y = 0.0, z = 0.0, w = 0.0; }
		Vector4(const Vector3 &u, float w) : x(u.x), y(u.y), z(u.z), w(w) {}
		Vector4(float x, float y, float z, float w) : x(x), y(y), z(z), w(w){};
		~Vector4() {};

		Vector4 operator+(const Vector4& other)
		{
			return Vector4(x + other.x, y + other.y, z + other.z, w + other.w);
		}
		Vector4 operator-(const Vector4& other)
		{
			return Vector4(x - other.x, y - other.y, z - other.z, w - other.w);
		}
		Vector3 operator-(const Vector3& other)
		{
			return Vector3(x - other.x, y - other.y, z - other.z);
		}
		LIBSPEC Vector4& operator/= (float num) { x /= num; y /= num; z /= num; w /= num; return *this; }
		LIBSPEC Vector4& operator/= (const Vector4& u) { x /= u.x; y /= u.y; z /= u.z; w /= u.w; return *this; }

		float Len() const
		{
			float fret{ 1 };
			float ret = ((x * x) + (y * y) + (z * z) + (w * w));
			for (int i = 0; i < 10; ++i) fret = 0.5 * ((fret)+(ret / fret));

			return fret;
		}
	};

	LIBSPEC void Normalize4f(Vector4& dest, const Vector4& source);
	LIBSPEC float Dot4f(const Vector4& v1, const Vector4& v2);

#ifdef __cplusplus
}
#endif
#endif

