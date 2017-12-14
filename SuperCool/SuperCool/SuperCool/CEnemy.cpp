#include "Define.h"
#include "Objects.h"

void CEnemy::Init()
{
	m_speed = 1.0f;
	m_rotate = 0.0f;
}

void CEnemy::LookPlayer()
{
	// 목표를 바라보는 방향벡터 생성. 방향벡터를 단위벡터로 만든다
	Vector3 face = RENDERMANAGER->GetPlayerPos() - m_objInfo.pos;
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
	m_objInfo.rotation.x = cross.x;
	m_objInfo.rotation.y = cross.y;
	m_objInfo.rotation.z = cross.z;
	m_objInfo.rotation.w = degree;
}

void CEnemy::Move(float frameTime)
{
	Vector3 face = RENDERMANAGER->GetPlayerPos() - m_objInfo.pos;
	float dist = sqrt(face.x + face.y + face.z);
	float move = m_speed * frameTime;
	dist = abs(dist);
	if (dist == 0 || dist < 1.0f) return;
	face *= move;
	m_objInfo.pos += face;
}


void CEnemy::Update(float frameTime)
{
	this->LookPlayer();
	this->Move(frameTime);
}

void CEnemy::Render()
{

	glPushMatrix();
	glTranslatef(m_objInfo.pos.x, m_objInfo.pos.y, m_objInfo.pos.z);
	glRotatef(m_objInfo.rotation.w, m_objInfo.rotation.x, m_objInfo.rotation.y, m_objInfo.rotation.z);
	glScalef(0.5, 0.5, 0.4);
	glPushMatrix(); // 몸통
	{
		glColor3f(1.0, 0.0, 1.0);
		glScalef(1.0, 1.5, 1.0);
		glutSolidCube(m_objInfo.size);
	}
	glPopMatrix();

	glPushMatrix(); // 머리
	{
		glTranslatef(0.0, m_objInfo.size, 0.0);

		glPushMatrix(); // 코
		{
			glScalef(0.8, 1.0, 0.8);
			glColor3f(1.0, 1.0, 0.0);
			glutSolidCube(m_objInfo.size);
		}
		glPopMatrix();

		glTranslatef(0.0, m_objInfo.size / 10, m_objInfo.size / 10);
		glColor3f(0.0, 1.0, 1.0);
		glScalef(0.1, 0.1, 1.0);
		glutSolidCube(m_objInfo.size);

	}
	glPopMatrix();

	glPushMatrix(); // 왼쪽 팔
	{
		glTranslatef(-m_objInfo.size * 0.65, 0.0, 0.0);
		glColor3f(1.0, 0.0, 0.0);
		glTranslatef(0.0, 0.7, 0.0);
		//glRotatef(m_rotate, 1.0, 0.0, 0.0);
		glTranslatef(0.0, -0.7, 0.0);
		glScalef(0.3, 0.7, 0.3);

		glutSolidCube(m_objInfo.size);

	}
	glPopMatrix();

	glPushMatrix(); // 오른쪽 팔
	{
		glTranslatef(m_objInfo.size * 0.65, 0.0, 0.0);
		glTranslatef(0.0, 0.7, 0.0);
		//glRotatef(-m_rotate, 1.0, 0.0, 0.0);
		glTranslatef(0.0, -0.7, 0.0);
		glScalef(0.3, 0.7, 0.3);
		glColor3f(0.0, 0.0, 1.0);
		glutSolidCube(m_objInfo.size);
	}
	glPopMatrix();

	glPushMatrix(); // 왼 다리 ( 오른 팔이랑 같은 색 )
	{
		glTranslatef(-m_objInfo.size * 0.2, -m_objInfo.size, 0.0);
		glTranslatef(0.0, m_objInfo.size * 0.6, 0.0);
		//glRotatef(-m_rotate, 1.0, 0.0, 0.0);
		glTranslatef(0.0, -m_objInfo.size * 0.6, 0.0);
		glScalef(0.3, 0.6, 0.3);
		glColor3f(0.0, 0.0, 1.0);
		glutSolidCube(m_objInfo.size);
	}
	glPopMatrix();

	glPushMatrix(); // 오른 다리 ( 왼 팔이랑 같은 색 )
	{
		glTranslatef(m_objInfo.size * 0.2, -m_objInfo.size, 0.0);
		glTranslatef(0.0, m_objInfo.size * 0.6, 0.0);
		//glRotatef(m_rotate, 1.0, 0.0, 0.0);
		glTranslatef(0.0, -m_objInfo.size * 0.6, 0.0);
		glScalef(0.3, 0.6, 0.3);
		glColor3f(1.0, 0.0, 0.0);
		glutSolidCube(m_objInfo.size);
	}
	glPopMatrix();

	glPopMatrix();


}
