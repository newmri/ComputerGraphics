#include "Define.h"

#pragma comment(linker , "/entry:WinMainCRTStartup /subsystem:console")

BOOL CALLBACK ObjectListProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam);
BOOL CALLBACK ProjectionInfoDlgProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam);

HINSTANCE g_hInst;

HWND g_hWnd;
HWND g_hProjectionInfoDlg;
HWND g_hObjectTab;
HWND g_hViewList[2];

double g_projection_fovy{ REAL_WINDOW_FOVY }, g_projection_w{ WINDOW_WIDTH }, g_projection_h{ WINDOW_HEIGHT }, g_projection_far{ WINDOW_DEPTH };
float g_projection_z{ -80.0f };

void SetUpRC();
void RenderScene();
void Reshape(int w, int h);

void InitTab(HWND& hWnd);
void InitViewList(HWND& hWnd);
void ChangeViewList(const int& sel);
void ChangeProjection(const double fovy, const double w, const double h, const double f, const float z);

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance
	, LPSTR lpszCmdParam, int nCmdShow)
{
	HWND hWnd;

	g_hInst = hInstance;

	hWnd = CreateDialog(g_hInst, MAKEINTRESOURCE(IDD_OBJECT_LIST), NULL, ObjectListProc);
	ShowWindow(hWnd, SW_SHOW);
	g_hProjectionInfoDlg = CreateDialog(g_hInst, MAKEINTRESOURCE(IDD_PROJECTION_DIG), NULL, ProjectionInfoDlgProc);
	ShowWindow(g_hProjectionInfoDlg, SW_SHOW);

	g_hWnd = hWnd;
	
	SetUpRC();
	glutCreateWindow("MapTool");
	glutDisplayFunc(RenderScene);
	glutReshapeFunc(Reshape);
	glutMainLoop();
	//GAMEMANAGER->Initiallize(hWnd);

	return 0;
}



BOOL CALLBACK ProjectionInfoDlgProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	char fovy[10], w[10], h[10], f[10], z[10]{};
	switch (iMessage) {
	case WM_INITDIALOG:
		SetWindowPos(hWnd, NULL, WINDOW_INIT_X + WINDOW_WIDTH, WINDOW_INIT_Y, NULL, NULL, SWP_NOSIZE);
		break;

	case WM_COMMAND:
		switch (LOWORD(wParam)) {
		case IDC_PROJECTION_APPLY_BUTTON:
			GetDlgItemText(hWnd, IDC_PROJECTION_FOVY_EDIT, fovy, 10);
			GetDlgItemText(hWnd, IDC_PROJECTION_W_EDIT, w, 10);
			GetDlgItemText(hWnd, IDC_PROJECTION_H_EDIT, h, 10);
			GetDlgItemText(hWnd, IDC_PROJECTION_F_EDIT, f, 10);
			GetDlgItemText(hWnd, IDC_PROJECTION_Z_EDIT, z, 10);

			ChangeProjection(atof(fovy), atof(w), atof(h), atof(f), atof(z));
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
		InitViewList(hDlg);
		ChangeViewList(sel);
		break;
	case WM_NOTIFY:
		switch (((LPNMHDR)lParam)->code) {
		case TCN_SELCHANGE:
			sel = TabCtrl_GetCurSel(g_hObjectTab);
			ChangeViewList(sel);
			break;
		}

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

	SetWindowPos(hWnd, NULL, 0, WINDOW_INIT_Y, NULL, NULL, SWP_NOSIZE);
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

	for(int i = 0; i < OBJECT_SELECT_TYPE::END; ++i)
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

	glutSwapBuffers(); // Draw
}

void Reshape(int w, int h)
{
	glViewport(0, 0, w, h); // Change viewport with window size
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(g_projection_fovy, g_projection_w / g_projection_h, 1.0, g_projection_far); // Use perspective
	glTranslatef(0.0f, 0.0f, g_projection_z);

}

void ChangeProjection(const double fovy, const double w, const double h, const double f, const float z)
{
	g_projection_fovy = fovy;
	g_projection_w = w;
	g_projection_h = h;
	g_projection_far = f;
	g_projection_z = z;
	cout << z << endl;
}