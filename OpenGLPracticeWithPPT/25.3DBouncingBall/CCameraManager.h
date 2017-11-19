#pragma once

struct Vector3
{
	float x, y, z;
	Vector3()
	{
		x = 0.0f, y = 0.0f, z = 0.0f;
	}

	Vector3(float x, float y, float z) : x(x), y(y), z(z) {};
	Vector3(float x, float y) : x(x), y(y) {};

	Vector3 operator-(const Vector3& other)
	{
		return Vector3(x - other.x, y - other.y, z - other.z);
	}

	void operator+=(const Vector3& other)
	{
		x += other.x;
		y += other.y;
		z += other.z;
	}
	void Normalize()
	{
		x = x / this->GetLength();
		y = y / this->GetLength();
	    z = z / this->GetLength();
	}

	Vector3 GetNormalized()
	{
		return Vector3(x / this->GetLength(), y / this->GetLength(), z / this->GetLength());
	}

	float GetDot(const Vector3& other)
	{
		return (x * other.x) + (y * other.y) + (z * other.z);
	}

	Vector3 GetCross(const Vector3& other)
	{
		return Vector3((y * other.z - other.y * z), (z*other.x - other.z - x), (x * other.y - other.x * y));
	}

	double GetLength()
	{
		return sqrt((x * x) + (y * y) + (z * z));
	}

};

class CCameraManager
{
public:
	static CCameraManager* GetInstance()
	{
		if (m_instance == nullptr)
			m_instance = new CCameraManager;

		return m_instance;
	}

	CCameraManager() { this->Init(); }

public:
	void Init();
	void Reset();
	void Update();

public:
	void SetPos(const Vector3 pos) { m_pos = pos; }
	void SetRotate(const unsigned char rotate);
	void SetMove(const unsigned char key);

public:
	Vector3& GetPos() { return m_pos; }
	float GetAngle() { return m_angle; }
	float GetIncre() { return m_angleIn; }
public:
	bool IsRotatingToCCW() { return (m_angleIn > 0.0f); }
public:
	void Rotate();
	void Move();
private:
	static CCameraManager* m_instance;
	Vector3 m_rotate;
	float m_angle, m_angleIn;
	Vector3 m_pos;
};