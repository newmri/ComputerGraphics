#pragma once

#include "Define.h"

class CObject
{
public:
	void Init(OBJTYPE objType, Vector3 pos, Vector3 scale, DATA_TYPE size, Color color)
	{
		m_objType = objType;
		m_pos = pos;
		m_size = size;
		m_bodyColor = color;
		m_scale = scale;
	}
	void Init(OBJTYPE objType, Vector3 pos, Vector3 scale, DATA_TYPE size, Color bodycolor, Color leafcolor)
	{
		m_objType = objType;
		m_pos = pos;
		m_size = size;
		m_bodyColor = bodycolor;
		m_leafColor = leafcolor;
		m_scale = scale;
	}

	void Init(OBJTYPE objType, Vector3 pos, DATA_TYPE size, float lightNum)
	{
		m_objType = objType;
		m_pos = pos;
		m_size = size;
		m_lightNum = lightNum;
		m_lightOn = true;

	}
	virtual void Init() = 0;
	virtual void Update() = 0;
	virtual void Render() = 0;

public:
	const OBJTYPE& GetObjType() { return m_objType; }
	const Vector3& GetPos() { return m_pos; }
	const Color& GetBodyColor() { return m_bodyColor; }

public:
	void SetPos(const Vector3 newPos) { m_pos = newPos; }
	void SetBodyColor(const Color newColor) { m_bodyColor = newColor; }
	void SetRotation(const Vector3 newRotation) { m_rotation = newRotation; }

	void Rotate()
	{
		if (m_angle < 360.0f) m_angle += 3.0f;
		else m_angle = 0.0f;

	}

	void ChangeSizeBigger()
	{
		m_size += 0.001f;
		glScalef(m_size, m_size, m_size);
	}
public:
	float GetSize() { return m_size; }


public:
	void SwitchLight() { m_lightOn = !m_lightOn; }
	void IncreAmbient()
	{
		for (int i = 0; i < 3; ++i) {
			if (AmbientLight[i] < 1.0f) AmbientLight[i] += 0.05f;
		}
	}

	void DecreAmbient()
	{
		for (int i = 0; i < 3; ++i) {
			if (AmbientLight[i] > 0.0f) AmbientLight[i] -= 0.05f;
		}
	}
	void IncreDiffuse()
	{
		for (int i = 0; i < 3; ++i) {
			if (DiffuseLight[i] < 1.0f) DiffuseLight[i] += 0.05f;
		}
	}

	void DecreDiffuse()
	{
		for (int i = 0; i < 3; ++i) {
			if (DiffuseLight[i] > 0.0f) DiffuseLight[i] -= 0.05f;
		}
	}

	void IncreSpecular()
	{
		for (int i = 0; i < 3; ++i) {
			if (SpecularLight[i] < 1.0f) SpecularLight[i] += 0.05f;
		}

	}

	void DecreSpecular()
	{
		for (int i = 0; i < 3; ++i) {
			if (SpecularLight[i] > 0.0f) SpecularLight[i] -= 0.05f;
		}
	}
protected:
	OBJTYPE m_objType;
	Color m_bodyColor, m_leafColor;
	Vector3 m_pos, m_scale, m_rotation;
	DATA_TYPE m_size;
	float m_angle;
	float m_lightNum;
	bool m_lightOn;
	GLfloat AmbientLight[4];
	GLfloat DiffuseLight[4];
	GLfloat SpecularLight[4];
};
