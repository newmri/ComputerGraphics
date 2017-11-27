#include "Define.h"
#include "Objects.h"

void CPyramid::Init()
{

	m_doorScale.x = m_scale.y;
	m_doorScale.y = m_scale.x;
	m_doorScale.z = m_scale.z;
	m_yDist = m_doorScale.x;

	m_doorIncre = 0.1f;
	m_doorPosIncre = -0.25f;

	m_planetAngle = 0.0f;
	m_moonAngle = 90.0f;

}


void CPyramid::Update()
{

	if (m_planetAngle < 360.0f) m_planetAngle += CAMERA_SPEED;
	else m_planetAngle = 0.0f;

	if (m_moonAngle < 360.0f) m_moonAngle += CAMERA_SPEED * 4.0f;
	else m_moonAngle = 0.0f;
}

void CPyramid::Render()
{

	glPushMatrix();
	glTranslatef(m_pos.x, m_pos.y, m_pos.z);


	// Render Door
	glPushMatrix();
	glColor3f(m_bodyColor.R, m_bodyColor.G, m_bodyColor.B);

	glBegin(GL_TRIANGLES);
	//  Front
	glVertex3f(0.0f, m_size, 0.0f);
	glVertex3f(-m_size, -m_size, m_size);
	glVertex3f(m_size, -m_size, m_size);
	
	// Left
	glVertex3f(0.0f, m_size, 0.0f);
	glVertex3f(-m_size, -m_size, m_size);
	glVertex3f(0.0f, -m_size, -m_size);
	
	// Right
	glVertex3f(0.0f, m_size, 0.0f);
	glVertex3f(0.0f, -m_size, -m_size);
	glVertex3f(m_size, -m_size, m_size);

	// Back
	glVertex3f(-m_size, -m_size, m_size);
	glVertex3f(0.0f, -m_size, -m_size);
	glVertex3f(m_size, -m_size, m_size);
	glEnd();

	// Render blue planet
	glPushMatrix();

	glTranslatef((TRACK_RAD * cos(m_planetAngle * PIE / 180)) * 3,
		TRACK_RAD * sin(m_planetAngle * PIE / 180), TRACK_RAD * sin(m_planetAngle * PIE / 180));

	glutSolidSphere(PLANET_RAD, 30, 30);

	// Render moon track
	glPushMatrix();


	// Render moon
	glColor3f(1.0f, 1.0f, 0.0f);
	glTranslatef((MOON_TRACK_RAD * cos(m_moonAngle * PIE / 180)) * 3,
		MOON_TRACK_RAD * sin(m_moonAngle * PIE / 180),
		-(MOON_TRACK_RAD * sin(m_moonAngle * PIE / 180)));

	glutSolidSphere(MOON_RAD, 30, 30);

	glPopMatrix();

	glPopMatrix();

	glPopMatrix();
	glPopMatrix();



}