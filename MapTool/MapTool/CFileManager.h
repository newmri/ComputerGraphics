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
	OPENFILENAME m_OFN;     // 파일열기 대화상자를 초기화하기 위한 변수
	char m_fileName[MAX_PATH]; // 파일의 경로 및 이름을 복사하기 위한 문자열
	HANDLE m_hFile;
};