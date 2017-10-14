#include "Define.h"

GLvoid Init(GLvoid);
GLvoid DrawScene(GLvoid);
GLvoid Reshape(int w, int h);
GLvoid Animate(int n);
GLubyte* LoadDlBitmap(const char* filename, BITMAPINFO** info);
BITMAPINFO* m_bitinfo;
GLubyte* m_bitmap;


const unsigned int ANIMATION_TIME = 1000 / 30;

CRect g_rect;
vector<Vector2> g_v;

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdParam, int nCmdShow)
{
	Init();
	glutCreateWindow("ShapeClipping");

	glutDisplayFunc(DrawScene);
	glutReshapeFunc(Reshape);
	m_bitmap = LoadDlBitmap("KnifeTopRight.bmp", &m_bitinfo);
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f); // Set background in blue
	glutTimerFunc(ANIMATION_TIME, Animate, true);
	MOUSEMANAGER->Init();
	glutMainLoop();

	delete m_bitmap;
	delete m_bitinfo;
	return 0;
	
}



GLvoid Init(GLvoid)
{
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(WINDOWS_WIDTH, WINDOWS_HEIGHT);

}

GLvoid DrawScene(GLvoid)
{

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	g_rect.Render();

	GLfloat xsize, ysize;
	GLfloat xoffset, yoffset;
	GLfloat xscale, yscale;

	glutSetCursor(GLUT_CURSOR_NONE);

	glPushMatrix();

	if (m_bitinfo){
		xsize = 50;
		ysize = m_bitinfo->bmiHeader.biHeight * xsize / m_bitinfo->bmiHeader.biWidth;
		if (ysize > WINDOWS_HEIGHT){
			ysize = WINDOWS_HEIGHT;
			xsize = m_bitinfo->bmiHeader.biWidth * ysize / m_bitinfo->bmiHeader.biHeight;
		}
		
		xscale = xsize / m_bitinfo->bmiHeader.biWidth;
		yscale = ysize / m_bitinfo->bmiHeader.biHeight;

		glRasterPos2f(MOUSEMANAGER->GetPos().x, MOUSEMANAGER->GetPos().y);
		glPixelZoom(xscale, yscale);
		glDrawPixels(m_bitinfo->bmiHeader.biWidth, m_bitinfo->bmiHeader.biHeight, GL_BGR_EXT, GL_UNSIGNED_BYTE, m_bitmap);
	}
	glPopMatrix();
	glutSwapBuffers(); // Draw
}

GLvoid Reshape(int w, int h)
{
	glViewport(0, 0, w, h); // Change viewport with window size
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

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

GLvoid Animate(int n)
{
	DrawScene();
	glutTimerFunc(ANIMATION_TIME, Animate, true);
}

