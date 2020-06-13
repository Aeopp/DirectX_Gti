#include "UCore.h"
#include "UWindow.h"
#include "UDevice.h"
#include "UTimer.h"
#include "UInput.h"
#include "USound.h"
#include "UWorld.h"

bool UCore::Init()
{
	return true;
}

bool UCore::Frame(float DeltaTime)
{
	return true;
}

bool UCore::PreRender(float DeltaTime)
{
	float clearcolor[4] = { 1.f,0.f,0.f,1 };
	UDevice::Instance().D3DContext->ClearRenderTargetView(UDevice::Instance().RTV, clearcolor);
	UWorld::Instance().Render(DeltaTime);

	return true;
}

bool UCore::Render(float DeltaTime)
{
	return true;
}

bool UCore::PostRender(float DeltaTime)
{
	UDevice::Instance().SwapChain->Present(1, 0);

	return true;
}

bool UCore::Release()
{
	return true;
}

bool UCore::CoreInit()
{
	UTimer::Instance().Init();
	UInput::Instance().Init();
	USound::Instance().Init();
	UWorld::Instance().Init();

	{
		auto&& __CurrentClientRect = UWindow::Instance().GetClientFRect();
		if (UDevice::Instance().SetD3DDevice(
			static_cast<UINT>(__CurrentClientRect.right),
			static_cast<UINT>(__CurrentClientRect.bottom)) == false) {
			return false;
		}
	}

	HRESULT hr = UDevice::Instance().GIFactory->MakeWindowAssociation(UWindow::Instance().hWnd, 0);

	if (FAILED(hr)) {
		return false;
	}

	Init();
	return true;
}

bool UCore::CoreFrame(float DeltaTime)
{
	UTimer::Instance().Frame();
	UInput::Instance().Frame();
	USound::Instance().Frame();
	UWorld::Instance().Frame(DeltaTime);

	if (UInput::Instance().KeyState[DIK_ESCAPE] & 0x80) {
		UWindow::Instance().bExit = true;
		return false;
	};

	Frame(DeltaTime);
	return true;
}

bool UCore::CoreRender(float DeltaTime)
{
	PreRender(DeltaTime);
	Render(DeltaTime);
	PostRender(DeltaTime);
	return true;
}

bool UCore::CoreRelease()
{
	Release();
	UTimer::Instance().Release();
	UInput::Instance().Release();
	USound::Instance().Release();
	UWorld::Instance().Release();
	UDevice::Instance().ReleaseDevice();

	return true;
}

bool UCore::Run()&
{
	CoreInit();
	while (UWindow::Instance().bExit == false) {
		if (UWindow::Instance().WinRun()) {
			const float CurrentDeltaTime = UTimer::Instance().GetDeltaTime();

			CoreFrame(CurrentDeltaTime);
			CoreRender(CurrentDeltaTime);
		}
	}
	CoreRelease();
	return true;
}

UCore::UCore()
{
}

UCore::~UCore()
{
}
