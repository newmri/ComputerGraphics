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

	//m_ref.y = 5.0f;
	//m_ref.z = 3.0f;
	//Normalize3f(m_z, m_pos - m_ref);
	//Vector3 tv;
	//Cross3f(tv, Vector3(0.0f, 1.0f, 0.0f), m_z);
	//Normalize3f(m_x, tv);
	//Cross3f(m_y, m_z, m_x);
	
	//CalculateViewMatrix();
	//LookAt(Vector3(0.0f, 0.875f, 0.0f),Vector3(0.0f, 0.875f, 2.5f), true);
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
void CCameraManager::SetRotate(unsigned char rotate)
{
	switch (rotate) {
	case 'x': if (m_angleIn < 0.0f) m_angleIn = -m_angleIn;
		m_rotate.x = 0.0f;
		m_rotate.y = 0.0f;
		m_rotate.z = 0.0f;
		break;
	case 'X': //if (m_angleIn > 0.0f) m_angleIn = -m_angleIn;
		m_rotate.x = 0.0f;
		m_rotate.y = 0.0f;
		m_rotate.z = 0.0f;
		break;
	case 'y': if (m_angleIn < 0.0f) m_angleIn = -m_angleIn;
		m_rotate.x = 0.0f;
		m_rotate.y = 1.0f;
		m_rotate.z = 0.0f;
		break;
	case 'Y': if (m_angleIn > 0.0f) m_angleIn = -m_angleIn;
		m_rotate.x = 0.0f;
		m_rotate.y = 1.0f;
		m_rotate.z = 0.0f;
		break;
	case 'z': if (m_angleIn < 0.0f) m_angleIn = -m_angleIn;
		m_rotate.x = 0.0f;
		m_rotate.y = 0.0f;
		m_rotate.z = 1.0f;
		break;
	case 'Z': if (m_angleIn > 0.0f) m_angleIn = -m_angleIn;
		m_rotate.x = 0.0f;
		m_rotate.y = 0.0f;
		m_rotate.z = 1.0f;
		break;
	}
}

void CCameraManager::SetMove(const unsigned char key)
{
	Vector3 up(0.0f, 1.0f, 0.0f);
	Vector3 right = m_x;
	Vector3 forward;
	Cross3f(forward, up, right);

	up *= CAMERA_SPEED;
	right *= CAMERA_SPEED;
	forward *= CAMERA_SPEED;
	Vector3 move;

	switch (key) {
	case 'w': move += forward; break;
	case 's': move -= forward; break;
	case 'a': move -= right; break;
	case 'd': move += right; break;
	case 'q': move -= forward; move -= right; break;
	case 'e': move += forward; move += right; break;
	case 'z': move += up; break;
	case 'x': move -= up; break;
	}

	m_ref += move;
	m_pos += move;
	
	this->CalculateViewMatrix();
}

void CCameraManager::Rotate()
{
	/*
	GLfloat tempMatrix[16];

	if (m_rotate.x == 1.0f || m_rotate.y == 1.0f || m_rotate.z == 1.0f) {
		if (m_angle < 360.0f || m_angle < -360.0f) m_angle += m_angleIn;
		else m_angle = 0.0f;
		glGetFloatv(GL_MODELVIEW_MATRIX, tempMatrix);
		glLoadIdentity();
		glRotatef(m_angle, m_rotate.x, m_rotate.y, m_rotate.z);
		glMultMatrixf(tempMatrix);
	}
	*/

}

void CCameraManager::Move()
{
	//glPushMatrix();
	gluLookAt(m_pos.x, m_pos.y, m_pos.z, m_x.x, m_y.y, m_z.z, 0.0, 1.0, 0.0);
	//glPopMatrix();
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

void CCameraManager::Update()
{
	this->Rotate();
	this->Move();
}

void CCameraManager::Wheel(float z)
{
	m_pos -= m_ref;

	
	if (z < 0 && m_pos.Len() < 500.0f)
	{
		m_pos = m_pos + m_pos * 0.1f;
	}

	if (z > 0 && m_pos.Len() > 0.05f)
	{
		m_pos = m_pos  - m_pos * 0.5f;
	}

	m_pos += m_ref;

	CalculateViewMatrix();

}

void CCameraManager::OnMouseMove(int x, int y)
{

	float sensitivity = 0.25f;

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

void CCameraManager::SetButton(int button, int x, int y)
{
	m_button = button;
	if (button == GLUT_LEFT_BUTTON) RENDERMANAGER->SelectObject(x, y);
	else {
		m_lastCurPos.x = x;
		m_lastCurPos.y = y;
	}
}