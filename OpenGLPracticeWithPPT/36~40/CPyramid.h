#pragma once

#include "CObject.h"

class CPyramid : public CObject
{
public:
	virtual void Init();
	virtual void Update();
	virtual void Render();

public:
	void GenerateColors();
	double GetRandomColor(bool reset = false);

public:
	void Divide(float* a, float* b, float* c, float* d, int iterations);
	void Draw(float* a, float* b, float* c, float* d);

private:
	float m_pyramid[4][3];
	int m_iterations;
	double m_colors[1000];
	DWORD m_time;
};