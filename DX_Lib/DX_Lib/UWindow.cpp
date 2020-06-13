#include "UWindow.h"
#include "UDevice.h"

LRESULT CALLBACK WndProc(
	HWND hWnd,
	UINT msg,
	WPARAM wParam,
	LPARAM lParam)
{
	/*assert(g_pWindow);*/
	return UWindow::Instance().MsgProc(hWnd, msg, wParam, lParam);
}

bool UWindow::SetWindow(HINSTANCE hInstance)&
{
	this->hInstance = hInstance;

	// 1, 생성할 윈도우클래스 운영체제 등록
	WNDCLASSEXW wc;
	ZeroMemory(&wc, sizeof(WNDCLASSEXW));
	wc.cbSize = sizeof(WNDCLASSEXW);
	wc.hInstance = hInstance;
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.lpszClassName = L"KGCAWIN";
	wc.lpfnWndProc = WndProc;
	wc.hbrBackground = (HBRUSH)GetStockObject(GRAY_BRUSH);
	if (RegisterClassEx(&wc) == false)
	{
		return false;
	}
	RECT rt = { 0,0,800,600 };
	AdjustWindowRect(&rt, WS_OVERLAPPEDWINDOW, FALSE);
	// 2, 등록된 윈도우클래스로 윈도우 생성
	hWnd = CreateWindowEx(0,
		L"KGCAWIN",
		L"SAMPLEWINDOW",
		WS_OVERLAPPEDWINDOW,//WS_POPUPWINDOW,//WS_OVERLAPPEDWINDOW,
		0,
		0,
		rt.right - rt.left,
		rt.bottom - rt.top,
		0, 0, hInstance, 0);

	if (hWnd  == NULL) return 1;
	RECT client_rect, window_rect;

	GetClientRect(hWnd, &client_rect);
	GetWindowRect(hWnd, &window_rect);

	RectClient = FRect{ client_rect.left,client_rect.top,client_rect.right,client_rect.bottom };
	RectWindow = FRect{ window_rect.left,window_rect.top,window_rect.right,window_rect.bottom };

	ShowWindow(hWnd, SW_SHOW);
	return true;
}

bool UWindow::WinRun()&
{
	if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
		if (msg.message == WM_QUIT)
		{
			bExit = true;
		}
		return false;
	}
	return true;
}

LRESULT UWindow::MsgProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_SIZE:
	{
		UINT width = LOWORD(lParam);
		UINT height = HIWORD(lParam);
		UDevice::Instance().ResizeDevice(width, height);
		RECT __ClientRect;
		RECT __WindowRect;
		GetClientRect(hWnd, &__ClientRect);
		GetWindowRect(hWnd, &__WindowRect);
		RectClient = __ClientRect;
		RectWindow = __WindowRect;
	}break;
	case WM_DESTROY:
	{
		PostQuitMessage(0);
	}break;
	}
	return DefWindowProc(hWnd, msg, wParam, lParam);
}

bool UWindow::GameRun()&
{
	return true;
}

UWindow::UWindow()
{
	ZeroMemory(&msg, sizeof(MSG));
}

UWindow::~UWindow()
{
}
