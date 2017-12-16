#pragma once

#include <map>
#include <Windows.h>

#include "Enum.h"

const int TEXTURE_NUM = 6;

class CTextureManager
{
public:
	static CTextureManager* GetInstance()
	{
		if (m_instance == nullptr)
			m_instance = new CTextureManager;

		return m_instance;
	}

	CTextureManager() {}
	~CTextureManager() { delete m_instance; }

public:
	void Init();

public:
	unsigned int GetTexture(int index) { return m_texture[index]; }

public:
	unsigned char* LoadDIBitmap(const char* filename, BITMAPINFO** info);

private:
	static CTextureManager* m_instance;
	unsigned int m_texture[TEXTURE_NUM];
};