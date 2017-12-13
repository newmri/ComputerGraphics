#pragma once

#include "Enum.h"
#include "Define.h"

struct Color
{
	float r, g, b;
	Color()
	{
		r = 1.0f;
		g = 1.0f;
		b = 1.0f;
	}

	Color(float r, float g, float b) : r(r), g(g), b(b) {};
};


struct ObjectInfo
{
	OBJECT_TYPE objType;
	Color color;
	Vector4 rotation;
	Vector3 pos, scale;
	float size;
	bool haveToDelete;
	ObjectInfo() {};
	ObjectInfo(OBJECT_TYPE objType, Color color, Vector3 pos, Vector4 rotation, Vector3 scale, float size) : objType(objType), color(color), pos(pos), rotation(rotation), scale(scale), size(size) { haveToDelete = false; };
};

class CObject
{
public:
	void Init(ObjectInfo objInfo) { m_objInfo = objInfo; }
	const ObjectInfo& GetObjInfo() { return m_objInfo; }
	void SetPos(Vector3 pos) { m_objInfo.pos = pos; }
	void SetSize(float size) { m_objInfo.size = size; }
	void SetColor(Color color) { m_objInfo.color = color; }
	bool CheckCollision(const ObjectInfo& other)
	{
		if (pow(other.pos.x - m_objInfo.pos.x, 2) + pow(other.pos.y - m_objInfo.pos.y, 2) + pow(other.pos.z - m_objInfo.pos.z, 2) <= pow(m_objInfo.size + other.size, 2)) // 이게 참이면 충돌함.
			return false;
		return true;
	}
public:
	virtual void Init() = 0;
	virtual void Update() = 0;
	virtual void Render() = 0;

protected:
	ObjectInfo m_objInfo;
};