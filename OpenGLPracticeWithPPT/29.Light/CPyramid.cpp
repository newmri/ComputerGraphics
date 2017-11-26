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



	glPushMatrix();
	glTranslatef(m_pos.x, m_pos.y, m_pos.z);

	// Render Door
	glPushMatrix();
	glColor3f(m_bodyColor.R, m_bodyColor.G, m_bodyColor.B);

	// Front
	glBegin(GL_TRIANGLES);
	glVertex3f(m_size + m_pos.x, m_pos.y - m_size, 0.0f);
	glVertex3f(m_pos.x - m_size, m_pos.y - m_size, 0.0f);
	glVertex3f(m_pos.x, m_pos.y + m_size, -m_size / 2.0f);
	glEnd();

	// Left
	glPushMatrix();
	glTranslatef(-m_size, 0.0f, -m_size);
	glRotatef(90.0f, 0.0f, 1.0f, 0.0f);
	glBegin(GL_TRIANGLES);
	glVertex3f(m_size / 2.0f + m_pos.x, m_pos.y - m_size, 0.0f);
	glVertex3f(m_pos.x - m_size, m_pos.y - m_size, 0.0f);
	glVertex3f(m_pos.x - m_size / 2.0f, m_pos.y + m_size, m_size);
	glEnd();
	glPopMatrix();

	// Back
	glBegin(GL_TRIANGLES);
	glVertex3f(m_size + m_pos.x, m_pos.y - m_size, -m_size * 1.5f);
	glVertex3f(m_pos.x - m_size, m_pos.y - m_size, -m_size * 1.5f);
	glVertex3f(m_pos.x, m_pos.y + m_size, -m_size / 2.0f);
	glEnd();

	// Right
	glPushMatrix();
	glTranslatef(m_size, 0.0f, -m_size);
	glRotatef(-90.0f, 0.0f, 1.0f, 0.0f);
	glBegin(GL_TRIANGLES);
	glVertex3f(m_pos.x - m_size / 2.0f, m_pos.y - m_size, 0.0f);
	glVertex3f(m_pos.x + m_size, m_pos.y - m_size, 0.0f);
	glVertex3f(m_pos.x + m_size / 2.0f, m_pos.y + m_size, m_size);
	glEnd();
	glPopMatrix();




	// Render track
	glPushMatrix();
	/*
	glScalef(3.0f, 1.0f, 1.0f);
	glColor3f(1.0f / RGB, 0.0f, 1.0f);
	glBegin(GL_POINTS);
	for (int i = 0; i < 360; i += 10) {
		double angle = (i * PIE / 180);
		double x = TRACK_RAD * cos(angle);
		double y = TRACK_RAD * sin(angle);
		glVertex2f(x, y);
	}
	glEnd();
	*/
	glPopMatrix();

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
	glPopMatrix();


}