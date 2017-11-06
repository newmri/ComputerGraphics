#pragma once

#include "CObject.h"

class CAirplain : public CObject
{
public:
	virtual void Init();
	virtual void Update();
	virtual void Render();


public:
	void Move();
	void SetLeftRotate() { m_left = true; }
	void SetRightRotate() { m_left = false; }
private:
	float m_incre;
	Vector3 m_propelerRotation;
	float m_proplerAngle;
	float m_i, m_trackAngle;
	float m_headAngle;
	Vector3 m_dPos;
	Vector3 m_target;
	bool m_left;
};
