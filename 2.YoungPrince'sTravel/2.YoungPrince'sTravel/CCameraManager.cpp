#include "Define.h"

CCameraManager* CCameraManager::m_instance = nullptr;

void CCameraManager::Init()
{
	m_angle = 0.0f;
	m_angleIn = CAMERA_ANGLE_IN;
	m_x.x = 1.0f;
	m_y.y = 1.0f;
	m_z.z = 1.0f;
}

void CCameraManager::Reset()
{
	m_angle = 0.0f;
	m_angleIn = CAMERA_ANGLE_IN;
	ZeroMemory(&m_pos, sizeof(m_pos));
	ZeroMemory(&m_rotate, sizeof(m_rotate));
	ZeroMemory(&m_x, sizeof(m_x));
	ZeroMemory(&m_y, sizeof(m_y));
	ZeroMemory(&m_z, sizeof(m_z));
	m_x.x = 1.0f;
	m_y.y = 1.0f;
	m_z.z = 1.0f;
	this->LookAt(Vector3(0.0f, 0.0f, 0.0f), Vector3(30.0f, 0.0f, 90.0f), true);
	
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
	case 'y': 
		if (m_angleIn < 0.0f) m_angleIn = -m_angleIn;
		m_rotate.x = 0.0f;
		m_rotate.y = 1.0f;
		m_rotate.z = 0.0f;
		break;
	case 'Y': if (m_angleIn > 0.0f) m_angleIn = -m_angleIn;
		m_rotate.x = 0.0f;
		m_rotate.y = 1.0f;
		m_rotate.z = 0.0f;
		break;
	case 'z': 
		if (m_angleIn < 0.0f) m_angleIn = -m_angleIn;
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

}

void CCameraManager::Move()
{
	gluLookAt(m_pos.x, m_pos.y, m_pos.z, m_x.x, m_y.y , m_z.z, 0.0, 1.0, 0.0);
}
void CCameraManager::Update()
{
	this->Rotate();
	this->Move();
}

void CCameraManager::SetButton(int button, int x, int y)
{
	m_button = button;

	if (button == GLUT_RIGHT_BUTTON) {
		m_lastPos.x = x;
		m_lastPos.y = y;
	}
	else {
		GLint viewport[4];
		GLdouble modelview[16], projection[16];
		GLfloat wx = x, wy, wz;

		glGetIntegerv(GL_VIEWPORT, viewport);
		y = viewport[3] - y;
		wy = y;
		glGetDoublev(GL_MODELVIEW_MATRIX, modelview);
		glGetDoublev(GL_PROJECTION_MATRIX, projection);
		glReadPixels(x, y, 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT, &wz);

		GLfloat winX = 0.0, winY = 0.0, winZ = 0.0;

		GLdouble posX = 0.0, posY = 0.0, posZ = 0.0;
		winX = (float)x;
		winY = (float)viewport[3] - (float)y;   // invert winY so that down lowers value
		glReadPixels(x, int(winY), 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT, &winZ);
		gluUnProject(winX, winY, winZ, modelview, projection, viewport, &posX, &posY, &posZ);
		//RENDERMANAGER->IncreaseRow(Vector3(posX, -posY, -posZ));


	}

}
void CCameraManager::OnMouseMove(int x, int y)
{
	
		float sensitivity = 0.15f;

		float hangle = (float)x * sensitivity;
		float vangle = (float)y * sensitivity;

		m_pos -= m_ref;

		m_y = RotateVector(m_y, vangle, m_x);
		m_z = RotateVector(m_z, vangle, m_x);

		/*
		if (m_y.y < 0.0f)
		{
			m_z = Vector3(0.0f, m_z.y > 0.0f ? 1.0f : -1.0f, 0.0f);
			Cross3f(m_y, m_z, m_x);
		}
		*/
		m_x = RotateVector(m_x, hangle, Vector3(0.0f, 1.0f, 0.0f));
		m_y = RotateVector(m_y, hangle, Vector3(0.0f, 1.0f, 0.0f));
		m_z = RotateVector(m_z, hangle, Vector3(0.0f, 1.0f, 0.0f));

		m_pos = m_ref + m_z * m_pos.Len();
		
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