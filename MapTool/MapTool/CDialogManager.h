#pragma once

#include "Define.h"

class CDialogManager
{
public:
	static CDialogManager* GetInstance()
	{
		if (m_instance == nullptr)
			m_instance = new CDialogManager;

		return m_instance;
	}

	CDialogManager() {  }
	~CDialogManager() { delete m_instance; }

public:
	void Init(HWND& hDlg, HINSTANCE& hInst);
	void InitViewList();

public:
	void SelectItem(int sel);
	OBJECT_TYPE GetSelectedObject() { return m_selectedObj; }
	void ChangeViewList(const int& sel);

public:
	void MouseMove(const LPARAM& lParam);
	void MouseButtonUp();
	void SetDrag(int& hDrag, int& sel, LPNMHDR& hdr);

private:
	static CDialogManager* m_instance;
private:
	HWND m_hDlg;
	HINSTANCE m_hInst;
	HWND m_hViewList[2];
	POINT m_pt;
	HIMAGELIST m_hIml;
	bool m_dragStart;
	OBJECT_TYPE m_selectedObj;
};