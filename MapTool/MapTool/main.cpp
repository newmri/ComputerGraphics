#include "Define.h"

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
BOOL CALLBACK ObjectListProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam);
HINSTANCE g_hInst;
LPCTSTR lpszClass = TEXT("MapTool");

HWND g_hWnd;
HWND g_hObjectTab;
HWND g_hObjectList;

void InitTab(HWND& hWnd);
void InitViewList(HWND& hWnd);
int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance
	, LPSTR lpszCmdParam, int nCmdShow)
{
	HWND hWnd;
	MSG Message;
	WNDCLASS WndClass;
	g_hInst = hInstance;

	WndClass.cbClsExtra = 0;
	WndClass.cbWndExtra = 0;
	WndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	WndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	WndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	WndClass.hInstance = hInstance;
	WndClass.lpfnWndProc = WndProc;
	WndClass.lpszClassName = lpszClass;
	WndClass.lpszMenuName = MAKEINTRESOURCE(MAIN_MENU);
	WndClass.style = CS_HREDRAW | CS_VREDRAW;
	RegisterClass(&WndClass);

	hWnd = CreateWindow(lpszClass, lpszClass, WS_OVERLAPPEDWINDOW,
		WINDOW_INIT_X, WINDOW_INIT_Y, WINDOW_WIDTH, WINDOW_HEIGHT,
		NULL, (HMENU)NULL, hInstance, NULL);
	ShowWindow(hWnd, nCmdShow);

	g_hWnd = hWnd;

	//GAMEMANAGER->Initiallize(hWnd);

	DWORD dwTime = GetTickCount();

	memset(&Message, 0, sizeof(Message));
	while (Message.message != WM_QUIT) {
		if (PeekMessage(&Message, NULL, 0, 0, PM_REMOVE)) {
			TranslateMessage(&Message);
			DispatchMessage(&Message);
		}

		else {
			//if (dwTime + 0 < GetTickCount()) GAMEMANAGER->Update();
		}

	}
	return (int)Message.wParam;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	HWND hDlg;
	switch (iMessage) {
	case WM_CREATE:
		hDlg = CreateDialog(g_hInst, MAKEINTRESOURCE(IDD_OBJECT_LIST), hWnd, ObjectListProc);
		ShowWindow(hDlg, SW_SHOW);
		break;
	case WM_PAINT:
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}
	return(DefWindowProc(hWnd, iMessage, wParam, lParam));
}

BOOL CALLBACK ObjectListProc(HWND hDlg, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	int sel;

	switch (iMessage) {
	case WM_INITDIALOG:
		InitTab(hDlg);
		InitViewList(hDlg);
		break;
	case WM_NOTIFY:
		switch (((LPNMHDR)lParam)->code) {
		case TCN_SELCHANGE:
			sel = TabCtrl_GetCurSel(g_hObjectTab);
			break;
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
	tie.pszText = L"Object1";
	TabCtrl_InsertItem(g_hObjectTab, 0, &tie);
	tie.pszText = L"Object2";
	TabCtrl_InsertItem(g_hObjectTab, 1, &tie);

}

void InitViewList(HWND& hWnd)
{
	LVITEM ritem;
	HIMAGELIST hSmall;

	g_hObjectList = GetDlgItem(hWnd, IDC_LIST1);

	g_hObjectList = CreateWindow(WC_LISTVIEW, NULL, WS_CHILD | LVS_SMALLICON | WS_VISIBLE,
		30, 70, 100, 100, hWnd, (HMENU)0, g_hInst, NULL);

	hSmall = ImageList_LoadBitmap(g_hInst, MAKEINTRESOURCE(IDB_BITMAP2), 16, 1, RGB(192, 192, 192));
	SendMessage(g_hObjectList, LVM_SETIMAGELIST, (WPARAM)LVSIL_SMALL, (LPARAM)hSmall);

	ritem.mask = LVIF_TEXT | LVIF_IMAGE;
	ritem.state = 0;
	ritem.stateMask = 0;
	ritem.iImage = 1;
	ritem.iSubItem = 0;
	ritem.iItem = 0;
	ritem.pszText = L"Jone";
	SendMessage(g_hObjectList, LVM_INSERTITEM, 0, (LPARAM)&ritem);

	/*
	ritem.iSubItem = 0;
	ritem.iItem = 1;
	ritem.pszText = L"Jone";
	SendMessage(hList, LVM_INSERTITEM, 0, (LPARAM)&ritem);
	*/
}