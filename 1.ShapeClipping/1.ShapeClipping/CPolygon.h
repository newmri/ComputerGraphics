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
	const float GetLowPos(float a, float b)
	{
		if (a > b) return b;
		else return a;
	}

	const float GetHighPos(float a, float b)
	{
		if (a < b) return b;
		else return a;
	}
public:
	const float GetPolygonLeftPos()
	{
		float ret;
		ret = GetLowPos(m_v1.x, m_v2.x);
		ret = GetLowPos(ret, m_v4.x);
		if(m_v3.x != 0.0f) ret = GetLowPos(ret, m_v3.x);

		return ret;
	}
	const float GetPolygonRightPos()
	{
		float ret;
		ret = GetHighPos(m_v1.x, m_v2.x);
		ret = GetHighPos(ret, m_v4.x);
		if (m_v3.x != 0.0f) ret = GetHighPos(ret, m_v3.x);

		return ret;
	}
	const float GetPolygonTopPos()
	{
		float ret;
		ret = GetHighPos(m_v1.y, m_v2.y);
		ret = GetHighPos(ret, m_v4.y);
		if (m_v3.y != 0.0f) ret = GetHighPos(ret, m_v3.y);

		return ret + m_pos.y;
	}
	const float GetPolygonBottomPos()
	{
		float ret;
		ret = GetLowPos(m_v1.y, m_v2.y);
		ret = GetLowPos(ret, m_v4.y);
		if (m_v3.y != 0.0f) ret = GetLowPos(ret, m_v3.y);

		return ret + m_pos.y;
	}
public:
	const bool GetDrop() { return m_drop; }
public:
	void StopDrop() { m_drop = false; }
public:
	void SetV1(const Vector2 v1) { m_v1 = v1; }
	void SetV2(const Vector2 v2) { m_v2 = v2; }
	void SetV3(const Vector2 v3) { m_v3 = v3; m_haveV3 = true;}
	void SetV4(const Vector2 v4) { m_v4 = v4; }

public:
	bool HaveV3() { return m_haveV3; }
public:
	Vector2 GetV1() { return m_v1; }
	Vector2 GetV2() { return m_v2; }
	Vector2 GetV3() { return m_v3; }
	Vector2 GetV4() { return m_v4; }
private:
	Vector2 m_v1, m_v2, m_v3, m_v4;
	Vector2 m_whitePos;
	bool m_haveV3;
	bool m_isWhite;
	bool m_drop;
};