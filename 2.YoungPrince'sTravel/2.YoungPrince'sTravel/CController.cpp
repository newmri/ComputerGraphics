#include "Objects.h"

void CController::Init()
{
	ZeroMemory(&m_x, sizeof(m_x));
	ZeroMemory(&m_y, sizeof(m_x));
	ZeroMemory(&m_z, sizeof(m_x));
	m_x.y = -CUBE_SIZE / 2.0f + EARTH_RAD / 2.0f;
	m_x.z = CUBE_SIZE / 2.0f - EARTH_RAD;

	m_y.x = -CUBE_SIZE / 2.0f + EARTH_RAD / 2.0f;
	m_y.z = CUBE_SIZE / 2.0f - EARTH_RAD; 

	m_z.x = -CUBE_SIZE / 2.0f + EARTH_RAD / 2.0f;
	m_z.y = -CUBE_SIZE / 2.0f + EARTH_RAD / 2.0f;
}


void CController::Move(char dir)
{
	switch (dir) {
	case '6': m_x.x += CONTROLLER_SPEED;  m_y.x += CONTROLLER_SPEED; m_z.x += CONTROLLER_SPEED; break; // Right
	case '4': m_x.x -= CONTROLLER_SPEED;  m_y.x -= CONTROLLER_SPEED; m_z.x -= CONTROLLER_SPEED; break; // Left
	case '8': m_x.y += CONTROLLER_SPEED;  m_y.y += CONTROLLER_SPEED; m_z.y += CONTROLLER_SPEED; break; // Up
	case '2': m_x.y -= CONTROLLER_SPEED;  m_y.y -= CONTROLLER_SPEED; m_z.y -= CONTROLLER_SPEED; break; // Down
	case '7': m_x.z -= CONTROLLER_SPEED;  m_y.z -= CONTROLLER_SPEED; m_z.z -= CONTROLLER_SPEED; break; // - Z
	case '1': m_x.z += CONTROLLER_SPEED;  m_y.z += CONTROLLER_SPEED; m_z.z += CONTROLLER_SPEED; break; // + Z
	}
}

void CController::Update()
{
	
}

void CController::Render()
{
	// Draw X Line
	glPushMatrix();
	glTranslatef(m_x.x, m_x.y, m_x.z);
	glColor3f(0.0f, 0.0f, 1.0f);
	glBegin(GL_LINES);
	glVertex3f(CUBE_SIZE / 2.0f, 0.0f, 0.0f);
	glVertex3f(-CUBE_SIZE / 2.0f, 0.0f, 0.0f);
	glEnd();
	glPopMatrix();

	// Draw Y Line
	glPushMatrix();
	glTranslatef(m_y.x, m_y.y, m_y.z);
	glColor3f(0.0f, 1.0f, 0.0f);
	glBegin(GL_LINES);
	glVertex3f(0.0f, CUBE_SIZE / 2.0f, 0.0f);
	glVertex3f(0.0f, -CUBE_SIZE / 2.0f, 0.0f);
	glEnd();
	glPopMatrix();

	// Draw Z Line
	glPushMatrix();
	glTranslatef(m_z.x, m_z.y, m_z.z);
	glColor3f(1.0f, 0.0f, 0.0f);
	glBegin(GL_LINES);
	glVertex3f(0.0f, 0.0f, CUBE_SIZE / 2.0f);
	glVertex3f(0.0f, 0.0f, -CUBE_SIZE / 2.0f);
	glEnd();
	glPopMatrix();
}