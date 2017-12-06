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
public:
	void SetButton(int button, int x, int y);
	void OnMouseMove(int x, int y);
	bool IsOnRightMouse() { return (m_button == GLUT_RIGHT_BUTTON); }
	Vector3 GetLastPos() { return m_lastPos; }
	void SetLastPos(int x, int y) { m_lastPos.x = x, m_lastPos.y = y; }

public:
	void SwapLook();
	void LookAt(Vector3 reference, Vector3 pos, bool rotateAroundReference);
	void CalculateViewMatrix() { if (m_view) *m_view = GetViewMatrix(m_x, m_y, m_z, m_pos); }
public:
	Vector3& GetPos() { return m_pos; }

public:
	void Rotate();
	void Move();
private:
	static CCameraManager* m_instance;
	Matrix4* m_view;
	Vector3 m_rotate;
	Vector3 target;
	float m_angle, m_angleIn;
	Vector3 m_pos, m_ref, m_lastPos;
	Vector3 m_x, m_y, m_z;
	float theta;
	float phi;
	int m_button;
};