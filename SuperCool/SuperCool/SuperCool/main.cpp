#include "Define.h"
#include "CWnd.h"

//#pragma comment(linker , "/entry:WinMainCRTStartup /subsystem:console")

CWnd Wnd;

LRESULT CALLBACK WndProc(HWND hWnd, UINT uiMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uiMsg)
	{

	case WM_CLOSE:
		PostQuitMessage(0);
		break;

	case WM_KEYDOWN:
		Wnd.OnKeyDown((UINT)wParam);
		break;

	case WM_LBUTTONDOWN:
		Wnd.OnLButtonDown(LOWORD(lParam), HIWORD(lParam));
		break;

	case WM_MOUSEMOVE:
		Wnd.OnMouseMove(LOWORD(lParam), HIWORD(lParam));
		break;

	case 0x020A: // WM_MOUSWHEEL
		Wnd.OnMouseWheel(HIWORD(wParam));
		break;

	case WM_PAINT:
		Wnd.OnPaint();
		break;

	case WM_RBUTTONDOWN:
		Wnd.OnRButtonDown(LOWORD(lParam), HIWORD(lParam));
		break;

	case WM_SIZE:
		Wnd.OnSize(LOWORD(lParam), HIWORD(lParam));
		break;

	default:
		return DefWindowProc(hWnd, uiMsg, wParam, lParam);
	}

	return 0;
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR sCmdLine, int iShow)
{
	if (Wnd.Create(hInstance, "", WINDOW_WIDTH, WINDOW_HEIGHT))
	{
		Wnd.Show(true);
		Wnd.MessageLoop();
	}
	else cout << "Error" << endl;
	
	Wnd.Destroy();

	return 0;

}

