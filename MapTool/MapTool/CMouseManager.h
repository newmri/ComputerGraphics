#pragma once

struct Vector3;

class CMouseManager
{
public:
	static CMouseManager* GetInstance()
	{
		if (m_instance == nullptr) m_instance = new CMouseManager;
		return m_instance;
	}

public:
	void Init(HWND& hDlg, HINSTANCE& hInst);
	void InitViewList();

public:
	void MouseMove(const LPARAM& lParam);
	void MouseButtonUp();
	Vector3 Do3DPicking(int x, int y);

public:
	void SetDrag(int& hDrag, int& sel, LPNMHDR& hdr);

private:
	CMouseManager() {};
	CMouseManager(const CMouseManager&) = delete;
	void operator=(const CMouseManager&) = delete;
	static CMouseManager* m_instance;

private:
	HWND m_hDlg;
	HINSTANCE m_hInst;
	HWND m_hViewList[2];
	POINT m_pt;
	HIMAGELIST m_hIml;
	bool m_dragStart;
};