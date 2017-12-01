#include "Define.h"
#include "Objects.h"
#include "Enum.h"

void CFloor::Init()
{

}

void CFloor::Update()
{

}


void CFloor::Render()
{
	glTranslatef(m_pos.x, m_pos.y, m_pos.z);

	glEnable(GL_TEXTURE_2D);
	// 자동 매핑 설정


	glBindTexture(GL_TEXTURE_2D, TEXTUREMANAGER->GetTexture()[FLOOR_TEXTURE]);

	glPushMatrix();
	glScalef(m_scale.x, 0.0f, m_scale.z);
	glBegin(GL_QUADS);
	// Mapping
	// Front
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(CUBE_RAD, CUBE_RAD, 0.0f); // Top Right
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(-CUBE_RAD, CUBE_RAD, 0.0f); // Top Left
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(-CUBE_RAD, -CUBE_RAD, 0.0f); // Bottom Left
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(CUBE_RAD, -CUBE_RAD, 0.0f); // Bottom Right
	glEnd();

	glBegin(GL_QUADS);
	// Back
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(CUBE_RAD, CUBE_RAD, -CUBE_RAD * 2.0f); // Top Right
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(-CUBE_RAD, CUBE_RAD, -CUBE_RAD * 2.0f); // Top Left
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(-CUBE_RAD, -CUBE_RAD, -CUBE_RAD * 2.0f); // Bottom Left
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(CUBE_RAD, -CUBE_RAD, -CUBE_RAD * 2.0f); // Bottom Right
	glEnd();

	glBegin(GL_QUADS);
	// Top
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(CUBE_RAD, CUBE_RAD, -CUBE_RAD * 2.0f); // Top Right
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(-CUBE_RAD, CUBE_RAD, -CUBE_RAD * 2.0f); // Top Left
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(-CUBE_RAD, CUBE_RAD, 0.0f); // Bottom Left
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(CUBE_RAD, CUBE_RAD, 0.0f); // Bottom Right
	glEnd();

	glBegin(GL_QUADS);
	// Bottom
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(CUBE_RAD, -CUBE_RAD, -CUBE_RAD * 2.0f); // Top Right
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(-CUBE_RAD, -CUBE_RAD, -CUBE_RAD * 2.0f); // Top Left
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(-CUBE_RAD, -CUBE_RAD, 0.0f); // Bottom Left
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(CUBE_RAD, -CUBE_RAD, 0.0f); // Bottom Right
	glEnd();

	glBegin(GL_QUADS);
	// Left
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(-CUBE_RAD, CUBE_RAD, 0.0f); // Top Right
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(-CUBE_RAD, CUBE_RAD, -CUBE_RAD * 2.0f); // Top Left
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(-CUBE_RAD, -CUBE_RAD, -CUBE_RAD * 2.0f); // Bottom Left
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(-CUBE_RAD, -CUBE_RAD, 0.0f); // Bottom Right
	glEnd();

	glBegin(GL_QUADS);
	// Right
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(CUBE_RAD, CUBE_RAD, -CUBE_RAD * 2.0f);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(CUBE_RAD, CUBE_RAD, 0.0f);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(CUBE_RAD, -CUBE_RAD, 0.0f);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(CUBE_RAD, -CUBE_RAD, -CUBE_RAD * 2.0f);
	glEnd();
	glPopMatrix();

	glPopMatrix();
	glDisable(GL_TEXTURE_2D);
}