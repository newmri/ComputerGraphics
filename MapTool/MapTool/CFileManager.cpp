#include "Define.h"

CFileManager* CFileManager::m_instance = nullptr;


void CFileManager::LoadFile()
{

	memset(&m_OFN, 0, sizeof(OPENFILENAME));
	memset(&m_fileName, 0, MAX_PATH);
	m_OFN.lStructSize = sizeof(OPENFILENAME);
	m_OFN.hwndOwner = m_hWnd;
	m_OFN.lpstrFilter = "Every File(*.*)\0*.*\0Text File\0*.txt;*.doc\0";
	m_OFN.lpstrFile = m_fileName;
	m_OFN.nMaxFile = 256;
	m_OFN.lpstrInitialDir = "c:\\";
	m_OFN.Flags = OFN_EXPLORER | OFN_ENABLEHOOK;
	m_OFN.lpfnHook = OFNHookProc;

	if (GetOpenFileName(&m_OFN) != 0) {
		m_hFile = CreateFile(m_OFN.lpstrFile, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, 0, 0);
		DWORD size;
		Object obj;
		int fileSize = GetFileSize(m_hFile, NULL);
		char* buf = new char[fileSize];
		//ReadFile(m_hFile, (LPVOID)&obj, sizeof(obj), &size, NULL);
		ReadFile(m_hFile, buf, fileSize, &size, NULL);
		int idx = 0;
		while (idx < fileSize) {
			memcpy(&obj, &buf[idx], sizeof(obj));
			RENDERMANAGER->AddObject(obj);
			idx += sizeof(obj) + 2;
		}

		CloseHandle(m_hFile);
	}

}


void CFileManager::SaveFile()
{

	memset(&m_OFN, 0, sizeof(OPENFILENAME));
	memset(&m_fileName, 0, MAX_PATH);
	m_OFN.lStructSize = sizeof(OPENFILENAME);
	m_OFN.hwndOwner = m_hWnd;
	m_OFN.lpstrFilter = "Every File(*.*)\0*.*\0Text File\0*.txt;*.doc\0";
	m_OFN.lpstrFile = m_fileName;
	m_OFN.nMaxFile = 256;
	m_OFN.lpstrInitialDir = "c:\\";
	m_OFN.Flags = OFN_EXPLORER | OFN_ENABLEHOOK;
	m_OFN.lpfnHook = OFNHookProc;
	//SetWindowPos(m_hWnd, HWND_TOPMOST, 200, 200, 0, 0, SWP_NOSIZE);

	if (GetSaveFileName(&m_OFN) != 0) {
		m_hFile = CreateFile(m_OFN.lpstrFile, GENERIC_WRITE, FILE_SHARE_WRITE, NULL, CREATE_ALWAYS, 0, 0);

		if (RENDERMANAGER->GetObjects().size() != 0) {
			for (auto d : RENDERMANAGER->GetObjects()) {
				DWORD size = sizeof(d);
				WriteFile(m_hFile, (LPCVOID)&d, sizeof(d), &size, NULL);;
				char NewLine[] = "\r\n";
				DWORD NumWritten;
				BOOL Result = WriteFile(m_hFile, &NewLine, 2, &NumWritten, NULL);
			}
		}
		CloseHandle(m_hFile);
	}
}

static UINT_PTR CALLBACK OFNHookProc(HWND hdlg, UINT uiMsg, WPARAM wParam, LPARAM lParam)
{

	if ((uiMsg == WM_NOTIFY) &&
		(reinterpret_cast<OFNOTIFY*>(lParam)->hdr.code == CDN_INITDONE)){
		SetWindowPos(GetParent(hdlg), HWND_TOPMOST, WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2, 0, 0, SWP_NOSIZE);
	}

	return 0;
}