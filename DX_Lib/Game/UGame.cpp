#include "UGame.h"

#include "UWindow.h"
#include "USound.h"
#include "UInput.h"
#include "UTimer.h"
#include "UDevice.h"
#include "UWorld.h"
#include "APlayer.h"
#include "UMesh.h"
#include "UMeshData.h"

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

bool UGame::Render(float DeltaTime){
	return true; 
}

bool UGame::Init()
{
	USound::Instance().Load((path::s::DefaultResourcePath + path::s::TimeGame ));
	USound::Instance().Load((path::s::DefaultResourcePath + path::s::WhenTheMorningComess));

	UInput::Instance().EventRegist(
		[SoundPath = path::s::DefaultResourcePath +path::s::TimeGame](float) {
		USound::Instance().Play(SoundPath,true);
	},EKeyState::Press, DIK_F5);

	UInput::Instance().EventRegist(
		[SoundPath = path::s::DefaultResourcePath + path::s::WhenTheMorningComess](float) {
		USound::Instance().Play(SoundPath,true);
	}, EKeyState::Press, DIK_F6);

	UInput::Instance().EventRegist([](float) {
		UMeshData::ApplyRastrizerState(UDevice::Instance().GetContext(),
			UMeshData::RSWireFrameBack);
	}, EKeyState::Press, DIK_F6);

	UInput::Instance().EventRegist([](float) {
		UMeshData::ApplyRastrizerState(UDevice::Instance().GetContext(),
			UMeshData::RSSolidNone);
		}, EKeyState::Press, DIK_F7);


	UInput::Instance().EventRegist([](float) {
		UMeshData::ApplyRastrizerState(UDevice::Instance().GetContext(),
			UMeshData::RSSolidFront);
		}, EKeyState::Press, DIK_F8);

	UInput::Instance().EventRegist([](float) {
		UMeshData::ApplyRastrizerState(UDevice::Instance().GetContext(),
			UMeshData::RSSolidBack);
		}, EKeyState::Press, DIK_F9);

	IDXGISurface* Surface = nullptr;
	UDevice::Instance().SwapChain->GetBuffer(0,__uuidof(IDXGISurface),(void**)&Surface);

	DX::Safe_Release(Surface);

	auto Player = UWorld::Instance().CreateActor<APlayer>();
	auto BackGround = UWorld::Instance().CreateActor<AActor>();

	BackGround->SetMesh(UWorld::Instance().CreateObject<UMesh>(BackGround));
	BackGround->GetMesh()->Create(path::w::DefaultMapleResourcePath + L"Hennessy.bmp",
		{ 0.f,0.f,5830.f,3279.f }, BackGround, UMesh::ELayer::BackGround);
	BackGround->SetLocation(FVector3{0,0,0});

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