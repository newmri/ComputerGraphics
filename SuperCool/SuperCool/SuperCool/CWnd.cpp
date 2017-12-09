#include "Define.h"
#include "CWnd.h"

// ----------------------------------------------------------------------------------------------------------------------------

CString ModuleDirectory, ErrorLog;

bool wgl_context_forward_compatible = false;

int gl_version = 0, use_gl_version = 21, gl_max_texture_size = 0, gl_max_texture_max_anisotropy_ext = 0;

// ----------------------------------------------------------------------------------------------------------------------------

CWnd::CWnd()
{
	char *moduledirectory = new char[256];
	GetModuleFileName(GetModuleHandle(NULL), moduledirectory, 256);
	*(strrchr(moduledirectory, '\\') + 1) = 0;
	ModuleDirectory = moduledirectory;
	delete[] moduledirectory;
}

CWnd::~CWnd()
{
}

bool CWnd::Create(HINSTANCE hInstance, char *WindowName, int Width, int Height, int Samples, bool CreateForwardCompatibleContext, bool DisableVerticalSynchronization)
{
	WNDCLASSEX WndClassEx;

	memset(&WndClassEx, 0, sizeof(WNDCLASSEX));

	WndClassEx.cbSize = sizeof(WNDCLASSEX);
	WndClassEx.style = CS_OWNDC | CS_HREDRAW | CS_VREDRAW;
	WndClassEx.lpfnWndProc = WndProc;
	WndClassEx.hInstance = hInstance;
	WndClassEx.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	WndClassEx.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
	WndClassEx.hCursor = LoadCursor(NULL, IDC_ARROW);
	WndClassEx.lpszClassName = "Win32OpenGLWindowClass";

	if (RegisterClassEx(&WndClassEx) == 0)
	{
		ErrorLog.SetString("RegisterClassEx failed!");
		return false;
	}

	this->WindowName = WindowName;

	this->Width = Width;
	this->Height = Height;

	DWORD Style = WS_OVERLAPPEDWINDOW | WS_CLIPSIBLINGS | WS_CLIPCHILDREN;

	if ((hWnd = CreateWindowEx(WS_EX_APPWINDOW, WndClassEx.lpszClassName, WindowName, Style, 0, 0, Width, Height, NULL, NULL, hInstance, NULL)) == NULL)
	{
		ErrorLog.SetString("CreateWindowEx failed!");
		return false;
	}

	if ((hDC = GetDC(hWnd)) == NULL)
	{
		ErrorLog.SetString("GetDC failed!");
		return false;
	}

	PIXELFORMATDESCRIPTOR pfd;

	memset(&pfd, 0, sizeof(PIXELFORMATDESCRIPTOR));

	pfd.nSize = sizeof(PIXELFORMATDESCRIPTOR);
	pfd.nVersion = 1;
	pfd.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
	pfd.iPixelType = PFD_TYPE_RGBA;
	pfd.cColorBits = 32;
	pfd.cDepthBits = 24;
	pfd.iLayerType = PFD_MAIN_PLANE;

	int PixelFormat;

	if ((PixelFormat = ChoosePixelFormat(hDC, &pfd)) == 0)
	{
		ErrorLog.SetString("ChoosePixelFormat failed!");
		return false;
	}

	static int MSAAPixelFormat = 0;

	if (SetPixelFormat(hDC, MSAAPixelFormat == 0 ? PixelFormat : MSAAPixelFormat, &pfd) == FALSE)
	{
		ErrorLog.SetString("SetPixelFormat failed!");
		return false;
	}

	if ((hGLRC = wglCreateContext(hDC)) == NULL)
	{
		ErrorLog.SetString("wglCreateContext failed!");
		return false;
	}

	if (wglMakeCurrent(hDC, hGLRC) == FALSE)
	{
		ErrorLog.SetString("wglMakeCurrent failed!");
		return false;
	}

	if (glewInit() != GLEW_OK)
	{
		ErrorLog.SetString("glewInit failed!");
		return false;
	}

	if (MSAAPixelFormat == 0 && Samples > 0)
	{
		if (GLEW_ARB_multisample && WGLEW_ARB_pixel_format)
		{
			while (Samples > 0)
			{
				UINT NumFormats = 0;

				int iAttributes[] =
				{
					WGL_DRAW_TO_WINDOW_ARB, GL_TRUE,
					WGL_SUPPORT_OPENGL_ARB, GL_TRUE,
					WGL_DOUBLE_BUFFER_ARB, GL_TRUE,
					WGL_PIXEL_TYPE_ARB, WGL_TYPE_RGBA_ARB,
					WGL_COLOR_BITS_ARB, 32,
					WGL_DEPTH_BITS_ARB, 24,
					WGL_ACCELERATION_ARB, WGL_FULL_ACCELERATION_ARB,
					WGL_SAMPLE_BUFFERS_ARB, GL_TRUE,
					WGL_SAMPLES_ARB, Samples,
					0
				};

				if (wglChoosePixelFormatARB(hDC, iAttributes, NULL, 1, &MSAAPixelFormat, &NumFormats) == TRUE && NumFormats > 0) break;

				Samples--;
			}

			wglDeleteContext(hGLRC);

			DestroyWindow(hWnd);

			UnregisterClass(WndClassEx.lpszClassName, hInstance);

			return Create(hInstance, WindowName, Width, Height, Samples, CreateForwardCompatibleContext, DisableVerticalSynchronization);
		}
		else
		{
			Samples = 0;
		}
	}

	this->Samples = Samples;

	int major, minor;

	sscanf_s((char*)glGetString(GL_VERSION), "%d.%d", &major, &minor);

	gl_version = major * 10 + minor;

	if (CreateForwardCompatibleContext && gl_version >= 30 && WGLEW_ARB_create_context)
	{
		wglDeleteContext(hGLRC);

		int GLFCRCAttribs[] =
		{
			WGL_CONTEXT_MAJOR_VERSION_ARB, major,
			WGL_CONTEXT_MINOR_VERSION_ARB, minor,
			WGL_CONTEXT_FLAGS_ARB, WGL_CONTEXT_FORWARD_COMPATIBLE_BIT_ARB,
			0
		};

		if ((hGLRC = wglCreateContextAttribsARB(hDC, 0, GLFCRCAttribs)) == NULL)
		{
			ErrorLog.SetString("wglCreateContextAttribsARB failed!");
			return false;
		}

		if (wglMakeCurrent(hDC, hGLRC) == FALSE)
		{
			ErrorLog.SetString("wglMakeCurrent failed!");
			return false;
		}

		wgl_context_forward_compatible = true;
	}
	else
	{
		wgl_context_forward_compatible = false;
	}

	glGetIntegerv(GL_MAX_TEXTURE_SIZE, &gl_max_texture_size);

	if (GLEW_EXT_texture_filter_anisotropic)
	{
		glGetIntegerv(GL_MAX_TEXTURE_MAX_ANISOTROPY_EXT, &gl_max_texture_max_anisotropy_ext);
	}

	if (DisableVerticalSynchronization && WGLEW_EXT_swap_control)
	{
		wglSwapIntervalEXT(0);
	}

	RENDERMANAGER->Init();
	return true;
}

void CWnd::Show(bool Maximized)
{
	RECT dRect, wRect, cRect;

	GetWindowRect(GetDesktopWindow(), &dRect);
	GetWindowRect(hWnd, &wRect);
	GetClientRect(hWnd, &cRect);

	wRect.right += Width - cRect.right;
	wRect.bottom += Height - cRect.bottom;

	wRect.right -= wRect.left;
	wRect.bottom -= wRect.top;

	wRect.left = dRect.right / 2 - wRect.right / 2;
	wRect.top = dRect.bottom / 2 - wRect.bottom / 2;

	MoveWindow(hWnd, wRect.left, wRect.top, wRect.right, wRect.bottom, FALSE);

	ShowWindow(hWnd, Maximized ? SW_SHOWMAXIMIZED : SW_SHOWNORMAL);
}

void CWnd::MessageLoop()
{
	MSG Msg;

	while (GetMessage(&Msg, NULL, 0, 0) > 0)
	{
		TranslateMessage(&Msg);
		DispatchMessage(&Msg);
	}
}

void CWnd::Destroy()
{

	wglDeleteContext(hGLRC);

	DestroyWindow(hWnd);
}

void CWnd::OnKeyDown(UINT Key)
{
	switch (Key)
	{
	case VK_F1:
		//OpenGLRenderer.ShowAxisGrid = !OpenGLRenderer.ShowAxisGrid;
		break;

	case VK_F2:
		//OpenGLRenderer.WireFrame = !OpenGLRenderer.WireFrame;
		break;

	case VK_F3:
		//OpenGLRenderer.Texturing = !OpenGLRenderer.Texturing;
		break;

	case '1':
		use_gl_version = 11;
		break;

	case '2':
		use_gl_version = 15;
		break;

	case '3':
		use_gl_version = 21;
		break;

	case 'i': CAMERAMANAGER->Reset(); break;

	}
}

void CWnd::OnLButtonDown(int cx, int cy)
{
	RENDERMANAGER->SelectObject(cx, cy);
}

void CWnd::OnMouseMove(int cx, int cy)
{
	if (GetKeyState(VK_LBUTTON) & 0x80)
	{
		//RENDERMANAGER->MoveSelectedObject(cx, cy);
	}

	if (GetKeyState(VK_RBUTTON) & 0x80){
		CAMERAMANAGER->OnMouseMove(LastCurPos.x - cx, LastCurPos.y - cy);

		LastCurPos.x = cx;
		LastCurPos.y = cy;
	}
}

void CWnd::OnMouseWheel(short zDelta)
{
	CAMERAMANAGER->OnMouseWheel(zDelta);
}

void CWnd::OnPaint()
{
	PAINTSTRUCT ps;

	BeginPaint(hWnd, &ps);

	static DWORD LastFPSTime = GetTickCount(), LastFrameTime = LastFPSTime;
	static int FPS = 0;

	DWORD Time = GetTickCount();

	float FrameTime = (Time - LastFrameTime) * 0.001f;

	LastFrameTime = Time;

	if (Time - LastFPSTime > 1000)
	{
		CString Text = WindowName;
		CString fps;

		fps.Format(" FPS: %d", FPS);
		Text.Append(fps);

		SetWindowText(hWnd, Text);

		LastFPSTime = Time;
		FPS = 0;
	}
	else
	{
		FPS++;
	}

	BYTE Keys = 0x00;

	if (GetKeyState('W') & 0x80) Keys |= 0x01;
	if (GetKeyState('S') & 0x80) Keys |= 0x02;
	if (GetKeyState('A') & 0x80) Keys |= 0x04;
	if (GetKeyState('D') & 0x80) Keys |= 0x08;
	if (GetKeyState('R') & 0x80) Keys |= 0x10;
	if (GetKeyState('F') & 0x80) Keys |= 0x20;

	if (GetKeyState(VK_SHIFT) & 0x80) Keys |= 0x40;

	if (Keys & 0x3F)
	{
		Vector3 Movement = CAMERAMANAGER->OnKeys(Keys, FrameTime);
		CAMERAMANAGER->Move(Movement);
	}

	RENDERMANAGER->Render(FrameTime);
	SwapBuffers(hDC);

	EndPaint(hWnd, &ps);

	InvalidateRect(hWnd, NULL, FALSE);
}

void CWnd::OnRButtonDown(int cx, int cy)
{
	LastCurPos.x = cx;
	LastCurPos.y = cy;
}

void CWnd::OnSize(int Width, int Height)
{
	this->Width = Width;
	this->Height = Height;

	RENDERMANAGER->Resize(Width, Height);
}