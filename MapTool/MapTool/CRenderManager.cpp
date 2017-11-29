#include "Define.h"

CRenderManager* CRenderManager::m_instance = nullptr;

void CRenderManager::Init()
{
	CAMERAMANAGER->SetViewMatrix(&m_view);
	m_perspective.Fovy = PERSPEVTIVE_FOVY;
	m_perspective.Near = PERSPEVTIVE_NEAR;
	m_perspective.Far = PERSPEVTIVE_FAR;
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

	if (NdotR != 0.0f)
	{
		float Distance = (Dot3f(m_planeNormal, CAMERAMANAGER->GetPos()) + m_planeD) / NdotR;
		Vector3 Point = ray * Distance + CAMERAMANAGER->GetPos();

		Vector3 Offset = Point - m_selectedPoint;

		m_selectedPoint = Point;

		m_objPos = m_objPos + Offset;

	}
}

void CRenderManager::SelectObject(int x, int y)
{
	y = m_height - 1 - y;

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


		float s = (float)x / (float)(m_width - 1);
		float t = (float)y / (float)(m_height - 1);

		float Depth;

		glReadPixels(x, y, 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT, &Depth);

		Vector4 Point = GetViewMatrixInverse(m_view) * (m_projectionBiasInverse * Vector4(s, t, Depth, 1.0f));
		Point /= Point.w;

		Vector3 tv (Point.x, Point.y, Point.z);
		m_selectedPoint = tv;

		float omcospi4 = 1.0f - cos((float)PIE / 4.0f);

		if (CAMERAMANAGER->GetZ().y > -omcospi4 && CAMERAMANAGER->GetZ().y < omcospi4)
		{
			Normalize3f(m_planeNormal,Vector3(CAMERAMANAGER->GetZ().x, 0.0f, CAMERAMANAGER->GetZ().z));
		}
		else
		{
			m_planeNormal = Vector3(0.0f, 1.0f, 0.0f);
		}

		m_planeD = -Dot3f(m_planeNormal, m_selectedPoint);
	
}


void CRenderManager::Render()
{
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
		glVertex3f(i, 0.0f, -d);
		glVertex3f(i, 0.0f, d);
		glVertex3f(-d, 0.0f, i);
		glVertex3f(d, 0.0f, i);
	}

	glEnd();
}