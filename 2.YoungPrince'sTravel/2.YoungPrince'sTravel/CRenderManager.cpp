#include "Define.h"
#include "Objects.h"

CRenderManager* CRenderManager::m_instance = nullptr;


void CRenderManager::Init()
{
	CAMERAMANAGER->SetViewMatrix(&m_view);
	m_perspective.Fovy = PERSPEVTIVE_FOVY;
	m_perspective.Near = PERSPEVTIVE_NEAR;
	m_perspective.Far = PERSPEVTIVE_FAR;
	CAMERAMANAGER->LookAt(Vector3(0.0f, 0.0f, 0.0f), Vector3(30.0f, 0.0f, 90.0f), true);
	m_row = 0;
	m_haveAirPlane = false;
	m_gotGoal = false;
	m_pointCnt = 0;
	m_obj.emplace_back(FACTORYMANAGER->CreateObj(CUBE, Vector3(0.0f, 0.0f, 0.0f), CUBE_SIZE, Color(1.0f, 1.0f, 1.0f)));
	m_obj.emplace_back(FACTORYMANAGER->CreateObj(PARTICLE, Vector3(0.0f, 0.0f, 0.0f), 0.3f, Color(1.0f, 1.0f, 1.0f)));
	Vector3 lt(Vector3(-CUBE_SIZE / 2.0f + EARTH_RAD, CUBE_SIZE / 2.0f - EARTH_RAD, CUBE_SIZE / 2.0f - EARTH_RAD));
	Vector3 rb(Vector3(CUBE_SIZE / 2.0f - EARTH_RAD, -CUBE_SIZE / 2.0f + EARTH_RAD, -CUBE_SIZE / 2.0f + EARTH_RAD));
	m_obj.emplace_back(FACTORYMANAGER->CreateObj(EARTH, lt, EARTH_RAD, Color(1.0f, 1.0f, 1.0f)));
	m_obj.emplace_back(FACTORYMANAGER->CreateObj(EARTH, rb, EARTH_RAD, Color(1.0f, 1.0f, 1.0f)));
	m_obj.emplace_back(FACTORYMANAGER->CreateObj(CONTROLLER, rb, EARTH_RAD, Color(1.0f, 1.0f, 1.0f)));

	int num = rand() % 20 + 15;
	Vector3* pos = new Vector3[num];
	int* rad = new int[num];
	for (int i = 0; i < num; ++i) {
		if (i == 0) {
			pos[i] = lt;
			rad[i] = EARTH_RAD;
		}
		if (i == 1) {
			pos[i] = rb;
			rad[i] = EARTH_RAD;
		}
		bool chk = false;
		if (i != 0 && i != 1) {
			rad[i] = rand() % 5 + 2;
			int max = CUBE_SIZE - rad[i] * 2;
			float min = (CUBE_SIZE / 2.0f) - rad[i];

			pos[i].x = (float)(rand() % max) - min;
			pos[i].y = (float)(rand() % max) - min;
			pos[i].z = (float)(rand() % max) - min;
		}
		for (int j = 0; j < i; ++j) {
			chk = (pow(pos[j].x - pos[i].x, 2) + pow(pos[j].y - pos[i].y, 2) +
				pow(pos[j].z - pos[i].z, 2) < pow(rad[i] + rad[j], 2));

			if (chk) {
				chk = false;
				i -= 1;
			}
		}

	}


	for (int i = 0; i < num; ++i) {
		m_obj.emplace_back(FACTORYMANAGER->CreateObj(PLANET, pos[i], rad[i], Color(1.0f, 1.0f, 1.0f)));
	}
	delete[] pos;
	delete[] rad;
}

void CRenderManager::Reset()
{
	this->ResetController();
	vector<shared_ptr<CObject>>::iterator itor = m_obj.begin();
	while (itor != m_obj.end()) {
		
		if ((*itor)->GetObjType() == AIRPLANE) { itor = m_obj.erase(itor); m_haveAirPlane = false; }
		else ++itor;
	}
	
}
void CRenderManager::ResetController()
{
	m_obj[CONTROLLER]->Init();
	m_row = 0;
	ZeroMemory(&m_controlV, sizeof(m_controlV));
}
void CRenderManager::Update()
{
	
	for (auto& d : m_obj) d->Update();

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

void CRenderManager::IncreaseRow(Vector3 pos)
{
	if (m_pointCnt == 30) return;

	m_ctrlpoints[m_row][0] = pos.x;
	m_ctrlpoints[m_row][1] = pos.y;
	m_ctrlpoints[m_row][2] = pos.z;
	m_pointZ[m_row] = pos.z;

	if ((pos.x < CUBE_SIZE / 2.0f && pos.x > CUBE_SIZE / 2.0f - (EARTH_RAD * 2.0f)) &&
		(pos.y > -CUBE_SIZE / 2.0f && pos.y < -CUBE_SIZE / 2.0f + (EARTH_RAD * 2.0f)) &&
		(pos.z > -CUBE_SIZE / 2.0f + EARTH_RAD && pos.z < -CUBE_SIZE / 2.0f + EARTH_RAD * 2)) {
		m_obj[EARTH]->SetColor(Color(1.0f, 0.0f, 0.0f));
		m_gotGoal = true;
	}

	m_row++;

	m_pointCnt++;

	if (m_row == 4) {
		if (!m_haveAirPlane) {
			m_haveAirPlane = true;
			Vector3 airplanePos = Vector3(m_ctrlpoints[0][0], m_ctrlpoints[0][1], m_ctrlpoints[0][2]);
			Vector3 targetPos[3];
			for (int i = 0; i < m_row - 1; ++i) {
					targetPos[i].x = m_ctrlpoints[i + 1][0];
					targetPos[i].y = m_ctrlpoints[i + 1][1];
					targetPos[i].z = m_ctrlpoints[i + 1][2];
			}
			m_obj.emplace_back(FACTORYMANAGER->CreateObj(AIRPLANE, airplanePos, targetPos, AIRPLANE_SIZE, Color(1.0f, 1.0f, 1.0f)));
		}
		else {
			Vector3 targetPos[3];
			for (int i = 0; i < m_row - 1; ++i) {
				targetPos[i].x = m_ctrlpoints[i + 1][0];
				targetPos[i].y = m_ctrlpoints[i + 1][1];
				targetPos[i].z = m_ctrlpoints[i + 1][2];
			}
			for (auto& d : m_obj) {
				if (d->GetObjType() == AIRPLANE) {
					CAirPlane* ap = dynamic_cast<CAirPlane*> (d.get());
					ap->SetTarget(targetPos);
					break;
				}
			}
		}
		m_controlV.push_back(Points(m_ctrlpoints, m_pointZ));
		m_row = 1;
		for (int i = 0; i < 3; ++i) m_ctrlpoints[0][i] = m_ctrlpoints[3][i];
	}
}

void CRenderManager::DecreaseRow()
{
	if(m_row > 1) m_row--;
}

void CRenderManager::Render()
{
	for (auto& d : m_obj) d->Render();

	glPushMatrix();

	if (m_controlV.size() != 0) {
		for (auto d : m_controlV) {
			// 곡선 제어점 설정: 매개변수 u의 최소값은 0, 최대값은 1,
			// 제어점간의 데이터 개수는 3, 제어점은 4개를 사용
			glMap1f(GL_MAP1_VERTEX_3, 0.0, 1.0, 4, 4, &d.ctrlpoints[0][0]);
			glEnable(GL_MAP1_VERTEX_3);
			// 제어점 사이의 곡선위의 점들을 계산한다. 제어점 사이를 10개로 나누어 그 점들을 연결한다.  곡선위의 점 계산
			glMapGrid1f(10.0, 0.0, 1.0); // 매개변수 0~1 사이를 10개로 나눔
			glEvalMesh1(GL_LINE, 0, 10); // 선분으로 나눈 부분 0~10까지 선으로 그림
			glDisable(GL_MAP1_VERTEX_3);
			// 제어점에 점을 그린다.
			glPointSize(5.0);
			glColor3f(0.0, 0.0, 1.0);
			for (int i = 0; i < m_row; i++) {
				glPushMatrix();
				//glTranslatef(0.0f, 0.0f, m_pointZ[i]);
				glBegin(GL_POINTS);
				glVertex3fv(&m_ctrlpoints[i][0]);
				glEnd();
				glPopMatrix();
			}
		}
		// 제어점에 점을 그린다.
		glPointSize(5.0);
		glColor3f(0.0, 0.0, 1.0);
		for (int i = 0; i < m_row; i++) {
			glPushMatrix();
			//glTranslatef(0.0f, 0.0f, m_pointZ[i]);
			glBegin(GL_POINTS);
			glVertex3fv(&m_ctrlpoints[i][0]);
			glEnd();
			glPopMatrix();
		}
	} 
	else {
		// 제어점에 점을 그린다.
		glPointSize(5.0);
		glColor3f(0.0, 0.0, 1.0);
		
		for (int i = 0; i < m_row; i++) {
			glPushMatrix();
			//glTranslatef(0.0f, 0.0f, m_pointZ[i]);
			glBegin(GL_POINTS);
			glVertex3fv(&m_ctrlpoints[i][0]);
			glEnd();
			glPopMatrix();
		}
	}
	glPopMatrix();


}

