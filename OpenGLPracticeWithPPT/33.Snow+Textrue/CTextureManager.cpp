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
	bytes = LoadDIBitmap("WoodFloor.bmp", &info);
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
	bytes = LoadDIBitmap("Pyramid.bmp", &info);
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
	bytes = LoadDIBitmap("Earth.bmp", &info);
	if (bytes == NULL) { cout << "CTextureManager::Init() Error" << endl; while (true); }
	// Set setting of textrue
	glTexImage2D(GL_TEXTURE_2D, 0, 3, info->bmiHeader.biWidth, info->bmiHeader.biHeight, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, bytes);
	// Set parameter
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);


	m_textureList.insert(make_pair(FLOOR_TEXTURE, m_texture[0]));
	m_textureList.insert(make_pair(PYRAMID_TEXTURE, m_texture[1]));
	m_textureList.insert(make_pair(EARTH_TEXTURE, m_texture[2]));

	// Set texture mode
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	glEnable(GL_DEPTH_TEST);
	

}

unsigned char* CTextureManager::LoadDIBitmap(const char* filename, BITMAPINFO** info)
{
	FILE *fp;
	GLubyte *bits;
	int bitsize, infosize;
	BITMAPFILEHEADER header;
	// 바이너리 읽기 모드로 파일을 연다
	if ((fopen_s(&fp,filename, "rb")) != 0)
		return NULL;
	// 비트맵 파일 헤더를 읽는다.
	if (fread(&header, sizeof(BITMAPFILEHEADER), 1, fp) < 1) {
		fclose(fp);
		return NULL;
	}
	// 파일이 BMP 파일인지 확인한다.
	if (header.bfType != 'MB') {
		fclose(fp);
		return NULL;
	}
	// BITMAPINFOHEADER 위치로 갂다.
	infosize = header.bfOffBits - sizeof(BITMAPFILEHEADER);
	// 비트맵 이미지 데이터를 넣을 메모리 할당을 한다.
	if ((*info = (BITMAPINFO *)malloc(infosize)) == NULL) {
		fclose(fp);
		exit(0);
		return NULL;
	}
	// 비트맵 인포 헤더를 읽는다.
	if (fread(*info, 1, infosize, fp) < (unsigned int)infosize) {
		free(*info);
		fclose(fp);
		return NULL;
	}

	// 비트맵의 크기 설정
	if ((bitsize = (*info)->bmiHeader.biSizeImage) == 0)
		bitsize = ((*info)->bmiHeader.biWidth*(*info)->bmiHeader.biBitCount + 7) / 8.0 * abs((*info)->bmiHeader.biHeight);
	// 비트맵의 크기만큼 메모리를 할당한다.
	if ((bits = (unsigned char *)malloc(bitsize)) == NULL) {
		free(*info);
		fclose(fp);
		return NULL;
	}
	// 비트맵 데이터를 bit(GLubyte 타입)에 저장한다.
	if (fread(bits, 1, bitsize, fp) < (unsigned int)bitsize) {
		free(*info); free(bits);
		fclose(fp);
		return NULL;
	}
	fclose(fp);
	return bits;
}