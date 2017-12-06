#include "Define.h"
#include "Objects.h"

void CAirPlane::Init()
{
	m_angle = 0.0f;
	m_propelerRotation.x = 1.0f;
	m_propelerRotation.y = 0.0f;
	m_propelerRotation.z = 0.0f;
	m_proplerAngle = 0.0f;
	this->SetRotation(Vector3(0.0f, 1.0f, 0.0f));

	m_scale = Vector3(2.0f, 1.0f, 1.0f);

}
void CAirPlane::SetTarget(Vector3 target[])
{
	memcpy(m_target, target, sizeof(m_target));
	
	// 목표를 바라보는 방향벡터 생성. 방향벡터를 단위벡터로 만든다
	Vector3 face = target[0] - m_pos;
	Normalize3f(face, face);
	// Up 벡터 생성
	Vector3 up = { 0.0f, 1.0f, 0.0f };
	// 방향 벡터와 up 백터의 내적을 구함
	float theta = Dot3f(up, face);
	theta = acosf(theta);
	float degree = theta * 180.0 / PI;
	// 방향 벡터와 up 벡터의 외적을 구함
	Vector3 cross;
	Cross3f(cross, up, face);
	m_headAngle = degree;
	m_rotation = cross;
	m_idx = 0;

}

bool CAirPlane::DidGetGoal()
{
	// 목표를 바라보는 방향벡터 생성. 방향벡터를 단위벡터로 만든다
	Vector3 face = m_target[m_idx] - m_pos;
	float dist = sqrt(face.x + face.y + face.z);
	dist = abs(dist);
	if (dist == 0 || dist < 1) return true;
	return false;
}

void CAirPlane::Move()
{


	// 목표를 바라보는 방향벡터 생성. 방향벡터를 단위벡터로 만든다
	Vector3 face = m_target[m_idx] - m_pos;

	if (this->DidGetGoal()) return;
	else {
		if (m_idx < 2) m_idx++;
	}


	Normalize3f(face, face);
	// Up 벡터 생성
	Vector3 up = { 0.0f, 1.0f, 0.0f };
	// 방향 벡터와 up 백터의 내적을 구함
	float theta = Dot3f(up, face);
	theta = acosf(theta);
	float degree = theta * 180.0 / PI;
	// 방향 벡터와 up 벡터의 외적을 구함
	Vector3 cross;
	Cross3f(cross, up, face);
	m_headAngle = degree;
	m_rotation = cross;

	face *= 0.5f;
	m_pos += face;

}

void CAirPlane::Update()
{
	if (m_proplerAngle < 360.0f) m_proplerAngle += 10.0f;
	else m_proplerAngle = 0.0f;

	this->Move();


}


void CAirPlane::Render()
{

	glPushMatrix();

	glTranslatef(m_pos.x + m_dPos.x, m_pos.y, m_pos.z + m_dPos.z);
	glRotatef(-90, 0.0f, 0.0f, 1.0f);
	glRotatef(m_headAngle, m_rotation.x, m_rotation.y, m_rotation.z);
	// Render Body
	glPushMatrix();
	glScalef(m_scale.x, m_scale.y, m_scale.z);
	glColor3f(1.0f, 1.0f, 1.0f);
	glutSolidCube(m_size);
	glPopMatrix();

	// Render Propeler
	glPushMatrix();
	glColor3f(1.0f, 1.0f, 1.0f);
	glScalef(0.5f, 0.5f, 3.0f);
	glTranslatef(-m_size * 2.0f, 0.0f, 0.0f);
	glRotatef(m_proplerAngle, m_propelerRotation.x, m_propelerRotation.y, m_propelerRotation.z);
	glutSolidCube(m_size);
	glPopMatrix();

	// Render Right Wing
	glPushMatrix();
	glTranslatef(0.0f, 0.0f, -m_size * m_scale.x);
	glColor3f(1.0f, 1.0f, 1.0f);
	glBegin(GL_TRIANGLES);
	glVertex3f(0.0f, 0.0f, 0.0f);
	glVertex3f(0.0f, 0.0f, 5.0f);
	glVertex3f(-m_size, 0.0f, 5.0f);
	glEnd();
	glPopMatrix();

	// Render Left Wing
	glPushMatrix();
	glTranslatef(0.0f, 0.0f, m_size / 2.0f);
	glColor3f(1.0f, 1.0f, 1.0f);
	glBegin(GL_TRIANGLES);
	glVertex3f(0.0f, 0.0f, 0.0f);
	glVertex3f(0.0f, 0.0f, 5.0f);
	glVertex3f(-m_size, 0.0f, 0.0f);
	glEnd();
	glPopMatrix();

	// Render Cuty Tail
	glPushMatrix();
	glColor3f(1.0f, 0.0f, 0.0f);
	glScalef(1.0f, 0.5f, 0.5f);
	glTranslatef(m_size * 1.5f, 0.0f, 0.0f);
	glutSolidCube(m_size);
	glutSolidCone(m_size, m_size, 25, 25);
	glPopMatrix();

	glPopMatrix();

}