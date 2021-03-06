#include "Define.h"

void CRect::Init()
{
	m_pos.y = 0.5f;
	m_haveToDrawWhite = false;
	m_vX = SPEED;
	m_waterHDevide = WATER_DEVIDE;
	m_waterHDevide2 = MAX_WATER_H;
	m_waterInc = -WATER_INC;
	m_waterInc2 = WATER_INC;
	m_move = true;
	switch (m_position) {
	case LT:
		m_pos.x = -m_size;
		m_pos.y += m_size;
		break;
	case T:
		m_pos.y += m_size;
		break;
	case RT:
		m_pos.x = m_size;
		m_pos.y += m_size;
		break;
	case L:
		m_pos.x = -m_size;
		break;
	case M:
		m_color.b = 0.0f;
		break;
	case R:
		m_pos.x = m_size;
		break;
	case LB:
		m_pos.x = -m_size;
		m_pos.y -= m_size;
		break;
	case B:
		m_pos.y -= m_size;
		break;
	case RB:
		m_pos.x = m_size;
		m_pos.y -= m_size;
		break;
	case BASKET:
		m_pos.x = m_size / 2;
		m_pos.y -= m_size * 4;
		m_color.a = 0.0f;
		m_color.b = 0.0f;
		m_color.r = 0.0f;
		break;
	default: break;
	}
}

void CRect::Update()
{
	if(m_move) m_pos.x -= m_vX;
}

void CRect::Render()
{

	glPushMatrix();
		glColor4f(m_color.r, m_color.g, m_color.b, m_color.a);
		glTranslatef(m_pos.x, m_pos.y, 0.0f);
		glutSolidCube(m_size);
	glPopMatrix();


}

void CRect::RenderWater()
{
	if (m_position == BASKET) {
		m_waterHDevide += m_waterInc;
		m_waterHDevide2 += m_waterInc2;
		if (m_waterHDevide < MAX_WATER_H || m_waterHDevide > WATER_DEVIDE) m_waterInc = -m_waterInc;
		if (m_waterHDevide2 < MAX_WATER_H || m_waterHDevide2 > WATER_DEVIDE) m_waterInc2 = -m_waterInc2;
		glBegin(GL_POLYGON);
		glColor4f(85.0f / 255.0f, 134.0f / 255.0f, 235.0f / 255.0f, 1.0f);
		glVertex2f(this->GetLeftPos() + 0.02f, this->GetBottomPos());
		glVertex2f(this->GetLeftPos() + 0.02f, this->GetBottomPos() + (m_size / m_waterHDevide));
		glVertex2f(this->GetRightPos() - 0.02f, this->GetBottomPos() + (m_size / m_waterHDevide));
		glVertex2f(this->GetRightPos() - 0.02f, this->GetBottomPos());
		glEnd();
	}
}