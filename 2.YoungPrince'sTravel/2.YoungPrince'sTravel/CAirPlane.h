#pragma once

#include "CObject.h"

class CAirPlane : public CObject
{
public:
	virtual void Init();
	virtual void Update();
	virtual void Render();


public:
	void SetTarget(Vector3 target[]);
	bool DidGetGoal();

public:
	void Move();

private:
	float m_incre;
	Vector3 m_propelerRotation;
	float m_proplerAngle;
	float m_headAngle;
	Vector3 m_dPos;
	Vector3 m_target[3];
	int m_idx;
};
