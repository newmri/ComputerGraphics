#include "Define.h"
#include "Objects.h"

void CCube::Init()
{
	this->SetRotation(Vector3{ 0.0f, 0.0f, 1.0f });
}

void CCube::Move()
{

}

void CCube::Update()
{

}

void CCube::Render()
{
	glPushMatrix();
	// Draw Cube
	glBegin(GL_QUADS);

	// Back
	glColor3f(1.0f, 1.0f, 1.0f);
	glVertex3f(CUBE_RAD, CUBE_RAD, -CUBE_RAD * 2.0f); // Top Right
	glVertex3f(-CUBE_RAD, CUBE_RAD, -CUBE_RAD * 2.0f); // Top Left
	glVertex3f(-CUBE_RAD, -CUBE_RAD, -CUBE_RAD * 2.0f); // Bottom Left
	glVertex3f(CUBE_RAD, -CUBE_RAD, -CUBE_RAD * 2.0f); // Bottom Right


													   // Top
	glColor3f(1.0f, 0.0f, 0.0f);
	glVertex3f(CUBE_RAD, CUBE_RAD, -CUBE_RAD * 2.0f); // Top Right
	glVertex3f(-CUBE_RAD, CUBE_RAD, -CUBE_RAD * 2.0f); // Top Left
	glVertex3f(-CUBE_RAD, CUBE_RAD, -0.0f); // Bottom Left
	glVertex3f(CUBE_RAD, CUBE_RAD, -0.0f); // Bottom Right

										   // Bottom
	glColor3f(1.0f, 1.0f, 0.0f);
	glVertex3f(CUBE_RAD, -CUBE_RAD, -CUBE_RAD * 2.0f); // Top Right
	glVertex3f(-CUBE_RAD, -CUBE_RAD, -CUBE_RAD * 2.0f); // Top Left
	glVertex3f(-CUBE_RAD, -CUBE_RAD, 0.0f); // Bottom Left
	glVertex3f(CUBE_RAD, -CUBE_RAD, 0.0f); // Bottom Right

										   // Left
	glColor3f(1.0f, 0.0f, 1.0f);
	glVertex3f(-CUBE_RAD, CUBE_RAD, 0.0f); // Top Right
	glVertex3f(-CUBE_RAD, CUBE_RAD, -CUBE_RAD * 2.0f); // Top Left
	glVertex3f(-CUBE_RAD, -CUBE_RAD, -CUBE_RAD * 2.0f); // Bottom Left
	glVertex3f(-CUBE_RAD, -CUBE_RAD, 0.0f); // Bottom Right

											// Right
	glColor3f(0.0f, 0.0f, 1.0f);
	glVertex3f(CUBE_RAD, CUBE_RAD, -CUBE_RAD * 2.0f);
	glVertex3f(CUBE_RAD, CUBE_RAD, 0.0f);
	glVertex3f(CUBE_RAD, -CUBE_RAD, 0.0f);
	glVertex3f(CUBE_RAD, -CUBE_RAD, -CUBE_RAD * 2.0f);


	glEnd();
	glPopMatrix();

}