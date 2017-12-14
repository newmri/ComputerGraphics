#include "Define.h"
#include "Objects.h"

void CEnemy::Init()
{
	m_speed = 1.0f;
	m_rotate = 0.0f;
}

void CEnemy::LookPlayer()
{
	// ��ǥ�� �ٶ󺸴� ���⺤�� ����. ���⺤�͸� �������ͷ� �����
	Vector3 face = RENDERMANAGER->GetPlayerPos() - m_objInfo.pos;
	Normalize3f(face, face);
	// Up ���� ����
	Vector3 up = { 0.0f, 1.0f, 0.0f };
	// ���� ���Ϳ� up ������ ������ ����
	float theta = Dot3f(up, face);
	theta = acosf(theta);
	float degree = theta * 180.0 / PI;
	// ���� ���Ϳ� up ������ ������ ����
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
	glPushMatrix(); // ����
	{
		glColor3f(1.0, 0.0, 1.0);
		glScalef(1.0, 1.5, 1.0);
		glutSolidCube(m_objInfo.size);
	}
	glPopMatrix();

	glPushMatrix(); // �Ӹ�
	{
		glTranslatef(0.0, m_objInfo.size, 0.0);

		glPushMatrix(); // ��
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

	glPushMatrix(); // ���� ��
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

	glPushMatrix(); // ������ ��
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

	glPushMatrix(); // �� �ٸ� ( ���� ���̶� ���� �� )
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

	glPushMatrix(); // ���� �ٸ� ( �� ���̶� ���� �� )
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
