#include "Define.h"

CRenderManager* CRenderManager::m_instance = nullptr;

void CRenderManager::Init()
{
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	glFrontFace(GL_CCW);
	glEnable(GL_DEPTH_TEST);

	m_perspective.Fovy = PERSPEVTIVE_FOVY;
	m_perspective.Near = PERSPEVTIVE_NEAR;
	m_perspective.Far = PERSPEVTIVE_FAR;
	m_selectedObjIdx = -1;
	m_showCollisionArea = false;
	m_enemyCnt = 0;
	CAMERAMANAGER->SetViewMatrix(&m_view);
	FILEMANAGER->LoadFileWithPath("./Resources//Stage//default.txt");
	m_player = make_shared<CPlayer>();
	m_player->Init();
	m_stageTime = GetTickCount();
	m_stage = 1;
	this->SetPlayerPos(CAMERAMANAGER->GetPos().x, CAMERAMANAGER->GetPos().y, CAMERAMANAGER->GetPos().z - 1.0f);
	
	for (int i = 0; i < m_stage; ++i) {
		Vector3 pos(rand() % 50 - ITEM_RAD, ENEMY_SIZE / 1.5f, rand() % 50 - ITEM_RAD);
		if (rand() % 2) pos.x = -pos.x;
		if (rand() % 2) pos.z = -pos.z;
		m_obj.emplace_back(FACTORYMANAGER->CreateObj(ObjectInfo(ENEMY, Color(0.0f, 1.0f, 1.0f), pos, Vector4(Vector3(), 5.0f), Vector3(), ENEMY_SIZE)));
		m_enemyCnt++;
	}

	for (int i = 0; i < m_stage + 2; ++i) {
		Vector3 pos(rand() % 50 - ITEM_RAD, 50 - ITEM_RAD, rand() % 50 - ITEM_RAD);
		if (rand() % 2) pos.x = -pos.x;
		if (rand() % 2) pos.z = -pos.z;
		m_obj.emplace_back(FACTORYMANAGER->CreateObj(ObjectInfo(ITEM, Color(), pos, Vector4(), Vector3(), ITEM_RAD)));
	}

	for (int i = 0; i < m_stage + 2; ++i) {
		Vector3 pos(rand() % 50 - ITEM_RAD, BULLET_RAD, rand() % 50 - ITEM_RAD);
		if (rand() % 2) pos.x = -pos.x;
		if (rand() % 2) pos.z = -pos.z;
		m_obj.emplace_back(FACTORYMANAGER->CreateObj(ObjectInfo(BULLET, Color(1.0f, 0.0f, 0.0f), pos, Vector4(), Vector3(), BULLET_RAD)));
	}
}

void CRenderManager::ReSet()
{
	CAMERAMANAGER->Reset();
	m_player->Init();
	this->SetPlayerPos(CAMERAMANAGER->GetPos().x, CAMERAMANAGER->GetPos().y, CAMERAMANAGER->GetPos().z - 1.0f);
	m_stageTime = GetTickCount();

	m_enemyCnt = 0;

	vector<shared_ptr<CObject>>::iterator itor = m_obj.begin();
	while (itor != m_obj.end()) {
		if ((*itor)->GetObjInfo().objType != CUBE) itor = m_obj.erase(itor);
		else ++itor;
	}

	for (int i = 0; i < m_stage; ++i) {
		Vector3 pos(rand() % 50 - ITEM_RAD, ENEMY_SIZE / 1.5f, rand() % 50 - ITEM_RAD);
		if (rand() % 2) pos.x = -pos.x;
		if (rand() % 2) pos.z = -pos.z;
		m_obj.emplace_back(FACTORYMANAGER->CreateObj(ObjectInfo(ENEMY, Color(0.0f, 1.0f, 1.0f), pos, Vector4(Vector3(), 5.0f), Vector3(), ENEMY_SIZE)));
		m_enemyCnt++;
	}

	for (int i = 0; i < m_stage + 2; ++i) {
		Vector3 pos(rand() % 50 - ITEM_RAD, 50 - ITEM_RAD, rand() % 50 - ITEM_RAD);
		if (rand() % 2) pos.x = -pos.x;
		if (rand() % 2) pos.z = -pos.z;
		m_obj.emplace_back(FACTORYMANAGER->CreateObj(ObjectInfo(ITEM, Color(), pos, Vector4(), Vector3(), ITEM_RAD)));
	}

	for (int i = 0; i < m_stage + 2; ++i) {
		Vector3 pos(rand() % 50 - ITEM_RAD, BULLET_RAD, rand() % 50 - ITEM_RAD);
		if (rand() % 2) pos.x = -pos.x;
		if (rand() % 2) pos.z = -pos.z;
		m_obj.emplace_back(FACTORYMANAGER->CreateObj(ObjectInfo(BULLET, Color(1.0f, 0.0f, 0.0f), pos, Vector4(), Vector3(), BULLET_RAD)));
	}
}

void CRenderManager::Resize(int w, int h)
{
	m_width = w;
	m_height = h;

	glViewport(0, 0, w, h);
	m_projection = GetPerspectiveProjectionMatrix(m_perspective.Fovy, (float)w, (float)h, m_perspective.Near, m_perspective.Far);
	m_projectionBiasInverse = GetPerspectiveProjectionMatrixInverse(m_projection) * GetBiasMatrixInverse();
	glMatrixMode(GL_PROJECTION);
	glLoadMatrixf(&m_projection);
}


void CRenderManager::MoveObject(int x, int y)
{
	y = m_height - 1 - y;

	float s = (float)x / (float)(m_width - 1);
	float t = (float)y / (float)(m_height - 1);

	Vector4 Point = GetViewMatrixInverse(m_view) * (m_projectionBiasInverse * Vector4(s, t, 0.5f, 1.0f));
	Point /= Point.w;

	Vector3 ray;
	Normalize3f(ray, (Point - CAMERAMANAGER->GetPos()));

	float NdotR = -Dot3f(m_planeNormal, ray);

	if (NdotR != 0.0f){
		float Distance = (Dot3f(m_planeNormal, CAMERAMANAGER->GetPos()) + m_planeD) / NdotR;
		Vector3 Point = ray * Distance + CAMERAMANAGER->GetPos();

		Vector3 Offset = Point - m_selectedPoint;

		m_selectedPoint = Point;
		//m_objPos = m_objPos + Offset;

	}
}


void CRenderManager::SelectObject(int x, int y)
{

	GLint viewport[4];
	GLdouble modelview[16], projection[16];
	GLfloat wx = x, wy, wz;

	glGetIntegerv(GL_VIEWPORT, viewport);
	//y = viewport[3] - y;
	wy = y;
	glGetDoublev(GL_MODELVIEW_MATRIX, modelview);
	glGetDoublev(GL_PROJECTION_MATRIX, projection);
	glReadPixels(x, y, 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT, &wz);

	GLfloat winX = 0.0, winY = 0.0, winZ = 0.0;


	GLdouble posX = 0.0, posY = 0.0, posZ = 0.0;
	winX = (float)x;
	winY = (float)viewport[3] - (float)y;   // invert winY so that down lowers value
	glReadPixels(x, int(winY), 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT, &winZ);
	gluUnProject(winX, winY, winZ, modelview, projection, viewport, &posX, &posY, &posZ);
	//cout << -posZ << endl;
	
	
}

void CRenderManager::Update(float frameTime)
{

	m_player->Update(frameTime);
	for (auto& d : m_obj) {
		if (d != nullptr) {
		d->Update(frameTime);
			if (d->GetObjInfo().objType == BULLET)
				if (!m_player->CheckCollision(d->GetObjInfo())) {
					m_player->CreateBullet(d->GetObjInfo());
					d->SetDelete();
				}

			if (d->GetObjInfo().objType == ENEMY)
				if (!m_player->CheckCollision(d->GetObjInfo())) {
					this->ReSet();
					SOUNDMANAGER->effplaysound(DEATH);
				}
		}
		if (d->GetObjInfo().objType == ITEM && !m_player->CheckCollision(d->GetObjInfo())) {
			SOUNDMANAGER->effplaysound(ITEM_DROP);
			CItem* p = dynamic_cast<CItem*>(d.get());
			CAMERAMANAGER->SetItem(p->GetItemType());
			d->SetDelete();
		}
	}

	this->DeleteObject();
	if (m_enemyCnt == 0) {
		m_stage++;
		this->ReSet();
	}
}

void CRenderManager::renderBitmapString(float x, float y, void *font, char *string)
{

	char *s;
	// set position to start drawing fonts
	glRasterPos2f(x, y);
	// loop all the characters in the string
	for (s = string; *s != '\0'; s++) {
		glutBitmapCharacter(font, *s);
	}
}
void  CRenderManager::RenderText()
{
	sprintf_s(m_text.bullets, "Num of Bullet: %d", m_player->GetBulletNum());
	sprintf_s(m_text.enymies, "Num of Enemy: %d", m_enemyCnt);
	sprintf_s(m_text.stageTime, "Stage Time: %.2f", (m_stageTime + STAGE1_TIME - GetTickCount()) / 1000.0f);
	sprintf_s(m_text.stage, "Stage: %d", m_stage);
	this->setOrthographicProjection();
	glColor3f(0.0, 0.0, 0.0);
	glPushMatrix();
	{
		glLoadIdentity();
		renderBitmapString(0, 10, GLUT_BITMAP_TIMES_ROMAN_24, m_text.bullets);  // 총알
		renderBitmapString(0, 10 + 15, GLUT_BITMAP_TIMES_ROMAN_24, m_text.enymies);  // 남은 적
		renderBitmapString(m_width / 2.0f, 10, GLUT_BITMAP_TIMES_ROMAN_24, m_text.stage);
		renderBitmapString(m_width / 2.0f, 10 + 15, GLUT_BITMAP_TIMES_ROMAN_24, m_text.stageTime); // 스테이지 종료 남은 시간
		int cnt{};
		for (int i = 0; i < ITEM_NUM; ++i) {
			if (CAMERAMANAGER->GetOnItem(i)) {
				switch (i) {
				case SPEED_UP: 
					sprintf_s(m_text.item, "Speed Up Remained: %.2f", CAMERAMANAGER->GetItemRemainTime(i));
					renderBitmapString(m_width - strlen(m_text.item) * 11, 10 + (cnt++ * 15) , GLUT_BITMAP_TIMES_ROMAN_24, m_text.item);
					break;
				case SPEED_DOWN:
					sprintf_s(m_text.item, "Speed Down Remained: %.2f", CAMERAMANAGER->GetItemRemainTime(i));
					renderBitmapString(m_width - 295, 10 + (cnt++ * 15), GLUT_BITMAP_TIMES_ROMAN_24, m_text.item);
					break;
				case FROZEN:
					sprintf_s(m_text.item, "Frozen Remained: %.2f", CAMERAMANAGER->GetItemRemainTime(i));
					renderBitmapString(m_width - strlen(m_text.item) * 11, 10 + (cnt++ * 15), GLUT_BITMAP_TIMES_ROMAN_24, m_text.item);
					break;
				default: break;
				}
			}
		}
	}
	this->resetPerspectiveProjection();
}

void CRenderManager::setOrthographicProjection()
{
	// 투영 모드 바꿈
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	// 행렬 초기화
	glLoadIdentity();
	// 2차원 ortho 좌표계로 바꿈
	gluOrtho2D(0, m_width, 0, m_height / 2);
	// y축을 오픈지엘 형식으로 변환
	glScalef(1, -1, 1);
	glTranslatef(0, -m_height / 2, 0);
	glMatrixMode(GL_MODELVIEW);
}

void CRenderManager::resetPerspectiveProjection()
{
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
}

void CRenderManager::Render(float frameTime)
{
	glMatrixMode(GL_MODELVIEW);
	glLoadMatrixf(&m_view);

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glEnable(GL_DEPTH_TEST);


	// render axises and grid -------------------------------------------------------------------------------------------------

	glLineWidth(2.0f);

	glBegin(GL_LINES);

	glColor3f(1.0f, 0.0f, 0.0f);

	glVertex3f(0.0f, 0.0f, 0.0f); glVertex3f(1.0f, 0.0f, 0.0f);
	glVertex3f(1.0f, 0.1f, 0.0f); glVertex3f(1.1f, -0.1f, 0.0f);
	glVertex3f(1.1f, 0.1f, 0.0f); glVertex3f(1.0f, -0.1f, 0.0f);

	glColor3f(0.0f, 1.0f, 0.0f);

	glVertex3f(0.0f, 0.0f, 0.0f); glVertex3f(0.0f, 1.0f, 0.0f);
	glVertex3f(-0.05f, 1.25f, 0.0f); glVertex3f(0.0f, 1.15f, 0.0f);
	glVertex3f(0.05f, 1.25f, 0.0f); glVertex3f(0.0f, 1.15f, 0.0f);
	glVertex3f(0.0f, 1.15f, 0.0f); glVertex3f(0.0f, 1.05f, 0.0f);

	glColor3f(0.0f, 0.0f, 1.0f);

	glVertex3f(0.0f, 0.0f, 0.0f); glVertex3f(0.0f, 0.0f, 1.0f);
	glVertex3f(-0.05f, 0.1f, 1.05f); glVertex3f(0.05f, 0.1f, 1.05f);
	glVertex3f(0.05f, 0.1f, 1.05f); glVertex3f(-0.05f, -0.1f, 1.05f);
	glVertex3f(-0.05f, -0.1f, 1.05f); glVertex3f(0.05f, -0.1f, 1.05f);

	glEnd();

	glLineWidth(1.0f);

	glColor3f(1.0f, 1.0f, 1.0f);

	glBegin(GL_LINES);

	float d = 50.0f;

	for (float i = -d; i <= d; i += 1.0f)
	{
		glColor3f(0.0f, 0.0f, 0.0f);
		glVertex3f(i, 0.0f, -d);
		glVertex3f(i, 0.0f, d);
		glVertex3f(-d, 0.0f, i);
		glVertex3f(d, 0.0f, i);
	}

	glEnd();
	
	for (auto d : m_obj) d->Render();
	m_player->Render();
	this->RenderText();

	glPopMatrix();

	glDisable(GL_DEPTH_TEST);




}



void CRenderManager::AddObject(ObjectInfo obj)
{
	m_obj.emplace_back(FACTORYMANAGER->CreateObj(obj));
}

void CRenderManager::DeleteObject()
{
	vector<shared_ptr<CObject>>::iterator itor = m_obj.begin();
	while (itor != m_obj.end()) {
		if ((*itor)->GetDelete()) {
			if ((*itor)->GetObjInfo().objType == ENEMY) m_enemyCnt--;
			itor = m_obj.erase(itor);
		}
		else ++itor;
	}
}

void CRenderManager::SpeedDownEnemies()
{
	for (auto& d : m_obj) {
		if (d != nullptr) {
			if (d->GetObjInfo().objType == ENEMY) {
				CEnemy* p = dynamic_cast<CEnemy*>(d.get());
				p->SetSpeed(ENEMY_DOWN_SPEED);
			}
		}
	}
}

void CRenderManager::FrozenEnemies()
{
	SOUNDMANAGER->effplaysound(SOUND_FROZEN);
	for (auto& d : m_obj) {
		if (d != nullptr) {
			if (d->GetObjInfo().objType == ENEMY) {
				CEnemy* p = dynamic_cast<CEnemy*>(d.get());
				p->SetSpeed(0.0f);
			}
		}
	}
}
void CRenderManager::SpeedResetEnemies()
{
	for (auto& d : m_obj) {
		if (d != nullptr) {
			if (d->GetObjInfo().objType == ENEMY) {
				CEnemy* p = dynamic_cast<CEnemy*>(d.get());
				p->SetSpeed(ENEMY_SPEED);
			}
		}
	}
}

void CRenderManager::CreateParticle(Vector3 pos)
{
	Vector3 rotation;

	for (int i = 0; i < PARTICLE_NUM; ++i) {
		rotation.x = rand() % 360;
		rotation.y = rand() % 360;
		rotation.z = rand() % 360;

		if (rand() % 2) rotation.x = -rotation.x;
		if (rand() % 2) rotation.y = -rotation.y;
		if (rand() % 2) rotation.z = -rotation.z;

		m_obj.emplace_back(FACTORYMANAGER->CreateObj(ObjectInfo(PARTICLE, Color(), pos, Vector4(rotation, 0.0f), Vector3(), ENEMY_SIZE)));
	}
}