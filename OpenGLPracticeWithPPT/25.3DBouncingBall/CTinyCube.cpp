#include "Define.h"
#include "Objects.h"

void CTinyCube::Init()
{
	m_firstMove = true;
}

void CTinyCube::Move()
{
	
	if (CAMERAMANAGER->IsRotatingWithZ()) {

		// CCW
		if (CAMERAMANAGER->GetAngle() > 90 && CAMERAMANAGER->GetAngle() < 90 + 50) {
			if (CAMERAMANAGER->IsRotatingToCCW()) m_pos.y += CAMERA_ANGLE_IN;
		}
		else if (CAMERAMANAGER->GetAngle() > 90 + 50 && CAMERAMANAGER->GetAngle() < 180) {
			if (m_pos.y + m_size < 33) m_pos.y += CAMERA_ANGLE_IN;

		}

		// CCW -> CW
		if (CAMERAMANAGER->GetAngle() < 90 && CAMERAMANAGER->GetAngle() > 0 && !CAMERAMANAGER->IsRotatingToCCW()) {
			if (m_pos.y - m_size > -33) m_pos.y += -CAMERA_ANGLE_IN;
		}

		// CCW
		if (CAMERAMANAGER->GetAngle() > 180 && CAMERAMANAGER->GetAngle() < 180 + 50) {
			if (CAMERAMANAGER->IsRotatingToCCW()) m_pos.x += CAMERA_ANGLE_IN;
		}
		else if (CAMERAMANAGER->GetAngle() > 180 + 50 && CAMERAMANAGER->GetAngle() < 270) {
			if (m_pos.x + m_size < 33) m_pos.x += CAMERA_ANGLE_IN;
		}

		// CCW -> CW
		if (CAMERAMANAGER->GetAngle() < 180 && CAMERAMANAGER->GetAngle() > 90 && !CAMERAMANAGER->IsRotatingToCCW()) {
			if (m_pos.x - m_size > -33) m_pos.x += -CAMERA_ANGLE_IN;
		}

		// CCW
		if (CAMERAMANAGER->GetAngle() > 270 && CAMERAMANAGER->GetAngle() < 270 + 50) {
			if (CAMERAMANAGER->IsRotatingToCCW()) m_pos.y += -CAMERA_ANGLE_IN;
			m_firstMove = false;
		}
		else if (CAMERAMANAGER->GetAngle() > 270 + 50 && CAMERAMANAGER->GetAngle() < 360) {
			if (m_pos.y - m_size > -35) m_pos.y += -CAMERA_ANGLE_IN;
		}


		// CCW -> CW
		if (CAMERAMANAGER->GetAngle() < 360 && CAMERAMANAGER->GetAngle() > 270 && !CAMERAMANAGER->IsRotatingToCCW()) {
			if (m_pos.y - m_size > -33) m_pos.y += CAMERA_ANGLE_IN;
		}

		// CCW
		/*
		if (CAMERAMANAGER->GetAngle() > 0 && CAMERAMANAGER->GetAngle() < 50 && !m_firstMove) {
			if(CAMERAMANAGER->IsRotatingToCCW()) m_pos.x += -CAMERA_ANGLE_IN;
		}
		else if (CAMERAMANAGER->GetAngle() > 50 && CAMERAMANAGER->GetAngle() < 90 && !m_firstMove) {
			if (m_pos.x - m_size > -35) m_pos.x += -CAMERA_ANGLE_IN;
		}
		*/

		// CW
		if (CAMERAMANAGER->GetAngle() < 0 && CAMERAMANAGER->GetAngle() > -50) {
			if (!CAMERAMANAGER->IsRotatingToCCW()) m_pos.x += CAMERA_ANGLE_IN;
		}
		else if (CAMERAMANAGER->GetAngle() < -50 && CAMERAMANAGER->GetAngle() > -90) {
			if (m_pos.x + m_size < 33) m_pos.x += CAMERA_ANGLE_IN;
		}


		// CW -> CCW
		if (CAMERAMANAGER->GetAngle() > 0 && CAMERAMANAGER->GetAngle() < 90 && CAMERAMANAGER->IsRotatingToCCW()) {
			if (m_pos.x - m_size > -33) m_pos.x += -CAMERA_ANGLE_IN;
		}


		// CW
		if (CAMERAMANAGER->GetAngle() < -90 && CAMERAMANAGER->GetAngle() > -90 - 50) {
			if (!CAMERAMANAGER->IsRotatingToCCW()) m_pos.y += CAMERA_ANGLE_IN;
		}
		else if (CAMERAMANAGER->GetAngle() < -90 - 50 && CAMERAMANAGER->GetAngle() > -180) {
			if (m_pos.y + m_size < 33) m_pos.y += CAMERA_ANGLE_IN;
		}

		// CW -> CCW
		if (CAMERAMANAGER->GetAngle() > -90 && CAMERAMANAGER->GetAngle() < 0 && CAMERAMANAGER->IsRotatingToCCW()) {
			if (m_pos.y - m_size > -33) m_pos.y += -CAMERA_ANGLE_IN;
		}


		// CW
		if (CAMERAMANAGER->GetAngle() < -180 && CAMERAMANAGER->GetAngle() > -180 - 50) {
			if (!CAMERAMANAGER->IsRotatingToCCW()) m_pos.x -= CAMERA_ANGLE_IN;
			m_firstMove = false;
		}
		else if (CAMERAMANAGER->GetAngle() < -180 - 50 && CAMERAMANAGER->GetAngle() > -270) {
			if (m_pos.x - m_size > -35) m_pos.x -= CAMERA_ANGLE_IN;
		}

		// CW -> CCW
		if (CAMERAMANAGER->GetAngle() > -180 && CAMERAMANAGER->GetAngle() < -90 && CAMERAMANAGER->IsRotatingToCCW()) {
			if (m_pos.x + m_size < 33) m_pos.x += CAMERA_ANGLE_IN;
		}

		// CW
		if (CAMERAMANAGER->GetAngle() < -270 && CAMERAMANAGER->GetAngle() > -270 - 50) {
			if (!CAMERAMANAGER->IsRotatingToCCW()) m_pos.y -= CAMERA_ANGLE_IN;
		}
		else if (CAMERAMANAGER->GetAngle() < -270 - 50 && CAMERAMANAGER->GetAngle() > -360) {
			if (m_pos.y - m_size > -35) m_pos.y -= CAMERA_ANGLE_IN;
		}

		// CW -> CCW
		if (CAMERAMANAGER->GetAngle() > -270 && CAMERAMANAGER->GetAngle() < -180 && CAMERAMANAGER->IsRotatingToCCW()) {
			if (m_pos.y + m_size < 33) m_pos.y += CAMERA_ANGLE_IN;

		}
	}
	
}

void CTinyCube::Update()
{
	this->Move();
	
}

void CTinyCube::Render()
{
	glPushMatrix();
	glTranslatef(0.0f, 0.0f, CUBE_RAD / -2.0f);
	glTranslatef(m_pos.x, m_pos.y, m_pos.z); // Let's move!

	if(m_size == 10) glColor3f(1.0f, 0.0f, 0.0f);
	else if(m_size == 5) glColor3f(1.0f, 1.0f, 1.0f);
	else glColor3f(1.0f, .0f, 1.0f);
	glutSolidCube(m_size);
	glPopMatrix();

}