#include "Objects.h"

void CPlanet::Init()
{
	m_precision = 100;

	if (m_objType == EARTH) { m_textureNum = 0; return; }
	// 2 ~ 7
	m_textureNum = rand() % (TEXTURE_NUM - 5 + 1) + 2;
	if (rand() % 4 == 0) {
		m_rotate = true;
		SetRotation(Vector3(0.0f, 1.0f, 0.0f));
	}

}

void CPlanet::Update()
{
	if(m_rotate) this->Rotate();
}

void CPlanet::Render()
{
	glPushMatrix();
	glEnable(GL_TEXTURE_2D);

	glMatrixMode(GL_TEXTURE);
	glLoadIdentity();
	if (m_pos.z > 0) {
		glTranslatef(-m_pos.x, -m_pos.y, -m_pos.z);
		glRotatef(m_angle, m_rotation.x, m_rotation.y, m_rotation.z);
		glTranslatef(m_pos.x, m_pos.y, m_pos.z);
	}
	else {
		glTranslatef(m_pos.x, m_pos.y, m_pos.z);
		glRotatef(m_angle, m_rotation.x, m_rotation.y, m_rotation.z);
		glTranslatef(-m_pos.x, -m_pos.y, -m_pos.z);
	}
	glMatrixMode(GL_MODELVIEW);


	glBindTexture(GL_TEXTURE_2D, TEXTUREMANAGER->GetTexture(m_textureNum));


	/*
	Create a sphere centered at c, with radius r, and precision n
	Draw a point for zero radius spheres
	*/
	double theta1, theta2, theta3;
	Vector3 e, p;


	if (m_size < 0) m_size = -m_size;
	if (m_precision < 4 || m_size <= 0) {
		glBegin(GL_POINTS);
		glVertex3f(m_pos.x, m_pos.y, m_pos.z);
		glEnd();
		return;
	}

	for (int j = 0; j < m_precision / 2; j++) {

		theta1 = j * TWOPI / m_precision - PID2;
		theta2 = (j + 1) * TWOPI / m_precision - PID2;

		glBegin(GL_QUAD_STRIP);
		for (int i = 0; i <= m_precision; i++) {
			theta3 = i * TWOPI / m_precision;

			e.x = cos(theta2) * cos(theta3);
			e.y = sin(theta2);
			e.z = cos(theta2) * sin(theta3);
			p.x = m_pos.x + m_size * e.x;
			p.y = m_pos.y + m_size * e.y;
			p.z = m_pos.z + m_size * e.z;

			glNormal3f(e.x, e.y, e.z);
			glTexCoord2f(i / (double)m_precision, 2 * (j + 1) / (double)m_precision);
			glVertex3f(p.x, p.y, p.z);

			e.x = cos(theta1) * cos(theta3);
			e.y = sin(theta1);
			e.z = cos(theta1) * sin(theta3);
			p.x = m_pos.x + m_size * e.x;
			p.y = m_pos.y + m_size * e.y;
			p.z = m_pos.z + m_size * e.z;

			glNormal3f(e.x, e.y, e.z);
			glTexCoord2f(i / (double)m_precision, 2 * j / (double)m_precision);
			glVertex3f(p.x, p.y, p.z);
		}
		glEnd();
	}

	glDisable(GL_TEXTURE_2D);
	// Draw Marker
	if (m_objType == EARTH) {
		if (m_pos.x > 0) glTranslatef(m_pos.x, m_pos.y + m_size + HOUSE_RAD * 4.0f, m_pos.z);
		else glTranslatef(m_pos.x, m_pos.y + m_size + 3, m_pos.z);
		glColor3f(m_color.R, m_color.G, m_color.B);
		glBegin(GL_QUADS);
		glVertex3f(1.0f, -1.0f, 0.0f);
		glVertex3f(-1.0f, -1.0f, 0.0f);
		glVertex3f(-1.0f, 1.0f, 0.0f);
		glVertex3f(1.0f, 1.0f, 0.0f);
		glEnd();
		glBegin(GL_TRIANGLES);
		glVertex3f(0.0f, -3.0f, 0.0f);
		glVertex3f(-2.0f, 0.0f, 0.0f);
		glVertex3f(2.0f, 0.0f, 0.0f);
		glEnd();
	}
	glPopMatrix();

	
}