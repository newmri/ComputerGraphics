#include "Objects.h"

void CCube::Init()
{

}

void CCube::Update()
{

}

void CCube::Render()
{
	glPushMatrix();

	glTranslatef(m_pos.x, m_pos.y, m_pos.z);
	glColor3f(1.0, 1.0, 0.0);
	glutWireCube(m_size);
	// Back
	glEnable(GL_BLEND);
	glBlendFunc(GL_ONE, GL_ZERO);
	glColor4f(0.0, 0.0, 0.0,0.1);
	glBegin(GL_QUADS);
	glVertex3f(m_size / 2, m_size / 2, -m_size / 2);
	glVertex3f(-m_size / 2, m_size / 2, -m_size / 2);
	glVertex3f(-m_size / 2, -m_size / 2, -m_size / 2);
	glVertex3f(m_size / 2, -m_size / 2, -m_size / 2);
	glEnd();

	// Right
	//glEnable(GL_BLEND);
	glBlendFunc(GL_ONE, GL_ZERO);
	glColor4f(0.0, 0.0, 0.0, 0.1);
	glBegin(GL_QUADS);
	glVertex3f(m_size / 2, m_size / 2, m_size / 2);
	glVertex3f(m_size / 2, m_size / 2, -m_size / 2);
	glVertex3f(m_size / 2, -m_size / 2, -m_size / 2);
	glVertex3f(m_size / 2, -m_size / 2, m_size / 2);

	// Left
	//glEnable(GL_BLEND);
	glBlendFunc(GL_ONE, GL_ZERO);
	glColor4f(0.0, 0.0, 0.0, 0.1);
	glBegin(GL_QUADS);
	glVertex3f(-m_size / 2, m_size / 2, m_size / 2);
	glVertex3f(-m_size / 2, m_size / 2, -m_size / 2);
	glVertex3f(-m_size / 2, -m_size / 2, -m_size / 2);
	glVertex3f(-m_size / 2,-m_size / 2, m_size / 2);
	glEnd();


	// Top
	//glEnable(GL_BLEND);
	glBlendFunc(GL_ONE, GL_ZERO);
	glColor4f(0.0, 0.0, 0.0, 0.1);
	glBegin(GL_QUADS);
	glVertex3f(m_size / 2, m_size / 2, -m_size / 2);
	glVertex3f(-m_size / 2, m_size / 2, -m_size / 2);
	glVertex3f(-m_size / 2, m_size / 2, m_size / 2);
	glVertex3f(m_size / 2, m_size / 2, m_size / 2);
	glEnd();

	// Bottom
	//glEnable(GL_BLEND);
	glBlendFunc(GL_ONE, GL_ZERO);
	glColor4f(0.0, 0.0, 0.0, 0.1);
	glBegin(GL_QUADS);
	glVertex3f(m_size / 2, -m_size / 2, -m_size / 2);
	glVertex3f(-m_size / 2, -m_size / 2, -m_size / 2);
	glVertex3f(-m_size / 2, -m_size / 2, m_size / 2);
	glVertex3f(m_size / 2, -m_size / 2, m_size / 2);

	glEnd();
	glDisable(GL_BLEND);
	glPopMatrix();


	// Render House
	glPushMatrix();
	glTranslatef(CUBE_SIZE / 2.0f - EARTH_RAD , -CUBE_SIZE / 2.0f + (EARTH_RAD * 2 + HOUSE_RAD), -CUBE_SIZE / 2.0f + EARTH_RAD * 2.0f);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, TEXTUREMANAGER->GetTexture(HOUSE_FRONT));
	glBegin(GL_QUADS);
	// Mapping
	// Front
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(HOUSE_RAD, HOUSE_RAD, 0.0f); // Top Right
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(-HOUSE_RAD, HOUSE_RAD, 0.0f); // Top Left
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(-HOUSE_RAD, -HOUSE_RAD, 0.0f); // Bottom Left
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(HOUSE_RAD, -HOUSE_RAD, 0.0f); // Bottom Right
	glEnd();

	glBindTexture(GL_TEXTURE_2D, TEXTUREMANAGER->GetTexture(HOUSE_SIDE));
	glBegin(GL_QUADS);
	// Back
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(HOUSE_RAD, HOUSE_RAD, -HOUSE_RAD * 2.0f); // Top Right
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(-HOUSE_RAD, HOUSE_RAD, -HOUSE_RAD * 2.0f); // Top Left
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(-HOUSE_RAD, -HOUSE_RAD, -HOUSE_RAD * 2.0f); // Bottom Left
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(HOUSE_RAD, -HOUSE_RAD, -HOUSE_RAD * 2.0f); // Bottom Right
	glEnd();

	glBindTexture(GL_TEXTURE_2D, TEXTUREMANAGER->GetTexture(HOUSE_SIDE));
	glBegin(GL_QUADS);
	// Top
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(HOUSE_RAD, HOUSE_RAD, -HOUSE_RAD * 2.0f); // Top Right
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(-HOUSE_RAD, HOUSE_RAD, -HOUSE_RAD * 2.0f); // Top Left
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(-HOUSE_RAD, HOUSE_RAD, 0.0f); // Bottom Left
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(HOUSE_RAD, HOUSE_RAD, 0.0f); // Bottom Right
	glEnd();

	glBindTexture(GL_TEXTURE_2D, TEXTUREMANAGER->GetTexture(HOUSE_SIDE));
	glBegin(GL_QUADS);
	// Bottom
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(HOUSE_RAD, -HOUSE_RAD, -HOUSE_RAD * 2.0f); // Top Right
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(-HOUSE_RAD, -HOUSE_RAD, -HOUSE_RAD * 2.0f); // Top Left
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(-HOUSE_RAD, -HOUSE_RAD, 0.0f); // Bottom Left
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(HOUSE_RAD, -HOUSE_RAD, 0.0f); // Bottom Right
	glEnd();

	glBindTexture(GL_TEXTURE_2D, TEXTUREMANAGER->GetTexture(HOUSE_SIDE));
	glBegin(GL_QUADS);
	// Left
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(-HOUSE_RAD, HOUSE_RAD, 0.0f); // Top Right
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(-HOUSE_RAD, HOUSE_RAD, -HOUSE_RAD * 2.0f); // Top Left
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(-HOUSE_RAD, -HOUSE_RAD, -HOUSE_RAD * 2.0f); // Bottom Left
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(-HOUSE_RAD, -HOUSE_RAD, 0.0f); // Bottom Right
	glEnd();

	glBindTexture(GL_TEXTURE_2D, TEXTUREMANAGER->GetTexture(HOUSE_SIDE));
	glBegin(GL_QUADS);
	// Right
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(HOUSE_RAD, HOUSE_RAD, -HOUSE_RAD * 2.0f);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(HOUSE_RAD, HOUSE_RAD, 0.0f);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(HOUSE_RAD, -HOUSE_RAD, 0.0f);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(HOUSE_RAD, -HOUSE_RAD, -HOUSE_RAD * 2.0f);
	glEnd();

	glDisable(GL_TEXTURE_2D);
	glPopMatrix();
}