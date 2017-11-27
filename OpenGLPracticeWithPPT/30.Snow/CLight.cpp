#include "Define.h"
#include "Objects.h"

void CLight::Init()
{
	ZeroMemory(&AmbientLight, sizeof(AmbientLight));
	ZeroMemory(&DiffuseLight, sizeof(AmbientLight));
	ZeroMemory(&SpecularLight, sizeof(AmbientLight));
	this->SetRotation(Vector3(0.0f, 0.0f, 1.0f));
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

	switch (m_objType) {
	case LIGHT1: m_light = GL_LIGHT0; break;
	case LIGHT2: m_light = GL_LIGHT1; break;
	case LIGHT3: m_light = GL_LIGHT2; break;
	case LIGHT4: m_light = GL_LIGHT3; break;

	}
}


void CLight::Update()
{
	if (CAMERAMANAGER->DoRotateLight()) this->Rotate();
}

void CLight::Render()
{
	glPushMatrix();

	glTranslatef(m_pos.x, m_pos.y, m_pos.z);
	glRotatef(m_angle, m_rotation.x, m_rotation.y, m_rotation.z);
	glutSolidCone(m_size / 2.0f, m_size, 25, 25);

	GLfloat lightPos[] = { m_pos.x, m_pos.y, m_pos.z, 1.0 };
												 // 조명을 사용하도록 설정
	if (m_lightOn) {
		glEnable(GL_LIGHTING);
		// 조명 설정

		glLightfv(m_light, GL_AMBIENT, AmbientLight);
		glLightfv(m_light, GL_DIFFUSE, DiffuseLight);
		glLightfv(m_light, GL_SPECULAR, SpecularLight);
		glLightfv(m_light, GL_POSITION, lightPos);
		glLightf(m_light, GL_SPOT_CUTOFF, 90.0f);
		glEnable(m_light);

		glEnable(GL_COLOR_MATERIAL);
		glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);

		glMaterialfv(GL_FRONT, GL_AMBIENT, AmbientLight);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, DiffuseLight);
		glMateriali(GL_FRONT, GL_SHININESS, 64);
	}
	else glDisable(m_light);

	glPopMatrix();

}