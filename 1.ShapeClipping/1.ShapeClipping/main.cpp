#include "Define.h"

GLvoid Init(GLvoid);
GLvoid InitObject(GLvoid);
GLvoid ClearObject(GLvoid);
GLvoid ResetObject(GLvoid);
GLvoid DrawScene(GLvoid);
GLvoid Reshape(int w, int h);
GLvoid Animate(int n);
GLvoid DoClliping();
GLvoid CutLine();
GLvoid Key(unsigned char key, int x, int y);
GLvoid CheckCollision();
GLvoid DrawWaterPart();
float GetDist();
bool VerticalCheck();
bool HorizontalCheck();
float GetDistance(const Vector2& v1, const Vector2& v2);

GLubyte* LoadDlBitmap(const char* filename, BITMAPINFO** info);
BITMAPINFO* m_bitinfo;
GLubyte* m_bitmap;

bool g_drawWaterPart = false;

const unsigned int ANIMATION_TIME = 1000 / 30;

vector<unique_ptr<CRect>> g_v;

Vector2 g_line[2];
Vector2 lastLine;
Vector2 g_thirdLine;
CPolygon g_polygon;
CPolygon g_whitePolygon;


bool g_haveToRenderWhite;

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
	glutKeyboardFunc(Key);
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

	InitObject();

}

GLvoid DrawScene(GLvoid)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	for (auto& d : g_v) d->Render();
	g_polygon.Render();
	g_whitePolygon.RenderWhitePolygon();
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

	
	/*
	glBegin(GL_LINES);
	glColor3f(0.0f, 0.0f, 0.0f);
	//glVertex2f(g_line[0].x, g_line[0].y);
	//glVertex2f(g_line[1].x, g_line[1].y);
	glVertex2f(g_polygon.GetPolygonLeftPos(), g_polygon.GetPolygonBottomPos());
	glVertex2f(g_polygon.GetPolygonRightPos(), g_polygon.GetPolygonBottomPos());
	glEnd();
	*/
	if(g_drawWaterPart) DrawWaterPart();
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
	g_polygon.Update();
	g_whitePolygon.Update();
	for (auto& d : g_v) d->Update();
	if (g_v[M]->GetLeftPos() < -1.0f || g_v[M]->GetRightPos() > 1.0f){
		g_whitePolygon.ChangeDirection();
		for (auto& d : g_v) {
			if(d->GetPosition() != BASKET) d->ChangeDirection();
		}
	}

	if (g_v[BASKET]->GetLeftPos() < -1.0f || g_v[BASKET]->GetRightPos() > 1.0f) g_v[BASKET]->ChangeDirection();

	DrawScene();
	CheckCollision();
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

	if (g_line[0].x == g_v[M]->GetLeftPos() || g_line[1].x == g_v[M]->GetLeftPos()) lastLine.x = g_v[M]->GetLeftPos();
	else if (g_line[0].x == g_v[M]->GetRightPos() || g_line[1].x == g_v[M]->GetRightPos()) lastLine.x = g_v[M]->GetRightPos();

	if (g_line[0].y == g_v[M]->GetTopPos() || g_line[1].y == g_v[M]->GetTopPos()) lastLine.y = g_v[M]->GetTopPos();
	else if (g_line[0].y == g_v[M]->GetBottomPos() || g_line[1].y == g_v[M]->GetBottomPos()) lastLine.y = g_v[M]->GetBottomPos();

	g_polygon.SetV1(g_line[0]);
	g_polygon.SetV2(g_line[1]);
	if (VerticalCheck() && HorizontalCheck()) g_polygon.ReSetV3();
	g_polygon.SetV4(lastLine);

	g_whitePolygon = g_polygon;
	g_whitePolygon.SetWhite(g_v[M]->GetDirection());

	g_polygon.SetDrop();
}

float GetDistance(const Vector2& v1, const Vector2& v2)
{
	return sqrt(pow(v1.x - v2.x, 2) + pow(v1.y - v2.y, 2));

}

bool VerticalCheck()
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

		g_thirdLine.x = lastLine.x;
		g_thirdLine.y = g_v[M]->GetBottomPos();
		g_polygon.SetV3(g_thirdLine);
		return false;
	}

	return true;
}

bool HorizontalCheck()
{
	if ((g_line[0].x == g_v[M]->GetLeftPos() || g_line[1].x == g_v[M]->GetLeftPos()) &&
		(g_line[0].x == g_v[M]->GetRightPos() || g_line[1].x == g_v[M]->GetRightPos())) {
		Vector2 v1, v2;
		v1.x = g_v[M]->GetLeftPos();
		v1.y = g_v[M]->GetTopPos();
		v2.x = g_v[M]->GetLeftPos();
		v2.y = g_v[M]->GetBottomPos();

		if (GetDistance(g_line[0], v1) < GetDistance(g_line[0], v2)) lastLine.y = g_v[M]->GetTopPos();
		else lastLine.y = g_v[M]->GetBottomPos();

		g_thirdLine.x = g_v[M]->GetRightPos();
		g_thirdLine.y = lastLine.y;
		g_polygon.SetV3(g_thirdLine);
		return false;

	}

	return true;
}

GLvoid InitObject(GLvoid)
{
	random_device rd;
	mt19937 rng(rd());

	uniform_real_distribution<> dis(0.2f, 0.33f);
	float size = dis(rng);
	for (int i = 0; i < POSITION::END; ++i) {
		unique_ptr<CRect> rect(new CRect(static_cast<POSITION>(i), size));
		g_v.push_back(move(rect));
	}
}

GLvoid Key(unsigned char key, int x, int y)
{
	switch (key) {
	case 'q':
	case 'Q': ResetObject(); break;
	}
}

GLvoid ClearObject(GLvoid)
{
	g_v.clear();
	MOUSEMANAGER->GetPosList().clear();

	ZeroMemory(&g_line, sizeof(g_line));
	ZeroMemory(&lastLine, sizeof(lastLine));
	ZeroMemory(&g_thirdLine, sizeof(g_thirdLine));
	ZeroMemory(&g_polygon, sizeof(g_polygon));
	ZeroMemory(&g_whitePolygon, sizeof(g_whitePolygon));
}

GLvoid ResetObject(GLvoid)
{
	ClearObject();
	InitObject();
}

GLvoid CheckCollision()
{
	// Let's check collision

	// Left
	if (g_polygon.GetDrop()) {
		if (g_polygon.GetPolygonBottomPos() < g_v[BASKET]->GetTopPos() &&
			g_polygon.GetPolygonTopPos() > g_v[BASKET]->GetBottomPos() &&
			(g_polygon.GetPolygonLeftPos() < g_v[BASKET]->GetLeftPos() &&
				g_polygon.GetPolygonRightPos() > g_v[BASKET]->GetLeftPos() + 0.02f)) {
			g_polygon.StopDrop();
			g_v[BASKET]->StopMove();
			Vector2 pos;
			pos.x = g_polygon.GetPos().x;
			pos.y = g_polygon.GetPos().y + (g_v[BASKET]->GetTopPos() - g_polygon.GetPolygonBottomPos());
			g_polygon.SetPos(pos);
		}

		// Right
		if (g_polygon.GetPolygonBottomPos() < g_v[BASKET]->GetTopPos() &&
			g_polygon.GetPolygonTopPos() > g_v[BASKET]->GetBottomPos() &&
			(g_polygon.GetPolygonLeftPos() > g_v[BASKET]->GetRightPos() - 0.02f &&
				g_polygon.GetPolygonRightPos() < g_v[BASKET]->GetRightPos())) {
			g_polygon.StopDrop();
			g_v[BASKET]->StopMove();
			Vector2 pos;
			pos.x = g_polygon.GetPos().x;
			pos.y = g_polygon.GetPos().y + (g_v[BASKET]->GetTopPos() - g_polygon.GetPolygonBottomPos());
			g_polygon.SetPos(pos);
		}

		if (g_polygon.GetPolygonBottomPos() < g_v[BASKET]->GetBottomPos() &&
			g_polygon.GetPolygonTopPos() > g_v[BASKET]->GetBottomPos() &&
			(g_polygon.GetPolygonLeftPos() > g_v[BASKET]->GetLeftPos() &&
				g_polygon.GetPolygonRightPos() < g_v[BASKET]->GetRightPos())) {
			g_polygon.StopDrop();
			g_v[BASKET]->StopMove();
			Vector2 pos;
			pos.x = g_polygon.GetPos().x;
			pos.y = g_polygon.GetPos().y + (g_v[BASKET]->GetBottomPos() - g_polygon.GetPolygonBottomPos());
			g_polygon.SetPos(pos);
			g_drawWaterPart = true;
		}

	}

}

GLvoid DrawWaterPart()
{
	
	glColor4f(85.0f / 255.0f, 134.0f / 255.0f, 235.0f / 255.0f, 1.0f);
	Vector2 v1, v2;
	v1.x = g_polygon.GetPolygonLeftPos();
	v1.y = g_polygon.GetPolygonTopPos();
	v2.x = g_polygon.GetPolygonRightPos();
	v2.y = g_polygon.GetPolygonBottomPos();
	float dif = g_polygon.GetPolygonRightPos() - g_polygon.GetPolygonLeftPos();
	glBegin(GL_LINE_LOOP);
	glVertex2f(g_polygon.GetPolygonLeftPos(), g_polygon.GetPolygonBottomPos());
	glVertex2f(g_polygon.GetPolygonLeftPos(), g_polygon.GetPolygonTopPos());
	glVertex2f(g_polygon.GetPolygonRightPos(), g_polygon.GetPolygonTopPos());
	glVertex2f(g_polygon.GetPolygonRightPos(), g_polygon.GetPolygonBottomPos());
	/*
	Vector2 v1, v2;
	v1.x = g_polygon.GetPolygonLeftPos();
	v1.y = g_polygon.GetPolygonTopPos();
	v2.x = g_polygon.GetPolygonRightPos();
	v2.y = g_polygon.GetPolygonBottomPos();
	float dif = g_polygon.GetPolygonRightPos() - g_polygon.GetPolygonLeftPos();
	glVertex2f(g_v[BASKET]->GetLeftPos(), g_v[BASKET]->GetWaterHeight());
	glVertex2f((g_v[BASKET]->GetLeftPos() + GetDistance(v1, v2) / g_v[BASKET]->GetDevide()) - dif  , g_v[BASKET]->GetWaterHeight());
	glEnd();
	*/
	/*
	glPushMatrix();
	glTranslatef(0.0f, g_polygon.GetPos().y, 0.0f);
	glBegin(GL_LINE_LOOP);
	glVertex2f(g_polygon.GetV1().x, g_polygon.GetV1().y);
	glVertex2f(g_polygon.GetV2().x, g_polygon.GetV2().y);
	if(g_polygon.HaveV3()) glVertex2f(g_polygon.GetV3().x, g_polygon.GetV3().y);
	glVertex2f(g_polygon.GetV4().x, g_polygon.GetV4().y);
	*/
	glEnd();
	//glPopMatrix();
	

}

