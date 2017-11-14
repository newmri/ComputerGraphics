#ifndef COBJECT_H
#define COBJECT_H

#include "Define.h"

class CObject
{
public:
	void Init(float(*arr)[3]);
	void Update();
	void Render();

public:
	const Vector3& GetPos() { return m_pos; }
	GLfloat(*GetPoints(void))[3]{ return m_ctrlPoints; }
public:
	void SetPos(const Vector3 newPos) { m_pos = newPos; }
	void SetRotation(const Vector3 newRotation) { m_rotation = newRotation; }




private:
	Vector3 m_pos, m_rotation;
	GLfloat m_ctrlPoints[4][3];
};

#endif