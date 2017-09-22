// Texture.h: interface for the CTexture class.
//
//////////////////////////////////////////////////////////////////////

#include <Windows.h>

#if !defined(AFX_TEXTURE_H__982EC4E7_BB1B_11D4_B3AD_00485430521C__INCLUDED_)
#define AFX_TEXTURE_H__982EC4E7_BB1B_11D4_B3AD_00485430521C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CTexture  
{
public:
	CTexture();
	CTexture(const CTexture& texture);
	virtual ~CTexture();

	// Operator Overloading
	void operator =(const CTexture& texture);

	// Method
	bool Load(const char* pathname);	// Open Texture Image File(*.BMP)

	unsigned char *Data;				// Data Storage of Texture Image
	long Width;							// Width of Texture Image
	long Height;						// Height of Texture Image
	int bit;
};

#endif // !defined(AFX_TEXTURE_H__982EC4E7_BB1B_11D4_B3AD_00485430521C__INCLUDED_)
