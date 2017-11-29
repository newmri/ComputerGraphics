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

	m_pos.z = 50.0f;
	m_pos.y = 5.0f;
	m_button = -1;
}

void CCameraManager::Reset()
{
	m_angle = 0.0f;
	m_angleIn = CAMERA_ANGLE_IN;
	ZeroMemory(&m_pos, sizeof(m_pos));
	ZeroMemory(&m_rotate, sizeof(m_rotate));
	m_pos.z = 50.0f;
	m_pos.y = 5.0f;
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
	case 'q': m_pos.x += -CAMERA_SPEED; m_pos.z += -CAMERA_SPEED; break;
	case 'e': m_pos.x += CAMERA_SPEED; m_pos.z += -CAMERA_SPEED; break;
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
	//glPushMatrix();
	gluLookAt(m_pos.x, m_pos.y, m_pos.z, 0.0, 0.0, -100.0f, 0.0, 1.0, 0.0);
	//glPopMatrix();
}
void CCameraManager::Update()
{
	this->Rotate();
	this->Move();
}

void CCameraManager::Wheel(float z)
{
	m_pos = m_pos - m_ref;

	
	if (z < 0 && m_pos.Len() < 500.0f)
	{
		m_pos = m_pos + m_pos * 0.1f;
	}

	if (z > 0 && m_pos.Len() > 0.05f)
	{
		m_pos = m_pos  - m_pos * 0.5f;
	}

	m_pos = m_pos + m_ref;

	CalculateViewMatrix();

}

void CCameraManager::OnMouseMove(int x, int y)
{

	int tx = x;
	int ty = y;
	x = m_lastCurPos.x - x;
	y = m_lastCurPos.y - y;

	m_lastCurPos.x = tx;
	m_lastCurPos.y = ty;

	float sensitivity = 0.25f;

	float hangle = (float)x * sensitivity;
	float vangle = (float)y * sensitivity;

	m_pos = m_pos - m_ref;

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
	cout << m_y.z << endl;
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