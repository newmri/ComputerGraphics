#include "Define.h"
#include "Objects.h"

void CLight::Init()
{
	ZeroMemory(&AmbientLight, sizeof(AmbientLight));
	ZeroMemory(&DiffuseLight, sizeof(AmbientLight));
	ZeroMemory(&SpecularLight, sizeof(AmbientLight));

	DiffuseLight[3] = 1.0f;
	SpecularLight[3] = 1.0f;
	if (m_lightNum == 0) {
		DiffuseLight[0] = 1.0f;
		SpecularLight[0] = 1.0f;
	}

	else {
		DiffuseLight[2] = 1.0f;
		SpecularLight[1] = 1.0f;

	}
}


void CLight::Update()
{

}

void CLight::Render()
{
	glPushMatrix();

	glTranslatef(m_pos.x, m_pos.y, m_pos.z);
	glutSolidCone(m_size / 2.0f, m_size, 25, 25);

	GLfloat lightPos[] = { m_pos.x, m_pos.y, m_pos.z, 1.0 };
												 // 조명을 사용하도록 설정
	if (m_lightOn) {
		glEnable(GL_LIGHTING);
		// 조명 설정
		if (m_lightNum == 0) {
			glLightfv(GL_LIGHT0, GL_AMBIENT, AmbientLight);
			glLightfv(GL_LIGHT0, GL_DIFFUSE, DiffuseLight);
			glLightfv(GL_LIGHT0, GL_SPECULAR, SpecularLight);
			glLightfv(GL_LIGHT0, GL_POSITION, lightPos);
			glLightf(GL_LIGHT0, GL_SPOT_CUTOFF, 90.0f);
			glEnable(GL_LIGHT0);
		}

		else {
			glLightfv(GL_LIGHT1, GL_AMBIENT, AmbientLight);
			glLightfv(GL_LIGHT1, GL_DIFFUSE, DiffuseLight);
			glLightfv(GL_LIGHT1, GL_SPECULAR, SpecularLight);
			glLightfv(GL_LIGHT1, GL_POSITION, lightPos);
			glLightf(GL_LIGHT1, GL_SPOT_CUTOFF, 90.0f);
			glEnable(GL_LIGHT1);
		}


		glEnable(GL_COLOR_MATERIAL);
		glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);

		glMaterialfv(GL_FRONT, GL_AMBIENT, AmbientLight);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, DiffuseLight);
		glMateriali(GL_FRONT, GL_SHININESS, 64);
	}
	else {
		if (m_lightNum == 0) glDisable(GL_LIGHT0);
		else glDisable(GL_LIGHT1);
	}
	glPopMatrix();

}