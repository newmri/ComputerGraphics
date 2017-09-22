// Texture.cpp: implementation of the CTexture class.
//
//////////////////////////////////////////////////////////////////////

#include <iostream>
#include <Windows.h>
#include "Texture.h"


//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CTexture::CTexture()
{
	Width = 0;
	Height = 0;
	Data = NULL;
}

CTexture::~CTexture()
{
	delete Data;
}

CTexture::CTexture(const CTexture& texture)
{
	Width = texture.Width;
	Height = texture.Height;

	// Copy Image data
	long size = Width * Height * 3;
	Data = new unsigned char[size];
	memcpy(Data, texture.Data, size);
}

void CTexture::operator =(const CTexture& texture)
{
	Width = texture.Width;
	Height = texture.Height;

	// Copy Image data
	long size = Width * Height * 3;
	Data = new unsigned char[size];
	memcpy(Data, texture.Data, size);
}


bool CTexture::Load(const char* pathname)
{
	BITMAPINFO *info;

	FILE *fp;
    int bitsize;
    int infosize;
    BITMAPFILEHEADER header;

    if ((fp = fopen(pathname, "rb")) == NULL)
        return NULL;

    if (fread(&header, sizeof(BITMAPFILEHEADER), 1, fp) < 1)
	{
		fclose(fp);
        return NULL;
	}

    if (header.bfType != 'MB')
	{
        fclose(fp);
        return NULL;
	}

	infosize = header.bfOffBits - sizeof(BITMAPFILEHEADER);
    if ((info = (BITMAPINFO *)malloc(infosize)) == NULL)
	{
        fclose(fp);
        return NULL;
	}

    if (fread(info, 1, infosize, fp) < (unsigned int)infosize)
	{
        free(info);
        fclose(fp);
        return (NULL);
	}

	Width = info->bmiHeader.biWidth;
	Height = info->bmiHeader.biHeight;
	
    if ((bitsize = (info)->bmiHeader.biSizeImage) == 0)
        bitsize = ((info)->bmiHeader.biWidth *
                   (info)->bmiHeader.biBitCount + 7) / 8 *
  	           abs((info)->bmiHeader.biHeight);

    if ((Data = (unsigned char *)malloc(bitsize)) == NULL)
	{
        free(info);
        fclose(fp);
        return NULL;
	}

    if (fread(Data, 1, bitsize, fp) < (unsigned int)bitsize)
	{
        free(info);
        free(Data);
        fclose(fp);
        return NULL;
	}

	unsigned char *temp = (unsigned char *)malloc(bitsize);

	for (int j = Height - 1; j >= 0; j--) {
		for (int i = 0; i < Width; i++) {
			*(temp + i * 3 + j * Width * 3 ) = *(Data + i * 3 + j * Width * 3 + 2);
			*(temp + i * 3 + j * Width * 3 + 1) = *(Data + i * 3 + j * Width * 3 + 1);
			*(temp + i * 3 + j * Width * 3 + 2) = *(Data + i * 3 + j * Width * 3);
		}
	}

	for (int j = Height - 1; j >= 0; j--) {
		for (int i = 0; i < Width; i++) {
			*(Data + i * 3 + j * Width * 3 ) = *(temp + i * 3 + j * Width * 3);
			*(Data + i * 3 + j * Width * 3 + 1) = *(temp + i * 3 + j * Width * 3 + 1);
			*(Data + i * 3 + j * Width * 3 + 2) = *(temp + i * 3 + j * Width * 3 + 2);
		}
	}

    fclose(fp);

    return true;
}

/*
bool CTexture::Load(const char* pathname)
{
	CFile file;
	if (!file.Open(pathname, CFile::modeRead|CFile::typeBinary)) return false;

	// Open BMP file
	Width = 0;
	Height = 0;
	bit = 0;
	unsigned char temp;
	long check;

	// Read Header
	file.Read(&temp, 1);
	if (temp != 'B') return false;
	file.Read(&temp, 1);
	if (temp != 'M') return false;

	// skip
	for (int i = 0; i < 16; i++) file.Read(&temp, 1);

	// read width
	file.Read(&temp, 1);
	Width += temp;
	file.Read(&temp, 1);
	Width += temp * 0x100;
	file.Read(&temp, 1);
	Width += temp * 0x10000;
	file.Read(&temp, 1);
	Width += temp * 0x1000000;

	check = Width;
	while (!(check % 2)) check /= 2;
	if (check != 1) {
		Width = 0;
		return false;
	}

	// read height
	file.Read(&temp, 1);
	Height += temp;
	file.Read(&temp, 1);
	Height += temp * 0x100;
	file.Read(&temp, 1);
	Height += temp * 0x10000;
	file.Read(&temp, 1);
	Height += temp * 0x1000000;

	check = Height;
	while (!(check % 2)) check /= 2;
	if (check != 1) {
		Width = 0;
		Height = 0;
		return false;
	}

	// skip
	for (i = 0; i < 2; i++) file.Read(&temp, 1);

	// read color depth
	file.Read(&temp, 1);
	bit += temp;
	file.Read(&temp, 1);
	bit += temp * 0x100;

	// If the bitmap is not 24bit color, Can't use the bitmap
	if (bit != 24) {
		bit = 0;
		Width = 0;
		Height = 0;
		return false;
	}

	// skip
	for (i = 0; i < 24; i++) file.Read(&temp, 1);

	// read picture (convert bmp to row data)
	Data = new unsigned char[Width * Height * 3];
	for (int j = Height - 1; j >= 0; j--) {
		for (int i = 0; i < Width; i++) {
			file.Read(&temp, 1);
			*(Data + i * 3 + j * Width * 3 + 2) = temp;
			file.Read(&temp, 1);
			*(Data + i * 3 + j * Width * 3 + 1) = temp;
			file.Read(&temp, 1);
			*(Data + i * 3 + j * Width * 3) = temp;
		}
	}
	
	file.Close();

	return true;
}
*/