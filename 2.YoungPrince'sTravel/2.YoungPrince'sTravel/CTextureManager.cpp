#include "Define.h"

CTextureManager* CTextureManager::m_instance = nullptr;

void CTextureManager::Init()
{
	BITMAPINFO* info;
	unsigned char* bytes;
	glGenTextures(TEXTURE_NUM, m_texture);

	// Bind texture and object
	glBindTexture(GL_TEXTURE_2D, m_texture[0]);
	// Load Image
	bytes = LoadDIBitmap("Texture//Earth.bmp", &info);
	if (bytes == NULL) { cout << "CTextureManager::Init() Error" << endl; while (true); }
	// Set setting of textrue
	glTexImage2D(GL_TEXTURE_2D, 0, 3, info->bmiHeader.biWidth, info->bmiHeader.biHeight, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, bytes);
	// Set parameter
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	// Bind texture and object
	glBindTexture(GL_TEXTURE_2D, m_texture[1]);
	// Load Image
	bytes = LoadDIBitmap("Texture//EarthNight.bmp", &info);
	if (bytes == NULL) { cout << "CTextureManager::Init() Error" << endl; while (true); }
	// Set setting of textrue
	glTexImage2D(GL_TEXTURE_2D, 0, 3, info->bmiHeader.biWidth, info->bmiHeader.biHeight, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, bytes);
	// Set parameter
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);



	// Bind texture and object
	glBindTexture(GL_TEXTURE_2D, m_texture[2]);
	// Load Image
	bytes = LoadDIBitmap("Texture//Jupiter.bmp", &info);
	if (bytes == NULL) { cout << "CTextureManager::Init() Error" << endl; while (true); }
	// Set setting of textrue
	glTexImage2D(GL_TEXTURE_2D, 0, 3, info->bmiHeader.biWidth, info->bmiHeader.biHeight, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, bytes);
	// Set parameter
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);


	
	// Bind texture and object
	glBindTexture(GL_TEXTURE_2D, m_texture[3]);
	// Load Image
	bytes = LoadDIBitmap("Texture//Mars.bmp", &info);
	if (bytes == NULL) { cout << "CTextureManager::Init() Error" << endl; while (true); }
	// Set setting of textrue
	glTexImage2D(GL_TEXTURE_2D, 0, 3, info->bmiHeader.biWidth, info->bmiHeader.biHeight, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, bytes);
	// Set parameter
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);


	
	// Bind texture and object
	glBindTexture(GL_TEXTURE_2D, m_texture[4]);
	// Load Image
	bytes = LoadDIBitmap("Texture//Mercury.bmp", &info);
	if (bytes == NULL) { cout << "CTextureManager::Init() Error" << endl; while (true); }
	// Set setting of textrue
	glTexImage2D(GL_TEXTURE_2D, 0, 3, info->bmiHeader.biWidth, info->bmiHeader.biHeight, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, bytes);
	// Set parameter
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);


	
	// Bind texture and object
	glBindTexture(GL_TEXTURE_2D, m_texture[5]);
	// Load Image
	bytes = LoadDIBitmap("Texture//Neptune.bmp", &info);
	if (bytes == NULL) { cout << "CTextureManager::Init() Error" << endl; while (true); }
	// Set setting of textrue
	glTexImage2D(GL_TEXTURE_2D, 0, 3, info->bmiHeader.biWidth, info->bmiHeader.biHeight, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, bytes);
	// Set parameter
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);


	
	// Bind texture and object
	glBindTexture(GL_TEXTURE_2D, m_texture[6]);
	// Load Image
	bytes = LoadDIBitmap("Texture//Sun.bmp", &info);
	if (bytes == NULL) { cout << "CTextureManager::Init() Error" << endl; while (true); }
	// Set setting of textrue
	glTexImage2D(GL_TEXTURE_2D, 0, 3, info->bmiHeader.biWidth, info->bmiHeader.biHeight, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, bytes);
	// Set parameter
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);


	
	// Bind texture and object
	glBindTexture(GL_TEXTURE_2D, m_texture[7]);
	// Load Image
	bytes = LoadDIBitmap("Texture//Venus.bmp", &info);
	if (bytes == NULL) { cout << "CTextureManager::Init() Error" << endl; while (true); }
	// Set setting of textrue
	glTexImage2D(GL_TEXTURE_2D, 0, 3, info->bmiHeader.biWidth, info->bmiHeader.biHeight, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, bytes);
	// Set parameter
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	
	// Bind texture and object
	glBindTexture(GL_TEXTURE_2D, m_texture[8]);
	// Load Image
	bytes = LoadDIBitmap("Texture//HouseFront.bmp", &info);
	if (bytes == NULL) { cout << "CTextureManager::Init() Error" << endl; while (true); }
	// Set setting of textrue
	glTexImage2D(GL_TEXTURE_2D, 0, 3, info->bmiHeader.biWidth, info->bmiHeader.biHeight, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, bytes);
	// Set parameter
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);


	// Bind texture and object
	glBindTexture(GL_TEXTURE_2D, m_texture[9]);
	// Load Image
	bytes = LoadDIBitmap("Texture//HouseSide.bmp", &info);
	if (bytes == NULL) { cout << "CTextureManager::Init() Error" << endl; while (true); }
	// Set setting of textrue
	glTexImage2D(GL_TEXTURE_2D, 0, 3, info->bmiHeader.biWidth, info->bmiHeader.biHeight, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, bytes);
	// Set parameter
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);



	// Set texture mode
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
	glEnable(GL_DEPTH_TEST);
	

}

unsigned char* CTextureManager::LoadDIBitmap(const char* filename, BITMAPINFO** info)
{
	FILE *fp;
	GLubyte *bits;
	int bitsize, infosize;
	BITMAPFILEHEADER header;
	// ���̳ʸ� �б� ���� ������ ����
	if ((fopen_s(&fp,filename, "rb")) != 0)
		return NULL;
	// ��Ʈ�� ���� ����� �д´�.
	if (fread(&header, sizeof(BITMAPFILEHEADER), 1, fp) < 1) {
		fclose(fp);
		return NULL;
	}
	// ������ BMP �������� Ȯ���Ѵ�.
	if (header.bfType != 'MB') {
		fclose(fp);
		return NULL;
	}
	// BITMAPINFOHEADER ��ġ�� �A��.
	infosize = header.bfOffBits - sizeof(BITMAPFILEHEADER);
	// ��Ʈ�� �̹��� �����͸� ���� �޸� �Ҵ��� �Ѵ�.
	if ((*info = (BITMAPINFO *)malloc(infosize)) == NULL) {
		fclose(fp);
		exit(0);
		return NULL;
	}
	// ��Ʈ�� ���� ����� �д´�.
	if (fread(*info, 1, infosize, fp) < (unsigned int)infosize) {
		free(*info);
		fclose(fp);
		return NULL;
	}

	// ��Ʈ���� ũ�� ����
	if ((bitsize = (*info)->bmiHeader.biSizeImage) == 0)
		bitsize = ((*info)->bmiHeader.biWidth*(*info)->bmiHeader.biBitCount + 7) / 8.0 * abs((*info)->bmiHeader.biHeight);
	// ��Ʈ���� ũ�⸸ŭ �޸𸮸� �Ҵ��Ѵ�.
	if ((bits = (unsigned char *)malloc(bitsize)) == NULL) {
		free(*info);
		fclose(fp);
		return NULL;
	}
	// ��Ʈ�� �����͸� bit(GLubyte Ÿ��)�� �����Ѵ�.
	if (fread(bits, 1, bitsize, fp) < (unsigned int)bitsize) {
		free(*info); free(bits);
		fclose(fp);
		return NULL;
	}
	fclose(fp);
	return bits;
}