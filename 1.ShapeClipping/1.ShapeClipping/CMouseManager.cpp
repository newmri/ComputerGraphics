#include "Define.h"

CMouseManager* CMouseManager::m_instance = nullptr;

vector<Vector2> CMouseManager::m_posV;
bool CMouseManager::m_isLeftOn;

void CMouseManager::Init()
{
	glutMouseFunc(MouseClick);
	glutMotionFunc(this->MouseClickMove);
	glutPassiveMotionFunc(this->MouseMove);
	m_isLeftOn = false;
}

void CMouseManager::ConvertDeviceToOpenGL(const int x, const int y, Vector2& pos)
{
	float w = WINDOWS_WIDTH;
	float h = WINDOWS_HEIGHT;

	pos.x = (x - w / 2.0f) * (1.0f / (w / 2.0f));
	pos.y = -(y - h / 2.0f) * (1.0f / (h / 2.0f));
}

void CMouseManager::MouseClick(const int button, const int state, const int x, const int y)
{
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) m_isLeftOn = true;
	else m_isLeftOn = false;
}

void CMouseManager::MouseClickMove(const int x, const int y)
{
	if (m_isLeftOn) {
		ConvertDeviceToOpenGL(x, y, MOUSEMANAGER->GetPos());
		m_posV.emplace_back(MOUSEMANAGER->GetPos());
	}
}

void CMouseManager::MouseMove(const int x, const int y)
{
	ConvertDeviceToOpenGL(x, y, MOUSEMANAGER->GetPos());
	m_isLeftOn = false;
}

const bool CMouseManager::HaveSomethingToClip()
{
	return (!m_isLeftOn && m_posV.size() != 0);
}

void CMouseManager::Update()
{
	
}