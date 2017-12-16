#include "Define.h"
#include "Objects.h"


void CItem::Init()
{
	m_imgIdx = rand() % 3;
	m_speed = rand() % ITEM_SPEED + 1.0f;
}

void CItem::Move(float frameTime)
{
	m_objInfo.pos.y = Clamp(m_objInfo.size, m_objInfo.pos.y - m_speed * frameTime, 100);
}

void CItem::Update(float frameTime)
{
	this->Move(frameTime);
}

void CItem::Render()
{
	glEnable(GL_TEXTURE_2D);

	glPushMatrix();
	glTranslatef(m_objInfo.pos.x, m_objInfo.pos.y, m_objInfo.pos.z);
	//�ؽ�ó ��ü�� ����
	glBindTexture(GL_TEXTURE_2D, TEXTUREMANAGER->GetTexture(m_imgIdx));
	//�ո�
	glBegin(GL_QUADS);
	{
		glTexCoord2f(1, 1);
		glVertex3f(ITEM_RAD, ITEM_RAD, ITEM_RAD);
		glTexCoord2f(0, 1);
		glVertex3f(-ITEM_RAD, ITEM_RAD, ITEM_RAD);
		glTexCoord2f(0, 0);
		glVertex3f(-ITEM_RAD, -ITEM_RAD, ITEM_RAD);
		glTexCoord2f(1, 0);
		glVertex3f(ITEM_RAD, -ITEM_RAD, ITEM_RAD);
	}
	glEnd();

	//�ؽ�ó ��ü�� ����
	glBindTexture(GL_TEXTURE_2D, TEXTUREMANAGER->GetTexture(m_imgIdx));
	//�޸�
	glBegin(GL_QUADS);
	{
		glTexCoord2f(1, 1);
		glVertex3f(-ITEM_RAD, ITEM_RAD, -ITEM_RAD);
		glTexCoord2f(0, 1);
		glVertex3f(ITEM_RAD, ITEM_RAD, -ITEM_RAD);
		glTexCoord2f(0, 0);
		glVertex3f(ITEM_RAD, -ITEM_RAD, -ITEM_RAD);
		glTexCoord2f(1, 0);
		glVertex3f(-ITEM_RAD, -ITEM_RAD, -ITEM_RAD);
	}
	glEnd();

	//�ؽ�ó ��ü�� ����
	glBindTexture(GL_TEXTURE_2D, TEXTUREMANAGER->GetTexture(m_imgIdx));
	//����
	glBegin(GL_QUADS);
	{
		glTexCoord2f(1, 1);
		glVertex3f(-ITEM_RAD, ITEM_RAD, ITEM_RAD);
		glTexCoord2f(0, 1);
		glVertex3f(ITEM_RAD, ITEM_RAD, ITEM_RAD);
		glTexCoord2f(0, 0);
		glVertex3f(ITEM_RAD, ITEM_RAD, -ITEM_RAD);
		glTexCoord2f(1, 0);
		glVertex3f(-ITEM_RAD, ITEM_RAD, -ITEM_RAD);
	}
	glEnd();

	//�ؽ�ó ��ü�� ����
	glBindTexture(GL_TEXTURE_2D, TEXTUREMANAGER->GetTexture(m_imgIdx));
	//�Ʒ���
	glBegin(GL_QUADS);
	{
		glTexCoord2f(1, 1);
		glVertex3f(ITEM_RAD, -ITEM_RAD, -ITEM_RAD);
		glTexCoord2f(0, 1);
		glVertex3f(ITEM_RAD, -ITEM_RAD, ITEM_RAD);
		glTexCoord2f(0, 0);
		glVertex3f(-ITEM_RAD, -ITEM_RAD, ITEM_RAD);
		glTexCoord2f(1, 0);
		glVertex3f(-ITEM_RAD, -ITEM_RAD, -ITEM_RAD);
	}
	glEnd();

	//�ؽ�ó ��ü�� ����
	glBindTexture(GL_TEXTURE_2D, TEXTUREMANAGER->GetTexture(m_imgIdx));
	//���ʸ�
	glBegin(GL_QUADS);
	{
		glTexCoord2f(1, 1);
		glVertex3f(-ITEM_RAD, ITEM_RAD, ITEM_RAD);
		glTexCoord2f(0, 1);
		glVertex3f(-ITEM_RAD, ITEM_RAD, -ITEM_RAD);
		glTexCoord2f(0, 0);
		glVertex3f(-ITEM_RAD, -ITEM_RAD, -ITEM_RAD);
		glTexCoord2f(1, 0);
		glVertex3f(-ITEM_RAD, -ITEM_RAD, ITEM_RAD);
	}
	glEnd();

	//�ؽ�ó ��ü�� ����
	glBindTexture(GL_TEXTURE_2D, TEXTUREMANAGER->GetTexture(m_imgIdx));
	//�����ʸ� 
	glBegin(GL_QUADS);
	{
		glTexCoord2f(1, 1);
		glVertex3f(ITEM_RAD, ITEM_RAD, -ITEM_RAD);
		glTexCoord2f(0, 1);
		glVertex3f(ITEM_RAD, ITEM_RAD, ITEM_RAD);
		glTexCoord2f(0, 0);
		glVertex3f(ITEM_RAD, -ITEM_RAD, ITEM_RAD);
		glTexCoord2f(1, 0);
		glVertex3f(ITEM_RAD, -ITEM_RAD, -ITEM_RAD);
	}
	glEnd();
	glPopMatrix();

	glDisable(GL_TEXTURE_2D);
}