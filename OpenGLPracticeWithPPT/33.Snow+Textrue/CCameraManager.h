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
	void SetNormalize(bool num) { m_normalize = num; }

public:
	Vector3& GetPos() { return m_pos; }
	bool DoRotateLight() { return m_rotateLight; }
	bool DoNormalize() { return m_normalize; }
public:
	void Rotate();
	void Move();
private:
	static CCameraManager* m_instance;
	Vector3 m_rotate;
	float m_angle, m_angleIn;
	Vector3 m_pos;
	bool m_animation;
	int m_animationCnt;
	bool m_rotateLight;
	bool m_normalize;
};