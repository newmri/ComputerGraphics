#pragma once

#include <map>
#include <Windows.h>

#include "Enum.h"

const int TEXTURE_NUM = 4;

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
	std::map<TEXTURE, unsigned int>& GetTexture() { return m_textureList; }

public:
	unsigned char* LoadDIBitmap(const char* filename, BITMAPINFO** info);

private:
	static CTextureManager* m_instance;
	std::map<TEXTURE, unsigned int> m_textureList;
	unsigned int m_texture[TEXTURE_NUM];
};