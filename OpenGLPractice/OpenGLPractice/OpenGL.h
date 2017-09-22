// OpenGL.h: interface for the COpenGL class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_OPENGL_H__1D5C692F_D7A4_4148_8AB8_2E1B9BD0C0DB__INCLUDED_)
#define AFX_OPENGL_H__1D5C692F_D7A4_4148_8AB8_2E1B9BD0C0DB__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Texture.h"


#define ORTHO_VIEW			1
#define PERSPECTIVE_VIEW	2

#define PI	3.141592f

class COpenGL  
{
public:
	COpenGL();
	virtual ~COpenGL();

	// Functions for moving & Mouse
	void SetLButtonStatus(BOOL IsDown);
	void SetMButtonStatus(BOOL IsDown);
	void StartMouseMove(float x, float y);
	void DoMouseMove(float x, float y);
	void Zoom(float delta) {m_depth += delta;};

	// Setup & Draw functions
	static void Resize(int w, int h);
	static void Release();
	void Init();
	void Draw();

	// Functions for light
	void TurnRed();
	void TurnGreen();
	void TurnBlue();
	BOOL GetRed() {return m_IsOnRed;};
	BOOL GetGreen() {return m_IsOnGreen;};
	BOOL GetBlue() {return m_IsOnBlue;};

	// Functions for case
	void SetStatusDrawerPart1();
	void SetStatusDrawerPart2();
	void MoveStatusDrawerPart1();
	void MoveStatusDrawerPart2();
	int GetStatusDrawerPart1() {return m_StatusDrawerPart1;};
	int GetStatusDrawerPart2() {return m_StatusDrawerPart2;};

private:
	// Shape Loading functions
	void LoadShapeBook();
	void LoadShapeDrawerPart();
	void LoadShapeDrawer();
	void LoadShapeJointPart2();
	void LoadShapeJointPart1();
	void LoadShapeTJoint();
	void LoadShapeIJoint();
	void LoadShapeFrame();
	void LoadShapeBoard();
	void LoadShape();

	// Material Loading function
	void LoadMaterial();

	// Setup & Rendering fuctions
	void SetupRC();
	void RenderScene();
	
	// Texture
	CTexture m_Texture;

	// valiables for moving & Mouse
	float m_xRot;
	float m_yRot;
	float m_depth;
	
	float m_oldX;
	float m_oldY;

	BOOL m_IsLButtonDown;
	BOOL m_IsMButtonDown;

	// 조명을 위한 변수들
	BOOL m_IsOnRed;
	BOOL m_IsOnGreen;
	BOOL m_IsOnBlue;

	// 서랍을 위한 변수들
	int m_StatusDrawerPart1;
	int m_StatusDrawerPart2;
	float m_zDrawerPart1;
	float m_zDrawerPart2;
};

#endif // !defined(AFX_OPENGL_H__1D5C692F_D7A4_4148_8AB8_2E1B9BD0C0DB__INCLUDED_)
