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

	glEnable(GL_TEXTURE_2D);
	// 자동 매핑 설정
	glBindTexture(GL_TEXTURE_2D, TEXTUREMANAGER->GetTexture()[PYRAMID_TEXTURE]);

	glPushMatrix();
	glTranslatef(m_pos.x, m_pos.y, m_pos.z);

	// Render Door
	glPushMatrix();
	glColor3f(m_bodyColor.R, m_bodyColor.G, m_bodyColor.B);

	glBegin(GL_TRIANGLES);
	
	if (CAMERAMANAGER->DoNormalize()) {
		glEnable(GL_NORMALIZE);
		glNormal3f(0.0, 0.0, 1.0);
	}
	//  Front
	glTexCoord2d(0.5f, 1.0f);
	glVertex3f(0.0f, m_size, 0.0f);
	glTexCoord2d(0.0f, 0.0f);
	glVertex3f(-m_size, -m_size, m_size);
	glTexCoord2d(1.0f, 0.0f);
	glVertex3f(m_size, -m_size, m_size);
	
	glEnd();

	glBegin(GL_TRIANGLES);
	if (CAMERAMANAGER->DoNormalize()) {
		glEnable(GL_NORMALIZE);
		glNormal3f(-1.0, 0.0, 0.0);
	}
	// Left
	glTexCoord2d(0.5f, 1.0f);
	glVertex3f(0.0f, m_size, 0.0f);
	glTexCoord2d(0.0f, 0.0f);
	glVertex3f(-m_size, -m_size, m_size);
	glTexCoord2d(1.0f, 0.0f);
	glVertex3f(0.0f, -m_size, -m_size);
	glEnd();

	glBegin(GL_TRIANGLES);
	if (CAMERAMANAGER->DoNormalize()) {
		glEnable(GL_NORMALIZE);
		glNormal3f(1.0, 0.0, 0.0);
	}
	// Right
	glTexCoord2d(0.5f, 1.0f);
	glVertex3f(0.0f, m_size, 0.0f);
	glTexCoord2d(0.0f, 0.0f);
	glVertex3f(0.0f, -m_size, -m_size);
	glTexCoord2d(1.0f, 0.0f);
	glVertex3f(m_size, -m_size, m_size);
	glEnd();
	
	glBegin(GL_TRIANGLES);
	if (CAMERAMANAGER->DoNormalize()) {
		glEnable(GL_NORMALIZE);
		glNormal3f(0.0, 0.0, -1.0);
	}
	
	// Back
	glTexCoord2d(0.5f, 1.0f);
	glVertex3f(-m_size, -m_size, m_size);
	glTexCoord2d(0.0f, 0.0f);
	glVertex3f(0.0f, -m_size, -m_size);
	glTexCoord2d(1.0f, 0.0f);
	glVertex3f(m_size, -m_size, m_size);
	glEnd();

	// Render blue planet
	glPushMatrix();

	glEnable(GL_TEXTURE_GEN_S);
	glEnable(GL_TEXTURE_GEN_T);
	glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP);
	glTexGeni(GL_T, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP);
	glTranslatef((TRACK_RAD * cos(m_planetAngle * PIE / 180)) * 3,
		TRACK_RAD * sin(m_planetAngle * PIE / 180), TRACK_RAD * sin(m_planetAngle * PIE / 180));
	glBindTexture(GL_TEXTURE_2D, TEXTUREMANAGER->GetTexture()[EARTH_TEXTURE]);
	glColor3f(1.0, 1.0, 1.0);
	glutSolidSphere(PLANET_RAD, 30, 30);
	glDisable(GL_TEXTURE_GEN_S);
	glDisable(GL_TEXTURE_GEN_T);
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


	glDisable(GL_TEXTURE_2D);
}