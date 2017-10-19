#include "Define.h"

GLvoid Init(GLvoid);
GLvoid DrawScene(GLvoid);
GLvoid Reshape(int w, int h);
GLvoid Animate(int n);
GLvoid DoClliping();
GLvoid CutLine();
GLvoid VerticalDraw();

double GetDistance(const Vector2& v1, const Vector2& v2);

GLubyte* LoadDlBitmap(const char* filename, BITMAPINFO** info);
BITMAPINFO* m_bitinfo;
GLubyte* m_bitmap;


const unsigned int ANIMATION_TIME = 1000 / 30;

vector<unique_ptr<CRect>> g_v;

Vector2 g_line[2];
Vector2 lastLine;

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
	for (int i = 0; i < POSITION::END; ++i) {
		unique_ptr<CRect> rect(new CRect(static_cast<POSITION>(i)));
		g_v.push_back(move(rect));
	}
}

GLvoid DrawScene(GLvoid)
{

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	
	for (auto& d : g_v) d->Render();

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
		float y = -(ysize - WINDOWS_HEIGHT / 2.0f) * (1.0f / (WINDOWS_HEIGHT / 2.0f));
		xscale = xsize / m_bitinfo->bmiHeader.biWidth;
		yscale = ysize / m_bitinfo->bmiHeader.biHeight;

		glRasterPos2f(MOUSEMANAGER->GetPos().x, MOUSEMANAGER->GetPos().y - ((y * yscale) + 0.1f));
		glPixelZoom(xscale, yscale);
		glDrawPixels(m_bitinfo->bmiHeader.biWidth, m_bitinfo->bmiHeader.biHeight, GL_BGR_EXT, GL_UNSIGNED_BYTE, m_bitmap);
	}

	// Draw Line
	glBegin(GL_LINES);
	glColor3f(1.0f, 1.0f, 1.0f);
	glVertex2f(g_line[0].x, g_line[0].y);
	glVertex2f(g_line[1].x, g_line[1].y);
	glEnd();

	// Draw Cut Shape
	glBegin(GL_POLYGON);
	glColor3f(1.0f, 0.0f, 0.0f);
	glVertex2f(g_line[0].x, g_line[0].y);
	glVertex2f(g_line[1].x, g_line[1].y);

	if (g_line[0].x == g_v[M]->GetLeftPos() || g_line[1].x == g_v[M]->GetLeftPos()) lastLine.x = g_v[M]->GetLeftPos();
	else if (g_line[0].x == g_v[M]->GetRightPos() || g_line[1].x == g_v[M]->GetRightPos()) lastLine.x = g_v[M]->GetRightPos();

	if (g_line[0].y == g_v[M]->GetTopPos() || g_line[1].y == g_v[M]->GetTopPos()) lastLine.y = g_v[M]->GetTopPos();
	else if (g_line[0].y == g_v[M]->GetBottomPos() || g_line[1].y == g_v[M]->GetBottomPos()) lastLine.y = g_v[M]->GetBottomPos();

	VerticalDraw();
		
	glVertex2f(lastLine.x, lastLine.y);
	glEnd();

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
	if (MOUSEMANAGER->HaveSomethingToClip()) DoClliping();
	DrawScene();
	glutTimerFunc(ANIMATION_TIME, Animate, true);
}

GLvoid DoClliping()
{
	Flags flag[2]{ false, };

	for (int j = 0; j < END; ++j) {

		if (MOUSEMANAGER->GetPosList()[0].x >= g_v[j]->GetLeftPos() &&
			MOUSEMANAGER->GetPosList()[0].x <= g_v[j]->GetRightPos() &&
			MOUSEMANAGER->GetPosList()[0].y <= g_v[j]->GetTopPos() &&
			MOUSEMANAGER->GetPosList()[0].y >= g_v[j]->GetBottomPos()) {
			switch (j) {
			case LT: flag[0].left = true; flag[0].top = true; break;
			case T: flag[0].top = true; break;
			case RT: flag[0].right = true; flag[0].top = true; break;
			case L: flag[0].left = true; break;
			case R: flag[0].right = true; break;
			case LB: flag[0].left = true; flag[0].bottom = true; break;
			case B: flag[0].bottom = true; break;
			case RB: flag[0].right = true; flag[0].bottom = true; break;
			}
		}

		if (MOUSEMANAGER->GetPosList()[END_OF_LINE].x >= g_v[j]->GetLeftPos() &&
			MOUSEMANAGER->GetPosList()[END_OF_LINE].x <= g_v[j]->GetRightPos() &&
			MOUSEMANAGER->GetPosList()[END_OF_LINE].y <= g_v[j]->GetTopPos() &&
			MOUSEMANAGER->GetPosList()[END_OF_LINE].y >= g_v[j]->GetBottomPos()) {
			switch (j) {
			case LT: flag[1].left = true; flag[1].top = true; break;
			case T: flag[1].top = true; break;
			case RT: flag[1].right = true; flag[1].top = true; break;
			case L: flag[1].left = true; break;
			case R: flag[1].right = true; break;
			case LB: flag[1].left = true; flag[1].bottom = true; break;
			case B: flag[1].bottom = true; break;
			case RB: flag[1].right = true; flag[1].bottom = true; break;
			}
		}

	}


	if (!(flag[0] & flag[1])){
		if (MOUSEMANAGER->IsInArea(g_v[M]->GetLeftPos(), g_v[M]->GetRightPos(),
			g_v[M]->GetTopPos(), g_v[M]->GetBottomPos())) CutLine();

		MOUSEMANAGER->GetPosList().clear();
	}

	else MOUSEMANAGER->GetPosList().clear();
}

GLvoid CutLine()
{
	g_line[0] = MOUSEMANAGER->GetPosList()[0];
	g_line[1] = MOUSEMANAGER->GetPosList()[END_OF_LINE];

	for (int i = 0; i < 2; ++i) {
		// Vertical Boundary Check
		if (g_line[i].x < g_v[M]->GetLeftPos()) g_line[i].x = g_v[M]->GetLeftPos();
		if (g_line[i].x > g_v[M]->GetRightPos()) g_line[i].x = g_v[M]->GetRightPos();

		// Horizontal Boundary Check
		if (g_line[i].y > g_v[M]->GetTopPos()) g_line[i].y = g_v[M]->GetTopPos();
		if (g_line[i].y < g_v[M]->GetBottomPos()) g_line[i].y = g_v[M]->GetBottomPos();
	}
}

double GetDistance(const Vector2& v1, const Vector2& v2)
{
	return sqrt(pow(v1.x - v2.x, 2) + pow(v1.y - v2.y, 2));

}

GLvoid VerticalDraw()
{
	if ((g_line[0].y == g_v[M]->GetTopPos() || g_line[1].y == g_v[M]->GetTopPos()) &&
		(g_line[0].y == g_v[M]->GetBottomPos() || g_line[1].y == g_v[M]->GetBottomPos())) {
		Vector2 v1, v2;
		v1.x = g_v[M]->GetLeftPos();
		v1.y = g_v[M]->GetTopPos();
		v2.x = g_v[M]->GetRightPos();
		v2.y = g_v[M]->GetTopPos();

		if (GetDistance(g_line[0], v1) > GetDistance(g_line[0], v2)) lastLine.x = g_v[M]->GetRightPos();
		else lastLine.x = g_v[M]->GetLeftPos();

		glVertex2f(lastLine.x, g_v[M]->GetBottomPos());

	}
}