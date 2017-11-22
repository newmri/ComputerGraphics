#include "Define.h"

CMouseManager* CMouseManager::m_instance = nullptr;

void CMouseManager::Init(HWND& hDlg, HINSTANCE& hInst)
{
	m_hDlg = hDlg;
	m_hInst = hInst;
	m_dragStart = false;
	m_pt.x = 0;
	m_pt.y = 0;

	this->InitViewList();
}

void CMouseManager::InitViewList()
{
	LVITEM ritem;
	HIMAGELIST hSmall;

	for (int i = 0; i < OBJECT_SELECT_TYPE::END; ++i)
		m_hViewList[i] = CreateWindow(WC_LISTVIEW, NULL, WS_CHILD | LVS_SMALLICON | WS_VISIBLE,
			30, 70, 100, 100, m_hDlg, (HMENU)0, m_hInst, NULL);


	hSmall = ImageList_LoadBitmap(m_hInst, MAKEINTRESOURCE(IDB_BITMAP2), 16, 1, RGB(192, 192, 192));
	SendMessage(m_hViewList[0], LVM_SETIMAGELIST, (WPARAM)LVSIL_SMALL, (LPARAM)hSmall);

	ritem.mask = LVIF_TEXT | LVIF_IMAGE;
	ritem.state = 0;
	ritem.stateMask = 0;
	ritem.iImage = 1;
	ritem.iSubItem = 0;
	ritem.iItem = 0;
	ritem.pszText = "Brick";
	SendMessage(m_hViewList[0], LVM_INSERTITEM, 0, (LPARAM)&ritem);

	hSmall = ImageList_LoadBitmap(m_hInst, MAKEINTRESOURCE(IDB_BITMAP2), 16, 1, RGB(192, 192, 192));
	SendMessage(m_hViewList[1], LVM_SETIMAGELIST, (WPARAM)LVSIL_SMALL, (LPARAM)hSmall);

	ritem.mask = LVIF_TEXT | LVIF_IMAGE;
	ritem.state = 0;
	ritem.stateMask = 0;
	ritem.iImage = 1;
	ritem.iSubItem = 0;
	ritem.iItem = 0;
	ritem.pszText = "Obstacle";
	SendMessage(m_hViewList[1], LVM_INSERTITEM, 0, (LPARAM)&ritem);

	/*
	ritem.iSubItem = 0;
	ritem.iItem = 1;
	ritem.pszText = L"Jone";
	SendMessage(hList, LVM_INSERTITEM, 0, (LPARAM)&ritem);
	*/
}

void CMouseManager::MouseMove(const LPARAM& lParam)
{
	if (m_dragStart) {
		m_pt.x = LOWORD(lParam);
		m_pt.y = HIWORD(lParam);
		ClientToScreen(m_hDlg, &m_pt);
		ImageList_DragMove(m_pt.x, m_pt.y);
	}
}

void CMouseManager::MouseButtonUp()
{
	if (m_dragStart) {
		// 드래그를 종료한다.
		ImageList_DragLeave(NULL);
		ImageList_EndDrag();
		ReleaseCapture();
		m_dragStart = false;
		ImageList_Destroy(m_hIml);
	}
}

void CMouseManager::SetDrag(int& hDrag, int& sel, LPNMHDR& hdr)
{
	// 드래그 이미지 리스트 만듦
	m_hIml = ListView_CreateDragImage(m_hViewList[sel], hDrag, &m_pt);
	if (m_hIml == NULL) return;
	ImageList_BeginDrag(m_hIml, 0, 0, 0);
	m_pt = ((NM_LISTVIEW*)hdr)->ptAction;
	ClientToScreen(m_hViewList[sel], &m_pt);

	ImageList_DragEnter(GetDesktopWindow(), m_pt.x, m_pt.y);
	// 계속적인 드래그 동작을 위해 커서를 캡처한다.
	SetCapture(m_hDlg);
	m_dragStart = true;
}