#include "Define.h"

CCameraManager* CCameraManager::m_instance = nullptr;


void CCameraManager::Init()
{
	m_angle = 0.0f;
	m_angleIn = CAMERA_ANGLE_IN;
	m_view = nullptr;
	m_x.x = 1.0f;
	m_y.y = 1.0f;
	m_z.z = 1.0f;
	m_pos.z = CAMERA_INIT_Z;
	m_pos.y = 5.0f;
	m_button = -1;
	
	//this->LookAt(Vector3(0.0f, 0.875f, 0.0f), Vector3(0.0f, 0.875f, 2.5f), true);

}

void CCameraManager::Reset()
{
	m_angle = 0.0f;
	m_angleIn = CAMERA_ANGLE_IN;
	ZeroMemory(&m_pos, sizeof(m_pos));
	ZeroMemory(&m_rotate, sizeof(m_rotate));
	m_pos.z = CAMERA_INIT_Z;
	m_pos.y = 5.0f;

}


void CCameraManager::Move(Vector3 move)
{
	m_ref += move;
	m_pos += move;

	this->CalculateViewMatrix();
}

void CCameraManager::LookAt(Vector3 reference, Vector3 pos, bool rotateAroundReference)
{
	this->m_ref = reference;
	this->m_pos = pos;

	Normalize3f(m_z, pos - reference);
	Vector3 tv;
	Cross3f(tv, Vector3(0.0f, 1.0f, 0.0f), m_z);
	Normalize3f(m_x, tv);
	Cross3f(m_y, m_z, m_x);

	if (!rotateAroundReference)
	{
		this->m_ref = this->m_pos;
		this->m_pos += m_z * 0.05f;
	}

	CalculateViewMatrix();
}

void CCameraManager::OnMouseMove(int x, int y)
{

	float sensitivity = 0.10f;

	float hangle = (float)x * sensitivity;
	float vangle = (float)y * sensitivity;

	m_pos -= m_ref;

	m_y = RotateVector(m_y, vangle, m_x);
	m_z = RotateVector(m_z, vangle, m_x);

	if (m_y.y < 0.0f)
	{
		m_z = Vector3(0.0f, m_z.y > 0.0f ? 1.0f : -1.0f, 0.0f);
		Cross3f(m_y, m_z, m_x);
	}
	
	m_x = RotateVector(m_x, hangle, Vector3(0.0f, 1.0f, 0.0f));
	m_y = RotateVector(m_y, hangle, Vector3(0.0f, 1.0f, 0.0f));
	m_z = RotateVector(m_z, hangle, Vector3(0.0f, 1.0f, 0.0f));

	m_pos = m_ref + m_z * m_pos.Len();
	CalculateViewMatrix();
}



Vector3 CCameraManager::OnKeys(BYTE Keys, float frameTime)
{
	float speed = CAMERA_SPEED;
	// Shift
	if (Keys & 0x40) speed *= 2.0f;
	
	float dist = speed * frameTime;

	Vector3 up(0.0f, 1.0f, 0.0f);
	Vector3 right = m_x;
	Vector3 forward;
	Cross3f(forward, up, right);

	up *= dist;
	right *= dist;
	forward *= dist;

	Vector3 move;

	// w
	if (Keys & 0x01) move += forward;
	// s
	if (Keys & 0x02) move -= forward;
	// a
	if (Keys & 0x04) move -= right;
	// d
	if (Keys & 0x08) move += right;
	// r
	if (Keys & 0x10) move += up;
	// f
	if (Keys & 0x20) move -= up;
	
	return move;
}

void CCameraManager::OnMouseWheel(float zDelta)
{
	m_pos -= m_ref;

	if (zDelta < 0 && m_pos.Len() < 500.0f) m_pos = m_pos + m_pos * 0.1f;
	if (zDelta > 0 && m_pos.Len() > 0.05f) m_pos = m_pos - m_pos * 0.5f;
	
	m_pos += m_ref;

	CalculateViewMatrix();
}