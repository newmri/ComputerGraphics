#pragma once

#include <memory>
#include "Objects.h"

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
	void Render(float frameTime);

public:
	void AddObject(ObjectInfo obj);
	void DeleteObject();

	std::vector<std::shared_ptr<CObject>> GetObjects() { return m_obj; }
	void SelectObject(int x, int y);
	void MoveObject(int x, int y);

public:
	const Perspective& GetPerspective() { return m_perspective; }

public:
	void SetPerspective(const Perspective p) { m_perspective = p; this->Resize(m_width, m_height); }


private:
	static CRenderManager* m_instance;

	int m_width, m_height;
	Matrix4 m_model, m_view, m_projection, m_projectionBiasInverse;
	int objCnt;
	int SelectedObject;
	float m_planeD;
	Vector3 m_selectedPoint, m_planeNormal;
	Perspective m_perspective;
	int m_selectedObjIdx;

private:
	std::vector<std::shared_ptr<CObject>> m_obj;

};