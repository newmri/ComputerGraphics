#pragma once

#include "CPolygon.h"

class CRect : public CObject
{

public:
	virtual void Init();
	virtual void Update();
	virtual void Render();

public:
	const POSITION GetPosition() { return m_position; }
	const float GetWaterHeight() { return this->GetBottomPos() + (m_size / m_waterHDevide); }
	const float GetDevide() { return m_waterHDevide2; }

public:
	void StopMove() { m_move = false; }
public:
	void SetWhitePolygon(CPolygon polygon) { m_haveToDrawWhite = true; m_whitePolygon = polygon; }
public:
	CRect() {};
	CRect(const POSITION position, const float size) { m_position = position; m_size = size; this->Init(); }
private:
	POSITION m_position;
	bool m_haveToDrawWhite;
	CPolygon m_whitePolygon;
	float m_waterHDevide, m_waterHDevide2;
	float m_waterInc, m_waterInc2;
	bool m_move;
};