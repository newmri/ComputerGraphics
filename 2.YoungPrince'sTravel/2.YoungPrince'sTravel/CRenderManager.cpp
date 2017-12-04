#include "Define.h"

CRenderManager* CRenderManager::m_instance = nullptr;


void CRenderManager::Init()
{
	CAMERAMANAGER->SetViewMatrix(&m_view);
	m_perspective.Fovy = PERSPEVTIVE_FOVY;
	m_perspective.Near = PERSPEVTIVE_NEAR;
	m_perspective.Far = PERSPEVTIVE_FAR;
	CAMERAMANAGER->LookAt(Vector3(0.0f, 0.0f, 0.0f), Vector3(30.0f, 0.0f, 90.0f), true);
	m_row = 0;
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






void CRenderManager::Render()
{

	
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
				glTranslatef(0.0f, 0.0f, m_pointZ[i]);
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
			glTranslatef(0.0f, 0.0f, m_pointZ[i]);
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
			glTranslatef(0.0f, 0.0f, m_pointZ[i]);
			glBegin(GL_POINTS);
			glVertex3fv(&m_ctrlpoints[i][0]);
			glEnd();
			glPopMatrix();
		}
	}
	glPopMatrix();


}

