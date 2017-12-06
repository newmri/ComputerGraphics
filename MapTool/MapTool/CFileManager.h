#pragma once

#include <Windows.h>


static UINT_PTR CALLBACK OFNHookProc(HWND hdlg, UINT uiMsg, WPARAM wParam, LPARAM lParam);

class CFileManager
{
public:
	static CFileManager* GetInstance()
	{
		if (m_instance == nullptr)
			m_instance = new CFileManager;

		return m_instance;
	}

	CFileManager() {  }
	~CFileManager() { delete m_instance; }

public:
	void Init(HWND& hWnd) { m_hWnd = hWnd;}

public:
	void SaveFile();
	void LoadFile();

private:
	static CFileManager* m_instance;

private:
	HWND m_hWnd;
	OPENFILENAME m_OFN;     // ���Ͽ��� ��ȭ���ڸ� �ʱ�ȭ�ϱ� ���� ����
	char m_fileName[MAX_PATH]; // ������ ��� �� �̸��� �����ϱ� ���� ���ڿ�
	HANDLE m_hFile;
};