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

static const int TEXT_LEN = 30;

struct Text
{
	char bullets[TEXT_LEN];
	char stage[TEXT_LEN];
	char enymies[TEXT_LEN];
	char item[TEXT_LEN];
	char stageTime[TEXT_LEN];
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
	void ReSet();
	void Update(float frameTime);
	void Resize(int w, int h);
	void Render(float frameTime);

public:
	void setOrthographicProjection();
	void resetPerspectiveProjection();
	void renderBitmapString(float x, float y, void *font, char *string);
	void RenderText();

public:
	void AddObject(ObjectInfo obj);
	void DeleteObject();

	std::vector<std::shared_ptr<CObject>> GetObjects() { return m_obj; }
	void SelectObject(int x, int y);
	void MoveObject(int x, int y);

public:
	const Perspective& GetPerspective() { return m_perspective; }
	Vector3 GetPlayerPos() { return m_player->GetObjInfo().pos; }
public:
	void SetPerspective(const Perspective p) { m_perspective = p; this->Resize(m_width, m_height); }

public:
	void SetPlayerPos(const float x, const float y, const float z) { m_player->SetPos(x, y, z); }
	void ShootBullet() { m_player->Shoot(); }

public:
	void SwapShowCollisionArea() { m_showCollisionArea = !m_showCollisionArea; }
	bool ShowCollisionArea() { return m_showCollisionArea; }

public:
	void SpeedDownEnemies();
	void FrozenEnemies();
	void SpeedResetEnemies();

public:
	void CreateParticle(Vector3 pos);

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
	std::shared_ptr<CPlayer> m_player;
	bool m_showCollisionArea;
	Text m_text;
	int m_enemyCnt;
	DWORD m_stageTime;
	int m_stage;
	bool m_stageClear;
};