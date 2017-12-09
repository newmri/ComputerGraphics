#pragma once


LRESULT CALLBACK WndProc(HWND hWnd, UINT uiMsg, WPARAM wParam, LPARAM lParam);
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR sCmdLine, int iShow);


class CWnd
{
protected:
	HWND hWnd;
	HDC hDC;
	HGLRC hGLRC;
	char *WindowName;
	int Width, Height, Samples;
	POINT LastCurPos;

public:
	CWnd();
	~CWnd();

	bool Create(HINSTANCE hInstance, char *WindowName, int Width, int Height, int Samples = 4, bool CreateForwardCompatibleContext = false, bool DisableVerticalSynchronization = true);
	void Show(bool Maximized = false);
	void MessageLoop();
	void Destroy();

	void OnKeyDown(UINT Key);
	void OnLButtonDown(int cx, int cy);
	void OnMouseMove(int cx, int cy);
	void OnMouseWheel(short zDelta);
	void OnPaint();
	void OnRButtonDown(int cx, int cy);
	void OnSize(int Width, int Height);
};