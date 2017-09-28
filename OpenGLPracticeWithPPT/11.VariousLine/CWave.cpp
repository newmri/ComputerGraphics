#include "CWave.h"

void CWave::Init(OBJTYPE objType, MOVETYPE moveType, Pos pos) {}

void CWave::Init(OBJTYPE objType, MOVETYPE moveType, WAVETYPE waveType)
{
	m_objType = objType;
	m_moveType = moveType;
	m_waveType = waveType;
}
void CWave::Move()
{
}

void CWave::Update()
{

}

void CWave::Render()
{
	glBegin(GL_LINE_STRIP);
	if (m_waveType == WAVETYPE::COS) {
		for (m_pos.x = 0.0f, m_seta = 0; m_pos.x < PIE / 2; m_pos.x += 0.03, m_seta += 0.7) {
			m_pos.y = cos(m_seta);
			glVertex3f(m_pos.x, m_pos.y / 15.0f, 1.0f);
		}
	}

	else {
		for (m_pos.x = 0.0f, m_seta = 0; m_pos.x < PIE / 2; m_pos.x += 0.03, m_seta += 0.7) {
			m_pos.y = sin(m_seta);
			glVertex3f(m_pos.x, m_pos.y / 15.0f, 1.0f);
		}
	}
	glEnd();
}

