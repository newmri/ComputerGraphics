#pragma once

#include "CObject.h"


class CPolygon : public CObject
{

public:
	virtual void Init();
	virtual void Update();
	virtual void Render();

public:
	CPolygon() { this->Init(); }

	void RenderWhitePolygon();
public:
	void ReSetV3() { m_haveV3 = false; }
	void SetWhite(const float dir) { m_isWhite = true; m_vX = dir; }
	void SetDrop() { m_drop = true; }
	void ResetDrop() { m_drop = false; }
public:
	void SetV1(const Vector2 v1) { m_v1 = v1; }
	void SetV2(const Vector2 v2) { m_v2 = v2; }
	void SetV3(const Vector2 v3) { m_v3 = v3; m_haveV3 = true;}
	void SetV4(const Vector2 v4) { m_v4 = v4; }
private:
	Vector2 m_v1, m_v2, m_v3, m_v4;
	Vector2 m_whitePos;
	bool m_haveV3;
	bool m_isWhite;
	bool m_drop;
};