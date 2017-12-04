#pragma once

#include "Enum.h"

struct Perspective
{
	float Fovy;
	float Near;
	float Far;

	Perspective()
	{
		Fovy = 0.0f;
		Near = 0.0f;
		Far = 0.0f;
	}

	Perspective(float Fovy, float Near, float Far) : Fovy(Fovy), Near(Near), Far(Far) {};

};

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


struct Object
{
	OBJECT_TYPE objType;
	Color color;
	Vector4 rotation;
	Vector3 pos, scale;
	float size;

	Object() {};
	Object(OBJECT_TYPE objType, Color color, Vector3 pos, Vector4 rotation, Vector3 scale, float size) : objType(objType), color(color), pos(pos), rotation(rotation), scale(scale), size(size) {};
};

class CRenderManager
{
public:
	static CRenderManager* GetInstance()
	{
		if (m_instance == nullptr)
			m_instance = new CRenderManager;

		return m_instance;
	}

	CRenderManager() {  }
	~CRenderManager() { delete m_instance; }

public:
	void Init();
	void Resize(int w, int h);
	void Render();

public:
	void AddObject(Object obj);
	std::vector<Object>& GetObjects() { return m_v; }
	void SelectObject(int x, int y);
	void MoveObject(int x, int y);
	void SelectObject(int a) { objects = a; }

public:
	const Perspective& GetPerspective() { return m_perspective; }

public:
	void SetPerspective(const Perspective p) { m_perspective = p; this->Resize(m_width, m_height); }

private:
	static CRenderManager* m_instance;

	int m_width, m_height;
	Matrix4 m_model, m_view, m_projection, m_projectionBiasInverse;

	//CShaderProgram Shader;

	//int ObjectsCount, LightObjectID;
	//CObject* Objects;
	std::vector<Object> m_v;
	int objCnt;
	int SelectedObject;
	float m_planeD;
	Vector3 m_selectedPoint, m_planeNormal;
	Perspective m_perspective;
	int objects;
};