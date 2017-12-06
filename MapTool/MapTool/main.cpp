#include "Define.h"

#pragma comment(linker , "/entry:WinMainCRTStartup /subsystem:console")


HINSTANCE g_hInst;

HWND g_hWnd;
HWND g_hProjectionInfoDlg;
HWND g_hObjectInfoDlg;
HWND g_hObjectInfoModifyDlg;
HWND g_hObjectTab;
HWND g_hViewList[2];

void SetUpRC();
void RenderScene();
void Reshape(int w, int h);
void Idle();
void InitTab(HWND& hWnd);

void AddObject();


GLvoid Mouse(int button, int state, int x, int y);
GLvoid MouseMotion(int x, int y);
GLvoid Keyboard(unsigned char key, int x, int y);
GLvoid SpecialKeyboard(int key, int x, int y);
void WheelFunc(int wheel, int dir, int x, int y);

RECT rcWindow;

BOOL CALLBACK PerspectiveInfoDlgProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam);
BOOL CALLBACK ObjectListProc(HWND hDlg, UINT iMessage, WPARAM wParam, LPARAM lParam);
BOOL CALLBACK ObjectInfoProc(HWND hDlg, UINT iMessage, WPARAM wParam, LPARAM lParam);
BOOL CALLBACK ObjectInfoModifyProc(HWND hDlg, UINT iMessage, WPARAM wParam, LPARAM lParam);

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance
	, LPSTR lpszCmdParam, int nCmdShow)
{
	
	HWND hWnd;

	g_hInst = hInstance;

	hWnd = CreateDialog(g_hInst, MAKEINTRESOURCE(IDD_OBJECT_LIST), NULL, ObjectListProc);
	ShowWindow(hWnd, SW_SHOW);
	g_hProjectionInfoDlg = CreateDialog(g_hInst, MAKEINTRESOURCE(IDD_PERSPECTIVE_DIG), NULL, PerspectiveInfoDlgProc);
	ShowWindow(g_hProjectionInfoDlg, SW_SHOW);

	g_hObjectInfoDlg = CreateDialog(g_hInst, MAKEINTRESOURCE(IDD_OBJECT_INFO), NULL, ObjectInfoProc);
	ShowWindow(g_hObjectInfoDlg, SW_SHOW);

	g_hObjectInfoModifyDlg = CreateDialog(g_hInst, MAKEINTRESOURCE(IDD_OBJECT_INFO), NULL, ObjectInfoModifyProc);
	ShowWindow(g_hObjectInfoModifyDlg, SW_SHOW);

	g_hWnd = hWnd;
	char *myargv[1];
	int myargc = 1;
	myargv[0] = strdup("Myappname");
	glutInit(&myargc, myargv);
	SetUpRC();
	glutCreateWindow("MapTool");
	glutDisplayFunc(RenderScene);
	glutReshapeFunc(Reshape);
	glutMouseFunc(Mouse);
	glutKeyboardFunc(Keyboard);
	glutSpecialFunc(SpecialKeyboard);
	glutMouseWheelFunc(WheelFunc);
	glutMotionFunc(MouseMotion);
	glutIdleFunc(Idle);
	glutMainLoop();
	//GAMEMANAGER->Initiallize(hWnd);

	return 0;
}

BOOL CALLBACK PerspectiveInfoDlgProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	char fovy[40], Near[40], Far[40]{0};
	sprintf(fovy, "%0.3f", RENDERMANAGER->GetPerspective().Fovy);
	sprintf(Near, "%0.3f", RENDERMANAGER->GetPerspective().Near);
	sprintf(Far, "%0.3f", RENDERMANAGER->GetPerspective().Far);
	switch (iMessage) {
	case WM_INITDIALOG:
		SetWindowPos(hWnd, NULL, WINDOW_INIT_X + WINDOW_WIDTH, TAB_WINDOW_INIT_Y, NULL, NULL, SWP_NOSIZE);
		SetDlgItemText(hWnd, IDC_PERSPECTIVE_FOVY_EDIT, fovy);
		SetDlgItemText(hWnd, IDC_PERSPECTIVE_NEAR_EDIT, Near);
		SetDlgItemText(hWnd, IDC_PERSPECTIVE_FAR_EDIT, Far);
		break;

	case WM_COMMAND:
		switch (LOWORD(wParam)) {
		case IDC_PROJECTION_APPLY_BUTTON:
			GetDlgItemText(hWnd, IDC_PERSPECTIVE_FOVY_EDIT, fovy, 40);
			GetDlgItemText(hWnd, IDC_PERSPECTIVE_NEAR_EDIT, Near, 40);
			GetDlgItemText(hWnd, IDC_PERSPECTIVE_FAR_EDIT, Far, 40);
			RENDERMANAGER->SetPerspective(Perspective(atof(fovy), atof(Near), atof(Far)));
			break;
		}

	}
	return 0;
}

BOOL CALLBACK ObjectInfoProc(HWND hDlg, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	static RECT rcWindow;
	char color[3][40];
	char pos[3][40];
	char rotation[4][40];
	char scale[3][40];
	char size[40];
	Color initColor;
	Vector3 initPos;
	Vector3 initScale(1.0f, 1.0f, 1.0f);
	Vector4 initRotation;

	sprintf(color[0], "%0.1f", initColor.r);
	sprintf(color[1], "%0.1f", initColor.g);
	sprintf(color[2], "%0.1f", initColor.b);

	sprintf(pos[0], "%0.1f", initPos.x);
	sprintf(pos[1], "%0.1f", initPos.y);
	sprintf(pos[2], "%0.1f", initPos.z);

	sprintf(rotation[0], "%0.1f", initRotation.x);
	sprintf(rotation[1], "%0.1f", initRotation.y);
	sprintf(rotation[2], "%0.1f", initRotation.z);
	sprintf(rotation[3], "%0.1f", initRotation.w);

	sprintf(scale[0], "%0.1f", initScale.x);
	sprintf(scale[1], "%0.1f", initScale.y);
	sprintf(scale[2], "%0.1f", initScale.z);

	sprintf(size, "%d", 3);


	switch (iMessage) {
	case WM_INITDIALOG:
		RENDERMANAGER->SetObjectInfoDlg(hDlg);
		GetWindowRect(hDlg, &rcWindow);
		SetWindowPos(hDlg, NULL, WINDOW_INIT_X - rcWindow.right, TAB_WINDOW_INIT_Y + 345, NULL, NULL, SWP_NOSIZE);
		SetDlgItemText(hDlg, IDC_COLOR_R_EDIT, color[0]);
		SetDlgItemText(hDlg, IDC_COLOR_G_EDIT, color[1]);
		SetDlgItemText(hDlg, IDC_COLOR_B_EDIT, color[2]);

		SetDlgItemText(hDlg, IDC_POS_X_EDIT, pos[0]);
		SetDlgItemText(hDlg, IDC_POS_Y_EDIT, pos[1]);
		SetDlgItemText(hDlg, IDC_POS_Z_EDIT, pos[2]);

		SetDlgItemText(hDlg, IDC_ROTATION_X_EDIT, rotation[0]);
		SetDlgItemText(hDlg, IDC_ROTATION_Y_EDIT, rotation[1]);
		SetDlgItemText(hDlg, IDC_ROTATION_Z_EDIT, rotation[2]);
		SetDlgItemText(hDlg, IDC_ROTATION_ANGLE_EDIT, rotation[3]);

		SetDlgItemText(hDlg, IDC_SCALE_X_EDIT, color[0]);
		SetDlgItemText(hDlg, IDC_SCALE_Y_EDIT, color[1]);
		SetDlgItemText(hDlg, IDC_SCALE_Z_EDIT, color[2]);

		SetDlgItemText(hDlg, IDC_SIZE_EDIT, size);
		break;

	case WM_COMMAND:
		switch (LOWORD(wParam)) {
		case IDC_OBJECT_INFO_APPLY_BUTTON:
			AddObject();
			break;
		}

	}
	return 0;
}

BOOL CALLBACK ObjectInfoModifyProc(HWND hDlg, UINT iMessage, WPARAM wParam, LPARAM lParam)
{

	switch (iMessage) {
	case WM_INITDIALOG:
		SetWindowPos(hDlg, NULL, WINDOW_INIT_X + WINDOW_WIDTH, TAB_WINDOW_INIT_Y + 345, NULL, NULL, SWP_NOSIZE);
		SetDlgItemText(hDlg, IDC_OBJECT_INFO_APPLY_BUTTON, "Modify");
		RENDERMANAGER->SetObjectModifyDlg(hDlg);
		break;
	case WM_COMMAND:
		switch (LOWORD(wParam)) {
		case IDC_OBJECT_INFO_APPLY_BUTTON: RENDERMANAGER->ModifySelectedObject(); break;
		}
	}

	return 0;
}
BOOL CALLBACK ObjectListProc(HWND hDlg, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	int sel{};
	switch (iMessage) {
	case WM_INITDIALOG: {
		InitTab(hDlg);
		DIALOGMANAGER->Init(hDlg, g_hInst);
		DIALOGMANAGER->ChangeViewList(sel);
		RENDERMANAGER->Init();
		//SetDlgItemText(hDlg, IDC_NAME_STATIC, "the new text");
		break;
	}
	case WM_NOTIFY:
		LPNMHDR hdr;
		LPNMLISTVIEW nlv;
		hdr = (LPNMHDR)lParam;
		nlv = (LPNMLISTVIEW)lParam;

		switch (hdr->code) {
		case TCN_SELCHANGE:
			sel = TabCtrl_GetCurSel(g_hObjectTab);
			DIALOGMANAGER->ChangeViewList(sel);
			break;

		case NM_CLICK: DIALOGMANAGER->SelectItem(sel); break;
	
		case LVN_BEGINDRAG:
			// 드래그되는 항목 저장
			DIALOGMANAGER->SetDrag(nlv->iItem, sel, hdr);
			break;
		}

	case WM_MOUSEMOVE:
		DIALOGMANAGER->MouseMove(lParam);
		break;

	case WM_LBUTTONUP:
		DIALOGMANAGER->MouseButtonUp();
		/*
		if (LOWORD(lParam) > rcWindow.right) {
			RENDERMANAGER->MoveObject(LOWORD(lParam) - rcWindow.right, HIWORD(lParam));
			RENDERMANAGER->AddObject(LOWORD(lParam) - rcWindow.right, HIWORD(lParam));
		}
		*/
		break;

	case WM_RBUTTONDOWN:
		break;
	case WM_COMMAND:
		switch (LOWORD(wParam)) {
		case IDCANCEL:
			EndDialog(hDlg, IDCANCEL);
			PostQuitMessage(0);
			return TRUE;
		}
	}

	return 0;
}


void InitTab(HWND& hWnd)
{
	TCITEM tie;

	GetWindowRect(hWnd, &rcWindow);
	SetWindowPos(hWnd, NULL, WINDOW_INIT_X - rcWindow.right, TAB_WINDOW_INIT_Y, NULL, NULL, SWP_NOSIZE);
	g_hObjectTab = GetDlgItem(hWnd, IDC_OBJECT_TAB);
	tie.mask = TCIF_TEXT;
	tie.pszText = "Shape";
	TabCtrl_InsertItem(g_hObjectTab, 0, &tie);
	tie.pszText = "Object2";
	TabCtrl_InsertItem(g_hObjectTab, 1, &tie);



}



void SetUpRC()
{
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	glFrontFace(GL_CCW);
	glEnable(GL_DEPTH_TEST);
	glutInitWindowPosition(WINDOW_INIT_X, WINDOW_INIT_Y);
	glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);


}

void RenderScene()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glEnable(GL_DEPTH_TEST);
	CAMERAMANAGER->Update();

	RENDERMANAGER->Render();
	
	glutSwapBuffers(); // Draw

}

void Reshape(int w, int h)
{
	RENDERMANAGER->Resize(w, h);

}


GLvoid Mouse(int button, int state, int x, int y)
{
	if(state == GLUT_DOWN) CAMERAMANAGER->SetButton(button, x, y);
}

void Idle()
{
	RenderScene();
}

GLvoid Keyboard(unsigned char key, int x, int y)
{

	switch (key) {
	case 'X':
	case 'y':
	case 'Y': CAMERAMANAGER->SetRotate(key); break;

	case 'w':
	case 'a':
	case 'd':
	case 'q':
	case 'e':
	case 'z':
	case 'x': CAMERAMANAGER->SetMove(key); break;

	case 'i': CAMERAMANAGER->Reset(); break;
	case 'r': RENDERMANAGER->GoToStartPos(); break;
	case 's': {
		int mod = glutGetModifiers();
		if (mod && GLUT_ACTIVE_CTRL | GLUT_ACTIVE_ALT)  FILEMANAGER->SaveFile();
		else CAMERAMANAGER->SetMove(key);
		break;
	}
	case 'o': {
		int mod = glutGetModifiers();
		if (mod && GLUT_ACTIVE_CTRL | GLUT_ACTIVE_ALT)  FILEMANAGER->LoadFile();
		break;
	}

	case '4':
	case '6':
	case '8':
	case '5':
	case '+':
	case '-': if (RENDERMANAGER->haveObject()) RENDERMANAGER->MoveSelectedObject(key); break;

	case 127: RENDERMANAGER->DeleteObject(); break;
	case ' ':  AddObject(); break;
	default: break;
	}
	RenderScene();
}

void WheelFunc(int wheel, int dir, int x, int y)
{
	CAMERAMANAGER->Wheel(dir);
}

GLvoid MouseMotion(int x, int y)
{
	if (CAMERAMANAGER->GetButton() == GLUT_RIGHT_BUTTON) {
		CAMERAMANAGER->OnMouseMove(CAMERAMANAGER->GetLastCurPos().x - x, CAMERAMANAGER->GetLastCurPos().y - y);
		CAMERAMANAGER->SetLastCurPos(x, y);
	}
	//else RENDERMANAGER->MoveObject(x, y);
}

GLvoid SpecialKeyboard(int key, int x, int y)
{
	//if(key == GLUT_KEY
}

void AddObject()
{
	char color[3][40];
	char pos[3][40];
	char rotation[4][40];
	char scale[3][40];
	char size[40];

	GetDlgItemText(g_hObjectInfoDlg, IDC_COLOR_R_EDIT, color[0], 40);
	GetDlgItemText(g_hObjectInfoDlg, IDC_COLOR_G_EDIT, color[1], 40);
	GetDlgItemText(g_hObjectInfoDlg, IDC_COLOR_B_EDIT, color[2], 40);

	GetDlgItemText(g_hObjectInfoDlg, IDC_POS_X_EDIT, pos[0], 40);
	GetDlgItemText(g_hObjectInfoDlg, IDC_POS_Y_EDIT, pos[1], 40);
	GetDlgItemText(g_hObjectInfoDlg, IDC_POS_Z_EDIT, pos[2], 40);

	GetDlgItemText(g_hObjectInfoDlg, IDC_ROTATION_X_EDIT, rotation[0], 40);
	GetDlgItemText(g_hObjectInfoDlg, IDC_ROTATION_Y_EDIT, rotation[1], 40);
	GetDlgItemText(g_hObjectInfoDlg, IDC_ROTATION_Z_EDIT, rotation[2], 40);
	GetDlgItemText(g_hObjectInfoDlg, IDC_ROTATION_ANGLE_EDIT, rotation[3], 40);

	GetDlgItemText(g_hObjectInfoDlg, IDC_SCALE_X_EDIT, scale[0], 40);
	GetDlgItemText(g_hObjectInfoDlg, IDC_SCALE_Y_EDIT, scale[1], 40);
	GetDlgItemText(g_hObjectInfoDlg, IDC_SCALE_Z_EDIT, scale[2], 40);

	GetDlgItemText(g_hObjectInfoDlg, IDC_SIZE_EDIT, size, 40);

	RENDERMANAGER->AddObject(Object(DIALOGMANAGER->GetSelectedObject(), Color(atof(color[0]), atof(color[1]), atof(color[2])),
		Vector3(atof(pos[0]), atof(pos[1]), atof(pos[2])),
		Vector4(atof(rotation[0]), atof(rotation[1]), atof(rotation[2]), atof(rotation[3])),
		Vector3(atof(scale[0]), atof(scale[1]), atof(scale[2])), atoi(size)));


}

