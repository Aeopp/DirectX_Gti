#pragma once
#include "SingleTon.h"
#include "FMath.h"
#include <Windows.h>


class UWindow : public SingleTon<UWindow>
{
public :
	HINSTANCE hInstance{ nullptr }; 
	HWND hWnd{ nullptr }; 
	bool bExit{ false }; 

	FRect RectWindow{}; 
	FRect RectClient{}; 
private:
	MSG msg{}; 
public :
	inline FRect GetClientFRect() const&{
		return RectClient;
	}
	inline FRect GetWindowFRect() {
		return RectWindow;
	}
	bool SetWindow(HINSTANCE hInstance)&;
	bool WinRun()&;
	virtual LRESULT MsgProc(HWND hWnd,UINT msg,WPARAM wParam,LPARAM lParam);
	virtual bool GameRun()&;
public:
	UWindow();
	virtual ~UWindow();
};

