#include <iostream>
#include <gl/glut.h>
#include <Windows.h>

BITMAPINFO* m_bitinfo;
GLubyte* m_bitmap;

int m_nWidth{}, m_nHeight{};

void SetUpRC();
void RenderScene();
void ReshapeScene(int w, int h);
GLubyte* LoadDlBitmap(const char* filename, BITMAPINFO** info);

int main()
{
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA); // Set display mode
	glutInitWindowPosition(100, 100); // Set window position
	glutInitWindowSize(500, 500); // Set window size
	glutCreateWindow("BitmapViewer"); // Create window
	glutDisplayFunc(RenderScene); // Set render func
	glutReshapeFunc(ReshapeScene); // Change window size func

	// Load bitmap
	m_bitmap = LoadDlBitmap("AImage.bmp", &m_bitinfo);

	SetUpRC();
	glutMainLoop();

	delete m_bitmap;
	delete m_bitinfo;

	return 0;
}

void SetUpRC()
{
	glClearColor(0.0f, 0.0f, 1.0f, 1.0f); // Set background in blue
}

void ReshapeScene(int w, int h)
{
	float fRange = 100.0f;

	m_nWidth = w;
	m_nHeight = h;

	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	glOrtho(0, w, 0, h, -1, 1);


}

void RenderScene()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	GLfloat xsize, ysize;
	GLfloat xoffset, yoffset;
	GLfloat xscale, yscale;

	if (m_bitinfo)
	{
		xsize = (GLfloat)m_nWidth;
		ysize = m_bitinfo->bmiHeader.biHeight * xsize / m_bitinfo->bmiHeader.biWidth;
		if (ysize > m_nHeight)
		{
			ysize = (GLfloat)m_nHeight;
			xsize = m_bitinfo->bmiHeader.biWidth * ysize / m_bitinfo->bmiHeader.biHeight;
		}

		xscale = xsize / m_bitinfo->bmiHeader.biWidth;
		yscale = ysize / m_bitinfo->bmiHeader.biHeight;

		xoffset = (GLfloat)((m_nWidth - xsize) * 0.5);
		yoffset = (GLfloat)((m_nHeight - ysize) * 0.5);

		glRasterPos2f(xoffset, yoffset);
		glPixelZoom(xscale, yscale);

		glDrawPixels(m_bitinfo->bmiHeader.biWidth, m_bitinfo->bmiHeader.biHeight, GL_BGR_EXT, GL_UNSIGNED_BYTE, m_bitmap);
	}

	glFlush();

}

GLubyte* LoadDlBitmap(const char* filename, BITMAPINFO** info)
{
	FILE* fp;
	GLubyte* bits;

	int bitsize, infosize;
	BITMAPFILEHEADER header;

	if ((fp = fopen(filename, "rb")) == NULL) return NULL; // Open bitmap file with binary mode

	// Read header info
	if (fread(&header, sizeof(BITMAPFILEHEADER), 1, fp) < 1) {
		fclose(fp);
		return NULL;
	}

	if (header.bfType != 'MB') {
		fclose(fp);
		return NULL;
	}

	infosize = header.bfOffBits - sizeof(BITMAPFILEHEADER); // Calculate BITMAPINFO's position
	if ((*info = new BITMAPINFO) == nullptr) {
		fclose(fp);
		return NULL;
	}

	if (fread(*info, 1, infosize, fp) < (unsigned int)infosize) { // Read BITMAPINFO
		delete info;
		fclose(fp);
		return NULL;
	}

	// Calculate bitmap size
	if ((bitsize = (*info)->bmiHeader.biSizeImage) == 0)
		bitsize = ((*info)->bmiHeader.biWidth * (*info)->bmiHeader.biBitCount + 7) / 8
		* abs((*info)->bmiHeader.biHeight);

	// Read bitmap data and close
	if ((bits = new unsigned char[bitsize]) == nullptr) {
		delete[] bits;
		fclose(fp);
		return NULL;
	}

	if (fread(bits, 1, bitsize, fp) < (unsigned int)bitsize) {
		delete info;
		delete[] bits;
		fclose(fp);
		return NULL;
	}

	fclose(fp);
	return bits;
}