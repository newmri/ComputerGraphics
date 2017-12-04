#pragma once

#include <vector>
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
	void Resize(int w, int h);
	void Render();

public:
	//std::vector<Vector3> GetObjPos() { return m_v; }
	const Perspective& GetPerspective() { return m_perspective; }

public:
	void IncreaseRow(Vector3 pos)
	{
		m_ctrlpoints[m_row][0] = pos.x;
		m_ctrlpoints[m_row][1] = pos.y;
		m_ctrlpoints[m_row][2] = pos.z;
		m_pointZ[m_row] = pos.z;

		m_row++;

		if (m_row == 4) {
			m_controlV.push_back(Points(m_ctrlpoints, m_pointZ));
			m_row = 1;
			for (int i = 0; i < 3; ++i) m_ctrlpoints[0][i] = m_ctrlpoints[3][i];
		}
	}
public:
	void SetPerspective(const Perspective p) { m_perspective = p; this->Resize(m_width, m_height); }

private:
	static CRenderManager* m_instance;

	int m_width, m_height;
	Matrix4 m_model, m_view, m_projection, m_projectionBiasInverse;

	Perspective m_perspective;
	std::vector<Points> m_controlV;
	int m_row;
	float m_ctrlpoints[4][4]{};
	float m_pointZ[4];

}; 
