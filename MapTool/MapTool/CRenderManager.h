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
	bool haveToDelete;
	Object() {};
	Object(OBJECT_TYPE objType, Color color, Vector3 pos, Vector4 rotation, Vector3 scale, float size) : objType(objType), color(color), pos(pos), rotation(rotation), scale(scale), size(size) { haveToDelete = false; };
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
	void DeleteObject();
	void ModifySelectedObject();
	void MoveSelectedObject(char key);
	std::vector<Object>& GetObjects() { return m_obj; }
	bool haveObject() { if (m_selectedObjIdx > -1) return true; return false; }
	bool haveBeforeObject() { if (m_selectedObjIdx > 0) return true; return false; }
	Object GetSelectedObject() { return m_obj[m_selectedObjIdx]; }
	Vector3 GetBeforeObjectPos() { return m_obj[m_selectedObjIdx - 1].pos; }
	void SelectObject(int x, int y);
	void MoveObject(int x, int y);

public:
	const Perspective& GetPerspective() { return m_perspective; }

public:
	void SetPerspective(const Perspective p) { m_perspective = p; this->Resize(m_width, m_height); }
	void SetObjectInfoDlg(HWND& hWnd) { m_objectInfoDlg = hWnd; }
	void SetObjectModifyDlg(HWND& hWnd) { m_ObjectModifyDlg = hWnd; }
	void SetText(Object obj);
	void ReSetText();

public:
	void GoToStartPos();

private:
	static CRenderManager* m_instance;

	int m_width, m_height;
	Matrix4 m_model, m_view, m_projection, m_projectionBiasInverse;

	//CShaderProgram Shader;

	//int ObjectsCount, LightObjectID;
	//CObject* Objects;
	std::vector<Object> m_obj;
	int objCnt;
	int SelectedObject;
	float m_planeD;
	Vector3 m_selectedPoint, m_planeNormal;
	Perspective m_perspective;
	int m_selectedObjIdx;

	HWND m_objectInfoDlg;
	HWND m_ObjectModifyDlg;
};