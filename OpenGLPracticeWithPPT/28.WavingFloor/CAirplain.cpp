#include "Define.h"
#include "Objects.h"

void CAirplain::Init()
{
	m_angle = 0.0f;
	m_propelerRotation.x = 1.0f;
	m_propelerRotation.y = 0.0f;
	m_propelerRotation.z = 0.0f;
	m_proplerAngle = 0.0f;
	this->SetRotation(Vector3(0.0f, 1.0f, 0.0f));
	m_i = 90.0f;
	m_trackAngle = 0.0f;
	m_left = false;


	double angle = (270 * 3.141592 / 180);
	double x = TRACK_RAD * cos(angle);
	double z = TRACK_RAD * sin(angle);
	m_target.x = x;
	m_target.z = z;


}

void CAirplain::Move()
{


	if (!m_left) {
		if (m_i < 360.0f) m_i += 3.0f;
		else m_i = 0.0f;
	}
	else {
		if (m_i > -360.0f) m_i -= 3.0f;
		else m_i = 0.0f;
	}
	m_trackAngle = (m_i * PIE / 180);
	m_dPos.x = TRACK_RAD * cos(m_trackAngle);
	m_dPos.z = TRACK_RAD * sin(m_trackAngle);


	//float angle = ((m_i - 180) * PIE / 180);
	//tPos.x = (TRACK_RAD * cos(0)) + TRACK_RAD;
   //tPos.z = TRACK_RAD * sin(0);

	Vector3 v = m_target.GetNormalized();
	Vector3 t = m_dPos.GetNormalized();


	//cout << (float)acos(v.GetDot(t)) << endl;

	m_headAngle = (float)acos(v.GetDot(t));
	m_headAngle = m_headAngle * 180 / PIE;

	if (!m_left) m_headAngle = 180.0f - m_headAngle;
	else m_headAngle = 360.0f - m_headAngle;
	Vector3 right = v.GetCross(Vector3(0.0f, 1.0f, 0.0f));

	if (right.GetDot(t) < 0) m_headAngle = -m_headAngle;



}

void CAirplain::Update()
{
	if (m_proplerAngle < 360.0f) m_proplerAngle += 10.0f;
	else m_proplerAngle = 0.0f;

	this->Move();
}


void CAirplain::Render()
{

	glPushMatrix();

	glTranslatef(m_pos.x + m_dPos.x, m_pos.y, m_pos.z + m_dPos.z);

	glRotatef(m_headAngle, m_rotation.x, m_rotation.y, m_rotation.z);
	// Render Body
	glPushMatrix();
	glScalef(m_scale.x, m_scale.y, m_scale.z);
	glColor3f(m_bodyColor.R, m_bodyColor.G, m_bodyColor.B);
	glutSolidCube(m_size);
	glPopMatrix();

	// Render Propeler
	glPushMatrix();
	glColor3f(1.0f, 1.0f, 1.0f);
	glScalef(0.5f, 0.5f, 3.0f);
	glTranslatef(-m_size * 2.0f, 0.0f, 0.0f);
	glRotatef(m_proplerAngle, m_propelerRotation.x, m_propelerRotation.y, m_propelerRotation.z);
	glutSolidCube(m_size);
	glPopMatrix();

	// Render Right Wing
	glPushMatrix();
	glTranslatef(0.0f, 0.0f, -m_size * m_scale.x);
	glColor3f(1.0f, 1.0f, 1.0f);
	glBegin(GL_TRIANGLES);
	glVertex3f(0.0f, 0.0f, 0.0f);
	glVertex3f(0.0f, 0.0f, 5.0f);
	glVertex3f(-m_size, 0.0f, 5.0f);
	glEnd();
	glPopMatrix();

	// Render Left Wing
	glPushMatrix();
	glTranslatef(0.0f, 0.0f, m_size / 2.0f);
	glColor3f(1.0f, 1.0f, 1.0f);
	glBegin(GL_TRIANGLES);
	glVertex3f(0.0f, 0.0f, 0.0f);
	glVertex3f(0.0f, 0.0f, 5.0f);
	glVertex3f(-m_size, 0.0f, 0.0f);
	glEnd();
	glPopMatrix();

	// Render Cuty Tail
	glPushMatrix();
	glColor3f(1.0f, 0.0f, 0.0f);
	glScalef(1.0f, 0.5f, 0.5f);
	glTranslatef(m_size * 1.5f, 0.0f, 0.0f);
	//glutSolidCube(m_size);
	glutSolidCone(m_size, m_size, 25, 25);
	glPopMatrix();

	glPopMatrix();

	glBegin(GL_LINES);
	for (int i = 0; i < 360; i += 1) {
		double angle = (i * 3.141592 / 180);
		double x = TRACK_RAD * cos(angle);
		double y = TRACK_RAD * sin(angle);

		glPushMatrix();
		glVertex3f(x, m_pos.y, y);
		glPopMatrix();
	}
	glEnd();
}