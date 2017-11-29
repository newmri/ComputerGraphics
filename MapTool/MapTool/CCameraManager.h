#pragma once

#include "Matrix.h"

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
	~CCameraManager() { delete m_instance; }

public:
	void Init();
	void Reset();
	void Update();

public:
	void SetPos(const Vector3 pos) { m_pos = pos; }
	void SetRotate(const unsigned char rotate);
	void SetMove(const unsigned char key);
	void SetViewMatrix(float* view)
	{
		m_view = (Matrix4*)view;
		this->CalculateViewMatrix();
	}
	void SetButton(int n, int x, int y);
	int GetButton() { return m_button; }

public:
	Vector3& GetPos() { return m_pos; }
	Vector3& GetZ() { return m_z; }

public:
	void CalculateViewMatrix() { if (m_view) *m_view = GetViewMatrix(m_x, m_y, m_z, m_pos); }

public:
	void Rotate();
	void Move();
	void Wheel(float z );
	void OnMouseMove(int x, int y);
private:
	static CCameraManager* m_instance;
	Vector3 m_rotate;
	float m_angle, m_angleIn;
	Vector3 m_x, m_y, m_z, m_pos, m_ref;
	Matrix4* m_view;
	int m_button;
	POINT m_lastCurPos;
};