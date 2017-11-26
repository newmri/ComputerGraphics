#include "Define.h"

CCameraManager* CCameraManager::m_instance = nullptr;

void CCameraManager::Init()
{
	m_angle = 0.0f;
	m_angleIn = CAMERA_ANGLE_IN;
	m_pos.x = 10;
}

void CCameraManager::Reset()
{
	m_angle = 0.0f;
	m_angleIn = CAMERA_ANGLE_IN;
	ZeroMemory(&m_pos, sizeof(m_pos));
	ZeroMemory(&m_rotate, sizeof(m_rotate));
}
void CCameraManager::SetRotate(unsigned char rotate)
{
	switch (rotate) {
	case 'x': if (m_angleIn < 0.0f) m_angleIn = -m_angleIn;
		m_rotate.x = 1.0f;
		m_rotate.y = 0.0f;
		m_rotate.z = 0.0f;
		break;
	case 'X': if (m_angleIn > 0.0f) m_angleIn = -m_angleIn;
		m_rotate.x = 1.0f;
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
	switch (key) {
	case 'w': m_pos.y += CAMERA_SPEED; break;
	case 's': m_pos.y += -CAMERA_SPEED; break;
	case 'a': m_pos.x += -CAMERA_SPEED; break;
	case 'd': m_pos.x +=  CAMERA_SPEED; break;
	case '+': m_pos.z += -CAMERA_SPEED; break;
	case '-': m_pos.z += CAMERA_SPEED;  break;
	}

}

void CCameraManager::Rotate()
{
	GLfloat tempMatrix[16];

	if (m_rotate.x == 1.0f || m_rotate.y == 1.0f || m_rotate.z == 1.0f) {
		if (m_angle < 360.0f || m_angle < -360.0f) m_angle += m_angleIn;
		else m_angle = 0.0f;

		glGetFloatv(GL_MODELVIEW_MATRIX, tempMatrix);
		glLoadIdentity();
		glRotatef(m_angle, m_rotate.x, m_rotate.y, m_rotate.z);
		glMultMatrixf(tempMatrix);
	}
}

void CCameraManager::Move()
{
	gluLookAt(m_pos.x, m_pos.y, m_pos.z, 0.0, 0.0, -100.0f, 0.0, 1.0, 0.0);
}
void CCameraManager::Update()
{
	this->Rotate();
	this->Move();
}

