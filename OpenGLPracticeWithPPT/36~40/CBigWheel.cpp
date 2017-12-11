#include "Define.h"
#include "Objects.h"


void CBigWheel::Init()
{
	m_seatSize = m_objInfo.size / 3.0f;
}



void CBigWheel::Update()
{
	if (m_objInfo.rotation.w < 360) m_objInfo.rotation.w++;
	else m_objInfo.rotation.w = 0.0f;
}



void CBigWheel::Render()
{
	glPushMatrix();
	glTranslatef(m_objInfo.pos.x, m_objInfo.pos.y, m_objInfo.pos.z);
	glRotatef(m_objInfo.rotation.w, m_objInfo.rotation.x, m_objInfo.rotation.y, m_objInfo.rotation.z);
	// Render Wheel
	glColor3f(1.0f, 1.0f, 1.0f);
	glutSolidTorus(m_objInfo.size / 15.0f, m_objInfo.size, 50, 50);
	
	// Horizontal
	glPushMatrix();
	glPushMatrix();
	glScalef(m_objInfo.scale.x, m_objInfo.scale.y, m_objInfo.scale.z);
	glutSolidCube(m_objInfo.size);
	glPopMatrix();

	// Right Seat
	glPushMatrix();
	glTranslatef(m_objInfo.pos.x - m_seatSize, 0.0f, 0.0f);
	glRotatef(-m_objInfo.rotation.w, m_objInfo.rotation.x, m_objInfo.rotation.y, m_objInfo.rotation.z);
	glColor3f(0.0f, 0.0f, 1.0f);
	glutSolidCube(m_seatSize);
	glPopMatrix();

	// Left Seat
	glPushMatrix();
	glTranslatef(-m_objInfo.pos.x + m_seatSize, 0.0f, 0.0f);
	glRotatef(-m_objInfo.rotation.w, m_objInfo.rotation.x, m_objInfo.rotation.y, m_objInfo.rotation.z);
	glColor3f(0.0f, 0.0f, 1.0f);
	glutSolidCube(m_seatSize);
	glPopMatrix();
	glPopMatrix();

	// Right Vertical
	glPushMatrix();
	glPushMatrix();
	glRotatef(45.0f, 0.0f, 0.0f, 1.0f);
	glScalef(m_objInfo.scale.x, m_objInfo.scale.y, m_objInfo.scale.z);
	glColor3f(1.0f, 1.0f, 1.0f);
	glutSolidCube(m_objInfo.size);
	glPopMatrix();

	// Right Seat
	glPushMatrix();
	glTranslatef(m_objInfo.pos.x - m_seatSize * 2.5f, m_objInfo.pos.y - m_seatSize * 1.5f, 0.0f);
	glRotatef(-m_objInfo.rotation.w, m_objInfo.rotation.x, m_objInfo.rotation.y, m_objInfo.rotation.z);
	glColor3f(0.0f, 0.0f, 1.0f);
	glutSolidCube(m_seatSize);
	glPopMatrix();

	// Left Seat
	glPushMatrix();
	glTranslatef(-m_objInfo.pos.x + m_seatSize * 2.5f, -m_objInfo.pos.y + m_seatSize * 1.5f, 0.0f);
	glRotatef(-m_objInfo.rotation.w, m_objInfo.rotation.x, m_objInfo.rotation.y, m_objInfo.rotation.z);
	glColor3f(0.0f, 0.0f, 1.0f);
	glutSolidCube(m_seatSize);
	glPopMatrix();
	glPopMatrix();

	// Right Vertical
	glPushMatrix();
	glPushMatrix();
	glRotatef(45.0f, 0.0f, 0.0f, 1.0f);
	glScalef(m_objInfo.scale.x, m_objInfo.scale.y, m_objInfo.scale.z);
	glColor3f(1.0f, 1.0f, 1.0f);
	glutSolidCube(m_objInfo.size);
	glPopMatrix();

	// Right Seat
	glPushMatrix();
	glTranslatef(m_objInfo.pos.x - m_seatSize * 2.5f, m_objInfo.pos.y - m_seatSize * 1.5f, 0.0f);
	glRotatef(-m_objInfo.rotation.w, m_objInfo.rotation.x, m_objInfo.rotation.y, m_objInfo.rotation.z);
	glColor3f(0.0f, 0.0f, 1.0f);
	glutSolidCube(m_seatSize);
	glPopMatrix();

	// Left Seat
	glPushMatrix();
	glTranslatef(-m_objInfo.pos.x + m_seatSize * 2.5f, -m_objInfo.pos.y + m_seatSize * 1.5f, 0.0f);
	glRotatef(-m_objInfo.rotation.w, m_objInfo.rotation.x, m_objInfo.rotation.y, m_objInfo.rotation.z);
	glColor3f(0.0f, 0.0f, 1.0f);
	glutSolidCube(m_seatSize);
	glPopMatrix();
	glPopMatrix();

	// Left Vertical
	glPushMatrix();
	glPushMatrix();
	glRotatef(-45.0f, 0.0f, 0.0f, 1.0f);
	glScalef(m_objInfo.scale.x, m_objInfo.scale.y, m_objInfo.scale.z);
	glColor3f(1.0f, 1.0f, 1.0f);
	glutSolidCube(m_objInfo.size);
	glPopMatrix();

	// Right Seat
	glPushMatrix();
	glTranslatef(m_objInfo.pos.x - m_seatSize * 2.5f, -m_objInfo.pos.y + m_seatSize * 1.5f, 0.0f);
	glRotatef(-m_objInfo.rotation.w, m_objInfo.rotation.x, m_objInfo.rotation.y, m_objInfo.rotation.z);
	glColor3f(0.0f, 0.0f, 1.0f);
	glutSolidCube(m_seatSize);
	glPopMatrix();

	// Left Seat
	glPushMatrix();
	glTranslatef(-m_objInfo.pos.x + m_seatSize * 2.5f, m_objInfo.pos.y - m_seatSize * 1.5f, 0.0f);
	glRotatef(-m_objInfo.rotation.w, m_objInfo.rotation.x, m_objInfo.rotation.y, m_objInfo.rotation.z);
	glColor3f(0.0f, 0.0f, 1.0f);
	glutSolidCube(m_seatSize);
	glPopMatrix();
	glPopMatrix();


	// Vertical
	glPushMatrix();
	glPushMatrix();
	glScalef(m_objInfo.scale.y, m_objInfo.scale.x, m_objInfo.scale.z);
	glColor3f(1.0f, 1.0f, 1.0f);
	glutSolidCube(m_objInfo.size);
	glPopMatrix();

	// Top Seat
	glPushMatrix();
	glTranslatef(0.0f, m_objInfo.pos.y - m_seatSize / 2.0f, 0.0f);
	glRotatef(-m_objInfo.rotation.w, m_objInfo.rotation.x, m_objInfo.rotation.y, m_objInfo.rotation.z);
	glColor3f(0.0f, 0.0f, 1.0f);
	glutSolidCube(m_seatSize);
	glPopMatrix();

	// Bottom Seat
	glPushMatrix();
	glTranslatef(0.0f, -m_objInfo.pos.y + m_seatSize / 2.0f, 0.0f);
	glRotatef(-m_objInfo.rotation.w, m_objInfo.rotation.x, m_objInfo.rotation.y, m_objInfo.rotation.z);
	glColor3f(0.0f, 0.0f, 1.0f);
	glutSolidCube(m_seatSize);
	glPopMatrix();
	glPopMatrix();

	glPopMatrix();
}