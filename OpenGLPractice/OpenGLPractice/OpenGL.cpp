// OpenGL.cpp: implementation of the COpenGL class.
//
//////////////////////////////////////////////////////////////////////

#include <iostream>
#include <gl/glut.h>
#include <Windows.h>

#include "OpenGL.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

#define SHAPE_BOARD			1
#define SHAPE_FRAME			2
#define SHAPE_I_JOINT		3
#define SHAPE_T_JOINT		4
#define SHAPE_DRAWER			5
#define SHAPE_DRAWER_PART		6
#define SHAPE_BOOK			7

#define SHAPE_JOINT_PART_1	101
#define SHAPE_JOINT_PART_2	102

#define MATERIAL_FLAT_WHITE	201
#define MATERIAL_FLAT_GRAY	202
#define MATERIAL_GLASS		203
#define MATERIAL_BOOK		204

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

COpenGL::COpenGL()
{
	m_xRot = 0.0f;
	m_yRot = 0.0f;
	m_depth = -3.0f;
	m_IsLButtonDown = FALSE;
	m_IsMButtonDown = FALSE;
	// 조명을 위한 변수들
	m_IsOnRed = TRUE;
	m_IsOnGreen = TRUE;
	m_IsOnBlue = TRUE;
	// 서랍을 위한 변수들
	m_StatusDrawerPart1 = 0;
	m_StatusDrawerPart2 = 0;
	m_zDrawerPart1 = 0.0f;
	m_zDrawerPart2 = 0.0f;
}

COpenGL::~COpenGL()
{

}

void COpenGL::Draw()
{
	RenderScene();
	glFlush();								// 화면에 출력하기
}

void COpenGL::Init()
{

	SetupRC();

}

void COpenGL::Release()
{
}

void COpenGL::SetupRC()
{
	// Red
	float AmbientR[4] = {0.3f, 0.0f, 0.0f, 1.0f};		// Ambient
	float DiffuseR[4] = {0.7f, 0.0f, 0.0f, 1.0f};		// Diffuse
	float PositionR[4] = {10.0f, 50.0f, 50.0f, 1.0f};	// Light position
	float SpecularR[4] = {1.0f, 0.0f, 0.0f, 1.0f};		// Specular

	// Green
	float AmbientG[4] = {0.0f, 0.3f, 0.0f, 1.0f};		// Ambient
	float DiffuseG[4] = {0.0f, 0.7f, 0.0f, 1.0f};		// Diffuse
	float PositionG[4] = {0.0f, 50.0f, 50.0f, 1.0f};	// Light position
	float SpecularG[4] = {0.0f, 1.0f, 0.0f, 1.0f};		// Specular

	// Blue
	float AmbientB[4] = {0.0f, 0.0f, 0.3f, 1.0f};		// Ambient
	float DiffuseB[4] = {0.0f, 0.0f, 0.7f, 1.0f};		// Diffuse
	float PositionB[4] = {-10.0f, 50.0f, 50.0f, 1.0f};	// Light position
	float SpecularB[4] = {0.0f, 0.0f, 1.0f, 1.0f};		// Specular

	// Set Light
	glEnable(GL_LIGHTING);
	glLightfv(GL_LIGHT0, GL_AMBIENT, AmbientR);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, DiffuseR);
	glLightfv(GL_LIGHT0, GL_SPECULAR, SpecularR);
	glLightfv(GL_LIGHT0, GL_POSITION, PositionR);
	glEnable(GL_LIGHT0);
	glLightfv(GL_LIGHT1, GL_AMBIENT, AmbientG);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, DiffuseG);
	glLightfv(GL_LIGHT1, GL_SPECULAR, SpecularG);
	glLightfv(GL_LIGHT1, GL_POSITION, PositionG);
	glEnable(GL_LIGHT1);
	glLightfv(GL_LIGHT2, GL_AMBIENT, AmbientB);
	glLightfv(GL_LIGHT2, GL_DIFFUSE, DiffuseB);
	glLightfv(GL_LIGHT2, GL_SPECULAR, SpecularB);
	glLightfv(GL_LIGHT2, GL_POSITION, PositionB);
	glEnable(GL_LIGHT2);

	// Set Material
	glEnable(GL_COLOR_MATERIAL);
	glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);

	// Culling(CCW)
	glFrontFace(GL_CCW);
	glEnable(GL_CULL_FACE);

	// Enable Depth Test
	glEnable(GL_DEPTH_TEST);

	// Blending
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	// Set clear color(Black)
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

	// Load Texture
	m_Texture.Load("TexBook.bmp");

	// Load Material & Shape
	LoadMaterial();
	LoadShape();
}

void COpenGL::Resize(int w, int h)
{
	// avoid divide 0
	if (h == 0) h = 1;

	// set range of viewport
	glViewport(0, 0, w, h);

	// projection
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();	// reset

	int type = PERSPECTIVE_VIEW;

	if (type == ORTHO_VIEW) {
		// set cliping volume
		if (w <= h) glOrtho(-2.0f, 2.0f, -2.0f * h/w, 2.0f * h/w, -10.0f, 10.0f);
		else glOrtho(-2.0f * w/h, 2.0f * w/h, -2.0f, 2.0f, -10.0f, 10.0f);
	} else {
		gluPerspective(45.0f, (float)w/(float)h, 0.01f, 1000.0);
	}

	// Modelview
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();	// reset

}

void COpenGL::RenderScene()
{
	// Clear color & depth buffer bit
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glPushMatrix();
		glTranslatef(0.0f, -0.5f, m_depth);
		glRotatef(m_yRot, 0.0f, 1.0f, 0.0f);
		glRotatef(m_xRot, 1.0f, 0.0f, 0.0f);
		// Left leg
		glPushMatrix();
			glTranslatef(-0.8f, 0.0f, -0.5f);
			glCallList(SHAPE_FRAME);
			glPushMatrix();
				glRotatef(90.0f, 0.0f, 0.0f, 1.0f);
				glCallList(SHAPE_T_JOINT);
			glPopMatrix();
			glPushMatrix();
				glTranslatef(0.0f, 0.0f, 0.9f);
				glCallList(SHAPE_I_JOINT);
			glPopMatrix();
			glRotatef(-90.0f, 1.0f, 0.0f, 0.0f);
			glPushMatrix();
				glTranslatef(0.0f, 0.0f, 0.9f);
				glCallList(SHAPE_I_JOINT);
			glPopMatrix();
			glScalef(1.0f, 1.0f, 1.09f);
			glCallList(SHAPE_FRAME);
		glPopMatrix();
		// Right leg
		glPushMatrix();
			glTranslatef(0.8f, 0.0f, -0.5f);
			glCallList(SHAPE_FRAME);
			glPushMatrix();
				glRotatef(180.0f, 0.0f, 0.0f, 1.0f);
				glCallList(SHAPE_T_JOINT);
			glPopMatrix();
			glPushMatrix();
				glTranslatef(0.0f, 0.0f, 0.9f);
				glCallList(SHAPE_I_JOINT);
			glPopMatrix();
			glRotatef(-90.0f, 1.0f, 0.0f, 0.0f);
			glPushMatrix();
				glTranslatef(0.0f, 0.0f, 0.9f);
				glCallList(SHAPE_I_JOINT);
			glPopMatrix();
			glScalef(1.0f, 1.0f, 1.09f);
			glCallList(SHAPE_FRAME);
		glPopMatrix();
		// Center leg
		glPushMatrix();
			glTranslatef(0.8f, 0.0f, -0.5f);
			glRotatef(-90.0f, 0.0f, 1.0f, 0.0f);
			glScalef(1.0f, 1.0f, 1.6f);
			glCallList(SHAPE_FRAME);
		glPopMatrix();
		// 서랍
		glPushMatrix();
			glTranslatef(0.5f, -0.025f, 0.2f);
			glCallList(SHAPE_DRAWER);
			glPushMatrix();
				// 서랍1의 z좌표에 따라 이동 
				glTranslatef(0.0f, 0.3f, m_zDrawerPart1);
				glCallList(SHAPE_DRAWER_PART);
			glPopMatrix();
			glPushMatrix();
				// 서랍2의 z좌표에 따라 이동
				glTranslatef(0.0f, 0.0f, m_zDrawerPart2);
				glCallList(SHAPE_DRAWER_PART);
			glPopMatrix();
		glPopMatrix();
		// Board
		glPushMatrix();
			glTranslatef(0.0f, 1.0f, 0.0f);
			glPushMatrix();
				glTranslatef(0.0f, 0.02f, 0.0f);
				glRotatef(30.0f, 0.0f, 1.0f, 0.0);
				glRotatef(-90.0f, 1.0f, 0.0f, 0.0);
				glCallList(SHAPE_BOOK);
			glPopMatrix();
			glCallList(SHAPE_BOARD);
		glPopMatrix();
	glPopMatrix();

	glFlush();
}

void COpenGL::LoadShape()
{
	LoadShapeBoard();
	LoadShapeFrame();
	LoadShapeIJoint();
	LoadShapeTJoint();
	LoadShapeDrawer();
	LoadShapeDrawerPart();
	LoadShapeBook();
}

void COpenGL::LoadMaterial()
{
	// Load flat white material
	glNewList(MATERIAL_FLAT_WHITE, GL_COMPILE);
	{
		float Ambient[4] = {0.1f, 0.1f, 0.1f, 1.0f};
		float Diffuse[4] = {1.0f, 1.0f, 0.9f, 1.0f};
		float Specular[4] = {0.5f, 0.5f, 0.5f, 1.0f};
		glMaterialfv(GL_FRONT, GL_AMBIENT, Ambient);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, Diffuse);
		glMaterialfv(GL_FRONT, GL_SPECULAR, Specular);
		glMateriali(GL_FRONT, GL_SHININESS, 16);
		glColor3f(1.0f, 1.0f, 0.95f);
	}
	glEndList();

	// Load flat gray material
	glNewList(MATERIAL_FLAT_GRAY, GL_COMPILE);
	{
		float Ambient[4] = {0.1f, 0.1f, 0.1f, 1.0f};
		float Diffuse[4] = {0.6f, 0.6f, 0.5f, 1.0f};
		float Specular[4] = {0.5f, 0.5f, 0.5f, 1.0f};
		glMaterialfv(GL_FRONT, GL_AMBIENT, Ambient);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, Diffuse);
		glMaterialfv(GL_FRONT, GL_SPECULAR, Specular);
		glMateriali(GL_FRONT, GL_SHININESS, 16);
		glColor3f(0.4f, 0.4f, 0.35f);
	}
	glEndList();

	// Load glass material
	glNewList(MATERIAL_GLASS, GL_COMPILE);
	{
		float Ambient[4] = {0.3f, 0.3f, 0.3f, 0.3f};
		float Diffuse[4] = {0.3f, 0.3f, 0.3f, 0.3f};
		float Specular[4] = {1.0f, 1.0f, 1.0f, 1.0f};
		glMaterialfv(GL_FRONT, GL_AMBIENT, Ambient);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, Diffuse);
		glMaterialfv(GL_FRONT, GL_SPECULAR, Specular);
		glMateriali(GL_FRONT, GL_SHININESS, 128);
		glColor4f(0.3f, 0.3f, 0.3f, 0.3f);
	}
	glEndList();

	// Load book material
	glNewList(MATERIAL_BOOK, GL_COMPILE);
	{
		float Ambient[4] = {1.0f, 1.0f, 1.0f, 1.0f};
		float Diffuse[4] = {1.0f, 1.0f, 1.0f, 1.0f};
		float Specular[4] = {0.5f, 0.5f, 0.5f, 1.0f};
		glMaterialfv(GL_FRONT, GL_AMBIENT, Ambient);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, Diffuse);
		glMaterialfv(GL_FRONT, GL_SPECULAR, Specular);
		glMateriali(GL_FRONT, GL_SHININESS, 16);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glPixelStorei(GL_UNPACK_ALIGNMENT, 4);
		glPixelStorei(GL_UNPACK_ROW_LENGTH, 0);
		glPixelStorei(GL_UNPACK_SKIP_ROWS, 0);
		glPixelStorei(GL_UNPACK_SKIP_PIXELS, 0);
		glTexImage2D(GL_TEXTURE_2D, 0, 3, m_Texture.Width, m_Texture.Height, 0, GL_RGB, GL_UNSIGNED_BYTE, m_Texture.Data);
		glColor3f(1.0f, 1.0f, 1.0f);
	}
	glEndList();
}

void COpenGL::StartMouseMove(float x, float y)
{
	// 마우스가 눌린 지점을 기억
	m_oldX = x;
	m_oldY = y;
}

void COpenGL::DoMouseMove(float x, float y)
{
	// 왼쪽 버튼이 눌렸을 때: 회전
	if (m_IsLButtonDown) {
		m_xRot = (y - m_oldY);
		m_yRot = (x - m_oldX);
	}

	// 가운데 버튼이 눌렸을 때: 확대/축소
	if (m_IsMButtonDown) {
		m_depth = -3 + (y - m_oldY ) / 50.0f;
	}

}

void COpenGL::SetLButtonStatus(BOOL IsDown)
{
	m_IsLButtonDown = IsDown;
}

void COpenGL::SetMButtonStatus(BOOL IsDown)
{
	m_IsMButtonDown = IsDown;
}

void COpenGL::LoadShapeBoard()
{
	float vertex[24][3] =
		{{1.0f, 0.02f, -0.5f}, {-1.0f, 0.02f, -0.5f}, {-1.0f, 0.02f, 0.5f}, {1.0f, 0.02f, 0.5f},
		{1.0f, -0.02f, -0.5f}, {-1.0f, -0.02f, -0.5f}, {-1.0f, -0.02f, 0.5f}, {1.0f, -0.02f, 0.5f},
		{0.98f, 0.02f, -0.48f}, {-0.98f, 0.02f, -0.48f}, {-0.98f, 0.02f, 0.48f}, {0.98f, 0.02f, 0.48f},
		{0.98f, 0.0f, -0.48f}, {-0.98f, 0.0f, -0.48f}, {-0.98f, 0.0f, 0.48f}, {0.98f, 0.0f, 0.48f},
		{0.95f, 0.0f, -0.45f}, {-0.95f, 0.0f, -0.45f}, {-0.95f, 0.0f, 0.45f}, {0.95f, 0.0f, 0.45f},
		{0.95f, -0.02f, -0.45f}, {-0.95f, -0.02f, -0.45f}, {-0.95f, -0.02f, 0.45f}, {0.95f, -0.02f, 0.45f}};
	float normal[6][3] =
		{{0.0f, 0.0f, -1.0f}, {-1.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 1.0f}, {1.0f, 0.0f, 0.0f}, {0.0f, 1.0f, 0.0f}, {0.0f, -1.0f, 0.0f}};
	glNewList(SHAPE_BOARD, GL_COMPILE);
		glCallList(MATERIAL_FLAT_WHITE);
		glBegin(GL_TRIANGLES);
		for (int i = 0; i < 4; i++) {
			// Outside
			glNormal3fv(normal[i]);
			glVertex3fv(vertex[i]); glVertex3fv(vertex[4 + i]); glVertex3fv(vertex[(i + 1) % 4 + 4]);
			glVertex3fv(vertex[(i + 1) % 4 + 4]); glVertex3fv(vertex[(i + 1) % 4]); glVertex3fv(vertex[i]);
			// Top
			glNormal3fv(normal[4]);
			glVertex3fv(vertex[i]); glVertex3fv(vertex[(i + 1) % 4]); glVertex3fv(vertex[(i + 1) % 4 + 8]);
			glVertex3fv(vertex[(i + 1) % 4 + 8]); glVertex3fv(vertex[8 + i]); glVertex3fv(vertex[i]);
			// Inside(Upper)
			glNormal3fv(normal[(i + 2) % 4]);
			glVertex3fv(vertex[i + 8]); glVertex3fv(vertex[(i + 1) % 4 + 8]); glVertex3fv(vertex[(i + 1) % 4 + 12]);
			glVertex3fv(vertex[(i + 1) % 4 + 12]); glVertex3fv(vertex[i + 12]); glVertex3fv(vertex[i + 8]);
			// Inside(Middle)
			glNormal3fv(normal[4]);
			glVertex3fv(vertex[i + 12]); glVertex3fv(vertex[(i + 1) % 4 + 12]); glVertex3fv(vertex[(i + 1) % 4 + 16]);
			glVertex3fv(vertex[(i + 1) % 4 + 16]); glVertex3fv(vertex[i + 16]); glVertex3fv(vertex[i + 12]);
			// Inside(lower)
			glNormal3fv(normal[(i + 2) % 4]);
			glVertex3fv(vertex[i + 16]); glVertex3fv(vertex[(i + 1) % 4 + 16]); glVertex3fv(vertex[(i + 1) % 4 + 20]);
			glVertex3fv(vertex[(i + 1) % 4 + 20]); glVertex3fv(vertex[i + 20]); glVertex3fv(vertex[i + 16]);
			// Bottom
			glNormal3fv(normal[5]);
			glVertex3fv(vertex[i + 4]); glVertex3fv(vertex[i + 20]); glVertex3fv(vertex[(i + 1) % 4 + 20]);
			glVertex3fv(vertex[(i + 1) % 4 + 20]); glVertex3fv(vertex[(i + 1) % 4 + 4]); glVertex3fv(vertex[i + 4]);
		}
		glEnd();
		// Glass
		glEnable(GL_BLEND);
		glCallList(MATERIAL_GLASS);
		glBegin(GL_TRIANGLES);
			glNormal3fv(normal[4]);
			glVertex3fv(vertex[8]); glVertex3fv(vertex[9]); glVertex3fv(vertex[10]);
			glVertex3fv(vertex[10]); glVertex3fv(vertex[11]); glVertex3fv(vertex[8]);
			glNormal3fv(normal[5]);
			glVertex3fv(vertex[16]); glVertex3fv(vertex[19]); glVertex3fv(vertex[18]);
			glVertex3fv(vertex[18]); glVertex3fv(vertex[17]); glVertex3fv(vertex[16]);
		glEnd();
		glDisable(GL_BLEND);
	glEndList();
}

void COpenGL::LoadShapeFrame()
{
	float vertex[32][6];
	int index[32][3];

	for (int i = 0; i < 16; i++) {
		vertex[i][0] = cosf(PI / 8.0f * i);
		vertex[i][1] = sinf(PI / 8.0f * i);
		vertex[i][2] = 0.0f;
		vertex[i][3] = 0.023f * cosf(PI / 8.0f * i);
		vertex[i][4] = 0.023f * sinf(PI / 8.0f * i);
		vertex[i][5] = 0.0f;
		vertex[i + 16][0] = cosf(PI / 8.0f * i);
		vertex[i + 16][1] = sinf(PI / 8.0f * i);
		vertex[i + 16][2] = 0.0f;
		vertex[i + 16][3] = 0.023f * cosf(PI / 8.0f * i);
		vertex[i + 16][4] = 0.023f * sinf(PI / 8.0f * i);
		vertex[i + 16][5] = 1.0f;
	}

	for (int i = 0; i < 16; i++) {
		index[i][0] = i;
		index[i][1] = (i + 1) % 16;
		index[i][2] = (i + 1) % 16 + 16;
		index[i + 16][0] = (i + 1) % 16 + 16;
		index[i + 16][1] = i + 16;
		index[i + 16][2] = i;
	}

	glInterleavedArrays(GL_N3F_V3F, 0, vertex);
	glNewList(SHAPE_FRAME, GL_COMPILE);
	glCallList(MATERIAL_FLAT_WHITE);
	glDrawElements(GL_TRIANGLES, 32 * 3, GL_UNSIGNED_INT, index);
	glEndList();
}

void COpenGL::LoadShapeIJoint()
{
	float vertex[34][6];
	int index[64][3];

	for (int i = 0; i < 16; i++) {
		vertex[i][0] = cosf(PI / 8.0f * i);
		vertex[i][1] = sinf(PI / 8.0f * i);
		vertex[i][2] = 0.0f;
		vertex[i][3] = 0.025f * cosf(PI / 8.0f * i);
		vertex[i][4] = 0.025f * sinf(PI / 8.0f * i);
		vertex[i][5] = 0.0f;
		vertex[i + 16][0] = cosf(PI / 8.0f * i);
		vertex[i + 16][1] = sinf(PI / 8.0f * i);
		vertex[i + 16][2] = 0.0f;
		vertex[i + 16][3] = 0.025f * cosf(PI / 8.0f * i);
		vertex[i + 16][4] = 0.025f * sinf(PI / 8.0f * i);
		vertex[i + 16][5] = 0.2f;
	}
	vertex[32][0] = 0.0f; vertex[32][1] = 0.0f; vertex[32][2] = -1.0f;
	vertex[32][3] = 0.0f; vertex[32][4] = 0.0f; vertex[32][5] = 0.0f;
	vertex[33][0] = 0.0f; vertex[33][1] = 0.0f; vertex[33][2] = 1.0f;
	vertex[33][3] = 0.0f; vertex[33][4] = 0.0f; vertex[33][5] = 0.2f;

	for (int i = 0; i < 16; i++) {
		index[i][0] = i;
		index[i][1] = (i + 1) % 16;
		index[i][2] = (i + 1) % 16 + 16;
		index[i + 16][0] = (i + 1) % 16 + 16;
		index[i + 16][1] = i + 16;
		index[i + 16][2] = i;
		index[i + 32][0] = i;
		index[i + 32][1] = 32;
		index[i + 32][2] = (i + 1) % 16;
		index[i + 48][0] = 33;
		index[i + 48][1] = i + 16;
		index[i + 48][2] = (i + 1) % 16 + 16;
	}

	glInterleavedArrays(GL_N3F_V3F, 0, vertex);
	glNewList(SHAPE_I_JOINT, GL_COMPILE);
	glCallList(MATERIAL_FLAT_GRAY);
	glDrawElements(GL_TRIANGLES, 64 * 3, GL_UNSIGNED_INT, index);
	glEndList();
}

void COpenGL::LoadShapeTJoint()
{
	LoadShapeJointPart1();
	LoadShapeJointPart2();

	glNewList(SHAPE_T_JOINT, GL_COMPILE);
	glCallList(MATERIAL_FLAT_GRAY);
	glPushMatrix();
		glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
		glCallList(SHAPE_JOINT_PART_1);
	glPopMatrix();
	glPushMatrix();
		glRotatef(90.0f, 0.0f, 1.0f, 0.0f);
		glCallList(SHAPE_JOINT_PART_1);
	glPopMatrix();
	glCallList(SHAPE_JOINT_PART_1);
	glCallList(SHAPE_JOINT_PART_2);
	glEndList();
}

void COpenGL::LoadShapeJointPart1()
{
	float vertex[33][6];
	int index[48][3];

	for (int i = 0; i < 16; i++) {
		vertex[i][0] = cosf(PI / 8.0f * i);
		vertex[i][1] = sinf(PI / 8.0f * i);
		vertex[i][2] = 0.0f;
		vertex[i][3] = 0.025f * cosf(PI / 8.0f * i);
		vertex[i][4] = 0.025f * sinf(PI / 8.0f * i);
		vertex[i][5] = 0.0f;
		vertex[i + 16][0] = cosf(PI / 8.0f * i);
		vertex[i + 16][1] = sinf(PI / 8.0f * i);
		vertex[i + 16][2] = 0.0f;
		vertex[i + 16][3] = 0.025f * cosf(PI / 8.0f * i);
		vertex[i + 16][4] = 0.025f * sinf(PI / 8.0f * i);
		vertex[i + 16][5] = 0.1f;
	}
	vertex[32][0] = 0.0f; vertex[32][1] = 0.0f; vertex[32][2] = 1.0f;
	vertex[32][3] = 0.0f; vertex[32][4] = 0.0f; vertex[32][5] = 0.1f;

	for (int i = 0; i < 16; i++) {
		index[i][0] = i;
		index[i][1] = (i + 1) % 16;
		index[i][2] = (i + 1) % 16 + 16;
		index[i + 16][0] = (i + 1) % 16 + 16;
		index[i + 16][1] = i + 16;
		index[i + 16][2] = i;
		index[i + 32][0] = 32;
		index[i + 32][1] = i + 16;
		index[i + 32][2] = (i + 1) % 16 + 16;
	}

	glInterleavedArrays(GL_N3F_V3F, 0, vertex);
	glNewList(SHAPE_JOINT_PART_1, GL_COMPILE);
	glDrawElements(GL_TRIANGLES, 48 * 3, GL_UNSIGNED_INT, index);
	glEndList();
}

void COpenGL::LoadShapeJointPart2()
{
	float vertex[114][6];
	int index[224][3];

	for (int j = 1; j < 8; j++) {
		for (int i = 0; i < 16; i++) {
			vertex[i + (j - 1) * 16][0] = cosf(PI / 8.0f * i) * sinf(PI / 8.0f * j);
			vertex[i + (j - 1) * 16][1] = sinf(PI / 8.0f * i) * sinf(PI / 8.0f * j);
			vertex[i + (j - 1) * 16][2] = cosf(PI / 8.0f * j);
			vertex[i + (j - 1) * 16][3] = 0.025f * cosf(PI / 8.0f * i) * sinf(PI / 8.0f * j);
			vertex[i + (j - 1) * 16][4] = 0.025f * sinf(PI / 8.0f * i) * sinf(PI / 8.0f * j);
			vertex[i + (j - 1) * 16][5] = 0.025f * cosf(PI / 8.0f * j);
		}
	}
	vertex[112][0] = 0.0f; vertex[112][1] = 0.0f; vertex[112][2] = -1.0f;
	vertex[112][3] = 0.0f; vertex[112][4] = 0.0f; vertex[112][5] = -0.025f;
	vertex[113][0] = 0.0f; vertex[113][1] = 0.0f; vertex[113][2] = 1.0f;
	vertex[113][3] = 0.0f; vertex[113][4] = 0.0f; vertex[113][5] = 0.025f;

	for (int j = 0; j < 6; j++) {
		for (int i = 0; i < 16; i++) {
			index[i + j * 32][0] = i + j * 16;
			index[i + j * 32][1] = (i + 1) % 16 + 16 + j * 16;
			index[i + j * 32][2] = (i + 1) % 16 + j * 16;
			index[i + 16 + j * 32][0] = (i + 1) % 16 + 16 + j * 16;
			index[i + 16 + j * 32][1] = i + j * 16;
			index[i + 16 + j * 32][2] = i + 16 + j * 16;
		}
	}
	for (int i = 0; i < 16; i++) {
		index[i + 192][0] = 113;
		index[i + 192][1] = i;
		index[i + 192][2] = (i + 1) % 16;
		index[i + 208][0] = i + 96;
		index[i + 208][1] = 112;
		index[i + 208][2] = (i + 1) % 16 + 96;
	}

	glInterleavedArrays(GL_N3F_V3F, 0, vertex);
	glNewList(SHAPE_JOINT_PART_2, GL_COMPILE);
	glDrawElements(GL_TRIANGLES, 224 * 3, GL_UNSIGNED_INT, index);
	glEndList();
}

void COpenGL::LoadShapeDrawer()
{
	float vertex[26][3] =
		{{0.25f, 0.6f, -0.25f}, {-0.25f, 0.6f, -0.25f}, {-0.25f, 0.0f, -0.25f}, {0.25f, 0.0f, -0.25f},
		{0.25f, 0.6f, 0.25f}, {-0.25f, 0.6f, 0.25f}, {-0.25f, 0.0f, 0.25f}, {0.25f, 0.0f, 0.25f},
		{0.23f, 0.58f, 0.25f}, {-0.23f, 0.58f, 0.25f}, {-0.23f, 0.02f, 0.25f}, {0.23f, 0.02f, 0.25f},
		{0.23f, 0.58f, -0.23f}, {-0.23f, 0.58f, -0.23f}, {-0.23f, 0.02f, -0.23f}, {0.23f, 0.02f, -0.23f}};
	float normal[6][3] =
		{{0.0f, 1.0f, 0.0f}, {-1.0f, 0.0f, 0.0f}, {0.0f, -1.0f, 0.0f}, {1.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 1.0f}, {0.0f, 0.0f, -1.0f}};
	glNewList(SHAPE_DRAWER, GL_COMPILE);
		glCallList(MATERIAL_FLAT_WHITE);
		glBegin(GL_TRIANGLES);
		for (int i = 0; i < 4; i++) {
			// Outside
			glNormal3fv(normal[i]);
			glVertex3fv(vertex[i]); glVertex3fv(vertex[(i + 1) % 4]); glVertex3fv(vertex[(i + 1) % 4 + 4]);
			glVertex3fv(vertex[(i + 1) % 4 + 4]); glVertex3fv(vertex[i + 4]); glVertex3fv(vertex[i]);
			// Front
			glNormal3fv(normal[4]);
			glVertex3fv(vertex[i + 4]); glVertex3fv(vertex[(i + 1) % 4 + 4]); glVertex3fv(vertex[(i + 1) % 4 + 8]);
			glVertex3fv(vertex[(i + 1) % 4 + 8]); glVertex3fv(vertex[i + 8]); glVertex3fv(vertex[i + 4]);
			// Inside
			glNormal3fv(normal[(i + 2) % 4]);
			glVertex3fv(vertex[i + 8]); glVertex3fv(vertex[(i + 1) % 4 + 8]); glVertex3fv(vertex[(i + 1) % 4 + 12]);
			glVertex3fv(vertex[(i + 1) % 4 + 12]); glVertex3fv(vertex[i + 12]); glVertex3fv(vertex[i + 8]);
		}
		// Back
		glNormal3fv(normal[5]);
		glVertex3fv(vertex[0]); glVertex3fv(vertex[3]); glVertex3fv(vertex[2]);
		glVertex3fv(vertex[2]); glVertex3fv(vertex[1]); glVertex3fv(vertex[0]);
		// Inside front
		glNormal3fv(normal[4]);
		glVertex3fv(vertex[12]); glVertex3fv(vertex[13]); glVertex3fv(vertex[14]);
		glVertex3fv(vertex[14]); glVertex3fv(vertex[15]); glVertex3fv(vertex[12]);
		glEnd();
	glEndList();
}

void COpenGL::LoadShapeDrawerPart()
{
	float vertex[28][3] =
		{{0.22f, 0.02f, -0.23f}, {-0.22f, 0.02f, -0.23f}, {-0.22f, 0.02f, 0.25f}, {0.22f, 0.02f, 0.25f},
		{0.22f, 0.25f, -0.23f}, {-0.22f, 0.25f, -0.23f}, {-0.22f, 0.25f, 0.25f}, {0.22f, 0.25f, 0.25f},
		{0.21f, 0.25f, -0.22f}, {-0.21f, 0.25f, -0.22f}, {-0.21f, 0.25f, 0.25f}, {0.21f, 0.25f, 0.25f},
		{0.21f, 0.03f, -0.22f}, {-0.21f, 0.03f, -0.22f}, {-0.21f, 0.03f, 0.25f}, {0.21f, 0.03f, 0.25f},
		{0.25f, 0.295f, 0.25f}, {-0.25f, 0.295f, 0.25f}, {-0.25f, 0.0f, 0.25f}, {0.25f, 0.0f, 0.25f},
		{0.25f, 0.295f, 0.27f}, {-0.25f, 0.295f, 0.27f}, {-0.25f, 0.0f, 0.27f}, {0.25f, 0.0f, 0.27f},
		{0.24f, 0.295f, 0.28f}, {-0.24f, 0.295f, 0.28f}, {-0.24f, 0.0f, 0.28f}, {0.24f, 0.0f, 0.28f}};
	float normal[10][3] =
		{{0.0f, 1.0f, 0.0f}, {-1.0f, 0.0f, 0.0f}, {0.0f, -1.0f, 0.0f}, {1.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 1.0f}, {0.0f, 0.0f, -1.0f},
		{0.95f, 0.0f, 0.16f}, {-0.95f, 0.0f, 0.16f}, {0.16f, 0.0f, 0.95f}, {-0.16f, 0.0f, 0.95f}};
	glNewList(SHAPE_DRAWER_PART, GL_COMPILE);
		glCallList(MATERIAL_FLAT_WHITE);
		glBegin(GL_TRIANGLES);
			// Left
			glNormal3fv(normal[3]);
			glVertex3fv(vertex[0]); glVertex3fv(vertex[4]); glVertex3fv(vertex[7]);
			glVertex3fv(vertex[7]);	glVertex3fv(vertex[3]);	glVertex3fv(vertex[0]);
			glVertex3fv(vertex[13]); glVertex3fv(vertex[9]); glVertex3fv(vertex[10]);
			glVertex3fv(vertex[10]); glVertex3fv(vertex[14]); glVertex3fv(vertex[13]);
			// Right
			glNormal3fv(normal[1]); 
			glVertex3fv(vertex[1]); glVertex3fv(vertex[2]); glVertex3fv(vertex[6]); 
			glVertex3fv(vertex[6]); glVertex3fv(vertex[5]); glVertex3fv(vertex[1]); 
			glVertex3fv(vertex[12]); glVertex3fv(vertex[15]); glVertex3fv(vertex[11]); 
			glVertex3fv(vertex[11]); glVertex3fv(vertex[8]); glVertex3fv(vertex[12]);
			// Front
			glNormal3fv(normal[4]); 
			glVertex3fv(vertex[13]); glVertex3fv(vertex[12]); glVertex3fv(vertex[8]); 
			glVertex3fv(vertex[8]); glVertex3fv(vertex[9]); glVertex3fv(vertex[13]);
			// Back
			glNormal3fv(normal[5]);
			glVertex3fv(vertex[1]); glVertex3fv(vertex[5]); glVertex3fv(vertex[4]);
			glVertex3fv(vertex[4]); glVertex3fv(vertex[0]); glVertex3fv(vertex[1]);
			// Top
			glNormal3fv(normal[0]);
			glVertex3fv(vertex[12]); glVertex3fv(vertex[13]); glVertex3fv(vertex[14]);
			glVertex3fv(vertex[14]); glVertex3fv(vertex[15]); glVertex3fv(vertex[12]);
			glVertex3fv(vertex[6]); glVertex3fv(vertex[10]); glVertex3fv(vertex[9]);
			glVertex3fv(vertex[9]); glVertex3fv(vertex[5]); glVertex3fv(vertex[10]);
			glVertex3fv(vertex[5]); glVertex3fv(vertex[9]); glVertex3fv(vertex[8]);
			glVertex3fv(vertex[8]); glVertex3fv(vertex[4]); glVertex3fv(vertex[5]);
			glVertex3fv(vertex[8]); glVertex3fv(vertex[11]); glVertex3fv(vertex[7]);
			glVertex3fv(vertex[7]); glVertex3fv(vertex[4]); glVertex3fv(vertex[8]);
			// Bottom
			glNormal3fv(normal[2]);
			glVertex3fv(vertex[0]); glVertex3fv(vertex[3]); glVertex3fv(vertex[2]);
			glVertex3fv(vertex[2]); glVertex3fv(vertex[1]); glVertex3fv(vertex[0]);
			// Cover
			glNormal3fv(normal[5]);
			glVertex3fv(vertex[16]); glVertex3fv(vertex[19]); glVertex3fv(vertex[18]);
			glVertex3fv(vertex[18]); glVertex3fv(vertex[17]); glVertex3fv(vertex[16]);
			glNormal3fv(normal[0]);
			glVertex3fv(vertex[16]); glVertex3fv(vertex[17]); glVertex3fv(vertex[21]);
			glVertex3fv(vertex[21]); glVertex3fv(vertex[20]); glVertex3fv(vertex[16]);
			glVertex3fv(vertex[20]); glVertex3fv(vertex[21]); glVertex3fv(vertex[25]);
			glVertex3fv(vertex[25]); glVertex3fv(vertex[24]); glVertex3fv(vertex[20]);
			glNormal3fv(normal[2]);
			glVertex3fv(vertex[19]); glVertex3fv(vertex[23]); glVertex3fv(vertex[22]);
			glVertex3fv(vertex[22]); glVertex3fv(vertex[18]); glVertex3fv(vertex[19]);
			glVertex3fv(vertex[23]); glVertex3fv(vertex[27]); glVertex3fv(vertex[26]);
			glVertex3fv(vertex[26]); glVertex3fv(vertex[22]); glVertex3fv(vertex[23]);
			glNormal3fv(normal[1]);
			glVertex3fv(vertex[17]); glVertex3fv(vertex[18]);
			glNormal3fv(normal[7]);
			glVertex3fv(vertex[22]); glVertex3fv(vertex[22]); glVertex3fv(vertex[21]);
			glNormal3fv(normal[1]);
			glVertex3fv(vertex[17]);
			glNormal3fv(normal[7]);
			glVertex3fv(vertex[21]); glVertex3fv(vertex[22]);
			glNormal3fv(normal[9]);
			glVertex3fv(vertex[26]); glVertex3fv(vertex[26]); glVertex3fv(vertex[25]);
			glNormal3fv(normal[7]);
			glVertex3fv(vertex[21]);
			glNormal3fv(normal[9]);
			glVertex3fv(vertex[25]); glVertex3fv(vertex[26]);
			glNormal3fv(normal[8]);
			glVertex3fv(vertex[27]); glVertex3fv(vertex[27]); glVertex3fv(vertex[24]);
			glNormal3fv(normal[9]);
			glVertex3fv(vertex[25]);
			glNormal3fv(normal[8]);
			glVertex3fv(vertex[24]); glVertex3fv(vertex[27]);
			glNormal3fv(normal[6]);
			glVertex3fv(vertex[23]); glVertex3fv(vertex[23]); glVertex3fv(vertex[20]);
			glNormal3fv(normal[8]);
			glVertex3fv(vertex[24]);
			glNormal3fv(normal[6]);
			glVertex3fv(vertex[20]); glVertex3fv(vertex[23]);
			glNormal3fv(normal[3]);
			glVertex3fv(vertex[19]); glVertex3fv(vertex[19]); glVertex3fv(vertex[16]);
			glNormal3fv(normal[6]);
			glVertex3fv(vertex[20]);
			// Handle
		glEnd();
		glPushMatrix();
			glCallList(MATERIAL_FLAT_GRAY);
			glTranslatef(0.0f, 0.2f, 0.28f);
			glScalef(0.3f, 0.3f, 0.3f);
			glPushMatrix();
				glTranslatef(-0.1f, 0.0f, 0.0f);
				glCallList(SHAPE_JOINT_PART_1);
				glTranslatef(0.0f, 0.0f, 0.1f);
				glCallList(SHAPE_JOINT_PART_2);
				glRotatef(90.0f, 0.0f, 1.0f, 0.0);
				glScalef(1.0f, 1.0f, 2.0f);
				glCallList(SHAPE_JOINT_PART_1);
			glPopMatrix();
			glPushMatrix();
				glTranslatef(0.1f, 0.0f, 0.0f);
				glCallList(SHAPE_JOINT_PART_1);
				glTranslatef(0.0f, 0.0f, 0.1f);
				glCallList(SHAPE_JOINT_PART_2);
			glPopMatrix();
		glPopMatrix();
	glEndList();
}

void COpenGL::LoadShapeBook()
{
	float vertex[8][3] =
		{{0.09f, 0.11f, 0.0f}, {-0.09f, 0.11f, 0.0f}, {-0.09f, -0.11f, 0.0f}, {0.09f, -0.11f, 0.0f},
		{0.09f, 0.11f, 0.02f}, {-0.09f, 0.11f, 0.02f}, {-0.09f, -0.11f, 0.02f}, {0.09f, -0.11f, 0.02f}};
	float normal[6][3] =
		{{0.0f, 1.0f, 0.0f}, {-1.0f, 0.0f, 0.0f}, {0.0f, -1.0f, 0.0f}, {1.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 1.0f}, {0.0f, 0.0f, -1.0f}};
	glNewList(SHAPE_BOOK, GL_COMPILE);
		glCallList(MATERIAL_BOOK);
		glEnable(GL_TEXTURE_2D);
		glBegin(GL_TRIANGLES);
			glNormal3fv(normal[0]);
			glTexCoord2f(0.5f, -1.0f); glVertex3fv(vertex[0]);
			glTexCoord2f(0.5f, -0.0f); glVertex3fv(vertex[1]);
			glTexCoord2f(0.455f, -0.0f); glVertex3fv(vertex[5]);
			glTexCoord2f(0.455f, -0.0f); glVertex3fv(vertex[5]);
			glTexCoord2f(0.455f, -1.0f); glVertex3fv(vertex[4]);
			glTexCoord2f(0.5f, -1.0f); glVertex3fv(vertex[0]);
			glNormal3fv(normal[1]);
			glTexCoord2f(0.0f, -0.0f); glVertex3fv(vertex[1]);
			glTexCoord2f(0.0f, -1.0f); glVertex3fv(vertex[2]);
			glTexCoord2f(0.045f, -1.0f); glVertex3fv(vertex[6]);
			glTexCoord2f(0.045f, -1.0f); glVertex3fv(vertex[6]);
			glTexCoord2f(0.045f, -0.0f); glVertex3fv(vertex[5]);
			glTexCoord2f(0.0f, -0.0f); glVertex3fv(vertex[1]);
			glNormal3fv(normal[2]);
			glTexCoord2f(0.5f, -1.0f); glVertex3fv(vertex[2]);
			glTexCoord2f(0.5f, -0.0f); glVertex3fv(vertex[3]);
			glTexCoord2f(0.455f, -0.0f); glVertex3fv(vertex[7]);
			glTexCoord2f(0.455f, -0.0f); glVertex3fv(vertex[7]);
			glTexCoord2f(0.455f, -1.0f); glVertex3fv(vertex[6]);
			glTexCoord2f(0.5f, -1.0f); glVertex3fv(vertex[2]);
			glNormal3fv(normal[3]);
			glTexCoord2f(0.5f, -1.0f); glVertex3fv(vertex[3]);
			glTexCoord2f(0.5f, -0.0f); glVertex3fv(vertex[0]);
			glTexCoord2f(0.455f, -0.0f); glVertex3fv(vertex[4]);
			glTexCoord2f(0.455f, -0.0f); glVertex3fv(vertex[4]);
			glTexCoord2f(0.455f, -1.0f); glVertex3fv(vertex[7]);
			glTexCoord2f(0.5f, -1.0f); glVertex3fv(vertex[3]);
			glNormal3fv(normal[4]);
			glTexCoord2f(0.455f, -0.0f); glVertex3fv(vertex[4]);
			glTexCoord2f(0.045f, -0.0f); glVertex3fv(vertex[5]);
			glTexCoord2f(0.045f, -1.0f); glVertex3fv(vertex[6]);
			glTexCoord2f(0.045f, -1.0f); glVertex3fv(vertex[6]);
			glTexCoord2f(0.455f, -1.0f); glVertex3fv(vertex[7]);
			glTexCoord2f(0.455f, -0.0f); glVertex3fv(vertex[4]);
			glNormal3fv(normal[5]);
			glTexCoord2f(0.9f, -0.0f); glVertex3fv(vertex[0]);
			glTexCoord2f(0.9f, -1.0f); glVertex3fv(vertex[3]);
			glTexCoord2f(0.5f, -1.0f); glVertex3fv(vertex[2]);
			glTexCoord2f(0.5f, -1.0f); glVertex3fv(vertex[2]);
			glTexCoord2f(0.5f, -0.0f); glVertex3fv(vertex[1]);
			glTexCoord2f(0.9f, -0.0f); glVertex3fv(vertex[0]);
		glEnd();
		glDisable(GL_TEXTURE_2D);
	glEndList();
}

void COpenGL::TurnRed()
{
	if (!m_IsOnRed) {
		glEnable(GL_LIGHT0);
		m_IsOnRed = TRUE;
	} else {
		glDisable(GL_LIGHT0);
		m_IsOnRed = FALSE;
	}
}

void COpenGL::TurnGreen()
{
	if (!m_IsOnGreen) {
		glEnable(GL_LIGHT1);
		m_IsOnGreen = TRUE;
	} else {
		glDisable(GL_LIGHT1);
		m_IsOnGreen = FALSE;
	}
}

void COpenGL::TurnBlue()
{
	if (!m_IsOnBlue) {
		glEnable(GL_LIGHT2);
		m_IsOnBlue = TRUE;
	} else {
		glDisable(GL_LIGHT2);
		m_IsOnBlue = FALSE;
	}
}

void COpenGL::MoveStatusDrawerPart1()
{
	if (m_StatusDrawerPart1 == 1) {
		if (m_zDrawerPart1 >= 0.2f) m_StatusDrawerPart1 = 2;
		else m_zDrawerPart1 += 0.01f;
	} else if (m_StatusDrawerPart1 == 3) {
		if (m_zDrawerPart1 <= 0.0f) m_StatusDrawerPart1 = 0;
		else m_zDrawerPart1 -= 0.01f;
	}
}

void COpenGL::MoveStatusDrawerPart2()
{
	if (m_StatusDrawerPart2 == 1) {
		if (m_zDrawerPart2 >= 0.2f) m_StatusDrawerPart2 = 2;
		else m_zDrawerPart2 += 0.01f;
	} else if (m_StatusDrawerPart2 == 3) {
		if (m_zDrawerPart2 <= 0.0f) m_StatusDrawerPart2 = 0;
		else m_zDrawerPart2 -= 0.01f;
	}
}

void COpenGL::SetStatusDrawerPart1()
{
	if (m_StatusDrawerPart1 == 0) {
		m_StatusDrawerPart1 = 1;
	} else if (m_StatusDrawerPart1 == 2) {
		m_StatusDrawerPart1 = 3;
	} 
}

void COpenGL::SetStatusDrawerPart2()
{
	if (m_StatusDrawerPart2 == 0) {
		m_StatusDrawerPart2 = 1;
	} else if (m_StatusDrawerPart2 == 2) {
		m_StatusDrawerPart2 = 3;
	} 
}
