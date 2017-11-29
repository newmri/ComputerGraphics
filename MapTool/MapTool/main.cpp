#include "Define.h"

#pragma comment(linker , "/entry:WinMainCRTStartup /subsystem:console")


HINSTANCE g_hInst;

HWND g_hWnd;
HWND g_hProjectionInfoDlg;
HWND g_hObjectTab;
HWND g_hViewList[2];

void SetUpRC();
void RenderScene();
void Reshape(int w, int h);
void Idle();
void InitTab(HWND& hWnd);
void InitViewList(HWND& hWnd);
void ChangeViewList(const int& sel);

GLvoid Mouse(int button, int state, int x, int y);
GLvoid MouseMotion(int x, int y);
GLvoid Keyboard(unsigned char key, int x, int y);
void WheelFunc(int wheel, int dir, int x, int y);

RECT rcWindow;
Vector3 v;

BOOL CALLBACK PerspectiveInfoDlgProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam);
BOOL CALLBACK ObjectListProc(HWND hDlg, UINT iMessage, WPARAM wParam, LPARAM lParam);

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance
	, LPSTR lpszCmdParam, int nCmdShow)
{
	
	HWND hWnd;

	g_hInst = hInstance;

	hWnd = CreateDialog(g_hInst, MAKEINTRESOURCE(IDD_OBJECT_LIST), NULL, ObjectListProc);
	ShowWindow(hWnd, SW_SHOW);
	g_hProjectionInfoDlg = CreateDialog(g_hInst, MAKEINTRESOURCE(IDD_PERSPECTIVE_DIG), NULL, PerspectiveInfoDlgProc);
	ShowWindow(g_hProjectionInfoDlg, SW_SHOW);

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
BOOL CALLBACK ObjectListProc(HWND hDlg, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	int sel{};
	switch (iMessage) {
	case WM_INITDIALOG:
		InitTab(hDlg);
		MOUSEMANAGER->Init(hDlg, g_hInst);
		InitViewList(hDlg);
		ChangeViewList(sel);
		break;
	case WM_NOTIFY:
		LPNMHDR hdr;
		LPNMLISTVIEW nlv;
		hdr = (LPNMHDR)lParam;
		nlv = (LPNMLISTVIEW)lParam;

		switch (hdr->code) {
		case TCN_SELCHANGE:
			sel = TabCtrl_GetCurSel(g_hObjectTab);
			ChangeViewList(sel);
			break;
		case LVN_BEGINDRAG:
			// 드래그되는 항목 저장
			MOUSEMANAGER->SetDrag(nlv->iItem, sel, hdr);
			break;
		}

	case WM_MOUSEMOVE:
		MOUSEMANAGER->MouseMove(lParam);
		break;

	case WM_LBUTTONUP:
		MOUSEMANAGER->MouseButtonUp();

		if (LOWORD(lParam) > rcWindow.right) {
			RENDERMANAGER->MoveObject(LOWORD(lParam) - rcWindow.right, HIWORD(lParam));
		}
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
	tie.pszText = "Brick";
	TabCtrl_InsertItem(g_hObjectTab, 0, &tie);
	tie.pszText = "Object2";
	TabCtrl_InsertItem(g_hObjectTab, 1, &tie);



}

void InitViewList(HWND& hWnd)
{
	LVITEM ritem;
	HIMAGELIST hSmall;

	for (int i = 0; i < OBJECT_SELECT_TYPE::END; ++i)
		g_hViewList[i] = CreateWindow(WC_LISTVIEW, NULL, WS_CHILD | LVS_SMALLICON | WS_VISIBLE,
			30, 70, 100, 100, hWnd, (HMENU)0, g_hInst, NULL);


	hSmall = ImageList_LoadBitmap(g_hInst, MAKEINTRESOURCE(IDB_BITMAP2), 16, 1, RGB(192, 192, 192));
	SendMessage(g_hViewList[0], LVM_SETIMAGELIST, (WPARAM)LVSIL_SMALL, (LPARAM)hSmall);

	ritem.mask = LVIF_TEXT | LVIF_IMAGE;
	ritem.state = 0;
	ritem.stateMask = 0;
	ritem.iImage = 1;
	ritem.iSubItem = 0;
	ritem.iItem = 0;
	ritem.pszText = "Brick";
	SendMessage(g_hViewList[0], LVM_INSERTITEM, 0, (LPARAM)&ritem);

	hSmall = ImageList_LoadBitmap(g_hInst, MAKEINTRESOURCE(IDB_BITMAP2), 16, 1, RGB(192, 192, 192));
	SendMessage(g_hViewList[1], LVM_SETIMAGELIST, (WPARAM)LVSIL_SMALL, (LPARAM)hSmall);

	ritem.mask = LVIF_TEXT | LVIF_IMAGE;
	ritem.state = 0;
	ritem.stateMask = 0;
	ritem.iImage = 1;
	ritem.iSubItem = 0;
	ritem.iItem = 0;
	ritem.pszText = "Obstacle";
	SendMessage(g_hViewList[1], LVM_INSERTITEM, 0, (LPARAM)&ritem);

	/*
	ritem.iSubItem = 0;
	ritem.iItem = 1;
	ritem.pszText = L"Jone";
	SendMessage(hList, LVM_INSERTITEM, 0, (LPARAM)&ritem);
	*/
}



void ChangeViewList(const int& sel)
{
	for (int i = 0; i < OBJECT_SELECT_TYPE::END; ++i) ShowWindow(g_hViewList[i], SW_HIDE);
	ShowWindow(g_hViewList[sel], SW_SHOW);
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

	glPushMatrix();
	glTranslatef(RENDERMANAGER->GetObjPos().x, RENDERMANAGER->GetObjPos().y, RENDERMANAGER->GetObjPos().z);
	//glutSolidCube(3);
	glPopMatrix();

	//glutSolidCube(50);

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
	case 'x':
	case 'X':
	case 'y':
	case 'Y':
	case 'z':
	case 'Z': CAMERAMANAGER->SetRotate(key); break;

	case 'w':
	case 's':
	case 'a':
	case 'd':
	case 'q':
	case 'e':
	case '+':
	case '-': CAMERAMANAGER->SetMove(key);break;
	case 'i': CAMERAMANAGER->Reset(); break;

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
	if(CAMERAMANAGER->GetButton() == GLUT_RIGHT_BUTTON) CAMERAMANAGER->OnMouseMove(x, y);
	else RENDERMANAGER->MoveObject(x, y);
}