#ifndef CTRIANGLE_H
#define CTRIANGLE_H

#include "Define.h"

class CShape
{
public:
	void Init(OBJTYPE objType, Pos pos, DATA_TYPE size)
	{
		m_objType = objType;
		m_pos = pos;
		m_size = size;
		m_str = nullptr;
	}

public:
	void RenderText()
	{
		if (m_str != nullptr) {
			glDisable(GL_BLEND);
			glRasterPos2f(-70, -70);
			int len = (int)strlen(m_str);
			for (int i = 0; i < len; i++) glutBitmapCharacter(GLUT_BITMAP_HELVETICA_10, m_str[i]);
			glEnable(GL_BLEND);
		}

	}

	void SetStr(char* str) { m_str = str; }
public:
	virtual void Update() = 0;
	virtual void Render() = 0;

protected:
	OBJTYPE m_objType;
	Pos m_pos;
	DATA_TYPE m_size;
	char* m_str;
};

#endif
