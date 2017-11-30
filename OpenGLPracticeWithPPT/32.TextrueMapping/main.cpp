#include "Define.h"

GLvoid Init(GLvoid);
GLvoid SetUpRC();
GLvoid Idle(GLvoid);
GLvoid RenderScene(GLvoid);
GLvoid Reshape(int w, int h);
GLvoid Animate(int n);
GLvoid Keyboard(unsigned char key, int x, int y);
GLvoid Mouse(int button, int state, int x, int y);
GLvoid Rotate();
GLvoid Update();
GLvoid Render();
GLvoid MenuFunc(int button);



GLubyte* LoadDIBitmap(const char* filename, BITMAPINFO** info);

const unsigned int ANIMATION_TIME = 1000 / 30;


int winId;

float g_yAngle = 45.0f;
float g_frontOpen = false;
float g_frontZ = 0.0f;
float g_topOpen = false;
float g_topZ = 0.0f;

GLuint texture[2];
GLubyte* bytes;
BITMAPINFO* info;

void main(int argc, char* argv[])
{

	Init();

	winId = glutCreateWindow("32.TextrueMapping");
	SetUpRC();
	glutDisplayFunc(RenderScene);
	glutReshapeFunc(Reshape);
	glutKeyboardFunc(Keyboard);
	glutMouseFunc(Mouse);
	glutTimerFunc(ANIMATION_TIME, Animate, true);
	glutAttachMenu(GLUT_RIGHT_BUTTON);
	glutMainLoop();
}


GLvoid Init(GLvoid)
{
	srand((unsigned int)time(NULL));
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	glFrontFace(GL_CCW);

	glutInitWindowPosition(100, 100);
	glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);

	int subMenu = glutCreateMenu(MenuFunc);
	glutAddMenuEntry("Hidden Surface Delete On", HIDDEN_SURFAE_DELETE_ON);
	glutAddMenuEntry("Hidden Surface Delete off", HIDDEN_SURFACE_DELETE_OFF);
	glutAddMenuEntry("Culling On", CULLING_ON);
	glutAddMenuEntry("Culling off", CULLING_OFF);
	glutAddMenuEntry("Flat On", SHADING_FLAT);
	glutAddMenuEntry("Smooth On", SHADING_SMOOTH);
	glutAddMenuEntry("Front Side Open", FRONT_OPEN);
	glutAddMenuEntry("Front Side Close", FRONT_CLOSE);
	glutAddMenuEntry("Top Side Open", TOP_OPEN);
	glutAddMenuEntry("Top Side Close", TOP_CLOSE);
	int mainMenu = glutCreateMenu(MenuFunc);
	glutAddSubMenu("Select", subMenu);


}

GLvoid SetUpRC()
{
	// Image texture mapping n images

	glGenTextures(2, texture);

	// Bind texture and object
	glBindTexture(GL_TEXTURE_2D, texture[0]);
	// Load Image
	bytes = LoadDIBitmap("1.bmp", &info);
	// Set setting of textrue
	glTexImage2D(GL_TEXTURE_2D, 0, 3, 512, 512, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, bytes);
	// Set parameter
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	
	// Bind texture and object
	glBindTexture(GL_TEXTURE_2D, texture[1]);
	// Load Image
	bytes = LoadDIBitmap("2.bmp", &info);
	// Set setting of textrue
	glTexImage2D(GL_TEXTURE_2D, 0, 3, 512, 512, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, bytes);
	// Set parameter
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);


	// Set texture mode
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_COLOR, GL_MODULATE);
	glEnable(GL_TEXTURE_2D);

	glEnable(GL_DEPTH_TEST);
}

GLvoid RenderScene(GLvoid)
{
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // 바탕색을 'Black' 로 지정
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	Update();
	Render();

	glutSwapBuffers(); // Draw
}

GLvoid Reshape(int w, int h)
{
	glViewport(0, 0, w, h); // Change viewport with window size
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(REAL_WINDOW_WIDTH, WINDOW_WIDTH / WINDOW_HEIGHT, 1.0f, WINDOW_DEPTH); // Use perspective
	glTranslatef(0.0f, 0.0f, -80.0f);

}


GLvoid Animate(int n)
{
	RenderScene();
	glutTimerFunc(ANIMATION_TIME, Animate, true);
}


GLvoid Keyboard(unsigned char key, int x, int y)
{
	switch (key) {
	case 'x':
	case 'X':
	case 'y':
	case 'Y':
	case 'z':
	case 'Z': CAMERAMANAGER->SetRotate(key); break;

	case 'w':
	case 's':
	case 'a':
	case 'd':
	case 'q':
	case 'e':
	case '+':
	case '-': CAMERAMANAGER->SetMove(key); break;
	case 'i': CAMERAMANAGER->Reset(); break;

	default: break;
	}
	RenderScene();
}


GLvoid Mouse(int button, int state, int x, int y)
{
	RenderScene();
}


GLvoid Update()
{
	int ret{};
	CAMERAMANAGER->Update();
	if (g_yAngle >= MAX_DEGREE) g_yAngle = 0.0f;
	else g_yAngle += 1.0f;

	if (g_frontOpen) { if (g_frontZ < CUBE_RAD * 2.0f)  g_frontZ += 0.1f; }
	else { if (g_frontZ > 0) g_frontZ -= 0.1f; }

	if (g_topOpen) { if (g_topZ < CUBE_RAD * 2.0f)  g_topZ += 0.1f; }
	else { if (g_topZ > 0) g_topZ -= 0.1f; }
}

GLvoid Render()
{
	glPushMatrix();
	glRotatef(30.0f, 1.0f, 0.0f, 0.0f);
	glRotatef(g_yAngle, 0.0f, 1.0f, 0.0f);

	glBindTexture(GL_TEXTURE_2D, texture[0]);
	glBegin(GL_QUADS);
	// Mapping
	// Front
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(CUBE_RAD, CUBE_RAD, 0.0f); // Top Right
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(-CUBE_RAD + g_frontZ, CUBE_RAD, g_frontZ); // Top Left
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(-CUBE_RAD + g_frontZ, -CUBE_RAD, g_frontZ); // Bottom Left
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(CUBE_RAD, -CUBE_RAD, 0.0f); // Bottom Right
	glEnd();

	glBindTexture(GL_TEXTURE_2D, texture[1]);
	glBegin(GL_QUADS);
	// Back
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(CUBE_RAD, CUBE_RAD, -CUBE_RAD * 2.0f); // Top Right
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(-CUBE_RAD, CUBE_RAD, -CUBE_RAD * 2.0f); // Top Left
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(-CUBE_RAD, -CUBE_RAD, -CUBE_RAD * 2.0f); // Bottom Left
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(CUBE_RAD, -CUBE_RAD, -CUBE_RAD * 2.0f); // Bottom Right
	glEnd();
	
	glBindTexture(GL_TEXTURE_2D, texture[0]);
	glBegin(GL_QUADS);
	// Top
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(CUBE_RAD, CUBE_RAD, -CUBE_RAD * 2.0f); // Top Right
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(-CUBE_RAD, CUBE_RAD, -CUBE_RAD * 2.0f); // Top Left
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(-CUBE_RAD, CUBE_RAD + g_topZ, -g_topZ); // Bottom Left
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(CUBE_RAD, CUBE_RAD + g_topZ, -g_topZ); // Bottom Right
	glEnd();

	glBindTexture(GL_TEXTURE_2D, texture[1]);
	glBegin(GL_QUADS);
	// Bottom
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(CUBE_RAD, -CUBE_RAD, -CUBE_RAD * 2.0f); // Top Right
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(-CUBE_RAD, -CUBE_RAD, -CUBE_RAD * 2.0f); // Top Left
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(-CUBE_RAD, -CUBE_RAD, 0.0f); // Bottom Left
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(CUBE_RAD, -CUBE_RAD, 0.0f); // Bottom Right
	glEnd();

	glBindTexture(GL_TEXTURE_2D, texture[0]);
	glBegin(GL_QUADS);
    // Left
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(-CUBE_RAD, CUBE_RAD, 0.0f); // Top Right
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(-CUBE_RAD, CUBE_RAD, -CUBE_RAD * 2.0f); // Top Left
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(-CUBE_RAD, -CUBE_RAD, -CUBE_RAD * 2.0f); // Bottom Left
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(-CUBE_RAD, -CUBE_RAD, 0.0f); // Bottom Right
	glEnd();

	glBindTexture(GL_TEXTURE_2D, texture[1]);
	glBegin(GL_QUADS);
	// Right
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(CUBE_RAD, CUBE_RAD, -CUBE_RAD * 2.0f);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(CUBE_RAD, CUBE_RAD, 0.0f);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(CUBE_RAD, -CUBE_RAD, 0.0f);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(CUBE_RAD, -CUBE_RAD, -CUBE_RAD * 2.0f);
	glEnd();
	

	
	glPopMatrix();
}

GLvoid MenuFunc(int button)
{
	switch (button) {
	case HIDDEN_SURFAE_DELETE_ON: glEnable(GL_DEPTH_TEST); break;
	case HIDDEN_SURFACE_DELETE_OFF: glDisable(GL_DEPTH_TEST); break;
	case CULLING_ON: glEnable(GL_CULL_FACE); glCullFace(GL_BACK); break;
	case CULLING_OFF: glDisable(GL_CULL_FACE); break;
	case SHADING_FLAT: 	glShadeModel(GL_FLAT); break;
	case SHADING_SMOOTH: 	glShadeModel(GL_SMOOTH); break;
	case FRONT_OPEN: 	g_frontOpen = true; break;
	case FRONT_CLOSE: 	g_frontOpen = false; break;
	case TOP_OPEN: 	g_topOpen = true; break;
	case TOP_CLOSE: 	g_topOpen = false; break;
	default: break;
	}
}

GLubyte * LoadDIBitmap(const char *filename, BITMAPINFO **info)
{
	FILE *fp;
	GLubyte *bits;
	int bitsize, infosize;
	BITMAPFILEHEADER header;
	// 바이너리 읽기 모드로 파일을 연다
	if ((fp = fopen(filename, "rb")) == NULL)
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