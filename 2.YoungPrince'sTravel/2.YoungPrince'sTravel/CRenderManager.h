#pragma once

#include <vector>
#include <memory>

#include "Matrix.h"
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

struct Points
{
	float ctrlpoints[4][4]{};
	float z[4];
	Points() {};
	Points(float(*arr)[4], float posZ[4])
	{
		for (int i = 0; i < 4; ++i) {
			for (int j = 0; j < 3; ++j) ctrlpoints[i][j] = arr[i][j];
			z[i] = posZ[i];
		}
	}
};

struct CObject;

class CRenderManager
{
public:
	static CRenderManager* GetInstance()
	{
		if (m_instance == nullptr)
			m_instance = new CRenderManager;

		return m_instance;
	}

	//CRenderManager() { this->Init(); }
	//~CRenderManager() { delete m_instance; }

public:
	void Init();
	void Update();
	void Resize(int w, int h);
	void Render();

public:
	void Reset();
	void ResetController();
public:
	std::vector<std::shared_ptr<CObject>> GetObj() { return m_obj; }
	const Perspective& GetPerspective() { return m_perspective; }

public:
	void IncreaseRow(Vector3 pos);
	void DecreaseRow();
public:
	bool HaveAirPlane() { return m_haveAirPlane; }
	CObject* GetAirPlane() { return m_obj[AIRPLANE].get(); }
public:
	void SetPerspective(const Perspective p) { m_perspective = p; this->Resize(m_width, m_height); }

public:
	bool DidGetGoal() { return m_gotGoal; }
private:
	static CRenderManager* m_instance;
	std::vector<std::shared_ptr<CObject>> m_obj;
	int m_width, m_height;
	Matrix4 m_model, m_view, m_projection, m_projectionBiasInverse;

	Perspective m_perspective;
	std::vector<Points> m_controlV;
	int m_row;
	float m_ctrlpoints[4][4]{};
	float m_pointZ[4];
	bool m_haveAirPlane;
	bool m_gotGoal;
	int m_pointCnt;


}; 
