#include "define.h"


void CPolygon::Init()
{
	m_vX = SPEED;
	m_whitePos.y = 0.0f;
	m_drop = false;
}
void CPolygon::Update()
{
	if (!m_isWhite && m_drop) { m_pos.y -= SPEED;}
	else if(m_isWhite && !m_drop) m_whitePos.x -= m_vX;
	
}

void CPolygon::Render()
{
	glPushMatrix();
	if(m_v1.x != 0.0f) glTranslatef(m_pos.x, m_pos.y, 0.0f);
	glBegin(GL_POLYGON);
	glColor4f(1.0f, 1.0f, 0.0f, 1.0f);
	glVertex2f(m_v1.x, m_v1.y);
	glVertex2f(m_v2.x, m_v2.y);
	if (m_haveV3) glVertex2f(m_v3.x, m_v3.y);
	glVertex2f(m_v4.x, m_v4.y);
	glEnd();

	glBegin(GL_LINE_LOOP);
	glColor4f(1.0f, 0.0f, 0.0f, 1.0f);
	glVertex2f(m_v1.x, m_v1.y);
	glVertex2f(m_v2.x, m_v2.y);
	if (m_haveV3) glVertex2f(m_v3.x, m_v3.y);
	glVertex2f(m_v4.x, m_v4.y);
	glEnd();
	glPopMatrix();
}


void CPolygon::RenderWhitePolygon()
{
	if (m_isWhite) {
		glPushMatrix();
		glTranslatef(m_whitePos.x, m_whitePos.y, 0.0f);
		glBegin(GL_POLYGON);
		glColor4f(1.0f, 1.0f, 1.0f, 0.0f);
		glVertex2f(m_v1.x, m_v1.y);
		glVertex2f(m_v2.x, m_v2.y);
		if (m_haveV3) glVertex2f(m_v3.x, m_v3.y);
		glVertex2f(m_v4.x, m_v4.y);
		glEnd();
		glPopMatrix();
	}
}