#include "Define.h"

CMouseManager* CMouseManager::m_instance = nullptr;

void CMouseManager::Init()
{
	glutMotionFunc(this->MouseClickMove);
	glutPassiveMotionFunc(this->MouseMove);
}

void CMouseManager::ConvertDeviceToOpenGL(const int x, const int y, Vector2& pos)
{
	float w = WINDOWS_WIDTH;
	float h = WINDOWS_HEIGHT;

	pos.x = (x - w / 2.0f) * (1.0f / (w / 2.0f));
	pos.y = -(y - h / 2.0f) * (1.0f / (h / 2.0f));
}

void CMouseManager::MouseMove(const int x, const int y)
{
	ConvertDeviceToOpenGL(x, y, MOUSEMANAGER->GetPos());
}