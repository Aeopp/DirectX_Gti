#include "UGame.h"

#include "UWindow.h"
#include "USound.h"
#include "UInput.h"
#include "UTimer.h"
#include "UDevice.h"
#include "UWorld.h"
#include "APlayer.h"
#include "UMesh.h"

#include "DX_Header.h"
#include "DataTable.h"


#include <Windows.h>
#include <string_view>
#include <helper.h>
using namespace std::string_view_literals;
using namespace std::string_literals;

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nCmdShow) {
	if (UWindow::Instance().SetWindow(hInstance)) {
		UGame::Instance().Run();
	}
}

bool UGame::Render(float DeltaTime)
{
	return true; 
}

bool UGame::Init()
{
	USound::Instance().Load((path::s::DefaultResourcePath + path::s::TimeGame ));
	USound::Instance().Load((path::s::DefaultResourcePath + path::s::WhenTheMorningComess));

	UInput::Instance().EventRegist(
		[SoundPath = path::s::DefaultResourcePath +path::s::TimeGame](float) {
		USound::Instance().Play(SoundPath,true);
	},EKeyState::Press, DIK_F1);

	UInput::Instance().EventRegist(
		[SoundPath = path::s::DefaultResourcePath + path::s::WhenTheMorningComess](float) {
		USound::Instance().Play(SoundPath,true);
	}, EKeyState::Press, DIK_F2);
	
	auto Temp = [hWnd = UWindow::Instance().hWnd](float) {
			if (hWnd != nullptr) {
				MessageBox(hWnd, L"OnceEvent 5초지남", L"OnceEvent 5초지남", NULL);
			}
		};
	UTimer::Instance().EventRegist(Temp, UTimer::ECategory::Once, 5.f);
	
	auto Temp2 = [hWnd = UWindow::Instance().hWnd](float) {
		if (hWnd != nullptr) {
			MessageBox(hWnd, L"LoopEvent  10초지남", L"LoopEvent 10지남", NULL);
		}
	};
	UTimer::Instance().EventRegist(Temp2, UTimer::ECategory::Loop,10.f);


	IDXGISurface* Surface = nullptr;
	UDevice::Instance().SwapChain->GetBuffer(0,__uuidof(IDXGISurface),(void**)&Surface);

	DX::Safe_Release(Surface);


	return true;
}

bool UGame::Frame(float DeltaTime)
{
	return true;
}

bool UGame::Release()
{
	
	return true;
}
UGame::UGame() {};
UGame::~UGame() noexcept {};