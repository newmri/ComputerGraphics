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

public:
	void SetPos(const Vector3 pos) { m_pos = pos; }
	void SetViewMatrix(float* view)
	{
		m_view = (Matrix4*)view;
		this->CalculateViewMatrix();
	}

public:
	Vector3& GetPos() { return m_pos; }
	Vector3& GetZ() { return m_z; }

public:
	Vector3 OnKeys(BYTE Keys, float frameTime);
	void OnMouseWheel(float zDelta);

public:
	void CalculateViewMatrix() { if (m_view) *m_view = GetViewMatrix(m_x, m_y, m_z, m_pos); }

public:
	void LookAt(Vector3 reference, Vector3 pos, bool rotateAroundReference);
	void OnMouseMove(int x, int y);
	void Move(Vector3 move);

private:
	static CCameraManager* m_instance;
	Vector3 m_rotate;
	float m_angle, m_angleIn;
	Vector3 m_x, m_y, m_z, m_pos, m_ref;
	Matrix4* m_view;
	int m_button;
	POINT m_lastCurPos;
};