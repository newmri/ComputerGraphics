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
		//m_objPos = m_objPos + Offset;

	}
}


void CRenderManager::SelectObject(int x, int y)
{
	/*
	Point rayOri;
	Vector rayDir;
	calcRay(x, y, &rayOri, &rayDir);
	float t;
	for (auto d : m_v) {
		Point p;
		p.p[0] = d.pos.x;
		p.p[1] = d.pos.y;
		p.p[2] = d.pos.z;
		if (interSection(rayOri, rayDir, p, d.size, &t)) cout << "Click" << endl;
	}
	*/
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
	cout << -posZ << endl;
	/*
	y = m_height - 1 - y;



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

		cout << "Click: " << tv.z << endl;
		*/
	
	
}


void CRenderManager::Render()
{

	glCallList(objects);
	
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
	glInitNames();

	for (auto d : m_v) {
		glPushMatrix();
		glColor3f(d.color.r, d.color.g, d.color.b);
		glRotatef(d.rotation.w, d.rotation.x, d.rotation.y, d.rotation.z);
		glTranslatef(d.pos.x, d.pos.y, d.pos.z);
		glScalef(d.scale.x, d.scale.y, d.scale.z);
		if(d.objType == CUBE) glutSolidCube(d.size);
		else glutSolidSphere(d.size, 25, 25);
		glPopMatrix();
	}
	

}

void CRenderManager::AddObject(Object obj)
{
	m_v.push_back(obj);

	//glMatrixMode(GL_MODELVIEW);
	//glLoadMatrixf(&m_view);
	//glTranslatef(Objects[i].Position.x, Objects[i].Position.y, Objects[i].Position.z);
	/*
	y = m_height - 1 - y;


	float s = (float)x / (float)(m_width - 1);
	float t = (float)y / (float)(m_height - 1);

	Vector4 Point = GetViewMatrixInverse(m_view) * (m_projectionBiasInverse * Vector4(s, t, 0.1f, 1.0f));
	Point /= Point.w;


	Vector3 ray;
	
	Normalize3f(ray, Point - CAMERAMANAGER->GetPos());
	
	float NdotR = -Dot3f(m_planeNormal, ray);

	if (NdotR != 0.0f)
	{
		float Distance = (Dot3f(m_planeNormal, CAMERAMANAGER->GetPos()) + m_planeD) / NdotR;
		Vector3 Point = ray * Distance + CAMERAMANAGER->GetPos();

		Vector3 Offset = Point - m_selectedPoint;

		m_selectedPoint = Point;
		//m_objPos = m_objPos + Offset;

	}
	

	Vector3 tv(Point.x, Point.y, Point.z);
	//m_v.push_back(tv);
	*/
	

}