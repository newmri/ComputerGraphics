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

const bool CMouseManager::IsInArea(const float left, const float right, const float top, const float bottom)
{

	for (auto d : m_posV)
		if (d.x >= left && d.x <= right && d.y <= top && d.y >= bottom) return true;

	return false;

}


void CMouseManager::Update()
{
	
}

bool Flags::operator&(const Flags& other)
{

	if ((top == 0 && bottom == 0 && left == 0 && right == 0) &&
		(other.top == 0 && other.bottom == 0 && other.left == 0 && other.right == 0)) return true; // Line is in mid

	if ((top == 0 && bottom == 0 && left == 0 && right == 0) &&
		(other.top != 0 || other.bottom != 0 || other.left != 0 || other.right != 0)) return true; // Half Line

	if ((top != 0 || bottom != 0 || left != 0 || right != 0) &&
		(other.top == 0 && other.bottom == 0 && other.left == 0 && other.right == 0)) return true; // Half Line

	if ((top != 0 || bottom != 0 || left != 0 || right != 0) &&
		(other.top != 0 || other.bottom != 0 || other.left != 0 || other.right != 0)) {

		Flags flag;
		flag.top = top & other.top;
		flag.bottom = bottom & other.bottom;
		flag.left = left & other.left;
		flag.right = right & other.right;


		if (flag.top == 0 || flag.bottom == 0 ||
			flag.left == 0 || flag.right == 0) return false;

	}

	return true;

}