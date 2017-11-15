#include "Define.h"
#include "Objects.h"

void CFloor::Init()
{
	float leftCtrlPoints[3][3][3] = { { { -40.0, 0.0, 40.0 },{ -20.0, 0.0, 40.0 },{ 0.0, 0.0, 40.0 } },
								{ { -40.0, 0.0, 0.0 },{ -20.0, 0.0, 0.0 },{ 0.0, 0.0, 0.0 } },
								{ { -40.0, 0.0, -40.0 },{ -20.0, 0.0, -40.0 },{ 0.0, 0.0, -40.0 } } };

	float rightCtrlPoints[3][3][3] = { { { 0.0, 0.0, 40.0 },{ 20.0, 0.0, 40.0 },{ 40.0, 0.0, 40.0 } },
										{ { 0.0, 0.0, 0.0 },{ 20.0, 0.0, 0.0 },{ 40.0, 0.0, 0.0 } },
										{ { 0.0, 0.0, -40.0 },{ 20.0, 0.0, -40.0 },{ 40.0, 0.0, -40.0 } } };

	memcpy(&m_leftCtrlPoints, &leftCtrlPoints, sizeof(leftCtrlPoints));
	memcpy(&m_rightCtrlPoints, &rightCtrlPoints, sizeof(rightCtrlPoints));

	m_incre[0] = 1.0f;
	m_incre[1] = -1.0f;

}

void CFloor::Update()
{

}

void CFloor::ChangeControlPoint(int key)
{
	if (key == GLUT_KEY_RIGHT) {
		for (int h = 0; h < 3; ++h) {
			m_leftCtrlPoints[h][1][0] += m_incre[0];
			m_rightCtrlPoints[h][1][0] += m_incre[0];
			m_leftCtrlPoints[h][1][1] += m_incre[1];
			m_rightCtrlPoints[h][1][1] += m_incre[0];

			if (m_rightCtrlPoints[h][1][1] >= 15.0f || m_rightCtrlPoints[h][1][1] <= -15.0f) {
				m_incre[0] = -m_incre[0];
				m_incre[1] = -m_incre[1];
			}
		}

	}

}
void CFloor::Render()
{
	glTranslatef(m_pos.x, m_pos.y, m_pos.z);

	glPushMatrix();

	// 곡면 제어점 설정
	glMap2f(GL_MAP2_VERTEX_3, 0.0, 1.0, 3, 3, 0.0, 1.0, 9, 3, &m_leftCtrlPoints[0][0][0]);
	glEnable(GL_MAP2_VERTEX_3);
	// 그리드를 이용한 곡면 드로잉
	glColor3f(m_bodyColor.R, m_bodyColor.G, m_bodyColor.B);
	glMapGrid2f(100, 0.0, 1.0, 100, 0.0, 1.0);
	// 선을 이용하여 그리드 연결
	glEvalMesh2(GL_LINE, 0, 100, 0, 100);



	// 곡면 제어점 설정
	glMap2f(GL_MAP2_VERTEX_3, 0.0, 1.0, 3, 3, 0.0, 1.0, 9, 3, &m_rightCtrlPoints[0][0][0]);
	glEnable(GL_MAP2_VERTEX_3);
	// 그리드를 이용한 곡면 드로잉
	glColor3f(m_bodyColor.R, m_bodyColor.G, m_bodyColor.B);
	glMapGrid2f(100, 0.0, 1.0, 100, 0.0, 1.0);
	// 선을 이용하여 그리드 연결
	glEvalMesh2(GL_LINE, 0, 100, 0, 100);

	glPopMatrix();
}