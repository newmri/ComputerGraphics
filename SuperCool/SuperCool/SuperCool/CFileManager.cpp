#include "Define.h"
#include "CObject.h"

CFileManager* CFileManager::m_instance = nullptr;

void CFileManager::LoadFileWithPath(char* path)
{
	HANDLE hFile = CreateFile(path, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, 0, 0);
	DWORD size;
	ObjectInfo obj;

	int fileSize = GetFileSize(hFile, NULL);
	char* buf = new char[fileSize];
	ReadFile(hFile, buf, fileSize, &size, NULL);
	int idx = 0;

	while (idx < fileSize) {
		memcpy(&obj, &buf[idx], sizeof(obj));
		RENDERMANAGER->AddObject(obj);
		idx += sizeof(obj) + 2;
	}
	CloseHandle(hFile);
}

